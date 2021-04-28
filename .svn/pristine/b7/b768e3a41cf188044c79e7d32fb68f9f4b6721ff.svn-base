#We assume that the logs folders have been downloaded into directories such as
#p944 and that there are 4 log folders corresponding to rounds 1-4
#for Evan, Felix, Hal, Participant, and Shoreside
import sys
import subprocess
import os
import shutil

list_of_participant_dirs= []
list_of_dirs_to_organize = []

#step 1: make a list of directories that starts with a p
print "Hello, Python!"
cwd = os.getcwd()
print("Current working directory: " + cwd)

list_of_dirs = os.listdir(cwd)
print(list_of_dirs)
for curr_dir in list_of_dirs:
    temp_joined_dir = os.path.join(cwd,curr_dir)
    if(os.path.isdir(temp_joined_dir)):
        if('p' in curr_dir):
            list_of_participant_dirs.append(curr_dir)
            print(curr_dir)

#step 2: check to see if it already has the folders for rounds
#1-4 as r1, r2, r3, r4 made
#if so then skip
#if not, then add to list of folders to organize
for curr_dir in list_of_participant_dirs:
    temp_joined_dir = os.path.join(cwd, curr_dir)
    if(os.path.isdir(temp_joined_dir)):
        if('p' in curr_dir):
            print(curr_dir)
            os.chdir(temp_joined_dir)

            round_one_found = False
            round_two_found = False
            round_three_found = False
            round_four_found = False

            list_of_sub_dirs = os.listdir((os.getcwd()))
            for check_dir in list_of_sub_dirs:
                if('r1' == check_dir):
                    round_one_found = True
                elif('r2' == check_dir):
                    round_two_found = True
                elif('r3' == check_dir):
                    round_three_found = True
                elif('r4' == check_dir):
                    round_four_found = True

            if (round_one_found and round_two_found and round_three_found and round_four_found):
                continue
            else:
                list_of_dirs_to_organize.append(curr_dir)


    os.chdir(cwd)

print(" List of dirs to organize: " , list_of_dirs_to_organize)

#step 3: go through list of folders to organize
#grab the shoreside log folder names
#order the times for r1-r4
#then move those shoreside logs to appropriate subfolder
#then find for each of the 4 vehicles their corresponding log folder
# plus or minus a minute from shoreside
# and move it into the appropriate subfolder r1-r4
for curr_dir in list_of_dirs_to_organize:
    print('investigating dir: ' + curr_dir)
    joined_dir = os.path.join(cwd, curr_dir)
    print('joined dir: ' + joined_dir)
    if(os.path.isdir(joined_dir)):
        print(curr_dir + ' is a dir')
        if('p' in curr_dir):
            print(curr_dir)
            os.chdir(joined_dir)

            list_of_sub_dirs = os.listdir((os.getcwd()))

            list_of_sub_dirs.sort()
            list_of_shoreside_dirs = []
            list_of_evan_dirs = []
            list_of_hal_dirs = []
            list_of_felix_dirs = []
            list_of_p_log_dirs = []

            for check_dir in list_of_sub_dirs:
                if("SHORESIDE" in check_dir):
                    list_of_shoreside_dirs.append(check_dir)
                elif("EVAN" in check_dir):
                    list_of_evan_dirs.append(check_dir)
                elif("HAL" in check_dir):
                    list_of_hal_dirs.append(check_dir)
                elif("FELIX" in check_dir):
                    list_of_felix_dirs.append(check_dir)
                elif("_P" in check_dir):
                    list_of_p_log_dirs.append(check_dir)

            list_of_shoreside_dirs.sort()
            list_of_evan_dirs.sort()
            list_of_hal_dirs.sort()
            list_of_felix_dirs.sort()
            list_of_p_log_dirs.sort()

            shoreside_dir = list_of_shoreside_dirs.pop()
            evan_dir = list_of_evan_dirs.pop()
            felix_dir = list_of_felix_dirs.pop()
            hal_dir = list_of_hal_dirs.pop()
            p_dir = list_of_p_log_dirs.pop()

            print("Will put these dirs in r4 ")
            print(shoreside_dir)
            print(evan_dir)
            print(felix_dir)
            print(hal_dir)
            print(p_dir)

            os.mkdir('r4')
            shutil.move(shoreside_dir, 'r4')
            shutil.move(evan_dir, 'r4')
            shutil.move(felix_dir, 'r4')
            shutil.move(hal_dir, 'r4')
            shutil.move(p_dir, 'r4')

            shoreside_dir = list_of_shoreside_dirs.pop()
            evan_dir = list_of_evan_dirs.pop()
            felix_dir = list_of_felix_dirs.pop()
            hal_dir = list_of_hal_dirs.pop()
            p_dir = list_of_p_log_dirs.pop()

            print("Will put these dirs in r3 ")
            print(shoreside_dir)
            print(evan_dir)
            print(felix_dir)
            print(hal_dir)
            print(p_dir)

            os.mkdir('r3')
            shutil.move(shoreside_dir, 'r3')
            shutil.move(evan_dir, 'r3')
            shutil.move(felix_dir, 'r3')
            shutil.move(hal_dir, 'r3')
            shutil.move(p_dir, 'r3')


            shoreside_dir = list_of_shoreside_dirs.pop()
            evan_dir = list_of_evan_dirs.pop()
            felix_dir = list_of_felix_dirs.pop()
            hal_dir = list_of_hal_dirs.pop()
            p_dir = list_of_p_log_dirs.pop()

            print("Will put these dirs in r2 ")
            print(shoreside_dir)
            print(evan_dir)
            print(felix_dir)
            print(hal_dir)
            print(p_dir)

            os.mkdir('r2')
            shutil.move(shoreside_dir, 'r2')
            shutil.move(evan_dir, 'r2')
            shutil.move(felix_dir, 'r2')
            shutil.move(hal_dir, 'r2')
            shutil.move(p_dir, 'r2')


            shoreside_dir = list_of_shoreside_dirs.pop()
            evan_dir = list_of_evan_dirs.pop()
            felix_dir = list_of_felix_dirs.pop()
            hal_dir = list_of_hal_dirs.pop()
            p_dir = list_of_p_log_dirs.pop()

            print("Will put these dirs in r1 ")
            print(shoreside_dir)
            print(evan_dir)
            print(felix_dir)
            print(hal_dir)
            print(p_dir)

            os.mkdir('r1')
            shutil.move(shoreside_dir, 'r1')
            shutil.move(evan_dir, 'r1')
            shutil.move(felix_dir, 'r1')
            shutil.move(hal_dir, 'r1')
            shutil.move(p_dir, 'r1')

    os.chdir(cwd)


