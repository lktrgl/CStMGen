#include <CStMGen/cstmgen_params.h>

namespace cfg
{

cstmgen_params_t::cstmgen_params_t ( int argc, char** argv )
  : m_args ( argv, argv + argc )
{
  process_params();
}

void cstmgen_params_t::process_params()
{
}

} // namespace cfg
