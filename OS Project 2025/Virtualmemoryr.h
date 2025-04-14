#pragma once
#include <chrono>
#include "Process.h"
#include <vector>
#include "memoryStructs.h"

class VirtualMemory {
public:
	static int findFreeFrame(vector<Page>& physicalMemory);
	static void replacePage(vector<Page>& physicalMemory, vector<pageEntry>& pageTable, int newPageNumber, int processID);
	static void handlePageFault(vector<Page>& physicalMemory, vector<pageEntry>& pageTable, int pageNumber, int processID);
	static int virtualToPhysical(int virtualAddress, vector<pageEntry>& pageTable, vector<Page>& physicalMemory, int processID);
};



const int pageSize = 4096; //the size of each page
//2^16
const int virtualMemorySize = 65536; //size each proces thinks it has
//2^15 give 32 since that is max
const int physicalMemorySize = 32768; //how much each process actually has
const int virtualPages = virtualMemorySize / pageSize;
const int physicaPages = physicalMemorySize / pageSize;

void initializePhysicalMemory(std::vector<Page>&, int);
void initializePageTable(std::vector<pageEntry>&, int);
void modifyPage(int, std::vector<pageEntry>&);
void writeDirtyPagesBack(std::vector<pageEntry>&, std::vector<Page>&, int);
void printPageTable(const std::vector<pageEntry>&);