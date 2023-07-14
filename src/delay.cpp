#include <Arduino.h>
#include <delay.h>

Delay::Delay()
{
    start_time = 0;
    interval_time = 0;
}

/**
 * @brief start timer with an specific interval declared in milliseconds.
 * 
 * @param interval Interval of time in millisenconds.
 */
void Delay::start(unsigned long interval)
{
    start_time = millis();
    interval_time = interval;
}
/**
 * @brief Checks if interval of time has expired.
 * 
 * @return true if interval has expired, false if not.
 */
bool Delay::isExpired()
{
    return (millis() - start_time >= interval_time);
}

/**
 * @brief Reset timer.
 */
void Delay::reset()
{
    start_time = millis();
}

