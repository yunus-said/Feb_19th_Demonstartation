/*
 * sensor_thread_state.c
 *
 *  Created on: Feb 15, 2021
 *      Author: Team 09
 */

#include <sensor_state.h>
#include "debug.h"


void updateSensorFSM(sensorQueueMessage *msg) {
    static sensorStates state = INIT_AVERAGE;
    static int sensorTotal = 0;
    static int sensorCount = 0;
    static char* myChar;

    switch (state) {
        case INIT_AVERAGE:
            if (msg->type == TIMER70_MESSAGE) {
                sensorTotal = 0;
                sensorCount = 0;
            } else if (msg->type == TIMER500_MESSAGE) {
                sensorTotal = 0;
                sensorCount = 0;
                state = UPDATE_AVERAGE;
            }

            break;

        case UPDATE_AVERAGE:
            if (msg->type == TIMER70_MESSAGE) {
                sensorTotal += msg->sensorReading;
                sensorCount += 1;
                sprintf(myChar, "Sensor = %d mm", msg->sensorReading);
//                sendToUARTQueue(myChar);

            } else if (msg->type == TIMER500_MESSAGE) {
                int sensorAve = 0;
                if (sensorCount > 0) {
                    sensorAve = sensorTotal / sensorCount;
                }
                sprintf(myChar, "Avg = %d mm and Time = %d ms", sensorAve, msg->elapsedTime);

                state = INIT_AVERAGE;
            }

            break;
    }
}
