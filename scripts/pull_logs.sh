#!/bin/bash

# ===============================
# Parse command line options
# ===============================

SSH_USER=""
CID=""

for arg in "${@}"; do
    if [ "${arg:0:11}" = "--ssh-user=" ]; then
        SSH_USER="${arg#--ssh-user=*}"
    elif [ "${arg:0:6}" = "--cid=" ]; then
        CID="${arg#--cid=*}"
        CID=$(printf "%03s" $CID)
    fi
done

# ===============================
# Get input from user
# ===============================

if [[ "$CID" == "" ]]; then
    printf "CID: "
    read CID
    CID=$(printf "%03s" $CID)
fi

# ===============================
# Get input from user
# ===============================

printf "Download logs in this directory [y/N]: "
read response

if [[ "$response" != "y" && "$response" != "Y" && "$response" != "yes" ]]; then
    exit 0
fi

# ===============================
# Download files
# ===============================

mkdir -p raw_logs

printf "===============================\n"
printf " Downloading logs from C${CID}\n" 
printf "===============================\n"

err_code=""
if [[ "$SSH_USER" == "" ]]; then
    rsync -rv --progress oceanai.mit.edu:'/raiddrive/aquaticus_data/*/C'${CID}'*' raw_logs
    err_code="$?"
else
    rsync -rv --progress ${SSH_USER}@oceanai.mit.edu:'/raiddrive/aquaticus_data/*/C'${CID}'*' raw_logs
    err_code="$?"
fi

if [ "$err_code" == "23" ]; then
    printf "===============================\n"
    printf " Error: C${CID} not on server.!\n"
    printf "===============================\n"
    exit 1
elif [ "$err_code" != "0" ]; then
    printf "===============================\n"
    printf " Error with rsync!\n"
    printf "===============================\n"
    exit 1
fi

# ===============================
# Untar files
# ===============================

printf "===============================\n"
printf " Extracting Logs\n"
printf "===============================\n"

# Untar tar files
for file in raw_logs/C${CID}*.tar; do
    tar -xvf $file -C raw_logs/.
done

# Untar tgz files
for file in raw_logs/C${CID}*.tgz; do
    tar -xvzf $file -C raw_logs/.
done

# ===============================
# Create file structure
# ===============================

printf "link from C${CID} in current directory? [Y/n]: "
read response

if [[ "$response" == "N" || "$response" == "n" || "$response" != "no" ]]; then
    exit 0
fi

printf "===============================\n"
printf " Linking logs from C${CID}\n" 
printf "===============================\n"

bllinks.sh --log_dir=raw_logs --cid="$CID"
