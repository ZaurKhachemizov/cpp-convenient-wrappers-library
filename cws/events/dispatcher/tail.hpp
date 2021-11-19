// cws::events::dispatcher::Tail class is vertex class in cws::events::Dispatcher's scattered hierarchy.
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
            template <typename ..._Types>
            class Tail;


            //==================================================================================================================
            // 
            // Empty tail in cws::events::Dispatcher's scattered hierarchy.
            // 
            template <typename _Mutex, typename _Priority, typename _Comparator>
            class Tail<_Mutex, _Priority, _Comparator>
            {
            protected:
                //==============================================================================================================
                Tail() = default;

                //==============================================================================================================
                Tail(Tail &&_source) noexcept
                {
                }

                //==============================================================================================================
                void swap(Tail &_source) noexcept
                {
                }

                //==============================================================================================================
                void remove_listeners()
                {
                }

            private:
                Tail           (Tail const &) = delete;
                Tail &operator=(Tail const &) = delete;
                Tail &operator=(Tail &&)      = delete;
            };


            //==================================================================================================================
            //.
            // Vertex in cws::events::Dispatcher's scattered hierarchy. Inherited from cws::events::dispatcher::Head class for
            // the first provided event type and next vertex for the rest of events types.
            // 
            template <typename _Mutex, typename _Priority, typename _Comparator, typename _This, typename ..._Rest>
            class Tail<_Mutex, _Priority, _Comparator, _This, _Rest...> :
                public Head<_Mutex, _Priority, _Comparator, _This>,
                public Tail<_Mutex, _Priority, _Comparator, _Rest...>
            {
                typedef Head<_Mutex, _Priority, _Comparator, _This>     head_t;
                typedef Tail<_Mutex, _Priority, _Comparator, _Rest...>  tail_t;

            protected:
                //==============================================================================================================
                Tail() = default;

                //==============================================================================================================
                Tail(Tail &&_source) noexcept
                    : head_t(std::move(_source))
                    , tail_t(std::move(_source))
                {
                }

                //==============================================================================================================
                void swap(Tail &_source) noexcept
                {
                    head_t::swap(_source);
                    tail_t::swap(_source);
                }

                //==============================================================================================================
                // 
                // Removes all listeners for the current head and calls the same function for the rest of vertices.
                // 
                void remove_listeners()
                {
                    head_t::remove_listeners();
                    tail_t::remove_listeners();
                }

            private:
                Tail           (Tail const &) = delete;
                Tail &operator=(Tail const &) = delete;
                Tail &operator=(Tail &&)      = delete;
            };

        }  // namespace dispatcher

    }  // namespace events

}  // namespace cws
