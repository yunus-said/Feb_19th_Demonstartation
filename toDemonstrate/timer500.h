/*
 * timer500.h
 *
 *  Created on: Feb 13, 2021
 *      Author: Yunus
 */

#ifndef TIMER500_H_
#define TIMER500_H_

#include <stddef.h>
#include <stdbool.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Board Header file */
#include "ti_drivers_config.h"
#include "debug.h"

void timer500Thread();
void timerCallback500(Timer_Handle myHandle, int_fast16_t status);

#endif /* TIMER500_H_ */
