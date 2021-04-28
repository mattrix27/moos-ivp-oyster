#!/bin/bash 

# M200_IP
#  Emulator running on same machine as vehicle:     localhost
#  Emulator running on different machine:           IP address of that machine (often 192.168.2.1)
#  Actual evan vehicle:                             192.168.5.1
#  Actual felix vehile:                             192.168.6.1
#  Actual gus vehicle:                              192.168.7.1
M200_IP="192.168.5.1"


# SHORE_IP
#  Emulation, shoreside running on same machine as vehicle: localhost
#  Emulation, shoreside running on a different machine:     IP address of that machine (often 192.168.2.1)
#  Actual vehicle:                                          IP address of the shoreside computer
SHORE_IP="192.168.1.247"

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------


JUST_MAKE="no"
VNAME="archie"
COOL_FAC=50
COOL_STEPS=1000
CONCURRENT="true"
ADAPTIVE="false"
SURVEY_X=60
SURVEY_Y=-105
HEIGHT1=150
WIDTH1=120
LANE_WIDTH1=25
DEGREES1=0
PTS1=30
MAJOR1=150
MINOR1=150
CENTER1=60
BASE_WIDTH_F1=10
PEAK_WIDTH_F1=10
BUFFER_DISTANCE1=50
BASE_WIDTH_C1=5
PEAK_WIDTH_C1=5
BASE_WIDTH_Z1=20
PEAK_WIDTH_Z1=30
PERCENT_TEMP_HOT=0.98
PERCENT_TEMP_COLD=1.04
ZIG_ANGLE1=70
ZIG_DURATION1=25

COMMS_LENGTH=15
COMMS_PERIOD=2048


TIME_WARP=1
HELP="no"
JUST_BUILD="no"
EVAN="no"
FELIX="no"
GUS="no"
BAD_ARGS=""
MOOS_FILE=""
BHV_FILE=""
VTYPE="KAYAK"

printf "Initiate launch vehicle script\n"


for ARGI; do
    UNDEFINED_ARG=$ARGI
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	HELP="yes"
	UNDEFINED_ARG=""
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
        printf "EVAN vehicle selected.\n"
    fi
    if [ "${ARGI}" = "--gus" -o "${ARGI}" = "-g" ] ; then
        GUS="yes"
        UNDEFINED_ARG=""
        VNAME="gus"
        VPORT="9007"
        SHARE_LISTEN="9307"
        LOITER_PT="x=50,y=0"
        RETURN_PT="30,25"
        MOOS_FILE="targ_gus.moos"
        BHV_FILE="targ_gus.bhv"
        printf "GUS vehicle selected.\n"
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

if [ "${EVAN}" = "no" -a "${FELIX}" = "no" -a "${GUS}" = "no" ] ; then
    printf "ONE vehicle MUST be selected!!!!!!!!!!!! \n"
    HELP="yes"
fi

if [ "${EVAN}" = "yes" -a "${FELIX}" = "yes" ] ; then
    printf "ONE vehicle MUST be selected!!!!!!!!!!!! \n"
    HELP="yes"
fi

if [ "${EVAN}" = "yes" -a "${GUS}" = "yes" ] ; then
    printf "ONE vehicle MUST be selected!!!!!!!!!!!! \n"
    HELP="yes"
fi

if [ "${GUS}" = "yes" -a "${FELIX}" = "yes" ] ; then
    printf "ONE vehicle MUST be selected!!!!!!!!!!!! \n"
    HELP="yes"
fi

if [ "${HELP}" = "yes" ]; then
    printf "%s [SWITCHES]            \n" $0
    printf "Switches:                \n"
    printf "  --evan, -e             evan vehicle only       \n"
    printf "  --felix, -f            felix vehicle only      \n"
    printf "  --gus, -f              gus vehicle only        \n"
    printf "  --just_build, -j       \n" 
    printf "  --help, -h             \n"
    printf"  --adaptive, -a         \n"
    printf"  --unconcurrent, -c     \n"
    printf"  --cool=COOL_FAC        \n"
    exit 0;
fi

#-------------------------------------------------------
#  Part 3: Create the .moos and .bhv files. 
#-------------------------------------------------------

printf "Assembling MOOS file ${MOOS_FILE}\n"

START_POS="0,0"
#CRUISESPEED="1.5"
SHORE_LISTEN="9300"

nsplug meta_vehicle_fld.moos ${MOOS_FILE} -f \
   VNAME=$VNAME \
   VTYPE=$VTYPE               \
   START_POS=$START_POS       \
   VPORT=$VPORT               \
   WARP=$TIME_WARP            \
   SHARE_LISTEN=$SHARE_LISTEN \
   SHORE_LISTEN=$SHORE_LISTEN \
   SHORE_IP=$SHORE_IP         \
   M200_IP=$M200_IP           \
   HOSTIP_FORCE="localhost"   \
   COOL_FAC=$COOL_FAC         \
   COOL_STEPS=$COOL_STEPS     \
   CONCURRENT=$CONCURRENT     \
   ADAPTIVE=$ADAPTIVE 

printf "Assembling BHV file $BHV_FILE\n"
nsplug meta_vehicle.bhv ${BHV_FILE} -f \
   VNAME=$VNAME    \
   START_POS=$START_POS  \
   SURVEY_X=$SURVEY_X  \
   SURVEY_Y=$SURVEY_Y  \
   DEGREES=$DEGREES1  \
   PTS=$PTS1          \
   CENTER=$CENTER1  \
   MAJOR=$MAJOR1  \
   MINOR=$MINOR1  \
   PEAK_WIDTH_F=$PEAK_WIDTH_F1  \
   BASE_WIDTH_F=$BASE_WIDTH_F1  \
   BUFFER_DISTANCE=$BUFFER_DISTANCE1  \
   BASE_WIDTH_C=$BASE_WIDTH_C1  \
   PEAK_WIDTH_C=$PEAK_WIDTH_C1  \
   BASE_WIDTH_Z=$BASE_WIDTH_Z1  \
   PEAK_WIDTH_Z=$PEAK_WIDTH_Z1  \
   PERCENT_TEMP_HOT=$PERCENT_TEMP_HOT  \
   PERCENT_TEMP_COLD=$PERCENT_TEMP_COLD \
   ZIG_ANGLE=$ZIG_ANGLE1        \
   ZIG_DURATION=$ZIG_DURATION1 \
   COMMS_PERIOD=$COMMS_PERIOD \
   COMMS_LENGTH=$COMMS_LENGTH

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
#pAntler targ_$VNAME.moos >& /dev/null &
#uMAC targ_$VNAME.moos


# %1 matches the PID of the first job in the active jobs list, 
# namely the pAntler job launched in Part 4.
if [ "${ANSWER}" = "2" ]; then
    printf "Killing all processes ... \n "
    kill %1 
    printf "Done killing processes.   \n "
fi

