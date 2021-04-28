#!/bin/bash 
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
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
MAJOR1=175
MINOR1=175
CENTER1=60
BASE_WIDTH_F1=10
PEAK_WIDTH_F1=10
BUFFER_DISTANCE1=50
BASE_WIDTH_C1=5
PEAK_WIDTH_C1=5
BASE_WIDTH_Z1=30
PEAK_WIDTH_Z1=10
PERCENT_TEMP_HOT=0.98
PERCENT_TEMP_COLD=1.04
ZIG_ANGLE1=70
ZIG_DURATION1=35

COMMS_PERIOD=15
COMMS_LENGTH=2048

for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES] [time_warp]   \n" $0
	printf "  --just_make, -j    \n" 
	printf "  --vname=VNAME      \n" 
	printf "  --help, -h         \n"
	printf "  --warp=WARP_VALUE      \n"
	printf "  --adaptive, -a         \n"
	printf "  --unconcurrent, -uc       \n"
	printf "  --angle=DEGREE_VALUE   \n"
	printf "  --cool=COOL_FAC        \n"
	exit 0;
    elif [ "${ARGI:0:8}" = "--vname=" ] ; then
        VNAME="${ARGI#--vname=*}"
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then 
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
	JUST_MAKE="yes"
    elif [ "${ARGI:0:6}" = "--warp" ] ; then
        WARP="${ARGI#--warp=*}"
        UNDEFINED_ARG=""
    elif [ "${ARGI:0:6}" = "--cool" ] ; then
        COOL_FAC="${ARGI#--cool=*}"
        UNDEFINED_ARG=""
    elif [ "${ARGI:0:7}" = "--angle" ] ; then
        DEGREES1="${ARGI#--angle=*}"
        UNDEFINED_ARG=""
    elif [ "${ARGI}" = "--unconcurrent" -o "${ARGI}" = "-uc" ] ; then
        CONCURRENT="false"
        UNDEFINED_ARG=""
    elif [ "${ARGI}" = "--adaptive" -o "${ARGI}" = "-a" ] ; then
        ADAPTIVE="true"
        UNDEFINED_ARG=""
    else 
	printf "Bad Argument: %s \n" $ARGI
	exit 0
    fi
done

#-------------------------------------------------------
#  Part 2: Create the .moos and .bhv files. 
#-------------------------------------------------------

START_POS="0,0"

#start first vehicle:                                                                                                                                                                                                                         
nsplug meta_vehicle.moos targ_$VNAME.moos -f WARP=$TIME_WARP  \
   VNAME=$VNAME      START_POS=$START_POS                    \
   VPORT="9001"       SHARE_LISTEN="9301"                      \
   VTYPE=KAYAK          COOL_FAC=$COOL_FAC  COOL_STEPS=$COOL_STEPS\
   CONCURRENT=$CONCURRENT  ADAPTIVE=$ADAPTIVE \
   COMMS_PERIOD=$COMMS_PERIOD  COMMS_LENGTH=$COMMS_LENGTH

nsplug meta_vehicle.bhv targ_$VNAME.bhv -f VNAME=$VNAME      \
    START_POS=$START_POS SURVEY_X=$SURVEY_X SURVEY_Y=$SURVEY_Y \
        HEIGHT=$HEIGHT1    WIDTH=$WIDTH1 LANE_WIDTH=$LANE_WIDTH1 \
        DEGREES=$DEGREES1  PTS=$PTS1  MAJOR=$MAJOR1  MINOR=$MINOR1 \
	CENTER=$CENTER1 BASE_WIDTH_F=$BASE_WIDTH_F1 \
	PEAK_WIDTH_F=$PEAK_WIDTH_F1 BUFFER_DISTANCE=$BUFFER_DISTANCE1 \
	BASE_WIDTH_C=$BASE_WIDTH_C1 PEAK_WIDTH_C=$PEAK_WIDTH_C1  \
	BASE_WIDTH_Z=$BASE_WIDTH_Z1 PEAK_WIDTH_Z=$PEAK_WIDTH_Z1  \
	PERCENT_TEMP_HOT=$PERCENT_TEMP_HOT PERCENT_TEMP_COLD=$PERCENT_TEMP_COLD \
	ZIG_ANGLE=$ZIG_ANGLE1      ZIG_DURATION=$ZIG_DURATION1

if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------
printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME.moos >& /dev/null &

uMAC targ_$VNAME.moos

kill %1 
printf "Done.   \n"


