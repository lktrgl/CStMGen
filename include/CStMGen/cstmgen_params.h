#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace cfg
{

class cstmgen_params_t final
{
  static constexpr std::string_view const m_param_produce_state_enum = "--state-enum";
  static constexpr std::string_view const m_param_produce_state_header = "--state-header";
  static constexpr std::string_view const m_param_produce_state_implementation = "--state-implementation";

public:
  cstmgen_params_t ( int argc, char** argv );

  cstmgen_params_t ( cstmgen_params_t const& ) = delete;
  cstmgen_params_t& operator= ( cstmgen_params_t const& ) = delete;
  cstmgen_params_t ( cstmgen_params_t&& ) = delete;
  cstmgen_params_t& operator= ( cstmgen_params_t&& ) = delete;

private:
  void process_params();

private:
  std::vector<std::string> const m_args; // ( argv, argv + argc );
};

} // namespace cfg
