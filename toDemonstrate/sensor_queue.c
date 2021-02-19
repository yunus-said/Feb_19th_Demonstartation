#include "sensor_queue.h"
static QueueHandle_t sensorQueue = NULL;

void createSensorQueue()
{
    sensorQueue = xQueueCreate(MAX_QUEUE_SIZE, sizeof(sensorQueueMessage));
    if(sensorQueue == NULL) {
        stop();
    }
}

void sendToSensorQueue (sensorQueueMessage* msg)
{
    BaseType_t pd;
    dbgOutputEvent(DEBUG12); //BEFORE_SEND_QUEUE_ISR_TIMER1
    pd = xQueueSendFromISR(sensorQueue, (void *) msg, pdFALSE);
    if(pd == pdFALSE) {
        stop();
    }
    dbgOutputEvent(DEBUG13); //AFTER_SEND_QUEUE_ISR_TIMER1
}

void receiveFromSensorQueue(sensorQueueMessage* msg)
{
    BaseType_t pd;
    dbgOutputEvent(DEBUG16); //BEFORE_RECEIVE_QUEUE
    pd = xQueueReceive(sensorQueue, (void *) msg, portMAX_DELAY);
    if(pd == pdFALSE) {
        stop();
    }
    dbgOutputEvent(DEBUG17); //AFTER_RECEIVE_QUEUE
}
