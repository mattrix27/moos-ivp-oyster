#here we assume script is being run at the round level
#thus, the script needs to go into the corresponding
#SHORESIDE and PARTICIPANT folders and grab their .alog files
#assumes we have class_trial.py in same directory
import sys
import subprocess
import os
from collections import OrderedDict
from class_trial import TrialStats

def next_ordered_key(od,key):
    next = od._OrderedDict__map[key][1]
    if next is od._OrderedDict__root:
        raise ValueError("{!r} is the last key".format(key))
    return next[2]

#this function is independent of the class TrialStats in the sense that it works on an OrderedDict
#with variable types of TrialStats
#create a function that given the time of an event, will return the key to the appropriate scenario
#this function will be useful for going through the participant's logs and aligning events with scenarios
def find_proper_scenario_key_given_event_time(od,event_time):
    keyList=sorted(od.keys())
    lastKey = next(reversed(od))

    #scan through the events finding the appropriate key to return
    for key,value in od.items():
        print(key)
        #we check if at the last element and return that scenario's key
        if lastKey == key:
            return key
        else:
        #else we return the current scenario key if time is <= current key and < next key
            curr_scenario_time = od[key].TIME_FROM_AQUATICUS_GAME_START
            next_key = next_ordered_key(od,key)
            next_scenario_time = od[next_key].TIME_FROM_AQUATICUS_GAME_START
            if(event_time >= curr_scenario_time and event_time < next_scenario_time):
                return key




trialDictionary = OrderedDict() 

print "Hello, Python!"
shoreside_dir_name=""
cwd = os.getcwd()
print("Current working directory: " + cwd)
list_of_dirs = os.listdir(cwd)
print(list_of_dirs)
for curr_dir in list_of_dirs:
    if(os.path.isdir(curr_dir)):
        if('SHORESIDE' in curr_dir):
            shoreside_dir_name = curr_dir

print("Shoreside Directory: " + shoreside_dir_name)

subprocess.call('which aloggrep',shell=True)
alog_cmd = "aloggrep -q " + shoreside_dir_name + "/*.alog AQUATICUS_GAME* GROUP SCENARIO ROUND SELF_AUTHORIZE* RELIABLE SAY_MOOS| egrep 'AQUATICUS_GAME|GROUP|SCENARIO|ROUND|SELF_AUTHORIZE|RELIABLE|grab|goal|tag' > shoreside_compact.txt"
subprocess.call(alog_cmd,shell=True)

#populate important fields
GROUP=""
ROUND=""
SCENARIO=""
SELF_AUTHORIZE=""
RELIABLE=""
TOTAL_FLAG_GRABS_BLUE=0
TOTAL_FLAG_SCORES_BLUE=0
TOTAL_FLAG_GRABS_RED=0
TOTAL_FLAG_SCORES_RED=0
WIN_OR_LOSS=""
SHORESIDE_GAME_START=0.0
file = open("shoreside_compact.txt","r")
for line in file:
    fields = line.split()
    #0 is time, 1 is variable, 2 is source app, 3 is value
    print(fields[0] + " " + fields[1] + " " + fields[3])
    if(fields[1] == "GROUP"):
        GROUP=fields[3]
    elif(fields[1] == "ROUND"):
        ROUND=fields[3]
    elif(fields[1] == "SAY_MOOS"):
        if "deny" in fields[3]:
            continue
        if fields[3] == "file=tag_post_blue_one.wav":
            latestKey = next(reversed(trialDictionary))
            trialDictionary[latestKey].TIMES_TAGGED += 1
        elif "red" in fields[3]:
            if "grab" in fields[3]:
                TOTAL_FLAG_GRABS_RED = TOTAL_FLAG_GRABS_RED + 1
                latestKey = next(reversed(trialDictionary))
                trialDictionary[latestKey].RED_FLAG_GRABS += 1
            elif "goal" in fields[3]:
                TOTAL_FLAG_SCORES_RED = TOTAL_FLAG_SCORES_RED + 1
                latestKey = next(reversed(trialDictionary))
                trialDictionary[latestKey].RED_FLAG_SCORES += 1
        elif "blue" in fields[3]:
            if "grab" in fields[3]:
                TOTAL_FLAG_GRABS_BLUE = TOTAL_FLAG_GRABS_BLUE + 1
                latestKey = next(reversed(trialDictionary))
                trialDictionary[latestKey].BLUE_FLAG_GRABS += 1
            elif "goal" in fields[3]:
                TOTAL_FLAG_SCORES_BLUE = TOTAL_FLAG_SCORES_BLUE + 1
                latestKey = next(reversed(trialDictionary))
                trialDictionary[latestKey].BLUE_FLAG_SCORES += 1
    elif(fields[1] == "SELF_AUTHORIZE_BLUE_TWO"):
        SELF_AUTHORIZE = fields[3]
    elif(fields[1] == "SCENARIO"):
        #using the SCENARIO as the key to the ordered dictionary
        trialDictionary[fields[3]] = TrialStats()
        latestKey = next(reversed(trialDictionary))
        trialDictionary[latestKey].TIME_FROM_AQUATICUS_GAME_START = float(fields[0]) - float(SHORESIDE_GAME_START)
    elif("AQUATICUS_GAME" in fields[1]):
        if(fields[3]=="play"):
            SHORESIDE_GAME_START=fields[0]

#check for if proper information in shoreside log has been found
if GROUP=="" or ROUND=="" or SELF_AUTHORIZE=="" or SHORESIDE_GAME_START==0.0 or (len(trialDictionary)==0):
    print("missing key game information: GROUP "+ GROUP + " ROUND: " + ROUND + " SELF_AUTHORIZE: " + SELF_AUTHORIZE + " SHORESIDE_GAME_START: " + str(SHORESIDE_GAME_START))
    sys.exit(1)

participant_dir_name=""
for curr_dir in list_of_dirs:
    if(os.path.isdir(curr_dir)):
        if('P9' in curr_dir):
            participant_dir_name = curr_dir

participant_alog= "aloggrep " + participant_dir_name + "/*.alog AQUATICUS_GAME* uDialogManager uSpeechRec -q -nc -nr -gl -ac > participant_compact.txt"
subprocess.call(participant_alog,shell=True)

PARTICIPANT_GAME_START=0.0
file = open("participant_compact.txt","r")
for line in file:
    fields = line.split()
    #0 is time, 1 is variable, 2 is source app, 3 is value
    print(fields[0] + " " + fields[1] + " " + fields[3])
    if("AQUATICUS_GAME" in fields[1]):
        if(fields[3]=="play"):
            PARTICIPANT_GAME_START=fields[0]
    elif(fields[1]=="SPEECH_COMMANDED"):
        #identify which key we are adding this too
        event_time = float(fields[0]) - float(PARTICIPANT_GAME_START)
        current_key = find_proper_scenario_key_given_event_time(trialDictionary,event_time)
        trialDictionary[current_key].SPEECH_COMMANDED += trialDictionary[current_key].SPEECH_COMMANDED + 1
    elif(fields[1]=="DIALOG_ERROR"):
        #identify which key we are adding this too
        event_time = float(fields[0]) - float(PARTICIPANT_GAME_START)
        current_key = find_proper_scenario_key_given_event_time(trialDictionary,event_time)
        trialDictionary[current_key].DIALOG_ERROR += trialDictionary[current_key].DIALOG_ERROR + 1
    elif(fields[1]=="COMMAND_CANCELED"):
        #identify which key we are adding this too
        event_time = float(fields[0]) - float(PARTICIPANT_GAME_START)
        current_key = find_proper_scenario_key_given_event_time(trialDictionary,event_time)
        trialDictionary[current_key].COMMAND_CANCELED += trialDictionary[current_key].COMMAND_CANCELED + 1

#check for if proper information for participant log has been found
if PARTICIPANT_GAME_START==0.0:
    print("Missing key participant log information: PARTICIPANT_GAME_START " + PARTICIPANT_GAME_START)
    sys.exit(1)

#test for win or loss with respect to BLUE TEAM
if TOTAL_FLAG_SCORES_BLUE > TOTAL_FLAG_SCORES_RED:
    WIN_OR_LOSS = "WIN"
elif TOTAL_FLAG_SCORES_BLUE < TOTAL_FLAG_SCORES_RED:
    WIN_OR_LOSS = "LOSE"
elif TOTAL_FLAG_SCORES_BLUE ==  TOTAL_FLAG_SCORES_RED:
    if TOTAL_FLAG_GRABS_BLUE > TOTAL_FLAG_GRABS_RED:
        WIN_OR_LOSS = "WIN"
    elif TOTAL_FLAG_GRABS_BLUE < TOTAL_FLAG_GRABS_RED:
        WIN_OR_LOSS = "LOSE"
    elif TOTAL_FLAG_GRABS_BLUE == TOTAL_FLAG_GRABS_RED:
        WIN_OR_LOSS = "TIE"

print("GROUP: " + GROUP +" ROUND: " + ROUND)
print("Blue Robot Higher Level Autonomy: " + SELF_AUTHORIZE)
print("Blue Team Result: " + WIN_OR_LOSS)
print("Blue Team: Grabs " + str(TOTAL_FLAG_GRABS_BLUE) + " Scores: " + str(TOTAL_FLAG_SCORES_BLUE))
print("Red Team: Grabs " + str(TOTAL_FLAG_GRABS_RED) + " Scores: " + str(TOTAL_FLAG_SCORES_RED))

for key, value in trialDictionary.items():
    print("Trial: " + key)
    print("Blue flag scores: " + str(value.BLUE_FLAG_SCORES))
    print("Blue flag grabs: " + str(value.BLUE_FLAG_GRABS))
    print("Red flag scores: " + str(value.RED_FLAG_SCORES))
    print("Red flag grabs: " + str(value.RED_FLAG_GRABS))
    print("Reliable: " + value.RELIABLE)
    print("Times tagged: " + str(value.TIMES_TAGGED))
    print("Speech Commanded: " + str(value.SPEECH_COMMANDED))
    print("DIALOG_ERROR: " + str(value.DIALOG_ERROR))
    print("COMMAND_CANCELED: " + str(value.COMMAND_CANCELED))
 
