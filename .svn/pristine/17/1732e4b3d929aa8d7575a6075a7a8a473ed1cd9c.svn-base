#here we assume script is being run at the participant level
#thus, the script needs to go into the corresponding
#SHORESIDE and PARTICIPANT folders and grab their .alog files
#assumes we have class_trial.py in same directory
import sys
import subprocess
import os
from collections import OrderedDict
from class_trial import TrialStats
from return_ordered_dictionary import ordered_dictionary_of_trials 

def grab_round_results():
    results_string=""

    catching_od , GROUP, ROUND, SELF_AUTHORIZE,  WIN_OR_LOSS, TOTAL_FLAG_GRABS_BLUE, TOTAL_FLAG_SCORES_BLUE, TOTAL_FLAG_GRABS_RED, TOTAL_FLAG_SCORES_RED, LIST_OF_FLAG_EVENTS_AND_TIMES, TOTAL_TIME_BLUE_ONE_TAGGED, TOTAL_TIMES_BLUE_SPEECH_COMMANDED, TOTAL_TIMES_BLUE_DIALOG_ERROR, TOTAL_TIMES_BLUE_COMMAND_CANCELED = ordered_dictionary_of_trials()

    results_string=  GROUP + "," + ROUND + "," + SELF_AUTHORIZE +","+  WIN_OR_LOSS+","+ str(TOTAL_FLAG_GRABS_BLUE) +","+ str(TOTAL_FLAG_SCORES_BLUE) + "," + str(TOTAL_FLAG_GRABS_RED) + "," + str(TOTAL_FLAG_SCORES_RED) + "," + str(TOTAL_TIME_BLUE_ONE_TAGGED) + "," + str(TOTAL_TIMES_BLUE_SPEECH_COMMANDED) + "," + str(TOTAL_TIMES_BLUE_DIALOG_ERROR) + "," + str(TOTAL_TIMES_BLUE_COMMAND_CANCELED)

    if (len(catching_od) == 0):
        for i in range(10):
            results_string+= ", N\A"
            results_string+= ", N\A" 
            results_string+= ", N\A" 
            results_string+= ", N\A" 
            results_string+= ", N\A" 
            results_string+= ", N\A" 
            results_string+= ", N\A" 
            results_string+= ", N\A" 
            results_string+= ", N\A"
            results_string+= ", N\A"

    else:
        for key, value in catching_od.items():
            results_string+= "," + key
            results_string+= "," + value.RELIABLE
            results_string+= "," + str(value.BLUE_FLAG_SCORES)
            results_string+= "," + str(value.BLUE_FLAG_GRABS)
            results_string+= "," + str(value.RED_FLAG_SCORES)
            results_string+= "," + str(value.RED_FLAG_GRABS)
            results_string+= "," + str(value.TIMES_TAGGED)
            results_string+= "," + str(value.SPEECH_COMMANDED)
            results_string+= "," + str(value.DIALOG_ERROR)
            results_string+= "," + str(value.COMMAND_CANCELED)

    return results_string, LIST_OF_FLAG_EVENTS_AND_TIMES, ROUND

def return_string_of_all_round_results():
    results_r1=""
    results_r2=""
    results_r3=""
    results_r4=""

    list_of_flag_events_r1=""
    list_of_flag_events_r2=""
    list_of_flag_events_r3=""
    list_of_flag_events_r4=""
    list_of_zero_results = []
    list_of_flag_zeros = []
    partipant_id_clean=""
    print "Hello, Python!"
    shoreside_dir_name=""
    cwd = os.getcwd()
    print("Current working directory: " + cwd)

    #find PID of participant id
    curr_dir = cwd.split('/')
    participant_id= curr_dir[-1]
    print("Participant ID: " + participant_id)
    participant_id_clean = participant_id.replace("p","")
    print("Participant ID clean: " + participant_id_clean)

    list_of_dirs = os.listdir(cwd)
    print(list_of_dirs)
    for curr_dir in list_of_dirs:
        if(os.path.isdir(curr_dir)):
            if('r1' or 'r2' or 'r3' or 'r4' in curr_dir):
                print(curr_dir)
                os.chdir(curr_dir)
                results, list_of_flag_events, temp_ROUND = grab_round_results()
                #go through and assign directly based on round number
                #or put in a catch list to deal with later
                if ("1.0" in temp_ROUND):
                    results_r1 = results
                    list_of_flag_events_r1 = list_of_flag_events
                elif ("2.0" in temp_ROUND):
                    results_r2 = results
                    list_of_flag_events_r2 = list_of_flag_events
                elif ("3.0" in temp_ROUND):
                    results_r3 = results
                    list_of_flag_events_r3 = list_of_flag_events
                elif ("4.0" in temp_ROUND):
                    results_r4 = results
                    list_of_flag_events_r4 = list_of_flag_events
                else: #catch the rounds labelled 0s
                    list_of_zero_results.append(results)
                    list_of_flag_zeros.append(list_of_flag_events)

        os.chdir(cwd)

    #now go through list until empty
    if (results_r1 == ""):
        results_r1 = list_of_zero_results.pop()
        list_of_flag_events_r1 = list_of_flag_zeros.pop()

    if (results_r2 == ""):
        results_r2 = list_of_zero_results.pop()
        list_of_flag_events_r2 = list_of_flag_zeros.pop()

    if (results_r3 == ""):
        results_r3 = list_of_zero_results.pop()
        list_of_flag_events_r3 = list_of_flag_zeros.pop()

    if (results_r4 == ""):
        results_r4 = list_of_zero_results.pop()
        list_of_flag_events_r4 = list_of_flag_zeros.pop()

    if(results_r1=="" or results_r2=="" or results_r3=="" or results_r4==""):
        print("Unable to retrieve results from at least 1 round")
        exit(1)


    total_result_string = participant_id_clean + "," + results_r1 + "," + results_r2 + "," +results_r3 + "," + results_r4

    print(total_result_string)

    return total_result_string, participant_id_clean, list_of_flag_events_r1, list_of_flag_events_r2, list_of_flag_events_r3, list_of_flag_events_r4
