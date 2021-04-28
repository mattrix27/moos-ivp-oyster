#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
AMT=1
GOOD_GUYS="yes"
BAD_GUYS="yes"
VTEAM1="red"
VTEAM2="blue"
SHORE_IP="localhost"

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
    elif [ "${ARGI}" = "--bad_guys_no" -o "${ARGI}" = "-b" ] ; then
        BAD_GUYS="no"
    elif [ "${ARGI}" = "--good_guys_no" -o "${ARGI}" = "-g" ] ; then
        GOOD_GUYS="no"
    elif [ "${ARGI:0:6}" = "--amt=" ] ; then
        AMT="${ARGI#--amt=*}"
    else
        printf "Bad Argument: %s \n" $ARGI
        exit 0
    fi
done

# Ensure AMT is in the range of [1,26]
if [ $AMT -gt 26 ] ; then
    AMT=20
fi
if [ $AMT -lt 1 ] ; then
    AMT=1
fi


#-------------------------------------------------------
#  Part 1: Create the Shoreside MOOS file
#-------------------------------------------------------
SHORE_LISTEN="9300"

nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP    \
       SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN  SPORT="9000"   \
       VTEAM1=$VTEAM1 VTEAM2=$VTEAM2 SHORE_IP=$SHORE_IP

if [ ! -e targ_shoreside.moos ]; then echo "no targ_shoreside.moos"; exit; fi


#-------------------------------------------------------
#  Part 2: Create the Mokai for human driver 1.
#-------------------------------------------------------
VNAME="human1"
START_POS="55,25,240"

nsplug meta_mokai_sim.moos targ_human_1.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME           SHARE_LISTEN="9302"              \
    VPORT="9002"           SHORE_LISTEN=$SHORE_LISTEN       \
    VTEAM=$VTEAM1          START_POS=$START_POS JOY_ID="0"  \
    BUTTON="5"             SHORE_IP=$SHORE_IP

#nsplug meta_.bhv targ_mokai.bhv -f VNAME=$VNAME     \
#    START_POS=$START_POS

if [ ! -e targ_human_1.moos ]; then echo "no targ_human_1.moos"; exit; fi
#if [ ! -e targ_mokai.bhv  ]; then echo "no targ_mokai.bhv "; exit; fi

#-------------------------------------------------------
#  Part 3: Create the Mokai for human driver 2.
#-------------------------------------------------------
VNAME="human2"
START_POS="-54,-108,60"

nsplug meta_mokai_sim.moos targ_human_2.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME           SHARE_LISTEN="9303"              \
    VPORT="9003"           SHORE_LISTEN=$SHORE_LISTEN       \
    VTEAM=$VTEAM2          START_POS=$START_POS JOY_ID="1"  \
    BUTTON="4"             SHORE_IP=$SHORE_IP

#nsplug meta_.bhv targ_mokai.bhv -f VNAME=$VNAME     \
#    START_POS=$START_POS

if [ ! -e targ_human_2.moos ]; then echo "no targ_human_2.moos"; exit; fi
#if [ ! -e targ_mokai.bhv  ]; then echo "no targ_mokai.bhv "; exit; fi

#-------------------------------------------------------
#  Part 4: Possibly exit now if we're just building targ files
#-------------------------------------------------------

if [ ${JUST_MAKE} = "yes" ] ; then
    printf "targ files built. Nothing launched.\n"
    exit 0
fi

if [ ${BAD_GUYS} = "no" -a ${GOOD_GUYS} = "no"] ; then
    printf "targ files built. Nothing launched.\n"
    exit 0
fi

#-------------------------------------------------------
#  Part 5: Launch the Shoreside
#-------------------------------------------------------
printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done Launching Shoreside \n"

#-------------------------------------------------------
#  Part 6: Launch the GoodGuy processes
#-------------------------------------------------------
if [ ${GOOD_GUYS} = "yes" ] ; then
    printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_human_1.moos >& /dev/null &
    printf "Done Launching Good Guys \n"
fi

#-------------------------------------------------------
#  Part 6: Launch the mokai processes
#-------------------------------------------------------
if [ ${GOOD_GUYS} = "yes" ] ; then
    printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_human_2.moos >& /dev/null &
    printf "Done Launching Good Guys \n"
fi


uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill -- -$$
printf "Done killing processes.   \n"
