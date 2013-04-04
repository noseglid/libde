Dynamic Events
==============

Dynamic Events is a framework for emitting and absorbing events
between various areas of a C++ application. The philosophy is very
much inspired by NodeJS with the 'on' and 'emit' functions.

License
=======

Distributed under [MIT License](http://opensource.org/licenses/MIT). Use it freely!

Building and installing
=======================
Since it's headers only, no building is required.

You can either copy the contents of the `src/` folder appropriately,
By approriately means, all header files except `de.h` in one
folder called `libde`(probably in `/usr/local/include/libde/`)
then put `de.h` side-by-side with this folder (probably in `/usr/local/include/`).

Or you can have autoconf do the work, use `./autogen.sh`, then `./configure` and finally `make install`.
Obvously this approach requires autoconf (and automake).

Basic Usage
===========

```c++
#include <de.h>
#include <iostream>

class emitter : public de::Emitter<>
{
public:
    void do_stuff()
    {
        emit("signal");
    }
};

class receiver
{
public:
    void signal_method()
    {
        std::cout << "receiver::signal_handler" << std::endl;
    }
};

void signal_function()
{
    std::cout << "function signal_handler" << std::endl;
}

int main(void)
{
    emitter e;
    receiver r;

    auto bound_call = std::bind(&receiver::signal_method, &r);
    auto lambda = []() {
        std::cout << "lambda signal_handler" << std::endl;
    };

    e.on("signal", signal_function);
    e.on("signal", bound_call);
    e.on("signal", lambda);

    e.do_stuff();

    return 0;
}
```
```
function signal_handler
receiver::signal_handler
lambda signal_handler
```
Quick overview
--------------
```c++
    class emitter : public de::Emitter<>
```

The emitter must be a class, and it must extend `de::Emitter`.
The example class here have a function `do_stuff` which emits
the event `signal`.

The `signal_handler` is a basic function which will receive the event.

The `receiver`-class is nothing special. It just have a method which can be called.
We will later set this method to be called when `emitter` sends its event.

The auto variables and bind are C++11 mambo-jambo to be able to create
pointers to methods in instances of classes and lambdas. Read up on this if you need.

```c++
e.on("signal", signal_function);
e.on("signal", signal_method);
e.on("signal", signal_lambda);
```
The function `on` informs the emitter that we are interested in a certain type of event, in this case "signal".
The event (which here is "signal") can be anything, and if the Emitter emits that type, the callback will be
invoked.

```c++
e.do_stuff();
```
Performs some mundane tasks which inevitably will emit the event "signal".
At this point, all the callbacks will be invoked. The order in which the
callbacks are invoked is not defined - you should not rely on any particular
order.

The output is as expected:
```
function signal_handler
receiver::signal_handler
lambda signal_handler
```

Passing data
------------
You can easily include data using `std::bind`
```c++
void fn(int n)
{
	std::cout << "fn called with n: " << n << std::endl;
}

/* ... somewhere later ... */

auto signal_function = std::bind(&fn, 2);
e.on("signal", signal_function)
```
The same works for lambdas and member functions (methods).

You can include custom data in when you emit events by including that type
when you instantiate the Emitter.

```c++
class emitter :: de::Emitter<int>
{
public:
  void emitting_function()
  {
    emit("signal", 12);
  }
};
```

Here all signals emitted from `emitting_function` will include the custom data 12.
Naturally the receiving function must accept an integer argument.
