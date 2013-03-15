Dynamic Events
=====

Dynamic Events is a framework for emitting and absorbing events
between various areas of a C++ application. The philosophy is very
much inspired by NodeJS with the 'on' and 'emit' functions.

Basic Usage
===========

Two classes are the core `Emitter` and `Receiver`.

```c++
#include <iostream>
#include <de.h>
#include <pjson.hpp>

class emitter : public de::Emitter
{
public:
	void do_stuff()
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(12);
		emit("eventname", Json::Builder::create(v));
	}
};

class receiver : public de::Receiver
{
	void absorb(std::string event, const Json::Value& data)
	{
		std::cout << "Absorbed event: " << event << std::endl;
		std::cout << "Data: " << Json::serialize(data) << std::endl;
	}
};

int main(void)
{
	emitter e;
	receiver r;

	e.on("eventname", &r);
	e.do_stuff();

	return 0;
}
```
    Absorbed event: eventname
    Data: [1,12]

A receiver can subscribe on any event - identified by a string.
If the emitter emits an event with that identity (the same string), the receivers absorb callback will be called with appropriate information.
