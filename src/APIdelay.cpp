#include "APIdelay.h"


/**
 * @brief Initialize the delay_t structure with the specified duration.
 * 
 * @param delay Pointer to the delay_t structure to be initialized.
 * @param duration Duration of the delay in milliseconds.
 */
void delayInit(delay_t *delay, tick_t duration)
{
    delay->duration = duration;
    delay-> running = false;
}


/**
 * @brief Check if the specified delay has elapsed.
 * 
 * If the delay has not started yet (running = false), it will start the delay and return false.
 * If the delay is still running, it will check if the specified duration has passed since the delay started.
 * 
 * @param delay Pointer to the delay_t structure to be checked.
 * @return bool_t Returns true if the delay has elapsed; otherwise, false.
 */
bool_t delayRead(delay_t *delay)
{
    if(!delay->running)
    {
        delay->startTime = millis();
        delay->running = true;
    }else
    {
        tick_t currentTime = millis();
        if(currentTime - delay->startTime >= delay->duration)
        {
            delay->running = false;
            return true;
        } 
    }
    return false;
}


/**
 * @brief Set a new duration for the specified delay and stop the delay if it is currently running.
 * 
 * @param delay Pointer to the delay_t structure to be updated.
 * @param duration New duration of the delay in milliseconds.
 */
void delayWrite(delay_t *delay, tick_t duration)
{
    delay->duration = duration;
    delay ->running = false;
}
