#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
AMT=1
VTEAM1="red"
VTEAM2="blue"
RED_GUYS="yes"
BLUE_GUYS="yes"
SHORE_IP="localhost"
SHORE_LISTEN="9300"
BLUE_FLAG="x=-49.71,y=-75.47"
RED_FLAG="x=58.56,y=-23.74"

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
        BLUE_GUYS="no"
    elif [ "${ARGI}" = "--red_guys_no" -o "${ARGI}" = "-r" ] ; then
        RED_GUYS="no"
    elif [ "${ARGI:0:11}" = "--shore-ip=" ] ; then
        SHORE_IP="${ARGI#--shore-ip=*}"
    elif [ "${ARGI:0:13}" = "--shore-port=" ] ; then
        SHORE_LISTEN=${ARGI#--shore-port=*}
    else
        printf "Bad Argument: %s \n" $ARGI
        exit 0
    fi
done

#-------------------------------------------------------
#  Part 1: Create the Shoreside MOOS file
#-------------------------------------------------------
nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP    \
       SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN  SPORT="9000"   \
       VTEAM1=$VTEAM1 VTEAM2=$VTEAM2 SHORE_IP=$SHORE_IP              \
       RED_FLAG=${RED_FLAG} BLUE_FLAG=${BLUE_FLAG}

if [ ! -e targ_shoreside.moos ]; then echo "no targ_shoreside.moos"; exit 1; fi

#-------------------------------------------------------
#  Part 2: Possibly exit now if we're just building targ files
#-------------------------------------------------------

if [ ${JUST_MAKE} = "yes" ] ; then
    printf "Shoreside targ files built. Nothing launched.\n"
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the Shoreside
#-------------------------------------------------------
printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done Launching Shoreside \n"

uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
mykill
ktm
printf "Done killing processes.   \n"
