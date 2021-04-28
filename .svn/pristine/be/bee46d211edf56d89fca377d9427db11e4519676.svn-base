#!/bin/bash -e
#----------------------------------------------------------
#  Script: launch_shoreside.sh
#  Author: Michael Benjamin
#  LastEd: Nov 13th, 2020
#----------------------------------------------------------
#  Part 1: Set global var defaults
#----------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
AMT=1
VTEAM1="red"
VTEAM2="blue"
RED_GUYS="yes"
BLUE_GUYS="yes"
SHORE_IP="localhost"
SHORE_LISTEN="9300"
BLUE_FLAG="x=20,y=40"
RED_FLAG="x=140,y=40"

#-------------------------------------------------------
#  Part 2: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        echo "launch_shoreside.sh [SWITCHES] [time_warp]   "
        echo "  --help, -h                                 "
        echo "  --just_make, -j                            "
        exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ]; then
        JUST_MAKE="yes"
    elif [ "${ARGI}" = "--blue_guys_no" -o "${ARGI}" = "-b" ]; then
        BLUE_GUYS="no"
    elif [ "${ARGI}" = "--red_guys_no" -o "${ARGI}" = "-r" ]; then
        RED_GUYS="no"
    elif [ "${ARGI:0:11}" = "--shore-ip=" ]; then
        SHORE_IP="${ARGI#--shore-ip=*}"
    elif [ "${ARGI:0:13}" = "--shore-port=" ]; then
        SHORE_LISTEN=${ARGI#--shore-port=*}
    else
        echo "launch_shoreside.sh: Bad Arg:" $ARGI "Exiting with code: 1"
        exit 1
    fi
done

#-------------------------------------------------------
#  Part 3: Create the Shoreside MOOS file
#-------------------------------------------------------
nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP    \
       SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN  SPORT="9000"   \
       VTEAM1=$VTEAM1 VTEAM2=$VTEAM2 SHORE_IP=$SHORE_IP              \
       RED_FLAG=${RED_FLAG} BLUE_FLAG=${BLUE_FLAG}

if [ ! -e targ_shoreside.moos ]; then echo "no targ_shoreside.moos"; exit 1; fi

#-------------------------------------------------------
#  Part 4: Possibly exit now if we're just building targ files
#-------------------------------------------------------

if [ ${JUST_MAKE} = "yes" ] ; then
    echo "Shoreside targ files built. Nothing launched."
    exit 0
fi

#-------------------------------------------------------
#  Part 5: Launch the Shoreside
#-------------------------------------------------------
echo "Launching $SNAME MOOS Community. WARP:"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
echo "Done Launching Shoreside "

uMAC targ_shoreside.moos

echo "Killing all processes ..."
kill -- -$$
mykill
ktm
echo "Done killing processes.  "
