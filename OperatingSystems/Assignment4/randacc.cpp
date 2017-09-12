// randacc.cpp
// Bryan Burkhardt
// 10 Apr 2017
// CS 321 - Assignment 4
// Program for random access file I/O using mmap
	
#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
using std::getline;
#include <cstddef>
using std::size_t;
#include <limits>		// std::numeric_limits
using std::numeric_limits;
using std::streamsize;
#include <algorithm>	// for all_of
using std::all_of;
#include <cctype>		// for isprint
#include <unistd.h>		// for _exit, write, close
#include <sys/mman.h>	// for mmap, munmap, related constants
#include <fcntl.h>		// for open, related constants
#include <sys/stat.h> 	// for stat, struct stat
#include <sys/types.h> 	// for off_t, ssize_t

// wait_exit
// Print blank line & prompt; wait for user to press ENTER; then exit
// 		with the given code.
void wait_exit(int code)
{
    if (code != 2) {
    cout << "\nPress ENTER to quit \n";
	}
    while (cin.get() != '\n') ;
    _exit(code);
}

// getFileSize
// Given pathname (relative or fully qualified) of file, attempt to
// 		determine file size. Returns size in bytes if successful. On error
// 		(e.g., file nonexistent or directory inaccessible), returns (-1).
off_t getFileSize(const string &fpath) {
	// Buffer for info returned by stat
	struct stat fileinfo;
	
    // Attempt to get file size
	int stat_failure = stat(fpath.c_str(), &fileinfo);
	
    // Error check for stat
	if (stat_failure) {
		// Error determining file size; return (-1).
		return -1;
	}

	// stat succeeded; return size
	return fileinfo.st_size;
}

// closeFile
// Attempt to close given file descriptor. Print messages. Exit on failure.
void closeFile(int fd) {
	int closeFailed = close(fd);
	if(closeFailed) {
		cout << "Unable to close file.\n";
		cout << "Terminating\n";
		wait_exit(1);
	}
}

// doesFileExist
// Takes fpath and returns true if file exists
bool doesFileExist(const string& fpath) {
  	struct stat fileinfo;  
	return ( stat(fpath.c_str(), &fileinfo) == 0 ); 
}

// createFile
// Takes file name and creates a .txt file of given name with 100 dots
void createFile(const string &fpath) {
    const size_t SIZE = 100;      // How much of file to map
    ssize_t dummy;                // For ignored return values
 
    cout << "Creating '" << fpath << "'\n";
    int fd = open(
        fpath.c_str(),        	// Filename
        O_RDWR | O_CREAT,
                                 	// What to do:
                                 	// - read & write access
                                 	// - create if no file
        0666);                   	// File permissions (octal):
                                 	// - user read & write
                                 	// - group read
                                 	// - other read

    // Error check for open
    if (fd == -1)
    {
        cout << "Unable to open " << fpath << "\n";
        wait_exit(1);
    }

    // Write initial contents of file
    for (size_t i = 0; i < SIZE; ++i)
    {
        dummy = write(fd, ".", 1);
    }
    dummy = write(fd, "\n", 1);

	closeFile(fd);
}

// readFile
// takes fpath and allows the user to read an index from 0-99
// 		calls initFile if file doesn't exist
void readFile(const string &fpath) {
	if(!doesFileExist(fpath)) {
		cout << "\n" << fpath << " does not exist.\n";
		createFile(fpath);
	}
	else {
		cout << fpath << " already exists.\n";
	}

	int fd = open(
		fpath.c_str(), 	// Filename
		O_RDONLY, 			// read only access
		0644);				// File permissions (octal):
                            // - user read & write
                            // - group read
                            // - other read
	if (fd == -1) {
		cout << "Unable to open " << fpath << "\n";
		cout << "Program terminating.\n";
		wait_exit(1);
	}
	cout << fpath << " opened.\n";

	int findIndex;
    do {
        std::cout << "What index would you like to read? (0-99)\n";
        while ( !(cin >> findIndex) ) { // while the input is invalid
            cin.clear(); // clear the fail bit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid entry
            cout << "Please enter a valid index. (0-99)\n";
        }
        if (findIndex < 0 || findIndex > 99) {
	        cout << "Invalid index\n";
        }
    } while (findIndex < 0 || findIndex > 99);

	void *addr = mmap(
		nullptr, 				// Requested address [no request]
		getFileSize(fpath), 	// How much memory (bytes)
		PROT_READ, 				// Access flags
		MAP_SHARED, 			// File & sharing flags
		fd, 					// File descriptor
		0);						// Byte offset in file

	if (addr == MAP_FAILED) {
		cout << "mmap failed.\n";
		closeFile(fd);
	}

	char *memoryMap = (char *)addr;
	cout << "The value at " << findIndex << " is " << memoryMap[findIndex] << "\n";

	// Unmap (free) the memory
    int munmap_failure = munmap(
        addr,      					// Address of mem (mmap return value)
        getFileSize(fpath));        // How much mem (must be correct!)

    // Error check for munmap
    if (munmap_failure) {
    	cout << "munmap failed.\n";
        closeFile(fd);
        wait_exit(1);
    }
	closeFile(fd);
}

// writeToFile
// Takes fpath and allows the user to write to an index between 0 and 99
// If file does not exists, writeToFile calls createFile.
void writeToFile(const string &fpath) {
	if(!doesFileExist(fpath)) {
		cout << "\n" << fpath << " does not exist.\n";
		createFile(fpath);
	}
	else {
		cout <<fpath << " already exists.\n";
	}

    const size_t SIZE = 100;
    ssize_t dummy;			// For ignored return values

    // Open the file
    int fd = open(
        fpath.c_str(),          // Filename
        O_RDWR,					// - read & write access
        0644);                  // File permissions (octal):
                                // - user read & write
                                // - group read
                                // - other read

    // Error check for open
    if (fd == -1)
    {
        cout << "Unable to open " << fpath << "\n";
		cout << "Program terminating.\n";
		wait_exit(1);
    }
    cout <<  fpath << " opened.\n";

    // Memory map the file
    void * addr = mmap(
        nullptr,                 // Requested address (no request)
        SIZE,                    // How much memory
        PROT_READ | PROT_WRITE,  // Access flags
        MAP_SHARED,              // File & sharing flags
        fd,                      // File descriptor
        0);                      // Byte offset in file

    // Error check for mmap
    if (addr == MAP_FAILED)
    {
        cout << "mmap FAILED.\n";
        closeFile(fd);
        wait_exit(1);
    }

    off_t findIndex;
    do {
        std::cout << "What index do you want to edit? (0-99)\n";
        while ( !(cin >> findIndex) ) { // while the input is invalid
            cin.clear(); // clear the fail bit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid entry
            cout << "Please enter a valid index. (0-99)\n";
        }
        if (findIndex < 0 || findIndex > 99) {
	        cout << "Invalid index\n";
        }
    } while (findIndex < 0 || findIndex > 99);

	while (cin.get() != '\n')
		;

    cout << "\nEnter a character to be written at index " << findIndex << "\n";
	string input;
	getline(cin, input);
	while( (!(::isprint(input[0]))) || (input.length() > 1) ) {
    	cout << "Please enter a character.\n";
    	getline(cin, input);
	}

	char data = input[0];
    // Mess with the memory
    char * writeArray = (char *)addr;
    writeArray[findIndex] = data;

	// Unmap (free) the memory
    int munmap_failure = munmap(
        addr,      					// Address of mem (mmap return value)
        SIZE);     					// How much mem (must be correct!)

    // Error check for munmap
    if (munmap_failure) {
    	cout << "munmap failed.\n";
        closeFile(fd);
        wait_exit(1);
    }
    cout << "Write successful\n";
	closeFile(fd);
}


int main()
{
	int choice = 0;
	do {
		string fpath;
		cout << "\n\nThis program lets you read or write to a chosen file.\n";
		cout << "Press ENTER to continue.\n\n";
		while (cin.get() != '\n');
		do {

			cout << "Please enter a file you would like to access\n";
			cout << "File must end in .txt\n";
			getline(cin, fpath);
			if ((!(all_of(fpath.begin(), fpath.end(), ::isgraph))) || 
			!(fpath.length() > 4 && fpath.substr( fpath.length() - 4 ) == ".txt" )) {
				cout << "Invalid filename!\n";
			}
		} while ( (!(all_of(fpath.begin(), fpath.end(), ::isgraph
			))) || 
			!(fpath.length() > 4 && fpath.substr( fpath.length() - 4 ) == ".txt" ) );
		cout << "\nWhat would you like to do?\n";
		cout << "(1) Read a record.\n";
		cout << "(2) Write to a record.\n";
		cout << "(3) Exit.\n";
		cout << "Please enter a choice.\n";
		while (!(cin >> choice)) {
   		cin.clear(); //clear bad input flag
    	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
    	cout << "Invalid choice, please try again.\n";
		}
		switch (choice) {
			case 1:
				readFile(fpath);
				break;

			case 2:
				writeToFile(fpath);
				break;

			case 3:
				wait_exit(2);
				break;

			default
			:
				cout << "Invalid choice, please try again.\n";
				break;
		}
	} while(choice != 3);

	wait_exit(0);
}