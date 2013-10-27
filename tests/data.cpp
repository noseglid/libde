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

class recv
{
  de::Emitter<int>::id_t id;
public:
  void fn(de::Emitter<int>& em, bool& called, int val)
  {
    em.off(this->id);
    called = true;
  }

  void set(de::Emitter<int>::id_t id)
  {
    this->id = id;
  }
};

BOOST_AUTO_TEST_CASE( off_upcomming_consumer )
{
  emitter em;
  recv re;
  bool called = false;
  bool not_called = false;

  em.on("signal", std::bind(&recv::fn, &re, std::ref(em), std::ref(called), std::placeholders::_1));
  de::Emitter<int>::id_t idcb = em.on("signal", [&not_called](int) { not_called = true; });
  re.set(idcb);

  em.fn();

  BOOST_CHECK_EQUAL(called, true);
  BOOST_CHECK_EQUAL(not_called, false);
}
