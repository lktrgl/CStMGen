#ifndef CSTMGEN_CSTMGEN_PROCESS_UTILS_CPP_INCLUDED
#define CSTMGEN_CSTMGEN_PROCESS_UTILS_CPP_INCLUDED

/* ------------------------------------------------------------------------- */

#include <CStMGen/cstmgen_process.h>

/* ------------------------------------------------------------------------- */

#include <fstream>

/* ------------------------------------------------------------------------- */

namespace gen::utils
{

/* ------------------------------------------------------------------------- */

template<typename BUFFER, typename STRING, typename STRING_VIEW>
template<char const* const& VAR_NAME>
void cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::find_and_process_upper_var ( buffer_t& buffer,
    cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::string_t const& replacement_str ) const
{
  constexpr cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::string_view_t const target_str{VAR_NAME};

  auto local_replacement_str{replacement_str};
  convert_to_upper_case_inplace ( local_replacement_str );

  replace_all_occurences_inplace ( buffer, target_str, local_replacement_str );
}

/* ------------------------------------------------------------------------- */

template<typename BUFFER, typename STRING, typename STRING_VIEW>
template<char const* const& VAR_NAME>
void cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::find_and_process_lower_var ( buffer_t& buffer,
    cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::string_t const& replacement_str ) const
{
  constexpr cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::string_view_t const target_str{VAR_NAME};

  auto local_replacement_str{replacement_str};
  convert_to_lower_case_inplace ( local_replacement_str );

  replace_all_occurences_inplace ( buffer, target_str, local_replacement_str );
}

/* ------------------------------------------------------------------------- */

template<typename BUFFER, typename STRING, typename STRING_VIEW>
template <typename TARGET_STR_T, typename REPLACEMENT_STR_T>
void cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::replace_all_occurences_inplace ( buffer_t& buffer,
    TARGET_STR_T const& target_str,
    REPLACEMENT_STR_T const& replacement_str ) const
{
  for ( auto pos = buffer.find ( target_str, 0 );
        cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::string_t::npos != pos;
        pos = buffer.find ( target_str, 0 ) )
  {
    buffer.replace ( pos, target_str.size(), replacement_str );
  }
}

/* ------------------------------------------------------------------------- */

template<typename BUFFER, typename STRING, typename STRING_VIEW>
bool cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::get_text_file_contents (
  cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::string_t const& file_pathname,
  buffer_t& buffer ) const
{
  bool result = false;

  if ( file_pathname.length() )
  {
    std::ifstream in ( file_pathname, std::ios::in );

    if ( in.good() )
    {
      cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::string_t tmp;
      bool is_first = true;

      do
      {
        if ( not is_first )
        {
          buffer.append ( "\n" );
        }

        is_first = false;

        std::getline ( in, tmp );

        buffer.append ( tmp );
      }
      while ( not in.eof() );

      result = true;
    }
  }

  return result;
}

/* ------------------------------------------------------------------------- */

template<typename BUFFER, typename STRING, typename STRING_VIEW>
void cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::convert_to_lower_case_inplace ( buffer_t& buffer ) const
{
  auto& f = std::use_facet<std::ctype<char>> ( std::locale() );
  f.tolower ( buffer.data(), buffer.data() + buffer.size() );
}

/* ------------------------------------------------------------------------- */

template<typename BUFFER, typename STRING, typename STRING_VIEW>
void cstmgen_process_utils_t<BUFFER, STRING, STRING_VIEW>::convert_to_upper_case_inplace ( buffer_t& buffer ) const
{
  auto& f = std::use_facet<std::ctype<char>> ( std::locale() );
  f.toupper ( buffer.data(), buffer.data() + buffer.size() );
}

/* ------------------------------------------------------------------------- */

} // namespace gen::utils

#endif /*CSTMGEN_CSTMGEN_PROCESS_UTILS_CPP_INCLUDED*/
