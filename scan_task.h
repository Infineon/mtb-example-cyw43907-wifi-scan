/*******************************************************************************
* File Name: scan_task.h
*
* Description: This file includes the macros, enumerations, and function
* prototypes used in scan_task.c
*
* Related Document: See README.md
*
*
*******************************************************************************
* $ Copyright 2021 Cypress Semiconductor $
*******************************************************************************/

/*******************************************************************************
 *  Include guard
 ******************************************************************************/
#ifndef SOURCE_SCAN_TASK_H_
#define SOURCE_SCAN_TASK_H_


/*******************************************************************************
 * Header file includes
 ******************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "cy_wcm.h"
#include <stdio.h>


/*******************************************************************************
 * Macros
 ******************************************************************************/

/* Provide the value of SSID which should be used to filter the scan results.*/
#define SCAN_FOR_SSID_VALUE                     "SSID"

/* Provide the value of the MAC address which should be used to filter the scan
 * results. For example, MAC Address: 12:34:56:78:9A:BC should be entered as
 * shown below.
 */
#define SCAN_FOR_MAC_ADDRESS                     0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC

/* Provide the value of the ISM band (2.4 GHz/ 5 GHz/ both) which should be used
 * to filter the scan results. The valid values are provided in the enumeration
 * cy_wcm_wifi_band_t in cy_wcm.h. 
 */
#define SCAN_FOR_BAND_VALUE                     CY_WCM_WIFI_BAND_ANY

/* Provide the value of the RSSI range that should be used to filter the scan
 * results. The valid values are provided in the enumeration
 * cy_wcm_scan_rssi_range_t in cy_wcm.h.
 */
#define SCAN_FOR_RSSI_VALUE                     CY_WCM_SCAN_RSSI_EXCELLENT

/* The delay in milliseconds between successive scans.*/
#define SCAN_DELAY_MS                           (3000u)

#define SCAN_TASK_STACK_SIZE                    (4096u)
#define SCAN_TASK_PRIORITY                      (3u)

#define MAX_SECURITY_STRING_LENGTH              (15)

#define SECURITY_OPEN                           "OPEN"
#define SECURITY_WEP_PSK                        "WEP-PSK"
#define SECURITY_WEP_SHARED                     "WEP-SHARED"
#define SECURITY_WEP_TKIP_PSK                   "WEP-TKIP-PSK"
#define SECURITY_WPA_TKIP_PSK                   "WPA-TKIP-PSK"
#define SECURITY_WPA_AES_PSK                    "WPA-AES-PSK"
#define SECURITY_WPA_MIXED_PSK                  "WPA-MIXED-PSK"
#define SECURITY_WPA2_AES_PSK                   "WPA2-AES-PSK"
#define SECURITY_WPA2_TKIP_PSK                  "WPA2-TKIP-PSK"
#define SECURITY_WPA2_MIXED_PSK                 "WPA2-MIXED-PSK"
#define SECURITY_WPA2_FBT_PSK                   "WPA2-FBT-PSK"
#define SECURITY_WPA3_SAE                       "WPA3-SAE"
#define SECURITY_WPA2_WPA_AES_PSK               "WPA2-WPA-AES-PSK"
#define SECURITY_WPA2_WPA_MIXED_PSK             "WPA2-WPA-MIXED-PSK"
#define SECURITY_WPA3_WPA2_PSK                  "WPA3-WPA2-PSK"
#define SECURITY_WPA_TKIP_ENT                   "WPA-TKIP-ENT"
#define SECURITY_WPA_AES_ENT                    "WPA-AES-ENT"
#define SECURITY_WPA_MIXED_ENT                  "WPA-MIXED-ENT"
#define SECURITY_WPA2_TKIP_ENT                  "WPA2-TKIP-ENT"
#define SECURITY_WPA2_AES_ENT                   "WPA2-AES-ENT"
#define SECURITY_WPA2_MIXED_ENT                 "WPA2-MIXED-ENT"
#define SECURITY_WPA2_FBT_ENT                   "WPA2-FBT-ENT"
#define SECURITY_IBSS_OPEN                      "IBSS-OPEN"
#define SECURITY_WPS_SECURE                     "WPS-SECURE"
#define SECURITY_UNKNOWN                        "UNKNOWN"

#define PRINT_SCAN_TEMPLATE()                   printf("\n----------------------------------------------------------------------------------------------------\n" \
                                                "  #                  SSID                  RSSI   Channel       MAC Address              Security\n" \
                                                "----------------------------------------------------------------------------------------------------\n");

#define APP_INFO( x )           do { printf("\nInfo: "); printf x;} while(0);
#define ERR_INFO( x )           do { printf("\nError: "); printf x;} while(0);


/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
void scan_task(void* arg);
void gpio_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event);
void error_handler(cy_rslt_t result, char *message);


/*******************************************************************************
 * Enumerations
 ******************************************************************************/
/* This enumeration contains the different types of scan filters available. They
 * are,
 * SCAN_FILTER_NONE: No scan filter.
 * SCAN_FILTER_SSID: The scan results are filtered by SSID.
 * SCAN_FILTER_MAC: The scan results are filtered by MAC address of the AP.
 * SCAN_FILTER_BAND: The scan results are filtered by the ISM band (2.4 or 5 GHz
 * or both) that the AP is occupying.
 * SCAN_FILTER_RSSI: The scan results are filtered by the RSSI strength.
 * SCAN_FILTER_INVALID: Invalid scan filter.
 */
enum scan_filter_mode
{
    SCAN_FILTER_NONE = 0,
    SCAN_FILTER_SSID,
    SCAN_FILTER_MAC,
    SCAN_FILTER_BAND,
    SCAN_FILTER_RSSI,
    SCAN_FILTER_INVALID
};


/*******************************************************************************
 * Global Variables
 ******************************************************************************/
/* Network connection task handle */
extern TaskHandle_t scan_task_handle;
extern bool is_retarget_io_initialized;
extern bool is_led_initialized;

#endif /* SOURCE_SCAN_TASK_H_ */


/* [] END OF FILE */
