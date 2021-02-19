/*
 * sensor_thread_state.h
 *
 *  Created on: Feb 15, 2021
 *      Author: Team 09
 */

#ifndef SENSOR_STATE_H_
#define SENSOR_STATE_H_

#include "sensor_queue.h"

typedef enum {
    INIT_AVERAGE,
    UPDATE_AVERAGE
} sensorStates;

void updateSensorFSM(sensorQueueMessage *msg);

#endif /* SENSOR_STATE_H_ */
