//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
struct HelloWorldEvent
{
};


//==============================================================================================================================
class EventsListener
{
public:
    void hello_world(HelloWorldEvent const &)
    {
        std::cout << "Hello World!" << std::endl;
    }
};


//==============================================================================================================================
int main()
{
    cws::events::Dispatcher<HelloWorldEvent> dispatcher;
    EventsListener                           listener;

    dispatcher.add_listener<HelloWorldEvent>(boost::bind(&EventsListener::hello_world, &listener, _1));
    dispatcher.dispatch(HelloWorldEvent());

    dispatcher.remove_listener<HelloWorldEvent>(boost::bind(&EventsListener::hello_world, &listener, _1));
    dispatcher.dispatch(HelloWorldEvent());

    return 0;
}