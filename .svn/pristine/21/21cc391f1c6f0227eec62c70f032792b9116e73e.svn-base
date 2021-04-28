#!/bin/bash 

# M200_IP
#  Emulator running on same machine as vehicle:     localhost
#  Emulator running on different machine:           IP address of that machine (often 192.168.2.1)
#  Set by command line, with the following mapping
#  Actual evan vehicle:                              192.168.5.1
#  Actual felix vehicle:                             192.168.6.1
#  Actual gus vehicle:                               192.168.7.1
#  Actual hal vehile:                                192.168.8.1
#  Actual ida vehicle:                               192.168.9.1
#  Actual jing vehicle:                              192.168.10.1

# reasonable default, WILL BE OVERRIDDEN BY COMMAND LINE OPTIONS
M200_IP="localhost"
# M200_IP="192.168.6.1"

# SHORE_IP
#  Emulation, shoreside running on same machine as vehicle: localhost
#  Emulation, shoreside running on a different machine:     IP address of that machine (often 192.168.2.1)
#  Actual vehicle:                                          IP address of the shoreside computer
#SHORE_IP="localhost"
SHORE_IP="192.168.1.150"

WARP=1
HELP="no"
JUST_BUILD="no"
EVAN="no"
FELIX="no"
GUS="no"
HAL="no"
IDA="no"
JING="no"
BAD_ARGS=""
MOOS_FILE=""
BHV_FILE=""

printf "Initiate launch vehicle script\n"

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    UNDEFINED_ARG=$ARGI
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-hlp" ] ; then
	HELP="yes"
	UNDEFINED_ARG=""
    fi
    if [ "${ARGI}" = "--jing" -o "${ARGI}" = "-j" ] ; then
        JING="yes"
        UNDEFINED_ARG=""
        VNAME="jing"
        VPORT="9010"
        SHARE_LISTEN="9307"
        LOITER_PT="x=50,y=10"
        RETURN_PT="0,-20"
        MOOS_FILE="targ_jing.moos"
        BHV_FILE="targ_jing.bhv"
        M200_IP="192.168.10.1"
        printf "JING vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--ida" -o "${ARGI}" = "-i" ] ; then
        IDA="yes"
        UNDEFINED_ARG=""
        VNAME="ida"
        VPORT="9009"
        SHARE_LISTEN="9307"
        LOITER_PT="x=50,y=10"
        RETURN_PT="0,-20"
        MOOS_FILE="targ_ida.moos"
        BHV_FILE="targ_ida.bhv"
        M200_IP="192.168.9.1"
        printf "IDA vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--hal" -o "${ARGI}" = "-h" ] ; then
        HAL="yes"
        UNDEFINED_ARG=""
        VNAME="hal"
        VPORT="9008"
        SHARE_LISTEN="9307"
        LOITER_PT="x=50,y=10"
        RETURN_PT="0,-20"
        MOOS_FILE="targ_hal.moos"
        BHV_FILE="targ_hal.bhv"
        M200_IP="192.168.8.1"
        printf "HAL vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--gus" -o "${ARGI}" = "-g" ] ; then
        GUS="yes"
        UNDEFINED_ARG=""
        VNAME="gus"
        VPORT="9007"
        SHARE_LISTEN="9307"
        LOITER_PT="x=50,y=10"
        RETURN_PT="0,-20"
        MOOS_FILE="targ_gus.moos"
        BHV_FILE="targ_gus.bhv"
        M200_IP="192.168.7.1"
        printf "GUS vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--felix" -o "${ARGI}" = "-f" ] ; then
        FELIX="yes"
        UNDEFINED_ARG=""
        VNAME="felix"
        VPORT="9006"
        SHARE_LISTEN="9306"
        LOITER_PT="x=50,y=10"
        RETURN_PT="0,-20"
        MOOS_FILE="targ_felix.moos"
        BHV_FILE="targ_felix.bhv"
        M200_IP="192.168.6.1"
        printf "FELIX vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--evan" -o "${ARGI}" = "-e" ] ; then
        EVAN="yes"
        UNDEFINED_ARG=""
        VNAME="evan"
        VPORT="9005"
        SHARE_LISTEN="9305"
        LOITER_PT="x=50,y=0"
        RETURN_PT="30,-15"
        MOOS_FILE="targ_evan.moos"
        BHV_FILE="targ_evan.bhv"
        M200_IP="192.168.5.1"
        printf "EVAN vehicle selected.\n"
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

if [ "${EVAN}" = "no" -a "${FELIX}" = "no" -a "${GUS}" = "no" -a "${HAL}" = "no" -a "${IDA}" = "no" -a "${JING}" = "no" ] ; then
    printf "ONE vehicle MUST be selected!!!!!!!!!!!! \n"
    HELP="yes"
fi

if [ "${EVAN}" = "yes" -a "${FELIX}" = "yes" ] ; then
    printf "ONE vehicle MUST be selected!!!!!!!!!!!! \n"
    HELP="yes"
fi

if [ "${HELP}" = "yes" ]; then
    printf "%s [SWITCHES]            \n" $0
    printf "Switches:                \n"
    printf "  --evan, -e             evan vehicle only       \n"
    printf "  --felix, -f            felix vehicle only      \n"
    printf "  --gus, -g              gus vehicle only        \n"
    printf "  --hal, -h              hal vehicle only        \n"
    printf "  --ida, -i              ida vehicle only        \n"
    printf "  --jing, -j             jing vehicle only       \n"
    printf "  --just_build, -jb       \n" 
    printf "  --help, -hlp             \n" 
    exit 0;
fi

#-------------------------------------------------------
#  Part 3: Create the .moos and .bhv files. 
#-------------------------------------------------------

printf "Assembling MOOS file ${MOOS_FILE}\n"

CRUISESPEED="1.5"
SHORE_LISTEN="9300"

nsplug meta_vehicle_fld.moos ${MOOS_FILE} -f \
    VNAME=$VNAME                   \
	VPORT=$VPORT               \
	WARP=$WARP                 \
	SHARE_LISTEN=$SHARE_LISTEN \
	SHORE_LISTEN=$SHORE_LISTEN \
	SHORE_IP=$SHORE_IP         \
        M200_IP=$M200_IP           \
	HOSTIP_FORCE="localhost" 

printf "Assembling BHV file $BHV_FILE\n"
nsplug meta_vehicle.bhv $BHV_FILE -f                  \
    VNAME=$VNAME                                      \
	SPEED=$CRUISESPEED                                \
    ORDER="normal"

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

