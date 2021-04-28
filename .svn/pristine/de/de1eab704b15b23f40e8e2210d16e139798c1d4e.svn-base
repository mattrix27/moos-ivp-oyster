#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=5
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
VNAME1="betty"        
VNAME2="charlie"        
VNAME3="mokai"

START_POS1="0,-10"       

LOITER_POS1="x=50,y=-125"

SHORE_LISTEN="9300"

#-------------------------------------------------------
#  USV #1
#-------------------------------------------------------

nsplug meta_vehicle.moos targ_$VNAME1.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME1          SHARE_LISTEN="9301"              \
    VPORT="9001"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS1  VARIATION=$VARIATION   \
       VTYPE="kayak" 

nsplug meta_vehicle_trailer.bhv targ_$VNAME1.bhv -f VNAME=$VNAME1  \
      START_POS=$START_POS1 LOITER_POS=$LOITER_POS1       
#-------------------------------------------------------
#  USV #2
#-------------------------------------------------------

#nsplug meta_vehicle.moos targ_$VNAME2.moos -f WARP=$TIME_WARP \
#    VNAME=$VNAME2          SHARE_LISTEN="9302"              \
#    VPORT="9002"           SHORE_LISTEN=$SHORE_LISTEN       \
#    START_POS=$START_POS1  VARIATION=$VARIATION   \
#       VTYPE="kayak" 

#nsplug meta_vehicle_trailer.bhv targ_$VNAME2.bhv -f VNAME=$VNAME2  \
#      START_POS=$START_POS1 LOITER_POS=$LOITER_POS1       

#-------------------------------------------------------
#  USV #3
#-------------------------------------------------------

nsplug meta_speech.moos targ_$VNAME3.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME3          SHARE_LISTEN="9303"              \
    VPORT="9003"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS1  VARIATION=$VARIATION   \
       VTYPE="kayak" 

nsplug meta_vehicle_leader.bhv targ_$VNAME3.bhv -f VNAME=$VNAME3  \
      START_POS=$START_POS1 LOITER_POS=$LOITER_POS1       

#-------------------------------------------------------
#  SHORESIDE
#-------------------------------------------------------
nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP \
   SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN                  \
   SPORT="9000"     


if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------
printf "Launching $VNAME1 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME1}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
#pAntler targ_${VNAME2}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME3 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME3}.moos >& /dev/null &
sleep 0.25


printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done \n"

uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1 %2 %3 %4
printf "Done killing processes.   \n"
