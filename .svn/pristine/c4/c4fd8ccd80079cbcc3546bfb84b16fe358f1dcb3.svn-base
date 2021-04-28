#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=15
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
VNAME1="archie"        
VNAME2="evan"         
#VNAME3="hunter"        
VNAME4="mokai"        

START_POS1="0,-10"       
START_POS2="-5,-100"   
START_POS3="0,-20"       
START_POS4="-100,-150"

LOITER_POS1="x=50,y=-125"
LOITER_POS2="x=100,y=-180"

RETURN_POS1=-10,0
RETURN_POS2=-10,-10

SPEED1=2.0
SPEED2=2.0

WPT_PTS1=-150,-80:15,-80
WPT_PTS2=-150,-80:15,-80

TRAIL_RANGE1="40"
TRAIL_ANGLE1="330"

SHORE_LISTEN="9300"
SHORE_IP="localhost"

#-------------------------------------------------------
#  USV #1
#-------------------------------------------------------

nsplug meta_vehicle.moos targ_archie.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME1          SHARE_LISTEN="9301"              \
    VPORT="9001"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS1  VARIATION=$VARIATION   \
       VTYPE="kayak" SHORE_IP=$SHORE_IP

nsplug meta_vehicle.bhv targ_archie.bhv -f VNAME=$VNAME1  \
       START_POS=$START_POS1 LOITER_POS=$LOITER_POS1    \
       WPT_ORDER=normal WPT_PTS=$WPT_PTS1 SPEED=$SPEED1 \
              RETURN_POS=$RETURN_POS1

#-------------------------------------------------------
#  HUNTER = BETTY = TRAIL
#-------------------------------------------------------
nsplug meta_vehicle.moos targ_evan.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME2          SHARE_LISTEN="9302"              \
    VPORT="9002"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS2  VARIATION=$VARIATION   \
       VTYPE="kayak" SHORE_IP=$SHORE_IP

nsplug meta_hunter.bhv targ_evan.bhv -f VNAME=$VNAME2  \
    START_POS=$START_POS2 LOITER_POS=$LOITER_POS2     \
    WPT_ORDER=reverse WPT_PTS=$WPT_PTS2 SPEED=$SPEED2 \
    RETURN_POS=$RETURN_POS2  \
    TRAIL_RANGE=$TRAIL_RANGE1              \
    TRAIL_ANGLE=$TRAIL_ANGLE1

#-------------------------------------------------------
#  HUNTER
#-------------------------------------------------------
# nsplug meta_vehicle_sim_mokai.moos targ_hunter.moos -f WARP=$TIME_WARP \
#        VNAME=$VNAME3 \
#        OVNAME=$VNAME4      START_POS=$START_POS3                 \
#    VPORT="9003"       SHARE_LISTEN="9303"                   \
#    VTYPE="kayak"      SHORE_LISTEN=$SHORE_LISTEN            \
#    KNOWS_CONTACTS=1  SHORE_IP=$SHORE_IP

# nsplug meta_hunter.bhv targ_hunter.bhv -f VNAME=$VNAME3  \
#     START_POS=$START_POS3  \
#     TRAIL_RANGE=$TRAIL_RANGE1              \
#     TRAIL_ANGLE=$TRAIL_ANGLE1
#-------------------------------------------------------
#  MOKAI
#-------------------------------------------------------
nsplug meta_vehicle_sim_mokai.moos targ_$VNAME4.moos -f WARP=$TIME_WARP \
       VNAME=$VNAME4 \
   OVNAME=$VNAME4      START_POS=$START_POS4                 \
   VPORT="9004"       SHARE_LISTEN="9304"                   \
   VTYPE="kayak"    SHORE_LISTEN=$SHORE_LISTEN \
SHORE_IP=$SHORE_IP

nsplug meta_$VNAME4.bhv targ_$VNAME4.bhv -f VNAME=$VNAME4  \
    VNAME=$VNAME4 START_POS=$START_POS4 
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
#pAntler targ_${VNAME1}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME2}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME3 MOOS Community (WARP=%s) \n" $TIME_WARP
#pAntler targ_${VNAME3}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME4 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME4}.moos >& /dev/null &
sleep 0.25
printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done \n"

uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1 %2 %3 
printf "Done killing processes.   \n"



