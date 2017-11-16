/**********************************************************************
xdir.c by Bryan Burkhardt
Purpose:	
    The purpose of this file is to emulate the bash functions "ls -l"
    and "ls -a" or a combination of them
Command Parameters:
    Main accepts a Directory followed by any number of available switches
    in any order.
    Current available swithes:
    	-a : shows hidden files within the directory
    	-l : shows information about the file.
    		 (Name, type, # blocks, size in bytes)
Input:
    Directory name and switches
Results:
    Outputs a list of files/directories/pipes/links within the passed
    parent directory. Output changes depending on which switches are 
    passed. A -a switch will list non-hidden and hidden files. A -l 
    switch will list information about the file (Name, type, # blocks, 
    size in bytes). The user may combine switches. Files within a directory
    will be indented 4 spaces before being printed.
Returns:
    0 : Program executed successfully
Notes:
    None
**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
void errExit(const char szFmt[], ...);
char *fileType(struct stat *x);

int main(int argc, char *argv[]) {
	DIR *pDir; 						// Parent directory pointer
	struct dirent *pDirent;			// Structure of parent directory
	int iHiddenFile;				// Hidden file indicator
	char *cFileFirstChar;			// First character of file name
	bool bHidden = false;			// -a switch indicator
	bool bExtendedInfo = false;		// -l switch indicator
	struct stat statBuf;	
	char *szFullFileNm[500];		// Current file name with parent directory

	/* Open passed directory */
	pDir = opendir(argv[1]);

	/* Checks to make sure passed directory exists */

	if(pDir==NULL) 
	{
		errExit("opendir could not open '%s': %s", argv[1], strerror(errno));
	}

	/* Determine which switches were passed to main */

	int i;
	for(i = 0; i < argc; ++i) 
	{
		if((strcmp(argv[i], "-l")) == 0) {			
			/* -l was passed */
			bExtendedInfo = true;
		}
		if((strcmp(argv[i], "-a")) == 0) {	
			/* -a was passed */
			bHidden = true; 
		}
	}

	/* Print primary parent directory */
	printf("%s :\n", argv[1]);

	/* Check every file within parent directory */

	while((pDirent = readdir(pDir)) != NULL) 
	{
		/* Extract first character of current file */
		cFileFirstChar = pDirent->d_name[0];

		/* Check if current file begins with "." (hidden) */
		iHiddenFile = strcmp(&cFileFirstChar, ".");

		/* Create file name in format "directory/file" */
		snprintf(szFullFileNm, 500, "%s/%s", argv[1],pDirent->d_name);

		/* puts stats from current file into stat buffer */
		stat(szFullFileNm, &statBuf);

		/* -a and -l switches passed */
		if(bHidden == 1 && bExtendedInfo == 1) 
		{
			printf("    %s %s %ld blks %ld bytes\n", pDirent->d_name, fileType(&statBuf),
				   statBuf.st_blocks, statBuf.st_size);
		}

		/* -a switch passed */
		else if(bHidden == 1 && bExtendedInfo == 0) 
		{
			printf("    %s\n", pDirent->d_name);
		}

		/* -l switch passed */
		else if(bHidden == 0 && bExtendedInfo == 1) 
		{
			/* Skip printing hidden files */
			if(iHiddenFile !=0) 
			{
				printf("    %s %s %ld blks %ld bytes\n", pDirent->d_name, fileType(&statBuf),
				       statBuf.st_blocks, statBuf.st_size);
			}
		}

		/* No switches passed */
		else {
			if(iHiddenFile != 0) 
			{
				printf("    %s\n", pDirent->d_name);
			}
		}
	}
	closedir(pDir);
	return 0;
}

/******************** fileType ********************************************
char *fileType(struct stat *x) 
Purpose:
    Determines the type of the current file and returns a character for
    output.
Parameters:
    I   struct stat *buffer		struct containing multiple stats of file.
    O   char *cType				Single character indicating type of file.
Notes:
    None.
Return value:
    D 	File is a directory
    F 	File is a regular file
    P 	File is a pipe
    L 	File is a link
**************************************************************************/

char *fileType(struct stat *buffer) {
	char *cType; // File type (F, D, P, L)

	/* If file is a directory */
	if(S_ISDIR(buffer->st_mode) == 1) 
	{
		cType = "D";
	}

	/* If file is a regular file */
	else if(S_ISREG(buffer->st_mode) == 1) 
	{
		cType = "F";
	}

	/* If file is a pipe */
	else if(S_ISFIFO(buffer->st_mode) == 1) 
	{
		cType = "P";
	}

	/* If file is a link */
	else if(S_ISLNK(buffer->st_mode) == 1) 
	{
		cType = "L";
	}
	
	return cType;
}

