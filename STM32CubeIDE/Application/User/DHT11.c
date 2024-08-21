

/************** MAKE CHANGES HERE ********************/
#include "stm32h7xx_hal.h"
#include "DHT11.h"
#include "DWT.h"


//#define DHT_PORT GPIOE
//#define DHT_PIN GPIO_PIN_3

#define DHT_PORT GPIOI
#define DHT_PIN GPIO_PIN_8


static void Set_DHT_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull = GPIO_NOPULL;		// pullup is already on the DHT22 module
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static void Set_DHT_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;		// pullup is already on the DHT22 module
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}


unsigned char DHT_Start_and_Check_Response (){
	unsigned char bDHT_present = 0;

	// initialize cycle counter:
	DWT_Init();

	Set_DHT_Pin_Output (DHT_PORT, DHT_PIN);  // set the pin as output
	HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 0);   // pull the pin low

	//DWT_DelayUS (20000);   // wait > 18ms
	// wait > 18ms
	for(unsigned int i=0; i<200;i++){
		DWT_DelayUS (100);
	}

	HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 1);   // pull the pin high
	DWT_DelayUS (10);   // pull line high  and
	Set_DHT_Pin_Input(DHT_PORT, DHT_PIN);    // set the line as input

	// Wait for 40 us
	DWT_DelayUS (40);
	// Read the line, it must be low at this point
	if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))
	{
		// if the data line is LOW, wait for 80 us:
		DWT_DelayUS (80);
		// Read the line, it must be HIGH at this point
		if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))) bDHT_present = 1;
		else bDHT_present = 0;
	}
	return bDHT_present;
}



unsigned char DHT_Read_8bit () {
	unsigned char data = 0;

	// after the response, DHT will start the transmission.
	// Each bit’s transmission begins with low-voltage-level that last 50 us,
	// the following high-voltage-level signal’s length decides whether the bit is “1” or “0”.

	for (unsigned char j=0;j<8;j++)
	{
		while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))); // wait for the pin to go low
		while (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));   // wait for the pin to go high
		// If the length of H is around 26-28 us, the bit is “0”
		//If the length of H is around 70 us, the bit is “1”

		// wait for 40 us and check the line:
		DWT_DelayUS (40);   // wait for 40 us
		data = data << 1;
		if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))   // if the pin is HIGH
		{
			data |= 0x01;
		}
	}

	return data;
}


void DHT_GetData (DHT_DataTypedef *DHT_Data)
{
	unsigned char Rh_byteINT;
	unsigned char Rh_byteDEC;
	unsigned char Temp_byteINT;
	unsigned char Temp_byteDEC;
	unsigned char ChkSum;

	if(DHT_Start_and_Check_Response()){
		Rh_byteINT 		= DHT_Read_8bit();
		Rh_byteDEC 		= DHT_Read_8bit();
		Temp_byteINT 	= DHT_Read_8bit();
		Temp_byteDEC 	= DHT_Read_8bit();
		ChkSum 			= DHT_Read_8bit();
	}

	if (ChkSum == (unsigned char)(Rh_byteINT+Rh_byteDEC+Temp_byteINT+Temp_byteDEC)){
		DHT_Data->Temperature = Temp_byteINT + (Temp_byteDEC * 0.1);
		DHT_Data->Humidity = Rh_byteINT + (Rh_byteDEC * 0.1);
	}

}


