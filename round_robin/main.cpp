/****************************************************************************************
* ALI SAHBAZ
*
*
* ASZ Framework
*
* Date          : 15.07.2023
* By            : Ali Sahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#include <stdio.h>

#include "round_robin.h"

#define USB_PRIO  TASK_PRIO_3
#define WIFI_PRIO TASK_PRIO_9
#define GPIO_PRIO TASK_PRIO_7
#define MEMS_PRIO TASK_PRIO_2
#define ADC_PRIO  TASK_PRIO_1

static void _usb_task(int test)
{
    printf("_usb_task prio: %d , quantum time: %d \n", USB_PRIO, test);
}

static void _wifi_task(int test)
{
    printf("_wifi_task prio: %d , quantum time: %d \n", WIFI_PRIO, test);
}

static void _gpio_task(int test)
{
    printf("_gpio_task prio: %d , quantum time: %d \n", GPIO_PRIO, test);
}

static void _mems_task(int test)
{
    printf("_mems_task prio: %d , quantum time: %d \n", MEMS_PRIO, test);
}

static void _adc_task(int test)
{
    printf("_adc_task prio: %d , quantum time: %d \n" , ADC_PRIO , test);
}

int main() {

    rr_task_manager_t OS;

    rr_task_create(&OS);

    rr_task_add(&OS,
                "usb_task",
                USB_PRIO,
                &_usb_task);
     
    rr_task_add(&OS,
                "wifi_task",
                WIFI_PRIO,
                &_wifi_task);
     
    rr_task_add(&OS,
                "gpio_task",
                GPIO_PRIO,
                &_gpio_task);
     
    rr_task_add(&OS,
                "mems_task",
                MEMS_PRIO,
                &_mems_task);
     
    rr_task_add(&OS,
                "adc_task",
                ADC_PRIO,
                &_adc_task);

    rr_task_run(&OS);

    return 0;
}