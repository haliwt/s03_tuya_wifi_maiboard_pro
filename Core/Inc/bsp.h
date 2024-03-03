#ifndef __BSP_H_
#define __BSP_H_
#include "main.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "interrupt_manager.h"
#include "bsp_beep.h"
#include "bsp_fan.h"

#include "ultrasonic.h"
#include "dht11.h"
#include "wifi.h"
#include "led.h"
#include "run.h"
#include "bsp_fan.h"
#include "cmd_link.h"
#include "wifi_fun.h"
#include "special_power.h"
#include "delay.h"
#include "bsp_decoder.h"
#include "gpio.h"
#include "tim.h"
#include "iwdg.h"
#include "usart.h"
#include "tuya_protocol.h"
#include "bsp_connect.h"




void bsp_Idle(void);




#endif 
