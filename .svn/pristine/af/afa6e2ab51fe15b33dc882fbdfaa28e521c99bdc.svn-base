#!/bin/bash

WARP=1
SHORE_IP=192.168.1.155
SHORE_PORT=9000
VTEAM="red"

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES]                                          \n" $0
	printf "Switches:                                              \n"
	printf "  --vteam=TEAM      Set team name {red,blue}           \n"
	printf "  --just_build, -j  Just build files                   \n"
	printf "  --help, -h                                           \n"
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$WARP" = 1 ]; then
        WARP=$ARGI
    elif [ "${ARGI:0:8}" = "--vteam=" ] ; then
        VTEAM="${ARGI#--vteam=*}"
    elif [ "${ARGI:0:10}" = "--shoreip=" ] ; then
        SHORE_IP="${ARGI#--shoreip=*}"
    elif [ "${ARGI:0:7}" = "--port=" ] ; then
        PORT="${ARGI#--port=*}"
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_BUILD="yes"
    else
	printf "Bad Argument: %s \n" $BAD_ARGS ". Use --help"
	exit 1
    fi
done

    
#-------------------------------------------------------
#  Part 2: Create the .moos file.
#-------------------------------------------------------
nsplug meta_commander.moos targ_commander_${VTEAM}.moos -f --strict   \
       WARP=$WARP  SHORE_IP=$SHORE_IP SHORE_PORT=$SHORE_PORT     
    
if [ ! -e targ_commander_${VTEAM}.moos ]; then
    echo "no targ_${VNAME}.moos";
    exit 1;
fi

if [ ${JUST_BUILD} = "yes" ] ; then
    printf "targ file built; uCommand not launched; exiting per request.\n"
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the uCommand process
#-------------------------------------------------------
uCommand targ_commander_${VTEAM}.moos >& /dev/null
