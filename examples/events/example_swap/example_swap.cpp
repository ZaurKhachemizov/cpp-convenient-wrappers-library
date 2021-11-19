//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
struct SomeEvent
{
};


//==============================================================================================================================
void some_listener(SomeEvent const &)
{
    std::cout << __FUNCTION__ << std::endl;
}


//==============================================================================================================================
int main()
{
    cws::events::Dispatcher<SomeEvent> dispatcher;
    cws::events::Dispatcher<SomeEvent> otherDispatcher;

    dispatcher.add_listener<SomeEvent>(some_listener);

    dispatcher.swap(otherDispatcher);

    otherDispatcher.dispatch(SomeEvent());

    return 0;
}
