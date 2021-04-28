#!/bin/bash

SHORE_IP=192.168.1.155
# SHORE_IP=multicast_7
SHORE_LISTEN="9300"

WARP=1
HELP="no"
JUST_BUILD="no"
BAD_ARGS=""
VTEAM="red"
VNAME="mokai"
VPORT="9013"
SHARE_LISTEN="9313"

printf "Initiate launch MOKAI script.\n"

for ARGI; do
    UNDEFINED_ARG=$ARGI
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        HELP="yes"
        UNDEFINED_ARG=""
    fi
    if [ "${ARGI}" = "--red" -o "${ARGI}" = "-r" ] ; then
        VTEAM="red"
        UNDEFINED_ARG=""
        printf "Red team selected.\n"
    fi
    if [ "${ARGI}" = "--blue" -o "${ARGI}" = "-b" ] ; then
        VTEAM="blue"
        UNDEFINED_ARG=""
        printf "Blue team selected.\n"
    fi
    if [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_BUILD="yes"
        UNDEFINED_ARG=""
        printf "Just building files; no vehicle launch.\n"
    fi
    if [ "${UNDEFINED_ARG}" != "" ] ; then
        BAD_ARGS=$UNDEFINED_ARG
    fi
done

if [ "${BAD_ARGS}" != "" ] ; then
    printf "Bad Argument: %s \n" $BAD_ARGS
    exit 0
fi

if [ "${HELP}" = "yes" ]; then
    printf "%s [SWITCHES]            \n" $0
    printf "Switches:                \n"
    printf "  --just_build, -j       \n"
    printf "  --help, -h             \n"
    exit 0;
fi

printf "Assembling MOOS file targ_${VNAME}.moos .\n"

nsplug meta_mokai.moos targ_${VNAME}.moos -f  \
       VNAME="${VNAME}_${VTEAM}"                 \
       VPORT=$VPORT                 \
       WARP=$WARP                   \
       SHARE_LISTEN=$SHARE_LISTEN   \
       SHORE_LISTEN=$SHORE_LISTEN   \
       SHORE_IP=$SHORE_IP           \
       VTYPE="mokai"                \
       VTEAM=$VTEAM

if [ ${JUST_BUILD} = "yes" ] ; then
    printf "Files assembled; vehicle not launched; exiting per request.\n"
    exit 0
fi

if [ ! -e targ_${VNAME}.moos ]; then echo "no targ_${VNAME}.moos!"; exit 1; fi

printf "Launching $VNAME MOOS Community.\n"
pAntler targ_${VNAME}.moos >& /dev/null &
uMAC targ_${VNAME}.moos

printf "Killing all processes ... \n "
kill -- -$$
printf "Done killing processes.   \n "
