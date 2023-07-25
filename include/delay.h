//Header file for sensor functions
//In this file we can find al the function declarations.

#ifndef DELAY_H
#define DELAY_H
#include <Arduino.h>

#define DELAY_5_S 5000
#define DELAY_250_MS 250
#define DELAY_30_S 30000
#define DELAY_2_M 120000


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