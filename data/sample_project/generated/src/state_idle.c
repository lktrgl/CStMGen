#include <sens_comm/state_idle.h>

#include <sens_comm/state_sens_comm_enum.h>
#include <sens_comm/state_sens_comm_data_desc.h>

#include <CStM/state_default_handler.h>

#include <lggm/dbgprn.h>

#include <stddef.h>
#include <assert.h>

/* ------------------------------------------------------------------------- */

/* USER GLOBAL DATA AND CODE FOR 'IDLE' BEGIN */

/* put here global code for
   the ST_SENS_COMM_IDLE state scope */

/* USER GLOBAL DATA AND CODE  FOR 'IDLE' END */

/* ------------------------------------------------------------------------- */

static void s_enter_idle ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'IDLE' 'ENTER' BEGIN */

  /* put here some code to be executed once
     per each entering the ST_SENS_COMM_IDLE state */

  /* USER HANDLER FOR 'IDLE' 'ENTER' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_input_idle ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'IDLE' 'INPUT' BEGIN */

  /* put here some code to be executed every time
     before the 'run' handler */

  /* USER HANDLER FOR 'IDLE' 'INPUT' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_run_idle ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'IDLE' 'RUN' BEGIN */

  /* put here some code to be the contents of
     the ST_SENS_COMM_IDLE state;
     be aware that the code should not lock the execution
     inside this function  */

  /* USER HANDLER FOR 'IDLE' 'RUN' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_output_idle ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'IDLE' 'OUTPUT' BEGIN */

  /* put here some code to be executed every time
     after the 'run' handler */

  /* USER HANDLER FOR 'IDLE' 'OUTPUT' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_leave_idle ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'IDLE' 'LEAVE' BEGIN */

  /* put here some code to be executed once
     per each leaving the ST_SENS_COMM_IDLE state */

  /* USER HANDLER FOR 'IDLE' 'LEAVE' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static const state_handler_desc_t s_state_handler_idle =
{
  .enter = s_enter_idle,
  .input = s_input_idle,
  .run = s_run_idle,
  .output = s_output_idle,
  .leave = s_leave_idle
};

/* ========================================================================= */

/* ------------------------------------------------------------------------- */

static uint8_t s_transit_idle_to_read_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  LGGM_CALL_OUT_C ( 0 );

  /* USER TRANSIT CONDITION  IDLE TO READ_DEVICE BEGIN */

  /* return 1 (one) if the transition is required,
     return 0 (zero) otherwise */
  return 1;

  /* USER TRANSIT CONDITION  IDLE TO READ_DEVICE END */
}

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_idle_to_read_device =
{
  .is_transition = s_transit_idle_to_read_device,
  .next_state_node_index = ST_SENS_COMM_READ_DEVICE
};

/* ------------------------------------------------------------------------- */

static uint8_t s_transit_idle_to_write_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  LGGM_CALL_OUT_C ( 0 );

  /* USER TRANSIT CONDITION  IDLE TO WRITE_DEVICE BEGIN */

  /* return 1 (one) if the transition is required,
     return 0 (zero) otherwise */
  return 1;

  /* USER TRANSIT CONDITION  IDLE TO WRITE_DEVICE END */
}

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_idle_to_write_device =
{
  .is_transition = s_transit_idle_to_write_device,
  .next_state_node_index = ST_SENS_COMM_WRITE_DEVICE
};

/* ------------------------------------------------------------------------- */

static uint8_t s_transit_idle_to_failure ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  LGGM_CALL_OUT_C ( 0 );

  /* USER TRANSIT CONDITION  IDLE TO FAILURE BEGIN */

  /* return 1 (one) if the transition is required,
     return 0 (zero) otherwise */
  return 1;

  /* USER TRANSIT CONDITION  IDLE TO FAILURE END */
}

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_idle_to_failure =
{
  .is_transition = s_transit_idle_to_failure,
  .next_state_node_index = ST_SENS_COMM_FAILURE
};


/* ========================================================================= */

static const state_transition_desc_t* s_state_transitions_idle[] =
{
  &s_state_transition_idle_to_read_device,
  &s_state_transition_idle_to_write_device,
  &s_state_transition_idle_to_failure
};

/* ------------------------------------------------------------------------- */

const state_node_desc_t g_state_sens_comm_idle =
{
  .data = &g_state_data_sens_comm,
  .state_index = ST_SENS_COMM_IDLE,
  .state_handler = &s_state_handler_idle,
  .transitions = s_state_transitions_idle,
  .transitions_count = sizeof ( s_state_transitions_idle ) / sizeof ( s_state_transitions_idle[0] )
};
