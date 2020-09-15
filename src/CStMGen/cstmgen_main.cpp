#include <CStMGen/cstmgen_main.h>

#include <CStMGen/cstmgen_process.h>
#include <CStMGen/json_machine_structure.h>
#include <CStMGen/cstmgen_params.h>

#include <iostream>

/* ------------------------------------------------------------------------- */

int cstmgen_main ( int argc, char** argv )
{
  cfg::cstmgen_params_t const parameters ( argc, argv );

  if ( not parameters.valid() )
  {
    std::cerr << "Invalid parameters set occurred" << std::endl;
    return 1;
  }

  cfg::json_machine_structure_t const machine_structure ( parameters.get_json_machine_config_file() );

  if ( not machine_structure.valid() )
  {
    std::cerr << "Invalid machine structure occurred" << std::endl;
    return 1;
  }

  gen::cstmgen_process_t process ( parameters, machine_structure );

  return 0;
}
