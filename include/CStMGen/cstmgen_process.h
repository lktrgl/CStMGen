#pragma once

#include <CStMGen/cstmgen_params.h>
#include <CStMGen/cstmgen_json_machine_structure.h>

/* ------------------------------------------------------------------------- */

#include <CStMGen/cstmgen_process_utils.h>

/* ------------------------------------------------------------------------- */

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

using buffer_t = std::string;

}  // namespace details

/* ------------------------------------------------------------------------- */

class cstmgen_process_t final : gen::utils::cstmgen_process_utils_t<details::buffer_t, std::string, std::string_view>
{
  using buffer_t = details::buffer_t;

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
                      size_t idx,
                      cfg::cstmgen_json_machine_structure_t const& machine_structure );

  cstmgen_process_t ( cstmgen_process_t const& ) = delete;
  cstmgen_process_t& operator= ( cstmgen_process_t const& ) = delete;
  cstmgen_process_t ( cstmgen_process_t&& ) = delete;
  cstmgen_process_t& operator= ( cstmgen_process_t&& ) = delete;

private:
  template<char const* const& VAR_NAME>
  void find_and_process_var ( buffer_t& buffer, std::string const& new_str ) const;

  void replace_state_implementation_user_property_inplace ( buffer_t& buffer,
      std::string const& state_name ) const;

  void replace_transition_evaluation_inplace ( buffer_t& buffer,
      std::string const& state_name_from,
      std::string const& state_name_to,
      std::string const& user_property_file_name ) const;

  void replace_machine_data_decl_inplace ( buffer_t& buffer ) const;
  void replace_machine_data_init_inplace ( buffer_t& buffer ) const;

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

private:
  cfg::cstmgen_params_t const& m_params;
  size_t const m_idx;
  cfg::cstmgen_json_machine_structure_t const& m_machine_structure;
};

/* ------------------------------------------------------------------------- */

} // namespace gen
