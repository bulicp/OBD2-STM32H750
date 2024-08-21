/*
 * fdcan.c
 *
 *  Created on: Jan 4, 2023
 *      Author: patriciobulic
 */


/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"
#include "cmsis_os.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FDCAN_HandleTypeDef   hfdcan;
FDCAN_RxHeaderTypeDef RxHeader;
//FDCAN_TxHeaderTypeDef TxHeader;


extern uint8_t        TxData[8];
uint8_t               RxData[8];
extern osMessageQueueId_t 	  mid_OBD2MsgQueue;
static CAN_OBD2_MSGQUEUE_OBJ_t new_can_data;
static osStatus_t     osstatus;

/* Private function prototypes -----------------------------------------------*/


HAL_StatusTypeDef FDCAN1_Config(void)
{
  FDCAN_FilterTypeDef sFilterConfig;

  /* Bit time configuration:
    fdcan_ker_ck               = 40 MHz
    Time_quantum (tq)          = 25 ns
    Synchronization_segment    = 1 tq
    Propagation_segment        = 23 tq
    Phase_segment_1            = 8 tq
    Phase_segment_2            = 8 tq
    Synchronization_Jump_width = 8 tq
    Bit_length                 = 80 tq = 1 ns
    Bit_rate                   = 500 kBit/s

    P.B. 4.1.2022
    t_FDCLK = 40 Mhz
    bit_time = 1/BIT_RATE = 1/500000  = 2000ns
    tq = NOMPRE * t_FDCLK = 1 * 25
    bit_time = tq x (1 + NTS1 + NTS2)
    NTS1 + NTS2 = (bit_time / tq) - 1
    NTS1 + NTS2 = (2000 / 25) - 1 = 80-1 = 79

    We can use calculator:
    https://www.kvaser.com/support/calculators/can-fd-bit-timing-calculator/
  */
  hfdcan.Instance = FDCAN1;
  hfdcan.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan.Init.AutoRetransmission = ENABLE;
  //hfdcan.Init.AutoRetransmission = DISABLE;
  hfdcan.Init.TransmitPause = DISABLE;
  //hfdcan.Init.ProtocolException = ENABLE;
  hfdcan.Init.ProtocolException = DISABLE;

  hfdcan.Init.NominalPrescaler = 1U; 		/* tq = NominalPrescaler x (1/fdcan_ker_ck) */
  hfdcan.Init.NominalSyncJumpWidth = 11U;
  hfdcan.Init.NominalTimeSeg1 = 68U; 		/* NominalTimeSeg1 = Propagation_segment + Phase_segment_1 */
  hfdcan.Init.NominalTimeSeg2 = 11U;

  hfdcan.Init.MessageRAMOffset = 0;
  hfdcan.Init.StdFiltersNbr = 1;
  hfdcan.Init.ExtFiltersNbr = 0;
  hfdcan.Init.RxFifo0ElmtsNbr = 4;						// Use RX FIFO of 4 elements
  hfdcan.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;  	// each element in FIFO stores 8 B of data
  hfdcan.Init.RxFifo1ElmtsNbr = 0;
  hfdcan.Init.RxBuffersNbr = 0;
  hfdcan.Init.TxEventsNbr = 0;
  hfdcan.Init.TxBuffersNbr = 0;
  hfdcan.Init.TxFifoQueueElmtsNbr = 1;
  hfdcan.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan.Init.TxElmtSize = FDCAN_DATA_BYTES_8;


  if (HAL_FDCAN_Init(&hfdcan) != HAL_OK)
  {
    /* Initialization Error */
    return HAL_ERROR;
  }

  /* Configure Rx filter */
  sFilterConfig.IdType = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex = 0;
  sFilterConfig.FilterType = FDCAN_FILTER_MASK;			// Classic filter: FilterID1 = filter, FilterID2 = mask
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 = 0x7E0;
  sFilterConfig.FilterID2 = 0x7F0;
  //sFilterConfig.FilterID2 = 0x7ef;
  sFilterConfig.RxBufferIndex = 0;

  if (HAL_FDCAN_ConfigFilter(&hfdcan, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
   return HAL_ERROR;
  }

  /* Start the FDCAN module */
  if (HAL_FDCAN_Start(&hfdcan) != HAL_OK)
  {
    /* Start Error */
   return HAL_ERROR;
  }

  if (HAL_FDCAN_ActivateNotification(&hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  {
    /* Notification Error */
    return HAL_ERROR;
  }

  return HAL_OK;
}


HAL_StatusTypeDef CAN_SendMessage(FDCAN_HandleTypeDef* hfdcan, FDCAN_TxHeaderTypeDef* TxHeader, uint8_t* pTxData){

	/* Start the Transmission process */
    if (HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, TxHeader, TxData) != HAL_OK)
    {
    	/* Transmission request Error */
    	return HAL_ERROR;
    }

	return HAL_OK;
}


/**
  * @brief  Rx FIFO 0 callback.
  * @param  hfdcan: pointer to an FDCAN_HandleTypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  RxFifo0ITs: indicates which Rx FIFO 0 interrupts are signalled.
  *                     This parameter can be any combination of @arg FDCAN_Rx_Fifo0_Interrupts.
  * @retval None
  */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
    /* Retreive Rx messages from RX FIFO0 */
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    {
      // Reception Error
      __NOP();
    }

    //(RxHeader.Identifier == 0x7E8) &&

    if ((RxHeader.IsFilterMatchingFrame == 0) && (RxHeader.RxFrameType == FDCAN_DATA_FRAME) && (RxHeader.IdType == FDCAN_STANDARD_ID) && (RxHeader.DataLength == FDCAN_DLC_BYTES_8))
    {
      new_can_data.length = RxData[0];
      new_can_data.service = RxData[1];
      new_can_data.pid = RxData[2];
      for (int i=0; i<5;i++) {
    	  new_can_data.OBDData[i] = RxData[i+3];
      }

      /* PAZI!!!!! The highest interrupt priority that can be used by any interrupt service
  	  	  routine that makes calls to interrupt safe FreeRTOS API functions is
  	  	  configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY.
  	  	  DO NOT CALL INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
  	  	  PRIORITY THAN THIS! (higher priorities are lower numeric values. */
      if (new_can_data.service == 0x41)
    	  osstatus = osMessageQueuePut(mid_OBD2MsgQueue, &new_can_data, 0U, 0U); // Timeout should be set to zero if called from ISR!!
      if ( osstatus != osOK){
    	  // Message queue error
    	  __NOP();
      }
    }

    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
      // Notification Error
    	__NOP();

    }
  }
}



void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* hfdcan)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  FDCANx_TX_GPIO_CLK_ENABLE();
  FDCANx_RX_GPIO_CLK_ENABLE();

  /* Select PLL1Q as source of FDCANx clock */
  RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
  RCC_PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);


  /* Enable FDCANx clock */
  FDCANx_CLK_ENABLE();

  /*#- Configure peripheral GPIO ##########################################*/
  /**FDCAN1 GPIO Configuration
    PH14     ------> FDCAN1_RX
    PH13     ------> FDCAN1_TX
    */
  /* FDCANx TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = FDCANx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = FDCANx_TX_AF;
  HAL_GPIO_Init(FDCANx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* FDCANx RX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = FDCANx_RX_PIN;
  GPIO_InitStruct.Alternate = FDCANx_RX_AF;
  HAL_GPIO_Init(FDCANx_RX_GPIO_PORT, &GPIO_InitStruct);

  /*##-3- Configure the NVIC #################################################*/
  /* NVIC for FDCANx */
  /* The highest interrupt priority that can be used by any interrupt service
  routine that makes calls to interrupt safe FreeRTOS API functions is
  configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY.
  DO NOT CALL INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
  PRIORITY THAN THIS! (higher priorities are lower numeric values. */
  HAL_NVIC_SetPriority(FDCANx_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+1U, 1);
  HAL_NVIC_EnableIRQ(FDCANx_IRQn);
}

/**
  * @brief  DeInitializes the FDCAN MSP.
  * @param  hfdcan: pointer to an FDCAN_HandleTypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @retval None
  */
void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* hfdcan)
{
  /*##-1- Reset peripherals ##################################################*/
  FDCANx_FORCE_RESET();
  FDCANx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* Configure FDCANx Tx as alternate function  */
  HAL_GPIO_DeInit(FDCANx_TX_GPIO_PORT, FDCANx_TX_PIN);

  /* Configure FDCANx Rx as alternate function  */
  HAL_GPIO_DeInit(FDCANx_RX_GPIO_PORT, FDCANx_RX_PIN);

  /*##-3- Disable the NVIC for FDCANx ########################################*/
  HAL_NVIC_DisableIRQ(FDCANx_IRQn);
}






