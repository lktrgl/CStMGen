cmake_minimum_required(VERSION 3.5)

project ( CStMGen )

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

if(NOT IS_SUBPROJECT)
	set ( CMAKE_C_STANDARD 99 )
	set ( CMAKE_CXX_STANDARD 20 )
	set ( CMAKE_C_FLAGS "-Wall -Wextra -Werror -g3 -o0" )
	set ( CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g3 -o0" )
else()
	set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG" )
	set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG" )
endif()

add_subdirectory( contrib/lggm )

include_directories (
     include
     contrib/lggm/include
     contrib/rapidjson/include
     )

set (conv_util data/templates/conv/template_to_hex.sh)
set (ascii_files_src_folder data/templates)
set (hex_files_dest_folder include/CStMGen)

set (ascii_to_hex_files_sources
  #state machine enum
  state_machine_enum/cstm_state_enum_template_h
  state_machine_enum/cstm_state_enum_state_name_text
  state_machine_enum/cstm_state_enum_file_name_template_h

  #state machine data
  state_machine_data/cstm_state_data_desc_template_h
  state_machine_data/cstm_state_data_desc_template_c
  state_machine_data/cstm_state_data_desc_file_name_template_h
  state_machine_data/cstm_state_data_desc_file_name_template_c
  state_machine_data/cstm_state_data_decl_placeholder_name_template
  state_machine_data/cstm_state_data_init_placeholder_name_template
 
  #state diagram code
  state_diagram_code/cstm_state_diagram_template_h
  state_diagram_code/cstm_state_diagram_template_c
  state_diagram_code/cstm_state_diagram_file_name_template_h
  state_diagram_code/cstm_state_diagram_file_name_template_c
  state_diagram_code/cstm_state_include_text_template
  state_diagram_code/cstm_state_node_text_template

  #state code
  state_code/cstm_state_template_h
  state_code/cstm_state_template_c
  state_code/cstm_state_file_name_template_h
  state_code/cstm_state_file_name_template_c
  state_code/cstm_state_transition_template_c
  state_code/cstm_state_transition_name_template
  state_code/cstm_state_transition_evaluation_placeholder_name_template
  state_code/cstm_state_global_data_placeholder_name_template
  state_code/cstm_state_handler_enter_placeholder_name_template
  state_code/cstm_state_handler_input_placeholder_name_template
  state_code/cstm_state_handler_leave_placeholder_name_template
  state_code/cstm_state_handler_output_placeholder_name_template
  state_code/cstm_state_handler_run_placeholder_name_template
)

set(ascii_to_hex_files_outputs)
foreach(x_ascii_file ${ascii_to_hex_files_sources})
    set(x_ascii_file "${ascii_files_src_folder}/${x_ascii_file}")
    set(x_hex_file "${hex_files_dest_folder}/${x_ascii_file}.h")
    add_custom_command(OUTPUT ${x_hex_file}

        #dummy all the output folders creation
        COMMAND mkdir -vp ${hex_files_dest_folder}/data/templates
        COMMAND mkdir -vp ${hex_files_dest_folder}/data/templates/state_machine_enum
        COMMAND mkdir -vp ${hex_files_dest_folder}/data/templates/state_machine_data
        COMMAND mkdir -vp ${hex_files_dest_folder}/data/templates/state_diagram_code
        COMMAND mkdir -vp ${hex_files_dest_folder}/data/templates/state_code

        COMMAND ${conv_util} ${CMAKE_SOURCE_DIR} ${x_ascii_file} ${hex_files_dest_folder}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS ${x_ascii_file}
        COMMENT "Converting ASCII '${x_ascii_file}' to HEX '${x_hex_file}' file"
        VERBATIM
    )
    list(APPEND ascii_to_hex_files_outputs ${x_hex_file})
endforeach()

add_custom_target(ascii_to_hex_files ALL DEPENDS ${ascii_to_hex_files_outputs})

set (cstmgen_libsources 
     src/CStMGen/cstmgen_main.cpp
     include/CStMGen/cstmgen_main.h
     src/CStMGen/cstmgen_params.cpp
     include/CStMGen/cstmgen_params.h
     src/CStMGen/cstmgen_json_machine_structure.cpp
     include/CStMGen/cstmgen_json_machine_structure.h
     src/CStMGen/cstmgen_process.cpp
     include/CStMGen/cstmgen_process.h
     include/CStMGen/cstmgen_process_templates.h
     src/CStMGen/cstmgen_process_utils.cpp
     include/CStMGen/cstmgen_process_utils.h
     )

add_library ( cstmgen
    ${cstmgen_libsources}
     )

add_dependencies( cstmgen
    ascii_to_hex_files
    )

if(NOT IS_SUBPROJECT)
	add_executable(cstmgen_app
	     src/app/main.cpp
	     )
	
	target_link_libraries(cstmgen_app
	     cstmgen
	     lggm
	     )
endif()
