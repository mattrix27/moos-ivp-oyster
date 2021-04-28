#!/bin/bash
TIME_WARP=1

CMD_ARGS=""
NO_HERON=""
NO_MOKAI=""
NO_SHORESIDE=""

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        HELP="yes"
    elif [ "${ARGI}" = "--no_shoreside" -o "${ARGI}" = "-ns" ] ; then
        NO_SHORESIDE="true"
    elif [ "${ARGI}" = "--no_mokai" -o "${ARGI}" = "-nmo" ] ; then
        NO_MOKAI="true"
    elif [ "${ARGI}" = "--no_heron" -o "${ARGI}" = "-nh" ] ; then
        NO_HERON="true"
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
        echo "Time warp set up to $TIME_WARP."
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_BUILD="yes"
        echo "Just building files; no vehicle launch."
    else
        CMD_ARGS=$CMD_ARGS" "$ARGI
    fi
done


if [ "${HELP}" = "yes" ]; then
  echo "$0 [SWITCHES]"
  echo "  XX                  : Time warp"
  echo "  --no_shoreside, -ns"
  echo "  --no_mokai, -nmo"
  echo "  --no_heron, -nh"
  echo "  --just_build, -j"
  echo "  --help, -h"
  exit 0;
fi

#-------------------------------------------------------
#  Part 2: Launching herons
#-------------------------------------------------------
if [[ -z $NO_HERON ]]; then
  cd ./heron
  # Evan Blue
  ./launch_heron.sh e r3 r4 $TIME_WARP -s > /dev/null &
  sleep 1
  # Felix Red
  ./launch_heron.sh f b3 b4 $TIME_WARP -s > /dev/null &
  sleep 1
  # Hal Blue
  ./launch_heron.sh h r4 r3 $TIME_WARP -s > /dev/null &
  sleep 1
  # Ida Red
  ./launch_heron.sh i b4 b3 $TIME_WARP -s > /dev/null &
  sleep 1
  cd ..
fi

#-------------------------------------------------------
#  Part 3: Launching MOKAIs
#-------------------------------------------------------
if [[ -z $NO_MOKAI ]]; then
  cd ./mokai
  # Blue one
  ./launch_mokai.sh b1 b3 b4 $TIME_WARP -ss >& /dev/null &
  sleep 1
  # Red one
  ./launch_mokai.sh r1 r3 r4 $TIME_WARP -ss >& /dev/null &
  sleep 1
  # Blue two
  ./launch_mokai.sh b2 b3 b4 $TIME_WARP -ss >& /dev/null &
  sleep 1
  # Red two
  ./launch_mokai.sh r2 r3 r4 $TIME_WARP -ss >& /dev/null &
  sleep 1
  cd ..
fi

#-------------------------------------------------------
#  Part 4: Launching shoreside
#-------------------------------------------------------
if [[ -z $NO_SHORESIDE ]]; then
  cd ./shoreside
  ./launch_shoreside.sh $TIME_WARP >& /dev/null &
  cd ..
fi

#-------------------------------------------------------
#  Part 4: Launching uMAC
#-------------------------------------------------------
uMAC shoreside/targ_shoreside.moos

#-------------------------------------------------------
#  Part 5: Killing all processes launched from script
#-------------------------------------------------------
echo "Killing Simulation..."
kill -- -$$
# sleep is to give enough time to all processes to die
sleep 3
echo "All processes killed"
