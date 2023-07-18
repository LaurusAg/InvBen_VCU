//Header file for sensor functions
//In this file we can find al the function declarations.

#ifndef DELAY_H
#define DELAY_H
#include <Arduino.h>

class Delay
{
    public:
        Delay();
        void start(unsigned long interval);
        bool isExpired();
        void reset();
        void stop();

    private:
        unsigned long start_time;
        unsigned long interval_time;
        bool stopped; 
};



#endif