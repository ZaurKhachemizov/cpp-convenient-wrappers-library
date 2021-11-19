// cws::events::dispatcher::Type is using to customize cws::events::Dispatcher.
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
#include "../dispatcher.hpp"
#include "type/base.hpp"


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
            //! @brief Specifies custom Dispatcher type.
            //! 
            //! A convenient way to declare Dispatcher of custom type with specified mutex type and/or priority type and events
            //! list.
            //! 
            //! @tparam ..._Types Can contain MutexType and/or PriorityType. Must contain TypesList.
            //! 
            //! @remark Template parameters order makes no sense.
            //! 
            //! @par Header
            //! cws/events.hpp
            //! 
            //! @par Namespace
            //! cws::events::dispatcher
            //! 
            //! @par Example
            //! @include{lineno} example_dispatcher_type.cpp
            //! 
            //! @par Output
            //! @include example_dispatcher_type.txt
            //! 
            template <typename ..._Types>
            struct Type:
                private type::Base<_Types...>
            {
                typedef Dispatcher<typename Type::mutex_t, typename Type::priority_t, typename Type::list_t>  type;  //!< Uses to instantiate Dispatcher<_Types...>
            };

        }  // namespace dispatcher

    }  // namespace events

}  // namespace cws
