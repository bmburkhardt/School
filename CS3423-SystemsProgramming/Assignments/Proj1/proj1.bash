#!/bin/bash
# Bryan Burkhardt / xmv643
# 01 Sep 2017
# proj1.bash for Assignment 1
# Bash program to manage apartment complex customer files.
#		Program creates new customer files, updates account
#		account balances, and finds customer info based on 
#		apartment number.

# Ensure needed files have proper permissions
chmod 700 create.bash
chmod 700 findApt.bash
chmod 700 payment.bash

go=0
# While loop that handles input for the requested actions
while [ $go ]; do
	echo "Enter one of the following actions or press CTRL-D to exit."
	echo "C - create a customer file"
	echo "P - accept a customer payment"
	echo "F - find customer by apartment number"
	if ! read ans; then
		break
	fi
	# Case statement for input from user menu.
	case "$ans" in
		# Create a customer file. 
		# Prompts user for customer information. Checks if customer doesn't exist. 
		#		If doesn't exist, creates a new customer file with information given 
		# 		by user. If customer already exists, error message displayed.
		C)	read -p "Customer Email: " email
			read -p "Customer Full Name: " name
			read -p "Apartment Number: " number
			read -p "Monthly Rent Amt: " rent
			read -p "Next Due Date: " dueDate
			
			# If/else to find out if customer already exists.
			if [ ! -f "Data/$email" ]; then
				touch > "Data/$email"
				export email name number rent dueDate
				bash create.bash < Data/$email
			else
				echo "Error: customer already exists"
			fi
			;;

		# Accept payment from customer.
		# Prompts user for customer information. Checks to see if customer exists. 
		#		If exists, program updates account balance with information given
		#		by user. If customer doesn't exist, error message displayed.
		P) 	read -p "Customer Email: " email
			read -p "Payment Amount: " payment
			
			# If/else to check if customer exists.
			if [ -f "Data/$email" ]; then
				export payment
				bash payment.bash < Data/$email
			else
				echo "Error: customer not found"
			fi
			;;

		# Find customer information by apartment number.
		# Prompts user for customer apartment number. Checks all files in Data directory
		#		for a match of the given apartment number. If apartment number found 
		#		within a file, the contents of the file are printed to the terminal. If
		#		apartment number not found, error message is displayed.
		F) 	found=0
			read -p "Enter apartment number:" number
			
			# If statement to ensure apartment number is properly formatted by user.
			if [[ $number =~ APT-.* ]]; then
				# For loop to check all files for apartment number.
				for fileFound in $(grep -rnwl "$number" Data/*); do
					found=1
					bash findApt.bash < $fileFound
				done
			fi
			if [ $found -eq 0 ]; then
				echo "Error: apartment number not found"
			fi
			;;
		*) 	echo "Error: invalid action value"
	esac
done