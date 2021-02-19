/*
 * sensor_thread.c
 *
 *  Created on: Feb 9, 2021
 *      Author: alisd
 */

#include "timer70.h"
#include "sensor_queue.h"

//void *timer70Thread(void *arg0)
void timer70Thread()
{
    dbgOutputEvent(DEBUG1);
    Timer_Handle timer;
    Timer_Params params;

    Timer_Params_init(&params);
    params.period = 70000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback70;

    timer = Timer_open(CONFIG_TIMER_0, &params);

    if (timer == NULL) {
    /* Failed to initialized timer */
        while (1) {
            dbgOutputEvent(DEBUG2);
        }
    }

    if (Timer_start(timer) == Timer_STATUS_ERROR) {
    /* Failed to start timer */
         while (1) {
             dbgOutputEvent(DEBUG3);
         }
    }
}

void timerCallback70(Timer_Handle myHandle, int_fast16_t status)
{
    static sensorQueueMessage message;
    dbgOutputEvent(DEBUG75); //DEBUG4

    GPIO_toggle(CONFIG_GPIO_LED_0);

    static int var = 0;
    if (var >= 200) {
        var = 0;
    } else {
        var += 1;
    }

    message.type = TIMER70_MESSAGE;
    message.sensorReading = var;
    sendToSensorQueue(&message);

//    dbgOutputEvent(EXIT_TIMER70);
}


