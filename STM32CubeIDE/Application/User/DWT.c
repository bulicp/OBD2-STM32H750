/*
 * DWT.c
 *
 * The DWT (Data Watchpoint and Trace) timer is a feature of the Cortex-M cores used in
 * STM32 microcontrollers. The DWT unit is part of the ARM Cortex-M Debug and Trace
 * architecture and provides various debugging and performance monitoring capabilities.
 * The DWT includes a cycle counter that can be used to measure the number of clock
 * cycles elapsed between two points in code. It counts machine cycles, so is the
 * highest resolution counter typically available. This is particularly useful for profiling
 * code to determine execution time.
 *
 *  Created on: Jan 18, 2024
 *      Author: patriciobulic
 */

#include "stm32h7xx_hal.h"
#include "DWT.h"

/*
 * Initialize Data Watchpoint and Trace Unit
 * Patricio Bulic, UL FRI
 */

char DWT_Init(){

	/* Enable trace and debug block in Debug Exception and Monitor Control Register */
	CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;
	// Unlock access to DWT (ITM, etc.) registers:
	DWT->LAR = 0xC5ACCE55;

	/* Reset the clock cycle counter value */
	DWT->CYCCNT = 0;

	/* Enable  clock cycle counter */
	DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

	// Execute 3 NOP instructiio0n just to wait for a few cycles:
	__NOP();
	__NOP();
	__NOP();

	/* Check if clock cycle counter has started */
	if(DWT->CYCCNT)
	{
		return 0; /* clock cycle counter started */
	}
	else
	{
		return 1; /* clock cycle counter not started */
	}
}


/*
 * DWT delay in microseconds
 * Patricio Bulic, UL FRI
 */

void DWT_DelayUS(unsigned int microseconds)
{
  // read cycle counter:
  DWT->CYCCNT = 0;
  unsigned int clk_cycle_start = DWT->CYCCNT;

  // get CPU cycles per us:
  volatile unsigned int cpu_freq = HAL_RCC_GetSysClockFreq();
  unsigned int cycles_per_us = (cpu_freq / 1000000);

  unsigned int delay = clk_cycle_start + microseconds*cycles_per_us;
  //microseconds = microseconds*cycles_per_us;


  if ((clk_cycle_start + delay) < clk_cycle_start) { // overflow!!!

  }
  else{
	  while ((DWT->CYCCNT) < delay);
  }

}









