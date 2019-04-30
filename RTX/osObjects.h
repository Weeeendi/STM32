/*----------------------------------------------------------------------------
 * osObjects.h: CMSIS-RTOS global object definitions for an application
 *----------------------------------------------------------------------------
 *
 * This header file defines global RTOS objects used throughout a project
 *
 * #define osObjectsPublic indicates that objects are defined; without that
 * definition the objects are defined as external symbols.
 *
 *--------------------------------------------------------------------------*/


#ifndef __osObjects
#define __osObjects

#if (!defined (osObjectsPublic))
#define osObjectsExternal           // define RTOS objects with extern attribute
#endif

#include "cmsis_os.h"               // CMSIS RTOS header file


// global 'thread' functions ---------------------------------------------------
/*
extern void sample_name (void const *argument);         // thread function

osThreadId tid_sample_name;                             // thread id
osThreadDef (sample_name, osPriorityNormal, 1, 0);      // thread object
*/



// global 'semaphores' ----------------------------------------------------------
/* 
Example:
osSemaphoreId sid_sample_name;                          // semaphore id
osSemaphoreDef (sample_name);                           // semaphore object
*/



// global 'memory pools' --------------------------------------------------------

// object data type
//Example
/*
osPoolId mpid_sample_name;                              // memory pool id
osPoolDef (Mypool, 16, long);          // memory pool object
*/


// global 'message queues' -------------------------------------------------------
/* 
Example:
typedef struct sample_name type_sample_name;            // object data type

osMessageQId mid_sample_name;                           // message queue id
osMessageQDef (sample_name, 16, type_sample_name);      // message queue object
*/


// global 'mail queues' ----------------------------------------------------------
/* 
Example:
typedef struct sample_name type_sample_name;            // object data type

osMailQId qid_sample_name;                              // mail queue id
osMailQDef (sample_name, 16, type_sample_name);         // mail queue object
*/

#endif  // __osObjects
