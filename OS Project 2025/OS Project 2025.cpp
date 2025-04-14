//Here is where the os system begins its process of running
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "bootUp.h"
#include "auth.h"
#include "Process.h"
#include "schedule.h"
#include "Virtualmemoryr.h"
using namespace std;

int main()
{
    // Create Process objects with (PID, Arrival Time, Burst Time, Completion Time, Memory, I/O Operations)
    Process P1(1, 0, 10, 0, 256, { "Disk Read","Network IO" });
    Process P2(2, 3, 12, 0, 256);
    Process P3(3, 6, 15, 0, 512, { "load image.png","Save image.jpg" });
    Process P4(4, 9, 18, 0, 512);
    Process P5(5, 12, 21, 0, 128, { "Load video.mp4" });

    biosStart();  // Starts BIOS loading process
    int osChoice = bootLoader();  // Get user input for OS selection

    if (osChoice == 1) {
        windowsLoading();
        authenticateUser();

        // Store processes in a vector
        vector<Process> processes = { P1, P2, P3, P4, P5 };

        // Create the Scheduler object
        Scheduler scheduler(processes);

        // Choose a scheduling algorithm
        int schedulingChoice;
        cout << "Select Scheduling Algorithm: \n";
        cout << "1. First-Come, First-Served (FCFS)\n";
        cout << "2. Shortest Job First (Non-Preemptive)\n";
        cout << "3. Shortest Job First (Preemptive)\n";
        cout << "Enter choice: ";
        cin >> schedulingChoice;

        switch (schedulingChoice) {
        case 1:
            cout << "Running FCFS Scheduling...\n";
            scheduler.scheduleFCFS();
            break;
        case 2:
            cout << "Running SJF Non-Preemptive Scheduling...\n";
            scheduler.scheduleSJFNonPreemptive();
            break;
        case 3:
            cout << "Running SJF Preemptive Scheduling...\n";
            scheduler.scheduleSJFPreemptive();
            break;
        default:
            cout << "Invalid choice. Defaulting to FCFS.\n";
            scheduler.scheduleFCFS();
            break;
        }

        // Display the scheduling results
        scheduler.displayResults();
    }
    else {
        cout << "Entering Recovery Mode..." << endl;
    }

    return 0;
}
