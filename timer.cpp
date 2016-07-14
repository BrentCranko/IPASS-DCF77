
// ==========================================================================
// Copyright : Marten Butter 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "timer.hpp"

timer::timer(unsigned const long interval):
    interval(interval),
    is_running(0)
{}

long timer::start(){
    start_time = hwlib::now_us();
    is_running = 1;
    previous_time = start_time;
    return start_time;
}

long timer::stop(){
    stop_time = hwlib::now_us();
    is_running = 0;
    return stop_time;
}

int timer::poll(){
    previous_time = current_time;
    current_time = hwlib::now_us();
    interval_time += current_time - previous_time;
    if(interval_time>= interval){
        interval_time = 0;
        return 1;
    }
    return 0;
}
