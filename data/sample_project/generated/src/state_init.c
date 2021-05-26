#include <sens_comm/state_init.h>

#include <sens_comm/state_sens_comm_enum.h>
#include <sens_comm/state_sens_comm_data_desc.h>

#include <CStM/state_default_handler.h>

#include <lggm/dbgprn.h>

#include <stddef.h>
#include <assert.h>

/* ------------------------------------------------------------------------- */

/* USER GLOBAL DATA AND CODE FOR 'INIT' BEGIN */

/* put here global code for
   the ST_SENS_COMM_INIT state scope */

/*
* fake global data
*/


/* USER GLOBAL DATA AND CODE  FOR 'INIT' END */

/* ------------------------------------------------------------------------- */

static void s_enter_init ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'INIT' 'ENTER' BEGIN */

  /* put here some code to be executed once
     per each entering the ST_SENS_COMM_INIT state */

  /*
  * fake state enter code
  */


  /* USER HANDLER FOR 'INIT' 'ENTER' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_input_init ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'INIT' 'INPUT' BEGIN */

  /* put here some code to be executed every time
     before the 'run' handler */

  /*
  * fake state input code
  */


  /* USER HANDLER FOR 'INIT' 'INPUT' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_run_init ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'INIT' 'RUN' BEGIN */

  /* put here some code to be the contents of
     the ST_SENS_COMM_INIT state;
     be aware that the code should not lock the execution
     inside this function  */

  /*
  * fake state run code
  */


  /* USER HANDLER FOR 'INIT' 'RUN' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_output_init ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'INIT' 'OUTPUT' BEGIN */

  /* put here some code to be executed every time
     after the 'run' handler */

  /*
  * fake state output code
  */


  /* USER HANDLER FOR 'INIT' 'OUTPUT' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_leave_init ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'INIT' 'LEAVE' BEGIN */

  /* put here some code to be executed once
     per each leaving the ST_SENS_COMM_INIT state */

  /*
  * fake state leave code
  */


  /* USER HANDLER FOR 'INIT' 'LEAVE' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static const state_handler_desc_t s_state_handler_init =
{
  .enter = s_enter_init,
  .input = s_input_init,
  .run = s_run_init,
  .output = s_output_init,
  .leave = s_leave_init
};

/* ========================================================================= */

/* ------------------------------------------------------------------------- */

static uint8_t s_transit_init_to_search_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  LGGM_CALL_OUT_C ( 0 );

  /* USER TRANSIT CONDITION  INIT TO SEARCH_DEVICE BEGIN */

  /* return 1 (one) if the transition is required,
     return 0 (zero) otherwise */
  return 1;

  /* USER TRANSIT CONDITION  INIT TO SEARCH_DEVICE END */
}

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_init_to_search_device =
{
  .is_transition = s_transit_init_to_search_device,
  .next_state_node_index = ST_SENS_COMM_SEARCH_DEVICE
};

/* ------------------------------------------------------------------------- */

static uint8_t s_transit_init_to_failure ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  LGGM_CALL_OUT_C ( 0 );

  /* USER TRANSIT CONDITION  INIT TO FAILURE BEGIN */

  /* return 1 (one) if the transition is required,
     return 0 (zero) otherwise */
  return 1;

  /* USER TRANSIT CONDITION  INIT TO FAILURE END */
}

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_init_to_failure =
{
  .is_transition = s_transit_init_to_failure,
  .next_state_node_index = ST_SENS_COMM_FAILURE
};


/* ========================================================================= */

static const state_transition_desc_t* s_state_transitions_init[] =
{
  &s_state_transition_init_to_search_device,
  &s_state_transition_init_to_failure
};

/* ------------------------------------------------------------------------- */

const state_node_desc_t g_state_sens_comm_init =
{
  .data = &g_state_data_sens_comm,
  .state_index = ST_SENS_COMM_INIT,
  .state_handler = &s_state_handler_init,
  .transitions = s_state_transitions_init,
  .transitions_count = sizeof ( s_state_transitions_init ) / sizeof ( s_state_transitions_init[0] )
};
