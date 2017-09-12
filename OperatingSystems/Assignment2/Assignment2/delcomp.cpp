// delcomp.cpp
// Bryan Burkhardt
// 17 Feb 2017
// CS311 - Assignment 2
// Program that accepts integervalues from the user. Once input is complete, program uses threads to compute values. 
//		The values are sent back to the master thread and are output once available.

#include "sa2a.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <thread>
using std::thread;
#include <queue>
using std::queue;
#include <mutex>
using std::mutex;
#include <string>
using std::string;
#include <sstream>
using std::ostringstream;

const int NUMTHREADS = 6;
vector<bool> threadStatus(NUMTHREADS); // Vector that tracks status of threads. true == thread is available.
vector<thread> threads(NUMTHREADS);	   // Vector that holds the spawned threads.
queue<int> in;		 // Queue to hold input values from the user.
queue<string> out;	 // Queue to hold output values.
mutex main_mutex;    // Mutex that handles locking/unlocking within main.
mutex thread_mutex;  // Mutex that handles locking/unlocking within the threads.

// workerThread function
// Pre:
//		Thread must be available
// Post:
//		Computed sa2a value is pushed to the output queue as an output stream.
// Exception Neutral
// Strong guarantee
void workerThread(int value, int thread) {	
	int outputValue;
	outputValue = sa2a(value);
	ostringstream oss;
	oss << "sa2a(" << value << ") = " << outputValue << endl;
	
	thread_mutex.lock();
	out.push(oss.str());
	threadStatus[thread] = true;
	thread_mutex.unlock();
}

// isWorkComplete function
// Pre:
//		None.
// Post:
//		Returns true if all threads are finished working or false if threads are still in progress.
//		This function ensures we dont exit the program before all input values are computed.
// Exception Neutral
// No-Throw guarantee	
bool isWorkComplete() {
	for (int i = 0; i < threadStatus.size(); ++i)
		if (threadStatus[i] == false)
			return false;
	return true;
}

// Main 
int main() {
	
	// for loop to spawn our threads and set their status to available.
	for (auto i = 0; i < NUMTHREADS; ++i) {
		main_mutex.lock();
		threadStatus[i] = true;
		main_mutex.unlock();
	}

	// while loop for the input from the user. Loop adds integers values to the input queue
	//		until the user enters 0 to end input.
	int a = 1;
	while(a > 0)
	{
		cout << "Enter a positive integer (or 0 to end input): ";
		cin >> a;
		if(a==0)
			break;
		in.push(a);
	}
	
	// for loop that sends values from the input queue to the workerThread function.
	for (int i = 0; i < NUMTHREADS; ++i) {
		if (in.size() > 0) {
			main_mutex.lock();
			threadStatus[i] = false;
			main_mutex.unlock();
			threads[i] = thread(workerThread, in.front(), i);
			main_mutex.lock();
			in.pop();
			main_mutex.unlock();
		}
	}
	
	// while loop that ensures all the work is complete before the program exits. This loop 
	//		takes care of outputting the computed values as they become available. It also 
	//		sends work to available threads.
	int size = in.size();
	while (size || out.size() > 0 || !isWorkComplete()) {
		if (out.size() != 0) {
			
				main_mutex.lock();
				cout << out.front();
				out.pop();
				main_mutex.unlock();
			
		}
		for (int i = 0; i < NUMTHREADS; ++i) {
			if (size) {
				if (threadStatus[i]) {
					threads[i].join();
					--size;
					thread_mutex.lock();
					threadStatus[i] = false;
					thread_mutex.unlock();
					threads[i] = thread(workerThread, in.front(), i);
					main_mutex.lock();
					in.pop();
					main_mutex.unlock();
				}
			}
		}
	}
	
	// Clean up for loop to make sure all threads are joined and work is complete.
	for(int i = 0; i < threads.size(); ++i) {
		if (threads[i].joinable()) {
			threads[i].join();
		}
	}
}