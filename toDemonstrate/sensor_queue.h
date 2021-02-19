#ifndef SENSOR_QUEUE_H_
#define SENSOR_QUEUE_H_

#include "debug.h"
#include "queue.h"

#define MAX_QUEUE_SIZE (3)

typedef enum {
    TIMER70_MESSAGE,
    TIMER500_MESSAGE
} sensorQueueMessageType;

typedef struct {
    sensorQueueMessageType type;
    int sensorReading;
    int elapsedTime;
} sensorQueueMessage;

void createSensorQueue();
void sendToSensorQueue(sensorQueueMessage* );
void receiveFromSensorQueue(sensorQueueMessage* );

#endif /* SENSOR_QUEUE_H_ */
