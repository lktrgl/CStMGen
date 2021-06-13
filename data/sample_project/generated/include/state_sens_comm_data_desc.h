#ifndef STATE_SENS_COMM_DATA_DESC_H_INCLUDED
#define STATE_SENS_COMM_DATA_DESC_H_INCLUDED

#include <stdint.h>

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------- */

typedef struct sens_comm_data_desc_tag
{
  /* USER DATA FIELDS DECL BEGIN */

  /* put here all the data fields to be used
     by SENS_COMM state machine;
     below is a sample field */

  uint8_t dummy_field;


  /* USER DATA FIELDS DECL END */
} sens_comm_data_desc_t;

/* ------------------------------------------------------------------------- */

extern sens_comm_data_desc_t g_state_data_sens_comm;

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
} /* extern "C" */
#endif

/* ------------------------------------------------------------------------- */

#endif /* STATE_SENS_COMM_DATA_DESC_H_INCLUDED */
