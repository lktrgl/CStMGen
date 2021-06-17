#include <CStMGen/cstmgen_json_machine_structure.h>

#include <CStMGen/data/templates/state_code/cstm_state_global_data_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_enter_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_input_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_leave_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_output_placeholder_name_template.h>
#include <CStMGen/data/templates/state_code/cstm_state_handler_run_placeholder_name_template.h>

#include <rapidjson/document.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>

/* ------------------------------------------------------------------------- */

namespace cfg
{

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_user_property_templates_t const
cstmgen_json_machine_structure_t::m_state_user_property_templates =
{
  {
    m_key_state_user_code_global,
    std::make_shared<state_user_property_template_t> (
      data_templates_state_code_cstm_state_global_data_placeholder_name_template,
      data_templates_state_code_cstm_state_global_data_placeholder_name_template_len
    )
  },
  {
    m_key_state_user_code_enter,
    std::make_shared<state_user_property_template_t> (
      data_templates_state_code_cstm_state_handler_enter_placeholder_name_template,
      data_templates_state_code_cstm_state_handler_enter_placeholder_name_template_len
    )
  },
  {
    m_key_state_user_code_input,
    std::make_shared<state_user_property_template_t> (
      data_templates_state_code_cstm_state_handler_input_placeholder_name_template,
      data_templates_state_code_cstm_state_handler_input_placeholder_name_template_len
    )
  },
  {
    m_key_state_user_code_run,
    std::make_shared<state_user_property_template_t> (
      data_templates_state_code_cstm_state_handler_run_placeholder_name_template,
      data_templates_state_code_cstm_state_handler_run_placeholder_name_template_len
    )
  },
  {
    m_key_state_user_code_output,
    std::make_shared<state_user_property_template_t> (
      data_templates_state_code_cstm_state_handler_output_placeholder_name_template,
      data_templates_state_code_cstm_state_handler_output_placeholder_name_template_len
    )
  },
  {
    m_key_state_user_code_leave,
    std::make_shared<state_user_property_template_t> (
      data_templates_state_code_cstm_state_handler_leave_placeholder_name_template,
      data_templates_state_code_cstm_state_handler_leave_placeholder_name_template_len
    )
  }
};

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_property_t::machine_property_t ( id_t id,
    coord_t x,
    coord_t y )
{
  m_property_map[m_key_state_id] = id;

  m_property_map[m_key_coord_x] = x;
  m_property_map[m_key_coord_y] = y;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_property_t::machine_property_t ( machine_property_t const& other )
{
  *this = other;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_property_t&
cstmgen_json_machine_structure_t::machine_property_t::operator= ( machine_property_t const& other )
{
  this->m_property_map = other.m_property_map;
  return *this;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_property_t&
cstmgen_json_machine_structure_t::machine_property_t::operator= ( machine_property_t&& other )
{
  std::swap ( this->m_property_map, other.m_property_map );
  return *this;
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::machine_property_t::get_id() const
{
  return m_property_map.at ( m_key_state_id );
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_property_t::state_property_t ( state_id_t id,
    state_value_t value,
    state_user_code_t user_code_global,
    state_user_code_t user_code_enter,
    state_user_code_t user_code_input,
    state_user_code_t user_code_run,
    state_user_code_t user_code_output,
    state_user_code_t user_code_leave,
    coord_t x,
    coord_t y )
{
  m_property_map[m_key_state_id] = id;
  m_property_map[m_key_state_numeric_value] = value;

  m_property_map[m_key_state_user_code_global] = user_code_global;
  m_property_map[m_key_state_user_code_enter] = user_code_enter;
  m_property_map[m_key_state_user_code_input] = user_code_input;
  m_property_map[m_key_state_user_code_run] = user_code_run;
  m_property_map[m_key_state_user_code_output] = user_code_output;
  m_property_map[m_key_state_user_code_leave] = user_code_leave;

  m_property_map[m_key_coord_x] = x;
  m_property_map[m_key_coord_y] = y;
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::state_property_t::get_property ( std::string_view const& name ) const
{
  return m_property_map.at ( name );
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::state_property_t::get_property ( std::string const& name ) const
{
  return m_property_map.at ( name );
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::state_property_t::get_id() const
{
  return m_property_map.at ( m_key_state_id );
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::state_property_t::get_value() const
{
  return m_property_map.at ( m_key_state_numeric_value );
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_property_t::state_property_t ( state_property_t const& other )
{
  *this = other;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_property_t&
cstmgen_json_machine_structure_t::state_property_t::operator= ( state_property_t const& other )
{
  this->m_property_map = other.m_property_map;
  return *this;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_user_property_template_t::state_user_property_template_t (
  uint8_t const* template_data_ptr,
  size_t template_data_len )
  : m_template_data_ptr ( template_data_ptr )
  , m_template_data_len ( template_data_len )
{
  /* EMPTY */
}

/* ------------------------------------------------------------------------- */

uint8_t const*
cstmgen_json_machine_structure_t::state_user_property_template_t::get_ptr() const
{
  return m_template_data_ptr;
}

/* ------------------------------------------------------------------------- */

size_t
cstmgen_json_machine_structure_t::state_user_property_template_t::get_length() const
{
  return m_template_data_len;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::transition_property_t::transition_property_t (
  std::string const& state_from,
  std::string const& state_to,
  std::string const& condition_code )
{
  m_property_map[m_key_transition_from] = state_from;
  m_property_map[m_key_transition_to] = state_to;
  m_property_map[m_key_transition_condition_user_code] = condition_code;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::transition_property_t::transition_property_t (
  transition_property_t const& other )
{
  *this = other;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::transition_property_t&
cstmgen_json_machine_structure_t::transition_property_t::operator= (
  transition_property_t const& other )
{
  m_property_map = other.m_property_map;
  return *this;
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::transition_property_t::get_property ( std::string_view const& name ) const
{
  return m_property_map.at ( name );
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::transition_property_t::get_property ( std::string const& name ) const
{
  return m_property_map.at ( name );
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::transition_property_t::get_state_from() const
{
  return m_property_map.at ( m_key_transition_from );
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::transition_property_t::get_state_to() const
{
  return m_property_map.at ( m_key_transition_to );
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::transition_property_t::get_condition_user_code() const
{
  return m_property_map.at ( m_key_transition_condition_user_code );
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_data_t::machine_data_t ( std::string const& data_field_decl,
    std::string const& data_field_init,
    coord_t x,
    coord_t y )
{
  m_property_map[m_key_data_user_decl] = data_field_decl;
  m_property_map[m_key_data_user_init] = data_field_init;

  m_property_map[m_key_coord_x] = x;
  m_property_map[m_key_coord_y] = y;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_data_t::machine_data_t ( machine_data_t const& other )
{
  *this = other;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_data_t&
cstmgen_json_machine_structure_t::machine_data_t::operator= ( machine_data_t const& other )
{
  this->m_property_map = other.m_property_map;
  return *this;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_data_t&
cstmgen_json_machine_structure_t::machine_data_t::operator= ( machine_data_t&& other )
{
  std::swap ( this->m_property_map, other.m_property_map );
  return *this;
}

/* ------------------------------------------------------------------------- */

void
cstmgen_json_machine_structure_t::machine_data_t::set_decl ( std::string const& data_field_decl )
{
  m_property_map[m_key_data_user_decl] = data_field_decl;
}

/* ------------------------------------------------------------------------- */

void
cstmgen_json_machine_structure_t::machine_data_t::set_init ( std::string const& data_field_init )
{
  m_property_map[m_key_data_user_init] = data_field_init;
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::machine_data_t::get_decl() const
{
  return m_property_map.at ( m_key_data_user_decl );
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::machine_data_t::get_init() const
{
  return m_property_map.at ( m_key_data_user_init );
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::cstmgen_json_machine_structure_t ( std::string const& config_file_pathname )
  : m_config_file_pathname ( config_file_pathname )
{
  load_from_file ( m_config_file_pathname );
}

/* ------------------------------------------------------------------------- */

std::string const& cstmgen_json_machine_structure_t::get_machine_name ( size_t idx ) const
{
  return m_state_machines.at ( idx ).m_machine.get_id();
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_data_t const&
cstmgen_json_machine_structure_t::get_machine_data ( size_t idx ) const
{
  return m_state_machines.at ( idx ).m_machine_data;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::states_t const&
cstmgen_json_machine_structure_t::get_states ( size_t idx ) const
{
  return m_state_machines.at ( idx ).m_states;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_user_property_templates_t const&
cstmgen_json_machine_structure_t::get_state_user_property_templates() const
{
  return m_state_user_property_templates;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::states_sorted_t
cstmgen_json_machine_structure_t::get_states_sorted ( size_t idx ) const
{
  states_sorted_t result{m_state_machines.at ( idx ).m_states.cbegin(), m_state_machines.at ( idx ).m_states.cend() };

  if ( not result.empty() )
  {
    std::sort ( result.begin(), result.end(), [] ( auto const & left, auto const & right )
    {
      auto const left_value = std::strtoul ( left.second->get_value().c_str(), nullptr, 10 );
      auto const right_value = std::strtoul ( right.second->get_value().c_str(), nullptr, 10 );
      return left_value < right_value;
    } );
  }

  return result;
}

/* ------------------------------------------------------------------------- */

std::string const& cstmgen_json_machine_structure_t::get_initial_state_name ( size_t idx ) const
{
  return m_state_machines.at ( idx ).m_initial_state_name;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::transitions_t const&
cstmgen_json_machine_structure_t::get_transitions ( size_t idx ) const
{
  return m_state_machines.at ( idx ).m_transitions;
}

/* ------------------------------------------------------------------------- */

bool cstmgen_json_machine_structure_t::valid ( size_t idx ) const
{
  bool const is_valid = m_state_machines.at ( idx ).m_machine.get_id().length()
                        && m_state_machines.at ( idx ).m_machine_data.get_decl().length()
                        && m_state_machines.at ( idx ).m_states.size()
                        && m_state_machines.at ( idx ).m_initial_state_name.length()
                        && m_state_machines.at ( idx ).m_transitions.size();
#ifndef NDEBUG

  if ( not is_valid )
  {
    std::cerr << "the '" << m_config_file_pathname << "' file does not contain valid machine structure." << std::endl;
  }

#endif
  return is_valid;
}

/* ------------------------------------------------------------------------- */

void cstmgen_json_machine_structure_t::load_from_file ( std::string const& config_file_pathname )
{
  std::ifstream in { config_file_pathname, std::ios::binary | std::ios::ate};

  if ( not in.is_open() )
  {
    std::cerr << "cannot open the '" << config_file_pathname << "' file." << std::endl;
    return;
  }

  size_t const in_length = in.tellg();
  in.seekg ( 0, std::ios::beg );

  buffer_t buff ( in_length + 1 );

  in.read ( buff.data(), buff.size() );

  if ( not load_from_buffer ( buff ) )
  {
#ifndef NDEBUG
    std::cerr
        << "the '" << config_file_pathname << "' config file does not contain relevant machine structure or is empty."
        << std::endl;
#endif
  }
}

/* ------------------------------------------------------------------------- */

struct json_parser_t
{
  using document_t = std::shared_ptr<rapidjson::Document>;
  using machine_property_t = std::optional<cstmgen_json_machine_structure_t::machine_property_t>;
  using machine_data_t = std::optional<cstmgen_json_machine_structure_t::machine_data_t>;
  using state_property_t = std::optional<cstmgen_json_machine_structure_t::state_property_t>;
  using transition_property_t = std::optional<cstmgen_json_machine_structure_t::transition_property_t>;
  using string_t = std::optional<std::string>;

  json_parser_t ( cstmgen_json_machine_structure_t& jms )
    : m_jms ( jms )
  {
    /* EMPTY */
  }

  std::string get_string_if_exists ( rapidjson::Value& obj, std::string_view const& token ) const
  {
    auto get_string_by_iter_if_exists = [& obj] ( auto & it )->std::string
    {
      if ( obj.MemberEnd() == it or not it->value.IsString() )
      {
        return {};
      }
      else
      {
        return {it->value.GetString() };
      }
    };

    auto get_string_if_exists = [&obj, &get_string_by_iter_if_exists] ( auto & token )->std::string
    {
      rapidjson::Value::ConstMemberIterator it = obj.FindMember ( token.data() );
      return get_string_by_iter_if_exists ( it );
    };

    return get_string_if_exists ( token );
  }

  document_t parse_buffer ( cstmgen_json_machine_structure_t::buffer_t const& buff )
  {
    m_document = std::make_shared<rapidjson::Document>();

    m_document->Parse ( buff.data() );

    return m_document;
  }

  machine_property_t
  get_machine_properties_from_obj ( rapidjson::Value& machine_obj ) const
  {
    machine_property_t result;

    do
    {
      if ( not machine_obj.IsObject() )
      {
#ifndef NDEBUG
        std::cerr
            << "the '" << m_jms.m_key_global_machine << "' property is not an object."
            << std::endl;
#endif
        break;
      }

      if ( not get_string_if_exists ( machine_obj, m_jms.m_key_state_id ).length() )
      {
#ifndef NDEBUG
        std::cerr
            << "item of the '" << m_jms.m_key_global_machine << "' does not have expected members."
            << std::endl;
#endif
        break;
      }

      result.emplace ( get_string_if_exists ( machine_obj, m_jms.m_key_state_id ),
                       get_string_if_exists ( machine_obj, m_jms.m_key_coord_x ),
                       get_string_if_exists ( machine_obj, m_jms.m_key_coord_y )
                     );
    }
    while ( false );

    return result;
  }

  machine_data_t
  get_machine_data_from_obj ( rapidjson::Value& machine_data_obj ) const
  {
    machine_data_t result;

    do
    {
      if ( not machine_data_obj.IsObject() )
      {
#ifndef NDEBUG
        std::cerr
            << "the '" << m_jms.m_key_global_machine_data << "' property is not an object."
            << std::endl;
#endif
        break;
      }

      if ( not get_string_if_exists ( machine_data_obj, m_jms.m_key_data_user_decl ).length()
           or not get_string_if_exists ( machine_data_obj, m_jms.m_key_data_user_init ).length() )
      {
#ifndef NDEBUG
        std::cerr
            << "item of the '" << m_jms.m_key_global_machine_data << "' does not have expected members."
            << std::endl;
#endif
        break;
      }

      result.emplace (
        get_string_if_exists ( machine_data_obj, m_jms.m_key_data_user_decl ),
        get_string_if_exists ( machine_data_obj, m_jms.m_key_data_user_init ),
        get_string_if_exists ( machine_data_obj, m_jms.m_key_coord_x ),
        get_string_if_exists ( machine_data_obj, m_jms.m_key_coord_y )
      );
    }
    while ( false );

    return result;
  }

  state_property_t
  get_state_properties_from_obj ( rapidjson::Value& state_obj ) const
  {
    state_property_t result;

    do
    {
      if ( not state_obj.IsObject() )
      {
#ifndef NDEBUG
        std::cerr
            << "item of the '" << m_jms.m_key_global_states << "' array is not a object."
            << std::endl;
#endif
        break;
      }

      if ( not get_string_if_exists ( state_obj, m_jms.m_key_state_id ).length()
           or
           not get_string_if_exists ( state_obj, m_jms.m_key_state_numeric_value ).length() )
      {
#ifndef NDEBUG
        std::cerr
            << "item of the '" << m_jms.m_key_global_states << "' does not have expected members."
            << std::endl;
#endif
        break;
      }

      result.emplace (
        get_string_if_exists ( state_obj, m_jms.m_key_state_id ),
        get_string_if_exists ( state_obj, m_jms.m_key_state_numeric_value ),
        get_string_if_exists ( state_obj, m_jms.m_key_state_user_code_global ),
        get_string_if_exists ( state_obj, m_jms.m_key_state_user_code_enter ),
        get_string_if_exists ( state_obj, m_jms.m_key_state_user_code_input ),
        get_string_if_exists ( state_obj, m_jms.m_key_state_user_code_run ),
        get_string_if_exists ( state_obj, m_jms.m_key_state_user_code_output ),
        get_string_if_exists ( state_obj, m_jms.m_key_state_user_code_leave ),
        get_string_if_exists ( state_obj, m_jms.m_key_coord_x ),
        get_string_if_exists ( state_obj, m_jms.m_key_coord_y )
      );
    }
    while ( false );

    return result;
  }

  transition_property_t
  get_transition_properties_from_obj ( rapidjson::Value& transition_obj ) const
  {
    transition_property_t result;

    do
    {
      if ( not transition_obj.IsObject() )
      {
#ifndef NDEBUG
        std::cerr
            << "item of the '" << m_jms.m_key_global_transitions << "' array is not a object."
            << std::endl;
#endif
        break;
      }

      if ( not get_string_if_exists ( transition_obj, m_jms.m_key_transition_from ).length() or
           not get_string_if_exists ( transition_obj, m_jms.m_key_transition_to ).length() )
      {
#ifndef NDEBUG
        std::cerr
            << "item of the '" << m_jms.m_key_global_transitions << "' does not have expected members."
            << std::endl;
#endif
        break;
      }

      result.emplace (
        get_string_if_exists ( transition_obj, m_jms.m_key_transition_from ),
        get_string_if_exists ( transition_obj, m_jms.m_key_transition_to ),
        get_string_if_exists ( transition_obj, m_jms.m_key_transition_condition_user_code )
      );
    }
    while ( false );

    return result;
  }

  string_t get_initial_state_from_obj ( rapidjson::Value& state_machine_obj ) const
  {
    string_t result;

    do
    {
      if ( not get_string_if_exists ( state_machine_obj, m_jms.m_key_global_initial_state ).length() )
      {
#ifndef NDEBUG
        std::cerr << "the '" << m_jms.m_key_global_initial_state << "' property is not a string." << std::endl;
#endif
        break;
      }

      result.emplace ( get_string_if_exists ( state_machine_obj, m_jms.m_key_global_initial_state ) );
    }
    while ( false );

    return result;
  }

private:
  cstmgen_json_machine_structure_t& m_jms;
  document_t m_document;
};

/* ------------------------------------------------------------------------- */

bool cstmgen_json_machine_structure_t::load_from_buffer ( buffer_t const& buff )
{
  json_parser_t json_parser ( *this );

  json_parser_t::document_t json_document = json_parser.parse_buffer ( buff );

  if ( not json_document or json_document->HasParseError() )
  {
#ifndef NDEBUG
    std::cerr
        << "the input does not contain relevant machine structure or is empty."
        << std::endl;
#endif
    return false;
  }

  auto& json_document_ref = ( *json_document.get() );

  if ( json_document_ref.HasMember ( m_key_global_state_machines.data() ) )
  {
    // retrieve the "state-machines"
    rapidjson::Value& array_of_state_machines = json_document_ref[m_key_global_state_machines.data()];

    if ( not array_of_state_machines.IsArray() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_state_machines << "' property is not an array." << std::endl;
#endif
      return false;
    }

    for ( rapidjson::Value::ValueIterator state_machine_itr = array_of_state_machines.Begin();
          state_machine_itr != array_of_state_machines.End();
          ++state_machine_itr )
    {
      rapidjson::Value& state_machine_obj = *state_machine_itr;

      if ( not state_machine_obj.IsObject() )
      {
#ifndef NDEBUG
        std::cerr << "item of the '" << m_key_global_state_machines << "' array is not a object." << std::endl;
#endif
        continue;
      }

      state_machine_t state_machine;

      if ( state_machine_obj.HasMember ( m_key_global_machine.data() ) )
      {
        // retrieve the "machine"
        auto const optional_machine_properties = json_parser.get_machine_properties_from_obj (
              state_machine_obj[m_key_global_machine.data()] );

        if ( not optional_machine_properties )
        {
          return false;
        }

        state_machine.m_machine = optional_machine_properties.value();
      }

      if ( state_machine_obj.HasMember ( m_key_global_machine_data.data() ) )
      {
        // retrieve the "machine-data"
        auto const optional_machine_data = json_parser.get_machine_data_from_obj (
                                             state_machine_obj[m_key_global_machine_data.data()] );

        if ( not optional_machine_data )
        {
          return false;
        }

        state_machine.m_machine_data = optional_machine_data.value();
      }

      if ( state_machine_obj.HasMember ( m_key_global_states.data() ) )
      {
        // retrieve the "states"
        rapidjson::Value& array_of_states = state_machine_obj[m_key_global_states.data()];

        if ( not array_of_states.IsArray() )
        {
#ifndef NDEBUG
          std::cerr << "the '" << m_key_global_states << "' property is not an array." << std::endl;
#endif
          return false;
        }

        for ( rapidjson::Value::ValueIterator states_itr = array_of_states.Begin();
              states_itr != array_of_states.End();
              ++states_itr )
        {
          rapidjson::Value& state_obj = *states_itr;

          auto const optional_state_properties = json_parser.get_state_properties_from_obj ( state_obj );

          if ( not optional_state_properties )
          {
            return false;
          }

          state_property_t state_property ( optional_state_properties.value() );

          state_machine.m_states.insert (
            std::make_pair ( state_property.get_id(),
                             std::make_shared<state_property_t> ( state_property ) ) );
        } // for states_itr
      }

      if ( state_machine_obj.HasMember ( m_key_global_initial_state.data() ) )
      {
        // retrieve the "initial-state"
        auto const optional_initial_state = json_parser.get_initial_state_from_obj ( state_machine_obj );

        if ( not optional_initial_state )
        {
          return false;
        }

        state_machine.m_initial_state_name = optional_initial_state.value();

        if ( not state_machine.m_initial_state_name.length() )
        {
#ifndef NDEBUG
          std::cerr << "the '" << m_key_global_initial_state << "' property is empty." << std::endl;
#endif
          return false;
        }
      }

      if ( state_machine_obj.HasMember ( m_key_global_transitions.data() ) )
      {
        // retrieve the "transitions"
        rapidjson::Value& array_of_transitions = state_machine_obj[m_key_global_transitions.data()];

        if ( not array_of_transitions.IsArray() )
        {
#ifndef NDEBUG
          std::cerr << "the '" << m_key_global_transitions << "' property is not an array." << std::endl;
#endif
          return false;
        }

        for ( rapidjson::Value::ValueIterator transitions_itr = array_of_transitions.Begin();
              transitions_itr != array_of_transitions.End();
              ++transitions_itr )
        {
          rapidjson::Value& transition_obj = *transitions_itr;

          auto const optional_transition_properties = json_parser.get_transition_properties_from_obj ( transition_obj );

          if ( not optional_transition_properties )
          {
            return false;
          }

          transition_property_t transition_properties ( optional_transition_properties.value() );

          state_machine.m_transitions.insert ( std::make_pair ( transition_properties.get_state_from(),
                                               std::make_shared<transition_property_t> ( transition_properties ) ) );
        } // for transitions_itr
      }

      m_state_machines.push_back ( state_machine );

    } // for state_machine_itr
  }

  return true;
}

/* ------------------------------------------------------------------------- */

} // namespace cfg
