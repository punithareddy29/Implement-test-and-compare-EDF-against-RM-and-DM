#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <projdefs.h>
#include <timers.h>
#include <list.h>
#include <croutine.h>
#include <portable.h>
#include <stack_macros.h>
#include <mpu_wrappers.h>
#include <FreeRTOSVariant.h>
#include <message_buffer.h>
#include <semphr.h>
#include <FreeRTOSConfig.h>
#include <stream_buffer.h>
#include <portmacro.h>
#include <event_groups.h>
#include <queue.h>
#include <Arduino.h>



#ifdef __cplusplus
extern "C" {
#endif


#define schedSCHEDULING_POLICY_RMS 1 		
#define schedSCHEDULING_POLICY_DMS 2
#define schedSCHEDULING_POLICY_EDF 3


#define schedSCHEDULING_POLICY schedSCHEDULING_POLICY_RMS     /* Rate-monotonic scheduling */
//#define schedSCHEDULING_POLICY schedSCHEDULING_POLICY_DMS   /* Deadline-monotonic scheduling */
//#define schedSCHEDULING_POLICY schedSCHEDULING_POLICY_EDF   /* EarliestDeadlineFirst scheduling */

/* Maximum number of periodic tasks that can be created. (Scheduler task is
 * not included) */
#define schedMAX_NUMBER_OF_PERIODIC_TASKS 5

/* Set this define to 1 to enable Timing-Error-Detection for detecting tasks
 * that have missed their deadlines. Tasks that have missed their deadlines
 * will be deleted, recreated and restarted during next period. */
#define schedUSE_TIMING_ERROR_DETECTION_DEADLINE 1

/* Set this define to 1 to enable Timing-Error-Detection for detecting tasks
 * that have exceeded their worst-case execution time. Tasks that have exceeded
 * their worst-case execution time will be preempted until next period. */
#define schedUSE_TIMING_ERROR_DETECTION_EXECUTION_TIME 1

/* Set this define to 1 to enable the scheduler task. This define must be set to 1
* when using following features:
* EDF scheduling policy, Timing-Error-Detection of execution time,
* Timing-Error-Detection of deadline, Polling Server. */
#define schedUSE_SCHEDULER_TASK 1


#if( schedUSE_SCHEDULER_TASK == 1 )
	/* Priority of the scheduler task. */
	#define schedSCHEDULER_PRIORITY ( configMAX_PRIORITIES - 1 )
	/* Stack size of the scheduler task. */
	#define schedSCHEDULER_TASK_STACK_SIZE 200 
	/* The period of the scheduler task in software ticks. */
	#define schedSCHEDULER_TASK_PERIOD pdMS_TO_TICKS( 100 )	
#endif /* schedUSE_SCHEDULER_TASK */

/* This function must be called before any other function call from scheduler.h. */
void vSchedulerInit( void );
void vApplicationTickHook( void );

void vSchedulerPeriodicTaskCreate( TaskFunction_t pvTaskCode, const char *pcName, UBaseType_t uxStackDepth, void *pvParameters, UBaseType_t uxPriority,
		TaskHandle_t *pxCreatedTask, TickType_t xPhaseTick, TickType_t xPeriodTick, TickType_t xMaxExecTimeTick, TickType_t xDeadlineTick );

/* Deletes a periodic task associated with the given task handle. */
void vSchedulerPeriodicTaskDelete( TaskHandle_t xTaskHandle );

/* Starts scheduling tasks. */
void vSchedulerStart( void );

#ifdef __cplusplus
}
#endif
#if( schedSCHEDULING_POLICY == schedSCHEDULING_POLICY_EDF)
	/* One of these defines must be set to 1, and the other one must be set to 0. */
	#define schedEDF_NAIVE 1 			/* Naive EDF implementation. */
	#define schedEDF_EFFICIENT 0 		/* Efficient EDF implementation. */
#endif


#define schedUSE_TIMING_ERROR_DETECTION_DEADLINE 1


#define schedUSE_TIMING_ERROR_DETECTION_EXECUTION_TIME 1

#if( schedUSE_POLLING_SERVER == 1 || schedSCHEDULING_POLICY == schedSCHEDULING_POLICY_EDF || schedUSE_TIMING_ERROR_DETECTION_DEADLINE == 1 || schedMAX_NUMBER_OF_SPORADIC_JOBS == 1)

	#define schedUSE_SCHEDULER_TASK 1
#else
	#define schedUSE_SCHEDULER_TASK 0
#endif



#endif /* SCHEDULER_H_ */
