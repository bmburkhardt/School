#!/bin/bash
# Bryan Burkhardt / xmv643
# 22 Sep 2017
# p2b.bash for Assignment 2
# Bash script that produces user id's of people who have not logged in
#		since the start of 2017. This file utilizes sed scripts and
#		other bash utilities for creating this data.

# Ensure proper permissions.
chmod u=rw p2a.sed p2b.sed

# p2a.sed
# Produces list of user id's of users who have not logged in since 2017.
sed -f p2a.sed lastlog1.out > lastlog1new.out
sed -f p2a.sed lastlog2.out > lastlog2new.out

# Merge both log files together and clean up excess files.
cat lastlog1new.out lastlog2new.out > merge.out
rm lastlog1new.out lastlog2new.out

# Sort user id's in merged logfile.
# Invoke uniq -c to group duplicate user id's.
# Remove exces files.
sort merge.out -o merge.out
uniq -c merge.out > unique.out
rm merge.out

# p2b.sed
# Deletes lines from file that contain unique user names. Once deleted,
#		formats remaining user id's to remove starting spaces and the
#		"2" from uniq -c. Then removes excess files.
sed -f p2b.sed unique.out > p2b.out
rm unique.out