#!/bin/bash
WARP=1

SHORE_IP=192.168.1.155
SHORE_LISTEN="9300"

TRAIL_RANGE="3"
TRAIL_ANGLE="330"
VNAME="evan"
VTEAM="red"
JUST_BUILD="no"

PLAYBOOK="meta_heron.bhv"
VERBOSE="false"
START_POS=""
RETURN_POS=""
LOITER_POS="x=100,y=-180"
GRAB_POS=""
UNTAG_POS=""
DEFEND_POS=""
SIM="NO"

printf "Initiate launch vehicle script\n"

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES]                                             \n" $0
	printf "Switches:                                                 \n"
	printf "  --vname=NAME      Set vehicle name {evan,felix,gus,hal} \n"
	printf "  --vteam=TEAM      Set team name {red,blue}              \n"
	printf "  --warp=WARP       Set the time warp (Simulation only)   \n"
	printf "  --sim, -s         Simulation mode                       \n"
	printf "  --just_build, -j  Just build files                      \n"
	printf "  --help, -h                                              \n"
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$WARP" = 1 ]; then
        WARP=$ARGI
    elif [ "${ARGI:0:7}" = "--warp=" ] ; then
        WARP="${ARGI#--warp=*}"
    elif [ "${ARGI:0:8}" = "--vname=" ] ; then
        VNAME="${ARGI#--vname=*}"
    elif [ "${ARGI:0:8}" = "--vteam=" ] ; then
        VTEAM="${ARGI#--vteam=*}"
    elif [ "${ARGI:0:11}" = "--startpos=" ] ; then
        START_POS="${ARGI#--startpos=*}"
    elif [ "${ARGI:0:11}" = "--playbook=" ] ; then
        PLAYBOOK="${ARGI#--playbook=*}"
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_BUILD="yes"
    elif [ "${ARGI}" = "--sim" -o "${ARGI}" = "-s" ] ; then
        SIM="YES"
	SHORE_IP="localhost"
    else
	printf "Bad Argument: %s \n" $BAD_ARGS ". Use --help"
	exit 0
    fi
done

if [ "${SIM}" = "NO" -a "$TIME_WARP" != 1 ]; then
    printf "WARP other than 1 can only be used in simulation. Exiting. \n"
    exit 1
fi



#-------------------------------------------------------
# Part 2: Set Vehicle specific parameters
#-------------------------------------------------------
if [ "${VNAME}" = "evan" ] ; then
    M300_IP=192.168.5.1 #evan
    VPORT="9005"
    SHARE_LISTEN="9305"
elif [ "${VNAME}" = "felix" ] ; then
    M300_IP=192.168.6.1 #felix
    VPORT="9006"
    SHARE_LISTEN="9306"
elif [ "${VNAME}" = "gus" ] ; then
    M300_IP=192.168.7.1 #gus
    VPORT="9007"
    SHARE_LISTEN="9307"
elif [ "${VNAME}" = "hal" ] ; then
    M300_IP=192.168.8.1 #hal
    VPORT="9008"
    SHARE_LISTEN="9308"
else
    printf "Unrecognized or no vehicle name selected: $VNAME \n";
    exit 1
fi

printf "$VNAME vehicle selected.  \n"
    
#-------------------------------------------------------
# Part 3: Set Team specific parameters
#-------------------------------------------------------
if [ "${VTEAM}" = "red" ] ; then
    GRAB_POS="-57,-71"
    RETURN_POS="50,-26"
    UNTAG_POS="50,-26"     
    DEFEND_POS="25,-37"     
elif [ "${VTEAM}" = "blue" ] ; then
    GRAB_POS="50,-26"
    RETURN_POS="-57,-71"
    UNTAG_POS="-57,-71"    
    DEFEND_POS="-25,-62"    
else
    printf "Unrecognized or no vehicle team selected: $VTEAM \n";
    exit 1
fi

printf "$VTEAM vehicle team selected.  \n"
    
#-------------------------------------------------------
#  Part 4: Create the .moos and .bhv files.
#-------------------------------------------------------
printf "Assembling MOOS file targ_${VNAME}.moos\n"

nsplug meta_heron.moos targ_${VNAME}.moos -f --strict     \
       VNAME=$VNAME          SHARE_LISTEN=$SHARE_LISTEN  \
       VPORT=$VPORT          SHORE_LISTEN=$SHORE_LISTEN  \
       WARP=$WARP            SHORE_IP=$SHORE_IP          \
       M300_IP=$M300_IP      HOSTIP_FORCE="localhost"    \
       VTYPE="kayak"         LOITER_POS=$LOITER_POS      \
       VTEAM=$VTEAM          START_POS=$START_POS        \
       SIM=$SIM
    
printf "Assembling BHV file targ_${VNAME}.bhv\n"
nsplug $PLAYBOOK targ_${VNAME}.bhv -f --strict       \
       RETURN_POS=${RETURN_POS}     VTEAM=$VTEAM         \
       TRAIL_RANGE=$TRAIL_RANGE     VNAME=$VNAME         \
       TRAIL_ANGLE=$TRAIL_ANGLE     GRAB_POS=$GRAB_POS   \
       DEFEND_POS=$DEFEND_POS       UNTAG_POS=$UNTAG_POS         


if [ ! -e targ_${VNAME}.moos ]; then echo "no targ_${VNAME}.moos"; exit; fi
if [ ! -e targ_${VNAME}.bhv ];  then echo "no targ_${VNAME}.bhv"; exit; fi

if [ ${JUST_BUILD} = "yes" ] ; then
    printf "Files assembled; vehicle not launched; exiting per request.\n"
    exit 0
fi

#-------------------------------------------------------
#  Part 4: Launch the processes
#-------------------------------------------------------

printf "Launching $VNAME MOOS Community \n"
pAntler targ_${VNAME}.moos >& /dev/null &

#uMAC targ_${VNAME}.moos
#printf "Killing all processes ... \n "
#kill -- -$$
#printf "Done killing processes.   \n "
