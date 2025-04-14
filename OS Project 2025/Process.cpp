//proccess class is contained here

#include <iostream>
#include <vector>
#include <string>
#include "Process.h"
#include "Virtualmemoryr.h"
using namespace std;
//declaration of process class

Process::Process(int id, int arrival, int burst, int pri, int memory, vector<string> io_ops) {
	pid = id;
	arrival_time = arrival;
	burst_time = burst;
	priority = pri;
	state = "New";
	remaining_time = burst;
	waiting_time = 0;
	turnaround_time = 0;
	memory_required = memory;
	io_operations = io_ops;
	completion_time = 0;
	has_started = false;
	pageTable.resize(virtualPages);
}
//updates the state of the process
void Process::updateState(string nState) {
	state = nState;
	cout << "The New state of " << pid << " is " << nState << endl;
}

//updates the remaing time to find if the process still needs to run or if its finished running
void Process::execution(int time_slice, int current_time) {
	//updates the state right away to make sure the state reflects where the process should be
	if (state == "New") {
		updateState("Ready");
	}

	if (!has_started) {
		// Process starts execution for the first time
		waiting_time = current_time - arrival_time;
		has_started = true;
	}

	else if (state == "Ready") {  // If process was waiting before running
		waiting_time += current_time - (completion_time - remaining_time);
	}

	if (remaining_time > 0) {
		updateRemaining_time(time_slice);

		//if its less than or equal to zero that means the process should have been terminated
		if (remaining_time <= 0) {


			updateState("Terminated");
			updateTurnaround_Time(); //update turnaround time since process is completed
		}

		//if its above zero then the process is still running
		else {
			updateState("Running");
			cout << "Process " << pid << " is running the remaining time till execution is:" << remaining_time << "seconds" << endl;
		}

	}
}
//updates remaing time
void Process::updateRemaining_time(int time) {
	remaining_time -= time;
}
//updates turnaround time
void Process::updateTurnaround_Time() {

	turnaround_time = completion_time - arrival_time;
}

void Process::setCompletionTime(int time) {
	this->completion_time = time;
	updateTurnaround_Time();  // Turnaround time = Completion Time - Arrival Time
}

void Process::setTurnaroundTime(int turnaroundTime) {
	this->turnaround_time = turnaroundTime;
}

void Process::setWaitingTime(int waitingTime) {
	this->waiting_time = waitingTime;
}

int Process::getPhysicalAddress(int virtualAddress, std::vector<Page>& physicalMemory) {
	return VirtualMemory::virtualToPhysical(virtualAddress, pageTable, physicalMemory, this->pid);
}

//getters
int Process::getPID() const {
	return pid;
}

int Process::getArrivalTime() const {
	return arrival_time;
}

int Process::getBurstTime() const {
	return burst_time;
}

int Process::getPriority() const {
	return priority;
}

string Process::getState() const {
	return state;
}

int Process::getRemainingTime() const {
	return remaining_time;
}

int Process::getWaitingTime() const {
	return waiting_time;
}

int Process::getTurnaroundTime() const {
	return turnaround_time;
}

int Process::getMemoryRequired() const {
	return memory_required;
}

const vector <string>& Process::getIOOperations() const {
	return io_operations;
}

int Process::getCompletionTime() const {
	return completion_time;
}
