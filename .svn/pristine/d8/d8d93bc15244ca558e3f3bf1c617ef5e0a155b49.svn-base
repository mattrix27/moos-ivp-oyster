#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
SHORE_IP=192.168.1.155
TIME_WARP=1
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
VNAME2="betty"         
VNAME3="charlie" #hunter"        
#VNAME4="jackal"

WPT_ORDER1="normal"
WPT_ORDER2="reverse"
WPT_ORDER3="normal"

RETURN_POS="0,0"

START_POS1="100,-20"
START_POS2="-100,-20"
START_POS3="0,-100"

SPEED1=2.0
SPEED2=2.0
SPEED3=1.3

LOITER_POS1="x=50,y=-125"
LOITER_POS2="x=100,y=-180"
LOITER_POS3="x=100,y=-180"

TRAIL_RANGE1="40"
TRAIL_ANGLE1="330"

SHORE_LISTEN="9300"

#-------------------------------------------------------
#  Part 2a: Geometries
#-------------------------------------------------------
# geom names: Geom_Direction_MinDist
# HP = home plate, DHP = double home plate '<==>', diamond,
# Direction: EW = east-west, NS = north-south, MIT = parallel to dock
# MinDist refers to smallest distance btwn waypoints (informs alert/kill dist) [m]

# original starburst
#SB_A="119.5,-146.6:80.5,-33.4" # 11-5
#SB_B="82.5,-147.3:117.5,-32.7" # 1-6
#SB_C="59.9,-134.5:140.1,-45.5" # 2-7
#SB_D="42,-105.5:158,-74.5" # 2.5-7.5
#SB_E="43.3,-70.5:156.7,-109.5" # 4-10
#SB_F="63.1,-42.7:136.9,-137.3" # 10.5-4.5
#SB_G="100,-30:100,-150" # 12-6

# translated 50 left, 20 down
SB_A="69.5,-166.6:30.5,-53.4" # 11-5
SB_B="22.5,-167.3:87.5,-52.7" # 1-6
SB_C="9.9,-154.5:110.1,-65.5" # 2-7
SB_D="-12,-125.5:128,-94.5" # 2.5-7.5
SB_E="-13.3,-90.5:126.7,-129.5" # 4-10
SB_F="13.1,-62.7:106.9,-157.3" # 10.5-4.5
SB_G="50,-50:70,-170" # 12-6

DHP_EW_35="80,-40:100,-70:80,-100:20,-100:0,-70:20,-40"
DHP_MIT_35="61.7,-29.2:93.7,-45.8:90.8,-81.7:38.3,-110.8:6.3,-94.2:9.2,-58.3"
DHP_NS_35="20,-30:50,-10:80,-30:80,-90:50,-110:20,-90"

DIAMOND_NS_35="20,-40:0,-70:20,-100:40,-70"
DIAMOND_MIT_35="56.8,-25.1:23.4,-38.8:23.2,-74.9:56.6,-61.2"

HP_EW_35="20,-40:0,-70:20,-100:60,-100:60,-40"
HP_MIT_35="18.4,-37.9:13,-73.5:43.8,-92.3:80.1,-75.4:54.7,-21"
HP_NS_35="42,-72:72,-92:102,-72:102,-32:42,-32"

SQUARE_NS_30="20,-10:20,-40:50,-40:50,-10"
SQUARE_MIT_30="14.9,-18.1:28.1,-45.1:55.1,-31.9:41.9,-4.9"

HP_NS_30="22.5,-9.2:22.5,-39.2:38,-55:52.5,-39.2:52.5,-9.2"

WPT_PTS1=$SB_B
WPT_PTS2=$SB_F
WPT_PTS3=$SB_D


#-------------------------------------------------------
#  USV #1
#-------------------------------------------------------

nsplug meta_vehicle.moos targ_archie.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME1          SHARE_LISTEN="9301"              \
    VPORT="9001"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS1  VARIATION=$VARIATION   \
       VTYPE="kayak"       SHORE_IP=$SHORE_IP

nsplug meta_vehicle.bhv targ_archie.bhv -f VNAME=$VNAME1  \
       RETURN_POS=$RETURN_POS LOITER_POS=$LOITER_POS1       \
       WPT_ORDER=$WPT_ORDER1 WPT_PTS=$WPT_PTS1   \
       SPEED=$SPEED1
#-------------------------------------------------------
#  USV #2
#-------------------------------------------------------
nsplug meta_vehicle.moos targ_betty.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME2          SHARE_LISTEN="9302"              \
    VPORT="9002"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS2  VARIATION=$VARIATION   \
       VTYPE="kayak"   SHORE_IP=$SHORE_IP

nsplug meta_vehicle.bhv targ_betty.bhv -f VNAME=$VNAME2  \
        RETURN_POS=$RETURN_POS LOITER_POS=$LOITER_POS2 \
       WPT_ORDER=$WPT_ORDER2 WPT_PTS=$WPT_PTS2 \
       SPEED=$SPEED2
#-------------------------------------------------------
#  USV #3
#-------------------------------------------------------
nsplug meta_vehicle.moos targ_charlie.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME3          SHARE_LISTEN="9303"              \
    VPORT="9003"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS3  VARIATION=$VARIATION   \
       VTYPE="kayak"   SHORE_IP=$SHORE_IP

nsplug meta_vehicle.bhv targ_charlie.bhv -f VNAME=$VNAME3  \
        RETURN_POS=$RETURN_POS LOITER_POS=$LOITER_POS3 \
       WPT_ORDER=$WPT_ORDER3 WPT_PTS=$WPT_PTS3 \
       SPEED=$SPEED3
#-------------------------------------------------------
#  HUNTER
# #-------------------------------------------------------
# nsplug meta_vehicle.moos targ_hunter.moos -f WARP=$TIME_WARP \
#        VNAME=$VNAME3 \
#        OVNAME=$VNAME4      START_POS=$START_POS3                 \
#    VPORT="9003"       SHARE_LISTEN="9303"                   \
#    VTYPE="kayak"      SHORE_LISTEN=$SHORE_LISTEN            \
#    KNOWS_CONTACTS=1  

#nsplug meta_hunter.bhv targ_hunter.bhv -f VNAME=$VNAME3  \
    START_POS=$START_POS3  \
    TRAIL_RANGE=$TRAIL_RANGE1              \
    TRAIL_ANGLE=$TRAIL_ANGLE1
#-------------------------------------------------------
#  JACKAL
#-------------------------------------------------------
#nsplug meta_vehicle.moos targ_jackal.moos -f WARP=$TIME_WARP \
       VNAME=$VNAME4 \
   OVNAME=$VNAME3      START_POS=$START_POS4                 \
   VPORT="9004"       SHARE_LISTEN="9304"                   \
   VTYPE="uuv"      SHORE_LISTEN=$SHORE_LISTEN   \
   SHORE_IP=$SHORE_IP

#nsplug meta_jackal.bhv targ_jackal.bhv -f VNAME=$VNAME4  \
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
pAntler targ_${VNAME1}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME2}.moos >& /dev/null &
sleep 0.25

printf "Launching $VNAME3 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME3}.moos >& /dev/null &
sleep 0.25

#printf "Launching $VNAME4 MOOS Community (WARP=%s) \n" $TIME_WARP
#pAntler targ_${VNAME4}.moos >& /dev/null &
#sleep 0.25
#printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
#pAntler targ_shoreside.moos >& /dev/null &
#printf "Done \n"

uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1 %2 %3 
printf "Done killing processes.   \n"



