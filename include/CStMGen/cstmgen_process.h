#pragma once

#include <CStMGen/cstmgen_params.h>
#include <CStMGen/cstmgen_json_machine_structure.h>

#include <string>
#include <ios>

/* ------------------------------------------------------------------------- */

namespace gen
{

/* ------------------------------------------------------------------------- */

namespace details
{

template <char const* const& VAR_NAME>
struct dependent_false_t
{
  static bool const value = false;
};

}  // namespace details

/* ------------------------------------------------------------------------- */

class cstmgen_process_t final
{
  using buffer_t = std::string;

  static constexpr char const* const m_var_STATE_MACHINE_NAME = "%{STATE-MACHINE-NAME}%";
  static constexpr char const* const m_var_state_machine_name = "%{state-machine-name}%";
  static constexpr char const* const m_var_STATE_NAMES_LIST = "%{STATE-NAMES-LIST}%";
  static constexpr char const* const m_var_STATE_NAME = "%{STATE-NAME}%";
  static constexpr char const* const m_var_state_name = "%{state-name}%";
  static constexpr char const* const m_var_STATE_NAME_FROM = "%{STATE-NAME-FROM}%";
  static constexpr char const* const m_var_state_name_from = "%{state-name-from}%";
  static constexpr char const* const m_var_STATE_NAME_TO = "%{STATE-NAME-TO}%";
  static constexpr char const* const m_var_state_name_to = "%{state-name-to}%";
  static constexpr char const* const m_var_state_transitions_definition = "%{state-transitions-definition}%";
  static constexpr char const* const m_var_state_transitions_list = "%{state-transitions-list}%";
  static constexpr char const* const m_var_state_includes_list = "%{state-includes-list}%";
  static constexpr char const* const m_var_state_nodes_list = "%{state-nodes-list}%";
  static constexpr char const* const m_var_initial_state_name = "%{inital-state-name}%";

public:
  cstmgen_process_t ( cfg::cstmgen_params_t const& params,
                      cfg::cstmgen_json_machine_structure_t const& machine_structure );

  cstmgen_process_t ( cstmgen_process_t const& ) = delete;
  cstmgen_process_t& operator= ( cstmgen_process_t const& ) = delete;
  cstmgen_process_t ( cstmgen_process_t&& ) = delete;
  cstmgen_process_t& operator= ( cstmgen_process_t&& ) = delete;

private:
  template<char const* const& VAR_NAME>
  void find_and_process_var ( buffer_t& buffer, std::string const& new_str ) const;

  template<char const* const& VAR_NAME>
  void find_and_process_upper_var ( buffer_t& buffer,
                                    std::string const& replacement_str ) const;

  template<char const* const& VAR_NAME>
  void find_and_process_lower_var ( buffer_t& buffer,
                                    std::string const& replacement_str ) const;

  template <typename TARGET_STR_T, typename REPLACEMENT_STR_T>
  void replace_all_occurences_inplace ( buffer_t& buffer,
                                        TARGET_STR_T const& target_str,
                                        REPLACEMENT_STR_T const& replacement_str ) const;

  void generate_state_enum ( std::string const& header_folder,
                             std::ios_base::openmode out_file_mode ) const;
  void generate_state_machine_data_header ( std::string const& header_folder,
      std::ios_base::openmode out_file_mode ) const;
  void generate_state_header ( std::string const& header_folder,
                               std::ios_base::openmode out_file_mode,
                               std::string const& state_name ) const;
  void generate_state_diagram_header ( std::string const& header_folder,
                                       std::ios_base::openmode out_file_mode ) const;
  void generate_state_machine_data_implementation ( std::string const& implementation_folder,
      std::ios_base::openmode out_file_mode ) const;
  void generate_state_implementation ( std::string const& implementation_folder,
                                       std::ios_base::openmode out_file_mode,
                                       std::string const& state_name ) const;
  void generate_state_diagram_implementation ( std::string const& implementation_folder,
      std::ios_base::openmode out_file_mode ) const;

  void generate_files() const;

  void process_all_vars ( buffer_t& buffer, buffer_t const& state_name ) const;

  buffer_t get_state_enum_state_name ( buffer_t const& state_name ) const;
  buffer_t get_state_transition_name ( buffer_t const& state_name_from,
                                       buffer_t const& state_name_to ) const;

  void convert_to_lower_case_inplace ( buffer_t& buffer ) const;
  void convert_to_upper_case_inplace ( buffer_t& buffer ) const;

private:
  cfg::cstmgen_params_t const& m_params;
  cfg::cstmgen_json_machine_structure_t const& m_machine_structure;
};

/* ------------------------------------------------------------------------- */

} // namespace gen
