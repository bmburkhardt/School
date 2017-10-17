#!/usr/bin/perl -w
# Bryan Burkhardt / xmv643
# 17 Oct 2017
# find.pl for Assignment 6
# Accepts and optional -i, a regular expression, and a list of files. If -i is
#		not passed, program will print a list of files where the filename matches
#		the regular expression. If the filename does not match, it will then check
#		the cntents of that file and print the filename followed by the line for
#		the first match of the regular expression within the file.
#
#		If the -i option is passed, the program will do the opposite and print a
#		a list of files that don't match the regular expression and dont contain
#		it anywhere within the file.

use strict;

my $regex;
my $arg;
my $dir;
my $file;

# if statement that handles if -i option is passed.
if($ARGV[0] eq "-i") {
	$regex = $ARGV[1];
	shift @ARGV; # get rid of -i
	shift @ARGV; # get rid of regular expression

	foreach $arg (@ARGV) {
		my $found = 0; # variable to indicate if pattern matched in file
		($dir, $file) = split("/", $arg); # Remove "DataA/"
		
		# Check if file name doesn't match regular expression
		if($arg !~ m/$regex/) {
			open(IN, "<", $arg) or die "Could not open file $arg\n";
			while(my $line = <IN>) {
				chomp $line;
				# if the regex is found within the file, sets $found to 1 and breaks
				if($line =~ m/$regex/){
					$found = 1;
					last;
				}
			}
			# Prints filename if regex does not match filename or anywhere in file
			if($found == 0) {
				print "$file\n";
			}
		}
	}
}

# Handles if -i option is NOT passed.
else {
	$regex = $ARGV[0];
	shift @ARGV; # get rid of regular expression
	foreach $arg (@ARGV) {
		($dir, $file) = split("/", $arg); # get rid of "DataA/"
		
		# Check if file name matches regular expression. If it does, prints filename
		if($arg =~ m/$regex/) {
			print "$file\n";
		}
		
		# If filename was not a match, checks the contents of file
		else {
			open(IN, "<", $arg) or die "Could not open file $arg\n";
			while(my $line = <IN>) {
				chomp $line;
				# If regular expression found, prints filename and first line of occurence then breaks
				if($line =~ m/$regex/){
					print "$file: $line\n";
					last;
				}
			}
		}
	}
}