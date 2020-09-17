#include <CStMGen/cstmgen_params.h>

#include <iostream>
#include <sstream>

/* ------------------------------------------------------------------------- */

namespace cfg
{

/* ------------------------------------------------------------------------- */

cstmgen_params_t::cstmgen_params_t ( int argc, char** argv )
  : m_args ( argv, argv + argc )
{
  process_params();
}

/* ------------------------------------------------------------------------- */

std::string cstmgen_params_t::usage()
{
  std::stringstream ss;
  ss
      << m_param_json_machine_config_file << " File pathname to the state machine structure description in JSON format" <<
      std::endl;
  ss
      << m_param_header_folder << " Folder pathname where to store the declaration files to" << std::endl;
  ss
      << m_param_implementation_folder << " Folder pathname where to store the implementation files to" << std::endl;
  ss
      << m_param_produce_all << " Whether producing all the file set" << std::endl;
  ss
      << m_param_produce_state_enum << " Whether producing a file with the state machine states enumeration" << std::endl;
  ss
      << m_param_produce_state_header << " Whether producing a file with the state machine state declaration per state" <<
      std::endl;
  ss
      << m_param_produce_state_implementation <<
      " Whether producing a file with the state machine state implementation per state" << std::endl;
  ss
      << m_param_produce_state_diagram_header << "Whether producing a file with the state diagram declaration" << std::endl;
  ss
      << m_param_produce_state_diagram_implementation << "Whether producing a file with the state diagram definition" <<
      std::endl;
  ss
      << m_param_produce_state_machine_data_header << "Whether producing a file with the state data declaration" << std::endl;
  ss
      << m_param_produce_state_machine_data_implementation << "Whether producing a file with the state data definition" <<
      std::endl;

  return ss.str();
}

/* ------------------------------------------------------------------------- */

bool cstmgen_params_t::valid() const
{
  bool const is_valid = get_json_machine_config_file().length()
                        &&
                        (
                          (
                            get_produce_state_enum()
                            &&
                            get_header_folder().length()
                          )
                          ||
                          (
                            get_produce_state_header()
                            &&
                            get_header_folder().length()
                          )
                          ||
                          (
                            get_produce_state_diagram_header()
                            &&
                            get_header_folder().length()
                          )
                          ||
                          (
                            get_produce_state_machine_data_header()
                            &&
                            get_header_folder().length()
                          )
                          ||
                          (
                            get_produce_state_implementation()
                            &&
                            get_implementation_folder().length()
                          )
                          ||
                          (
                            get_produce_state_diagram_implementation()
                            &&
                            get_implementation_folder().length()
                          )
                          ||
                          (
                            get_produce_state_machine_data_implementation()
                            &&
                            get_implementation_folder().length()
                          )
                        );

  return is_valid;
}

/* ------------------------------------------------------------------------- */

void cstmgen_params_t::process_params()
{
  if ( m_args.size() < 1 )
  {
#ifndef NDEBUG
    std::cerr << usage() << std::endl;
    std::cerr << "Too few parameters provided'" << std::endl;
#endif
  }
  else
  {
    for ( size_t i = 1; i < m_args.size(); ++i )
    {
      auto const p = m_args.at ( i );

      if ( p.starts_with ( m_param_json_machine_config_file ) )
      {
        m_json_machine_config_file.assign ( p.substr ( m_param_json_machine_config_file.length() ) );
      }
      else if ( p.starts_with ( m_param_header_folder ) )
      {
        m_header_folder.assign ( p.substr ( m_param_header_folder.length() ) );
      }
      else if ( p.starts_with ( m_param_implementation_folder ) )
      {
        m_implementation_folder.assign ( p.substr ( m_param_implementation_folder.length() ) );
      }
      else if ( m_param_produce_all == p )
      {
        m_produce_all.assign ( p );
      }
      else if ( m_param_produce_state_enum == p )
      {
        m_produce_state_enum.assign ( p );
      }
      else if ( m_param_produce_state_machine_data_header == p )
      {
        m_produce_state_machine_data_header.assign ( p );
      }
      else if ( m_param_produce_state_machine_data_implementation == p )
      {
        m_produce_state_machine_data_implementation.assign ( p );
      }
      else if ( m_param_produce_state_header == p )
      {
        m_produce_state_header.assign ( p );
      }
      else if ( m_param_produce_state_implementation == p )
      {
        m_produce_state_implementation.assign ( p );
      }
      else if ( m_param_produce_state_diagram_header == p )
      {
        m_produce_state_diagram_header.assign ( p );
      }
      else if ( m_param_produce_state_diagram_implementation == p )
      {
        m_produce_state_diagram_implementation.assign ( p );
      }
      else
      {
#ifndef NDEBUG
        std::cerr << usage() << std::endl;
        std::cerr << "Unknown option: '" << p << "'" << std::endl;
#endif
      }
    }
  }
}

/* ------------------------------------------------------------------------- */

} // namespace cfg
