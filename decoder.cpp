
// ==========================================================================
// Copyright : Brent Cranko 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "decoder.hpp"

decoder::decoder(int (&raw_data_buffer)[5760]): 
        raw_data_buffer(raw_data_buffer)
        
{}

int (&decoder::get_decoded_signal())[59]{
    return decoded_signal;
}

bool decoder::store_data(){
    int j = 0;
    if(buffer[marker_begin + 1] || !buffer[marker_begin + 21]){
        
        hwlib::cout<<"eerste bit is niet correct\n";
        return 0;
    }
    for(int i = marker_begin + 1; i < marker_end; i++){
        decoded_signal[j] = buffer[i];
        j++;
    }
    return 1;
}

bool decoder::process_data(){
        
        int zero_counter = 0;
        int one_counter = 0;
        int n = 0;
        
        for(int i=0;i<5760;i++){
            if(raw_data_buffer[i] == 0){
                zero_counter++;
                if(zero_counter >= 86){
                        buffer[n] = 2;
                        if(marker_begin){
                            marker_end = n;
                            hwlib::cout<<"marker 2 is gevonden \n";
                        }
                        else{
                            marker_begin = n;
                            hwlib::cout<<"marker 1 is gevonden \n";
                        }
                        n++;
                        zero_counter = 0;
                }
            }
        
            if (raw_data_buffer[i] == 1){
                one_counter++;
                
                if((raw_data_buffer[i] == 1)and(raw_data_buffer[i+1] == 0)){
                    if(one_counter < 3){
                        one_counter = 0;
                        continue;
                    }
                    if (zero_counter < 30 && one_counter >= 1){
                        one_counter = 0;
                    }
                    zero_counter = 0;
                    
                    if(one_counter <= 5) {
                        buffer[n] = 0;            
                    }
                    
                    if(one_counter >= 6){
                        buffer[n] = 1;
                    }
                    n++;
                    one_counter=0;
                }
            }
        }
        return store_data();
}

bool decoder::parity_check_all(){
      return parity_check(21, 28) and parity_check(29, 35) and parity_check(36, 58);
}

 bool decoder::parity_check(int start, int stop){
      int sum = 0;
      for (int i = start; i<stop;i++){
          sum += decoded_signal[i];
      }
      return (sum%2) == decoded_signal[stop];
  }

//bool decoder::parity_check() {
//    return parity_check_minutes() and parity_check_hour() and parity_check_date();
//}
//
//// bool decoder::parity_check(bit_matrix, start, stop)
//    
//bool decoder::parity_check_minutes(){
//    int sum =0;
//    for(int i = 21; i<28;i++) {
//        sum += decoded_signal[i];
//    }
//    return (sum % 2) == decoded_signal[28]);
//}
//
//    
//bool decoder::parity_check_hour(){
//    int sum =0;
//    for(int i = 29; i<35;i++)
//        sum += decoded_signal[i];
//    return sum % 2 == decoded_signal[35];
//    }
//    
//bool decoder::parity_check_date(){
//    int sum =0;
//    for(int i = 36; i<58;i++)
//        sum += decoded_signal[i];
//    return sum % 2 == decoded_signal[58];
//    }

void decoder::print_decoded_signal(){
    for(int i = 0; i < 59; i++){
        hwlib::cout << i << ":  "<< decoded_signal[i] << "\n";
    }
}

int decoder::calc_minutes(){
    int minutes = 0;
    minutes += decoded_signal[21];
    minutes += decoded_signal[22] * 2;
    minutes += decoded_signal[23] * 4;
    minutes += decoded_signal[24] * 8;
    minutes += decoded_signal[25] * 10;
    minutes += decoded_signal[26] * 20;
    minutes += decoded_signal[27] * 40;
    return minutes;
    }
int decoder::calc_hour(){
    int hour= 0;
    hour += decoded_signal[29];
    hour += decoded_signal[30] * 2;
    hour += decoded_signal[31] * 4;
    hour += decoded_signal[32] * 8;
    hour += decoded_signal[33] * 10;
    hour += decoded_signal[34] * 20;
    return hour;
    }
int decoder::calc_day_of_the_month(){
    int day_of_the_month= 0;
    day_of_the_month += decoded_signal[36];
    day_of_the_month += decoded_signal[37] * 2;
    day_of_the_month += decoded_signal[38] * 4;
    day_of_the_month += decoded_signal[39] * 8;
    day_of_the_month += decoded_signal[40] * 10;
    day_of_the_month += decoded_signal[41] * 20;
    return day_of_the_month;
    }
int decoder::calc_day_of_the_week(){
    int day_of_the_week= 0;
    day_of_the_week += decoded_signal[42];
    day_of_the_week += decoded_signal[43] * 2;
    day_of_the_week += decoded_signal[44] * 4;
    return day_of_the_week;
    }
int decoder::calc_month(){
    int month= 0;
    month += decoded_signal[45];
    month += decoded_signal[46] *2;
    month += decoded_signal[47] *4;
    month += decoded_signal[48] *8;
    month += decoded_signal[49] *10;
    return month;
    }
int decoder::calc_year_in_century(){
    int year_in_century= 0;
    year_in_century += decoded_signal[50];
    year_in_century += decoded_signal[51]*2;
    year_in_century += decoded_signal[52]*4;
    year_in_century += decoded_signal[53]*8;
    year_in_century += decoded_signal[54]*10;
    year_in_century += decoded_signal[55]*20;
    year_in_century += decoded_signal[56]*40;
    year_in_century += decoded_signal[57]*50;
    return year_in_century;
    }

