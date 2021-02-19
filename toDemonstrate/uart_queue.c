/*
 * uart_queue.c
 *
 *  Created on: Feb 17, 2021
 *      Author: Team 09
 */

#include "uart_queue.h"
static QueueHandle_t uartQueue = NULL;

void createUartQueue()
{
    uartQueue = xQueueCreate(MAX_QUEUE_SIZE, sizeof(sensorQueueMessage));
    if(uartQueue == NULL) {
        stop();
    }
}

void sendToUartQueue (sensorQueueMessage* msg)
{
    BaseType_t pd;
    dbgOutputEvent(DEBUG12); //BEFORE_SEND_QUEUE_ISR_TIMER1
    pd = xQueueSendFromISR(uartQueue, (void *) msg, pdFALSE);
    if(pd == pdFALSE) {
        stop();
    }
    dbgOutputEvent(DEBUG13); //AFTER_SEND_QUEUE_ISR_TIMER1
}

void receiveFromUartQueue(sensorQueueMessage* msg)
{
    BaseType_t pd;
    dbgOutputEvent(DEBUG16); //BEFORE_RECEIVE_QUEUE
    pd = xQueueReceive(uartQueue, (void *) msg, portMAX_DELAY);
    if(pd == pdFALSE) {
        stop();
    }
    dbgOutputEvent(DEBUG17); //AFTER_RECEIVE_QUEUE
}
