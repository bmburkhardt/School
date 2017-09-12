#!/bin/bash
# Bryan Burkhardt / xmv643
# 01 Sep 2017
# findApt.bash for Assignment 1
# Reads from files containing the passed apartment number. Outputs customer
#		data to the terminal.

read email name
read number rent amount dueDate

echo "Email: $email"
echo "Name: $name"
echo "Apt: $number"
echo "Balance: $amount"
echo "Rent Amt: $rent"
echo "Due Date: $dueDate"