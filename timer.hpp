
// ==========================================================================
// Copyright : Marten Butter 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef TIMER_HPP
#define TIMER_HPP

#include "hwlib.hpp"
class timer
{
private:
    unsigned long interval;
    unsigned long interval_time;
    unsigned long start_time;
    unsigned long previous_time;
    unsigned long current_time;
    int is_running;
    unsigned long stop_time;
    
public:
    timer(unsigned const long interval_time);
    
    long start();
    long stop();
        
    int poll();
    
    
};

#endif // TIMER_HPP
