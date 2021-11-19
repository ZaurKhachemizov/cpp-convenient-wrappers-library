// Template structures using to specify cws::events::dispatcher::Base type.
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
#include "../../details.hpp"


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
            namespace base
            {


                //==============================================================================================================
                // 
                // Specifies default Dispatcher's base type.
                // 
                template <typename ..._Events>
                struct DefaultType
                {
                    typedef Base<typename MutexType<>::type, typename PriorityType<>::priority_type,
                                 typename PriorityType<>::comparator_type, _Events...>  type;
                };


                //==============================================================================================================
                // 
                // Specifies custom Dispatcher's base type.
                // 
                template <typename _Mutex, typename _Priority, typename _Comparator, typename ..._Events>
                struct Type
                {
                    typedef Base<_Mutex, _Priority, _Comparator, _Events...>  type;
                };

            }  // base

        }  // dispatcher

    }  // events

}  // cws
