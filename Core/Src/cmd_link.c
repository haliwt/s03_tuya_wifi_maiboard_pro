#include "cmd_link.h"
#include "bsp.h"

#define MAX_BUFFER_SIZE  8

uint8_t  inputBuf[4];
uint8_t  inputCmd[2];
uint8_t  wifiInputBuf[1];
//unsigned char rx_value;

uint8_t rx_wifi_data[30];


static uint8_t transferSize;
static uint8_t outputBuf[MAX_BUFFER_SIZE];
volatile static uint8_t transOngoingFlag;


/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint8_t state=0;
    if(huart->Instance==USART1)//if(huart==&huart1) // Motor Board receive data (filter)
	{

		switch(state)
		{
		case 0:  //#0
			if(inputBuf[0] == 'T')  //hex :54 - "T" -touch
				state=1; //=1
		
			break;
		case 1: //#1
             if(inputBuf[0] == 'K')  //hex :4B - "K" -key
				state=2; //=1
			else
			   state =0;
			break;
            
        case 2:
             inputCmd[0]= inputBuf[0];
             state = 3;
        
        break;
        
        case 3:
            inputCmd[1]= inputBuf[0];
            run_t.decodeFlag =1;
            state = 0;
        
        break;
	
		default:
			state=0;
			run_t.decodeFlag =0;
		}
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_PEF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_FEF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_NEF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_OREF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_IDLEF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_TCF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_LBDF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_CTSF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_CMF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_WUF);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_TXFECF);
		HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
		
	}
    
  
 }
    
/********************************************
	*
	*Function Name:void Decode_Function(void)
    *Function: receive dsipay panel of order
    *Input Ref:NO
    *Return Ref:NO

*********************************************/ 
void Decode_Function(void)
{
   if(run_t.decodeFlag==1){
   
      run_t.decodeFlag =0;
      Decode_RunCmd();
      
     }
}

/********************************************************************************
	**
	*Function Name:void sendData_Real_TempHum(uint8_t hum,uint8_t temp)
	*Function :
	*Input Ref: humidity value and temperature value
	*Return Ref:NO
	*
*******************************************************************************/
void sendData_Real_TempHum(uint8_t hum,uint8_t temp)
{

	//crc=0x55;
	outputBuf[0]='M'; //4D
	outputBuf[1]='A'; //41
	outputBuf[2]='D'; //44	// 'D' data
	outputBuf[3]=hum; //	// 'R' rotator motor for select filter
	outputBuf[4]=temp; // // one command parameter
	
	//for(i=3;i<6;i++) crc ^= outputBuf[i];
	//outputBuf[i]=crc;
	transferSize=5;
	if(transferSize)
	{
		while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}



}
void SendWifiData_To_PanelTime(uint8_t dat1)
{
   
	//crc=0x55;
		outputBuf[0]='M'; //4D
		outputBuf[1]='A'; //41
		outputBuf[2]='T'; //44	// 'T' time
		outputBuf[3]=dat1; //	
		 
		
		//for(i=3;i<6;i++) crc ^= outputBuf[i];
		//outputBuf[i]=crc;
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}



}

void SendWifiData_To_PanelTemp(uint8_t dat1)
{
   
	//crc=0x55;
		outputBuf[0]='M'; //4D
		outputBuf[1]='A'; //41
		outputBuf[2]='P'; //44	// 'T' time
		outputBuf[3]=dat1; //	
	
		
		//for(i=3;i<6;i++) crc ^= outputBuf[i];
		//outputBuf[i]=crc;
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}



}

void SendWifiData_To_PanelWindSpeed(uint8_t dat1)
{
   
	//crc=0x55;
		outputBuf[0]='M'; //
		outputBuf[1]='A'; //
		outputBuf[2]='S'; // wind speed
		outputBuf[3]=dat1; //	
	
		
		//for(i=3;i<6;i++) crc ^= outputBuf[i];
		//outputBuf[i]=crc;
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}

}

void SendWifiData_To_Cmd(uint8_t wdata)
{
  
	//crc=0x55;
			outputBuf[0]='M'; //4D
			outputBuf[1]='A'; //41
			outputBuf[2]='W'; //44	// wifi ->infomation link wifi 
			outputBuf[3]=wdata; //
			//for(i=3;i<6;i++) crc ^= outputBuf[i];
			//outputBuf[i]=crc;
			transferSize=4;
			if(transferSize)
			{
				while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
				transOngoingFlag=1;
				HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
			}
}

void SendWifiData_To_SetTime(uint8_t dat)
{
   
	//crc=0x55;
		outputBuf[0]='M'; //
		outputBuf[1]='A'; //
		outputBuf[2]='T'; // wind speed
		outputBuf[3]=dat; //	
	
		
		//for(i=3;i<6;i++) crc ^= outputBuf[i];
		//outputBuf[i]=crc;
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}

}

/***************************************************************
 * 
 * Function: panel power on and special function
***************************************************************/
void SendWifiCmd_To_Order(uint8_t odata)
{
  
	//crc=0x55;
			outputBuf[0]='M'; //4D
			outputBuf[1]='A'; //41
			outputBuf[2]='C'; //44	// 'C' ->control 
			outputBuf[3]=odata; //	
		
			//for(i=3;i<6;i++) crc ^= outputBuf[i];
			//outputBuf[i]=crc;
			transferSize=4;
			if(transferSize)
			{
				while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
				transOngoingFlag=1;
				HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
			}



}

void SendData_Real_GMT(uint8_t hdata,uint8_t mdata,uint8_t sdata)
{
   

	outputBuf[0]='M'; //4D
	outputBuf[1]='A'; //41
	outputBuf[2]='B'; //44	// 'C' ->control 
	outputBuf[3]=hdata; //	
	outputBuf[4]=mdata; //
	outputBuf[5] =sdata;
	//for(i=3;i<6;i++) crc ^= outputBuf[i];
	//outputBuf[i]=crc;
	transferSize=6;
	if(transferSize)
	{
		while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}

}

/********************************************************************************
**
*Function Name:void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
*Function :UART callback function  for UART interrupt for transmit data
*Input Ref: structure UART_HandleTypeDef pointer
*Return Ref:NO
*
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		transOngoingFlag=0; //UART Transmit interrupt flag =0 ,RUN
	}

	if(huart== &huart2){



	}

}





