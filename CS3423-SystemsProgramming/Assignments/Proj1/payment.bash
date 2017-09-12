#!/bin/bash
# Bryan Burkhardt / xmv643
# 01 Sep 2017
# payment.bash for Assignment 1
# Updates account balance for given email address

read email name
read number rent amount dueDate

echo "$email $name" > "Data/$email"
echo "$number $rent $((amount+payment)) $dueDate" >> "Data/$email"