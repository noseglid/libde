#include "../src/Emitter.h"

#define BOOST_TEST_MODULE basic
#include <boost/test/included/unit_test.hpp>

class emitter : public de::Emitter<int>
{
public:
	void fn()
	{
		emit("signal", 1);
	}
};

struct datastruct
{
	int i;
	std::string str;
};

class emitter2 : public de::Emitter<datastruct>
{
public:
	void fn()
	{
		struct datastruct ds;
		ds.i = 1;
		ds.str = "MyString";
		emit("signal", ds);
	}
};

BOOST_AUTO_TEST_CASE( simple )
{
	emitter em;

	int param = 0;
	std::function<void(int)> cb = [&param](int a) { param = a; };

	em.on("signal", cb);
	em.fn();

	BOOST_CHECK(1 == param);
}

BOOST_AUTO_TEST_CASE( dstest )
{
	emitter2 em;
	struct datastruct ds;
	std::function<void(struct datastruct)> cb = [&ds](struct datastruct ids) { ds = ids; };

	em.on("signal", cb);
	em.fn();

	BOOST_CHECK(ds.i == 1);
	BOOST_CHECK(ds.str == "MyString");
}
