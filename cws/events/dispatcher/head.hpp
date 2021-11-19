// cws::events::dispatcher::Head class is head class in cws::events::Dispatcher's scattered hierarchy.
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
#include <boost/signals2.hpp>


//==============================================================================================================================
#include "../details.hpp"


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
            // 
            // Specifies head class for a specified event in cws::events::Dispatcher's scattered hierarchy.
            // 
            template <typename _Mutex, typename _Priority, typename _Comparator, typename _Event>
            class Head
            {
                typedef typename boost::signals2::signal_type<void(_Event const &),
                                                              boost::signals2::keywords::group_type<_Priority>,
                                                              boost::signals2::keywords::group_compare_type<_Comparator>,
                                                              boost::signals2::keywords::mutex_type<_Mutex>>::type  signal_t;

                typedef std::unique_ptr<signal_t>  unique_signal_t;

            protected:
                //==============================================================================================================
                Head()
                    : uniqueSignal_(new signal_t())
                {
                }

                //==============================================================================================================
                Head(Head &&_source) noexcept
                    : uniqueSignal_(std::move(_source.uniqueSignal_))
                {
                }

                //==============================================================================================================
                void swap(Head &_source) noexcept
                {
                    std::swap(uniqueSignal_, _source.uniqueSignal_);
                }

                //==============================================================================================================
                // 
                // Adds listener into dispatcher for the current event in the specified order.
                // The listener is any callable object.
                // 
                template <typename _Callable>
                void add_listener(_Callable &&_callable, Order _order)
                {
                    remove_listener(std::forward<_Callable>(_callable));
                    uniqueSignal_->connect(std::forward<_Callable>(_callable),
                                           static_cast<boost::signals2::connect_position>(_order));
                }

                //==============================================================================================================
                //
                // Adds listener into dispatcher for the current event using specified priority and order.
                // The listener is any callable object.
                //
                template <typename _Callable>
                void add_listener(_Priority _priority, _Callable &&_callable, Order _order)
                {
                    remove_listener(std::forward<_Callable>(_callable));
                    uniqueSignal_->connect(_priority, std::forward<_Callable>(_callable),
                                           static_cast<boost::signals2::connect_position>(_order));
                }

                //==============================================================================================================
                // 
                // Adds listener into dispatcher for the current event in the specified order.
                // The listener is a member function with a pointer to object storing in std::shared_ptr.
                // 
                template <typename _Function, typename _Object>
                void add_listener(_Function &&_function, std::shared_ptr<_Object> const &_object, Order _order)
                {
                    remove_tracked_listener(std::forward<_Function>(_function), _object);
                    uniqueSignal_->connect(signal_t::slot_type(std::forward<_Function>(_function), _object.get(),
                                                               _1).track_foreign(_object),
                                           static_cast<boost::signals2::connect_position>(_order));
                }

                //==============================================================================================================
                // 
                // Adds listener into dispatcher for the current event using specified priority and order.
                // The listener is a member function with a pointer to object storing in std::shared_ptr.
                // 
                template <typename _Function, typename _Object>
                void add_listener(_Priority _priority, _Function &&_function, std::shared_ptr<_Object> const &_object,
                                  Order _order)
                {
                    remove_tracked_listener(std::forward<_Function>(_function), _object);
                    uniqueSignal_->connect(_priority, signal_t::slot_type(std::forward<_Function>(_function), _object.get(),
                                                                          _1).track_foreign(_object),
                                           static_cast<boost::signals2::connect_position>(_order));
                }

                //==============================================================================================================
                // 
                // Adds listener into dispatcher for the current event in the specified order.
                // The listener is a member function with a pointer to object storing in boost::shared_ptr.
                // 
                template <typename _Function, typename _Object>
                void add_listener(_Function &&_function, boost::shared_ptr<_Object> const &_object, Order _order)
                {
                    remove_tracked_listener(std::forward<_Function>(_function), _object);
                    uniqueSignal_->connect(signal_t::slot_type(std::forward<_Function>(_function), _object.get(),
                                                               _1).track(_object),
                                           static_cast<boost::signals2::connect_position>(_order));
                }

                //==============================================================================================================
                // 
                // Adds listener into dispatcher for the current event using specified priority and order.
                // The listener is a member function with a pointer to object storing in boost::shared_ptr.
                // 
                template <typename _Function, typename _Object>
                void add_listener(_Priority _priority, _Function &&_function, boost::shared_ptr<_Object> const &_object,
                                  Order _order)
                {
                    remove_tracked_listener(std::forward<_Function>(_function), _object);
                    uniqueSignal_->connect(_priority, signal_t::slot_type(std::forward<_Function>(_function), _object.get(),
                                                                          _1).track(_object),
                                           static_cast<boost::signals2::connect_position>(_order));
                }

                //==============================================================================================================
                // 
                // Removes specified listener for the current event.
                // The listener is any callable object.
                // 
                template <typename _Callable>
                void remove_listener(_Callable &&_callable)
                {
                    uniqueSignal_->disconnect(std::forward<_Callable>(_callable));
                }

                //==============================================================================================================
                // 
                // Removes specified listener for the current event.
                // The listener is a member function with a pointer to object storing as an automatic pointer.
                // 
                template <typename _Function, typename _Object>
                void remove_tracked_listener(_Function &&_function, _Object const &_object)
                {
                    uniqueSignal_->disconnect(boost::bind(std::forward<_Function>(_function), _object.get(), _1));
                }

                //==============================================================================================================
                // 
                // Removes all listeners for the current event with the specified priority.
                // 
                void remove_listeners(_Priority _priority)
                {
                    uniqueSignal_->disconnect(_priority);
                }

                //==============================================================================================================
                // 
                // Removes all listeners for the current event.
                // 
                void remove_listeners()
                {
                    uniqueSignal_->disconnect_all_slots();
                }

                //==============================================================================================================
                // 
                // Dispatches current event object to corresponding listeners according to their priority and order.
                // 
                void dispatch(_Event const &_event)
                {
                    (*uniqueSignal_)(_event);
                }

            private:
                Head           (Head const &) = delete;
                Head &operator=(Head const &) = delete;
                Head &operator=(Head &&)      = delete;

            private:
                unique_signal_t uniqueSignal_;
            };


            //==================================================================================================================
            // 
            // Access to head class for a specified event in cws::event::Dispatcher's scattered hierarchy.
            // 
            template <typename _Mutex, typename _Priority, typename _Comparator>
            struct HeadType
            {
                template <typename _Event>
                using type = Head<_Mutex, _Priority, _Comparator, _Event>;
            };

        }  // namespace dispatcher

    }  // namespace events

}  // namespace cws
