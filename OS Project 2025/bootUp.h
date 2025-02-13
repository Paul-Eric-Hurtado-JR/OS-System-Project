//Used by main to get the all the boot up functions
#ifndef BOOTUP_H
#define BOOTUP_H
#include <iostream>

void clearScreen();
void printDelay(const std::string& text, int dTime = 500);
void biosStart();
int bootLoader();
void kernelLoading();
void windowsLoading();

#endif
