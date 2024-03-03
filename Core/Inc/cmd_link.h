#ifndef __CMD_LINK_H_
#define __CMD_LINK_H_
#include "main.h"


extern uint8_t rx_wifi_data[30];

extern uint8_t inputBuf[4];

extern uint8_t  inputCmd[2];
extern uint8_t wifiInputBuf[1];

void Decode_Function(void);


void sendData_Real_TempHum(uint8_t hum,uint8_t temp);


void SendWifiData_To_Cmd(uint8_t wdata);


void SendWifiData_To_PanelWindSpeed(uint8_t dat1);



void SendWifiData_To_PanelTime(uint8_t dat1);
void SendWifiData_To_PanelTemp(uint8_t dat1);
void SendWifiCmd_To_Order(uint8_t odata);
void SendData_Real_GMT(uint8_t hdata,uint8_t mdata,uint8_t sdata);
void SendWifiData_To_SetTime(uint8_t dat);


#endif 
