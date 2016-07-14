
// ==========================================================================
// Copyright : Brent Cranko 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "signal.hpp"

signal::signal(target::pin_in & p,unsigned long sampling_time):
        raw_data(p),
        sampling_time(sampling_time),
        buffer_counter(0)
        
{}

    unsigned long sampling_time;
    unsigned int buffer_counter;

void signal::fill(){
    
    unsigned int j = 0;
    while(j<5760){
        raw_data_buffer[j] = raw_data.get();
        j++;
        hwlib::wait_us(20000);
    }
}

int(& signal::get_signal())[5760]{
    return raw_data_buffer;
}

int signal::fill_once(){
    if(buffer_counter < 5760){
        raw_data_buffer[buffer_counter] = raw_data.get();
        buffer_counter++;
        return 0;
    }
    else{
        buffer_counter = 0;
        return 1;
    }
}

int signal::raw_data_buffer_element(int index){
    return raw_data_buffer[index];
}