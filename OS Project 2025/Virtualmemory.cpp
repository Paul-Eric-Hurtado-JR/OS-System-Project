#include <iostream>
#include <vector>
#include <chrono>
#include "virtualMemoryr.h"
#include "Process.h"

using namespace std;

// Initialize physical memory frames
void initializePhysicalMemory(vector<Page>& physicalMemory, int numFrames) {
    physicalMemory.resize(numFrames);
    for (int i = 0; i < numFrames; ++i) {
        physicalMemory[i].valid = false;
        physicalMemory[i].dirtyBit = false;
        physicalMemory[i].timestamp = system_clock::now();
        physicalMemory[i].pageNumber = -1;
        physicalMemory[i].processId = -1;
    }
}

// Initialize page table entries for a process
void initializePageTable(vector<pageEntry>& pageTable, int numPages) {
    pageTable.resize(numPages);
    for (int i = 0; i < numPages; ++i) {
        pageTable[i].validBit = false;
        pageTable[i].dirtyBit = false;
        pageTable[i].frameNumber = -1;
    }
}

// Translate virtual address to physical address
int VirtualMemory::virtualToPhysical(int virtualAddress, std::vector<pageEntry>& pageTable, std::vector<Page>& physicalMemory, int processID) {
    int pageNumber = virtualAddress / pageSize;
    int offset = virtualAddress % pageSize;

    if (pageTable[pageNumber].validBit) {
        return pageTable[pageNumber].frameNumber * pageSize + offset;
    }
    else {
        handlePageFault(physicalMemory, pageTable, pageNumber, processID);
        return pageTable[pageNumber].frameNumber * pageSize + offset;
    }
}


// Mark a page as dirty
void modifyPage(int pageNumber, vector<pageEntry>& pageTable) {
    pageTable[pageNumber].dirtyBit = true;
    cout << "Page " << pageNumber << " marked dirty.\n";
}

void writeDirtyPagesBack(vector<pageEntry>& pageTable, vector<Page>& physicalMemory, int frameIndex) {
    int evictedPage = physicalMemory[frameIndex].pageNumber;
    if (physicalMemory[frameIndex].dirtyBit) {
        cout << "Evicted page " << evictedPage << " is dirty. Writing back to disk...\n";
    }
}

void VirtualMemory::replacePage(std::vector<Page>& physicalMemory, std::vector<pageEntry>& pageTable, int newPageNumber, int processID) {
    int oldestFrame = 0;
    auto oldestTimestamp = physicalMemory[0].timestamp;

    // Find the oldest frame based on timestamp
    for (int i = 1; i < physicalMemory.size(); ++i) {
        if (physicalMemory[i].timestamp < oldestTimestamp) {
            oldestTimestamp = physicalMemory[i].timestamp;
            oldestFrame = i;
        }
    }

    // Evicted page number
    int evictedPage = physicalMemory[oldestFrame].pageNumber;

    // Handle the evicted page (write back dirty pages if needed)
    writeDirtyPagesBack(pageTable, physicalMemory, oldestFrame);

    // Mark the evicted page as invalid
    pageTable[evictedPage].validBit = false;
    physicalMemory[oldestFrame].valid = false;

    // Load the new page into the frame
    pageTable[newPageNumber].validBit = true;
    pageTable[newPageNumber].frameNumber = oldestFrame;

    physicalMemory[oldestFrame].valid = true;
    physicalMemory[oldestFrame].dirtyBit = false;
    physicalMemory[oldestFrame].pageNumber = newPageNumber;
    physicalMemory[oldestFrame].timestamp = chrono::system_clock::now();

    // Output the replacement information
    cout << "Replaced page " << evictedPage << " with page " << newPageNumber << " in frame " << oldestFrame << ".\n";
}

int VirtualMemory::findFreeFrame(std::vector<Page>& physicalMemory) {
    for (int i = 0; i < physicalMemory.size(); ++i) {
        if (!physicalMemory[i].valid) {
            return i;
        }
    }
    return -1; // No free frame
}

void VirtualMemory::handlePageFault(std::vector<Page>& physicalMemory, std::vector<pageEntry>& pageTable, int pageNumber, int processID) {
    int frameIndex = findFreeFrame(physicalMemory);
    if (frameIndex == -1) {
        replacePage(physicalMemory, pageTable, pageNumber, processID);
    }
    else {
        // Load page into free frame and update page table
        physicalMemory[frameIndex].valid = true;
        physicalMemory[frameIndex].processId = processID;
        physicalMemory[frameIndex].pageNumber = pageNumber;

        pageTable[pageNumber].validBit = true;
        pageTable[pageNumber].frameNumber = frameIndex;
    }
}

// Print current page table
void printPageTable(const vector<pageEntry>& pageTable) {
    cout << "\nCurrent Page Table:\n";
    for (int i = 0; i < pageTable.size(); ++i) {
        cout << "Page " << i << ": Valid=" << pageTable[i].validBit
            << ", Dirty=" << pageTable[i].dirtyBit
            << ", Frame=" << pageTable[i].frameNumber << "\n";
    }
}