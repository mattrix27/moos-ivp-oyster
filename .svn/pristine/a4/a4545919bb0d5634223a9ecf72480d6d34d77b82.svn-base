#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
VOIP="false"
VTEAM1="red"
VTEAM2="blue"
SHORE_IP="localhost"
SHORE_LISTEN="9300"
BLUE_FLAG="x=-52,y=-70"
RED_FLAG="x=50,y=-24"

CID=000 # Competiton id

for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        echo "$0 [SWITCHES]"
        echo "  --voip, -v       , Launch Murmur VoIP server"
        echo "  --shore-port=    , set up a shore listening port. (Default is $SHORE_LISTEN)"
        echo "  --shore-ip=      , set up a shore listening IP. (Default is $SHORE_IP)"
        echo "  --cid=           , competition id (for log file)"
        echo "  --just_make, -j    "
        echo "  --help, -h         "
        exit 0
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
        JUST_MAKE="yes"
    elif [ "${ARGI}" = "--voip" -o "${ARGI}" = "-v" ]; then
        VOIP="true"
    elif [ "${ARGI:0:11}" = "--shore-ip=" ] ; then
        SHORE_IP="${ARGI#--shore-ip=*}"
    elif [ "${ARGI:0:13}" = "--shore-port=" ] ; then
        SHORE_LISTEN=${ARGI#--shore-port=*}
    elif [ "${ARGI:0:6}" = "--cid=" ] ; then
        CID="${ARGI#--cid=*}"
        CID=$(printf "%03d" $CID)
    else
        echo "Bad Argument: " $ARGI
        exit 1
    fi
done

#-------------------------------------------------------
#  Part 1: Create the Shoreside MOOS file
#-------------------------------------------------------
nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP    \
       SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN  SPORT="9000"   \
       VTEAM1=$VTEAM1 VTEAM2=$VTEAM2 SHORE_IP=$SHORE_IP CID=$CID     \
       RED_FLAG=${RED_FLAG} BLUE_FLAG=${BLUE_FLAG}

if [ ! -e targ_shoreside.moos ]; then echo "no targ_shoreside.moos"; exit 1; fi

#-------------------------------------------------------
#  Part 2: Possibly exit now if we're just building targ files
#-------------------------------------------------------

if [ ${JUST_MAKE} = "yes" ] ; then
    echo "Shoreside targ files built. Nothing launched."
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the Shoreside
#-------------------------------------------------------

if [ "${VOIP}" = "true" ]; then
  echo "Launching Murmur VoIP Server Daemon"
  cd murmur

  if [ -x "$(command -v murmurd)" ]; then
    # This will fail if murmurd is an alias
    murmurd -ini murmur.ini
  else 
    echo "ERROR: You requested a VoIP Server, but murmurd wasn't found!"
    echo "Is it in your \$PATH and executable?"
    VOIP="error"
    echo "Sleeping for 10 seconds..."
    sleep 10s
  fi
  cd ..
fi

echo "Launching $SNAME MOOS Community (WARP=$TIME_WARP)"
pAntler targ_shoreside.moos >& /dev/null &
echo "Done Launching Shoreside "

uMAC targ_shoreside.moos

if [ "${VOIP}" = "true" ]; then
  echo "Killing Murmur Server"
  killall -m murmurd
fi

sleep .2 # Give them a chance to exit with grace
echo "Killing all processes ... "
kill -- -$$
echo "Done killing processes.   "
