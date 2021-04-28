#!/bin/bash
TIME_WARP=1

SHORE_IP=192.168.1.150
SHORE_LISTEN="9300"

TRAIL_RANGE="3"
TRAIL_ANGLE="330"
HELP="no"
JUST_BUILD="no"
VTEAM=""
VNAME=""
VMODEL="M300"

START_POS="56,16,240"
RETURN_POS="5,0"
LOITER_POS="x=100,y=-180"
GRAB_POS=""
GRABR_POS=""
GRABL_POS=""
UNTAG_POS=""

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
case "$1" in
    e|evan)
        HERON_IP=192.168.5.1
        echo "EVAN heron selected."
        ;;
    f|felix)
        HERON_IP=192.168.6.1
        echo "FELIX heron selected."
        ;;
    g|gus)
        HERON_IP=192.168.7.1
        echo "GUS heron selected."
        ;;
    h|hal)
        HERON_IP=192.168.8.1
        echo "HAL heron selected."
        ;;
    i|ida)
        HERON_IP=192.168.9.1
        echo "IDA heron selected."
        ;;
    j|jing)
        HERON_IP=192.168.10.1
        echo "JING heron selected."
        ;;
    k|kirk)
        HERON_IP=192.168.11.1
        echo "KIRK heron selected."
        ;;
    l|luke)
	    HERON_IP=192.168.12.1
	    echo "LUKE heron selected."
	    ;;
    *)
        HELP="yes"
        echo "Error invalid positional argument!"
        ;;
esac

case "$2" in
    r1|red_one)
        VTEAM="red"
        VNAME="red_one"
        VPORT="9011"
        SHARE_LISTEN="9311"
        echo "Vehical set to red one."
        ;;
    r2|red_two)
        VTEAM="red"
        VNAME="red_two"
        VPORT="9012"
        SHARE_LISTEN="9312"
        echo "Vehical set to red two."
        ;;
    r3|red_three)
        VTEAM="red"
        VNAME="red_three"
        VPORT="9013"
        SHARE_LISTEN="9313"
        echo "Vehical set to red two."
        ;;
    r4|red_four)
        VTEAM="red"
        VNAME="red_four"
        VPORT="9014"
        SHARE_LISTEN="9314"
        echo "Vehical set to red two."
        ;;
    b1|blue_one)
        VTEAM="blue"
        VNAME="blue_one"
        VPORT="9011"
        SHARE_LISTEN="9311"
        echo "Vehical set to blue one."
        ;;
    b2|blue_two)
        VTEAM="blue"
        VNAME="blue_two"
        VPORT="9012"
        SHARE_LISTEN="9312"
        echo "Vehical set to blue two."
        ;;
    b3|blue_three)
        VTEAM="blue"
        VNAME="blue_three"
        VPORT="9013"
        SHARE_LISTEN="9313"
        echo "Vehical set to blue three."
        ;;
    b4|blue_four)
        VTEAM="blue"
        VNAME="blue_four"
        VPORT="9014"
        SHARE_LISTEN="9314"
        echo "Vehical set to blue four."
        ;;
    *)
        HELP="yes"
        echo "Error invalid positional argument!"
        ;;
esac	

for arg in "${@:3}"; do
    if [ "${arg}" = "--help" -o "${arg}" = "-H" ]; then
        HELP="yes"
    elif [ "${arg//[^0-9]/}" = "$arg" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$arg
        echo "Time warp set to: " $arg
    elif [ "${arg}" = "--just_build" -o "${arg}" = "-J" ] ; then
        JUST_BUILD="yes"
        echo "Just building files; no vehicle launch."
    elif [ "${arg}" = "--sim" -o "${arg}" = "-s" ] ; then
        SIM="SIM"
        echo "Simulation mode ON."
    elif [ "${arg:0:10}" = "--start-x=" ] ; then
        START_POS_X="${arg#--start-x=*}"
    elif [ "${arg:0:10}" = "--start-y=" ] ; then
        START_POS_Y="${arg#--start-y=*}"
    elif [ "${arg:0:10}" = "--start-a=" ] ; then
        START_POS_A="${arg#--start-a=*}"
    else
        echo "Undefined switch:" $arg
        HELP="yes"
    fi
done

if [ "${VTEAM}" = "red" ]; then
    GRAB_POS="-52,-70"
    GRABR_POS="-46,-42"
    GRABL_POS="-29,-83"
    UNTAG_POS="50,-24"
    RETURN_POS="5,0"
    START_POS="50,-24,240"
    echo "Red team selected."
elif [ "${VTEAM}" = "blue" ]; then
    GRAB_POS="50,-24"
    GRABR_POS="42,-55"
    GRABL_POS="19,-11"
    UNTAG_POS="-52,-70"
    RETURN_POS="5,0"
    START_POS="-52,-70,60"
    echo "Blue team selected."
fi
   
#-------------------------------------------------------
#  Part 2: Handle Ill-formed command-line arguments
#-------------------------------------------------------

if [ "${HELP}" = "yes" ]; then
    echo ""
    echo "USAGE: $0 <heron_name> <vehical_name> [SWITCHES]"
    
    echo ""
    echo "POSSIBLE HERON NAMES:"
    echo "  evan,         e   : Evan heron."
    echo "  felix,        f   : Felix heron."
    echo "  gus,          g   : Gus heron."
    echo "  hal,          h   : Hal heron."
    echo "  ida,          i   : Ida heron."
    echo "  jing,         j   : Jing heron."
    echo "  kirk,         k   : Kirk heron."
    echo "  luke,         l   : Luke heron."

    echo ""
    echo "POSSIBLE VEHICAL NAMES:"
    echo "  blue_one,     b1  : Vehical one on blue team."
    echo "  blue_two,     b2  : Vehical two on blue team."
    echo "  blue_three,   b3  : Vehical three on blue team."
    echo "  blue_four,    b4  : Vehical four on blue team."

    echo "  red_one,      r1  : Vehical one on red team."
    echo "  red_two,      r2  : Vehical two on red team."
    echo "  red_three,    r3  : Vehical three on red team."
    echo "  red_four,     r4  : Vehical four on red team."

    echo ""
    echo "POSSIBLE SWITCHES:"
    echo "  --sim,        -s  : Simulation mode."
    echo "  --start-x=        : Start from x position (requires x y a)."
    echo "  --start-y=        : Start from y position (requires x y a)."
    echo "  --start-a=        : Start from angle (requires x y a)."
    echo "  --just_build, -J  : Just build targ files."
    echo "  --help,       -H  : Display this message."
    exit 0;
fi


#-------------------------------------------------------
#  Part 3: Create the .moos and .bhv files.
#-------------------------------------------------------

if [[ -n $START_POS_X && (-n $START_POS_Y && -n $START_POS_A)]]; then
  START_POS="$START_POS_X,$START_POS_Y,$START_POS_A"
  echo "Starting from " $START_POS
elif [[ -z $START_POS_X && (-z $START_POS_Y && -z $START_POS_A) ]]; then
  echo "Starting from default postion: " $START_POS
else [[ -z $START_POS_X || (-z $START_POS_Y || -z $START_POS_A) ]]
  echo "When specifing a strating coordinate, all 3 should be specified (x,y,a)."
  echo "See help (-h)."
  exit 1
fi

echo "Assembling MOOS file targ_${VNAME}.moos"


nsplug meta_heron.moos targ_${VNAME}.moos -f \
    VNAME=$VNAME                 \
    VPORT=$VPORT                 \
    WARP=$TIME_WARP              \
    SHARE_LISTEN=$SHARE_LISTEN   \
    SHORE_LISTEN=$SHORE_LISTEN   \
    SHORE_IP=$SHORE_IP           \
    HERON_IP=$HERON_IP             \
    HOSTIP_FORCE="localhost"     \
    LOITER_POS=$LOITER_POS       \
    VARIATION=$VARIATION         \
    VMODEL=$VMODEL               \
    VTYPE="kayak"                \
    VTEAM=$VTEAM                 \
    START_POS=$START_POS         \
    $SIM

echo "Assembling BHV file targ_${VNAME}.bhv"
nsplug meta_heron.bhv targ_${VNAME}.bhv -f  \
        RETURN_POS=${RETURN_POS}    \
        TRAIL_RANGE=$TRAIL_RANGE    \
        TRAIL_ANGLE=$TRAIL_ANGLE    \
        VTEAM=$VTEAM                \
        VNAME=$VNAME                \
        GRAB_POS=$GRAB_POS          \
        GRABR_POS=$GRABR_POS           \
        GRABL_POS=$GRABL_POS             \
        UNTAG_POS=$UNTAG_POS


if [ ${JUST_BUILD} = "yes" ] ; then
    echo "Files assembled; vehicle not launched; exiting per request."
    exit 0
fi

#-------------------------------------------------------
#  Part 4: Launch the processes
#-------------------------------------------------------

echo "Launching $VNAME MOOS Community "
pAntler targ_${VNAME}.moos >& /dev/null &

uMAC targ_${VNAME}.moos

echo "Killing all processes ..."
kill -- -$$
echo "Done killing processes."
