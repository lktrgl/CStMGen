#include <sens_comm/state_failure.h>

#include <sens_comm/state_sens_comm_enum.h>
#include <sens_comm/state_sens_comm_data_desc.h>

#include <CStM/state_default_handler.h>

#include <lggm/dbgprn.h>

#include <stddef.h>
#include <assert.h>

/* ------------------------------------------------------------------------- */

/* USER GLOBAL FAILURE ENTER BEGIN */

/* put here global code for
   the ST_SENS_COMM_FAILURE state scope */

/* USER GLOBAL FAILURE ENTER END */

/* ------------------------------------------------------------------------- */

static void s_enter_failure ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FAILURE ENTER BEGIN */

  /* put here some code to be executed once
     per each entering the ST_SENS_COMM_FAILURE state */

  /* USER HANDLER FAILURE ENTER END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_input_failure ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FAILURE INPUT BEGIN */

  /* put here some code to be executed every time
     before the 'run' handler */

  /* USER HANDLER FAILURE INPUT END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_run_failure ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FAILURE RUN BEGIN */

  /* put here some code to be the contents of
     the ST_SENS_COMM_FAILURE state;
     be aware that the code should not lock the execution
     inside this function  */

  /* USER HANDLER FAILURE RUN END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_output_failure ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FAILURE OUTPUT BEGIN */

  /* put here some code to be executed every time
     after the 'run' handler */

  /* USER HANDLER FAILURE OUTPUT END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_leave_failure ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FAILURE LEAVE BEGIN */

  /* put here some code to be executed once
     per each leaving the ST_SENS_COMM_FAILURE state */

  /* USER HANDLER FAILURE LEAVE END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static const state_handler_desc_t s_state_handler_failure =
{
  .enter = s_enter_failure,
  .input = s_input_failure,
  .run = s_run_failure,
  .output = s_output_failure,
  .leave = s_leave_failure
};

/* ========================================================================= */

/* ------------------------------------------------------------------------- */

static uint8_t s_transit_failure_to_search_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  LGGM_CALL_OUT_C ( 0 );

  /* USER TRANSIT CONDITION  FAILURE TO SEARCH_DEVICE BEGIN */

  /* return 1 (one) if the transition is required,
     return 0 (zero) otherwise */
  return 1;

  /* USER TRANSIT CONDITION  FAILURE TO SEARCH_DEVICE END */
}

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_failure_to_search_device =
{
  .is_transition = s_transit_failure_to_search_device,
  .next_state_node_index = ST_SENS_COMM_SEARCH_DEVICE
};


/* ========================================================================= */

static const state_transition_desc_t* s_state_transitions_failure[] =
{
  &s_state_transition_failure_to_search_device
};

/* ------------------------------------------------------------------------- */

const state_node_desc_t g_state_sens_comm_failure =
{
  .data = &g_state_data_sens_comm,
  .state_index = ST_SENS_COMM_FAILURE,
  .state_handler = &s_state_handler_failure,
  .transitions = s_state_transitions_failure,
  .transitions_count = sizeof ( s_state_transitions_failure ) / sizeof ( s_state_transitions_failure[0] )
};
