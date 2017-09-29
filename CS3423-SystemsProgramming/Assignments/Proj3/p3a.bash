#!/bin/bash
# Bryan Burkhardt / xmv643
# 25 Sep 2017
# p3a.bash for Assignment 3
# Bash file that utilizes an awk script and the sort utility to alphabetize
#		the names within the file by last name.
awk -f p3a1.awk unsortedNames.txt | sort | awk -f p3a1.awk > p3a.out