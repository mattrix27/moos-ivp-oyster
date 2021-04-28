#!/bin/bash -e
#----------------------------------------------------------
#  Script: launch_sim.sh
#  Author: Michael Benjamin
#  LastEd: Nov 13th, 2020
#----------------------------------------------------------
#  Part 1: Set global var defaults
#----------------------------------------------------------
TIME_WARP=1
JUST_MAKE=""

#-------------------------------------------------------
#  Part 2: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ]; then
	echo "launch_sim.sh [OPTIONS] [time_warp]                 "
	echo "Options:                                            "
	echo "  -j         Just Build the target files            " 
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_make" -o "${ARGI}" = "-j" ]; then
        JUST_MAKE="-j"
    else
	echo "launch_sim.sh: Bad Arg: " $ARGI " Exiting with code: 1"
	exit 1
    fi
done


#-----------------------------------------------
# Launch Evan and check for results      BLUE #1
#-----------------------------------------------
./launch_heron.sh --vname=evan   --startpos=35,50,170   \
                  --vteam=blue   $TIME_WARP $JUST_MAKE  

if [ $? -ne 0 ]; then echo Launch of evan failed; exit 1;  fi

#-----------------------------------------------
# Launch Gus and check for results        RED #1
#-----------------------------------------------
./launch_heron.sh --vname=gus   --startpos=135,50,230    \
		  --vteam=red   $TIME_WARP $JUST_MAKE 

if [ $? -ne 0 ]; then echo launch of Gus failed; exit 1; fi


#-----------------------------------------------
# Launch the Shoreside
#-----------------------------------------------
./launch_shoreside.sh $TIME_WARP $JUST_MAKE

