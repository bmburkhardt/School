#!/bin/bash
# Bryan Burkhardt / xmv643
# 01 Oct 2017
# proj4.bash for Assignment 4
# Bash file that is passed a date in format MM/DD/YYYY. If "Emails" sub directory
#		exists, it is deleted and re-made. Bash file then runs various awk and bash 
#		commands to create emails for customers who owe money.

# Ensures date passed to proj4.bash is of format MM/DD/YYYY.
if [[ ! $1 =~ [0-9][0-9]/[0-9][0-9]/[0-9][0-9][0-9][0-9]$ ]]; then
	echo "Please enter correct date format: MM/DD/YYYY"
	exit 1
fi
date=$1

# Remove Emails directory if already exists and create a new directory.
if [ -r "Emails/" ]; then
	rm -r Emails/
fi
mkdir Emails/


# Removes people from file who do not owe any money.
awk -f find.awk p4Customer.txt > gOweMoney.txt
# Creates bash file with all the necessary sed commands to create emails.
awk -v date="$date" -f createEmail.awk gOweMoney.txt > gSedCommands.bash
# Runs the generated sed commands.
bash gSedCommands.bash
# Clean up generated files to keep working directory clean.
rm gOweMoney.txt gSedCommands.bash
