# Bryan Burkhardt / xmv643
# 25 Sep 2017
# p3b.awk for Assignment 3
# Awk file that parses through a file of data to output neatly organized
#		customer information to certain specifications.

# Creating initial columns for output.
BEGIN { 
	FS=" ";
	printf("%-14s %-12s %8s %12s\n", "Name", "Flight", "Seats", "Total Cost");
}
{
	# Checks if the current line is the one which contains the customer's admin info.
	#		Initializes customer's total flight cost to 0 and assigns last name to
	#		the name variable.
	if( $1 == "CUST" ) {
		sum = 0
		name = $NF
	}

	# Checks if the current line is the one which contains the reservation info.
	#		Updates customer's total flight cost, prints their last name and
	#		flight info. Adds their flight number and seat count to hash array.
	if( $1 == "RESERVE" ) {
		sum += ($3 * $4)
		printf("%-14.12s %-12.10s %8s %12.2f\n", name, $2, $3, ($3 * $4))

		if( $2 in flightM) {
			flightM[$2] += $3
		}
		else {
			flightM[$2] = $3
		}
	}

	# Checks if the current line is the end of the customer info. If it is, prints
	#		their total flight cost.	
	if( $1 == "ENDCUST") {
		printf("%-14s %-12s %8s %12.2f\n", "", "", "Total", sum)
	}
}

# Once all customer's have been processed, outputs the flight numbers and total 
#		seats reserved for each flight.
END {
	printf("%-12s %12s\n", "Flight", "Total Seats")
	for (key in flightM) {
		printf("%-12s %12s\n", key, flightM[key])
	}
}