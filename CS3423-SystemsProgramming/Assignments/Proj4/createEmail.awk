# Bryan Burkhardt / xmv643
# 03 Oct 2017
# createEmail.awk for Assignment 4
# Awk script that creates sed commands for a passed CSV template file. Values
#		replaced are EMAIL, FULLNAME, NAME, TITLE, AMOUNT, DATE.
BEGIN { 
	FS=","
	gsub("/","\\\/",date)
}
{
	# if statement keeps empty lines in file from generating sed commands.
	if ($0){
		n = split($2, name, " ")
		print "sed -e 's/EMAIL/"$1"/g' -e 's/FULLNAME/"$2"/g' -e 's/NAME/"name[n]"/g' -e 's/TITLE/"$3"/g' -e 's/AMOUNT/"$5"/g' -e 's/DATE/"date"/g' template.txt > Emails/"$1
	}
}