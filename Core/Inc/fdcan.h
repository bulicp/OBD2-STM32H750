/*
 * fdcan.h
 *
 *  Created on: Jan 4, 2023
 *      Author: patriciobulic
 */

#ifndef INC_FDCAN_H_
#define INC_FDCAN_H_


/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"


#define __OBD2_FILTERING__
#define FDCANx_CLK_ENABLE()         __HAL_RCC_FDCAN_CLK_ENABLE()
#define FDCANx_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOH_CLK_ENABLE()
#define FDCANx_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOH_CLK_ENABLE()

#define FDCANx_FORCE_RESET()   __HAL_RCC_FDCAN_FORCE_RESET()
#define FDCANx_RELEASE_RESET() __HAL_RCC_FDCAN_RELEASE_RESET()

/* Definition for FDCANx Pins */
#define FDCANx_TX_PIN       GPIO_PIN_13
#define FDCANx_TX_GPIO_PORT GPIOH
#define FDCANx_TX_AF        GPIO_AF9_FDCAN1
#define FDCANx_RX_PIN       GPIO_PIN_14
#define FDCANx_RX_GPIO_PORT GPIOH
#define FDCANx_RX_AF        GPIO_AF9_FDCAN1

/* Definition for FDCANx's NVIC IRQ and IRQ Handlers */
#define FDCANx_IRQn        FDCAN1_IT0_IRQn


typedef enum
{
  CAN_NORMAL_MODE             = 0x00U,  // Normal mode
  CAN_LOOPBACK_MODE,  					// Loopback mode
  CAN_SILENTLOOP_MODE,  				// Silent combined with loop-back
  CAN_SILENT_MODE   					// Silent mode
} CAN_InitModeTypeDef;

typedef struct {                                // object data type
  uint8_t length;
  uint8_t service;
  uint8_t pid;
  uint8_t OBDData[5];
} CAN_OBD2_MSGQUEUE_OBJ_t;



HAL_StatusTypeDef FDCAN1_Config(void);
HAL_StatusTypeDef CAN_SendMessage(FDCAN_HandleTypeDef* hfdcan, FDCAN_TxHeaderTypeDef* TxHeader, uint8_t* pTxData);


#endif /* INC_FDCAN_H_ */
