#pragma once

#include <string>
#include <string_view>
#include <map>
#include <set>
#include <vector>
#include <memory>

/* ------------------------------------------------------------------------- */

namespace cfg
{

/* ------------------------------------------------------------------------- */

class cstmgen_json_machine_structure_t final
{
  constexpr static std::string_view const m_key_global_machine_name = "machine-name";
  constexpr static std::string_view const m_key_global_states = "states";
  constexpr static std::string_view const m_key_global_initial_state = "initial-state";
  constexpr static std::string_view const m_key_global_transitions = "transitions";

  constexpr static std::string_view const m_key_state_id = "id";
  constexpr static std::string_view const m_key_state_numeric_value = "value";
  constexpr static std::string_view const m_key_state_user_code_global = "user_code_global";
  constexpr static std::string_view const m_key_state_user_code_enter = "user_code_enter";
  constexpr static std::string_view const m_key_state_user_code_input = "user_code_input";
  constexpr static std::string_view const m_key_state_user_code_run = "user_code_run";
  constexpr static std::string_view const m_key_state_user_code_output = "user_code_output";
  constexpr static std::string_view const m_key_state_user_code_leave = "user_code_leave";

  constexpr static std::string_view const m_key_transition_from = "from";
  constexpr static std::string_view const m_key_transition_to = "to";

public:
  using state_id_t = std::string;
  using state_value_t = std::string;
  using state_user_code_t = std::string;

  struct state_property_t
  {
    state_property_t ( state_value_t value_,
                       state_user_code_t user_code_global_,
                       state_user_code_t user_code_enter_,
                       state_user_code_t user_code_input_,
                       state_user_code_t user_code_run_,
                       state_user_code_t user_code_output_,
                       state_user_code_t user_code_leave_ )
      : value ( value_ )
      , user_code_global ( user_code_global_ )
      , user_code_enter ( user_code_enter_ )
      , user_code_input ( user_code_input_ )
      , user_code_run ( user_code_run_ )
      , user_code_output ( user_code_output_ )
      , user_code_leave ( user_code_leave_ )
    {
      /* EMPTY */
    }

    state_value_t value;
    state_user_code_t user_code_global;
    state_user_code_t user_code_enter;
    state_user_code_t user_code_input;
    state_user_code_t user_code_run;
    state_user_code_t user_code_output;
    state_user_code_t user_code_leave;
  };

  using state_property_ptr = std::shared_ptr<state_property_t>;
  using states_t = std::map<state_id_t, state_property_ptr>;
  using state_user_property_names_t = std::set<std::string_view>;
  using states_sorted_t = std::vector<std::pair<state_id_t, state_property_ptr>>;
  using transitions_t = std::multimap<state_id_t, state_id_t>;

public:
  cstmgen_json_machine_structure_t ( std::string const& config_file_pathname );

  cstmgen_json_machine_structure_t ( cstmgen_json_machine_structure_t const& ) = delete;
  cstmgen_json_machine_structure_t& operator= ( cstmgen_json_machine_structure_t const& ) = delete;
  cstmgen_json_machine_structure_t ( cstmgen_json_machine_structure_t&& ) = delete;
  cstmgen_json_machine_structure_t& operator= ( cstmgen_json_machine_structure_t&& ) = delete;

  std::string const& get_machine_name() const;
  states_t const& get_states() const;
  state_user_property_names_t const& get_state_user_property_names() const;
  states_sorted_t get_states_sorted() const;
  std::string const& get_initial_state_name() const;
  transitions_t const& get_transitions() const;

  bool valid() const;

private:
  void import ( std::string const& config_file_pathname );

private:
  std::string const m_config_file_pathname;

  std::string m_machine_name;
  states_t m_states;
  std::string m_initial_state_name;
  transitions_t m_transitions;

  static state_user_property_names_t const m_state_user_property_names;
};

/* ------------------------------------------------------------------------- */

} // namespace cfg
