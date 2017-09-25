#!/bin/bash
# Bryan Burkhardt / xmv643
# 22 Sep 2017
# p2a.bash for Assignment 2
# Bash script that produces user id's of people who have not logged in
#		since the start of 2017. This file utilizes sed scripts for
#		creating this data.

# Ensure proper permissions.
chmod u=rw p2a.sed p2a.Dollar.sed
# p2a.sed
# Produces list of user id's of users who have not logged in since 2017.
sed -f p2a.sed lastlog1.out > lastlog1new.out

# p2a.Dollar.sed
# Produces list of user id's, followed by a "$" of users who have not
#		logged in since 2017.
sed -f p2a.Dollar.sed lastlog2.out > lastlog2new.out

# Create intersection of the two log files to ensure users haven't
#		logged in across all servers.
grep -f lastlog2new.out lastlog1new.out > p2a.out

# Clean up excess files.
rm lastlog1new.out lastlog2new.out