//==============================================================================================================================
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <cws/events.hpp>


//==============================================================================================================================
struct HelloWorldEvent
{
};


//==============================================================================================================================
void hello_world_listener(HelloWorldEvent const &)
{
    std::cout << "Hello World!" << std::endl;
}


//==============================================================================================================================
class Worker
{
    typedef cws::events::dispatcher::Type<cws::events::MutexType<std::mutex>,
                                          cws::events::TypesList<HelloWorldEvent>>::type dispatcher_t;

public:
    //==========================================================================================================================
    Worker()
        : managerHandle_   (std::thread(&Worker::manager,    this))
        , dispatcherHandle_(std::thread(&Worker::dispatcher, this))
    {
    }


    //==========================================================================================================================
    ~Worker()
    {
        managerHandle_.join();
        dispatcherHandle_.join();
    }

    //==========================================================================================================================
    void manager()
    {
        for (unsigned int i = 0; i != ITERATIONS_COUNT; ++i)
        {
            dispatcher_.add_listener<HelloWorldEvent>(hello_world_listener);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            dispatcher_.remove_listener<HelloWorldEvent>(hello_world_listener);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    //==========================================================================================================================
    void dispatcher()
    {
        for (unsigned int i = 0; i != ITERATIONS_COUNT; ++i)
        {
            dispatcher_.dispatch(HelloWorldEvent());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

private:
    //==========================================================================================================================
    dispatcher_t dispatcher_;
    std::thread  managerHandle_;
    std::thread  dispatcherHandle_;

private:
    //==========================================================================================================================
    const unsigned int ITERATIONS_COUNT = 100;
};


//==============================================================================================================================
int main()
{
    Worker worker;

    return 0;
}
