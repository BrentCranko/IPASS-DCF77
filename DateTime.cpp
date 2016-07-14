
// ==========================================================================
// Copyright : Brent Cranko 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "DateTime.hpp"

DateTime::DateTime(const int minutes,const int hour, const int day_of_the_week,const int day_of_the_month,const int month,const int century, const int year_in_century):
    minutes(minutes),
    hour(hour),
    day_of_the_week(static_cast<DAYOFTHEWEEK>(day_of_the_week)),
    day_of_the_month(day_of_the_month),
    month(month),
    century(century),
    year_in_century(year_in_century)
{}

DateTime::DateTime():
    minutes(0),
    hour(0),
    day_of_the_week(static_cast<DAYOFTHEWEEK>(0)),
    day_of_the_month(0),
    month(0),
    century(0),
    year_in_century(0)
{}    
    
hwlib::ostream & operator<<( hwlib::ostream & lhs, DateTime dateTime ){
    lhs << dateTime.hour << ":" << dateTime.minutes <<"\t" <<dateTime.day_of_the_week<<" "<< dateTime.day_of_the_month <<"/"<<dateTime.month<<"/"<<dateTime.century<< dateTime.year_in_century<<"\n";
    return lhs;
}

hwlib::ostream & operator<<(hwlib::ostream & lhs, DAYOFTHEWEEK day_of_the_week ){
    switch(day_of_the_week){
        case DAYOFTHEWEEK::MONDAY:
            return lhs << "Monday";
        case DAYOFTHEWEEK::TUESDAY:
            return lhs << "Tuesday";
        case DAYOFTHEWEEK::WEDNESDAY:
            return lhs << "Wednesday";
        case DAYOFTHEWEEK::THURSDAY:
            return lhs << "Thursday";
        case DAYOFTHEWEEK::FRIDAY:
            return lhs << "Friday";
        case DAYOFTHEWEEK::SATURDAY:
            return lhs << "Saturday";
        case DAYOFTHEWEEK::SUNDAY:
            return lhs << "Sunday";
        default:
            return lhs;
    }
}
