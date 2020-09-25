#include <CStMGen/cstmgen_main.h>

#include <CStMGen/cstmgen_process.h>
#include <CStMGen/cstmgen_json_machine_structure.h>
#include <CStMGen/cstmgen_params.h>

#include <iostream>

/* ------------------------------------------------------------------------- */

int cstmgen_main ( int argc, char** argv )
{
  cfg::cstmgen_params_t const parameters ( argc, argv );

  if ( not parameters.valid() )
  {
#ifndef NDEBUG
    std::cerr << parameters.usage() << std::endl;
    std::cerr << "Invalid parameters set occurred" << std::endl;
#endif
    return 1;
  }

  cfg::cstmgen_json_machine_structure_t const machine_structure ( parameters.get_json_machine_config_file() );

  if ( not machine_structure.valid() )
  {
#ifndef NDEBUG
    std::cerr << "Invalid machine structure occurred" << std::endl;
#endif
    return 1;
  }

  gen::cstmgen_process_t process ( parameters, machine_structure );

  return 0;
}
