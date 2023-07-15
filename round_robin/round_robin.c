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
#include <stdio.h>
#include <windows.h>

#include "round_robin.h"

#define NULL_CHECK(xx)    if(xx == NULL ){return TASK_FAIL;}

#define DEBUG_PROCESS_WAIT_TIME   1000
 
#define DEBUG_WATCH(str)   printf((const char *)str);



static void _task_clear(rr_task_obj_t *me)
{
	me->quantum_time = 0;
	me->name = NULL;
	me->prio = TASK_PRIO_EMPTY;
	me->task_fp = NULL;
	return TASK_SUCCESS;
}
static void _task_adder(rr_task_obj_t* me , 
			const char* name,
			rr_task_priority_t prio,
			rr_task_fp_fp task_fp  )
{
	me->name = name;
	me->prio = prio;
	me->task_fp = task_fp;
	return TASK_SUCCESS;
}

rr_task_fout_t rr_task_create(rr_task_manager_t* me)
{
	NULL_CHECK(me);

	unsigned short index = 0;
	do {
		_task_clear(&me->tasks[index]);
		index++;
	} while (index < RR_TASK_MAX_TASK);
	 
	me->loaded_task_max_num = 0;
	me->current_quantum_time = 0;
	me->task_render_index = 0;

	return TASK_SUCCESS;
}

rr_task_fout_t rr_task_add( rr_task_manager_t* me,
							const char* name,
							rr_task_priority_t prio,
							rr_task_fp_fp task_fp)
{
	NULL_CHECK(me);
	NULL_CHECK(name);
	NULL_CHECK(task_fp);
	 
	if (me->loaded_task_max_num < RR_TASK_MAX_TASK)
	{
		_task_adder(&me->tasks[me->loaded_task_max_num],
					name,
					prio,
					task_fp);
		me->loaded_task_max_num++;
	}
	 
	return TASK_SUCCESS;
}
 

/** return 1 -> error */
static char _round_robin_tasks_init(rr_task_manager_t* me)
{
	unsigned short index = 0;

	if (!me->loaded_task_max_num) {
		return 0;
	}
	

	do {
	
		// TODO add prio == 0 error

		me->tasks[index].quantum_time = (int)me->tasks[index].prio;

		index++;

	} while (index < me->loaded_task_max_num);

	return 1;
}

static char _check_all_tasks_times(rr_task_manager_t* me)
{
	unsigned short index = 0;
 
	do {
		 
		if (me->tasks[index].quantum_time > 0) {
			return 0;
		}

		index++;

	} while (index < me->loaded_task_max_num);

	return 1;
}


static char _round_robin_algorithm(rr_task_obj_t* me, int current_time   )
{
	char _q_process_step = 1;

	if (me->prio || me->quantum_time > 0 ) {
		 
		if (me->quantum_time+1 < RR_TASK_QUANTUM_TIME) {
			_q_process_step = 0;
		}

		//** task caller **
		me->task_fp(current_time);

		me->quantum_time--;

	}
	else {

		DEBUG_WATCH(" RR: prio or quantum 0 ! \n");
		 
		/** goto next task**/
		return 1;
	}
	 
	
	if (current_time) {
		if (_q_process_step == 0) {

			if (me->quantum_time < 1 || 
				(current_time % (me->quantum_time % RR_TASK_QUANTUM_TIME)) == 0)
			{ 
				/** goto next task**/
				return 1;
			}
		}
		else if ((current_time % RR_TASK_QUANTUM_TIME) == 0)
		{ 
			/** goto next task**/
			return 1;
		}
	}
	 
	return 0;
}


rr_task_fout_t rr_task_run(rr_task_manager_t* me)
{
	NULL_CHECK(me);

    char _is_loop_forewer = _round_robin_tasks_init(me);
  
	DEBUG_WATCH(" RR: loop start ! \n");

	while (_is_loop_forewer) {
	  
		if (_round_robin_algorithm(&me->tasks[me->task_render_index], me->current_quantum_time)) {

			me->task_render_index++;

			me->current_quantum_time = 0;

			if (me->task_render_index >= me->loaded_task_max_num ) {

				if (_check_all_tasks_times(me)) {

					DEBUG_WATCH(" RR: end ! \n");

					_round_robin_tasks_init(me);
				}
				 
				me->task_render_index = 0;
			} 

			Sleep(DEBUG_PROCESS_WAIT_TIME);
		}

		me->current_quantum_time++;
	}

	return TASK_SUCCESS;
}