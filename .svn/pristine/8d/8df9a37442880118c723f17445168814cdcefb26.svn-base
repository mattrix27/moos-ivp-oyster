#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
AMT=1
HUMAN_RED="no"
HUMAN_BLUE="no"
BOT1_RED="no"
BOT1_BLUE="no"
VTEAM1="red"
VTEAM2="blue"
BAD_ARGS=""
HELP="no"
SHORE_IP=128.30.31.217

printf "Initiate launch vehicle script\n"

for ARGI; do
    UNDEFINED_ARG=$ARGI

    if [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_MAKE="yes"
        UNDEFINED_ARG=""
    elif [ "${ARGI}" = "--red_human" -o "${ARGI}" = "-rh" ] ; then
        HUMAN_RED="yes"
        UNDEFINED_ARG=""
    elif [ "${ARGI}" = "--blue_human" -o "${ARGI}" = "-bh" ] ; then
        HUMAN_BLUE="yes"
        UNDEFINED_ARG=""
    elif [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        UNDEFINED_ARG=""
        HELP="YES"
    fi

    if [ "${UNDEFINED_ARG}" != "" ] ; then
        BAD_ARGS=$UNDEFINED_ARG
    fi
done



if [ "${BAD_ARGS}" != "" -o "${HELP}" = "YES" ] ; then
    if [ "${BAD_ARGS}" != "" ] ; then
        printf "Bad Argument: %s \n" $BAD_ARGS
    fi
    printf "%s [SWITCHES]   \n" $0
    printf "Switches: \n "
    printf "  --red_human, -rh    red human vehicle only \n"
    printf "  --blue_human, -bh    blue human vehicle only \n"
    printf "  --just_build, -j    \n"
    printf "  --help, -h         \n"
    exit 0
fi


# Ensure AMT is in the range of [1,26]
if [ $AMT -gt 26 ] ; then
    AMT=20
fi
if [ $AMT -lt 1 ] ; then
    AMT=1
fi


#-------------------------------------------------------
#  Part 1: Setup the Shoreside Parameters
#-------------------------------------------------------
SHORE_LISTEN="9300"

#-------------------------------------------------------
#  Part 2: Create the Mokai for human driver 1.
#-------------------------------------------------------
VNAME="red_human"
START_POS="20,-20,180"

nsplug meta_mokai_sim.moos targ_red_human.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME           SHARE_LISTEN="9302"              \
    VPORT="9002"           SHORE_LISTEN=$SHORE_LISTEN       \
    VTEAM=$VTEAM1          START_POS=$START_POS JOY_ID="3"  \
    BUTTON="1"             SHORE_IP=$SHORE_IP

#nsplug meta_.bhv targ_mokai.bhv -f VNAME=$VNAME     \
#    START_POS=$START_POS

if [ ! -e targ_red_human.moos ]; then echo "no targ_red_human.moos"; exit; fi
#if [ ! -e targ_mokai.bhv  ]; then echo "no targ_mokai.bhv "; exit; fi


#-------------------------------------------------------
#  Part 3: Create the Mokai for human driver 2.
#-------------------------------------------------------
VNAME="blue_human"
START_POS="20,-180,0"

nsplug meta_mokai_sim.moos targ_blue_human.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME           SHARE_LISTEN="9303"              \
    VPORT="9003"           SHORE_LISTEN=$SHORE_LISTEN       \
    VTEAM=$VTEAM2          START_POS=$START_POS JOY_ID="0"  \
    BUTTON="2"             SHORE_IP=$SHORE_IP

#nsplug meta_.bhv targ_mokai.bhv -f VNAME=$VNAME     \
#    START_POS=$START_POS

if [ ! -e targ_blue_human.moos ]; then echo "no targ_blue_human.moos"; exit; fi
#if [ ! -e targ_mokai.bhv  ]; then echo "no targ_mokai.bhv "; exit; fi


#-------------------------------------------------------
#  Part 4: Possibly exit now if we're just building targ files
#-------------------------------------------------------

if [ ${JUST_MAKE} = "yes" ] ; then
    printf "targ files built. Nothing launched.\n"
    exit 0
fi

#-------------------------------------------------------
#  Part 6: Launch the human processes
#-------------------------------------------------------
if [ ${HUMAN_RED} = "yes" ] ; then
    printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_red_human.moos >& /dev/null &
    MOOS_FILE=targ_red_human.moos
    printf "Done Launching Good Guys \n"
fi
if [ ${HUMAN_BLUE} = "yes" ] ; then
    printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_blue_human.moos >& /dev/null &
    MOOS_FILE=targ_blue_human.moos
    printf "Done Launching Good Guys \n"
fi


uMAC $MOOS_FILE

printf "Killing all processes ... \n"
kill -- -$$
printf "Done killing processes.   \n"
