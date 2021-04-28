#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
AMT=1
SHORE_IP="localhost"
SHORE_LISTEN="9300"

for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        printf "%s [SWITCHES] [time_warp]   \n" $0
        printf "  --just_make, -j    \n"
        printf "  --help, -h         \n"
        exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_MAKE="yes"
    elif [ "${ARGI}" = "--blue_guys_no" -o "${ARGI}" = "-b" ] ; then
        continue
    elif [ "${ARGI}" = "--red_guys_no" -o "${ARGI}" = "-r" ] ; then
        continue
    elif [ "${ARGI:0:11}" = "--shore-ip=" ] ; then
        SHORE_IP="${ARGI#--shore-ip=*}"
    elif [ "${ARGI:0:13}" = "--shore-port=" ] ; then
        SHORE_LISTEN=${ARGI#--shore-port=*}
    elif [ "${ARGI:0:6}" = "--amt=" ] ; then
        AMT="${ARGI#--amt=*}"
    else
        printf "Bad Argument: %s \n" $ARGI
        exit 0
    fi
done


echo "Shoreside setting = $SHORE_IP:$SHORE_LISTEN"

# Ensure AMT is in the range of [1,26]
if [ $AMT -gt 26 ] ; then
    AMT=20
fi
if [ $AMT -lt 1 ] ; then
    AMT=1
fi

#-------------------------------------------------------
#  Part 1: Launch Blue Team
#-------------------------------------------------------
bash ./launch_blue.sh "$@"

#-------------------------------------------------------
#  Part 2: Launch Red Team
#-------------------------------------------------------
bash ./launch_red.sh "$@"

#-------------------------------------------------------
#  Part 3: Launch Shoreside
#-------------------------------------------------------
bash ./launch_shoreside.sh "$@"

if [ ${JUST_MAKE} = "yes" ] ; then
    printf "Nothing else to do. ./launch.sh out!\n"
    exit 0
fi

printf "Killing all processes ... \n"
kill -- -$$
printf "Done killing processes.   \n"
