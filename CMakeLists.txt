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

set (ascii_to_hex_files_sources
  templates/cstm_state_diagram_template_h
  templates/cstm_state_diagram_template_c
  templates/cstm_state_enum_template_h
  templates/cstm_state_enum_state_name_template
  templates/cstm_state_data_desc_template_h
  templates/cstm_state_data_desc_template_c
  templates/cstm_state_transition_template_c
  templates/cstm_state_transition_name_template
  templates/cstm_state_template_h
  templates/cstm_state_template_c
  templates/cstm_state_include_text_template
  templates/cstm_state_node_text_template
)

set (conv_util data/templates/conv/template_to_hex.sh)
set (ascii_files_src_folder data/templates)
set (hex_files_dest_folder include/CStMGen)

add_custom_command(OUTPUT ${ascii_to_hex_files_sources}
  COMMAND mkdir -vp ${hex_files_dest_folder}/data/templates
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_diagram_template_h ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_diagram_template_c ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_enum_template_h ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_enum_state_name_template ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_data_desc_template_h ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_data_desc_template_c ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_transition_template_c ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_transition_name_template ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_template_h ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_template_c ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_include_text_template ${hex_files_dest_folder}
  COMMAND ${conv_util} ${ascii_files_src_folder}/cstm_state_node_text_template ${hex_files_dest_folder}

  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  DEPENDS data/sample_config_file.json
  COMMENT "Converting to HEX encoded include files"
  VERBATIM
)

add_custom_target(ascii_to_hex_files ALL DEPENDS ${ascii_to_hex_files_sources})

set (cstmgen_libsources 
     src/CStMGen/cstmgen_main.cpp
     include/CStMGen/cstmgen_main.h
     src/CStMGen/cstmgen_params.cpp
     include/CStMGen/cstmgen_params.h
     src/CStMGen/json_machine_structure.cpp
     include/CStMGen/json_machine_structure.h
     src/CStMGen/cstmgen_process.cpp
     include/CStMGen/cstmgen_process.h
     )

add_library ( cstmgen
    ${cstmgen_libsources}
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
