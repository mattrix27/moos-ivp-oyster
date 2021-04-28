#!/bin/bash
ulimit -c unlimited
error_code="$?"

if [[ "$error_code" != "0" ]]; then
    printf "Error in ulimit command!\n"
else
    printf "Core dumps enabled for this session.\n"
fi
