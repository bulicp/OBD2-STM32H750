/*
 * DHT22.h
 *
 *  Created on: Aug 20, 2024
 *      Author: patriciobulic
 */

#ifndef DHT22_H_
#define DHT22_H_


//#define DHT22_PORT GPIOE
//#define DHT22_PIN GPIO_PIN_3

#define DHT22_PORT GPIOI
#define DHT22_PIN GPIO_PIN_8

typedef struct
{
	float Temperature;
	float Humidity;
}DHT22_DataTypedef;


uint8_t DHT22_GetData (DHT22_DataTypedef *DHT22_Data);


#endif /* DHT22_H_ */
