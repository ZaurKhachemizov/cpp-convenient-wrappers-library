//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
struct SomeEvent
{
};


//==============================================================================================================================
void listener_move(SomeEvent const &)
{
    std::cout << __FUNCTION__ << std::endl;
}


//==============================================================================================================================
void listener_assignment(SomeEvent const &)
{
    std::cout << __FUNCTION__ << std::endl;
}


//==============================================================================================================================
cws::events::Dispatcher<SomeEvent> make_dispatcher_move()
{
    cws::events::Dispatcher<SomeEvent> dispatcher;

    dispatcher.add_listener<SomeEvent>(listener_move);

    return dispatcher;
}


//==============================================================================================================================
cws::events::Dispatcher<SomeEvent> make_dispatcher_assignment()
{
    cws::events::Dispatcher<SomeEvent> dispatcher;

    dispatcher.add_listener<SomeEvent>(listener_assignment);

    return dispatcher;
}


//==============================================================================================================================
int main()
{
    cws::events::Dispatcher<SomeEvent> dispatcher(make_dispatcher_move());

    dispatcher.dispatch(SomeEvent());

    dispatcher = make_dispatcher_assignment();

    dispatcher.dispatch(SomeEvent());

    return 0;
}
