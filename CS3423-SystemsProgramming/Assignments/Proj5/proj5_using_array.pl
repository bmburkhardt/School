#!/usr/bin/perl -w
# Bryan Burkhardt / xmv643
# 07 Oct 2017
# proj5.pl for Assignment 5
# Perl program that parses a customer file and creates emails using a template
#		file for customers who owe more than they have payed over the course
#		of being a customer. Program takes date as input from command line
#		in format mm/dd/yyyy.

use strict;
# Get date from command line argument
my $date = $ARGV[0];
# Ensures proper date format
if($date =~ m/\d{2}\/\d{2}\/\d{4}$/ && @ARGV == 1) {
	# Remove Emails directory if it already exists
	if(-d "Emails") {
		`rm -r Emails`;
	}
	mkdir "Emails" or die "Could not make directory Emails\n";
	open(CUSTFILE, "<", "p5Customer.txt") or die "Could not open file p5Customer.txt\n";
	# Parse the customer file
	while(my $line = <CUSTFILE>) {
		chomp $line;
		# Collect variables from customer file
		# $data[0] == email
		# $data[1] == fullname
		# $data[2] == title
		# $data[3] == paid amount
		# $data[4] == owe amount
		my @data = split(",", $line);
		(my @name) = split " ", $data[1];
		# Only create emails for customers who owe more than they have payed.
		if($data[4] >= $data[3]) {
			open(TEMPLATE, "<", "template.txt") or die "Could not open file template.txt\n";
			open(OUTFILE, ">>", "Emails/$data[0]") or die "Could not open file Emails/$data[0]\n";
			# Replace placeholders from template file into new file named by customer email.
			while(my $inline = <TEMPLATE>) {
				$inline =~ s/EMAIL/$data[0]/g;
				$inline =~ s/FULLNAME/$data[1]/g;
				$inline =~ s/NAME/$name[$#name]/g;
				$inline =~ s/TITLE/$data[2]/g;
				$inline =~ s/AMOUNT/$data[4]/g;
				$inline =~ s/DATE/$date/g;
				print OUTFILE $inline;
			}
			close(OUTFILE);
			close(TEMPLATE);
		}
	}
	close(CUSTFILE);
}
else {
	print "Please enter correct date format: mm/dd/yyyy\n";
}