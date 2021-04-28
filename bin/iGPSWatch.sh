# Title   : gps_info.sh
# Summary : A simple app that listens for a stream of GPS NMEA 1.7 messages
# and displays a human readable summary
#
# Author  : Raphael Segal
# Date    : 11/28/16


# Format
# PDOP   DELTA PDOP   HDOP    VDOP     SatelliteCount     SatelliteList
# #.##   #.##         #.##    #.##     #.##               ,,,,,,,,,,,,
# SAT: SNR, ...

#!/bin/bash

# NMEA sentences we are concerned with are GPGSA, GPGSV
RELEVANT_SENTENCES='GPGSA'

declare PDOP
declare OLD_PDOP
declare DELTA_PDOP
declare -i DELTA_PDOP_TIME
declare -i CURRENT_TIME
declare HDOP
declare VDOP
declare SATELLITE_LIST
declare SATELLITE_COUNT
declare SNR_LIST

OLD_PDOP="0.0"
DELTA_PDOP_TIME=`date +%s`

declare FIRST_ITERATION="true"

for SV in {1..60}
do
	SNR_LIST[SV]="-"
done

printf "PDOP\tDELTA PDOP\tHDOP\tVDOP\tSATELLITE COUNT\tSATELLITE LIST\n"

while read LINE
do
	IFS=' '
	# echo $LINE
    if [[ "$LINE" == *"GPGSA"* ]]
    then
    	# printf "\n%s" "$LINE"
    	IFS=','
		read -a GPGSA_ARRAY <<< "$LINE"
		IFS=' '
		read -a SATELLITE_LIST <<< "${GPGSA_ARRAY[@]:3:12}"
        PDOP="${GPGSA_ARRAY[15]}"
		HDOP="${GPGSA_ARRAY[16]}"

		IFS='*'
		read -r -a VDOP_AND_CHECKSUM <<< "${GPGSA_ARRAY[17]}"
		VDOP="${VDOP_AND_CHECKSUM[0]}"

    elif [[ "$LINE" == *"GPGSV"* ]]
    then
    	# GSV format:
		#
		# msg name				0
		# total msgs 			1
		# msg id    			2
		# visible satellites	3
		# 4x
		# satellite id			4 + 4n
		# ?						5 + 4n
		# ?						6 + 4n
		# SNR 					7 + 4n

    	IFS='*'
    	read -a GPGSV_LINE <<< "$LINE"

    	IFS=','
		read -a GPGSV_ARRAY <<< "${GPGSV_LINE[0]}"
		SATELLITE_COUNT="${GPGSV_ARRAY[3]}"

		SAT_ID_OFFSET=4
		SNR_OFFSET=7
		SATELLITE_LIST_RAW_LENGTH=${#GPGSV_ARRAY[@]}
		SATELLITES_IN_LIST=$(($SATELLITE_LIST_RAW_LENGTH/4-1))

		for ((i=0; i<$SATELLITES_IN_LIST; i++))
		do
			ID_LOCATION=$(( 4 * $i + $SAT_ID_OFFSET ))
			SNR_LOCATION=$(( 4 * $i + $SNR_OFFSET ))
			SAT_ID=${GPGSV_ARRAY[$ID_LOCATION]}
			SAT_SNR=${GPGSV_ARRAY[$SNR_LOCATION]}
			SNR_LIST[SAT_ID]=$SAT_SNR
		done
    fi

    if [ -n "$OLD_PDOP" ]
    then
    	DELTA_PDOP='-'
	fi

    CURRENT_TIME=`date +%s`
    if (($CURRENT_TIME - 60 >= $DELTA_PDOP_TIME))
    then
    	if [ -z "$OLD_PDOP" ]
    	then
			DIFFERENCE_EQUATION="$PDOP - $OLD_PDOP"
			DELTA_PDOP=`echo "$DIFFERENCE_EQUATION" | bc`
		fi

		OLD_PDOP=$PDOP
		DELTA_PDOP_TIME=$CURRENT_TIME
    fi

    # Scrub previous output
    if [ "$FIRST_ITERATION" == "true" ]
   	then
   		FIRST_ITERATION="false"
    else
    	tput cuu 1 # move cursor up by one line
   		tput el # clear the line
   		tput cuu 1 
    	tput el 
   	fi

    # Note the \r (carriage return) at the end - this causes it to reprint in 
    # place instead of scrolling.
    printf "% 4s\t% 4s\t\t% 4s\t% 4s\t% 2s" "$PDOP" "$DELTA_PDOP" "$HDOP" "$VDOP" "$SATELLITE_COUNT"
    printf "\t\t"
    for INDEX in ${!SATELLITE_LIST[@]}; do
    	printf "%s " "${SATELLITE_LIST[$INDEX]}"
	done
    printf "\r\n"
    for (( SAT_ID=1; SAT_ID < ${#SNR_LIST[@]}; SAT_ID++ )); do #SAT_ID in ${!SNR_LIST[@]}; do
    	SNR=${SNR_LIST[$SAT_ID]}
    	if [[ $SNR != "-" && ($SNR != " " && $SNR != "") ]]; then
    		printf "%s: % 2s%s" $SAT_ID $SNR ",  "
    	fi
	done
	printf "\r\n"

    sleep 0.03

done < "${1:-/dev/stdin}"

# for cleanliness on file read
printf "\nDone!\n"
