#!/bin/bash

# ===============================
# Functions
# ===============================

function full_path(){

    if [ ! -e "$1" ]; then
        printf "$1 is not a directory!\n"
        return 1
    fi

    case "$1" in
        /*)
            printf '%s\n' "$1"
            ;;
        *)
            printf '%s\n' "$PWD/$1"
            ;;
    esac
}

function display_help(){
    printf "\n"
    printf "bllinks.sh [SWITCHES]\n"
    printf "\n"
    printf "POSSIBLE SWITCHES:\n"
    printf "    --log_dir=DIRECTORY\n"
    printf "    --dest_dir=DIRECTORY\n"
    printf "    --cid=XXX\n"
    exit 0
}

# ===============================
# Parse command line options
# ===============================

CID=""
LOG_DIR=""
DEST_DIR=""

for arg in "${@}"; do
    if [ "${arg:0:10}" = "--log_dir=" ]; then
        LOG_DIR="${arg#--log_dir=*}"
    elif [ "${arg:0:11}" = "--dest_dir=" ]; then
        DEST_DIR="${arg#--dest_dir=*}"
    elif [ "${arg:0:6}" = "--cid=" ]; then
        CID="${arg#--cid=*}"
        CID=$(printf "%03s" $CID)
    fi
done

# ===============================
# Handle options
# ===============================

if [ ! -e "$LOG_DIR" ]; then
    printf "Error: LOG_DIR=${LOG_DIR} does not exist!\n"
    display_help
fi 

if [ ! -d "$LOG_DIR" ]; then
    printf "Error: LOG_DIR=${LOG_DIR} is not a directory!\n"
    display_help
fi 

if [ "$CID" == "" ]; then
    printf "Error: please select a cid with --cid=XXX\n"
    display_help
fi

if [ "$DEST_DIR" == "" ]; then
    printf "No dest_dir specified; setting to cid.\n"
    DEST_DIR="C${CID}"
fi

if [ -e "$DEST_DIR" ]; then
    printf "Overwrite \'$DEST_DIR\' [y/N]: "
    read response

    if [[ "$response" != "y" && "$response" != "Y" && "$response" != "yes" ]]; then
        exit 0
    fi
    
    rm -rf "$DEST_DIR"
fi


# ===============================
# Do linking
# ===============================

mkdir "${DEST_DIR}"

# Get full path becuase ln is picky
top_p=$(full_path "${DEST_DIR}")
heron_p="${top_p}/heron"
mokai_p="${top_p}/mokai"
shore_p="${top_p}/shoreside"

mkdir "$heron_p"
mkdir "$mokai_p"
mkdir "$shore_p"

for file in "$LOG_DIR"/*; do
    full_p=$(full_path $file)
    file_name="$(basename $file)"

    if [ ! -d "$full_p" ]; then
        continue
    fi

    case "$file" in
        *C${CID}*P*)
            printf "Linking mokai dir: ${file_name}\n"
            ln -s "$full_p" "${mokai_p}/${file_name}"
            ;;
        *C${CID}*_LOG_SHORESIDE_*)
            printf "Linking shorside dir: ${file_name}\n"
            ln -s "$full_p" "${shore_p}/${file_name}"
            ;;
        *C${CID}*)
            printf "Linking heron dir: ${file_name}\n"
            ln -s "$full_p" "${heron_p}/${file_name}"
            ;;
        *)
            ;;
    esac
done
