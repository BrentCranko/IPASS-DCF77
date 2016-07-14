
// ==========================================================================
// Copyright : Brent Cranko 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "signal.hpp"
#include "decoder.hpp"   
#include "DateTime.hpp"
#include "timer.hpp"

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   hwlib::wait_ms(500);

    target::pin_in p1(target::pins::d7);
    timer t(20000);
    signal s(p1,20000);
    DateTime dt;     
    int end_signal = 0;
    t.start();
    while(!end_signal){
        if(t.poll()){
            end_signal = s.fill_once();
        }       
    }
    
    hwlib::cout<<"\n\n";
    
    decoder d(s.get_signal());
    
    if(d.process_data()){
        if(d.parity_check_all()){
            dt = DateTime(d.calc_minutes(),d.calc_hour(),d.calc_day_of_the_week(),d.calc_day_of_the_month(),d.calc_month(),20,d.calc_year_in_century());
            hwlib::cout << dt;
        }
        else
            hwlib::cout << "parity check gone wrong";
    }
    else
        hwlib::cout<<"bit 0 of bit 20 niet correct, vals signaal!";
    
}

    

    
