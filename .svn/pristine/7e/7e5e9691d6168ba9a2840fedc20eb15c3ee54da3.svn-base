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
from go_through_rounds import return_string_of_all_round_results

#Step 1: open a file to write results out to
f = open("all_participant_results.csv","w")
g = open("all_participant_flag_events.csv", "w")

#Step 2: write the header out
header_string = "Participant ID "
for x in range(4):
    #each round is repeated 4 times

    each_round_string = ",GROUP, ROUND  , SELF_AUTHORIZE ,  WIN_OR_LOSS, TOTAL_FLAG_GRABS_BLUE,TOTAL_FLAG_SCORES_BLUE,TOTAL_FLAG_GRABS_RED,TOTAL_FLAG_SCORES_RED, TOTAL_TIMES_BLUE_ONE_TAGGED, TOTAL_TIMES_BLUE_SPEECH_COMMANDED, TOTAL_TIMES BLUE_DIALOG_ERROR, TOTAL_TIMES_BLUE_COMMAND_CANCELED"
    header_string += each_round_string
    for x in range(10):

    #each trial is repeated 10 times in a round
        trial_string = ", trial key,RELIABLE,BLUE_FLAG_SCORES,BLUE_FLAG_GRABS,RED_FLAG_SCORES,RED_FLAG_GRABS,TIMES_TAGGED,SPEECH_COMMANDED,DIALOG_ERROR,COMMAND_CANCELED"
        header_string += trial_string


f.write(header_string)

g.write("Participant ID, Round 1, Round 2, Round 3, Round 4")

#Step 3: collect each participant's results
#        and write it out to file line by line
print "Hello, Python!"
cwd = os.getcwd()
print("Current working directory: " + cwd)

list_of_dirs = os.listdir(cwd)
print(list_of_dirs)
for curr_dir in list_of_dirs:
    if(os.path.isdir(curr_dir)):
        if('p' in curr_dir):
            print(curr_dir)
            os.chdir(curr_dir)
            results_for_current_p = ""
            flag_events_r1=""
            flag_events_r2=""
            flag_events_r3=""
            flag_events_r4=""
            participant_id=""
            results_for_current_p, participant_id, flag_events_r1, flag_events_r2, flag_events_r3, flag_events_r4 = return_string_of_all_round_results()
            f.write('\n')
            f.write(results_for_current_p)

            g.write('\n')
            g.write(participant_id + "," + flag_events_r1 + "," + flag_events_r2 + "," + flag_events_r3 + "," + flag_events_r4)

    os.chdir(cwd)

f.close()
g.close()
