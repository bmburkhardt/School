# Bryan Burkhardt / xmv643
# 25 Sep 2017
# p3a1.awl for Assignment 3
# Awk script that simply swaps the name in the first and last position of the line.
#		Doing this allows bash to sort the files then swap the names again to return 
#		the file to name(first, last).
BEGIN { FS=" " }
{
	temp = $1;
	$1 = $NF;
	$NF = temp;
	print $0;
}