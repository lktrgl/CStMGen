#pragma once

#include <string>
#include <string_view>
#include <map>
#include <vector>

/* ------------------------------------------------------------------------- */

namespace cfg
{

/* ------------------------------------------------------------------------- */

class json_machine_structure_t final
{
public:
  using state_id_t = std::string;
  using state_value_t = std::string;
  using states_t = std::map<state_id_t, state_value_t>;
  using states_sorted_t = std::vector<std::pair<state_id_t, state_value_t>>;
  using transitions_t = std::multimap<state_id_t, state_id_t>;

public:
  json_machine_structure_t ( std::string const& config_file_pathname );

  json_machine_structure_t ( json_machine_structure_t const& ) = delete;
  json_machine_structure_t& operator= ( json_machine_structure_t const& ) = delete;
  json_machine_structure_t ( json_machine_structure_t&& ) = delete;
  json_machine_structure_t& operator= ( json_machine_structure_t&& ) = delete;

  std::string const& get_machine_name() const
  {
    return m_machine_name;
  }
  states_t const& get_states() const
  {
    return m_states;
  }
  states_sorted_t get_states_sorted() const;
  transitions_t const& get_transitions_from() const
  {
    return m_transitions_from;
  }

  bool valid() const
  {
    bool const is_valid = m_machine_name.length()
                          && m_states.size()
                          && m_transitions_from.size();
    return is_valid;
  }

private:
  void import ( std::string const& config_file_pathname );

private:
  std::string const m_config_file_pathname;

  std::string m_machine_name;
  states_t m_states;
  transitions_t m_transitions_from;

  constexpr static std::string_view const m_key_machine_name = "machine-name";
  constexpr static std::string_view const m_key_states = "states";
  constexpr static std::string_view const m_key_transitions = "transitions";

  constexpr static std::string_view const m_key_id = "id";
  constexpr static std::string_view const m_key_value = "value";

  constexpr static std::string_view const m_key_from = "from";
  constexpr static std::string_view const m_key_to = "to";

};

/* ------------------------------------------------------------------------- */

} // namespace cfg
