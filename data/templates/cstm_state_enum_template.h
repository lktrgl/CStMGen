#ifndef STATE_%{STATE-MACHINE-NAME}%_ENUM_H_INCLUDED
#define STATE_%{STATE-MACHINE-NAME}%_ENUM_H_INCLUDED

/* ------------------------------------------------------------------------- */

typedef enum state_%{state-machine-name}%_enum_tag
{
  %{STATE-NAMES-LIST}%

  ST_%{STATE-MACHINE-NAME}%_COUNT
} state_%{state-machine-name}%_enum_t;

/* ------------------------------------------------------------------------- */

#endif /* STATE_%{STATE-MACHINE-NAME}%_ENUM_H_INCLUDED */
