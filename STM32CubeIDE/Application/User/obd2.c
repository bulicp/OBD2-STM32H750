/*
 * obd2.c
 *
 *  Created on: Dec 30, 2022
 *      Author: patriciobulic
 */


/* Includes ------------------------------------------------------------------*/
#include "obd2.h"
#include "fdcan.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern FDCAN_HandleTypeDef 	hfdcan;
FDCAN_TxHeaderTypeDef   	TxHeader;
//CAN_RxHeaderTypeDef   RxHeader;
uint8_t               		TxData[8];
//uint8_t               RxData[8];
//uint32_t              TxMailbox;

/* Private function prototypes -----------------------------------------------*/

HAL_StatusTypeDef OBD2_SendQuery(uint8_t iOBD2_ServiceMode, OBD2_Mode1_PID_TypeDef pid){
	// Prepare Tx Header :
	TxHeader.Identifier = 0x7df;				// broadcast ODB2 request to all ECUs present
	TxHeader.IdType = FDCAN_STANDARD_ID;
	TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;	// OBD2 Requires #bytes = 8
	TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	TxHeader.MessageMarker = 0;


	/* Set the data to be transmitted */
	TxData[0] = 0x2U;			// OBD2 queries are always 2 bytes long
	//TxData[1] = iOBD2_ServiceMode;
	TxData[1] = 0x01U;
	TxData[2] = pid;
	TxData[3] = 0xcc;			// dummy, ISO 15765-2 suggests CCh to avoid bit stuffing
	TxData[4] = 0xcc;
	TxData[5] = 0xcc;
	TxData[6] = 0xcc;
	TxData[7] = 0xcc;

	/* Start the CAN Transmission process */
	//if (HAL_CAN_AddTxMessage(&CanHandle, &TxHeader, TxData, &TxMailbox)!= HAL_OK){
	if (CAN_SendMessage(&hfdcan, &TxHeader, TxData) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}



float OBD2DecodeEngineLoad(uint8_t *response)
{
	return ((response[0] * 100.0) / 255.0);
}

uint32_t OBD2DecodeEngineCoolantTemp(uint8_t *response)
{
	return (response[0] - 40);
}

uint32_t OBD2DecodeFuelPressure(uint8_t *response)
{
	return (response[0] * 3);
}

uint32_t OBD2DecodeIntakeAirTemp(uint8_t *response)
{
	return (response[0] - 40);
}

uint32_t OBD2DecodeEngineSpeed(uint8_t *response)
{
	return (((response[0]<<8) + response[1]) >> 2);
}

uint32_t OBD2DecodeRunTime(uint8_t *response)
{
	return (((response[0]<<8) + response[1]));
}

uint32_t OBD2DecodeVehicleSpeed(uint8_t *response)
{
	return response[0];
}

float OBD2DecodeMAFRate(uint8_t *response)
{
	return ((response[0]<<8) + response[1]) / 100.0;
}

float OBD2DecodeThrottlePosition(uint8_t *response)
{
	return (response[0] * 100.0) / 255.0;
}

float OBD2DecodeEngineFuelRate(uint8_t *response)
{
	return ((response[0]<<8) + response[1]) / 20.0;
}


uint32_t OBD2DecodeManifoldPressure(uint8_t *response)
{
	return response[0];
}

uint32_t OBD2DecodeOilTemp(uint8_t *response)
{
	return (response[0] - 40);
}

uint32_t OBD2DecodeOxySensorVoltage(uint8_t *response)
{
	return (response[0] * 5);  // mV
}

float OBD2DecodeOxySensorTrim(uint8_t *response)
{
	return (((100*response[1])<<7) - 100.0);  // %
}

void OBD2DecodeFuelType(uint8_t *response, uint8_t* out_string, uint32_t str_size)
{
	/*
	memset(out_string, "\0", str_size);
	switch (response[0]) {
	case 0:
		sprintf(out_string, "Not Avail");
		break;
	case 1:
		sprintf(out_string, "Gasoline");
		break;
	case 4:
		sprintf(out_string, "Diesel");
		break;
	case 5:
		sprintf(out_string, "LPG");
		break;
	default:
		sprintf(out_string, "NA");
		break;
	}
	*/
}

void OBD2DecodeFuelSystemStatus(uint8_t *response, uint8_t* out_string, uint32_t str_size)
{
	/*
	memset(out_string, "\0", str_size);
	switch (response[0]) {
	case 0:
		sprintf(out_string, "Motor Off");
		break;
	case 1:
		sprintf(out_string, "Open - low temp");
		break;
	case 2:
		sprintf(out_string, "Closed - OXY");
		break;
	case 4:
		sprintf(out_string, "Open - ENG. LOAD");
		break;
	case 8:
		sprintf(out_string, "SYS FAULT");
		break;
	default:
		sprintf(out_string, "Motor Off");
		break;
	}
	*/
}

uint32_t OBD2DecodeDistanceTraveled(uint8_t *response)
{
	return ((response[0]<<8) + response[1]);
}


void OBD2DecodeSupportedPIDs(uint8_t *response, OBD2_Supported_PIDs_TypeDef* supportedPIDS)
{
	supportedPIDS->SupportedPID_Engine_Load = (response[0] & 0x10U) ? 1 : 0;
	supportedPIDS->SupportedPID_Engine_Coolant_Temp = (response[0] & 0x10U) ? 1 : 0;

	supportedPIDS->SupportedPID_Fuel_Pressure = (response[1] & 0x40U) ? 1 : 0;
	supportedPIDS->SupportedPID_Engine_Speed = (response[1] & 0x10U) ? 1 : 0;
	supportedPIDS->SupportedPID_Vehicle_Speed = (response[1] & 0x08U) ? 1 : 0;
	supportedPIDS->SupportedPID_Intake_Air_Temp = (response[1] & 0x02U) ? 1 : 0;

	supportedPIDS->SupportedPID_Throttle_Position = (response[2] & 0x80U) ? 1 : 0;

}


uint32_t OBD2DecodeFuelRailPressure(uint8_t *response){
	return 10*((response[0]<<8) + response[1]);
}

uint32_t OBD2DecodeDistanceSinceCodeCleared(uint8_t *response){
	return ((response[0]<<8) + response[1]);
}

uint32_t OBD2DecodeAbsoluteBarometricPressure(uint8_t *response){
	return response[0]*10;
}


float OBD2DecodeCatalystTemperature(uint8_t *response){
	return ( ((response[0]<<8) + response[1])/10.0 -40.0 );
}

float OBD2DecodeControlModuleVoltage(uint8_t *response){
	return ( ((response[0]<<8) + response[1])/1000.0 );
}

uint32_t OBD2DecodeAmbientAirTemperature(uint8_t *response){
	return (response[0] - 40);
}

float OBD2DecodeAcceleratedPedalPosition(uint8_t *response){
	return ( (response[0]*100.0)/255.0 );
}

uint32_t OBD2DecodeFuelInjectionTiming(uint8_t *response){
	return ( (((response[0]<<8) + response[1])>>7)  - 210 );
}

float OBD2DecodeCommandedThrottlePosition(uint8_t *response){
	return ( (response[0]*100.0)/255.0 );
}

float OBD2DecodeCommandedEvaporatePurge(uint8_t *response){
	return ( (response[0]*100.0)/255.0 );
}

float OBD2DecodeCommandedEGR(uint8_t *response){
	return ( (response[0]*100.0)/255.0 );
}

uint32_t OBD2DecodeCommandedEGRError(uint8_t *response){
	return ( ((response[0]*100)>>7) - 100 );
}
















