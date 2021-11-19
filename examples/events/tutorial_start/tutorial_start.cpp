//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
struct HelloWorldEvent
{
};


//==============================================================================================================================
void hello_world_listener(HelloWorldEvent const &)
{
    std::cout << "Hello World!" << std::endl;
}


//==============================================================================================================================
int main()
{
    cws::events::Dispatcher<HelloWorldEvent> dispatcher;

    dispatcher.add_listener<HelloWorldEvent>(hello_world_listener);
    dispatcher.dispatch(HelloWorldEvent());

    dispatcher.remove_listener<HelloWorldEvent>(hello_world_listener);
    dispatcher.dispatch(HelloWorldEvent());

    return 0;
}
