#ifndef APIDELAY_H
#define APIDELAY_H

#include <Arduino.h>

typedef uint32_t tick_t;
typedef bool bool_t;

    typedef struct {
        tick_t startTime;
        tick_t duration;
        tick_t running;
    } delay_t;

#define DELAY_5_S 5000
#define DELAY_250_MS 250
#define DELAY_30_S 30000
#define DELAY_2_M 120000

    void delayInit(delay_t *delay, tick_t duration);
    bool_t delayRead(delay_t *delay);
    void delayWrite(delay_t *delay, tick_t duration);



#endif
