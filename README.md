Dynamic Events
=====

Dynamic Events is a framework for emitting and absorbing events
between various areas of a C++ application. The philosophy is very
much inspired by NodeJS with the 'on' and 'emit' functions.

Basic Usage
===========

```c++
#include <de.h>
#include <pjson.hpp>
#include <iostream>

class emitter : public de::Emitter
{
public:
	void do_stuff()
	{
		std::vector<int> v;
		v.push_back(12);
		v.push_back(1);
		emit("eventname", Json::Builder::create(v));
		emit("alarm", Json::Builder::create("important alarm data"));
	}
};

class receiver
{
public:
	void eventname_method(const Json::Value& data)
	{
		std::cout << "eventname_method: " << Json::serialize(data) << std::endl;
	}

	void alarm(const Json::Value& data)
	{
		std::cout << "It's an alarm: " << Json::serialize(data) << std::endl;
	}
};

void eventname_function(const Json::Value& data)
{
	std::cout << "eventname_function: " << Json::serialize(data) << std::endl;
}

int main(void)
{
	emitter e;
	receiver r;

	typedef std::function<void(const Json::Value&)> mthd_t;
	auto eventname_method = std::bind(&receiver::eventname_method, &r, std::placeholders::_1);
	auto alarm_method     = std::bind(&receiver::alarm, &r, std::placeholders::_1);

	e.on("eventname", eventname_function);
	e.on("eventname", eventname_method);
	e.on("eventname", [](const Json::Value& data) {
		std::cout << "eventname_lambda: " << Json::serialize(data) << std::endl;
	});

	e.on("alarm", alarm_method);

	e.do_stuff();

	return 0;
}
```
    eventname_function: [12,1]
    eventname_method: [12,1]
    eventname_lambda: [12,1]
    It's an alarm: "important alarm data"

Quick overview
--------------
    class emitter : public de::Emitter
The emitter must be a class, and it must extend `de::Emitter`.
The example class here have a function `do_stuff` which emits
two events, `eventname` and `alarm`.

	  void eventname_method(const Json::Value& data)
The member method which will receive an event.

    void eventname_function(const Json::Value& data)
The global function which will receive an event.

The typedefs and auto variables are C++ mambo-jambo to be able to create
pointers to methods in instances of classes. Read up on this if you need.

    e.on("eventname", eventname_function);
With `on` we registered consumers of events.

    e.do_stuff();
    ....
    emit("eventname", Json::Builder::create(v));
When we execute the method which `emit`s events, all registered consumers
will be called.

A consumer can subscribe on any event - identified by a string.
If the emitter emits an event with that identity (the same string), the consumer will be called with appropriate information.

JSON as data
============
libde depends on [libpjson](https://github.com/noseglid/pjson) for transport of data. This is simply a C++ serializer/deserializer for JSON.

JSON was chosen as it is very basic and easy to use, yet with very powerful capabilities.
