/*
 * DHT22.c
 *
 *  The RHT03 (also known as the DHT-22) is a low cost humidity and temperature sensor with a single wire digital interface.

Features:
	Humidity:
		Operating range: 0-100%RH; Accuracy: ±2% to ±5% RH; Resolution: 0.1% RH.
	Temperature:
		Operating range: -40~80Celsius, Accuracy: ±0.5°C; Resolution: 0.1°C.

	Power's voltage should be 3.3-6V DC. When power is supplied to sensor,
	don't send any instruction to the sensor within one second to pass unstable status.
	One capacitor valued 100nF can be added between VDD and GND for wave filtering.

MaxDetect 1-wire bus is used for communication between MCU and RHT03.
MaxDetect 1-Wire is a communication protocol developed by Maxim Integrated (now part of Analog Devices)
for their line of 1-Wire devices. The 1-Wire protocol is a low-speed, half-duplex, serial communication
protocol that uses a single data line and a ground reference for communication. The data transmission
consists of 40 bits: 16 bits for humidity, 16 bits for temperature, and 8 bits for a checksum to verify
data integrity. The timing of the high and low pulses determines whether a bit is a ‘0’ or a ‘1’.
 *
 *
 *  Created on: Aug 20, 2024
 *      Author: patriciobulic
 */

#include "stm32h7xx_hal.h"
#include "DHT22.h"
#include "DWT.h"


static inline void Set_DHT22_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull = GPIO_NOPULL;		// pullup is already on the DHT22 module
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static inline void Set_DHT22_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;		// pullup is already on the DHT22 module
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}


/*
 * DHT22_Start_and_Check_Response :
 *
 * Data-bus's free status is high voltage level. When communication between MCU and RHT03 begins,
 * MCU will pull low data-bus and this process must beyond at least 1~10ms to ensure RHT03 could
 * detect MCU's signal, then MCU will pulls up and wait 20-40us for RHT03's response.
 * When RHT03 detect the start signal, RHT03 will pull low the bus 80us as response signal,
 * then RHT03 pulls up 80us for preparation to send data.
 * Without start signal from MCU, RHT03 will not give response signal to MCU.
 *
 * Created on: Aug 20, 2024
 *    Author: patriciobulic
 */
static inline unsigned char DHT22_Start_and_Check_Response (){
	unsigned char bDHT22_present = 0;

	// initialize cycle counter (do this in main):
	//DWT_Init();

	Set_DHT22_Pin_Output (DHT22_PORT, DHT22_PIN);  	// set the pin as output
	HAL_GPIO_WritePin (DHT22_PORT, DHT22_PIN, 0);   // pull the pin low

	// wait > 1ms
	for(unsigned int i=0; i<20;i++){
		DWT_DelayUS (100);
	}

	HAL_GPIO_WritePin (DHT22_PORT, DHT22_PIN, 1);   // pull the pin high and
	Set_DHT22_Pin_Input(DHT22_PORT, DHT22_PIN);    	// set the line as input

	// Wait for 60 us
	DWT_DelayUS (60);
	// Read the line, it must be low at this point
	if (!(HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)))
	{
		// if the data line is LOW, wait for 80 us:
		DWT_DelayUS (80);
		// Read the line, it must be HIGH at this point
		if ((HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN))) bDHT22_present = -1;
		else bDHT22_present = 0;
	}
	return bDHT22_present;
}




/*
 * DHT22_Start_and_Check_Response :
 *
 * When RHT03 is sending data to MCU, every bit's transmission begin with low-voltage-level
 * When that last 50us, the following high-voltage-level signal's length decide the bit is "1" or "0".
 *
 * Created on: Aug 20, 2024
 *    Author: patriciobulic
 */

static inline uint64_t DHT22_Read_40bit () {
	uint64_t data = 0;

	// after the response, DHT will start the transmission.
	// Each bit’s transmission begins with low-voltage-level that last 50 us,
	// the following high-voltage-level signal’s length decides whether the bit is “1” or “0”.

	for (uint8_t j=0;j<40;j++)
	{
		while ((HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN))); 	// wait for the pin to go low
		while (!(HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)));   	// wait for the pin to go high
		// If the length of H is around 26-28 us, the bit is “0”
		// If the length of H is around 70 us, the bit is “1”

		// wait for 35 us and check the line:
		DWT_DelayUS (35);   // wait for 35 us
		data = data << 1;
		if ((HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)))   // if the pin is HIGH
		{
			data |= 0x01;
		}
	}

	return data;
}


/*
 * Checks if DHT22 is present and reads 40 bits.
 * Returns 0 if success, otherwise -1
 */

uint8_t DHT22_GetData (DHT22_DataTypedef *pDHT22_Data)
{
	uint8_t Rh_byteH;
	uint8_t Rh_byteL;
	uint8_t Temp_byteH;
	uint8_t Temp_byteL;
	uint8_t ChkSum;

	uint64_t dht22_data;
	uint8_t* pdata = (uint8_t*) &dht22_data;


	// check if DHT22 is present and read 40 bits
	if(DHT22_Start_and_Check_Response() != 0){
		return -1;   // DHT22 not present
	}

	dht22_data 	= DHT22_Read_40bit();

	Rh_byteH = pdata[4];
	Rh_byteL = pdata[3];
	Temp_byteH = pdata[2];
	Temp_byteL = pdata[1];
	ChkSum = pdata[0];


	/*
	 * If the data transmission is ok, check-sum should be:
	 *   Check sum=8 bit integral RH data+8 bit decimal RH data+8 bit integral T data+8 bit decimal T data
	 *   Example: MCU has received 40 bits data from RHT03 as
	 *   0000 0010 1000 1100 0000 0001 0101 1111 1110 1110
	 *   16 bits RH data 16 bits T data check sum
	 *   Check sum=0000 0010+1000 1100+0000 0001+0101 1111=1110 1110
	 *   RH= (0000 0010 1000 1100)/10=65.2%RH
	 *   T=(0000 0001 0101 1111)/10=35.1
	 */

	if (ChkSum == (unsigned char)(Rh_byteH+Rh_byteL+Temp_byteH+Temp_byteL)){

		if (Temp_byteH & 0x80) { // negative temperature !
			pDHT22_Data->Temperature = (((Temp_byteH & 0x7f) << 8) + Temp_byteL) * 0.1;
		}
		else {
			pDHT22_Data->Temperature = ((Temp_byteH << 8 ) + Temp_byteL) * 0.1 ;
		}

		pDHT22_Data->Humidity = ((Rh_byteH << 8 ) + Rh_byteL) * 0.1;

		return 0;
	}
	else return -1;
}


