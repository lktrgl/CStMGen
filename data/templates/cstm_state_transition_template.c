/* ------------------------------------------------------------------------- */

static uint8_t s_transit_%{state-name-from}%_%{state-name-to}% ( void* data )
{
  LGGM_CALL_IN_C(0);

  %{state-machine-name}%_data_desc_t* d = ( %{state-machine-name}%_data_desc_t* ) data;
  (void)d;

  LGGM_CALL_OUT_C(0);

  /* return 1 (one) if the transition is required, return 0 (zero) otherwise */
  return 1;
}


/* ------------------------------------------------------------------------- */

static const state_transition_desc_t s_state_transition_%{state-name-from}%_%{state-name-to}% =
{
  .is_transition = s_transit_%{state-name-from}%_%{state-name-to}%,
  .next_state_node_index = %{STATE-NAME-TO}%
};
