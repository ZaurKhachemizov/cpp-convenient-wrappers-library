// cws::events::Dispatcher class is used to manage listeners and dispatch events.
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
#include "details.hpp"
#include "dispatcher/base.hpp"
#include "dispatcher/base/types.hpp"


//==============================================================================================================================
namespace cws
{


    //==========================================================================================================================
    namespace events
    {


        //======================================================================================================================
        //! 
        //! @brief Default Dispatcher class.
        //! 
        //! Dispatcher class is used to subscribe listeners to events, unsubscribe listeners from events, and dispatch events to
        //! subscribed listeners.
        //! 
        //! @tparam ..._Events Types of events that dispatcher can dispatch.
        //! 
        //! @remark Dispatcher class is default-constructible, non-copyable, moveable.
        //! 
        //! @remark By default, Dispatcher class is non-thread-safe.
        //! 
        //! @remark By default, listeners' priority is of type int, and the method to determine the highest priority is
        //! std::less<int>.
        //! 
        //! @par Header
        //! cws/events.hpp
        //! 
        //! @par Namespace
        //! cws::events
        //! 
        //! @par Example
        //! @include{lineno} example_dispatch.cpp
        //! 
        //! @par Output
        //! @include example_dispatch.txt
        //! 
        template <typename ..._Events>
        class Dispatcher :
            public dispatcher::base::DefaultType<_Events...>::type
        {
            typedef typename dispatcher::base::DefaultType<_Events...>::type  base_t;

        public:
            //==================================================================================================================
            //! 
            //! @brief Default constructor.
            //! 
            //! Instantiates object of Dispatcher class according to provided template parameters.
            //! 
            //! @par Complexity
            //! Linear in the number of events.
            //! 
            //! @par Exception safety
            //! Will not throw.
            //! 
            //! @par Example
            //! @include{lineno} example_dispatch.cpp
            //! 
            //! @par Output
            //! @include example_dispatch.txt
            //! 
            Dispatcher() = default;

            //==================================================================================================================
            //! 
            //! @brief Move constructor.
            //! 
            //! Instantiates object of Dispatcher class by moving other Dispatcher class's instance.
            //! 
            //! @par Complexity
            //! Linear in the number of events.
            //! 
            //! @par Exception safety
            //! Will not throw.
            //! 
            //! @par Example
            //! @include{lineno} example_move.cpp
            //! 
            //! @par Output
            //! @include example_move.txt
            //! 
            Dispatcher(Dispatcher &&_source) noexcept
                : base_t(std::move(_source))
            {
            }

            //==================================================================================================================
            //! 
            //! @brief Move assignment.
            //! 
            //! Moving other instance of Dispatcher class into the existing one.
            //! 
            //! @par Complexity
            //! Linear in the number of events.
            //! 
            //! @par Exception safety
            //! Will not throw.
            //! 
            //! @par Example
            //! @include{lineno} example_move.cpp
            //! 
            //! @par Output
            //! @include example_move.txt
            //! 
            Dispatcher &operator=(Dispatcher &&_source) noexcept
            {
                Dispatcher that(std::move(_source));

                base_t::swap(that);

                return *this;
            }
        };


        //======================================================================================================================
        // 
        // Customizable Dispatcher class.
        // 
        // To use customizable Dispatcher class in a convenient way use csw::events::dispatcher::Type structure.
        // 
        template <typename _Mutex, typename _Priority, typename _Comparator, typename ..._Events>
        class Dispatcher<MutexType<_Mutex>, PriorityType<_Priority, _Comparator>, TypesList<_Events...>> :
            public dispatcher::base::Type<_Mutex, _Priority, _Comparator, _Events...>::type
        {
            typedef typename dispatcher::base::Type<_Mutex, _Priority, _Comparator, _Events...>::type  base_t;

        public:
            //==================================================================================================================
            Dispatcher() = default;

            //==================================================================================================================
            Dispatcher(Dispatcher &&_source) noexcept
                : base_t(std::move(_source))
            {
            }

            //==================================================================================================================
            Dispatcher &operator=(Dispatcher &&_source) noexcept
            {
                Dispatcher that(std::move(_source));

                base_t::swap(that);

                return *this;
            }
        };

    }  // namespace events

}  // namespace cws


//==============================================================================================================================
namespace std
{


    //==========================================================================================================================
    //! 
    //! @brief Exchanges content of Dispatcher objects.
    //! 
    //! This non-member function effectively calls _left.swap(_right). This is a specialization of the generic algorithm
    //! std::swap.
    //! 
    //! @tparam ..._Types Template parameters of Dispatcher class.
    //! 
    //! @param[in] _left References to Dispatcher object with the same type as _right (instantiated with the same template parameters) to swap with _right.
    //! @param[in] _right References to Dispatcher object with the same type as _left (instantiated with the same template parameters) to swap with _left.
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
    //! @par Header
    //! cws/events.hpp
    //! 
    //! @par Namespace
    //! std
    //! 
    //! @par Example
    //! @include{lineno} example_std_swap.cpp
    //! 
    //! @par Output
    //! @include example_std_swap.txt
    //! 
    template <typename ..._Types>
    inline void swap(cws::events::Dispatcher<_Types...> &_left, cws::events::Dispatcher<_Types...> &_right) noexcept
    {
        _left.swap(_right);
    }

}  // namespace std
