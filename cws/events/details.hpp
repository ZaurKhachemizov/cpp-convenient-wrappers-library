// Template structures are used to customize cws::events::Dispatcher and to specify listeners' invocation order.
// 
// Copyright (c) 2014-2021 Zaur Khachemizov
// 
// Use, modification, and distribution is subject to the C++ convenient wrappers library license Version 1.0 at accompanying
// file license.txt or at http://www.cpphelpers.org/license/
// 
// See documentation at docs/index.html


//==============================================================================================================================
//! 
//! @file
//! 
#pragma once


//==============================================================================================================================
#include <functional>


//==============================================================================================================================
#include <boost/signals2/dummy_mutex.hpp>
#include <boost/signals2/detail/slot_groups.hpp>


//==============================================================================================================================
namespace cws
{


    //==========================================================================================================================
    namespace events
    {


        //======================================================================================================================
        //! 
        //! @brief Specifies where the listener will be placed within priority order.
        //! 
        //! Uses as a parameter of function add_listener.
        //! 
        //! @remark When a priority value is specified, the final Order::BACK or Order::FRONT parameter describes where the
        //! listener will be placed within the priority order.
        //! 
        //! @remark Listeners without specified priority value and with the final Order::FRONT parameter will always precede all
        //! listeners with specified priority values.
        //! 
        //! @remark Listeners without specified priority value and with the final Order::BACK parameter will always succeed all
        //! listeners with specified priority values.
        //! 
        //! @par Header
        //! cws/events.hpp
        //! 
        //! @par Namespace
        //! cws::events
        //! 
        //! @par Example
        //! @include{lineno} example_order.cpp
        //! 
        //! @par Output
        //! @include example_order.txt
        //! 
        enum class Order
        {
            BACK  = boost::signals2::at_back,   //!< Specifies that listener will be placed to the queue's back.
            FRONT = boost::signals2::at_front,  //!< Specifies that listener will be placed to the queue's front.
        };


        //======================================================================================================================
        //! 
        //! @brief Specifies type of priority and method for determining higher priority.
        //! 
        //! Uses as a template parameter of Dispatcher class and dispatcher::Type structure.
        //! 
        //! @tparam _Priority A type of priority that is used for specifying listeners' invocation order.
        //! @tparam _Comparator A type of method used for determining higher priority.
        //! 
        //! @remark Invocation order:\n
        //! 1) Listeners subscribed without specifying priority value and with _order = Order::FRONT.\n
        //! 2) Listeners subscribed with a particular priority according to the ordering of their priority values.\n
        //! 3) Listeners subscribed without specifying priority value and with _order = Order::BACK.\n
        //! 
        //! @par Header
        //! cws/events.hpp
        //! 
        //! @par Namespace
        //! cws::events
        //! 
        //! @par Example
        //! @include{lineno} example_priority_type.cpp
        //! 
        //! @par Output
        //! @include example_priority_type.txt
        //! 
        template <typename _Priority = int, typename _Comparator = std::less<_Priority>>
        struct PriorityType
        {
            typedef _Priority    priority_type;   //!< Priority type provided through template parameter to instantiate struct.
            typedef _Comparator  comparator_type; //!< Comparator type provided through template parameter to instantiate struct.
        };


        //======================================================================================================================
        //! 
        //! @brief Specifies the type of mutex that will be used to provide tread safety.
        //! 
        //! Uses as a template parameter of Dispatcher class and dispatcher::Type structure.
        //! 
        //! @tparam _Mutex Any mutex type. It must be default-constructible and have public lock() and unlock() methods.
        //! 
        //! @remark Default value is boost::signals2::dummy_mutex.This is a fake mutex for use in single-threaded programs,
        //! where locking a real mutex would be useless overhead.
        //! 
        //! @par Header
        //! cws/events.hpp
        //! 
        //! @par Namespace
        //! cws::events
        //! 
        //! @par Example
        //! @include{lineno} example_mutex_type.cpp
        //! 
        //! @par Possible output
        //! @include example_mutex_type.txt
        //! 
        template <typename _Mutex = boost::signals2::dummy_mutex>
        struct MutexType
        {
            typedef _Mutex  type; //!< Mutex type provided through template parameter to instantiate struct.
        };


        //======================================================================================================================
        //! 
        //! @brief Specifies dispatcher's events list.
        //! 
        //! Uses as a template parameter of Dispatcher class and dispatcher::Type structure.
        //! 
        //! \tparam ..._Events Types of events that dispatcher can dispatch.
        //! 
        //! @par Header
        //! cws/events.hpp
        //! 
        //! @par Namespace
        //! cws::events
        //! 
        //! @par Example
        //! @include{lineno} example_types_list.cpp
        //! 
        //! @par Output
        //! @include example_types_list.txt
        //! 
        template <typename ..._Events>
        struct TypesList
        {
        };

    }  // namespace events

}  // namespace cws
