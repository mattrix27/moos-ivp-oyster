#!/bin/bash
WARP=1

#M200_IP="localhost"
#M200_IP=192.168.5.1 #evan
#M200_IP=192.168.6.1 #felix
#M200_IP=192.168.7.1 #gus

# SHORE_IP
#  Emulation, shoreside running on same machine as vehicle: localhost
#  Emulation, shoreside running on a different machine:     IP address of that machine (often 192.168.2.1)
#  Actual vehicle:                                          IP address of the shoreside computer
#SHORE_IP="localhost"
SHORE_IP=192.168.1.155
SHORE_LISTEN="9300"

TRAIL_RANGE="3"
TRAIL_ANGLE="330"
HELP="no"
JUST_BUILD="no"
EVAN="no"
FELIX="no"
GUS="no"
VTEAM="red"

RETURN_POS=""
LOITER_POS="x=100,y=-180"
GRAB_POS=""
UNTAG_POS=""

printf "Initiate launch vehicle script\n"

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    UNDEFINED_ARG=$ARGI
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        HELP="yes"
        UNDEFINED_ARG=""
    fi
    if [ "${ARGI}" = "--evan" -o "${ARGI}" = "-e" ] ; then
        M200_IP=192.168.5.1 #evan
        EVAN="yes"
        UNDEFINED_ARG=""
        VNAME="evan"
        VPORT="9005"
        SHARE_LISTEN="9305"
        printf "EVAN vehicle selected as HUNTER.\n"
    fi
    if [ "${ARGI}" = "--felix" -o "${ARGI}" = "-f" ] ; then
        M200_IP=192.168.6.1 #felix
        FELIX="yes"
        UNDEFINED_ARG=""
        VNAME="felix"
        VPORT="9006"
        SHARE_LISTEN="9306"
        printf "FELIX vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--gus" -o "${ARGI}" = "-g" ] ; then
        M200_IP=192.168.7.1 #gus
        GUS="yes"
        UNDEFINED_ARG=""
        VNAME="gus"
        VPORT="9007"
        SHARE_LISTEN="9307"
        printf "GUS vehicle selected as HUNTER.\n"
    fi
    if [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_BUILD="yes"
        UNDEFINED_ARG=""
        printf "Just building files; no vehicle launch.\n"
    fi
    if [ "${ARGI}" = "--red" -o "${ARGI}" = "-r" ] ; then
        VTEAM="red"
        UNDEFINED_ARG=""
        GRAB_POS="-57,-71"
        UNTAG_POS="50,-26"
        RETURN_POS="50,-26"
        printf "Red team selected.\n"
    fi
    if [ "${ARGI}" = "--blue" -o "${ARGI}" = "-b" ] ; then
        VTEAM="blue"
        UNDEFINED_ARG=""
        GRAB_POS="50,-26"
        UNTAG_POS="-57,-71"
        RETURN_POS="-57,-71"
        printf "Blue team selected.\n"
    fi
    if [ "${UNDEFINED_ARG}" != "" ] ; then
        BAD_ARGS=$UNDEFINED_ARG
    fi
done

#-------------------------------------------------------
#  Part 2: Handle Ill-formed command-line arguments
#-------------------------------------------------------

if [ "${BAD_ARGS}" != "" ] ; then
    printf "Bad Argument: %s \n" $BAD_ARGS
    exit 0
fi

if [ "${HELP}" = "yes" ]; then
    printf "%s [SWITCHES]            \n" $0
    printf "Switches:                \n"
    printf "  --evan, -e             evan vehicle only  \n"
    printf "  --felix, -f            felix vehicle only \n"
    printf "  --gus, -g              gus vehicle only   \n"
    printf "  --blue, -b       \n"
    printf "  --red, -r       \n"
    printf "  --just_build, -j       \n"
    printf "  --help, -h             \n"
    exit 0;
fi

#-------------------------------------------------------
#  Part 3: Create the .moos and .bhv files.
#-------------------------------------------------------

printf "Assembling MOOS file targ_${VNAME}.moos\n"

nsplug meta_m200.moos targ_${VNAME}.moos -f \
        VNAME=$VNAME                 \
        VPORT=$VPORT                 \
        WARP=$WARP                   \
        SHARE_LISTEN=$SHARE_LISTEN   \
        SHORE_LISTEN=$SHORE_LISTEN   \
        SHORE_IP=$SHORE_IP           \
        M200_IP=$M200_IP             \
        HOSTIP_FORCE="localhost"     \
        LOITER_POS=$LOITER_POS       \
        VARIATION=$VARIATION         \
        VTYPE="kayak"                \
        VTEAM=$VTEAM

printf "Assembling BHV file targ_${VNAME}.bhv\n"
nsplug meta_hunter.bhv targ_${VNAME}.bhv -f  \
        RETURN_POS=${RETURN_POS}    \
        TRAIL_RANGE=$TRAIL_RANGE    \
        TRAIL_ANGLE=$TRAIL_ANGLE    \
        VTEAM=$VTEAM                \
        VNAME=$VNAME                \
        GRAB_POS=$GRAB_POS          \
        UNTAG_POS=$UNTAG_POS


if [ ${JUST_BUILD} = "yes" ] ; then
    printf "Files assembled; vehicle not launched; exiting per request.\n"
    exit 0
fi

#-------------------------------------------------------
#  Part 4: Launch the processes
#-------------------------------------------------------

printf "Launching $VNAME MOOS Community \n"
pAntler targ_${VNAME}.moos >& /dev/null &
uMAC targ_${VNAME}.moos

printf "Killing all processes ... \n "
kill -- -$$
printf "Done killing processes.   \n "
