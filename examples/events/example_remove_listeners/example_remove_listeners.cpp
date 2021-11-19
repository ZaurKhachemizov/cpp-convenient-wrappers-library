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
class SomeClass
{
public:
    void listener(SomeEvent const &)
    {
        std::cout << __FUNCTION__ << std::endl;
    }
};


//==============================================================================================================================
int main()
{
    cws::events::Dispatcher<SomeEvent> dispatcher;
    SomeClass                          someClass;

    dispatcher.add_listener<SomeEvent>(some_listener);
    dispatcher.add_listener<SomeEvent>(boost::bind(&SomeClass::listener, &someClass, _1));

    dispatcher.dispatch(SomeEvent());

    std::cout << std::endl;

    dispatcher.remove_listeners();

    dispatcher.dispatch(SomeEvent());

    std::cout << "end" << std::endl;

    return 0;
}
