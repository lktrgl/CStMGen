#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace cfg
{

class cstmgen_params_t final
{
  static constexpr std::string_view const m_param_json_machine_config_file = "--json-machine-config-file=";
  static constexpr std::string_view const m_param_produce_state_enum = "--state-enum";
  static constexpr std::string_view const m_param_produce_state_header = "--state-header";
  static constexpr std::string_view const m_param_produce_state_implementation = "--state-implementation";
  static constexpr std::string_view const m_param_header_folder = "--header-folder=";
  static constexpr std::string_view const m_param_implementation_folder = "--implementation-folder=";

public:
  cstmgen_params_t ( int argc, char** argv );

  cstmgen_params_t ( cstmgen_params_t const& ) = delete;
  cstmgen_params_t& operator= ( cstmgen_params_t const& ) = delete;
  cstmgen_params_t ( cstmgen_params_t&& ) = delete;
  cstmgen_params_t& operator= ( cstmgen_params_t&& ) = delete;

  std::string const& get_json_machine_config_file()
  {
    return m_json_machine_config_file;
  }
  bool get_produce_state_enum()
  {
    return m_produce_state_enum.length();
  }
  bool get_produce_state_header()
  {
    return m_produce_state_header.length();
  }
  bool get_produce_state_implementation()
  {
    return m_produce_state_implementation.length();
  }
  std::string const& get_header_folder()
  {
    return m_header_folder;
  }
  std::string const& get_implementation_folder()
  {
    return m_implementation_folder;
  }

  static std::string usage();

private:
  void process_params();

private:
  std::vector<std::string> const m_args; // ( argv, argv + argc );

  std::string m_json_machine_config_file;
  std::string m_produce_state_enum;
  std::string m_produce_state_header;
  std::string m_produce_state_implementation;
  std::string m_header_folder;
  std::string m_implementation_folder;
};

} // namespace cfg
