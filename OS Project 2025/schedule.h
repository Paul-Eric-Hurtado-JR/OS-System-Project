#pragma once
#include <vector>
#include "Process.h"

using namespace std;

class Scheduler {
private:
    vector<Process> processes;  // List of processes

public:
    // Constructor
    Scheduler(std::vector<Process> procs);

    // Scheduling algorithms
    void scheduleFCFS();
    void scheduleSJFNonPreemptive();
    void scheduleSJFPreemptive();

    // Display results
    void displayResults();
};