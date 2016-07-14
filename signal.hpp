#ifndef SIGNAL_H
#define SIGNAL_H
#include "hwlib.hpp"
#include "stdbool.h"
///@file


namespace target = hwlib::target;

///signal Class
//
///This is a class made to get the signal for 2 minutes.
///The signal comes in on pin D7 on an arduino.
///It's stored in the variable raw_data_buffer. The size of this variable is set so that 2 minutes and 4 seconds of the signal fit in.
///The fill method is used to fill the array.
///The get_signal method is then used to return a reference to the filled array so that other parts of the code can use this as well.
class signal{
private:
    int raw_data_buffer[5760];
    target::pin_in raw_data;
    unsigned long long start_time;
    unsigned long interval_time;
    unsigned long sampling_time;
    unsigned int buffer_counter;
public:
///signal constructor
//
///This constructor method is given a pin. The levels of this are used as the signal input.
    signal(target::pin_in & p, unsigned long interval_time);

///fill_once method
//
///This methode can be called upon by something like a timer after which it will check the signal once. It wil also write the data to an array.
    int fill_once();

///fill method
//
///This is a void method fills the array with 2 minutes of signal.
    void fill();

///raw_data_buffer_element
//
///This method asks for an index number and returns the data stored in that location of the raw_data_buffer_element array
    int raw_data_buffer_element(int index);
    
///get signal
//
///This method returns the reference to the filled array.
    int (& get_signal())[5760];

};

#endif // SIGNAL_H
