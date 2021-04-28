#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
AMT=1
GOOD_GUYS="yes"
BAD_GUYS="yes"
VTEAM1="red"
VTEAM2="blue"
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES] [time_warp]   \n" $0
	printf "  --just_make, -j    \n" 
	printf "  --help, -h         \n" 
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then 
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
	JUST_MAKE="yes"
    elif [ "${ARGI}" = "--bad_guys_no" -o "${ARGI}" = "-b" ] ; then
	BAD_GUYS="no"
    elif [ "${ARGI}" = "--good_guys_no" -o "${ARGI}" = "-g" ] ; then
	GOOD_GUYS="no"
    elif [ "${ARGI:0:6}" = "--amt=" ] ; then
        AMT="${ARGI#--amt=*}"
    else 
	printf "Bad Argument: %s \n" $ARGI
	exit 0
    fi
done

# Ensure AMT is in the range of [1,26]
if [ $AMT -gt 26 ] ; then
    AMT=20
fi
if [ $AMT -lt 1 ] ; then
    AMT=1
fi


#-------------------------------------------------------
#  Part 1: Create the Shoreside MOOS file
#-------------------------------------------------------
SHORE_LISTEN="9300"

nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP    \
       SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN  SPORT="9000"   \
       VTEAM1=$VTEAM1 VTEAM2=$VTEAM2

if [ ! -e targ_shoreside.moos ]; then echo "no targ_shoreside.moos"; exit; fi

#-------------------------------------------------------
#  Part 2: Create the GoodGuy .moos and .bhv files. 
#-------------------------------------------------------
VNAME="henry"   
START_POS="60,-30,180"         

nsplug meta_vehicle.moos targ_henry.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME           SHARE_LISTEN="9301"              \
    VPORT="9001"           SHORE_LISTEN=$SHORE_LISTEN       \
    VTEAM=$VTEAM1          START_POS=$START_POS 

nsplug meta_vehicle.bhv targ_henry.bhv -f VNAME=$VNAME     \
    START_POS=$START_POS 

if [ ! -e targ_henry.moos ]; then echo "no targ_henry.moos"; exit; fi
if [ ! -e targ_henry.bhv  ]; then echo "no targ_henry.bhv "; exit; fi

#-------------------------------------------------------
#  Part 2: Create the Mokai for human driver. 
#-------------------------------------------------------
VNAME="mokai"   
START_POS="20,-20,180"         

nsplug meta_mokai_sim.moos targ_mokai.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME           SHARE_LISTEN="9302"              \
    VPORT="9002"           SHORE_LISTEN=$SHORE_LISTEN       \
    VTEAM=$VTEAM1          START_POS=$START_POS 

#nsplug meta_.bhv targ_mokai.bhv -f VNAME=$VNAME     \
#    START_POS=$START_POS 

if [ ! -e targ_mokai.moos ]; then echo "no targ_mokai.moos"; exit; fi
#if [ ! -e targ_mokai.bhv  ]; then echo "no targ_mokai.bhv "; exit; fi


#-------------------------------------------------------
#  Part 3: Create the BadGuy .moos and .bhv files. 
#-------------------------------------------------------
VNAMES=( apia baku cary doha elko fahy galt hays iola juba kiev lima mesa 
	 nuuk oslo pace quay rome sako troy ubly vimy waco xian york zahl )

STARTX=( 0 40 60 80 100 120 140 5 25 45 65 85 105 125 145 10 50 90 130
	 15 55 95 135 140 145 150 155 )

for INDEX in `seq 0 $(($AMT-1))`;
do 
    VNAME=${VNAMES[$INDEX]}
    VPOSX=${STARTX[$INDEX]}
    VPORT=`expr $INDEX + 9400`
    LPORT=`expr $INDEX + 9500`
    START_POS=$VPOSX",-80,180"
    
    echo "Vehicle:" $VNAME
    echo "Index:" $INDEX  "Port:" $VPORT "POS:" $START_POS 

    nsplug meta_tagger.moos targ_$VNAME.moos -f WARP=$TIME_WARP  \
	   VNAME=$VNAME                \
	   VPORT=$VPORT                \
	   VTEAM=$VTEAM2               \
	   SHARE_LISTEN=$LPORT         \
	   SHORE_LISTEN=$SHORE_LISTEN  \
	   START_POS=$START_POS
    
    nsplug meta_tagger.bhv targ_$VNAME.bhv -f VNAME=$VNAME     \
	START_POS=$START_POS  

    if [ ! -e targ_$VNAME.moos ]; then echo "no targ_$VNAME.moos"; exit; fi
    if [ ! -e targ_$VNAME.bhv  ]; then echo "no targ_$VNAME.bhv "; exit; fi

done

#-------------------------------------------------------
#  Part 4: Possibly exit now if we're just building targ files
#-------------------------------------------------------

if [ ${JUST_MAKE} = "yes" ] ; then
    printf "targ files built. Nothing launched.\n"
    exit 0
fi

if [ ${BAD_GUYS} = "no" -a ${GOOD_GUYS} = "no"] ; then
    printf "targ files built. Nothing launched.\n"
    exit 0
fi

#-------------------------------------------------------
#  Part 5: Launch the Shoreside
#-------------------------------------------------------
printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done Launching Shoreside \n"

#-------------------------------------------------------
#  Part 6: Launch the GoodGuy processes
#-------------------------------------------------------
if [ ${GOOD_GUYS} = "yes" ] ; then
    printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_henry.moos >& /dev/null &
    printf "Done Launching Good Guys \n"
fi

#-------------------------------------------------------
#  Part 6: Launch the mokai processes
#-------------------------------------------------------
if [ ${GOOD_GUYS} = "yes" ] ; then
    printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_mokai.moos >& /dev/null &
    printf "Done Launching Good Guys \n"
fi

#-------------------------------------------------------
#  Part 7: Launch the BadGuy processes
#-------------------------------------------------------
for INDEX in `seq 0 $(($AMT-1))`;
do 
    VNAME=${VNAMES[$INDEX]}
    printf "Launching $VNAME MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_$VNAME.moos >& /dev/null &
    sleep 0.1
done
printf "Done Launching Bad Guys \n"


uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
mykill
printf "Done killing processes.   \n"
