#include "schedule.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Constructor
Scheduler::Scheduler(vector<Process> procs) {
    processes = procs;
    phyMemory.resize(200);
}

// FCFS Scheduling
void Scheduler::scheduleFCFS() {
    int current_time = 0;

    for (auto& p : processes) {
        if (current_time < p.getArrivalTime()) {
            current_time = p.getArrivalTime();  // CPU stays idle until the process arrives
        }

        // Run the process for its full burst time
        p.execution(p.getBurstTime(), current_time);

        memoryAccess(p);

        // Set completion time (Scheduler's job)
        current_time += p.getBurstTime();
        p.setCompletionTime(current_time);

        int turnaround_time = current_time - p.getArrivalTime();
        p.setTurnaroundTime(turnaround_time);

        int waiting_time = turnaround_time - p.getBurstTime();
        p.setWaitingTime(waiting_time);
    }
}

// SJF Non-Preemptive Scheduling
void Scheduler::scheduleSJFNonPreemptive() {
    int current_time = 0;
    vector<Process*> readyQueue;

    // Sort by arrival time first
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
        });

    size_t index = 0;
    while (index < processes.size() || !readyQueue.empty()) {
        // Add processes that have arrived to the ready queue
        while (index < processes.size() && processes[index].getArrivalTime() <= current_time) {
            readyQueue.push_back(&processes[index]);
            index++;
        }

        if (!readyQueue.empty()) {
            // Sort ready queue by burst time (SJF rule)
            sort(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
                return a->getBurstTime() < b->getBurstTime();
                });

            // Pick shortest job and run it to completion
            Process* p = readyQueue.front();
            readyQueue.erase(readyQueue.begin());

            p->execution(p->getBurstTime(), current_time);
            current_time += p->getBurstTime();
            p->setCompletionTime(current_time);

            memoryAccess(*p);
        }
        else {
            // If no process is ready, CPU remains idle
            current_time++;
        }
    }
}
void Scheduler::scheduleSJFPreemptive() {
    int current_time = 0, completed = 0;
    int n = processes.size();
    vector<bool> isCompleted(n, false);  // Tracks if each process is done

    while (completed < n) {
        Process* shortest = nullptr;
        int shortestIndex = -1;

        // Find process with shortest remaining time that's arrived and not completed
        for (int i = 0; i < n; ++i) {
            if (!isCompleted[i] && processes[i].getArrivalTime() <= current_time) {
                if (!shortest || processes[i].getRemainingTime() < shortest->getRemainingTime()) {
                    shortest = &processes[i];
                    shortestIndex = i;
                }
            }
        }

        if (shortest) {
            shortest->execution(1, current_time);  // Run for 1 time unit (preemptive)
            current_time++;

            memoryAccess(*shortest);  // Translate virtual to physical memory

            if (shortest->getRemainingTime() <= 0) {
                shortest->setCompletionTime(current_time);
                isCompleted[shortestIndex] = true;
                completed++;
            }
        }
        else {
            // If no process is ready at current time, the CPU stays idle
            current_time++;
        }
    }
}
void Scheduler::memoryAccess(Process& proc) {
    int virtualAddr;
    int physicalAddr;
    for (int i = 0; i < proc.getBurstTime(); i++) {  // Using burst time to determine number of accesses
         virtualAddr = rand() % virtualMemorySize;  // Generate a random virtual address
        physicalAddr = proc.getPhysicalAddress(virtualAddr, phyMemory);  // Translate to physical address
    }
    cout << "Process " << proc.getPID() << ": Translated Virtual Address "
        << virtualAddr << " -> Physical Address " << physicalAddr << endl;
}

void Scheduler::displayResults() {
    cout << "\nProcess Execution Summary:\n";
    cout << left
        << setw(10) << "PID"
        << setw(10) << "Arrival"
        << setw(10) << "Burst"
        << setw(15) << "Completion"
        << setw(15) << "Turnaround"
        << setw(10) << "Waiting"
        << endl;

    int total_turnaround = 0;
    int total_waiting = 0;
    // Print each process' data
    for (auto& p : processes) {
        cout << setw(10) << p.getPID()
            << setw(10) << p.getArrivalTime()
            << setw(10) << p.getBurstTime()
            << setw(15) << p.getCompletionTime()
            << setw(15) << p.getTurnaroundTime()
            << setw(10) << p.getWaitingTime()
            << endl;

        total_turnaround += p.getTurnaroundTime();
        total_waiting += p.getWaitingTime();
    }

    double avg_turnaround = (double)total_turnaround / processes.size();
    double avg_waiting = (double)total_waiting / processes.size();

    // Display averages
    cout << "\nAverage Turnaround Time: " << avg_turnaround << "\n";
    cout << "Average Waiting Time: " << avg_waiting << "\n";
}