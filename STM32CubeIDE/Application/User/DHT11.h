/*
 * DHT.h
 *
 *  Created on: Jun 28, 2020
 *      Author: Controllerstech.com
 */

#ifndef DHT11_H_
#define DHT11_H_

typedef struct
{
	float Temperature;
	float Humidity;
}DHT_DataTypedef;

unsigned char DHT_Start_and_Check_Response ();
unsigned char DHT_Read_8bit ();

void DHT_GetData (DHT_DataTypedef *DHT_Data);

#endif /* DHT11_H_ */
