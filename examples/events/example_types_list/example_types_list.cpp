//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
struct SomeEvent
{
};


//==============================================================================================================================
struct SomeOtherEvent
{
};


//==============================================================================================================================
void some_listener(SomeEvent const &)
{
    std::cout << __FUNCTION__ << std::endl;
}


//==============================================================================================================================
void some_other_listener(SomeOtherEvent const &)
{
    std::cout << __FUNCTION__ << std::endl;
}


//==============================================================================================================================
int main()
{
    cws::events::dispatcher::Type<cws::events::TypesList<SomeEvent, SomeOtherEvent>>::type dispatcher;

    dispatcher.add_listener<SomeEvent>     (some_listener);
    dispatcher.add_listener<SomeOtherEvent>(some_other_listener);

    dispatcher.dispatch(SomeEvent     ());
    dispatcher.dispatch(SomeOtherEvent());

    return 0;
}
