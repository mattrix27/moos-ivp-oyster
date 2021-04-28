#!/bin/bash 
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
AMT=1
SHORE="multicast_9"
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [time_warp]   \n" $0
	exit 0;
    elif [ "${ARGI:0:6}" = "--amt=" ] ; then
        AMT="${ARGI#--amt=*}"
    elif [ "${ARGI:0:8}" = "--shore=" ] ; then
        SHORE="${ARGI#--shore=*}"
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then 
        TIME_WARP=$ARGI
    else 
	printf "Bad Argument: %s \n" $ARGI
	exit 0
    fi
done

#-------------------------------------------------------
#  Launch the vehicles
#-------------------------------------------------------

printf "Launching Archie....\n"
./launch_vehicle.sh --vname=archie  $TIME_WARP --shore=$SHORE --index=1 --startpos="10,0" >& /dev/null &

if [ $AMT -gt 1 ] ; then
printf "Launching Betty.... \n"
./launch_vehicle.sh --vname=betty   $TIME_WARP --shore=$SHORE --index=2 --startpos="30,0" >& /dev/null &
fi

