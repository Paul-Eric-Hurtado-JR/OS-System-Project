#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Process {
private:
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    string state;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int memory_required;
    vector<string> io_operations;
    int completion_time;
    bool has_started;

public:
    Process(int id, int arrival, int burst, int pri = 0, int memory = 0, vector<string> io_ops = {});

    void updateState(string nState);
    void execution(int time_slice, int current_time);
    void updateRemaining_time(int time);
    void updateTurnaround_Time();
    void setCompletionTime(int time);
    void setTurnaroundTime(int turnaroundTime);
    void setWaitingTime(int waitingTime);

    // Getters
    int getPID() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;
    string getState() const;
    int getRemainingTime() const;
    int getWaitingTime() const;
    int getTurnaroundTime() const;
    int getMemoryRequired() const;
    const vector<string>& getIOOperations() const;
    int getCompletionTime() const;
};

#endif
