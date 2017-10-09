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
		(my $email, my $fullname, my $title, my $paid, my $owe) = split ",", $line;
		(my @name) = split " ", $fullname;
		# Only create emails for customers who owe more than they have payed.
		if($owe >= $paid) {
			open(TEMPLATE, "<", "template.txt") or die "Could not open file template.txt\n";
			open(OUTFILE, ">>", "Emails/$email") or die "Could not open file Emails/$email\n";
			# Replace placeholders from template file into new file named by customer email.
			while(my $inline = <TEMPLATE>) {
				$inline =~ s/EMAIL/$email/g;
				$inline =~ s/FULLNAME/$fullname/g;
				$inline =~ s/NAME/$name[$#name]/g;
				$inline =~ s/TITLE/$title/g;
				$inline =~ s/AMOUNT/$owe/g;
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