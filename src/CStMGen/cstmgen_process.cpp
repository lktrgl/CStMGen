#include <CStMGen/cstmgen_process.h>

#include <CStMGen/data/templates/cstm_state_diagram_template_h.h>
#include <CStMGen/data/templates/cstm_state_diagram_template_c.h>
#include <CStMGen/data/templates/cstm_state_enum_template_h.h>
#include <CStMGen/data/templates/cstm_state_enum_state_name_text.h>
#include <CStMGen/data/templates/cstm_state_data_desc_template_h.h>
#include <CStMGen/data/templates/cstm_state_data_desc_template_c.h>
#include <CStMGen/data/templates/cstm_state_template_c.h>
#include <CStMGen/data/templates/cstm_state_template_h.h>
#include <CStMGen/data/templates/cstm_state_transition_template_c.h>
#include <CStMGen/data/templates/cstm_state_transition_name_template.h>
#include <CStMGen/data/templates/cstm_state_include_text_template.h>
#include <CStMGen/data/templates/cstm_state_node_text_template.h>
#include <CStMGen/data/templates/cstm_state_file_name_template_h.h>
#include <CStMGen/data/templates/cstm_state_file_name_template_c.h>
#include <CStMGen/data/templates/cstm_state_diagram_file_name_template_h.h>
#include <CStMGen/data/templates/cstm_state_diagram_file_name_template_c.h>
#include <CStMGen/data/templates/cstm_state_enum_file_name_template_h.h>
#include <CStMGen/data/templates/cstm_state_data_desc_file_name_template_h.h>
#include <CStMGen/data/templates/cstm_state_data_desc_file_name_template_c.h>

#include <locale>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

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
<cstmgen_process_t::m_var_STATE_NAMES_LIST> (  buffer_t& buffer,
    std::string const& state_name )
{
  ( void ) state_name;

  if ( std::string::npos == buffer.find ( m_var_STATE_NAMES_LIST ) )
  {
    return;
  }

  auto new_str = [this]()
  {
    std::stringstream ss;

    auto const& states_sorted = m_machine_structure.get_states_sorted();

    for ( auto const& s : states_sorted )
    {
      ss
          << get_state_enum_state_name ( s.first ) << ", ";
    }

    return ss.str();
  }
  ();

  find_and_process_upper_var<m_var_STATE_NAMES_LIST> ( buffer, new_str );
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_state_transitions_list> (  buffer_t& buffer,
    std::string const& state_name )
{
  if ( std::string::npos == buffer.find ( m_var_state_transitions_list ) )
  {
    return;
  }

  auto new_str = [this, &state_name]()
  {
    std::stringstream ss;

    auto const& transitions_from = m_machine_structure.get_transitions_from();
    auto const& transitions_from_state = transitions_from.equal_range ( state_name );

    auto first_item = true;

    for ( auto t = transitions_from_state.first; t != transitions_from_state.second; ++t )
    {
      ss
          << ( first_item ? ( first_item = false, "" ) : ", " )
          << "&" << get_state_transition_name ( state_name, t->second );
    }

    return ss.str();
  }
  ();

  find_and_process_lower_var<m_var_state_transitions_list> ( buffer, new_str );
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_state_transitions_definition> (  buffer_t& buffer,
    std::string const& state_name )
{
  if ( std::string::npos == buffer.find ( m_var_state_transitions_definition ) )
  {
    return;
  }

  auto new_str = [this, &state_name]()
  {
    std::stringstream ss;

    auto const& transitions_from = m_machine_structure.get_transitions_from();
    auto const& transitions_from_state = transitions_from.equal_range ( state_name );

    for ( auto t = transitions_from_state.first; t != transitions_from_state.second; ++t )
    {
      buffer_t buffer{data_templates_cstm_state_transition_template_c,
                      data_templates_cstm_state_transition_template_c + data_templates_cstm_state_transition_template_c_len};

      find_and_process_upper_var<m_var_STATE_MACHINE_NAME> ( buffer, m_machine_structure.get_machine_name() );
      find_and_process_lower_var<m_var_state_machine_name> ( buffer, m_machine_structure.get_machine_name() );
      find_and_process_lower_var<m_var_state_name_from> ( buffer, state_name );
      find_and_process_lower_var<m_var_state_name_to> ( buffer, t->second );
      find_and_process_upper_var<m_var_STATE_NAME_TO> ( buffer, t->second );

      ss
          << buffer;
    }

    return ss.str();
  }
  ();

  constexpr std::string_view const var{m_var_state_transitions_definition};

  replace_all_occurences_inplace ( buffer, var, new_str );
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_state_includes_list> (  buffer_t& buffer,
    std::string const& state_name )
{
  ( void ) state_name;

  if ( std::string::npos == buffer.find ( m_var_state_includes_list ) )
  {
    return;
  }

  auto new_str = [this]()
  {
    std::stringstream ss;

    auto const& states_sorted = m_machine_structure.get_states_sorted();

    auto const& new_machine_name = m_machine_structure.get_machine_name();

    auto first_item = true;

    for ( auto const& s : states_sorted )
    {
      buffer_t buffer{data_templates_cstm_state_include_text_template,
                      data_templates_cstm_state_include_text_template + data_templates_cstm_state_include_text_template_len};

      find_and_process_lower_var<m_var_state_machine_name> ( buffer, new_machine_name );
      find_and_process_lower_var<m_var_state_name> ( buffer, s.first );

      ss
          << ( first_item ? ( first_item = false, "" ) : "\n" )
          << buffer;
    }

    return ss.str();
  }
  ();

  find_and_process_lower_var<m_var_state_includes_list> ( buffer, new_str );
}

/* ------------------------------------------------------------------------- */

template<>
void cstmgen_process_t::find_and_process_var
<cstmgen_process_t::m_var_state_nodes_list> (  buffer_t& buffer,
    std::string const& state_name )
{
  ( void ) state_name;

  if ( std::string::npos == buffer.find ( m_var_state_nodes_list ) )
  {
    return;
  }

  auto new_str = [this]()
  {
    std::stringstream ss;

    auto const& states_sorted = m_machine_structure.get_states_sorted();

    auto const& new_machine_name = m_machine_structure.get_machine_name();

    auto first_item = true;

    for ( auto const& s : states_sorted )
    {
      buffer_t buffer{data_templates_cstm_state_node_text_template,
                      data_templates_cstm_state_node_text_template + data_templates_cstm_state_node_text_template_len};

      find_and_process_upper_var<m_var_STATE_MACHINE_NAME> ( buffer, new_machine_name );
      find_and_process_upper_var<m_var_STATE_NAME> ( buffer, s.first );
      find_and_process_lower_var<m_var_state_name> ( buffer, s.first );

      ss
          << ( first_item ? ( first_item = false, "" ) : ",\n  " )
          << buffer;
    }

    return ss.str();
  }
  ();

  constexpr std::string_view const var{m_var_state_nodes_list};
  replace_all_occurences_inplace ( buffer, var, new_str );
}

/* ------------------------------------------------------------------------- */

void cstmgen_process_t::generate_files()
{
  buffer_t buffer{data_templates_cstm_state_diagram_template_c,
                  data_templates_cstm_state_diagram_template_c + data_templates_cstm_state_diagram_template_c_len};
  //  buffer_t buffer{data_templates_cstm_state_diagram_template_h,
  //                  data_templates_cstm_state_diagram_template_h + data_templates_cstm_state_diagram_template_h_len};
  //  buffer_t buffer{data_templates_cstm_state_data_desc_template_c,
  //                  data_templates_cstm_state_data_desc_template_c + data_templates_cstm_state_data_desc_template_c_len};
  //  buffer_t buffer{data_templates_cstm_state_data_desc_template_h,
  //                  data_templates_cstm_state_data_desc_template_h + data_templates_cstm_state_data_desc_template_h_len};
  //  buffer_t buffer{data_templates_cstm_state_template_c,
  //                  data_templates_cstm_state_template_c + data_templates_cstm_state_template_c_len};
  //  buffer_t buffer{data_templates_cstm_state_enum_template_h,
  //                  data_templates_cstm_state_enum_template_h + data_templates_cstm_state_enum_template_h_len};
  //    std::string const state_name{m_machine_structure.get_states().cbegin()->first};
  std::string const state_name{"SEARCH_DEVICE"};

  process_all_vars ( buffer, state_name );

  std::cout << buffer << std::endl;
}

/* ------------------------------------------------------------------------- */

void cstmgen_process_t::process_all_vars ( buffer_t& buffer, std::string const& state_name )
{
  find_and_process_upper_var<m_var_STATE_MACHINE_NAME> ( buffer, m_machine_structure.get_machine_name() );
  find_and_process_lower_var<m_var_state_machine_name> ( buffer, m_machine_structure.get_machine_name() );
  find_and_process_var<m_var_STATE_NAMES_LIST> ( buffer, state_name );
  find_and_process_upper_var<m_var_STATE_NAME> ( buffer, state_name );
  find_and_process_lower_var<m_var_state_name> ( buffer, state_name );
  find_and_process_var<m_var_state_transitions_definition> ( buffer, state_name );
  find_and_process_var<m_var_state_transitions_list> ( buffer, state_name );
  find_and_process_var<m_var_state_includes_list> ( buffer, state_name );
  find_and_process_var<m_var_state_nodes_list> ( buffer, state_name );
}

/* ------------------------------------------------------------------------- */

cstmgen_process_t::buffer_t
cstmgen_process_t::get_state_enum_state_name ( const buffer_t& state_name )
{
  buffer_t result{data_templates_cstm_state_enum_state_name_text,
                  data_templates_cstm_state_enum_state_name_text + data_templates_cstm_state_enum_state_name_text_len};

  find_and_process_upper_var<m_var_STATE_MACHINE_NAME> ( result, m_machine_structure.get_machine_name() );
  find_and_process_upper_var<m_var_STATE_NAME> ( result, state_name );

  return result;
}

/* ------------------------------------------------------------------------- */

cstmgen_process_t::buffer_t
cstmgen_process_t::get_state_transition_name ( buffer_t const& state_name_from,
    buffer_t const& state_name_to )
{
  buffer_t result{data_templates_cstm_state_transition_name_template,
                  data_templates_cstm_state_transition_name_template + data_templates_cstm_state_transition_name_template_len};

  find_and_process_lower_var<m_var_state_name_from> ( result, state_name_from );
  find_and_process_lower_var<m_var_state_name_to> ( result, state_name_to );

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
