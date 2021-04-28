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


WARP=1
HELP="no"
JUST_BUILD="no"
ARCHIE="no"
BETTY="no"
EVAN="no"
FELIX="no"
GUS="no"
MOKAI="no"
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

WPT_PTSA=$SB_D
WPT_PTSB=$SB_D
WPT_PTSE=$SB_B
WPT_PTSF=$SB_B

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
DOT_MOOS="meta_vehicle_fld.moos"

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
    if [ "${ARGI}" = "--archie" -o "${ARGI}" = "-a" ] ; then
        M200_IP=192.168.1.171 #archie
        ARCHIE="yes"
        UNDEFINED_ARG=""
        VNAME="archie"
        VPORT="9001"
        SHARE_LISTEN="9301"
        LOITER_PT="x=50,y=10"
        MOOS_FILE="targ_archie.moos"
        BHV_FILE="targ_archie.bhv"
        DOT_MOOS="meta_vehicle_m100.moos"
        printf "ARCHIE vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERA}
        SPEEDV=$SPEEDA
        LOITER_POSV=$LOITER_POSA
        WPT_PTSV=$WPT_PTSA
        RETURN_POSV=$RETURN_POSA
    fi
    if [ "${ARGI}" = "--mokai" -o "${ARGI}" = "-m" ] ; then
        M200_IP=192.168.1.206 #mokai
        MOKAI="yes"
        UNDEFINED_ARG=""
        VNAME="mokai"
        VPORT="9013"
        SHARE_LISTEN="9313"
        LOITER_PT="x=50,y=10"
        MOOS_FILE="targ_mokai.moos"
        BHV_FILE="targ_mokai.bhv"
        DOT_MOOS="meta_vehicle_mokai.moos"
        printf "MOKAI vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERA}
        SPEEDV=$SPEEDA
        LOITER_POSV=$LOITER_POSA
        WPT_PTSV=$WPT_PTSA
        RETURN_POSV=$RETURN_POSA
    fi
    if [ "${ARGI}" = "--betty" -o "${ARGI}" = "-b" ] ; then
        M200_IP=192.168.1.172 #betty
        BETTY="yes"
        UNDEFINED_ARG=""
        VNAME="betty"
        VPORT="9002"
        SHARE_LISTEN="9302"
        LOITER_PT="x=50,y=10"
        MOOS_FILE="targ_betty.moos"
        BHV_FILE="targ_betty.bhv"
        DOT_MOOS="meta_vehicle_m100.moos"
        printf "BETTY vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERB}
        SPEEDV=$SPEEDB
        LOITER_POSV=$LOITER_POSB
        WPT_PTSV=$WPT_PTSB
        RETURN_POSV=$RETURN_POSB
    fi

    if [ "${ARGI}" = "--felix" -o "${ARGI}" = "-f" ] ; then
        M200_IP=192.168.6.1 #felix
        FELIX="yes"
        UNDEFINED_ARG=""
        VNAME="felix"
        VPORT="9006"
        SHARE_LISTEN="9306"
        LOITER_PT="x=50,y=10"
        MOOS_FILE="targ_felix.moos"
        BHV_FILE="targ_felix.bhv"
        printf "FELIX vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERF}
        SPEEDV=$SPEEDF
        LOITER_POSV=$LOITER_POSF
        WPT_PTSV=$WPT_PTSF
        RETURN_POSV=$RETURN_POSF
    fi
    if [ "${ARGI}" = "--evan" -o "${ARGI}" = "-e" ] ; then
        M200_IP=192.168.5.1 #evan
        EVAN="yes"
        UNDEFINED_ARG=""
        VNAME="evan"
        VPORT="9005"
        SHARE_LISTEN="9305"
        LOITER_PT="x=50,y=0"
        MOOS_FILE="targ_evan.moos"
        BHV_FILE="targ_evan.bhv"
        printf "EVAN vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERE}
        SPEEDV=$SPEEDE
        LOITER_POSV=$LOITER_POSE
        WPT_PTSV=$WPT_PTSE
        RETURN_POSV=$RETURN_POSE
    fi
    if [ "${ARGI}" = "--gus" -o "${ARGI}" = "-g" ] ; then
        M200_IP=192.168.7.1 #gus
        GUS="yes"
        UNDEFINED_ARG=""
        VNAME="gus"
        VPORT="9007"
        SHARE_LISTEN="9307"
        LOITER_PT="x=50,y=0"
        MOOS_FILE="targ_gus.moos"
        BHV_FILE="targ_gus.bhv"
        printf "GUS vehicle selected.\n"
        WPT_ORDERV=${WPT_ORDERE}
        SPEEDV=$SPEEDE
        LOITER_POSV=$LOITER_POSE
        WPT_PTSV=$WPT_PTSE
        RETURN_POSV=$RETURN_POSE
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
    printf "  --evan, -e             evan vehicle only                     \n"
    printf "  --felix, -f            felix vehicle only                    \n"
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

nsplug ${DOT_MOOS} ${MOOS_FILE} -f \
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
nsplug meta_vehicle.bhv $BHV_FILE -f   \
       VNAME=$VNAME                    \
       SPEED=$SPEEDV                   \
       RETURN_POS=${RETURN_POSV}         \
       LOITER_POS=${LOITER_POSV}       \
       WPT_ORDER=$WPT_ORDERV           \
       WPT_PTS=$WPT_PTSV               \


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
