#include <CStMGen/json_machine_structure.h>

#include <rapidjson/document.h>

#include <iostream>
#include <fstream>
#include <algorithm>

/* ------------------------------------------------------------------------- */

namespace cfg
{

/* ------------------------------------------------------------------------- */

json_machine_structure_t::json_machine_structure_t ( std::string const& config_file_pathname )
  : m_config_file_pathname ( config_file_pathname )
{
  import ( m_config_file_pathname );
}

/* ------------------------------------------------------------------------- */

json_machine_structure_t::states_sorted_t
json_machine_structure_t::get_states_sorted() const
{
  states_sorted_t result{m_states.cbegin(), m_states.cend() };
  std::sort ( result.begin(), result.end(), [] ( auto const & left, auto const & right )
  {
    auto const left_value = std::strtoul ( left.second.c_str(), nullptr, 10 );
    auto const right_value = std::strtoul ( right.second.c_str(), nullptr, 10 );
    return left_value < right_value;
  } );
  return result;
}

/* ------------------------------------------------------------------------- */

void json_machine_structure_t::import ( std::string const& config_file_pathname )
{
  std::ifstream in { config_file_pathname, std::ios::binary | std::ios::ate};

  if ( !in.is_open() )
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

  {
    // retrieve the "machine-name"
    rapidjson::Value& s = d[m_key_machine_name.data()];

    if ( not s.IsString() )
    {
      std::cerr << "the '" << m_key_machine_name << "' property is not a string." << std::endl;
      return;
    }

    m_machine_name = s.GetString();

    if ( not m_machine_name.length() )
    {
      std::cerr << "the '" << m_key_machine_name << "' property is empty." << std::endl;
      return;
    }
  }

  {
    // retrieve the "states"
    rapidjson::Value& a = d[m_key_states.data()];

    if ( not a.IsArray() )
    {
      std::cerr << "the '" << m_key_states << "' property is not an array." << std::endl;
      return;
    }

    for ( rapidjson::Value::ValueIterator itr = a.Begin(); itr != a.End(); ++itr )
    {
      rapidjson::Value& obj = *itr;

      if ( not obj.IsObject() )
      {
        std::cerr << "item of the '" << m_key_states << "' array is not a object." << std::endl;
        continue;
      }

      rapidjson::Value::ConstMemberIterator id = obj.FindMember ( m_key_id.data() );
      rapidjson::Value::ConstMemberIterator value = obj.FindMember ( m_key_value.data() );

      if ( obj.MemberEnd() == id or not id->value.IsString()
           or obj.MemberEnd() == value or not value->value.IsString() )
      {
        std::cerr << "item of the '" << m_key_states << "' does not have expected members." << std::endl;
        continue;
      }

      m_states.insert ( std::make_pair ( id->value.GetString(), value->value.GetString() ) );
    } // for itr
  }

  {
    // retrieve the "transitions"
    rapidjson::Value& a = d[m_key_transitions.data()];

    if ( not a.IsArray() )
    {
      std::cerr << "the '" << m_key_transitions << "' property is not an array." << std::endl;
      return;
    }

    for ( rapidjson::Value::ValueIterator itr = a.Begin(); itr != a.End(); ++itr )
    {
      rapidjson::Value& obj = *itr;

      if ( not obj.IsObject() )
      {
        std::cerr << "item of the '" << m_key_transitions << "' array is not a object." << std::endl;
        continue;
      }

      rapidjson::Value::ConstMemberIterator from = obj.FindMember ( m_key_from.data() );
      rapidjson::Value::ConstMemberIterator to = obj.FindMember ( m_key_to.data() );

      if ( obj.MemberEnd() == from or not from->value.IsString()
           or obj.MemberEnd() == to or not to->value.IsString() )
      {
        std::cerr << "item of the '" << m_key_transitions << "' does not have expected members." << std::endl;
        continue;
      }

      m_transitions_from.insert ( std::make_pair ( from->value.GetString(), to->value.GetString() ) );
    } // for itr
  }
}

/* ------------------------------------------------------------------------- */

} // namespace cfg
