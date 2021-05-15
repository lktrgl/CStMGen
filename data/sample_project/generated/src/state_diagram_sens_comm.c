#include <sens_comm/state_diagram_sens_comm.h>

#include <sens_comm/state_sens_comm_enum.h>

#include <sens_comm/state_init.h>
#include <sens_comm/state_search_device.h>
#include <sens_comm/state_idle.h>
#include <sens_comm/state_read_device.h>
#include <sens_comm/state_write_device.h>
#include <sens_comm/state_failure.h>

/* ------------------------------------------------------------------------- */

static const state_node_desc_t* state_nodes_sens_comm[] =
{
  [ST_SENS_COMM_INIT] = &g_state_sens_comm_init,
  [ST_SENS_COMM_SEARCH_DEVICE] = &g_state_sens_comm_search_device,
  [ST_SENS_COMM_IDLE] = &g_state_sens_comm_idle,
  [ST_SENS_COMM_READ_DEVICE] = &g_state_sens_comm_read_device,
  [ST_SENS_COMM_WRITE_DEVICE] = &g_state_sens_comm_write_device,
  [ST_SENS_COMM_FAILURE] = &g_state_sens_comm_failure
};

/* ------------------------------------------------------------------------- */

state_diagram_desc_t g_state_diagram_sens_comm =
{
  .current_state = &g_state_sens_comm_init,
  .states = state_nodes_sens_comm,
  .states_count = sizeof ( state_nodes_sens_comm ) / sizeof ( state_nodes_sens_comm[0] )
};

