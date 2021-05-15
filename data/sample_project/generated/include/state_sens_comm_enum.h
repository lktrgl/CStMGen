#ifndef STATE_SENS_COMM_ENUM_H_INCLUDED
#define STATE_SENS_COMM_ENUM_H_INCLUDED

/* ------------------------------------------------------------------------- */

typedef enum state_sens_comm_enum_tag
{
  ST_SENS_COMM_INIT = 0,
  ST_SENS_COMM_SEARCH_DEVICE = 1,
  ST_SENS_COMM_IDLE = 2,
  ST_SENS_COMM_READ_DEVICE = 3,
  ST_SENS_COMM_WRITE_DEVICE = 4,
  ST_SENS_COMM_FAILURE = 5,

  ST_SENS_COMM_COUNT
} state_sens_comm_enum_t;

/* ------------------------------------------------------------------------- */

#endif /* STATE_SENS_COMM_ENUM_H_INCLUDED */
