
// ==========================================================================
// Copyright : Brent Cranko 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef DATETIME_HPP
#define DATETIME_HPP
#include "hwlib.hpp"
///@file

///Enum
//
///This enum get's an integer value. It will be shown as one of the weekdays.
enum class DAYOFTHEWEEK {UNDEFINED = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY,SUNDAY};

///Day of the week stream insertion method
//
///This operator overloads the standard operator for hwlib::ostream so it wil show the name of a weekday instead of the integer value.
hwlib::ostream & operator<<(hwlib::ostream & lhs, DAYOFTHEWEEK day_of_the_week);

///DateTime class
//
///This is an Abstract Data Type.
///It gets data from the decoder and shows it on screen.
class DateTime{
private:
    int minutes;
    int hour;
    DAYOFTHEWEEK day_of_the_week;
    int day_of_the_month;
    int month ;
    int century ;
    int year_in_century ;
   
    
public:
///DateTime 
//
///Default constructor
    DateTime();
///DateTime
//
///Constructor for when all data is available. Most values are just the numeric values. Day_of_the_week is an enum. 1 is monday and 7 is sunday. 
///The signal doesn't tell us in which century or millenia we're in so that will be hardcoded.
    DateTime(const int minutes,const int hour, const int day_of_the_week,const int day_of_the_month,const int month,const int century, const int year_in_century);
    friend hwlib::ostream & operator<<( hwlib::ostream & lhs, DateTime pos );


};

#endif // DATETIME_HPP
