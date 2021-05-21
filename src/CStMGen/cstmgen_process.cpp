#include <CStMGen/cstmgen_process.h>

#include <CStMGen/data/templates/state_machine_enum/cstm_state_enum_template_h.h>
#include <CStMGen/data/templates/state_machine_enum/cstm_state_enum_state_name_text.h>
#include <CStMGen/data/templates/state_machine_enum/cstm_state_enum_file_name_template_h.h>

#include <CStMGen/data/templates/state_machine_data/cstm_state_data_desc_file_name_template_h.h>
#include <CStMGen/data/templates/state_machine_data/cstm_state_data_desc_file_name_template_c.h>
#include <CStMGen/data/templates/state_machine_data/cstm_state_data_desc_template_h.h>
#include <CStMGen/data/templates/state_machine_data/cstm_state_data_desc_template_c.h>

#include <CStMGen/data/templates/state_diagram_code/cstm_state_diagram_template_h.h>
#include <CStMGen/data/templates/state_diagram_code/cstm_state_diagram_template_c.h>
#include <CStMGen/data/templates/state_diagram_code/cstm_state_diagram_file_name_template_h.h>
#include <CStMGen/data/templates/state_diagram_code/cstm_state_diagram_file_name_template_c.h>
#include <CStMGen/data/templates/state_diagram_code/cstm_state_include_text_template.h>
#include <CStMGen/data/templates/state_diagram_code/cstm_state_node_text_template.h>

#include <CStMGen/data/templates/state_code/cstm_state_template_c.h>
#include <CStMGen/data/templates/state_code/cstm_state_template_h.h>
#include <CStMGen/data/templates/state_code/cstm_state_file_name_template_h.h>
#include <CStMGen/data/templates/state_code/cstm_state_file_name_template_c.h>
#include <CStMGen/data/templates/state_code/cstm_state_transition_template_c.h>
#include <CStMGen/data/templates/state_code/cstm_state_transition_name_template.h>

#include <CStMGen/data/templates/state_code/cstm_state_global_data_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_enter_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_input_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_leave_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_output_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_run_placeholder_name_template.h>

#include <locale>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>
#include <fstream>

/* ------------------------------------------------------------------------- */

namespace gen
{

/* ------------------------------------------------------------------------- */

cstmgen_process_t::cstmgen_process_t ( cfg::cstmgen_params_t const& params,
                                       cfg::cstmgen_json_machine_structure_t const& machine_structure )
  : m_params ( params )
  , m_machine_structure ( machine_structure )
{
  generate_files();
}

/* ------------------------------------------------------------------------- */

template<char const* const& VAR_NAME>
void cstmgen_process_t::find_and_process_var ( buffer_t& buffer, std::string const& replacement_str )
{
  ( void ) buffer;
  ( void ) replacement_str;

  static_assert ( details::dependent_false_t<VAR_NAME>::value, "You should define the full specification instead." );
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

  auto replacement_str = [this]()
  {
    std::stringstream ss;

    auto const& states_sorted = m_machine_structure.get_states_sorted();

    for ( auto const& s : states_sorted )
    {
      ss
          << get_state_enum_state_name ( s.first ) << "=" << s.second->value << ",\n";
    }

    return ss.str();
  }
  ();

  find_and_process_upper_var<m_var_STATE_NAMES_LIST> ( buffer, replacement_str );
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

  auto replacement_str = [this, &state_name]()
  {
    std::stringstream ss;

    auto const& transitions = m_machine_structure.get_transitions();
    auto const& transitions_from_state = transitions.equal_range ( state_name );

    auto first_item = true;

    for ( auto t = transitions_from_state.first; t != transitions_from_state.second; ++t )
    {
      ss
          << ( first_item ? ( first_item = false, "" ) : ",\n" )
          << "&" << get_state_transition_name ( state_name, t->second );
    }

    return ss.str();
  }
  ();

  find_and_process_lower_var<m_var_state_transitions_list> ( buffer, replacement_str );
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

  auto replacement_str = [this, &state_name]()
  {
    std::stringstream ss;

    auto const& transitions = m_machine_structure.get_transitions();
    auto const& transitions_from_state = transitions.equal_range ( state_name );

    for ( auto t = transitions_from_state.first; t != transitions_from_state.second; ++t )
    {
      buffer_t buffer{data_templates_state_code_cstm_state_transition_template_c,
                      data_templates_state_code_cstm_state_transition_template_c + data_templates_state_code_cstm_state_transition_template_c_len};

      find_and_process_upper_var<m_var_STATE_MACHINE_NAME> ( buffer, m_machine_structure.get_machine_name() );
      find_and_process_lower_var<m_var_state_machine_name> ( buffer, m_machine_structure.get_machine_name() );
      find_and_process_upper_var<m_var_STATE_NAME_FROM> ( buffer, state_name );
      find_and_process_lower_var<m_var_state_name_from> ( buffer, state_name );
      find_and_process_lower_var<m_var_state_name_to> ( buffer, t->second );
      find_and_process_upper_var<m_var_STATE_NAME_TO> ( buffer, t->second );

      ss
          << buffer;
    }

    return ss.str();
  }
  ();

  constexpr std::string_view const target_str{m_var_state_transitions_definition};

  replace_all_occurences_inplace ( buffer, target_str, replacement_str );
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

  auto replacement_str = [this]()
  {
    std::stringstream ss;

    auto const& states_sorted = m_machine_structure.get_states_sorted();

    auto const& new_machine_name = m_machine_structure.get_machine_name();

    auto first_item = true;

    for ( auto const& s : states_sorted )
    {
      buffer_t buffer{data_templates_state_diagram_code_cstm_state_include_text_template,
                      data_templates_state_diagram_code_cstm_state_include_text_template + data_templates_state_diagram_code_cstm_state_include_text_template_len};

      find_and_process_lower_var<m_var_state_machine_name> ( buffer, new_machine_name );
      find_and_process_lower_var<m_var_state_name> ( buffer, s.first );

      ss
          << ( first_item ? ( first_item = false, "" ) : "\n" )
          << buffer;
    }

    return ss.str();
  }
  ();

  find_and_process_lower_var<m_var_state_includes_list> ( buffer, replacement_str );
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

  auto replacement_str = [this]()
  {
    std::stringstream ss;

    auto const& states_sorted = m_machine_structure.get_states_sorted();

    auto const& new_machine_name = m_machine_structure.get_machine_name();

    auto first_item = true;

    for ( auto const& s : states_sorted )
    {
      buffer_t buffer{data_templates_state_diagram_code_cstm_state_node_text_template,
                      data_templates_state_diagram_code_cstm_state_node_text_template + data_templates_state_diagram_code_cstm_state_node_text_template_len};

      find_and_process_upper_var<m_var_STATE_MACHINE_NAME> ( buffer, new_machine_name );
      find_and_process_lower_var<m_var_state_machine_name> ( buffer, new_machine_name );
      find_and_process_upper_var<m_var_STATE_NAME> ( buffer, s.first );
      find_and_process_lower_var<m_var_state_name> ( buffer, s.first );

      ss
          << ( first_item ? ( first_item = false, "" ) : ",\n  " )
          << buffer;
    }

    return ss.str();
  }
  ();

  constexpr std::string_view const target_str{m_var_state_nodes_list};
  replace_all_occurences_inplace ( buffer, target_str, replacement_str );
}

/* ------------------------------------------------------------------------- */

template<char const* const& VAR_NAME>
void cstmgen_process_t::find_and_process_upper_var ( buffer_t& buffer,
    std::string const& replacement_str )
{
  constexpr std::string_view const target_str{VAR_NAME};

  auto local_replacement_str{replacement_str};
  convert_to_upper_case_inplace ( local_replacement_str );

  replace_all_occurences_inplace ( buffer, target_str, local_replacement_str );
}

/* ------------------------------------------------------------------------- */

template<char const* const& VAR_NAME>
void cstmgen_process_t::find_and_process_lower_var ( buffer_t& buffer,
    std::string const& replacement_str )
{
  constexpr std::string_view const target_str{VAR_NAME};

  auto local_replacement_str{replacement_str};
  convert_to_lower_case_inplace ( local_replacement_str );

  replace_all_occurences_inplace ( buffer, target_str, local_replacement_str );
}

/* ------------------------------------------------------------------------- */

template <typename TARGET_STR_T, typename REPLACEMENT_STR_T>
void cstmgen_process_t::replace_all_occurences_inplace ( buffer_t& buffer,
    TARGET_STR_T const& target_str,
    REPLACEMENT_STR_T const& replacement_str )
{
  for ( auto pos = buffer.find ( target_str, 0 );
        std::string::npos != pos;
        pos = buffer.find ( target_str, 0 ) )
  {
    buffer.replace ( pos, target_str.size(), replacement_str );
  }
}

/* ------------------------------------------------------------------------- */

void cstmgen_process_t::generate_files()
{
  constexpr static auto const out_file_mode = std::ios_base::binary | std::ios_base::out | std::ios_base::trunc;

  if ( m_params.get_header_folder_name().length() )
  {
    auto const& header_folder = m_params.get_header_folder_name();

    if ( m_params.is_produce_state_enum() )
    {
      buffer_t buffer_file_contents{data_templates_state_machine_enum_cstm_state_enum_template_h,
                                    data_templates_state_machine_enum_cstm_state_enum_template_h + data_templates_state_machine_enum_cstm_state_enum_template_h_len};
      process_all_vars ( buffer_file_contents, {} );

      buffer_t buffer_file_name{data_templates_state_machine_enum_cstm_state_enum_file_name_template_h,
                                data_templates_state_machine_enum_cstm_state_enum_file_name_template_h + data_templates_state_machine_enum_cstm_state_enum_file_name_template_h_len};
      process_all_vars ( buffer_file_name, {} );

      std::ofstream out ( {header_folder + '/' + buffer_file_name}, out_file_mode );
      out.write ( buffer_file_contents.data(), buffer_file_contents.size() );
      out.flush();
    }

    if ( m_params.is_produce_state_machine_data_header() )
    {
      buffer_t buffer_file_contents{data_templates_state_machine_data_cstm_state_data_desc_template_h,
                                    data_templates_state_machine_data_cstm_state_data_desc_template_h + data_templates_state_machine_data_cstm_state_data_desc_template_h_len};
      process_all_vars ( buffer_file_contents, {} );

      buffer_t buffer_file_name{data_templates_state_machine_data_cstm_state_data_desc_file_name_template_h,
                                data_templates_state_machine_data_cstm_state_data_desc_file_name_template_h + data_templates_state_machine_data_cstm_state_data_desc_file_name_template_h_len};
      process_all_vars ( buffer_file_name, {} );

      std::ofstream out ( {header_folder + '/' + buffer_file_name}, out_file_mode );
      out.write ( buffer_file_contents.data(), buffer_file_contents.size() );
      out.flush();
    }

    if ( m_params.is_produce_state_header() )
    {
      auto const& states = m_machine_structure.get_states();

      for ( auto const& s : states )
      {
        buffer_t buffer_file_contents{data_templates_state_code_cstm_state_template_h,
                                      data_templates_state_code_cstm_state_template_h + data_templates_state_code_cstm_state_template_h_len};
        process_all_vars ( buffer_file_contents, s.first );

        buffer_t buffer_file_name{data_templates_state_code_cstm_state_file_name_template_h,
                                  data_templates_state_code_cstm_state_file_name_template_h + data_templates_state_code_cstm_state_file_name_template_h_len};
        process_all_vars ( buffer_file_name, s.first );

        std::ofstream out ( {header_folder + '/' + buffer_file_name}, out_file_mode );
        out.write ( buffer_file_contents.data(), buffer_file_contents.size() );
        out.flush();
      }
    }

    if ( m_params.is_produce_state_diagram_header() )
    {
      buffer_t buffer_file_contents{data_templates_state_diagram_code_cstm_state_diagram_template_h,
                                    data_templates_state_diagram_code_cstm_state_diagram_template_h + data_templates_state_diagram_code_cstm_state_diagram_template_h_len};
      process_all_vars ( buffer_file_contents, {} );

      buffer_t buffer_file_name{data_templates_state_diagram_code_cstm_state_diagram_file_name_template_h,
                                data_templates_state_diagram_code_cstm_state_diagram_file_name_template_h + data_templates_state_diagram_code_cstm_state_diagram_file_name_template_h_len};
      process_all_vars ( buffer_file_name, {} );

      std::ofstream out ( {header_folder + '/' + buffer_file_name}, out_file_mode );
      out.write ( buffer_file_contents.data(), buffer_file_contents.size() );
      out.flush();
    }
  }

  if ( m_params.get_implementation_folder_name().length() )
  {
    auto const& implementation_folder = m_params.get_implementation_folder_name();

    if ( m_params.is_produce_state_machine_data_implementation() )
    {
      buffer_t buffer_file_contents{data_templates_state_machine_data_cstm_state_data_desc_template_c,
                                    data_templates_state_machine_data_cstm_state_data_desc_template_c + data_templates_state_machine_data_cstm_state_data_desc_template_c_len};
      process_all_vars ( buffer_file_contents, {} );

      buffer_t buffer_file_name{data_templates_state_machine_data_cstm_state_data_desc_file_name_template_c,
                                data_templates_state_machine_data_cstm_state_data_desc_file_name_template_c + data_templates_state_machine_data_cstm_state_data_desc_file_name_template_c_len};
      process_all_vars ( buffer_file_name, {} );

      std::ofstream out ( {implementation_folder + '/' + buffer_file_name}, out_file_mode );
      out.write ( buffer_file_contents.data(), buffer_file_contents.size() );
      out.flush();
    }

    if ( m_params.is_produce_state_implementation() )
    {
      auto const& states = m_machine_structure.get_states();

      for ( auto const& s : states )
      {
        buffer_t buffer_file_contents{data_templates_state_code_cstm_state_template_c,
                                      data_templates_state_code_cstm_state_template_c + data_templates_state_code_cstm_state_template_c_len};
        process_all_vars ( buffer_file_contents, s.first );

        buffer_t buffer_file_name{data_templates_state_code_cstm_state_file_name_template_c,
                                  data_templates_state_code_cstm_state_file_name_template_c + data_templates_state_code_cstm_state_file_name_template_c_len};
        process_all_vars ( buffer_file_name, s.first );

        std::ofstream out ( {implementation_folder + '/' + buffer_file_name}, out_file_mode );
        out.write ( buffer_file_contents.data(), buffer_file_contents.size() );
        out.flush();
      }
    }

    if ( m_params.is_produce_state_diagram_implementation() )
    {
      buffer_t buffer_file_contents{data_templates_state_diagram_code_cstm_state_diagram_template_c,
                                    data_templates_state_diagram_code_cstm_state_diagram_template_c + data_templates_state_diagram_code_cstm_state_diagram_template_c_len};
      process_all_vars ( buffer_file_contents, {} );

      buffer_t buffer_file_name{data_templates_state_diagram_code_cstm_state_diagram_file_name_template_c,
                                data_templates_state_diagram_code_cstm_state_diagram_file_name_template_c + data_templates_state_diagram_code_cstm_state_diagram_file_name_template_c_len};
      process_all_vars ( buffer_file_name, {} );

      std::ofstream out ( {implementation_folder + '/' + buffer_file_name}, out_file_mode );
      out.write ( buffer_file_contents.data(), buffer_file_contents.size() );
      out.flush();
    }
  }

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
  find_and_process_lower_var<m_var_initial_state_name> ( buffer, m_machine_structure.get_initial_state_name() );
}

/* ------------------------------------------------------------------------- */

cstmgen_process_t::buffer_t
cstmgen_process_t::get_state_enum_state_name ( const buffer_t& state_name )
{
  buffer_t result{data_templates_state_machine_enum_cstm_state_enum_state_name_text,
                  data_templates_state_machine_enum_cstm_state_enum_state_name_text + data_templates_state_machine_enum_cstm_state_enum_state_name_text_len};

  find_and_process_upper_var<m_var_STATE_MACHINE_NAME> ( result, m_machine_structure.get_machine_name() );
  find_and_process_upper_var<m_var_STATE_NAME> ( result, state_name );

  return result;
}

/* ------------------------------------------------------------------------- */

cstmgen_process_t::buffer_t
cstmgen_process_t::get_state_transition_name ( buffer_t const& state_name_from,
    buffer_t const& state_name_to )
{
  buffer_t result{data_templates_state_code_cstm_state_transition_name_template,
                  data_templates_state_code_cstm_state_transition_name_template + data_templates_state_code_cstm_state_transition_name_template_len};

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
