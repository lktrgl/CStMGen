#pragma once

#include <string>
#include <string_view>
#include <map>
#include <vector>

namespace cfg
{

class json_machine_structure_t final
{
  using state_id_t = std::string;
  using state_value_t = std::string;
  using states_t = std::map<state_id_t, state_value_t>;
  using transitions_t = std::multimap<state_id_t, state_id_t>;

  constexpr static std::string_view const m_key_machine_name = "machine-name";
  constexpr static std::string_view const m_key_states = "states";
  constexpr static std::string_view const m_key_transitions = "transitions";

  constexpr static std::string_view const m_key_id = "id";
  constexpr static std::string_view const m_key_value = "value";

  constexpr static std::string_view const m_key_from = "from";
  constexpr static std::string_view const m_key_to = "to";

  states_t const& get_states() const
  {
    return m_states;
  }
  transitions_t const& get_transitions_from() const
  {
    return m_transitions_from;
  }

public:
  json_machine_structure_t ( std::string const& config_file_pathname );

  json_machine_structure_t ( json_machine_structure_t const& ) = delete;
  json_machine_structure_t& operator= ( json_machine_structure_t const& ) = delete;
  json_machine_structure_t ( json_machine_structure_t&& ) = delete;
  json_machine_structure_t& operator= ( json_machine_structure_t&& ) = delete;

private:
  void import ( std::string const& config_file_pathname );

private:
  std::string const m_config_file_pathname;

  std::string m_machine_name;
  states_t m_states;
  transitions_t m_transitions_from;
};

} // namespace cfg
