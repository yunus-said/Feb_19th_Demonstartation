/*
 * debug.c
 *
 *  Created on: Feb 10, 2021
 *      Author: 38285
 */

#include "debug.h"

void dbg_init()
{
    /* Configure the GPIO pins */
    GPIO_setConfig(CONFIG_GPIO_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_2, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_3, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_4, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_5, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_6, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_7, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    /* Turn off user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
    GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);
}


void stop()
{
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
    vTaskSuspendAll();
    taskENTER_CRITICAL();
    taskDISABLE_INTERRUPTS();

    int loop = 0;
    while(1) {
        loop++;
        if (loop > DBG_ERROR_LED_TIME) {
            loop = 0;
            GPIO_toggle(CONFIG_GPIO_LED_0);
        }
    }
}


void dbgOutputEvent(unsigned int EveValue)
{
    if (EveValue <= 127)
    {
//        GPIO_write(CONFIG_GPIO_7, 1);

        if (EveValue & 1) {
            GPIO_write(CONFIG_GPIO_0, 1);
        } else {
            GPIO_write(CONFIG_GPIO_0, 0);
        }

        if (EveValue & 2) {
            GPIO_write(CONFIG_GPIO_1, 1);
        } else {
            GPIO_write(CONFIG_GPIO_1, 0);
        }

        if (EveValue & 4) {
            GPIO_write(CONFIG_GPIO_2, 1);
        } else {
            GPIO_write(CONFIG_GPIO_2, 0);
        }

        if (EveValue & 8) {
            GPIO_write(CONFIG_GPIO_3, 1);
        } else {
            GPIO_write(CONFIG_GPIO_3, 0);
        }

        if (EveValue & 16) {
            GPIO_write(CONFIG_GPIO_4, 1);
        } else {
            GPIO_write(CONFIG_GPIO_4, 0);
        }

        if (EveValue & 32) {
            GPIO_write(CONFIG_GPIO_5, 1);
        } else {
            GPIO_write(CONFIG_GPIO_5, 0);
        }

        if (EveValue & 64) {
            GPIO_write(CONFIG_GPIO_6, 1);
        } else {
            GPIO_write(CONFIG_GPIO_6, 0);
        }

//        GPIO_write(CONFIG_GPIO_7, 0);
    }
    else
    {
        stop();
    }
}
