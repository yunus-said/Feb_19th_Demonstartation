/*
 * timer500.c
 *
 *  Created on: Feb 13, 2021
 *      Author: Yunus
 */

#include "timer500.h"
#include "sensor_queue.h"

//void *timer500Thread(void *arg0)
void timer500Thread()
{
    dbgOutputEvent(DEBUG5);

    Timer_Handle timer;
    Timer_Params params;

    Timer_Params_init(&params);
    params.period = 200000; //209000 maximum period
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback500;

    timer = Timer_open(CONFIG_TIMER_1, &params);

    if (timer == NULL) {
    /* Failed to initialized timer */
        while (1) {
            dbgOutputEvent(DEBUG6);
        }
    }

    if (Timer_start(timer) == Timer_STATUS_ERROR) {
    /* Failed to start timer */
         while (1) {
             dbgOutputEvent(DEBUG7);
         }
    }
}

void timerCallback500(Timer_Handle myHandle, int_fast16_t status)
{
    static sensorQueueMessage message;
    dbgOutputEvent(DEBUG100); //DEBUG4

    GPIO_toggle(CONFIG_GPIO_LED_1);

    static uint32_t TimeBefore = 0;

    message.type = TIMER500_MESSAGE;
    message.elapsedTime = xTaskGetTickCountFromISR() - TimeBefore;
    message.sensorReading = xTaskGetTickCountFromISR();
    TimeBefore = xTaskGetTickCountFromISR();
    sendToSensorQueue(&message);

//    dbgOutputEvent(EXIT_TIMER500);
}


