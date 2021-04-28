#!/bin/bash 

# M200_IP
#  Emulator running on same machine as vehicle:     localhost
#  Emulator running on different machine:           IP address of that machine (often 192.168.2.1)
#  Actual evan vehicle:                             192.168.5.1
#  Actual felix vehile:                             192.168.6.1
#M200_IP="localhost"
#M200_IP=192.168.5.1 #evan
#M200_IP=192.168.6.1 #felix

# SHORE_IP
#  Emulation, shoreside running on same machine as vehicle: localhost
#  Emulation, shoreside running on a different machine:     IP address of that machine (often 192.168.2.1)
#  Actual vehicle:                                          IP address of the shoreside computer
#SHORE_IP="localhost"
SHORE_IP=192.168.1.155
TRAIL_ANGLE1="330"
WARP=1
HELP="no"
JUST_BUILD="no"
EVAN="no"
FELIX="no"
GUS="no"
HAL="no"
IDA="no"
JING="no"
KIRK="no"
BAD_ARGS=""
MOOS_FILE=""
BHV_FILE=""

#-------------------------------------------------------
#  Part 0: Geometry Configurations
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

WPT_PTSA=$HP_MIT_35
WPT_PTSB=$SB_C
WPT_PTSE=$SB_C
WPT_PTSF=$SB_E

SPEEDA=2.3
SPEEDB=2.3
SPEEDE=2.3
SPEEDF=2.3

WPT_ORDERA="reverse"
WPT_ORDERB="reverse"
WPT_ORDERE="reverse"
WPT_ORDERF="reverse"

RETURN_POSA="27,-6"
RETURN_POSB="27,-6"
RETURN_POSE="27,-6"
RETURN_POSF="24,-9"

LOITER_POSA="x=50,y=-125"
LOITER_POSB="x=50,y=-125"
LOITER_POSE="x=100,y=-180"
LOITER_POSF="x=100,y=-180"

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
        LOITER_PT="x=50,y=0"
	META_FILE="meta_vehicle_fld.moos"
        MOOS_FILE="targ_evan.moos"
        BHV_FILE="targ_evan.bhv"
        printf "EVAN vehicle selected as HUNTER.\n"
        WPT_ORDERV=${WPT_ORDERE}
        SPEEDV=$SPEEDE
        LOITER_POSV=$LOITER_POSE
        WPT_PTSV=$WPT_PTSE
	RETURN_POSV=$RETURN_POSE
    fi
        if [ "${ARGI}" = "--felix" -o "${ARGI}" = "-f" ] ; then
	M200_IP=192.168.6.1 #felix
        FELIX="yes"
        UNDEFINED_ARG=""
        VNAME="felix"
        VPORT="9006"
        SHARE_LISTEN="9306"
        LOITER_PT="x=50,y=10"
	META_FILE="meta_vehicle_fld.moos"
        MOOS_FILE="targ_felix.moos"
        BHV_FILE="targ_felix.bhv"
        printf "FELIX vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERF}
        SPEEDV=$SPEEDF
        LOITER_POSV=$LOITER_POSF
        WPT_PTSV=$WPT_PTSF
	RETURN_POSV=$RETURN_POSF
    fi
    if [ "${ARGI}" = "--gus" -o "${ARGI}" = "-g" ] ; then
	M200_IP=192.168.7.1 #gus
        GUS="yes"
        UNDEFINED_ARG=""
        VNAME="gus"
        VPORT="9007"
        SHARE_LISTEN="9307"
        LOITER_PT="x=50,y=0"
	META_FILE="meta_vehicle_fld.moos"
        MOOS_FILE="targ_gus.moos"
        BHV_FILE="targ_gus.bhv"
        printf "GUS vehicle selected as HUNTER.\n"
        WPT_ORDERV=${WPT_ORDERE}
        SPEEDV=$SPEEDE
        LOITER_POSV=$LOITER_POSE
        WPT_PTSV=$WPT_PTSE
	RETURN_POSV=$RETURN_POSE
    fi
    if [ "${ARGI}" = "--hal" -o "${ARGI}" = "-H" ] ; then
	M200_IP=192.168.8.1 #hal
        HAL="yes"
        UNDEFINED_ARG=""
        VNAME="hal"
        VPORT="9008"
        SHARE_LISTEN="9308"
        LOITER_PT="x=50,y=10"
	META_FILE="meta_vehicle_fld.moos"
        MOOS_FILE="targ_hal.moos"
        BHV_FILE="targ_hal.bhv"
        printf "HAL vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERF}
        SPEEDV=$SPEEDF
        LOITER_POSV=$LOITER_POSF
        WPT_PTSV=$WPT_PTSF
	RETURN_POSV=$RETURN_POSF
    fi
    if [ "${ARGI}" = "--ida" -o "${ARGI}" = "-i" ] ; then
	M200_IP=192.168.9.1 #ida
        IDA="yes"
        UNDEFINED_ARG=""
        VNAME="ida"
        VPORT="9009"
        SHARE_LISTEN="9309"
        LOITER_PT="x=50,y=10"
	META_FILE="meta_vehicle_fld.moos"
        MOOS_FILE="targ_ida.moos"
        BHV_FILE="targ_ida.bhv"
        printf "IDA vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERF}
        SPEEDV=$SPEEDF
        LOITER_POSV=$LOITER_POSF
        WPT_PTSV=$WPT_PTSF
	RETURN_POSV=$RETURN_POSF
    fi
    if [ "${ARGI}" = "--jing" -o "${ARGI}" = "-J" ] ; then
	M200_IP=192.168.10.1 #jing
        JING="yes"
        UNDEFINED_ARG=""
        VNAME="jing"
        VPORT="9010"
        SHARE_LISTEN="9310"
        LOITER_PT="x=50,y=10"
	META_FILE="meta_vehicle_fld.moos"
        MOOS_FILE="targ_jing.moos"
        BHV_FILE="targ_jing.bhv"
        printf "JING vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERF}
        SPEEDV=$SPEEDF
        LOITER_POSV=$LOITER_POSF
        WPT_PTSV=$WPT_PTSF
	RETURN_POSV=$RETURN_POSF
    fi
    if [ "${ARGI}" = "--kirk" -o "${ARGI}" = "-k" ] ; then
	M200_IP=192.168.11.1 #kirk
        KIRK="yes"
        UNDEFINED_ARG=""
        VNAME="kirk"
        VPORT="9011"
        SHARE_LISTEN="9311"
        LOITER_PT="x=50,y=10"
	META_FILE="meta_vehicle_fld.moos"
        MOOS_FILE="targ_kirk.moos"
        BHV_FILE="targ_kirk.bhv"
        printf "KIRK vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERF}
        SPEEDV=$SPEEDF
        LOITER_POSV=$LOITER_POSF
        WPT_PTSV=$WPT_PTSF
	RETURN_POSV=$RETURN_POSF
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

#-------------------------------------------------------
#  Part 2: Handle Ill-formed command-line arguments
#-------------------------------------------------------

if [ "${BAD_ARGS}" != "" ] ; then
    printf "Bad Argument: %s \n" $BAD_ARGS
    exit 0
fi

#if [ "${EVAN}" = "no" -a "${FELIX}" = "no" ] ; then
#    printf "ONE vehicle MUST be selected!!!!!!!!!!!! \n"
#    HELP="yes"
#fi

#if [ "${EVAN}" = "yes" -a "${FELIX}" = "yes" ] ; then
#    printf "ONE vehicle MUST be selected!!!!!!!!!!!! \n"
#    HELP="yes"
#fi

if [ "${HELP}" = "yes" ]; then
    printf "%s [SWITCHES]            \n" $0
    printf "Switches:                \n"
    printf "  --evan, -e             evan vehicle hunter                     \n"
    printf "  --felix, -f            felix vehicle hunter                     \n"
    printf "  --gus, -g              gus vehicle hunter                     \n"
    printf "  --hal, -H              hal vehicle hunter                     \n"
    printf "  --ida, -i              ida vehicle hunter                     \n"
    printf "  --jing, -J             jing vehicle hunter                     \n"
    printf "  --kirk, -k             kirk vehicle hunter                     \n"
    printf "  --just_build, -j       \n" 
    printf "  --help, -h             \n" 
    exit 0;
fi



#-------------------------------------------------------
#  Part 3: Create the .moos and .bhv files. 
#-------------------------------------------------------

printf "Assembling MOOS file ${MOOS_FILE}\n"

#CRUISESPEED="1.5"
SHORE_LISTEN="9300"

nsplug ${META_FILE} ${MOOS_FILE} -f \
       VNAME=$VNAME                   \
       VPORT=$VPORT               \
       WARP=$WARP                 \
       SHARE_LISTEN=$SHARE_LISTEN \
       SHORE_LISTEN=$SHORE_LISTEN \
       SHORE_IP=$SHORE_IP         \
       M200_IP=$M200_IP           \
       HOSTIP_FORCE="localhost"   \
       LOITER_POS=$LOITER_POSV \
       VARIATION=$VARIATION   \
       VTYPE="kayak"   

printf "Assembling BHV file $BHV_FILE\n"
nsplug meta_hunter.bhv $BHV_FILE -f   \
       VNAME=$VNAME                    \
       SPEED=$SPEEDV                   \
       RETURN_POS=${RETURN_POSV}         \
       LOITER_POS=${LOITER_POSV}       \
       WPT_ORDER=$WPT_ORDERV           \
       WPT_PTS=$WPT_PTSV               \
       START_POS=$RETURN_POSE  \
    TRAIL_RANGE=$TRAIL_RANGE1  \
    TRAIL_ANGLE=$TRAIL_ANGLE1 \

       
if [ ${JUST_BUILD} = "yes" ] ; then
    printf "Files assembled; vehicle not launched; exiting per request.\n"
    exit 0
fi

#-------------------------------------------------------
#  Part 4: Launch the processes
#-------------------------------------------------------

printf "Launching $VNAME MOOS Community \n"
pAntler $MOOS_FILE >& /dev/null &
uMAC $MOOS_FILE

# %1 matches the PID of the first job in the active jobs list, 
# namely the pAntler job launched in Part 4.
if [ "${ANSWER}" = "2" ]; then
    printf "Killing all processes ... \n "
    kill %1 
    printf "Done killing processes.   \n "
fi

