/**********************************************************************
cs3423p8.c by Bryan Burkhardt
Purpose:	
    This file contains the functions for conc and pipe
Command Parameters:
    N/A
Input:
    Input consists of a command followed by arguments with multiple
    commands separated by commas.
    	Example: 
    	conc cmd1 args1, cmd2 args2, ..., cmdi argsi
    Constraints:
    	conc - max of 5 commands
    	pipe - max of 2 commands
Results:
    Results are based on user input, for this assignment, it's primarily
    redirecting output to a file.
Returns:
    0: Program executed successfully
**********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "cs3423p8.h"

int concCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt) { 

	// For loop to ensure fork executes for each command.
	int i;
	for (i = 0; i < iCmdCnt; i++) {

		long lForkPid;			// fork process ID
		long lWaitPid;			// wait process ID
		int iExitStatus;		// Exit Status
		char *arguments[100];	// Stores argument values for commands
		int iInFileRedirect;	// Input file descriptor
		int iOutFileRedirect;	// Output file descriptor

		// Execute first fork
		lForkPid = fork();
		switch(lForkPid)
		{
			case -1:
			// fork failed.
				errExit("fork failed: %s", strerror(errno));
				break;
			
			case 0:
			// Child process

				/* Check for redirect */

				// stdout redirect is true
				if(cmdM[i].iStdoutRedirectIdx != 0) {
					// Set output file descriptor
					iOutFileRedirect = open(tokenM[cmdM[i].iStdoutRedirectIdx], O_WRONLY|O_CREAT|O_EXCL, 0777);
					if(iOutFileRedirect < 0) {
						errExit("Open file failed: %s", strerror(errno));
					}
					// Redirect output file descriptor
					else {
						dup2(iOutFileRedirect, STDOUT_FILENO);
						close(iOutFileRedirect);
					}
				}
				// stdin redirect is true
				if(cmdM[i].iStdinRedirectIdx != 0) {
					// Set input file descriptor
					iInFileRedirect = open(tokenM[cmdM[i].iStdinRedirectIdx], O_RDONLY, 0444);
					if(iInFileRedirect < 0) {
						errExit("Open file failed: %s", strerror(errno));
					}
					// Redirect input file descriptor
					else {
						dup2(iInFileRedirect, STDIN_FILENO);
						close(iInFileRedirect);
					}
				}
				
				/* Exec */
				// Iterate through arguments
				int iArgIdx = 1; // index counter for arguments array
				int j;
				// Set index 0 to the command being called
				arguments[0] = cmdM[i].szCmdNm;
				// Obtain arguments for command
				for(j = cmdM[i].iBeginIdx; j <= cmdM[i].iEndIdx; ++j) {
					arguments[iArgIdx] = tokenM[j];
					iArgIdx++;
				}
				arguments[iArgIdx] = NULL; // For execvp call
				// Call execvp
				execvp(cmdM[i].szCmdNm, arguments);
			
			default:
			// Parent process
				lWaitPid = wait(&iExitStatus);
				if(lWaitPid == -1) {
					errExit("wait error: %s", strerror(errno));
				}
				// Produce output for stderr. Output produced as follows:
				//		ParentID ChildID: command arguments
            	iArgIdx = 1; // Reset arguments counter to 1
            	int k;
            	fprintf(stderr, "%ld %ld: %s ", (long) getpid(), lForkPid, cmdM[i].szCmdNm);
            	for(k = cmdM[i].iBeginIdx; k <= cmdM[i].iEndIdx; ++k) {
            		arguments[iArgIdx] = tokenM[k];
            		fprintf(stderr, "%s ", arguments[iArgIdx]);
            		iArgIdx++;
            	}
            	fprintf(stderr, "\n");
            	fflush(stderr); // Output stderr to console
		}
	}
	return 0;
}




int pipeCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt){ 
	long lForkPidOne; 		// First fork ID
	long lForkPidTwo;		// Second fork ID
    int iExitStatus = 0;    // Used by parent to get status of child
    long lWaitPid;          // PID of child that terminated
    int fdM[2];             // contains file descriptors for the pipe
    char *arguments[100];	// Stores argument values for command 1
    char *arguments2[100];	// Stores argument values for command 2
    int iInFileRedirect;	// Input file descriptor
	int iOutFileRedirect;	// Output file descriptor
    
    // create the pipe
    if (pipe(fdM) == -1)
        errExit("pipe not created: %s", strerror(errno));
    
    // Execute first fork
    lForkPidOne = fork();
    int iTempfd0 = fdM[0];	// Read file descriptor for child 1
	int iTempfd1 = fdM[1]; 	// Write file descriptor for child 1
    switch(lForkPidOne) {
        case -1:
        // fork failed
            errExit("fork failed: %s", strerror(errno));
        
        case 0:  
        // child process
        	// stdin redirect is true
        	if(cmdM[0].iStdinRedirectIdx != 0) {
        		// Set input file descriptor
				iInFileRedirect = open(tokenM[cmdM[0].iStdinRedirectIdx], O_RDONLY, 0444);
				if(iInFileRedirect < 0) {
					errExit("Open file failed1: %s", strerror(errno));
				}
				// Redirect input file descriptor
				if(dup2(iInFileRedirect, STDIN_FILENO) < 0) {
					errExit("stdin redirect failed: %s", strerror(errno));
					
				}
			}
			// Redirect write file descriptor for child 1
			if(dup2(iTempfd1, STDOUT_FILENO) == -1) {
				errExit("Failed to redirect stdout: %s", strerror(errno));
			}
			// close read and write file descriptors for child 1
            close(iTempfd0); 
            close(iTempfd1);

            /* exec */
            // Iterate through arguments
            int iArgIdx = 1; // index counter for arguments array
			int j;
			// Set index 0 to called command
			arguments[0] = cmdM[0].szCmdNm;
			for(j = cmdM[0].iBeginIdx; j <= cmdM[0].iEndIdx; ++j) {
				arguments[iArgIdx] = tokenM[j];
				iArgIdx++;
			}
			arguments[iArgIdx] = NULL; // For execvp
			
			// Call execvp
            execvp(cmdM[0].szCmdNm, arguments);

        default: 
        // parent process
            // create the child 2
            lForkPidTwo = fork();
            switch(lForkPidTwo) {
                case -1:
                // fork failed
                    errExit("fork of second child failed: %s", strerror(errno));
                case 0:
                // Child process
                	// stdout redirect is true
                    if(cmdM[1].iStdoutRedirectIdx != 0) {
                    	// Set output file descriptor
						iOutFileRedirect = open(tokenM[cmdM[1].iStdoutRedirectIdx], O_WRONLY|O_CREAT|O_EXCL, 0777);
						if(iOutFileRedirect < 0) {
							errExit("Open file failed2: %s", strerror(errno));
						}
						// Redirect output file descriptor
						if(dup2(iOutFileRedirect, STDOUT_FILENO) < 0) {
							errExit("stdout redirect failed: %s", strerror(errno));
						}
					}
					// Redirect read file descriptor	
					if ( dup2(fdM[0], STDIN_FILENO) == -1) {
                        errExit("Failed to rediect stdin: %s", strerror(errno));
					}
					// close read and write file descriptors
                    close(fdM[0]);
                    close(fdM[1]);

                    /* exec */
                    // Itterate through arguments	
					int iArgIdx2 = 1; // Index counter for arguments2 array
					int k;
					// Set index 0 to called command
					arguments2[0] = cmdM[1].szCmdNm;
					for(k = cmdM[1].iBeginIdx; k <= cmdM[1].iEndIdx; ++k) {
						arguments2[iArgIdx2] = tokenM[k];
						iArgIdx2++;
					}
					arguments2[iArgIdx2] = NULL; // For execvp

					// Call execvp
                    execvp(cmdM[1].szCmdNm, arguments2);

                default:  
                // parent process
                	// Close read and write file descriptors
                    close(fdM[0]); 
                    close(fdM[1]);
                    
                    /* Print output to stderr */
					// Child 1
                    fprintf(stderr, "%ld %ld: %s ", (long) getpid(), (long) lForkPidOne, cmdM[0].szCmdNm);
                    int idx = 1;
                    int one;
                    for(one = cmdM[0].iBeginIdx; one <= cmdM[0].iEndIdx; ++one) {
                    	fprintf(stderr, "%s ", tokenM[one]);
                    }
                    fprintf(stderr, "\n");
                    // Child 2
                    fprintf(stderr, "%ld %ld: %s ", (long) getpid(), (long) lForkPidTwo, cmdM[1].szCmdNm);
                    idx = 1;
                    int two;
                    for(two = cmdM[1].iBeginIdx; two <= cmdM[1].iEndIdx; ++two) {
                    	fprintf(stderr, "%s ", tokenM[two]);
                    }
                    fprintf(stderr, "\n");
                    
                    fflush(stderr); // Output stderr to console

                    // Close input and output file descriptors
                    close(iInFileRedirect); 
                    close(iOutFileRedirect);
                    lWaitPid = wait (&iExitStatus);
            }
    }
    return 0;
}


