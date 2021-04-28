#!/bin/bash

SHORE_IP=192.168.1.155
SHORE_LISTEN="9300"

TIME_WARP=1
HELP="no"
JUST_BUILD="no"
START_POS="0,0,0"
VNAME="mokai"
VTEAM=""
VPORT="9013"
SHARE_LISTEN="9313"
BUTTON="5"
JOY_ID="0"
TEAMMATE=""
HRM="NO"
HRM_DEVICE=""

CID=000
PID=000

for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        HELP="yes"
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--red" -o "${ARGI}" = "-r" ] ; then
        VTEAM="red"
        START_POS="50,-24,240"
        GRAB_POS="-58,-71"
        UNTAG_POS="50,-24"
        RETURN_POS="50,-24"
        VPORT="9013"
        SHARE_LISTEN="9313"
        BUTTON="1"
        echo "Red team selected."
    elif [ "${ARGI}" = "--blue" -o "${ARGI}" = "-b" ] ; then
        VTEAM="blue"
        START_POS="-58,-71,60"
        GRAB_POS="50,-24"
        UNTAG_POS="-58,-71"
        RETURN_POS="-58,-71"
        VPORT="9014"
        SHARE_LISTEN="9314"
        BUTTON="2"
        echo "Blue team selected."
    elif [ "${ARGI}" = "--w-evan" -o "${ARGI}" = "-e" ] ; then
        TEAMMATE="evan"
    elif [ "${ARGI}" = "--w-felix" -o "${ARGI}" = "-f" ] ; then
        TEAMMATE="felix"
    elif [ "${ARGI}" = "--w-gus" -o "${ARGI}" = "-g" ] ; then
        TEAMMATE="gus"
    elif [ "${ARGI}" = "--w-hal" -o "${ARGI}" = "-H" ] ; then
        TEAMMATE="hal"
    elif [ "${ARGI}" = "--w-ida" -o "${ARGI}" = "-i" ] ; then
        TEAMMATE="ida"
    elif [ "${ARGI}" = "--w-jing" -o "${ARGI}" = "-J" ] ; then
        TEAMMATE="jing"
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_BUILD="yes"
        echo "Just building files; no vehicle launch."
    elif [ "${ARGI}" = "--sim" -o "${ARGI}" = "-s" ] ; then
        SIM="SIM=FULL"
        echo "Full simulation mode ON."
    elif [ "${ARGI}" = "--semi-sim" -o "${ARGI}" = "-ss" ] ; then
        SIM="SIM=SEMI"
        echo "Semi simulation mode ON."
    elif [ "${ARGI}" = "--voice-on" -o "${ARGI}" = "-von" ] ; then
        VOICE="ON"
        echo "Voice recognition ON."
    elif [ "${ARGI}" = "--voice-off" -o "${ARGI}" = "-voff" ] ; then
        VOICE="OFF"
        echo "Voice recognition OFF."
    elif [ "${ARGI}" = "--heart-rate-monitor1" -o "${ARGI}" = "-hrm1" ] ; then
        HRM="YES"
        HRM_DEVICE="1"
        echo "iZephyrHRM enabled. With HRM1"
    elif [ "${ARGI}" = "--heart-rate-monitor2" -o "${ARGI}" = "-hrm2" ] ; then
        HRM="YES"
        HRM_DEVICE="2"
        echo "iZephyrHRM enabled. With HRM2"
    elif [ "${ARGI:0:6}" = "--pid=" ] ; then
        PID="${ARGI#--pid=*}"
        PID=$(printf "%03d" $PID)
    elif [ "${ARGI:0:6}" = "--cid=" ] ; then
        CID="${ARGI#--cid=*}"
        CID=$(printf "%03d" $CID)
    else
      echo "Undefined argument:" $ARGI
      echo "Please use -h for help."
      exit 1
    fi
done

if [ "${HELP}" = "yes" ]; then
    echo "$0 [SWITCHES]"
    echo "  --blue,       -b    : Blue team"
    echo "  --red,        -r    : Red team"
    echo "  --w-evan,     -e    : Evan as a teammate."
    echo "  --w-felix,    -f    : Felix as a teammate."
    echo "  --w-gus,      -g    : Gus as a teammate."
    echo "  --w-hal,      -H    : Hal as a teammate."
    echo "  --w-ida,      -i    : Ida as a teammate."
    echo "  --w-jing,     -J    : Jing as a teammate."
    echo "  --semi-sim,   -ss   : Semi-autonomous simulation (w/ joysticks)"
    echo "  --sim,        -s    : Full simulation"
    echo "  --voice-on,   -von  : Voice recognition on"
    echo "  --voice-off,  -voff : Voice recognition off"
    echo "  --heart-rate-monitor1, -hrm1 : HRM Enabled"
    echo "  --heart-rate-monitor2, -hrm2 : HRM Enabled"
    echo "  --cid=              : Competition id (for log file)"
    echo "  --pid=              : Participant id (for log file)"
    echo "  --just_build, -j"
    echo "  --help,       -h"
    exit 0;
fi

if [ -z $VTEAM ]; then
    echo "No team has been selected..."
    echo "Exiting."
    exit 3
fi

if [ -z $TEAMMATE ]; then
    echo "No teammate has been selected..."
    echo "Exiting."
    exit 2
fi

echo "Assembling MOOS file targ_${VNAME}_${VTEAM}.moos ."

nsplug meta_mokai.moos targ_${VTEAM}_one.moos -f  \
       VNAME="${VTEAM}_one"    \
       VPORT=$VPORT                 \
       SHARE_LISTEN=$SHARE_LISTEN   \
       WARP=$TIME_WARP              \
       SHORE_LISTEN=$SHORE_LISTEN   \
       SHORE_IP=$SHORE_IP           \
       VTYPE="mokai"                \
       VTEAM=$VTEAM                 \
       BUTTON=$BUTTON               \
       JOY_ID=$JOY_ID               \
       TEAMMATE=$TEAMMATE           \
       VOICE=$VOICE                 \
       START_POS=$START_POS         \
       HRM=$HRM                     \
       HRM_DEVICE=$HRM_DEVICE       \
       CID=$CID                     \
       PID=$PID                     \
       $SIM

echo "Assembling BHV file targ_${VTEAM}_one.bhv ."

nsplug meta_mokai.bhv targ_${VTEAM}_one.bhv -f  \
       VNAME="${VTEAM}_one"    \
       VPORT=$VPORT                 \
       SHARE_LISTEN=$SHARE_LISTEN   \
       WARP=$WARP                   \
       SHORE_LISTEN=$SHORE_LISTEN   \
       SHORE_IP=$SHORE_IP           \
       VTYPE="mokai"                \
       VTEAM=$VTEAM                 \
       BUTTON=$BUTTON               \
       JOY_ID=$JOY_ID               \
       TEAMMATE=$TEAMMATE           \
       START_POS=$START_POS         \
       RETURN_POS=$RETURN_POS       \
       GRAB_POS=$GRAB_POS           \
       UNTAG_POS=$UNTAG_POS

if [ ${JUST_BUILD} = "yes" ] ; then
    echo "Files assembled; vehicle not launched; exiting per request."
    exit 0
fi

if [ ! -e targ_${VTEAM}_one.moos ]; then echo "no targ_${VTEAM}_one.moos!"; exit 1; fi
if [ ! -e targ_${VTEAM}_one.bhv ]; then echo "no targ_${VTEAM}_one.bhv!"; exit 1; fi

echo "Launching $VNAME MOOS Community."
pAntler targ_${VTEAM}_one.moos >& /dev/null &
uMAC targ_${VTEAM}_one.moos

echo "Killing all processes ..."
kill -- -$$
echo "Done killing processes."
