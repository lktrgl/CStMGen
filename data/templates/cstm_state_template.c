#include <%{state-machine-name}%/state_%{state-name}%.h>

#include <%{state-machine-name}%/state_%{state-machine-name}%_enum,h>

#include <CStM/state_default_handler.h>

#include <lggm/dbgprn.h>

#include <stddef.h>
#include <assert.h>

/* ------------------------------------------------------------------------- */

static void s_enter_%{state-name}% ( void* data )
{
  LGGM_CALL_IN_C(0);

  %{state-machine-name}%_data_desc_t* d = ( %{state-machine-name}%_data_desc_t* ) data;
  (void)d;

  LGGM_CALL_OUT_C(0);
}

/* ------------------------------------------------------------------------- */

static void s_input_%{state-name}% ( void* data )
{
  LGGM_CALL_IN_C(0);

  %{state-machine-name}%_data_desc_t* d = ( %{state-machine-name}%_data_desc_t* ) data;
  (void)d;

  LGGM_CALL_OUT_C(0);
}

/* ------------------------------------------------------------------------- */

static void s_run_%{state-name}% ( void* data )
{
  LGGM_CALL_IN_C(0);

  %{state-machine-name}%_data_desc_t* d = ( %{state-machine-name}%_data_desc_t* ) data;
  (void)d;

  LGGM_CALL_OUT_C(0);
}

/* ------------------------------------------------------------------------- */

static void s_output_%{state-name}% ( void* data )
{
  LGGM_CALL_IN_C(0);

  %{state-machine-name}%_data_desc_t* d = ( %{state-machine-name}%_data_desc_t* ) data;
  (void)d;

  LGGM_CALL_OUT_C(0);
}

/* ------------------------------------------------------------------------- */

static void s_leave_%{state-name}% ( void* data )
{
  LGGM_CALL_IN_C(0);

  %{state-machine-name}%_data_desc_t* d = ( %{state-machine-name}%_data_desc_t* ) data;
  (void)d;

  LGGM_CALL_OUT_C(0);
}

/* ------------------------------------------------------------------------- */

static const state_handler_desc_t s_state_handler_%{state-name}% =
{
  .enter = s_enter_%{state-name}%,
  .input = s_input_%{state-name}%,
  .run = s_run_%{state-name}%,
  .output = s_output_%{state-name}%,
  .leave = s_leave_%{state-name}%
};

/* ------------------------------------------------------------------------- */

%{state-transitions-definition}%

/* ------------------------------------------------------------------------- */

static const state_transition_desc_t* s_state_transitions_%{state-name}%[] =
{
  %{state-transitions-list}%
};

/* ------------------------------------------------------------------------- */

const state_node_desc_t g_state_%{state-name}% =
{
  .data = &g_%{state-machine-name}%_data,
  .state_index = %{STATE-NAME}%,
  .state_handler = &s_state_handler_%{state-name}%,
  .transitions = s_state_transitions_%{state-name}%,
  .transitions_count = sizeof ( s_state_transitions_%{state-name}% ) / sizeof ( s_state_transitions_%{state-name}%[0] )
};
