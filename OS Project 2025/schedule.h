#pragma once
#include <vector>
#include "Process.h"
#include "Virtualmemoryr.h"
using namespace std;

class Scheduler {
private:
    vector<Process> processes;  // List of processes
    vector<Page> phyMemory;
public:
    // Constructor
    Scheduler(std::vector<Process> procs);

    // Scheduling algorithms
    void scheduleFCFS();
    void scheduleSJFNonPreemptive();
    void scheduleSJFPreemptive();

    void memoryAccess(Process& proc);

    // Display results
    void displayResults();
};