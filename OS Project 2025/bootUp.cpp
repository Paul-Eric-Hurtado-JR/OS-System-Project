//cpp file that has all the boot up functions
#include <iostream>
#include <cstdlib>
#include <chrono> //allows for time manipulation
#include <thread> //allows for the sleep_for function

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//clears the screen
void clearScreen() {
	system("cls");
}

//delays the printing of text
void printDelay(const string& text, int dTime = 500) {
	cout << text << endl;
	sleep_for(milliseconds(dTime));
}

//Sets up the bios
void biosStart() {
	clearScreen();
	printDelay("Bios v1.01");
	printDelay("Copyright (C) 2025 All Rights Reserved.");
	printDelay("Initializing system");
	sleep_for(seconds(1));
	printDelay("Checking Memory");
	printDelay("Checking Hard Drives");
	printDelay("Press F12 to enter Bios");
	sleep_for(seconds(1));
}

//loads the whichever boot is selected
int bootLoader() {
	int choice;
	clearScreen();
	printDelay("[GRUB Bootloader]");
	printDelay("1. Start Windows 11");
	printDelay("2. Boot into Recovery Mode");

	cout << "Pick either 1 or 2" << endl;
	cin >> choice;

	return choice;
}

//loads the kernel
void kernelLoading() {
	clearScreen();
	printDelay("Loading Windows 11 Kernel...");
	printDelay("Initializing system drivers...");
	printDelay("Mounting file system...");
	printDelay("Detecting hardware...");
	printDelay("Starting network services...");
	printDelay("Enabling graphical interface...");
	sleep_for(seconds(1));
}

//if windows is selected this is loaded
void windowsLoading() {
	clearScreen();
	printDelay("Loading Windows 11...");
	printDelay("Checking file system...");
	printDelay("Loading drivers...");
	printDelay("Starting Windows services...");
	printDelay("Preparing login screen...");
	sleep_for(seconds(1));
}

