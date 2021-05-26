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

std::string cstmgen_params_t::get_usage_text()
{
  std::stringstream ss;
  ss
      << m_param_json_machine_config_file << " File pathname to the state machine structure description in JSON format" <<
      std::endl;
  ss
      << m_param_state_user_code_folder << " Folder where to search for the state implementation user code files" <<
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

bool cstmgen_params_t::is_valid() const
{

  bool const is_valid = m_is_valid_config_file_name
                        &&
                        m_is_valid_state_user_code_folder
                        &&
                        (
                          m_is_valid_produce_state_enum
                          ||
                          m_is_valid_produce_state_header
                          ||
                          m_is_valid_produce_state_diagram_header
                          ||
                          m_is_valid_produce_state_machine_data_header
                          ||
                          m_is_valid_produce_state_implementation
                          ||
                          m_is_valid_produce_state_diagram_implementation
                          ||
                          m_is_valid_produce_state_machine_data_implementation
                        );

  return is_valid;
}

/* ------------------------------------------------------------------------- */

void cstmgen_params_t::process_params()
{
  m_error_message_text.clear();

  auto append_error_message_text = [this] ( std::string const & msg_txt )
  {
    m_error_message_text += ( m_error_message_text.length() ) ? ( " " ) : ( "" );
    m_error_message_text += msg_txt;
  };

  if ( m_args.size() < 1 )
  {
    append_error_message_text ( "Too few parameters provided." );
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
      else if ( p.starts_with ( m_param_state_user_code_folder ) )
      {
        m_state_user_code_folder.assign ( p.substr ( m_param_state_user_code_folder.length() ) );
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
        std::string e ( "Unknown option: '" );
        e += p;
        e += "' detected.";
        append_error_message_text ( e );
      }
    }

    m_is_valid_config_file_name = get_json_machine_config_file_name().length();

    if ( not m_is_valid_config_file_name )
    {
      append_error_message_text ( "Configuration file name is invalid." );
    }

    m_is_valid_state_user_code_folder = get_state_user_code_folder_path().length();

    if ( not m_is_valid_state_user_code_folder )
    {
      append_error_message_text ( "Missing state implementation user code folder." );
    }

    m_is_valid_produce_state_enum =
      (
        is_produce_state_enum()
        &&
        get_header_folder_name().length()
      );

    if ( is_produce_state_enum() && not m_is_valid_produce_state_enum )
    {
      append_error_message_text ( "Missing header folder name for the state enum." );
    }

    m_is_valid_produce_state_header =
      (
        is_produce_state_header()
        &&
        get_header_folder_name().length()
      );

    if ( is_produce_state_header() && not m_is_valid_produce_state_header )
    {
      append_error_message_text ( "Missing header folder name for the state header." );
    }

    m_is_valid_produce_state_diagram_header =
      (
        is_produce_state_diagram_header()
        &&
        get_header_folder_name().length()
      );

    if ( is_produce_state_diagram_header() && not m_is_valid_produce_state_diagram_header )
    {
      append_error_message_text ( "Missing header folder name for the state diagram header." );
    }

    m_is_valid_produce_state_machine_data_header =
      (
        is_produce_state_machine_data_header()
        &&
        get_header_folder_name().length()
      );

    if ( is_produce_state_machine_data_header() && not m_is_valid_produce_state_machine_data_header )
    {
      append_error_message_text ( "Missing header folder name for the state machine data header." );
    }

    m_is_valid_produce_state_implementation =
      (
        is_produce_state_implementation()
        &&
        get_implementation_folder_name().length()
      );

    if ( is_produce_state_implementation() && not m_is_valid_produce_state_implementation )
    {
      append_error_message_text ( "Missing implementation folder name for the state implementation." );
    }

    m_is_valid_produce_state_diagram_implementation =
      (
        is_produce_state_diagram_implementation()
        &&
        get_implementation_folder_name().length()
      );

    if ( is_produce_state_diagram_implementation() && not m_is_valid_produce_state_diagram_implementation )
    {
      append_error_message_text ( "Missing implementation folder name for the state diagram implementation." );
    }

    m_is_valid_produce_state_machine_data_implementation =
      (
        is_produce_state_machine_data_implementation()
        &&
        get_implementation_folder_name().length()
      );

    if ( is_produce_state_machine_data_implementation() && not m_is_valid_produce_state_machine_data_implementation )
    {
      append_error_message_text ( "Missing implementation folder name for the state machine data implementation." );
    }
  }
}

/* ------------------------------------------------------------------------- */

} // namespace cfg
