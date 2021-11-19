//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
enum class Priority
{
    LOW,
    HIGH,
};


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
    cws::events::dispatcher::Type<cws::events::PriorityType<Priority, std::greater<Priority>>,
                                  cws::events::TypesList<HelloWorldEvent>>::type dispatcher;

    dispatcher.add_listener<HelloWorldEvent>(hello_world_listener<4>);
    dispatcher.add_listener<HelloWorldEvent>(hello_world_listener<0>, cws::events::Order::FRONT);

    dispatcher.add_listener<HelloWorldEvent>(Priority::HIGH, hello_world_listener<2>);
    dispatcher.add_listener<HelloWorldEvent>(Priority::HIGH, hello_world_listener<1>, cws::events::Order::FRONT);

    dispatcher.add_listener<HelloWorldEvent>(Priority::LOW, hello_world_listener<3>);

    dispatcher.dispatch(HelloWorldEvent());

    return 0;
}
