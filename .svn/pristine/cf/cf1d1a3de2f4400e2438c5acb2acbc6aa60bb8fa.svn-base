#!/bin/bash

SHORE_IP=192.168.1.150
SHORE_LISTEN="9300"

TIME_WARP=1
HELP="no"
JUST_BUILD="no"
START_POS="0,0,0"
VNAME=""
VTEAM=""
VPORT="9013"
SHARE_LISTEN="9313"
BUTTON="5"
JOY_ID="0"
TEAMMATE1=""
TEAMMATE2=""
VOICE="ON"
HRM="NO"

case "$1" in
    r1|red_one)
        VTEAM="red"
        VNAME="red_one"
        VPORT="9011"
        SHARE_LISTEN="9311"
        echo "Vehicle set to red one."
        ;;
    r2|red_two)
        VTEAM="red"
        VNAME="red_two"
        VPORT="9012"
        SHARE_LISTEN="9312"
        echo "Vehicle set to red two."
        ;;
    r3|red_three)
        VTEAM="red"
        VNAME="red_three"
        VPORT="9013"
        SHARE_LISTEN="9313"
        echo "Vehicle set to red two."
        ;;
    r4|red_four)
        VTEAM="red"
        VNAME="red_four"
        VPORT="9014"
        SHARE_LISTEN="9314"
        echo "Vehicle set to red two."
        ;;
    b1|blue_one)
        VTEAM="blue"
        VNAME="blue_one"
        VPORT="9015"
        SHARE_LISTEN="9315"
        echo "Vehicle set to blue one."
        ;;
    b2|blue_two)
        VTEAM="blue"
        VNAME="blue_two"
        VPORT="9016"
        SHARE_LISTEN="9316"
        echo "Vehicle set to blue two."
        ;;
    b3|blue_three)
        VTEAM="blue"
        VNAME="blue_three"
        VPORT="9017"
        SHARE_LISTEN="9317"
        echo "Vehicle set to blue three."
        ;;
    b4|blue_four)
        VTEAM="blue"
        VNAME="blue_four"
        VPORT="9018"
        SHARE_LISTEN="9318"
        echo "Vehicle set to blue four."
        ;;
    *)
        HELP="yes"
        echo "Error invalid positional argument!"
        ;;
esac

for arg in "${@:2:2}"; do
    REQUESTED_TEAMMATE=""
    case "$arg" in
        r1|red_one)
            REQUESTED_TEAMMATE="red_one"
            ;;
        r2|red_two)
            REQUESTED_TEAMMATE="red_two"
            ;;
        r3|red_three)
            REQUESTED_TEAMMATE="red_three"
            ;;
        r4|red_four)
            REQUESTED_TEAMMATE="red_four"
            ;;
        b1|blue_one)
            REQUESTED_TEAMMATE="blue_one"
            ;;
        b2|blue_two)
            REQUESTED_TEAMMATE="blue_two"
            ;;
        b3|blue_three)
            REQUESTED_TEAMMATE="blue_three"
            ;;
        b4|blue_four)
            REQUESTED_TEAMMATE="blue_four"
            ;;
        *)
            HELP="yes"
            echo "Error invalid teammate name!"
            ;;
    esac
    
       
    if [ -z $TEAMMATE1 ]; then
        TEAMMATE1=$REQUESTED_TEAMMATE
        echo $TEAMMATE1 "assigned as teammate1."
    else
        TEAMMATE2=$REQUESTED_TEAMMATE
        echo $TEAMMATE2 "assigned as teammate2"
    fi
done
	
for arg in "${@:4}"; do
    if [ "${arg}" = "--help" -o "${arg}" = "-H" ] ; then
        HELP="yes"
    elif [ "${arg//[^0-9]/}" = "$arg" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$arg
    elif [ "${arg}" = "--just_build" -o "${arg}" = "-J" ] ; then
        JUST_BUILD="yes"
        echo "Just building files; no vehicle launch."
    elif [ "${arg}" = "--sim" -o "${arg}" = "-s" ] ; then
        SIM="SIM=FULL"
        echo "Full simulation mode ON."
    elif [ "${arg}" = "--semi-sim" -o "${arg}" = "-ss" ] ; then
        SIM="SIM=SEMI"
        echo "Semi simulation mode ON."
    elif [ "${arg}" = "--voice-on" -o "${arg}" = "-von" ] ; then
        VOICE="ON"
        echo "Voice recognition ON."
    elif [ "${arg}" = "--voice-off" -o "${arg}" = "-voff" ] ; then
        VOICE="OFF"
        echo "Voice recognition OFF."
    elif [ "${arg}" = "--heart-rate-monitor" -o "${arg}" = "-hrm" ] ; then
        HRM="YES"
        echo "iZephyrHRM enabled."
    else
        echo "Undefined switch:" $arg
        HELP="yes"
    fi
done

if [ "${VTEAM}" = "red" ]; then
    START_POS="50,-24,240"
    GRAB_POS="-52,-70"
    UNTAG_POS="50,-24"
    RETURN_POS="50,-24"
    BUTTON="1"
    echo "Red team selected."
elif [ "${VTEAM}" = "blue" ]; then
    START_POS="-52,-70,60"
    GRAB_POS="50,-24"
    UNTAG_POS="-52,-70"
    RETURN_POS="-52,-70"
    BUTTON="2"
    echo "Blue team selected."
fi

if [ "${HELP}" = "yes" ]; then
    echo ""
    echo "$0 <vehical_name> <teammate1_name> <teammate2_name> [SWITCHES]"

    echo ""
    echo "POSSIBLE VEHICLE OR TEAMMATE NAMES:"
    echo "  blue_one,     b1    : Vehicle one on blue team."
    echo "  blue_two,     b2    : Vehicle two on blue team."
    echo "  blue_three,   b3    : Vehicle three on blue team."
    echo "  blue_four,    b4    : Vehicle four on blue team."

    echo "  red_one,      r1    : Vehicle one on red team."
    echo "  red_two,      r2    : Vehicle two on red team."
    echo "  red_three,    r3    : Vehicle three on red team."
    echo "  red_four,     r4    : Vehicle four on red team."

    echo ""
    echo "POSSIBLE SWITCHES:"
    echo "  --semi-sim,            -ss   : Semi-autonomous simulation (w/ joysticks)"
    echo "  --sim,                 -s    : Full simulation"
    echo "  --voice-on,            -von  : Voice recognition on"
    echo "  --voice-off,           -voff : Voice recognition off"
    echo "  --heart-rate-monitor , -hrm  : HRM enabled"
    echo "  --just_build,          -J    : Only build targ file"
    echo "  --help,                -H    : Display this help message"
    exit 0;
fi

if [ -z $VTEAM ]; then
    echo "No team has been selected..."
    echo "Exiting."
    exit 3
fi

if [ -z $TEAMMATE1 ]; then
    echo "Teammate 1 is missing..."
    echo "Exiting."
    exit 2
fi

if [ -z $TEAMMATE2 ]; then
    echo "Teammate 2 is missing..."
    echo "Exiting."
    exit 2
fi

echo "Assembling MOOS file targ_${VNAME}_${VTEAM}.moos ."

nsplug meta_mokai.moos targ_${VNAME}_${VTEAM}.moos -f  \
       VNAME="${VNAME}"             \
       VPORT=$VPORT                 \
       SHARE_LISTEN=$SHARE_LISTEN   \
       WARP=$TIME_WARP              \
       SHORE_LISTEN=$SHORE_LISTEN   \
       SHORE_IP=$SHORE_IP           \
       VTYPE="mokai"                \
       VTEAM=$VTEAM                 \
       BUTTON=$BUTTON               \
       JOY_ID=$JOY_ID               \
       TEAMMATE1=$TEAMMATE1         \
       TEAMMATE2=$TEAMMATE2         \
       VOICE=$VOICE                 \
       START_POS=$START_POS         \
       HRM=$HRM                     \
       $SIM

echo "Assembling BHV file targ_${VNAME}_${VTEAM}.bhv ."

nsplug meta_mokai.bhv targ_${VNAME}_${VTEAM}.bhv -f  \
       VNAME="${VNAME}"             \
       VPORT=$VPORT                 \
       SHARE_LISTEN=$SHARE_LISTEN   \
       WARP=$WARP                   \
       SHORE_LISTEN=$SHORE_LISTEN   \
       SHORE_IP=$SHORE_IP           \
       VTYPE="mokai"                \
       VTEAM=$VTEAM                 \
       BUTTON=$BUTTON               \
       JOY_ID=$JOY_ID               \
       TEAMMATE1=$TEAMMATE1         \
       TEAMMATE2=$TEAMMATE2         \
       START_POS=$START_POS         \
       RETURN_POS=$RETURN_POS       \
       GRAB_POS=$GRAB_POS           \
       UNTAG_POS=$UNTAG_POS

if [ ${JUST_BUILD} = "yes" ] ; then
    echo "Files assembled; vehicle not launched; exiting per request."
    exit 0
fi

if [ ! -e targ_${VNAME}_${VTEAM}.moos ]; then echo "no targ_${VNAME}_${VTEAM}.moos!"; exit 1; fi
if [ ! -e targ_${VNAME}_${VTEAM}.bhv ]; then echo "no targ_${VNAME}_${VTEAM}.bhv!"; exit 1; fi

echo "Launching $VNAME MOOS Community."
pAntler targ_${VNAME}_${VTEAM}.moos >& /dev/null &
uMAC targ_${VNAME}_${VTEAM}.moos

echo "Killing all processes ..."
kill -- -$$
echo "Done killing processes."
