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
EVAN="no"
FELIX="no"
GUS="no"
HAL="no"

#-------------------------------------------------------
#  Part 2: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ]; then
	echo "launch_sim.sh [OPTIONS] [time_warp]                 "
	echo "Options:                                            "
	echo "  --evan     Launch the vehicle EVAN                " 
	echo "  --felix    Launch the vehicle FELIX               " 
	echo "  --gus      Launch the vehicle GUS                 " 
	echo "  --hal      Launch the vehicle HAL                 " 
	echo "  --red, -r  Launch the RED Team EVAN,FELIX         " 
	echo "  --blue, -b Launch the BLUE Team, GUS,HAL          " 
	echo "  --all, -a  Launch all vehicles, EVAN,FELIX,GUS,HAL" 
	echo "  -j         Just Build the target files            " 
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_make" -o "${ARGI}" = "-j" ]; then
        JUST_MAKE="-j"
    elif [ "${ARGI}" = "--evan" ]; then
        EVAN="yes"
    elif [ "${ARGI}" = "--felix" ]; then
        FELIX="yes"
    elif [ "${ARGI}" = "--gus" ]; then
        GUS="yes"
    elif [ "${ARGI}" = "--hal" ]; then
        HAL="yes"
    elif [ "${ARGI}" = "--blue" -o "${ARGI}" = "-b" ]; then
        EVAN="yes"
        FELIX="yes"
    elif [ "${ARGI}" = "--red" -o "${ARGI}" = "-r" ]; then
        GUS="yes"
        HAL="yes"
    elif [ "${ARGI}" = "--all" -o "${ARGI}" = "-a" ]; then
        EVAN="yes"
        FELIX="yes"
        GUS="yes"
        HAL="yes"
    else
	echo "launch_sim.sh: Bad Arg: " $ARGI " Exiting with code: 1"
	exit 1
    fi
done


#-----------------------------------------------
# Launch Evan and check for results      BLUE #1
#-----------------------------------------------
if [ ${EVAN} = "yes" ]; then
    ./launch_heron.sh --vname=evan   --startpos=35,50,170   \
                      --vteam=blue   $TIME_WARP $JUST_MAKE  
    
    if [ $? -ne 0 ]; then echo Launch of evan failed; exit 1;  fi
fi

#-----------------------------------------------
# Launch Felix and check for results     BLUE #2
#-----------------------------------------------
if [ ${FELIX} = "yes" ]; then
    ./launch_heron.sh --vname=felix --startpos=35,15,20     \
		      --vteam=blue  $TIME_WARP $JUST_MAKE 

    if [ $? -ne 0 ]; then echo launch of Felix failed; exit 1; fi
fi
    
#-----------------------------------------------
# Launch Gus and check for results        RED #1
#-----------------------------------------------
if [ ${GUS} = "yes" ]; then
    ./launch_heron.sh --vname=gus   --startpos=135,50,230    \
		      --vteam=red   $TIME_WARP $JUST_MAKE 
    
    if [ $? -ne 0 ]; then echo launch of Gus failed; exit 1; fi
fi

#-----------------------------------------------
# Launch Hal and check for results        RED #2
#-----------------------------------------------
if [ ${HAL} = "yes" ]; then
    ./launch_heron.sh --vname=hal   --startpos=145,10,300    \
		      --vteam=red   $TIME_WARP $JUST_MAKE     
    if [ $? -ne 0 ]; then echo launch of Hal failed; exit 1; fi    
fi



#-----------------------------------------------
# Launch the Shoreside
#-----------------------------------------------
./launch_shoreside.sh $TIME_WARP $JUST_MAKE

