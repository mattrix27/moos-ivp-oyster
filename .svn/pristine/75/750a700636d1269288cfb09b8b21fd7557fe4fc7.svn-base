#!/bin/bash -e

TIME_WARP=1
JUST_MAKE=""

EVAN="no"
FELIX="no"
GUS="no"
HAL="no"

#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [OPTIONS] [WARP]                         \n\n" $0
	printf "Options:                                    \n"
	printf "  --evan   Launch the vehicle EVAN          \n" 
	printf "  --felix  Launch the vehicle FELIX         \n" 
	printf "  --gus    Launch the vehicle GUS           \n" 
	printf "  --hal    Launch the vehicle HAL           \n" 
	printf "  --red    Launch the RED Team EVAN,FELIX   \n" 
	printf "  --blue   Launch the BLUE Team, GUS,HAL    \n" 
	printf "  -j       Just Build the target files      \n" 
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI:0:7}" = "--warp=" ] ; then
	TIME_WARP="${ARGI#--warp=*}"
    elif [ "${ARGI}" = "--just_make" -o "${ARGI}" = "-j" ] ; then
        JUST_MAKE="-j"
    elif [ "${ARGI}" = "--evan" ] ; then
        EVAN="yes"
    elif [ "${ARGI}" = "--felix" ] ; then
        FELIX="yes"
    elif [ "${ARGI}" = "--gus" ] ; then
        GUS="yes"
    elif [ "${ARGI}" = "--hal" ] ; then
        HAL="yes"
    elif [ "${ARGI}" = "--blue" -o "${ARGI}" = "-b" ] ; then
        EVAN="yes"
        FELIX="yes"
    elif [ "${ARGI}" = "--red" -o "${ARGI}" = "-r" ] ; then
        GUS="yes"
        HAL="yes"
    elif [ "${ARGI}" = "--all" -o "${ARGI}" = "-a" ] ; then
        EVAN="yes"
        FELIX="yes"
        GUS="yes"
        HAL="yes"
    else
	printf "Bad Argument: %s \n" $ARGI ". Use --help"
	exit 0
    fi
done


#-----------------------------------------------
# Launch Evan and check for results      BLUE #1
#-----------------------------------------------
if [ ${EVAN} = "yes" ] ; then
    ./launch_heron.sh --vname=evan   --startpos=-25,-25,70        \
                      --vteam=blue   --lclock                     \
		      --sim $TIME_WARP $JUST_MAKE  

    if [ $? -ne 0 ]; then echo Launch of evan failed; exit 1;  fi
fi

#-----------------------------------------------
# Launch Felix and check for results     BLUE #2
#-----------------------------------------------
if [ ${FELIX} = "yes" ] ; then
    ./launch_heron.sh --vname=felix --startpos=-35,-75,70         \
		      --vteam=blue  --sim $TIME_WARP $JUST_MAKE 
    if [ $? -ne 0 ]; then echo launch of Felix failed; exit 1; fi
fi
    
#-----------------------------------------------
# Launch Gus and check for results        RED #1
#-----------------------------------------------
if [ ${GUS} = "yes" ] ; then
    ./launch_heron.sh --vname=gus   --startpos=40,-45,230         \
		      --vteam=red   --sim $TIME_WARP $JUST_MAKE 
    
    if [ $? -ne 0 ]; then echo launch of Gus failed; exit 1; fi
fi

#-----------------------------------------------
# Launch Hal and check for results        RED #2
#-----------------------------------------------
if [ ${HAL} = "yes" ] ; then
    ./launch_heron.sh --vname=hal   --startpos=25,-15,230         \
		      --vteam=red   --sim $TIME_WARP $JUST_MAKE     
    if [ $? -ne 0 ]; then echo launch of Hal failed; exit 1; fi    
fi



#-----------------------------------------------
# Launch the Shoreside
#-----------------------------------------------
./launch_shoreside.sh $TIME_WARP $JUST_MAKE

