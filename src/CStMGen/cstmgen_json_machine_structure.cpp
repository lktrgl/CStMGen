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

cstmgen_json_machine_structure_t::state_property_t::state_property_t ( state_value_t value,
    state_user_code_t user_code_global,
    state_user_code_t user_code_enter,
    state_user_code_t user_code_input,
    state_user_code_t user_code_run,
    state_user_code_t user_code_output,
    state_user_code_t user_code_leave,
    coord_t x,
    coord_t y )
{
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

cstmgen_json_machine_structure_t::transition_property_t::transition_property_t ( std::string const& state_to,
    std::string const& condition_code )
{
  m_property_map[m_key_transition_to] = state_to;
  m_property_map[m_key_transition_condition_user_code] = condition_code;
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
  import ( m_config_file_pathname );
}

/* ------------------------------------------------------------------------- */

std::string const& cstmgen_json_machine_structure_t::get_machine_name() const
{
  return m_machine.get_id();
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::machine_data_t const&
cstmgen_json_machine_structure_t::get_machine_data() const
{
  return m_machine_data;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::states_t const&
cstmgen_json_machine_structure_t::get_states() const
{
  return m_states;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_user_property_templates_t const&
cstmgen_json_machine_structure_t::get_state_user_property_templates() const
{
  return m_state_user_property_templates;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::states_sorted_t
cstmgen_json_machine_structure_t::get_states_sorted() const
{
  states_sorted_t result{m_states.cbegin(), m_states.cend() };

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

std::string const& cstmgen_json_machine_structure_t::get_initial_state_name() const
{
  return m_initial_state_name;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::transitions_t const&
cstmgen_json_machine_structure_t::get_transitions() const
{
  return m_transitions;
}

/* ------------------------------------------------------------------------- */

bool cstmgen_json_machine_structure_t::valid() const
{
  bool const is_valid = m_machine.get_id().length()
                        && m_machine_data.get_decl().length()
                        && m_states.size()
                        && m_initial_state_name.length()
                        && m_transitions.size();
#ifndef NDEBUG

  if ( not is_valid )
  {
    std::cerr << "the '" << m_config_file_pathname << "' file does not contain valid machine structure." << std::endl;
  }

#endif
  return is_valid;
}

/* ------------------------------------------------------------------------- */

void cstmgen_json_machine_structure_t::import ( std::string const& config_file_pathname )
{
  std::ifstream in { config_file_pathname, std::ios::binary | std::ios::ate};

  if ( not in.is_open() )
  {
    std::cerr << "cannot open the '" << config_file_pathname << "' file." << std::endl;
    return;
  }

  size_t const in_length = in.tellg();
  in.seekg ( 0, std::ios::beg );

  std::vector<char> buff ( in_length + 1 );

  in.read ( buff.data(), buff.size() );

  rapidjson::Document d;
  d.Parse ( buff.data() );

  if ( d.HasParseError() )
  {
#ifndef NDEBUG
    std::cerr
        << "the '" << config_file_pathname << "' file does not contain relevant machine structure or is empty."
        << std::endl;
#endif
    return;
  }

  {
    // retrieve the "machine"
    rapidjson::Value& obj = d[m_key_global_machine.data()];

    if ( not obj.IsObject() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_machine << "' property is not an object." << std::endl;
#endif
      return;
    }

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

    m_machine = machine_property_t
    {
      get_string_if_exists ( m_key_state_id ),
      get_string_if_exists ( m_key_coord_x ),
      get_string_if_exists ( m_key_coord_y )
    };

    if ( not m_machine.get_id().length() )
    {
#ifndef NDEBUG
      std::cerr << "item of the '" << m_key_global_machine << "' does not have expected members." << std::endl;
#endif
      return;
    }
  }

  {
    // retrieve the "machine-data"
    rapidjson::Value& obj = d[m_key_global_machine_data.data()];

    if ( not obj.IsObject() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_machine_data << "' property is not an object." << std::endl;
#endif
      return;
    }

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

    m_machine_data = machine_data_t
    {
      get_string_if_exists ( m_key_data_user_decl ),
      get_string_if_exists ( m_key_data_user_init ),
      get_string_if_exists ( m_key_coord_x ),
      get_string_if_exists ( m_key_coord_y )
    };

    if ( not m_machine_data.get_decl().length() or not m_machine_data.get_init().length() )
    {
#ifndef NDEBUG
      std::cerr << "item of the '" << m_key_global_machine_data << "' does not have expected members." << std::endl;
#endif
      return;
    }
  }

  {
    // retrieve the "states"
    rapidjson::Value& a = d[m_key_global_states.data()];

    if ( not a.IsArray() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_states << "' property is not an array." << std::endl;
#endif
      return;
    }

    for ( rapidjson::Value::ValueIterator itr = a.Begin(); itr != a.End(); ++itr )
    {
      rapidjson::Value& obj = *itr;

      if ( not obj.IsObject() )
      {
#ifndef NDEBUG
        std::cerr << "item of the '" << m_key_global_states << "' array is not a object." << std::endl;
#endif
        continue;
      }

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

      if ( not get_string_if_exists ( m_key_state_id ).length()
           or
           not get_string_if_exists ( m_key_state_numeric_value ).length() )
      {
#ifndef NDEBUG
        std::cerr << "item of the '" << m_key_global_states << "' does not have expected members." << std::endl;
#endif
        continue;
      }

      state_property_t
      state_property
      {
        get_string_if_exists ( m_key_state_numeric_value ),
        get_string_if_exists ( m_key_state_user_code_global ),
        get_string_if_exists ( m_key_state_user_code_enter ),
        get_string_if_exists ( m_key_state_user_code_input ),
        get_string_if_exists ( m_key_state_user_code_run ),
        get_string_if_exists ( m_key_state_user_code_output ),
        get_string_if_exists ( m_key_state_user_code_leave ),
        get_string_if_exists ( m_key_coord_x ),
        get_string_if_exists ( m_key_coord_y )
      };

      m_states.insert (
        std::make_pair ( get_string_if_exists ( m_key_state_id ), std::make_shared<state_property_t> ( state_property ) )
      );
    } // for itr
  }

  {
    // retrieve the "initial-state"
    rapidjson::Value& s = d[m_key_global_initial_state.data()];

    if ( not s.IsString() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_initial_state << "' property is not a string." << std::endl;
#endif
      return;
    }

    m_initial_state_name = s.GetString();

    if ( not m_initial_state_name.length() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_initial_state << "' property is empty." << std::endl;
#endif
      return;
    }
  }

  {
    // retrieve the "transitions"
    rapidjson::Value& a = d[m_key_global_transitions.data()];

    if ( not a.IsArray() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_transitions << "' property is not an array." << std::endl;
#endif
      return;
    }

    for ( rapidjson::Value::ValueIterator itr = a.Begin(); itr != a.End(); ++itr )
    {
      rapidjson::Value& obj = *itr;

      if ( not obj.IsObject() )
      {
#ifndef NDEBUG
        std::cerr << "item of the '" << m_key_global_transitions << "' array is not a object." << std::endl;
#endif
        continue;
      }

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

      if ( not get_string_if_exists ( m_key_transition_from ).length() or
           not get_string_if_exists ( m_key_transition_to ).length() )
      {
#ifndef NDEBUG
        std::cerr << "item of the '" << m_key_global_transitions << "' does not have expected members." << std::endl;
#endif
        continue;
      }

      m_transitions.insert ( std::make_pair ( get_string_if_exists ( m_key_transition_from ),
                                              std::make_shared<transition_property_t> (
                                                  get_string_if_exists ( m_key_transition_to ),
                                                  get_string_if_exists ( m_key_transition_condition_user_code )
                                              ) ) );
    } // for itr
  }
}

/* ------------------------------------------------------------------------- */

} // namespace cfg
