/*******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for Wi-Fi Scan Example in ModusToolbox.
*
* Related Document: See README.md
*
*
*******************************************************************************
* $ Copyright 2021-2023 Cypress Semiconductor $
*******************************************************************************/

#include "cybsp.h"
#include "cyhal.h"
#include "cy_retarget_io.h"

/* FreeRTOS header file. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

/* Task header files. */
#include "scan_task.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define GPIO_INTERRUPT_PRIORITY             (7)


/*******************************************************************************
 * Global Variables
 ******************************************************************************/


/*******************************************************************************
 * Function definitions
 ******************************************************************************/


/*******************************************************************************
 * Function Name: main
 *******************************************************************************
 * Summary:
 *  System entrance point. This function sets up user tasks and then starts
 *  the RTOS scheduler.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  int
 *
 ******************************************************************************/
int main()
{
    cy_rslt_t result;

    cyhal_gpio_callback_data_t cb_data =
    {
        .callback     = gpio_interrupt_handler,
        .callback_arg = (void*)NULL
    };

    /* Initialize the board support package. */
    result = cybsp_init();
    error_handler(result, NULL);

    result = cyhal_gpio_init(CYBSP_USER_LED2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    error_handler(result, NULL);
    is_led_initialized = true;

    result = cyhal_gpio_init(CYBSP_SW1, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULLUP, CYBSP_BTN_OFF);
    error_handler(result, NULL);

    /* Configure GPIO interrupt. */
    cyhal_gpio_register_callback(CYBSP_SW1, &cb_data);
    cyhal_gpio_enable_event(CYBSP_SW1, CYHAL_GPIO_IRQ_FALL, GPIO_INTERRUPT_PRIORITY, true);

    /* Enable global interrupts. */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port. */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);
    error_handler(result, NULL);
    is_retarget_io_initialized = true;

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen. */
    printf("\x1b[2J\x1b[;H");

    printf("********************************************************\n"
           "CYW43907 - Wi-Fi Scan\n"
           "********************************************************\n");

    /* Create the tasks. */
    xTaskCreate(scan_task, "Scan task", SCAN_TASK_STACK_SIZE, NULL, SCAN_TASK_PRIORITY, &scan_task_handle);

    /* Start the FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* Should never get here. */
    CY_ASSERT(0);
}


/* [] END OF FILE */
