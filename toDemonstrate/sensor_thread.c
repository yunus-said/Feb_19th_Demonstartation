#include <sensor_state.h>
#include <stdint.h>
#include <stddef.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include "ti_drivers_config.h"
#include "debug.h"
#include "sensor_queue.h"
#include "uart_queue.h"


/*
 *  ======== sensorThread ========
 */
void *sensorThread(void *arg0)
{
    static sensorQueueMessage message;
    dbgOutputEvent(DEBUG9);
//    const char  echoPrompt[] = "UARTout";
//    static int temp1 = 0;
    UART_Handle uart;
    UART_Params uartParams;

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        dbgOutputEvent(DEBUG10);
        while (1);
    }

    while (1) {
        receiveFromSensorQueue(&message);

        if (message.type == TIMER500_MESSAGE) {
            message.elapsedTime += 1;
        }

        sendToUartQueue(&message);
        receiveFromUartQueue(&message);

        int received = 0;
        char str[8];

        if (message.type == TIMER70_MESSAGE) {
            received = message.sensorReading;
            sprintf(str, "Sen=%d", received);
            UART_write(uart, str, sizeof(str));
        } else if (message.type == TIMER500_MESSAGE) {
            received = message.elapsedTime;
            sprintf(str, "Ave=%d", received);
            UART_write(uart, str, sizeof(str));
            received = message.sensorReading;
            sprintf(str, "AvT=%d", received);
            UART_write(uart, str, sizeof(str));
        }

//        char str[4];
//        sprintf(str, "Sensor = %d mm", received);
//        UART_write(uart, str, sizeof(str));

//        UART_write(uart, echoPrompt, sizeof(echoPrompt));
//        temp1 += 1;
//        if (temp1 >= 200) {
//            temp1 = 0;
//        }

//        int state = 0;
//
//        if (received == 70) {
//            int timerMessage = 0;
//            state = updateSensorFSM(timerMessage, 5);
//        } else if (received == 500) {
//            int timerMessage = 1;
//            state = updateSensorFSM(timerMessage, 5);
//        }
//
//        sprintf(str, "%d", state);
//        UART_write(uart, str, sizeof(str));
    }
}

