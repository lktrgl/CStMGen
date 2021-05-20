#include <sens_comm/state_write_device.h>

#include <sens_comm/state_sens_comm_enum.h>
#include <sens_comm/state_sens_comm_data_desc.h>

#include <CStM/state_default_handler.h>

#include <lggm/dbgprn.h>

#include <stddef.h>
#include <assert.h>

/* ------------------------------------------------------------------------- */

/* USER GLOBAL DATA AND CODE FOR 'WRITE_DEVICE' BEGIN */

/* put here global code for
   the ST_SENS_COMM_WRITE_DEVICE state scope */

/* USER GLOBAL DATA AND CODE  FOR 'WRITE_DEVICE' END */

/* ------------------------------------------------------------------------- */

static void s_enter_write_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'WRITE_DEVICE' 'ENTER' BEGIN */

  /* put here some code to be executed once
     per each entering the ST_SENS_COMM_WRITE_DEVICE state */

  /* USER HANDLER FOR 'WRITE_DEVICE' 'ENTER' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_input_write_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'WRITE_DEVICE' 'INPUT' BEGIN */

  /* put here some code to be executed every time
     before the 'run' handler */

  /* USER HANDLER FOR 'WRITE_DEVICE' 'INPUT' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_run_write_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'WRITE_DEVICE' 'RUN' BEGIN */

  /* put here some code to be the contents of
     the ST_SENS_COMM_WRITE_DEVICE state;
     be aware that the code should not lock the execution
     inside this function  */

  /* USER HANDLER FOR 'WRITE_DEVICE' 'RUN' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_output_write_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'WRITE_DEVICE' 'OUTPUT' BEGIN */

  /* put here some code to be executed every time
     after the 'run' handler */

  /* USER HANDLER FOR 'WRITE_DEVICE' 'OUTPUT' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static void s_leave_write_device ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  /* USER HANDLER FOR 'WRITE_DEVICE' 'LEAVE' BEGIN */

  /* put here some code to be executed once
     per each leaving the ST_SENS_COMM_WRITE_DEVICE state */

  /* USER HANDLER FOR 'WRITE_DEVICE' 'LEAVE' END */

  LGGM_CALL_OUT_C ( 0 );
}

/* ------------------------------------------------------------------------- */

static const state_handler_desc_t s_state_handler_write_device =
{
  .enter = s_enter_write_device,
  .input = s_input_write_device,
  .run = s_run_write_device,
  .output = s_output_write_device,
  .leave = s_leave_write_device
};

/* ========================================================================= */

/* ------------------------------------------------------------------------- */

static uint8_t s_transit_write_device_to_idle ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  LGGM_CALL_OUT_C ( 0 );

  /* USER TRANSIT CONDITION  WRITE_DEVICE TO IDLE BEGIN */

  /* return 1 (one) if the transition is required,
     return 0 (zero) otherwise */
  return 1;

  /* USER TRANSIT CONDITION  WRITE_DEVICE TO IDLE END */
}

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_write_device_to_idle =
{
  .is_transition = s_transit_write_device_to_idle,
  .next_state_node_index = ST_SENS_COMM_IDLE
};

/* ------------------------------------------------------------------------- */

static uint8_t s_transit_write_device_to_failure ( void* data )
{
  LGGM_CALL_IN_C ( 0 );

  sens_comm_data_desc_t* d = ( sens_comm_data_desc_t* ) data;
  ( void ) d;

  LGGM_CALL_OUT_C ( 0 );

  /* USER TRANSIT CONDITION  WRITE_DEVICE TO FAILURE BEGIN */

  /* return 1 (one) if the transition is required,
     return 0 (zero) otherwise */
  return 1;

  /* USER TRANSIT CONDITION  WRITE_DEVICE TO FAILURE END */
}

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_write_device_to_failure =
{
  .is_transition = s_transit_write_device_to_failure,
  .next_state_node_index = ST_SENS_COMM_FAILURE
};


/* ========================================================================= */

static const state_transition_desc_t* s_state_transitions_write_device[] =
{
  &s_state_transition_write_device_to_idle,
  &s_state_transition_write_device_to_failure
};

/* ------------------------------------------------------------------------- */

const state_node_desc_t g_state_sens_comm_write_device =
{
  .data = &g_state_data_sens_comm,
  .state_index = ST_SENS_COMM_WRITE_DEVICE,
  .state_handler = &s_state_handler_write_device,
  .transitions = s_state_transitions_write_device,
  .transitions_count = sizeof ( s_state_transitions_write_device ) / sizeof ( s_state_transitions_write_device[0] )
};
