//==============================================================================================================================
#include <iostream>
#include <mutex>
#include <cws/events.hpp>


//==============================================================================================================================
struct SomeEvent
{
};


//==============================================================================================================================
int main()
{
    cws::events::dispatcher::Type<cws::events::MutexType<std::mutex>, cws::events::PriorityType<int>,
        cws::events::TypesList<SomeEvent>>::type dispatcher;

    cws::events::dispatcher::Type<cws::events::PriorityType<int>, cws::events::MutexType<std::mutex>,
        cws::events::TypesList<SomeEvent>>::type otherDispatcher;

    cws::events::dispatcher::Type<cws::events::MutexType<std::mutex>,
        cws::events::TypesList<SomeEvent>>::type anotherDispatcher;

    cws::events::Dispatcher<SomeEvent> simpleDispatcher;

    std::cout << std::boolalpha << (typeid(dispatcher) == typeid(otherDispatcher  )) << std::endl;
    std::cout << std::boolalpha << (typeid(dispatcher) == typeid(anotherDispatcher)) << std::endl;
    std::cout << std::boolalpha << (typeid(dispatcher) == typeid(simpleDispatcher )) << std::endl;

    return 0;
}
