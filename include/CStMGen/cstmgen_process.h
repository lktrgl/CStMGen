#pragma once

#include <CStMGen/cstmgen_params.h>
#include <CStMGen/json_machine_structure.h>

#include <string>

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
  static constexpr char const* const m_var_state_name_from = "%{state-name-from}%";
  static constexpr char const* const m_var_STATE_NAME_TO = "%{STATE-NAME-TO}%";
  static constexpr char const* const m_var_state_name_to = "%{state-name-to}%";
  static constexpr char const* const m_var_state_transitions_sdefinition = "%{state-transitions-sdefinition}%";
  static constexpr char const* const m_var_state_transitions_list = "%{state-transitions-list}%";

public:
  cstmgen_process_t ( cfg::cstmgen_params_t const& params,
                      cfg::json_machine_structure_t const& machine_structure );

  cstmgen_process_t ( cstmgen_process_t const& ) = delete;
  cstmgen_process_t& operator= ( cstmgen_process_t const& ) = delete;
  cstmgen_process_t ( cstmgen_process_t&& ) = delete;
  cstmgen_process_t& operator= ( cstmgen_process_t&& ) = delete;

private:
  template<char const* const& VAR_NAME>
  void find_and_process_var ( buffer_t& buffer, std::string const& state_name )
  {
    ( void ) buffer;
    ( void ) state_name;

    static_assert ( details::dependent_false_t<VAR_NAME>::value, "You should define the full specification instead." );
  }

  template <typename OLD_STR_T, typename NEW_STR_T>
  void replace_all_occurences_inplace ( buffer_t& buffer,
                                        OLD_STR_T const& old_str,
                                        NEW_STR_T const& new_str )
  {
    for ( auto pos = buffer.find ( old_str, 0 );
          std::string::npos != pos;
          pos = buffer.find ( old_str, 0 ) )
    {
      buffer.replace ( pos, old_str.size(), new_str );
    }
  }

  void generate_files();

  void process_all_vars ( buffer_t& buffer, buffer_t const& state_name );

  buffer_t get_state_enum_state_name ( buffer_t const& state_name );
  buffer_t get_state_transition_name ( buffer_t const& state_name_from,
                                       buffer_t const& state_name_to );

  void convert_to_lower_case_inplace ( buffer_t& buffer );
  void convert_to_upper_case_inplace ( buffer_t& buffer );

private:
  cfg::cstmgen_params_t const& m_params;
  cfg::json_machine_structure_t const& m_machine_structure;
};

/* ------------------------------------------------------------------------- */

} // namespace gen
