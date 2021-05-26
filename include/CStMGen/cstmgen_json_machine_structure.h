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
  constexpr static std::string_view const m_key_transition_condition_user_code = "condition_handler";

public:
  using state_id_t = std::string;
  using state_value_t = std::string;
  using state_user_code_t = std::string;

  struct state_property_t
  {
    state_property_t ( state_value_t value,
                       state_user_code_t user_code_global,
                       state_user_code_t user_code_enter,
                       state_user_code_t user_code_input,
                       state_user_code_t user_code_run,
                       state_user_code_t user_code_output,
                       state_user_code_t user_code_leave );

    state_property_t ( state_property_t const& other );
    state_property_t& operator= ( state_property_t const& other );

    state_property_t ( state_property_t&& ) = delete;
    state_property_t& operator= ( state_property_t&& ) = delete;

    std::string const& get_property ( std::string_view const& name ) const;
    std::string const& get_property ( std::string const& name ) const;
    std::string const& get_value() const;

  private:
    using property_map_t = std::map<std::string_view, std::string>;

  private:
    property_map_t m_property_map;
  };

  struct state_user_property_template_t
  {
    state_user_property_template_t ( uint8_t const* template_data_ptr,
                                     size_t template_data_len );

    state_user_property_template_t ( state_user_property_template_t const& ) = delete;
    state_user_property_template_t& operator= ( state_user_property_template_t const& ) = delete;
    state_user_property_template_t ( state_user_property_template_t&& ) = delete;
    state_user_property_template_t& operator= ( state_user_property_template_t&& ) = delete;

    uint8_t const* get_ptr() const;
    size_t get_length() const;

  private:
    uint8_t const* const m_template_data_ptr;
    size_t const m_template_data_len;
  };

  using state_property_ptr = std::shared_ptr<state_property_t>;
  using state_user_property_template_ptr = std::shared_ptr<state_user_property_template_t>;

  using states_t = std::map<state_id_t, state_property_ptr>;
  using state_user_property_templates_t = std::map<std::string_view, state_user_property_template_ptr>;
  using states_sorted_t = std::vector<std::pair<state_id_t, state_property_ptr>>;

  struct transition_property_t
  {
    transition_property_t ( std::string const& state_to,
                            std::string const& condition_code );

    transition_property_t ( transition_property_t const& ) = delete;
    transition_property_t& operator= ( transition_property_t const& ) = delete;
    transition_property_t ( transition_property_t&& ) = delete;
    transition_property_t& operator= ( transition_property_t&& ) = delete;

    std::string const& get_property ( std::string_view const& name ) const;
    std::string const& get_property ( std::string const& name ) const;
    std::string const& get_state_to() const;
    std::string const& get_condition_user_code() const;

  private:
    using property_map_t = std::map<std::string_view, std::string>;

  private:
    property_map_t m_property_map;
  };

  using transition_property_ptr = std::shared_ptr<transition_property_t>;
  using transitions_t = std::multimap<state_id_t, transition_property_ptr>;

public:
  cstmgen_json_machine_structure_t ( std::string const& config_file_pathname );

  cstmgen_json_machine_structure_t ( cstmgen_json_machine_structure_t const& ) = delete;
  cstmgen_json_machine_structure_t& operator= ( cstmgen_json_machine_structure_t const& ) = delete;
  cstmgen_json_machine_structure_t ( cstmgen_json_machine_structure_t&& ) = delete;
  cstmgen_json_machine_structure_t& operator= ( cstmgen_json_machine_structure_t&& ) = delete;

  std::string const& get_machine_name() const;
  states_t const& get_states() const;
  state_user_property_templates_t const& get_state_user_property_templates() const;
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

  static state_user_property_templates_t const m_state_user_property_templates;
};

/* ------------------------------------------------------------------------- */

} // namespace cfg
