// cws::events::dispatcher::Base class is a root in cws::events::Dispatcher's scattered hierarchy.
// 
// Copyright (c) 2014-2021 Zaur Khachemizov
// 
// Use, modification, and distribution is subject to the C++ convenient wrappers library license Version 1.0 at accompanying
// file license.txt or at http://www.cpphelpers.org/license/
// 
// See documentation at docs/index.html


//==============================================================================================================================
#pragma once


//==============================================================================================================================
#include "head.hpp"
#include "tail.hpp"


//==============================================================================================================================
namespace cws
{


    //==========================================================================================================================
    namespace events
    {


        //======================================================================================================================
        namespace dispatcher
        {


            //==================================================================================================================
            //! 
            //! @brief Specifies root class in cws::events::Dispatcher's scattered hierarchy.
            //! 
            template <typename _Mutex, typename _Priority, typename _Comparator, typename ..._Events>
            class Base :
                public Tail<_Mutex, _Priority, _Comparator, _Events...>
            {
                typedef Tail<_Mutex, _Priority, _Comparator, _Events...>  tail_t;
                typedef HeadType<_Mutex, _Priority, _Comparator>          head_type_t;

            public:
                //==============================================================================================================
                typedef _Mutex       mutex_t;       //!< Mutex type provided through template parameter to instantiate Dispatcher.
                typedef _Priority    priority_t;    //!< Priority type provided through template parameter to instantiate Dispatcher.
                typedef _Comparator  comparator_t;  //!< Comparator type provided through template parameter to instantiate Dispatcher.

                //==============================================================================================================
                //! 
                //! @brief Exchanges content of Dispatcher objects.
                //! 
                //! @param[in] _source Reference to dispatcher object of the same type (instantiated with the same template
                //! parameters).
                //! 
                //! @return
                //! No return value.
                //! 
                //! @par Complexity
                //! Constant.
                //! 
                //! @par Exception safety
                //! Will not throw.
                //! 
                //! @par Example
                //! @include{lineno} example_swap.cpp
                //! 
                //! @par Output
                //! @include example_swap.txt
                //! 
                void swap(Base &_source) noexcept
                {
                    tail_t::swap(_source);
                }

                //==============================================================================================================
                #define HEAD_T(_Event) typedef typename head_type_t::template type<_Event>  head_t; head_t

                //==============================================================================================================
                //! 
                //! @{
                //! 
                //! @brief Subscribes listener to the event.
                //! 
                //! Takes type of event as a template parameter to subscribe listener.
                //! 
                //! @tparam _Event A type of event that listener is subscribing to.
                //! @tparam _Callable [1], [2] A type of function object or function.
                //! @tparam _Function [3] - [6] A type of member function.
                //! @tparam _Object [3] - [6] A class object whose _Function is a member.
                //! 
                //! @param[in] _priority A value that is used to determine listeners' invocation order.
                //! @param[in] _callable [1], [2] A reference to function object or pointer/reference to a function that will
                //! be invoked when an event occurs.
                //! @param[in] _function [3] - [6] A pointer to a member function that will be invoked when an event occurs.
                //! @param[in] _object [3], [5] A constant reference to object of std::shared_ptr<_Object> type.\n
                //! [4], [6] A constant reference to object of boost::shared_ptr<_Object> type.
                //! @param[in] _order Specifies where the listener will be placed. The default value is Order::BACK.
                //! 
                //! @return No return value.
                //! 
                //! @par Complexity
                //! The constant time when subscribing to an event without specifying priority value. Logarithmic in the number
                //! of priority values when subscribing with a particular priority.
                //! 
                //! @par Exception safety
                //! This routine meets the strong exception guarantee, where any exception thrown will cause the listener to not
                //! be subscribed to the event.
                //! 
                //! @remark Listener signature: void (_Event const &).
                //! 
                //! @remark Object tracking: [3] - [6] A listener will automatically unsubscribe the event when its object
                //! expires. Guaranteed that no listener object expires while the event it is subscribed to is dispatching.
                //! 
                //! @remark Function object must have overloaded operator ==.
                //! 
                //! @remark Call this function with the same parameters several times cause removing the listener from the
                //! dispatcher and adding it to the specified place.
                //! 
                //! @remark To subscribe member function as a listener using a pointer to object of the class whose function is
                //! a member boost::bind must be used.
                //! 
                //! @par Example
                //! @include{lineno} example_add_listener.cpp
                //! 
                //! @par Output
                //! @include example_add_listener.txt
                //! 
                template <typename _Event, typename _Callable>
                void add_listener(_Callable &&_callable, Order _order = Order::BACK)
                {
                    HEAD_T(_Event)::add_listener(std::forward<_Callable>(_callable), _order);
                }

                template <typename _Event, typename _Callable>
                void add_listener(_Priority _priority, _Callable &&_callable, Order _order = Order::BACK)
                {
                    HEAD_T(_Event)::add_listener(_priority, std::forward<_Callable>(_callable), _order);
                }

                template <typename _Event, typename _Function, typename _Object>
                void add_listener(_Function &&_function, std::shared_ptr<_Object> const &_object, Order _order = Order::BACK)
                {
                    HEAD_T(_Event)::add_listener(std::forward<_Function>(_function), _object, _order);
                }

                template <typename _Event, typename _Function, typename _Object>
                void add_listener(_Priority _priority, _Function &&_function, std::shared_ptr<_Object> const &_object,
                                  Order _order = Order::BACK)
                {
                    HEAD_T(_Event)::add_listener(_priority, std::forward<_Function>(_function), _object, _order);
                }

                template <typename _Event, typename _Function, typename _Object>
                void add_listener(_Function &&_function, boost::shared_ptr<_Object> const &_object, Order _order = Order::BACK)
                {
                    HEAD_T(_Event)::add_listener(std::forward<_Function>(_function), _object, _order);
                }

                template <typename _Event, typename _Function, typename _Object>
                void add_listener(_Priority _priority, _Function &&_function, boost::shared_ptr<_Object> const &_object,
                                  Order _order = Order::BACK)
                {
                    HEAD_T(_Event)::add_listener(_priority, std::forward<_Function>(_function), _object, _order);
                }
                //! 
                //! @}
                //! 

                //==============================================================================================================
                //! @{
                //! 
                //! @brief Unsubscribes listener from the event.
                //! 
                //! @tparam _Event A type of event that listener is unsubscribing.
                //! @tparam _Callable [1] A type of function object or function.
                //! @tparam _Function [2] - [3] A type of member function.
                //! @tparam _Object [2] - [3] A class object whose _Function is a member.
                //! 
                //! @param[in] _callable [1] A reference to function object or pointer/reference to a function that was
                //! subscribed earlier.
                //! @param[in] _function [2] - [3] A pointer to a member function that was subscribed earlier.
                //! @param[in] _object [2] A constant reference to object of std::shared_ptr<_Object> type.\n
                //! [3] A constant reference to object of boost::shared_ptr<_Object> type.
                //! 
                //! @return No return value.
                //! 
                //! @par Complexity
                //! Linear in the number of listeners subscribed to the event.
                //! 
                //! @par Exception safety
                //! Will not throw unless a user destructor or equality operator == throws. If either throw, the listener may
                //! stay not removed.
                //! 
                //! @par Example
                //! @include{lineno} example_remove_listener.cpp
                //! 
                //! @par Output
                //! @include example_remove_listener.txt
                //! 
                template <typename _Event, typename _Callable>
                void remove_listener(_Callable &&_callable)
                {
                    HEAD_T(_Event)::remove_listener(std::forward<_Callable>(_callable));
                }

                template <typename _Event, typename _Function, typename _Object>
                void remove_listener(_Function &&_function, std::shared_ptr<_Object> const &_object)
                {
                    HEAD_T(_Event)::remove_tracked_listener(std::forward<_Function>(_function), _object);
                }

                template <typename _Event, typename _Function, typename _Object>
                void remove_listener(_Function &&_function, boost::shared_ptr<_Object> const &_object)
                {
                    HEAD_T(_Event)::remove_tracked_listener(std::forward<_Function>(_function), _object);
                }
                //! 
                //! @}
                //! 

                //==============================================================================================================
                //! @{
                //! 
                //! @brief Unsubscribes several listeners.
                //! 
                //! [1] Unsubscribes all listeners from the event with the specified priority.\n
                //! [2] Unsubscribes all listeners from all events.
                //! 
                //! @tparam _Event [1] A type of event that listeners are unsubscribing.
                //! 
                //! @param[in] _priority [1] Listeners with what priority value must be unsubscribed.
                //! 
                //! @return No return value.
                //! 
                //! @par Complexity
                //! [1] Logarithmic in the number of priority values plus the number of listeners subscribed with the specified
                //! priority.\n
                //! [2] Linear in the number of listeners of all events.
                //! 
                //! @par Exception safety
                //! [1] Will not throw unless equality operator == throws.\n
                //! [1] - [2] Will not throw unless a user destructor throws.\n
                //! If either throw, some listeners may stay not removed.
                //! 
                //! @par Example
                //! @include{lineno} example_remove_listeners.cpp
                //! 
                //! @par Output
                //! @include example_remove_listeners.txt
                //! 
                template <typename _Event>
                void remove_listeners(_Priority _priority)
                {
                    HEAD_T(_Event)::remove_listeners(_priority);
                }

                //==============================================================================================================
                void remove_listeners()
                {
                    tail_t::remove_listeners();
                }
                //! 
                //! @}
                //! 

                //==============================================================================================================
                //! 
                //! @brief Invokes subscribed listeners.
                //! 
                //! Takes type of event as a template parameter listeners subscribed to and pass them event object as a
                //! parameter.
                //! 
                //! @tparam _Event The type of event occurs.
                //! 
                //! @param[in] _event Event object that will be passed as a parameter to subscribed listeners.
                //! 
                //! @return
                //! No return value.
                //! 
                //! @par Complexity
                //! Linear in the number of listeners subscribed to the specified event plus listeners' complexity.
                //! 
                //! @par Exception safety
                //! If an exception is thrown by a listener call, all listeners after that will not be invoked.
                //! 
                //! @remark Keep in mind that in a multithreaded environment listeners' code is executing in the same thread
                //! where this function is called.
                //! 
                //! @par Example
                //! @include{lineno} example_dispatch.cpp
                //! 
                //! @par Output
                //! @include example_dispatch.txt
                //! 
                template<typename _Event>
                void dispatch(_Event const &_event)
                {
                    HEAD_T(_Event)::dispatch(_event);
                }

                //==============================================================================================================
                #undef HEAD_T

            protected:
                //==============================================================================================================
                Base() = default;

                //==============================================================================================================
                Base(Base &&_source) noexcept
                    : tail_t(std::move(_source))
                {
                }

            private:
                //==============================================================================================================
                Base           (Base const  &_source) = delete;
                Base &operator=(Base const  &_source) = delete;
                Base &operator=(Base       &&_source) = delete;
            };

        }  // namespace dispatcher

    }  // namespace events

}  // namespace cws
