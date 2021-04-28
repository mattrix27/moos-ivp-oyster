#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
AMT=1
BLUE_GUYS="yes"
VTEAM="blue"
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
        BLUE_GUYS="no"
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

# Ensure AMT is in the range of [1,26]
if [ $AMT -gt 26 ] ; then
    AMT=20
fi
if [ $AMT -lt 1 ] ; then
    AMT=1
fi

#-------------------------------------------------------
#  Part 3: Create the Mokai for human driver 2.
#-------------------------------------------------------
VNAME="human2"
START_POS="-54,-108,60"

nsplug meta_mokai_sim.moos targ_$VNAME.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME           SHARE_LISTEN="9303"              \
    VPORT="9003"           SHORE_LISTEN=$SHORE_LISTEN       \
    VTEAM=$VTEAM           START_POS=$START_POS JOY_ID="1"  \
    BUTTON="4"             SHORE_IP=$SHORE_IP

if [ ! -e targ_$VNAME.moos ]; then echo "no targ_$VNAME.moos"; exit; fi

#-------------------------------------------------------
#  Part 3.1: Create the Chaser 2.
#-------------------------------------------------------
VNAME="chaser2"
START_POS="-86,-41,60"
LOITER_POS="x=-23,y=-53"

nsplug meta_chaser.moos targ_$VNAME.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME           SHARE_LISTEN="9305"              \
    VPORT="9005"           SHORE_LISTEN=$SHORE_LISTEN       \
    VTEAM=$VTEAM           START_POS=$START_POS             \
    SHORE_IP=$SHORE_IP

nsplug meta_chaser_def_saad.bhv targ_$VNAME.bhv -f VNAME=$VNAME     \
   START_POS=$START_POS LOITER_POS=$LOITER_POS

if [ ! -e targ_$VNAME.moos ]; then echo "no targ_$VNAME.moos"; exit; fi

#-------------------------------------------------------
#  Part 4: Exit if just make.
#-------------------------------------------------------
if [ ${JUST_MAKE} = "yes" ] ; then
  printf "Blue Team targ files built. Nothing launched.\n"
  exit 0
fi

#-------------------------------------------------------
#  Part 6: Launch the mokai processes
#-------------------------------------------------------
if [ ${BLUE_GUYS} = "yes" ] ; then
    printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_human2.moos >& /dev/null &
    pAntler targ_chaser2.moos >& /dev/null &
    printf "Done Launching Blue Guys \n"
fi
