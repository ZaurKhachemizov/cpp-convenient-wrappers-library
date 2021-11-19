// A convenient header for cws::events, pulling in all required headers in the library.
//
// Copyright (c) 2014-2021 Zaur Khachemizov
//
// Use, modification, and distribution is subject to the C++ convenient wrappers library license Version 1.0 at accompanying
// file license.txt
//
// See documentation at docs/index.html


//==============================================================================================================================
#pragma once


//==============================================================================================================================
#include "events/details.hpp"
#include "events/dispatcher.hpp"
#include "events/dispatcher/type.hpp"


//!
//! @mainpage C++ convenient wrappers library
//! 
//! @section About
//! C++ convenient wrappers library is a free open source library for C++ programming language. The library helps to increase
//! development speed, to make programs more stable and scalable, to make code neater and shorter, and allows to avoid
//! unnecessary relations and code duplications.
//! 
//! @subsection Usage
//! Include header files you need from ./csw folder depending on what parts of the library you want to use.\n
//! Below you will find lists of compilers, standards, and third-party libraries' versions the library tested with.
//! The library is cross-platform and supports a number of standards and third-party libraries' versions but when using it in
//! untested conditions, some fixes may be necessary.
//! 
//! For now, no build toolchain for tests is provided.To build anduse tests you need to build andrun ./tests/tests.cpp
//! using build toolchain you need.Also, you need to build.cpp files from ./examples/... so each app and corresponding.txt file
//! will be located in the tests' working directory.
//! 
//! @par Supported C++ Standards
//! C++14
//! 
//! @par Supported C++ Compilers
//! VC142
//! 
//! @par Supported Boost Versions
//! 1.72.0
//! 
//! @section Parts
//! 
//! @subsection Events
//! 
//! @par Terms
//! Event: An object that represents some event that occurs in some code section.\n
//! Listener: Function object, function, or member function that will be invoked, when an event occurs.\n
//! Dispatcher: An object that manages listeners and invokes them when events occur.\n
//! To subscribe: Add a listener to a dispatcher. The listener starts listening for an event.\n
//! To unsubscribe: Remove listener from a dispatcher. The listener no longer listens for the event.\n
//! 
//! @par Description
//! cws::events::Dispatcher class provides a simple way of subscribing listeners to events and invoking them when events occur.
//! This class can be both thread-safe or not, provides custom listeners' invocation order, and automatically unsubscribes
//! listeners that are managed by boost::shared_ptr and std::shared_ptr classes when the shared object expires.
//! 
//! @par Attention
//! cws::events::Dispatcher class is a boost::signals2 wrapper. It is necessary to have boost libraries installed on your
//! machine to use this class.
//! 
//! @par Tutorial
//! @ref tutorial_start_page
//! 
//! @section Copyright
//! 
//! @par License
//! This library (the "Library") is free of charge. Permission is granted to use, distribute, and prepare derivative works on
//! the Library.\n
//! This license must be included in all copies of the Library and all derivative works of the Library if they are distributed
//! as a source code.\n
//! The Library is provided without any kind of warranty. The copyright holders shall not be liable for any circumstances
//! arising from the use of the Library.
//! 
//! @par Author
//! Zaur Khachemizov
//! 
//! @par Date
//! 2014 - 2021
//! 

//! 
//! @page tutorial_start_page Events Tutorial Start
//! First, we define a structure HelloWorldEvent that will represent the Hello World event. Next, we define a dispatcher that
//! will be able to dispatch the event. After that, we subscribe the hello_world_listener function to the event using the
//! add_listener method. Finally, we use the dispatch method to notify the listener that the event occurred, which invokes the
//! hello_world_listener function. In addition, we unsubscribe the hello_world_listener function from the event using the
//! remove_listener method and call the dispatch method again.
//! 
//! @par Code
//! @include{lineno} tutorial_start.cpp
//!
//! @par Output
//! @include tutorial_start.txt
//! 
//! Any custom class can dispatch events. Learn more:
//! @ref tutorial_custom_class_page
//! 
//! Any function object, function, or member function can subscribe to events. Learn more:
//! @ref tutorial_listeners_page
//! 
//! By default listeners are invoked in the same order they were subscribed to. Listeners' invocation order can be customized.
//! Learn more:
//! @ref tutorial_priority_page
//! 
//! By default, a Dispatcher is not thread-safe. The dispatcher can be used in a multi-threaded environment. Learn more:
//! @ref tutorial_thread_safe_page
//! 

//! 
//! @page tutorial_custom_class_page Custom Class As Events Dispatcher
//! To make a custom class available to dispatch events, it must either be derived from the Dispatcher class or have a member
//! of the type Dispatcher. We define a class that is derived from Dispatcher. The Hello World event will occur when the
//! say_hello method will be called.
//! 
//! @par Code
//! @include{lineno} tutorial_custom_class.cpp
//!
//! @par Output
//! @include tutorial_custom_class.txt
//! 

//! 
//! @page tutorial_listeners_page Events Listeners
//! To subscribe a member function to the event, we use boost::bind that wrap a pointer to the member function and a pointer
//! to an object of the class function is a member into a function object.
//! 
//! @par Code
//! @include{lineno} tutorial_listeners.cpp
//!
//! @par Output
//! @include tutorial_listeners.txt
//! 
//! Function object must have overloaded operator ==. \n
//! 
//! Instead of a pointer to an object, std::shared_ptr or boost::shared_ptr can be used. Learn more:
//! @ref tutorial_shared_listeners
//! 

//! 
//! @page tutorial_shared_listeners Events Listeners As Shared Objects
//! For events listeners that are member functions of objects managed by boost::shared_ptr or std::shared_ptr, we just pass a
//! pointer to the member function and shared object as parameters to the add_listener function.
//! 
//! @par Code
//! @include{lineno} tutorial_shared_listeners.cpp
//!
//! @par Output
//! @include tutorial_shared_listeners.txt
//! 
//! In this case, the listener will automatically unsubscribe when the shared object expires.
//! 

//! 
//! @page tutorial_priority_page Listeners' Priority
//! To specify where the listener will be placed within the priority ordering enum class Order is used. Priority is specified
//! by the first parameter of the add_listener function. To unsubscribe listeners with the specified priority from the event
//! the remove_listeners method is used. To unsubscribe all listeners from all events the remove_listeners method without
//! parameters is used.
//! 
//! @par Code
//! @include{lineno} tutorial_priority.cpp
//!
//! @par Output
//! @include tutorial_priority.txt
//! 
//! By default, the type of priority is int, and the method to determine the highest priority is std::less. The type of
//! priority and a method to determine the highest priority can be customized. Learn more:
//! @ref tutorial_custom_priority_page
//! 

//! 
//! @page tutorial_custom_priority_page Listeners' Custom Priority
//! To specify the type of priority and a method to determine the highest priority a structure PriorityType and a class
//! dispatcher::Type are used.
//! 
//! @par Code
//! @include{lineno} tutorial_custom_priority.cpp
//!
//! @par Output
//! @include tutorial_custom_priority.txt
//! 
//! By default, a method to determine the highest priority is std::less, where type_of_priority is the first template parameter
//! in the structure PriorityType.
//! 

//!
//! @page tutorial_thread_safe_page Events Thread Safety
//! To use Dispatcher in a multi-threaded environment the type of mutex that will be used to provide thread safety must be
//! specified. To do so a structure MutexType and a class dispatcher::Type are used.
//! 
//! @par Code
//! @include{lineno} tutorial_thread_safe.cpp
//!
//! @par Possible output
//! @include tutorial_thread_safe.txt
//! 
//! A mutex can be of any default-constructible type with public methods lock() and unlock().
//! 
