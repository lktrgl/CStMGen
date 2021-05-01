#pragma once

#include <string>
#include <vector>
#include <string_view>

/* ------------------------------------------------------------------------- */

namespace cfg
{

/* ------------------------------------------------------------------------- */

class cstmgen_params_t final
{
  static constexpr std::string_view const m_param_json_machine_config_file = "--json-machine-config-file=";
  static constexpr std::string_view const m_param_header_folder = "--header-folder=";
  static constexpr std::string_view const m_param_implementation_folder = "--implementation-folder=";
  static constexpr std::string_view const m_param_produce_all = "--produce-all";
  static constexpr std::string_view const m_param_produce_state_enum = "--state-enum";
  static constexpr std::string_view const m_param_produce_state_header = "--state-header";
  static constexpr std::string_view const m_param_produce_state_implementation = "--state-implementation";
  static constexpr std::string_view const m_param_produce_state_diagram_header = "--state-diagram-header";
  static constexpr std::string_view const m_param_produce_state_diagram_implementation = "--state-diagram-implementation";
  static constexpr std::string_view const m_param_produce_state_machine_data_header = "--state-machine-data-header";
  static constexpr std::string_view const m_param_produce_state_machine_data_implementation =
    "--state-machine-data-implementation";

public:
  cstmgen_params_t ( int argc, char** argv );

  cstmgen_params_t ( cstmgen_params_t const& ) = delete;
  cstmgen_params_t& operator= ( cstmgen_params_t const& ) = delete;
  cstmgen_params_t ( cstmgen_params_t&& ) = delete;
  cstmgen_params_t& operator= ( cstmgen_params_t&& ) = delete;

  std::string const& get_json_machine_config_file_name() const
  {
    return m_json_machine_config_file;
  }
  std::string const& get_header_folder_name() const
  {
    return m_header_folder;
  }
  std::string const& get_implementation_folder_name() const
  {
    return m_implementation_folder;
  }
  bool is_produce_state_enum() const
  {
    return m_produce_state_enum.length() || m_produce_all.length();
  }
  bool is_produce_state_header() const
  {
    return m_produce_state_header.length() || m_produce_all.length();
  }
  bool is_produce_state_implementation() const
  {
    return m_produce_state_implementation.length() || m_produce_all.length();
  }
  bool is_produce_state_diagram_header() const
  {
    return m_produce_state_diagram_header.length() || m_produce_all.length();
  }
  bool is_produce_state_diagram_implementation() const
  {
    return m_produce_state_diagram_implementation.length() || m_produce_all.length();
  }
  bool is_produce_state_machine_data_header() const
  {
    return m_produce_state_machine_data_header.length() || m_produce_all.length();
  }
  bool is_produce_state_machine_data_implementation() const
  {
    return m_produce_state_machine_data_implementation.length() || m_produce_all.length();
  }

  std::string const& get_error_message_text() const
  {
    return m_error_message_text;
  }

  bool is_valid() const;
  static std::string get_usage_text();

private:
  void process_params();

private:
  std::vector<std::string> const m_args; // ( argv, argv + argc );

  std::string m_json_machine_config_file;
  std::string m_header_folder;
  std::string m_implementation_folder;

  std::string m_produce_all;
  std::string m_produce_state_enum;
  std::string m_produce_state_header;
  std::string m_produce_state_implementation;
  std::string m_produce_state_diagram_header;
  std::string m_produce_state_diagram_implementation;
  std::string m_produce_state_machine_data_header;
  std::string m_produce_state_machine_data_implementation;

  std::string m_error_message_text;

  bool m_is_valid_config_file_name = false;
  bool m_is_valid_produce_state_enum = false;
  bool m_is_valid_produce_state_header = false;
  bool m_is_valid_produce_state_diagram_header = false;
  bool m_is_valid_produce_state_machine_data_header = false;
  bool m_is_valid_produce_state_implementation = false;
  bool m_is_valid_produce_state_diagram_implementation = false;
  bool m_is_valid_produce_state_machine_data_implementation = false;
};

/* ------------------------------------------------------------------------- */

} // namespace cfg
