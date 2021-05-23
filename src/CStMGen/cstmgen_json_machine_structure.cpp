#include <CStMGen/cstmgen_json_machine_structure.h>

#include <rapidjson/document.h>

#include <iostream>
#include <fstream>
#include <algorithm>

/* ------------------------------------------------------------------------- */

namespace cfg
{

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_user_property_names_t const
cstmgen_json_machine_structure_t::m_state_user_property_names =
{
  m_key_state_user_code_global,
  m_key_state_user_code_enter,
  m_key_state_user_code_input,
  m_key_state_user_code_run,
  m_key_state_user_code_output,
  m_key_state_user_code_leave
};

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_property_t::state_property_t ( state_value_t value,
    state_user_code_t user_code_global,
    state_user_code_t user_code_enter,
    state_user_code_t user_code_input,
    state_user_code_t user_code_run,
    state_user_code_t user_code_output,
    state_user_code_t user_code_leave )
  : m_value ( value )
  , m_user_code_global ( user_code_global )
  , m_user_code_enter ( user_code_enter )
  , m_user_code_input ( user_code_input )
  , m_user_code_run ( user_code_run )
  , m_user_code_output ( user_code_output )
  , m_user_code_leave ( user_code_leave )
{
  /* EMPTY */
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::state_property_t::get_property ( std::string const& name ) const
{
  if ( not name.compare ( m_key_state_numeric_value ) )
  {
    return m_value;
  }
  else if ( not name.compare ( m_key_state_user_code_global ) )
  {
    return m_user_code_global;
  }
  else if ( not name.compare ( m_key_state_user_code_enter ) )
  {
    return m_user_code_enter;
  }
  else if ( not name.compare ( m_key_state_user_code_input ) )
  {
    return m_user_code_input;
  }
  else if ( not name.compare ( m_key_state_user_code_run ) )
  {
    return m_user_code_run;
  }
  else if ( not name.compare ( m_key_state_user_code_output ) )
  {
    return m_user_code_output;
  }
  else if ( not name.compare ( m_key_state_user_code_leave ) )
  {
    return m_user_code_leave;
  }

  return m_value;
}

/* ------------------------------------------------------------------------- */

std::string const&
cstmgen_json_machine_structure_t::state_property_t::get_value() const
{
  return m_value;
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
  return m_machine_name;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::states_t const&
cstmgen_json_machine_structure_t::get_states() const
{
  return m_states;
}

/* ------------------------------------------------------------------------- */

cstmgen_json_machine_structure_t::state_user_property_names_t const&
cstmgen_json_machine_structure_t::get_state_user_property_names() const
{
  return m_state_user_property_names;
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
  bool const is_valid = m_machine_name.length()
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
    // retrieve the "machine-name"
    rapidjson::Value& s = d[m_key_global_machine_name.data()];

    if ( not s.IsString() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_machine_name << "' property is not a string." << std::endl;
#endif
      return;
    }

    m_machine_name = s.GetString();

    if ( not m_machine_name.length() )
    {
#ifndef NDEBUG
      std::cerr << "the '" << m_key_global_machine_name << "' property is empty." << std::endl;
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
        get_string_if_exists ( m_key_state_user_code_leave )
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

      rapidjson::Value::ConstMemberIterator from = obj.FindMember ( m_key_transition_from.data() );
      rapidjson::Value::ConstMemberIterator to = obj.FindMember ( m_key_transition_to.data() );

      if ( obj.MemberEnd() == from or not from->value.IsString()
           or obj.MemberEnd() == to or not to->value.IsString() )
      {
#ifndef NDEBUG
        std::cerr << "item of the '" << m_key_global_transitions << "' does not have expected members." << std::endl;
#endif
        continue;
      }

      m_transitions.insert ( std::make_pair ( from->value.GetString(), to->value.GetString() ) );
    } // for itr
  }
}

/* ------------------------------------------------------------------------- */

} // namespace cfg
