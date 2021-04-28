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
SHORE_IP=192.168.1.150
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

SPEEDV=2.3

WPT_ORDERV="reverse"

RETURN_POSV="27,-6"

LOITER_POSV="x=50,y=-125"
LOITER_PT="x=50,y=0"
META_FILE="meta_vehicle_fld.moos"

printf "Initiate launch vehicle script\n"

if [ "$#" -eq 0 ]; then
    HELP="yes"
fi

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    UNDEFINED_ARG=$ARGI
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-H" ] ; then
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
        MOOS_FILE="targ_evan.moos"
        BHV_FILE="targ_evan.bhv"
        printf "EVAN vehicle selected as HUNTER.\n"
    fi
        if [ "${ARGI}" = "--felix" -o "${ARGI}" = "-f" ] ; then
	M200_IP=192.168.6.1 #felix
        FELIX="yes"
        UNDEFINED_ARG=""
        VNAME="felix"
        VPORT="9006"
        SHARE_LISTEN="9306"
        MOOS_FILE="targ_felix.moos"
        BHV_FILE="targ_felix.bhv"
        printf "FELIX vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--gus" -o "${ARGI}" = "-g" ] ; then
	M200_IP=192.168.7.1 #gus
        GUS="yes"
        UNDEFINED_ARG=""
        VNAME="gus"
        VPORT="9007"
        SHARE_LISTEN="9307"
        MOOS_FILE="targ_gus.moos"
        BHV_FILE="targ_gus.bhv"
        printf "GUS vehicle selected as HUNTER.\n"
    fi
    if [ "${ARGI}" = "--hal" -o "${ARGI}" = "-h" ] ; then
	M200_IP=192.168.8.1 #hal
        HAL="yes"
        UNDEFINED_ARG=""
        VNAME="hal"
        VPORT="9008"
        SHARE_LISTEN="9308"
        MOOS_FILE="targ_hal.moos"
        BHV_FILE="targ_hal.bhv"
        printf "HAL vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--ida" -o "${ARGI}" = "-i" ] ; then
	M200_IP=192.168.9.1 #ida
        IDA="yes"
        UNDEFINED_ARG=""
        VNAME="ida"
        VPORT="9009"
        SHARE_LISTEN="9309"
        MOOS_FILE="targ_ida.moos"
        BHV_FILE="targ_ida.bhv"
        printf "IDA vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--jing" -o "${ARGI}" = "-j" ] ; then
	M200_IP=192.168.10.1 #jing
        JING="yes"
        UNDEFINED_ARG=""
        VNAME="jing"
        VPORT="9010"
        SHARE_LISTEN="9310"
        MOOS_FILE="targ_jing.moos"
        BHV_FILE="targ_jing.bhv"
        printf "JING vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--kirk" -o "${ARGI}" = "-k" ] ; then
	M200_IP=192.168.11.1 #kirk
        KIRK="yes"
        UNDEFINED_ARG=""
        VNAME="kirk"
        VPORT="9011"
        SHARE_LISTEN="9311"
        MOOS_FILE="targ_kirk.moos"
        BHV_FILE="targ_kirk.bhv"
        printf "KIRK vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-jb" ] ; then
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
    printf "  --hal, -h              hal vehicle hunter                     \n"
    printf "  --ida, -i              ida vehicle hunter                     \n"
    printf "  --jing, -j             jing vehicle hunter                     \n"
    printf "  --kirk, -k             kirk vehicle hunter                     \n"
    printf "  --just_build, -jb       \n" 
    printf "  --help, -H             \n" 
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
       VTYPE="kayak"   

printf "Assembling BHV file $BHV_FILE\n"
nsplug meta_hunter.bhv $BHV_FILE -f   \
       VNAME=$VNAME                    \
       SPEED=$SPEEDV                   \
       RETURN_POS=${RETURN_POSV}         \
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

