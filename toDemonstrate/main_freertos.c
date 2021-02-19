/*
 *  ======== main_freertos.c ========
 */

#include <stdint.h>

#ifdef __ICCARM__
#include <DLib_Threads.h>
#endif

/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/UART.h>

#include "debug.h"
#include "timer70.h"
#include "timer500.h"
#include "sensor_queue.h"
#include "uart_queue.h"

#include <ti/drivers/Board.h>

extern void *sensorThread(void *arg0);
extern void *uartThread(void *arg0);

/* Stack size in bytes */
#define THREADSTACKSIZE   1024

/*
 *  ======== main ========
 */
int main(void)
{
    pthread_t           sensor_thread;
    pthread_t           uart_thread;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 sensor_retc;
    int                 uart_retc;

    /* initialize the system locks */
#ifdef __ICCARM__
    __iar_Initlocks();
#endif

    /* Call driver init functions */
    Board_init();
    GPIO_init();
    UART_init();
    Timer_init();
    dbg_init();

    createSensorQueue();
    createUartQueue();
    timer70Thread();
    timer500Thread();

    /* Initialize the attributes structure with default values */
    pthread_attr_init(&attrs);

    /* Set priority, detach state, and stack size attributes */
    priParam.sched_priority = 1;

    // sensor_Thread Initialization
    sensor_retc = pthread_attr_setschedparam(&attrs, &priParam);
    sensor_retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    sensor_retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (sensor_retc != 0) {
        /* failed to set attributes */
        while (1) {}
    }

//    // uart_Thread Initialization
//    uart_retc = pthread_attr_setschedparam(&attrs, &priParam);
//    uart_retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
//    uart_retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
//    if (uart_retc != 0) {
//        /* failed to set attributes */
//        while (1) {}
//    }

    sensor_retc = pthread_create(&sensor_thread, &attrs, sensorThread, NULL);
    if (sensor_retc != 0) {
        /* sensor_thread pthread_create() failed */
        while (1) {}
    }

//    uart_retc = pthread_create(&uart_thread, &attrs, uartThread, NULL);
//    if (uart_retc != 0) {
//        /* uart_thread pthread_create() failed */
//        while (1) {}
//    }

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return (0);
}


void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
