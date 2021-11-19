//==============================================================================================================================
#include <iostream>
#include <thread>
#include <mutex>
#include <cws/events.hpp>


//==============================================================================================================================
const size_t ITERATIONS_COUNT = 100;


//==============================================================================================================================
struct SomeEvent
{
    size_t value;
};


//==============================================================================================================================
void some_listener(SomeEvent const &_event)
{
    std::cout << "on event: " << _event.value << std::endl;
}


//==============================================================================================================================
typedef cws::events::dispatcher::Type<cws::events::MutexType<std::mutex>,
                                      cws::events::TypesList<SomeEvent>>::type SomeDispatcher;


//==============================================================================================================================
void listener_function(SomeDispatcher &_dispatcher)
{
    for (size_t i = 0; i != ITERATIONS_COUNT; ++i)
    {
        _dispatcher.add_listener<SomeEvent>(some_listener);
        std::this_thread::sleep_for(std::chrono::microseconds(1));

        _dispatcher.remove_listener<SomeEvent>(some_listener);
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}


//==============================================================================================================================
void event_function(SomeDispatcher &_dispatcher)
{
    for (size_t i = 0; i != ITERATIONS_COUNT; ++i)
    {
        _dispatcher.dispatch(SomeEvent({ i }));

        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}


//==============================================================================================================================
int main()
{
    SomeDispatcher dispatcher;

    std::thread listenerThread(listener_function, std::ref(dispatcher));
    std::thread eventThread   (event_function,    std::ref(dispatcher));

    listenerThread.join();
    eventThread.join();

    return 0;
}
