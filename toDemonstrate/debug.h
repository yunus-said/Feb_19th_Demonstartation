/*
 * debug.h
 *
 *  Created on: Feb 10, 2021
 *      Author: 38285
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdint.h>
#include <stddef.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include "ti_drivers_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include <pthread.h>
#include <ti/drivers/Board.h>
#include <string.h>
#include <stdio.h>


#define DBG_HALT (0b00000000)
#define ENTER_TASK (0b00000001)
#define WHILE1 (0b00000010)
#define DBG_ERROR_LED_TIME (250000)

#define DEBUG1  1   //Entering timer70 task
#define DEBUG2  2   //Failed to initialized timer70
#define DEBUG3  3   //Failed to start timer70
#define DEBUG4  4   //Timer70 callback
#define DEBUG5  5   //Entering timer500 task
#define DEBUG6  6   //Failed to initialized timer500
#define DEBUG7  7   //Failed to start timer500
#define DEBUG50  50   //Timer500 callback
#define DEBUG9  9   //Entering UART task
#define DEBUG10  10 //UART_open() failed
#define DEBUG75  75 //UART_timer70_write
#define DEBUG100  100 //UART_timer500_write
#define DEBUG12  12
#define DEBUG13  13
#define DEBUG14  14
#define DEBUG15  15
#define DEBUG16  16
#define DEBUG17  17
#define DEBUG18  18
#define DEBUG19  19
#define DEBUG20  20
#define DEBUG21  21
#define DEBUG22  22
#define DEBUG23  23
#define DEBUG24  24
#define DEBUG25  25

void dbg_init();
void stop();
void dbgOutputEvent(unsigned int EveValue);

#endif /* DEBUG_H_ */
