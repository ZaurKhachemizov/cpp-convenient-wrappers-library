//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
struct HelloWorldEvent
{
};


//==============================================================================================================================
template<int i>
void hello_world_listener(HelloWorldEvent const &)
{
    std::cout << i << ": Hello World!" << std::endl;
}


//==============================================================================================================================
int main()
{
    cws::events::Dispatcher<HelloWorldEvent> dispatcher;

    dispatcher.add_listener<HelloWorldEvent>(hello_world_listener<4>);
    dispatcher.add_listener<HelloWorldEvent>(hello_world_listener<0>, cws::events::Order::FRONT);

    dispatcher.add_listener<HelloWorldEvent>(0, hello_world_listener<2>);
    dispatcher.add_listener<HelloWorldEvent>(0, hello_world_listener<1>, cws::events::Order::FRONT);

    dispatcher.add_listener<HelloWorldEvent>(1, hello_world_listener<3>);

    dispatcher.dispatch(HelloWorldEvent());

    std::cout << std::endl;

    dispatcher.remove_listeners<HelloWorldEvent>(0);
    dispatcher.dispatch(HelloWorldEvent());

    dispatcher.remove_listeners();
    dispatcher.dispatch(HelloWorldEvent());

    return 0;
}
