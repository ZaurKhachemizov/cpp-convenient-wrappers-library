//==============================================================================================================================
#include <iostream>
#include <cws/events.hpp>


//==============================================================================================================================
struct SomeEvent
{
};


//==============================================================================================================================
enum class Priority
{
    LOW,
    HIGH
};


//==============================================================================================================================
void some_listener(SomeEvent const &)
{
    std::cout << __FUNCTION__ << std::endl;
}


//==============================================================================================================================
void some_other_listener(SomeEvent const &)
{
    std::cout << __FUNCTION__ << std::endl;
}


//==============================================================================================================================
class SomeClass
{
public:
    void listener_low(SomeEvent const &)
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    void listener_high(SomeEvent const &)
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    void other_listener_low(SomeEvent const &)
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    void other_listener_high(SomeEvent const &)
    {
        std::cout << __FUNCTION__ << std::endl;
    }
};


//==============================================================================================================================
int main()
{
    cws::events::dispatcher::Type<cws::events::PriorityType<Priority, std::greater<Priority>>,
        cws::events::TypesList<SomeEvent>>::type dispatcher;

    SomeClass someClass;

    dispatcher.add_listener<SomeEvent>(some_other_listener);
    dispatcher.add_listener<SomeEvent>(some_listener, cws::events::Order::FRONT);

    dispatcher.add_listener<SomeEvent>(Priority::LOW, boost::bind(&SomeClass::listener_low, &someClass, _1));
    dispatcher.add_listener<SomeEvent>(Priority::LOW, boost::bind(&SomeClass::other_listener_low, &someClass, _1));

    dispatcher.add_listener<SomeEvent>(Priority::HIGH, boost::bind(&SomeClass::other_listener_high, &someClass, _1));
    dispatcher.add_listener<SomeEvent>(Priority::HIGH, boost::bind(&SomeClass::listener_high, &someClass, _1),
                                       cws::events::Order::FRONT);

    dispatcher.dispatch(SomeEvent());

    return 0;
}
