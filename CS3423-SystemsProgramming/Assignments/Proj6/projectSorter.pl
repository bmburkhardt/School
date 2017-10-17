#!/usr/bin/perl -w
# Bryan Burkhardt / xmv643
# 17 Oct 2017
# projectSorter.pl for Assignment 6
# Program accepts a specified directory and rearranges its contents into new
#		sub-directories.

use strict;

my @files = glob "$ARGV[0]/*"; # Put files from directory into array
my $arg;

# Check if "misc" sub-directory does not exist. If it does not, create it.
unless( -e "$ARGV[0]/misc") {
	`mkdir $ARGV[0]/misc`;
}

# Run through each file in our array
foreach $arg (@files) {
	# Find the project files
	if($arg =~ m/proj.*/) {
		my ($proj, $filename) = split("proj", $arg); # get rid of "proj"
		my ($filename1, $ext) = split('\.', $filename); # get rid of file extension
		# Make new assignment directory if it does not exist
		unless( -e "$ARGV[0]/assignment$filename1") {
			`mkdir $ARGV[0]/assignment$filename1`;
		}
		`mv $arg $ARGV[0]/assignment$filename1`; # Move current file to its new directory
	}
	# Puts all non project files into misc directory
	else {
		`mv $arg $ARGV[0]/misc`;
	}
}