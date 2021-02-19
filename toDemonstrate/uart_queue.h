/*
 * uart_queue.h
 *
 *  Created on: Feb 17, 2021
 *      Author: Team 09
 */

#ifndef UART_QUEUE_H_
#define UART_QUEUE_H_

#include "debug.h"
#include "queue.h"
#include "sensor_queue.h"

void createUartQueue();
void sendToUartQueue(sensorQueueMessage* );
void receiveFromUartQueue(sensorQueueMessage* );

#endif /* UART_QUEUE_H_ */
