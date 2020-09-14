#!/bin/env bash

SRC_FILE="$1"
DEST_FOLDER="$2"

DEST_FILE_PATHNAME="${DEST_FOLDER}/${SRC_FILE}.h"

CMD_SED1="sed 's/unsigned char/uint8_t const/g'"
CMD_SED2="sed 's/unsigned int/size_t const/g'"

GUARD_STRING=

function usage()
{
    echo
    echo "$0 <source-file> <destination-folder>"
}

function print_error()
{
    local error_msg="$1"
    echo "Error: $1."
}

function check_input_params()
{

    if [ -z "${SRC_FILE}" ] ; then
        usage
        print_error "no source file has been specified"
        exit 1
    fi


    if [ -f "${SRC_FILE}" ] ; then
        true
    else
        usage
        print_error "no valid source file has been specified"
        exit 1
    fi

    if [ -z "${DEST_FOLDER}" ] ; then
        usage
        print_error "no destination folder has been specified"
        exit 1
    fi

    if [ -d "${DEST_FOLDER}" ] ; then
        true
    else
        usage
        print_error "no valid destination folder has been specified"
        exit 1
    fi

}

function prepare_output_file_guard()
{
    local in_file_name="$1"

    local guard_str=$(echo "${in_file_name}" | sed 's/[^a-zA-Z]*//g')

    guard_str="${guard_str^^}"

    GUARD_STRING="${guard_str}"
}

function touch_output_file()
{
    local out_file_name="$1"

    [ -f "${out_file_name}" ] && rm -f "${out_file_name}"
    touch "${out_file_name}"
}

function prepare_output_file_header()
{
    local out_file_name="$1"

    cat <<EOF_OUTPUT_FILE_HEADER >> "${out_file_name}"
#include <stddef.h>
#include <stdint.h>

#ifndef ${GUARD_STRING}
#define ${GUARD_STRING}

EOF_OUTPUT_FILE_HEADER
}

function prepare_output_file_contents()
{
    local in_file_name="$1"
    local out_file_name="$2"

    eval "xxd -i "${in_file_name}" | ${CMD_SED1} | ${CMD_SED2}" >> "${out_file_name}"
}

function prepare_output_file_footer()
{
    local out_file_name="$1"

    cat <<EOF_OUTPUT_FILE_FOOTER >> "${out_file_name}"

#endif /* ${GUARD_STRING} */
EOF_OUTPUT_FILE_FOOTER
}

check_input_params

prepare_output_file_guard "${DEST_FILE_PATHNAME}"
touch_output_file "${DEST_FILE_PATHNAME}"
prepare_output_file_header "${DEST_FILE_PATHNAME}"
prepare_output_file_contents "${SRC_FILE}" "${DEST_FILE_PATHNAME}"
prepare_output_file_footer "${DEST_FILE_PATHNAME}"
