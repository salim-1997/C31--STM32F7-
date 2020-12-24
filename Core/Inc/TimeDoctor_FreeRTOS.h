/*
 * TimeDoctor_FreeRTOS.h
 *
 * in FreeROSConfig.h, the following lines must be added
 *
 * #include "TimeDoctor.h"
 *
 * and
 *
 * #define configUSE_TRACE_FACILITY   1
 *
 * must be set.
 *
 */

#ifndef TIMEDOCTOR_FREERTOS_H_
#define TIMEDOCTOR_FREERTOS_H_

////////////////////// TimeDoctor FreeRTOS tracing backend /////////////////////

void TimeDoctor_CREATE(  uint32_t uxTaskNumber, char* taskName );
void TimeDoctor_TASK_SWITCHED_IN( uint32_t uxTaskNumber );
void TimeDoctor_TASK_SWITCHED_OUT( uint32_t uxTaskNumber );
void TimeDoctor_TASK_DELETE( uint32_t uxTaskNumber	);
void TimeDoctor_TASK_SUSPEND( uint32_t uxTaskNumber );
void TimeDoctor_TASK_RESUME( uint32_t uxTaskNumber );

void TimeDoctor_QUEUE_CREATE( uint32_t *uxQueueNumber );
void Timedoctor_QUEUE_REGISTRY_ADD( uint32_t uxQueueNumber, const char *pcQueueName );
void TimeDoctor_QUEUE_SEND( uint32_t uxQueueNumber, uint32_t uxMessagesWaiting );
void TimeDoctor_QUEUE_RECEIVE( uint32_t uxQueueNumber, uint32_t uxMessagesWaiting );
void TimeDoctor_QUEUE_DELETE( uint32_t uxQueueNumber );
void TimeDoctor_QUEUE_SEND_FROM_ISR( uint32_t uxQueueNumber, uint32_t uxMessagesWaiting );
void TimeDoctor_QUEUE_RECEIVE_FROM_ISR( uint32_t uxQueueNumber, uint32_t uxMessagesWaiting );

/////////////////////////// FreeRTOS macros //////////////////////////

// these defines map TimeDoctor backend to FreeRTOS trace facility names

#define traceTASK_CREATE(pxNewTCB) 				TimeDoctor_CREATE( pxNewTCB->uxTCBNumber, pxNewTCB->pcTaskName );
#define traceTASK_SWITCHED_IN() 				TimeDoctor_TASK_SWITCHED_IN( pxCurrentTCB->uxTCBNumber );
#define traceTASK_SWITCHED_OUT() 				TimeDoctor_TASK_SWITCHED_OUT( pxCurrentTCB->uxTCBNumber );
#define traceTASK_DELETE( pxTaskToDelete ) 		TimeDoctor_TASK_DELETE( pxTaskToDelete->uxTCBNumber );
#define traceTASK_SUSPEND( pxTaskToSuspend )	TimeDoctor_TASK_SUSPEND( pxTaskToSuspend->uxTCBNumber);
#define traceTASK_RESUME( pxTaskToResume ) 		TimeDoctor_TASK_RESUME( pxTaskToResume->uxTCBNumber );


#define traceQUEUE_CREATE(pxNewQueue) 					TimeDoctor_QUEUE_CREATE(&pxNewQueue->uxQueueNumber);
#define traceQUEUE_REGISTRY_ADD(xQueue, pcQueueName)	Timedoctor_QUEUE_REGISTRY_ADD(xQueue->uxQueueNumber, pcQueueName);
#define traceQUEUE_SEND(pxQueue) 						TimeDoctor_QUEUE_SEND(pxQueue->uxQueueNumber, pxQueue->uxMessagesWaiting);
#define traceQUEUE_RECEIVE(pxQueue) 					TimeDoctor_QUEUE_RECEIVE(pxQueue->uxQueueNumber, pxQueue->uxMessagesWaiting);
#define traceQUEUE_DELETE( pxQueue ) 					TimeDoctor_QUEUE_DELETE( pxQueue->uxQueueNumber );
#define traceQUEUE_SEND_FROM_ISR( pxQueue )  			TimeDoctor_QUEUE_SEND_FROM_ISR( pxQueue->uxQueueNumber, pxQueue->uxMessagesWaiting);
#define traceQUEUE_RECEIVE_FROM_ISR(pxQueue) 			TimeDoctor_QUEUE_RECEIVE_FROM_ISR(pxQueue->uxQueueNumber, pxQueue->uxMessagesWaiting);

#endif /* TIMEDOCTOR_FREERTOS_H_ */
