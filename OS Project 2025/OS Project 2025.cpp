//Here is where the os system begins its process of running
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "bootUp.h"
#include "auth.h"
#include "Process.h"
using namespace std;

int main()
{
    Process P1(1, 0, 10, 0, 256,{ "Disk Read","Network IO" });
    Process P2(2, 3, 12, 0, 256);
    Process P3(3, 6, 15 ,0, 512,{ "load image.png","Save image.jpg" });
    Process P4(4, 9, 18, 0, 512);
    Process P5(5, 12, 21, 0, 128, { "Load video.mp4" });

    biosStart();                //starts the process of loading the bios
    int osChoice = bootLoader();    //calls the the bootloader function to get user input for which os they wanted

    if (osChoice == 1) {    //if oschoice equals 1 then windows is loaded
        windowsLoading();
        authenticateUser();  
        // Create a vector to hold all processes
        vector<Process*> processes = { &P1, &P2, &P3, &P4, &P5 };

        int currentTime = 0;
        const int timeSlice = 3; // Time slice for each process in seconds
        bool allFinished = false;

        // Loop until all processes are finished
        while (!allFinished) {
            allFinished = true; // Assume all processes are finished

            for (auto& process : processes) {
                if (process->getRemainingTime() > 0) {
                    allFinished = false; // At least one process is still running

                    // Execute the process for the time slice
                    process->execution(timeSlice, currentTime);
                    currentTime += timeSlice; // Increment current time
                }
            }

            // Optional: Print the current time after each full round
            cout << "Current time after round: " << currentTime << endl;

            // Add a sleep to simulate time passing (optional)
            this_thread::sleep_for(chrono::seconds(timeSlice));
        }

        cout << "All processes have completed." << endl;
    }
    else {                  //else then recovery mode is entered
        cout << "Entering Recovery Mode..." << endl;
    }



    return 0;
}

