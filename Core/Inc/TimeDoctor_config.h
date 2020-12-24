#ifndef TIMEDOCTOR_CONFIG_H
#define TIMEDOCTOR_CONFIG_H


// size of buffer for TimeDoctor in internal RAM
#define TIMEDOCTOR_BUFFER_SIZE	64000

// set to 1 if the built-in cycle counter should be used (requires Cortex-M4 or better)
// set to 1 if the built-in cycle counter should not be used (e.g. on Cortex-M0)
#define TD_USE_CYCLECOUNTER 1

// set to a timer instance that should be used instead of cycle counter
//#define TD_USE_TIMER 1


//#define TD_USE_HAL_TICK


// set to 1 if FreeRTOS is available and should be traced by TimeDoctor
// set to 0 if FreeRTOS is not available or should not be traced by TimeDoctor
#define TD_USE_FREERTOS 1


//////////////////// pre-configured but user-changeable settings ////////////////

#include "main.h"

#if defined(TD_USE_CYCLECOUNTER) && (TD_USE_CYCLECOUNTER==1)

	#define TD_INIT_TICK() \
		do { \
			CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; \
			DWT->LAR = 0xC5ACCE55; \
			DWT->CYCCNT = 0; \
			DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; \
		} while(0)


	#define TD_GET_TICK() (DWT->CYCCNT)

	#define TD_GET_TICK_FREQ() (SystemCoreClock)

#endif // defined(TD_USE_CYCLECOUNTER) && (TD_USE_CYCLECOUNTER==1)


#endif
