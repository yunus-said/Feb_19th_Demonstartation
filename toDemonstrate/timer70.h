/*
 * timer70.h
 *
 *  Created on: Feb 13, 2021
 *      Author: Yunus
 */

#ifndef TIMER70_H_
#define TIMER70_H_

#include <stddef.h>
#include <stdbool.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Board Header file */
#include "ti_drivers_config.h"
#include "debug.h"

void timer70Thread();
void timerCallback70(Timer_Handle myHandle, int_fast16_t status);

#endif /* TIMER70_H_ */
