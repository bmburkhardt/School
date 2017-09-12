#!/bin/bash
# Bryan Burkhardt / xmv643
# 01 Sep 2017
# create.bash for Assignment 1
# Creates new record to given email if customer is 
#		not already in the database.

echo "$email $name" >> "Data/$email"
echo "$number $rent 0 $dueDate" >> "Data/$email"