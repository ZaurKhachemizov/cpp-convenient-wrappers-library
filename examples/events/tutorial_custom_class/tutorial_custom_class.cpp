//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
struct HelloWorldEvent
{
};


//==============================================================================================================================
class HelloWorldDispatcher : public cws::events::Dispatcher<HelloWorldEvent>
{
public:
    void say_hello()
    {
        dispatch(HelloWorldEvent());
    }
};


//==============================================================================================================================
void hello_world_listener(HelloWorldEvent const &)
{
    std::cout << "Hello World!" << std::endl;
}


//==============================================================================================================================
int main()
{
    HelloWorldDispatcher dispatcher;

    dispatcher.add_listener<HelloWorldEvent>(hello_world_listener);
    dispatcher.say_hello();

    return 0;
}
