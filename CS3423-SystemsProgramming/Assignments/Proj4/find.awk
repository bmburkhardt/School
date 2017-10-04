# Bryan Burkhardt / xmv643
# 01 Oct 2017
# find.awk for Assignment 4
# Awk script that removes "trusted" customers and keeps those who owe money.
BEGIN { FS="," }
{
	if ( $4 <= $5 ) {
		print
	}
}