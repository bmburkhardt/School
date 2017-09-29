#!/bin/bash
# Bryan Burkhardt / xmv643
# 25 Sep 2017
# p3b.bash for Assignment 3
# Bash file that utilizes an awk script on a reservation file to neatly output
#		customer flight information.
awk -f p3b.awk reservation.txt > p3b.out