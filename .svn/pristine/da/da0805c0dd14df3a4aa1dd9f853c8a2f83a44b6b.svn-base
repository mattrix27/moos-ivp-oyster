#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=10
JUST_MAKE="no"
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
    else 
	printf "Bad Argument: %s \n" $ARGI
	exit 0
    fi
done

#-------------------------------------------------------
#  Part 2: Create the .moos and .bhv files. 
#-------------------------------------------------------
VNAME7="geoff"        
VNAME8="harley"        
VNAME9="ingrid"

START_POS1="0,-10"       

LOITER_POS1="x=50,y=-125"

SHORE_LISTEN="9300"

#-------------------------------------------------------
#  USV #1
#-------------------------------------------------------

nsplug meta_vehicle.moos targ_$VNAME7.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME7          SHARE_LISTEN="9307"              \
    VPORT="9007"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS1  VARIATION=$VARIATION   \
       VTYPE="kayak"       

nsplug meta_vehicle_traffic.bhv targ_$VNAME7.bhv -f VNAME=$VNAME7  \
       START_POS=$START_POS1 LOITER_POS=$LOITER_POS1  \
       WPT_ORDER=normal
#-------------------------------------------------------
#  USV #2
#-------------------------------------------------------

nsplug meta_vehicle.moos targ_$VNAME8.moos -f WARP=$TIME_WARP \
   VNAME=$VNAME8          SHARE_LISTEN="9308"              \
   VPORT="9008"           SHORE_LISTEN=$SHORE_LISTEN       \
   START_POS=$START_POS1  VARIATION=$VARIATION   \
      VTYPE="kayak"       

nsplug meta_vehicle_traffic.bhv targ_$VNAME8.bhv -f VNAME=$VNAME8  \
       START_POS=$START_POS1 LOITER_POS=$LOITER_POS1   \
       WPT_ORDER=reverse

#-------------------------------------------------------
#  USV #3
#-------------------------------------------------------

nsplug meta_vehicle.moos targ_$VNAME9.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME9          SHARE_LISTEN="9309"              \
    VPORT="9009"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS1  VARIATION=$VARIATION   \
       VTYPE="kayak"      

nsplug meta_vehicle_traffic.bhv targ_$VNAME9.bhv -f VNAME=$VNAME9  \
       START_POS=$START_POS1 LOITER_POS=$LOITER_POS1       \
        WPT_ORDER=normal

#-------------------------------------------------------
#  SHORESIDE
#-------------------------------------------------------
#nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP \
#   SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN                  \
#   SPORT="9000"     


if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------
printf "Launching $VNAME7 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME7}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME8 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME8}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME9 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME9}.moos >& /dev/null &
sleep 0.25


printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
#pAntler targ_shoreside.moos >& /dev/null &
printf "Done \n"

uMAC targ_${VNAME7}.moos

printf "Killing all processes ... \n"
kill %1 %2 %3 %4
printf "Done killing processes.   \n"



