#include "unit_tests.hpp"
#include "app_tests.hpp"


//==============================================================================================================================
TEST_CASE("Function as a listener", "")
{
    reset();

    cws::events::Dispatcher<EventA> dispatcher;

    dispatcher.add_listener<EventA>(on_event);

    dispatcher.dispatch(EventA());

    REQUIRE(occured_event_index() == 1);


    reset();

    dispatcher.remove_listener<EventA>(on_event);

    dispatcher.dispatch(EventA());

    REQUIRE(occured_event_index() == 0);
}


//==============================================================================================================================
TEST_CASE("Member fuction as a listener", "")
{
    cws::events::Dispatcher<EventA> dispatcher;

    Listener listener;

    dispatcher.add_listener<EventA>(boost::bind(&Listener::on_event_a, &listener, _1));

    dispatcher.dispatch(EventA());

    REQUIRE(listener.occured_event_a_index() == 1);


    listener.reset();

    dispatcher.remove_listener<EventA>(boost::bind(&Listener::on_event_a, &listener, _1));

    dispatcher.dispatch(EventA());

    REQUIRE(listener.occured_event_a_index() == 0);
}


//==============================================================================================================================
TEST_CASE("Shared object's member fuction as a listener", "")
{
    cws::events::Dispatcher<EventA> dispatcher;

    auto listener = std::make_shared<Listener>();

    dispatcher.add_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 1);


    listener->reset();

    dispatcher.remove_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);
}


//==============================================================================================================================
TEST_CASE("Custom dispatcher", "")
{
    CustomDispatcher dispatcher;

    auto listener = std::make_shared<Listener>();

    dispatcher.add_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher.notify_event_occured();

    REQUIRE(listener->occured_event_a_index() == 1);


    listener->reset();

    dispatcher.remove_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher.notify_event_occured();

    REQUIRE(listener->occured_event_a_index() == 0);
}


//==============================================================================================================================
TEST_CASE("Order", "")
{
    reset();

    cws::events::Dispatcher<EventA> dispatcher;
    Listener                        listener;
    auto                            sharedListener = std::make_shared<Listener>();

    dispatcher.add_listener<EventA>(on_event);
    dispatcher.add_listener<EventA>(boost::bind(&Listener::on_event_a, &listener, _1), cws::events::Order::FRONT);
    dispatcher.add_listener<EventA>(&Listener::on_event_a, sharedListener, cws::events::Order::BACK);

    dispatcher.dispatch(EventA());

    REQUIRE(listener.occured_event_a_index       () == 1);
    REQUIRE(occured_event_index                  () == 2);
    REQUIRE(sharedListener->occured_event_a_index() == 3);


    reset();
    listener.reset();
    sharedListener->reset();

    dispatcher.remove_listeners();

    dispatcher.dispatch(EventA());

    REQUIRE(listener.occured_event_a_index       () == 0);
    REQUIRE(occured_event_index                  () == 0);
    REQUIRE(sharedListener->occured_event_a_index() == 0);
}


//==============================================================================================================================
TEST_CASE("Priority", "")
{
    reset();

    cws::events::Dispatcher<EventA> dispatcher;
    Listener                        listener0;
    Listener                        listener1;
    auto                            sharedListener0 = std::make_shared<Listener>();
    auto                            sharedListener1 = std::make_shared<Listener>();

    dispatcher.add_listener<EventA>(on_event);
    dispatcher.add_listener<EventA>(0, boost::bind(&Listener::on_event_a, &listener0, _1));
    dispatcher.add_listener<EventA>(0, boost::bind(&Listener::on_event_a, &listener1, _1), cws::events::Order::FRONT);
    dispatcher.add_listener<EventA>(1, &Listener::on_event_a, sharedListener0);
    dispatcher.add_listener<EventA>(&Listener::on_event_a, sharedListener1, cws::events::Order::FRONT);

    dispatcher.dispatch(EventA());

    REQUIRE(sharedListener1->occured_event_a_index() == 1);
    REQUIRE(listener1.occured_event_a_index       () == 2);
    REQUIRE(listener0.occured_event_a_index       () == 3);
    REQUIRE(sharedListener0->occured_event_a_index() == 4);
    REQUIRE(occured_event_index                   () == 5);


    reset();
    listener0.reset();
    listener1.reset();
    sharedListener0->reset();
    sharedListener1->reset();

    dispatcher.remove_listeners<EventA>(0);

    dispatcher.dispatch(EventA());

    REQUIRE(listener0.occured_event_a_index       () == 0);
    REQUIRE(listener1.occured_event_a_index       () == 0);
    REQUIRE(sharedListener1->occured_event_a_index() == 1);
    REQUIRE(sharedListener0->occured_event_a_index() == 2);
    REQUIRE(occured_event_index                   () == 3);


    reset();
    listener0.reset();
    listener1.reset();
    sharedListener0->reset();
    sharedListener1->reset();

    dispatcher.remove_listeners();

    dispatcher.dispatch(EventA());

    REQUIRE(listener0.occured_event_a_index       () == 0);
    REQUIRE(listener1.occured_event_a_index       () == 0);
    REQUIRE(sharedListener0->occured_event_a_index() == 0);
    REQUIRE(sharedListener1->occured_event_a_index() == 0);
    REQUIRE(occured_event_index                   () == 0);
}


//==============================================================================================================================
TEST_CASE("Custom priority", "")
{
    reset();

    cws::events::dispatcher::Type<cws::events::PriorityType<CustomPriority>, cws::events::TypesList<EventA>>::type dispatcher;

    Listener listener;
    auto     sharedListener = std::make_shared<Listener>();

    dispatcher.add_listener<EventA>(on_event);
    dispatcher.add_listener<EventA>(CustomPriority::HIGH, boost::bind(&Listener::on_event_a, &listener, _1));
    dispatcher.add_listener<EventA>(CustomPriority::LOW, &Listener::on_event_a, sharedListener);

    dispatcher.dispatch(EventA());

    REQUIRE(listener.occured_event_a_index       () == 1);
    REQUIRE(sharedListener->occured_event_a_index() == 2);
    REQUIRE(occured_event_index                  () == 3);


    reset();
    listener.reset();
    sharedListener->reset();

    dispatcher.remove_listeners<EventA>(CustomPriority::HIGH);

    dispatcher.dispatch(EventA());

    REQUIRE(listener.occured_event_a_index       () == 0);
    REQUIRE(sharedListener->occured_event_a_index() == 1);
    REQUIRE(occured_event_index                  () == 2);


    reset();
    listener.reset();
    sharedListener->reset();

    dispatcher.remove_listeners();

    dispatcher.dispatch(EventA());

    REQUIRE(listener.occured_event_a_index       () == 0);
    REQUIRE(sharedListener->occured_event_a_index() == 0);
    REQUIRE(occured_event_index                  () == 0);
}


//==============================================================================================================================
TEST_CASE("STD swap", "")
{
    cws::events::Dispatcher<EventA> dispatcher0;
    cws::events::Dispatcher<EventA> dispatcher1;

    auto listener = std::make_shared<Listener>();

    dispatcher1.add_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher0.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);

    dispatcher1.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 1);


    listener->reset();

    dispatcher0.swap(dispatcher1);

    dispatcher1.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);

    dispatcher0.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 1);


    listener->reset();

    dispatcher0.remove_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher0.dispatch(EventA());
    dispatcher1.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);
}


//==============================================================================================================================
TEST_CASE("Swap", "")
{
    cws::events::Dispatcher<EventA> dispatcher0;
    cws::events::Dispatcher<EventA> dispatcher1;

    auto listener = std::make_shared<Listener>();

    dispatcher1.add_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher0.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);

    dispatcher1.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 1);


    listener->reset();

    std::swap(dispatcher0, dispatcher1);

    dispatcher1.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);

    dispatcher0.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 1);


    listener->reset();

    dispatcher0.remove_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher0.dispatch(EventA());
    dispatcher1.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);
}


//==============================================================================================================================
TEST_CASE("Multiple events", "")
{
    cws::events::Dispatcher<EventA, EventB> dispatcher;

    auto listener = std::make_shared<Listener>();

    dispatcher.add_listener<EventA>(&Listener::on_event_a, listener);
    dispatcher.add_listener<EventB>(&Listener::on_event_b, listener);

    dispatcher.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 1);
    REQUIRE(listener->occured_event_b_index() == 0);


    listener->reset();

    dispatcher.dispatch(EventB());

    REQUIRE(listener->occured_event_a_index() == 0);
    REQUIRE(listener->occured_event_b_index() == 1);


    listener->reset();

    dispatcher.dispatch(EventA());
    dispatcher.dispatch(EventB());

    REQUIRE(listener->occured_event_a_index() == 1);
    REQUIRE(listener->occured_event_b_index() == 1);


    listener->reset();

    dispatcher.remove_listener<EventA>(&Listener::on_event_a, listener);

    dispatcher.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);
    REQUIRE(listener->occured_event_b_index() == 0);

    dispatcher.dispatch(EventB());

    REQUIRE(listener->occured_event_a_index() == 0);
    REQUIRE(listener->occured_event_b_index() == 1);


    listener->reset();

    dispatcher.remove_listeners();

    dispatcher.dispatch(EventA());

    REQUIRE(listener->occured_event_a_index() == 0);
    REQUIRE(listener->occured_event_b_index() == 0);

    dispatcher.dispatch(EventB());

    REQUIRE(listener->occured_event_a_index() == 0);
    REQUIRE(listener->occured_event_b_index() == 0);
}


//==============================================================================================================================
//==============================================================================================================================


//==============================================================================================================================
TEST_CASE("Add listener example", "")
{
    do_app_test("example_add_listener");
}


//==============================================================================================================================
TEST_CASE("Dispatch example", "")
{
    do_app_test("example_dispatch");
}


//==============================================================================================================================
TEST_CASE("Dispatcher type example", "")
{
    do_app_test("example_dispatcher_type");
}


//==============================================================================================================================
TEST_CASE("Dispatcher move and assignment", "")
{
    do_app_test("example_move");
}


//==============================================================================================================================
TEST_CASE("Order example", "")
{
    do_app_test("example_order");
}


//==============================================================================================================================
TEST_CASE("Priority type example", "")
{
    do_app_test("example_priority_type");
}


//==============================================================================================================================
TEST_CASE("Remove listener example", "")
{
    do_app_test("example_remove_listener");
}


//==============================================================================================================================
TEST_CASE("Remove listeners example", "")
{
    do_app_test("example_remove_listeners");
}

//==============================================================================================================================
TEST_CASE("STD swap example", "")
{
    do_app_test("example_std_swap");
}


//==============================================================================================================================
TEST_CASE("Swap example", "")
{
    do_app_test("example_swap");
}


//==============================================================================================================================
TEST_CASE("types list example", "")
{
    do_app_test("example_types_list");
}


//==============================================================================================================================
TEST_CASE("Custom class tutorial", "")
{
    do_app_test("tutorial_custom_class");
}


//==============================================================================================================================
TEST_CASE("Custom priority tutorial", "")
{
    do_app_test("tutorial_custom_priority");
}


//==============================================================================================================================
TEST_CASE("Listeners tutorial", "")
{
    do_app_test("tutorial_listeners");
}


//==============================================================================================================================
TEST_CASE("Priority tutorial", "")
{
    do_app_test("tutorial_priority");
}


//==============================================================================================================================
TEST_CASE("Shared listeners tutorial", "")
{
    do_app_test("tutorial_shared_listeners");
}


//==============================================================================================================================
TEST_CASE("Start tutorial", "")
{
    do_app_test("tutorial_start");
}
