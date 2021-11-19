// Template structures used to determine cws::events::Dispatcher's customization.
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
            namespace type
            {


                //==============================================================================================================
                template <typename ..._Types>
                struct Base;


                //==============================================================================================================
                // 
                // Last empty tail class with default empty mutex and priority parameters.
                // 
                template <>
                struct Base<>
                {
                protected:
                    typedef MutexType<>     mutex_t;
                    typedef PriorityType<>  priority_t;
                };


                //==============================================================================================================
                // 
                // Extracts mutex type from all cws::events::Dispatcher's template parameters.
                // 
                template <typename _Mutex, typename ..._Rest>
                struct Base<MutexType<_Mutex>, _Rest...> :
                    protected Base<_Rest...>
                {
                protected:
                    typedef MutexType<_Mutex>  mutex_t;
                };


                //==============================================================================================================
                // 
                // Extracts priority type from all cws::events::Dispatcher's template parameters.
                // 
                template <typename _Priority, typename _Comparator, typename ..._Rest>
                struct Base<PriorityType<_Priority, _Comparator>, _Rest...> :
                    protected Base<_Rest...>
                {
                protected:
                    typedef PriorityType<_Priority, _Comparator>  priority_t;
                };


                //==============================================================================================================
                // 
                // Extracts events list from all cws::events::Dispatcher's template parameters.
                // 
                template <typename ..._Events, typename ..._Rest>
                struct Base<TypesList<_Events...>, _Rest...> :
                    protected Base<_Rest...>
                {
                protected:
                    typedef TypesList<_Events...>  list_t;
                };

            } // namespace type

        }  // namespace dispatcher

    }  // namespace events

}  // namespace cws
