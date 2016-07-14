
// ==========================================================================
// Copyright : Brent Cranko 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef DECODER_HPP
#define DECODER_HPP
#include "hwlib.hpp"
#include "DateTime.hpp"

///@file

///decoder Class
//
///This class is made to interpret the data stored in the raw_data_buffer.
///It consists of a buffer for the complete signal, a decoded buffer that holds 59 spaces and a marker variable for the start and end of the signal.
///The class decodes the given raw data and puts it in an array. 
///It's also the place where parity checks are made to see if the signal is correct.
class decoder
{
private:
        ///Decoded signal variable
        //
        ///This is where the signal is stored after the markers have been found.
        int decoded_signal[59];
        
        ///Buffer variable
        //
        ///This variable stores the decoded signal. It uses 121 spaces so there will always be 2 markers present.
        int buffer[121];
        
        ///Marker begin
        //
        ///This is a variable which will be set to 1 when the first marker is found in the raw data stream
        int marker_begin = 0;
        
        ///Marker end
        //
        ///This is a variable which will be set to 1 when the second marker is found in the raw data stream
        int marker_end = 0;
        
        ///Raw data buffer
        //
        ///This is where the initial signal is stored. It contains enough space for 2 minutes of signal.
        ///The signal consists of zero's and one's. These are not logical zero's and one's though. The signal gives a logical 0 if it's high for 100ms and a logical 1 if it's high for 200ms
        int (&raw_data_buffer)[5760];
        
        ///Store Data method
        //
        ///This function first checks the signal. Bit 0 should always be 0 and bit 20 should always be 1. If these are incorrect the function will return 0.
        ///If they are both correct, the data will be stored in an array so it can be used,
        bool store_data();
        
        ///Parity check method. 
        //
        ///This method will perform a parity check. It takes the first place in the array over which the parity is checked as first argument.
        ///The second argument is the parity bit itself. Since the loop inside this function will run up untill the parity bit without including it another argument is not needed.
        bool parity_check(int start, int stop);
        
public:
        ///Decoder constructor
        //
        ///This sets up the decoder, takes two minutes of data.
        decoder(int (&raw_data_buffer)[5760]);
        
        ///Get decoded signal method
        //
        ///This method returns a reference to the fully decoded signal which consists of 59 bits.
        int (& get_decoded_signal())[59];
        
        ///Parity check
        //
        ///This runs the 3 private parity methods which check if the signal has degraded or not. It returns 1 for a good signal and 0 for a degraded signal.
        bool parity_check_all();
        
        ///Process Data 
        //
        ///This function takes the raw data stream and decodes it. It takes the raw data buffer and decodes it into logical bits.
        bool process_data();
        
        ///Print decoded signal
        //
        ///This takes the signal and then sends it to output
        void print_decoded_signal();
        
        ///Calc min
        //
        ///Get's the minutes from the decoded signal
        int calc_minutes();
        
        ///Calc hour
        //
        ///Get's the hour from the decoded signal
        int calc_hour();
        
        ///Calc day of the month
        //
        ///Get's the day of the month from the decoded signal
        int calc_day_of_the_month();
        
        ///Calc day of the week
        //
        ///Get's the day of the week from the decoded signal
        int calc_day_of_the_week();
        
        ///Calc month
        //
        ///Get's the month from the decoded signal
        int calc_month();
        
        ///Calc year in century
        //
        ///Get's the year in century from the decoded signal
        int calc_year_in_century();

};

#endif // DECODER_HPP
