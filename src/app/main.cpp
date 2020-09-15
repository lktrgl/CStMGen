#include <CStMGen/json_machine_structure.h>
#include <CStMGen/cstmgen_params.h>

#include <iostream>

int main ( int argc, char** argv )
{
  cfg::cstmgen_params_t args ( argc, argv );

  if ( not args.valid() )
  {
    std::cerr << "Invalid parameters set occurred" << std::endl;
    return 1;
  }

  cfg::json_machine_structure_t ms ( args.get_json_machine_config_file() );

  return 0;
}
