#include "../src/Emitter.h"

#define BOOST_TEST_MODULE basic
#include <boost/test/included/unit_test.hpp>

class em : public de::Emitter
{
public:
	void emit_fn()
	{
		emit("signal");
	}
};

BOOST_AUTO_TEST_CASE( on_lambda )
{
	em e;
	bool called = false;
	auto fn = [&called](void) { called = true; };

	e.on("signal", fn);
	e.emit_fn();

	BOOST_CHECK(called);
}

void fn(bool& called)
{
	called = true;
}

BOOST_AUTO_TEST_CASE( on_function )
{
	em e;
	bool called = false;
	e.on("signal", std::bind(fn, std::ref(called)));

	e.emit_fn();

	BOOST_CHECK(called);
}

class clfn
{
public:
	void fn(bool& called)
	{
		called = true;
	}
};

BOOST_AUTO_TEST_CASE( on_method )
{
	em e;
	clfn c;
	bool called = false;
	e.on("signal", std::bind(&clfn::fn, &c, std::ref(called)));

	e.emit_fn();

	BOOST_CHECK(called);
}

BOOST_AUTO_TEST_CASE( on_off )
{
	em e;
	bool called = false;
	auto cb = [&called]() { called = true; };

	de::Emitter::id_t cbid = e.on("signal", cb);
	e.emit_fn();
	BOOST_CHECK(called);

	called = false;
	e.off(cbid);
	e.emit_fn();
	BOOST_CHECK_EQUAL(called, false);
}

BOOST_AUTO_TEST_CASE( disable )
{
	em e;
	bool called1 = false, called2 = false;
	auto cb1 = [&called1]() { called1 = true; };
	auto cb2 = [&called2]() { called2 = true; };

	e.on("signal", cb1);
	e.on("signal", cb2);

	e.emit_fn();

	BOOST_CHECK(called1);
	BOOST_CHECK(called2);

	called1 = called2 = false;

	e.disable("signal");
	e.emit_fn();

	BOOST_CHECK_EQUAL(called1, false);
	BOOST_CHECK_EQUAL(called2, false);
}

BOOST_AUTO_TEST_CASE( emit_delete )
{
	em *e = new em();
	e->on("signal", [e]() { delete e; });

	e->emit_fn();

	BOOST_CHECK(true);
}
