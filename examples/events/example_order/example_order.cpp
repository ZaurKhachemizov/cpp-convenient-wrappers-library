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
    void ptr_listener(SomeEvent const &)
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    void shared_listener(SomeEvent const &)
    {
        std::cout << __FUNCTION__ << std::endl;
    }
};


//==============================================================================================================================
int main()
{
    cws::events::Dispatcher<SomeEvent> dispatcher;
    SomeClass                          someClass;
    std::shared_ptr<SomeClass>         sharedSomeClass(new SomeClass());

    dispatcher.add_listener<SomeEvent>(some_listener);
    dispatcher.add_listener<SomeEvent>(boost::bind(&SomeClass::ptr_listener, &someClass, _1), cws::events::Order::FRONT);
    dispatcher.add_listener<SomeEvent>(&SomeClass::shared_listener, sharedSomeClass);

    dispatcher.dispatch(SomeEvent());

    return 0;
}
