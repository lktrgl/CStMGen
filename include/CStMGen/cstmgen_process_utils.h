#pragma once

/* ------------------------------------------------------------------------- */

namespace gen::utils
{

/* ------------------------------------------------------------------------- */

template<typename BUFFER, typename STRING, typename STRING_VIEW>
struct cstmgen_process_utils_t
{
  using buffer_t = BUFFER;
  using string_t = STRING;
  using string_view_t = STRING_VIEW;

  cstmgen_process_utils_t() = default;
  cstmgen_process_utils_t ( cstmgen_process_utils_t const& ) = delete;
  cstmgen_process_utils_t& operator= ( cstmgen_process_utils_t const& ) = delete;
  cstmgen_process_utils_t ( cstmgen_process_utils_t&& ) = delete;
  cstmgen_process_utils_t& operator= ( cstmgen_process_utils_t&& ) = delete;

  template<char const* const& VAR_NAME>
  void find_and_process_upper_var ( buffer_t& buffer,
                                    string_t const& replacement_str ) const;

  template<char const* const& VAR_NAME>
  void find_and_process_lower_var ( buffer_t& buffer,
                                    string_t const& replacement_str ) const;

  template <typename TARGET_STR_T, typename REPLACEMENT_STR_T>
  void replace_all_occurences_inplace ( buffer_t& buffer,
                                        TARGET_STR_T const& target_str,
                                        REPLACEMENT_STR_T const& replacement_str ) const;

  bool get_text_file_contents ( string_t const& file_pathname,
                                buffer_t& buffer ) const;

  void convert_to_lower_case_inplace ( buffer_t& buffer ) const;
  void convert_to_upper_case_inplace ( buffer_t& buffer ) const;
};

/* ------------------------------------------------------------------------- */

} // namespace gen::utils
