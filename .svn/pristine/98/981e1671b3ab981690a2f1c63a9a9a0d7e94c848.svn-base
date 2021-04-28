#!/bin/bash 

# SHORE_IP
SHORE_IP="192.168.1.151"

TIME_WARP=1
JUST_BUILD="no"
MOOS_FILE="targ_mokai.moos"

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES] [time_warp]\n" $0
	printf "Switches:\n"
        printf "  --localhost, -l\n"
	printf "  --just_build, -j\n" 
	printf "  --help, -h\n" 
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then 
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
	JUST_BUILD="yes"
    elif [ "${ARGI}" = "--localhost" -o "${ARGI}" = "-l" ] ; then
        SHORE_IP="localhost"
    else 
	printf "Bad Argument: %s \n" $ARGI
	exit 0
    fi
done

#-------------------------------------------------------
#  Part 2: Handle Ill-formed command-line arguments
#-------------------------------------------------------




#-------------------------------------------------------
#  Part 3: Create the .moos and .bhv files. 
#-------------------------------------------------------

printf "Assembling MOOS file ${MOOS_FILE}\n"
printf "Shoreside comms at ${SHORE_IP}\n"

VPORT="9001"
VNAME="mokai"
SHORE_LISTEN="9300"
SHARE_LISTEN="9301"

nsplug meta_vehicle_fld.moos ${MOOS_FILE} -f                   \
       VNAME=$VNAME               VPORT=$VPORT                 \
       WARP=$TIME_WARP            SHORE_IP=$SHORE_IP           \
       SHORE_IP=$SHORE_IP                                      \
       SHARE_LISTEN=$SHARE_LISTEN SHORE_LISTEN=$SHORE_LISTEN

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

