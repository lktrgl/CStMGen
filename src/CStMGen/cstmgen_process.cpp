#include <CStMGen/cstmgen_process.h>

#include <CStMGen/data/templates/cstm_state_enum_template_h.h>
#include <CStMGen/data/templates/cstm_state_enum_state_name_template.h>
#include <CStMGen/data/templates/cstm_state_template_c.h>
#include <CStMGen/data/templates/cstm_state_template_h.h>
#include <CStMGen/data/templates/cstm_state_transition_template_c.h>

#include <locale>
#include <iostream>
#include <sstream>
#include <string_view>

/* ------------------------------------------------------------------------- */

namespace gen
{

/* ------------------------------------------------------------------------- */

cstmgen_process_t::cstmgen_process_t ( cfg::cstmgen_params_t const& params,
                                       cfg::json_machine_structure_t const& machine_structure )
  : m_params ( params )
  , m_machine_structure ( machine_structure )
{
  generate_files();
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_STATE_MACHINE_NAME> (  buffer_t& buffer,
    std::string const& state_name )
{
  ( void ) state_name;

  constexpr std::string_view const var{cstmgen_process_t::m_var_STATE_MACHINE_NAME};

  auto STATE_MACHINE_NAME = m_machine_structure.get_machine_name();

  convert_to_upper_case_inplace ( STATE_MACHINE_NAME );

  replace_all_occurences_inplace ( buffer, var, STATE_MACHINE_NAME );
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_state_machine_name> (  buffer_t& buffer,
    std::string const& state_name )
{
  ( void ) state_name;

  constexpr std::string_view const var{cstmgen_process_t::m_var_state_machine_name};

  auto state_machine_name = m_machine_structure.get_machine_name();

  convert_to_lower_case_inplace ( state_machine_name );

  replace_all_occurences_inplace ( buffer, var, state_machine_name );
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_STATE_NAMES_LIST> (  buffer_t& buffer,
    std::string const& state_name )
{
  ( void ) state_name;

  constexpr std::string_view const var{cstmgen_process_t::m_var_STATE_NAMES_LIST};

  auto STATE_MACHINE_NAME = m_machine_structure.get_machine_name();

  convert_to_upper_case_inplace ( STATE_MACHINE_NAME );

  auto new_str = [this, &STATE_MACHINE_NAME]()
  {
    std::stringstream ss;

    auto const& states = m_machine_structure.get_states();

    auto first_item = true;

    for ( auto const& s : states )
    {
      ss
          << ( first_item ? ( first_item = false, "" ) : ", " )
          << get_state_enum_state_name ( s.first );
    }

    return ss.str();
  }
  ();

  convert_to_upper_case_inplace ( new_str );

  replace_all_occurences_inplace ( buffer, var, new_str );
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_STATE_NAME> (  buffer_t& buffer,
    std::string const& state_name )
{
  auto new_state_name{state_name};

  constexpr std::string_view const var{cstmgen_process_t::m_var_STATE_NAME};

  convert_to_upper_case_inplace ( new_state_name );

  replace_all_occurences_inplace ( buffer, var, new_state_name );
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_state_name> (  buffer_t& buffer,
    std::string const& state_name )
{
  auto new_state_name{state_name};

  constexpr std::string_view const var{cstmgen_process_t::m_var_state_name};

  convert_to_lower_case_inplace ( new_state_name );

  replace_all_occurences_inplace ( buffer, var, new_state_name );
}

/* ------------------------------------------------------------------------- */

void cstmgen_process_t::generate_files()
{
  buffer_t buffer{data_templates_cstm_state_template_c,
                  data_templates_cstm_state_template_c + data_templates_cstm_state_template_c_len};
  std::string const state_name{m_machine_structure.get_states().cbegin()->first};

  process_all_vars ( buffer, state_name );

  std::cout << buffer << std::endl;
}

/* ------------------------------------------------------------------------- */

void cstmgen_process_t::process_all_vars ( buffer_t& buffer, std::string const& state_name )
{
  find_and_process_var<m_var_STATE_MACHINE_NAME> ( buffer, state_name );
  find_and_process_var<m_var_state_machine_name> ( buffer, state_name );
  find_and_process_var<m_var_STATE_NAMES_LIST> ( buffer, state_name );
  find_and_process_var<m_var_STATE_NAME> ( buffer, state_name );
  find_and_process_var<m_var_state_name> ( buffer, state_name );
  //  find_and_process_var<m_var_state_name_from> ( buffer, state_name );
  //  find_and_process_var<m_var_STATE_NAME_TO> ( buffer, state_name );
  //  find_and_process_var<m_var_state_name_to> ( buffer, state_name );
  //  find_and_process_var<m_var_state_transitions_sdefinition> ( buffer, state_name );
  //  find_and_process_var<m_var_state_transitions_list> ( buffer, state_name );
}

/* ------------------------------------------------------------------------- */

cstmgen_process_t::buffer_t
cstmgen_process_t::get_state_enum_state_name ( const buffer_t& state_name )
{
  buffer_t result{data_templates_cstm_state_enum_state_name_template,
                  data_templates_cstm_state_enum_state_name_template + data_templates_cstm_state_enum_state_name_template_len};

  {
    constexpr std::string_view const var_STATE_MACHINE_NAME{cstmgen_process_t::m_var_STATE_MACHINE_NAME};
    std::string new_state_machine_name{m_machine_structure.get_machine_name() };
    convert_to_upper_case_inplace ( new_state_machine_name );
    replace_all_occurences_inplace ( result, var_STATE_MACHINE_NAME, new_state_machine_name );
  }

  {
    constexpr std::string_view const var_STATE_NAME{cstmgen_process_t::m_var_STATE_NAME};
    std::string new_state_name{state_name};
    convert_to_upper_case_inplace ( new_state_name );
    replace_all_occurences_inplace ( result, var_STATE_NAME, new_state_name );
  }

  return result;
}

/* ------------------------------------------------------------------------- */

void cstmgen_process_t::convert_to_lower_case_inplace ( buffer_t& buffer )
{
  auto& f = std::use_facet<std::ctype<char>> ( std::locale() );
  f.tolower ( buffer.data(), buffer.data() + buffer.size() );
}

/* ------------------------------------------------------------------------- */

void cstmgen_process_t::convert_to_upper_case_inplace ( buffer_t& buffer )
{
  auto& f = std::use_facet<std::ctype<char>> ( std::locale() );
  f.toupper ( buffer.data(), buffer.data() + buffer.size() );
}

/* ------------------------------------------------------------------------- */

} // namespace gen
