/*
 * TimeDoctor_FreeRTOS.c
 */

#include <stdio.h>

#include "TimeDoctor.h"

#include "FreeRTOS.h"
#include "task.h"

extern char buffer[64000];
extern int buffer_used;
extern uint32_t lock;


#define PROLOG()	BaseType_t state = taskENTER_CRITICAL_FROM_ISR(); if(buffer_used < sizeof(buffer)-64) {
#define EPILOG()	} taskEXIT_CRITICAL_FROM_ISR(state);


/////////////////////// trace functions for task //////////////////////////////////////

void TimeDoctor_CREATE(  uint32_t uxTaskNumber, char* taskName )
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "CRE 0 %lu %lu\r\n", uxTaskNumber, TD_GET_TICK());
	buffer_used += sprintf( buffer+buffer_used, "NAM 0 %lu %s\r\n", uxTaskNumber, taskName );

	EPILOG();
}

void TimeDoctor_TASK_SWITCHED_IN( uint32_t uxTaskNumber )
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STA 0 %lu %lu\r\n", uxTaskNumber, TD_GET_TICK() );

	EPILOG();
}

void TimeDoctor_TASK_SWITCHED_OUT(uint32_t uxTaskNumber )
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STO 0 %lu %lu\r\n", uxTaskNumber, TD_GET_TICK() );

	EPILOG();
}

void TimeDoctor_TASK_DELETE( uint32_t uxTaskNumber)
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "DEL 0 %lu %lu\r\n", uxTaskNumber, TD_GET_TICK() );

	EPILOG();
}

void TimeDoctor_TASK_SUSPEND ( uint32_t uxTaskNumber)
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STO 0 %lu %lu\r\n", uxTaskNumber, TD_GET_TICK() );

	EPILOG();
}

void TimeDoctor_TASK_RESUME(  uint32_t uxTaskNumber)
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STA 0 %lu %lu\r\n", uxTaskNumber, TD_GET_TICK() );

	EPILOG();
}



/////////////////////// trace functions for queue //////////////////////////////////////

void TimeDoctor_QUEUE_CREATE( uint32_t *uxQueueNumber )
{
	static uint32_t nextQueueNumber = 0;

	PROLOG();

	*uxQueueNumber = nextQueueNumber++;
 	buffer_used += sprintf( buffer+buffer_used, "CRE 3 %lu %lu\r\n", *uxQueueNumber, TD_GET_TICK() );

	EPILOG();
}

void Timedoctor_QUEUE_REGISTRY_ADD( uint32_t uxQueueNumber, const char *pcQueueName )
{
	buffer_used += sprintf( buffer+buffer_used, "NAM 3 %lu %s\r\n", uxQueueNumber, pcQueueName );
}

void TimeDoctor_QUEUE_SEND(uint32_t uxQueueNumber, uint32_t uxMessagesWaiting)
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STA 3 %lu %lu %u\r\n", uxQueueNumber, TD_GET_TICK(), 1 );

	EPILOG();
}

void TimeDoctor_QUEUE_SEND_FROM_ISR( uint32_t uxQueueNumber, uint32_t uxMessagesWaiting)
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STA 3 %lu %lu %u\r\n", uxQueueNumber, TD_GET_TICK(), 1 );

	EPILOG();
}

void TimeDoctor_QUEUE_RECEIVE(uint32_t uxQueueNumber, uint32_t uxMessagesWaiting) /*The number of items currently in the queue. */
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STO 3 %lu %lu %u\r\n", uxQueueNumber, TD_GET_TICK(), 1 );

	EPILOG();
}

void TimeDoctor_QUEUE_RECEIVE_FROM_ISR( uint32_t uxQueueNumber, uint32_t uxMessagesWaiting )
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "STO 3 %lu %lu %u\r\n", uxQueueNumber, TD_GET_TICK(), 1 );

	EPILOG();
}

void TimeDoctor_QUEUE_DELETE( uint32_t uxQueueNumber )
{
	PROLOG();

	buffer_used += sprintf( buffer+buffer_used, "DEL 3 %lu %lu\r\n", uxQueueNumber, TD_GET_TICK());

	EPILOG();
}

