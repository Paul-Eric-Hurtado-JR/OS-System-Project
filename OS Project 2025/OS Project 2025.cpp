//Here is where the os system begins its process of running
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "bootUp.h"
#include "auth.h"

using namespace std;

int main()
{
    biosStart();                //starts the process of loading the bios
    int osChoice = bootLoader();    //calls the the bootloader function to get user input for which os they wanted

    if (osChoice == 1) {    //if oschoice equals 1 then windows is loaded
        windowsLoading();
        authenticateUser();
    }
    else {                  //else then recovery mode is entered
        cout << "Entering Recovery Mode..." << endl;
    }
    return 0;
}

