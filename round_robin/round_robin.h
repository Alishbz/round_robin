/****************************************************************************************
* ALI SAHBAZ
*
*
* ASZ Framework
*
* Date          : 15.07.2023
* By            : Ali Sahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#pragma once 
#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H
#ifdef __cplusplus
extern "C"
{
#endif


// !!!!!!!!1  rr -> round_robin   !!!!!!!!!!!!!
	 



// RoundRobin Private Developer Configs
#define RR_TASK_MAX_PRIO        TASK_PRIO_10
#define RR_TASK_MAX_TASK        20
#define RR_TASK_QUANTUM_TIME    3

typedef enum {
	TASK_SUCCESS,
	TASK_FAIL
}rr_task_fout_t;

/** high prio is high priorty of task  !! **/
typedef enum { 
	TASK_PRIO_EMPTY,
	TASK_PRIO_1 = 1,
	TASK_PRIO_2,
	TASK_PRIO_3,
	TASK_PRIO_4,
	TASK_PRIO_5,
	TASK_PRIO_6,
	TASK_PRIO_7,
	TASK_PRIO_8,
	TASK_PRIO_9,
	TASK_PRIO_10 
}rr_task_priority_t;

typedef void (*rr_task_fp_fp)( int quantum_time_test );

typedef struct {
	const char* name;
	rr_task_priority_t prio;
	rr_task_fp_fp task_fp; 

    int quantum_time;
}rr_task_obj_t;


typedef struct {

	// ALL PRÝVATE 

	rr_task_obj_t tasks[RR_TASK_MAX_TASK];

	unsigned short loaded_task_max_num;

	unsigned short task_render_index;
	  
	int current_quantum_time;
	  
}rr_task_manager_t;


rr_task_fout_t rr_task_create(rr_task_manager_t* me);

rr_task_fout_t rr_task_add( rr_task_manager_t* me ,
							const char* name,
							rr_task_priority_t prio,
							rr_task_fp_fp task_fp);


rr_task_fout_t rr_task_run(rr_task_manager_t* me);


#ifdef __cplusplus
}
#endif
#endif