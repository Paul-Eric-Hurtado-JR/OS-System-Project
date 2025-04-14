#pragma once
#include <chrono>

using namespace std::chrono;

struct pageEntry {
	bool validBit = false; //sees if page is in physical memory
	int frameNumber = -1; //sees what frame number is mapped to the process only if its valid
	bool dirtyBit = false; //sees if page has been written to if for write back policies is being done
};

struct Page {
	bool valid = false;
	int pageNumber = -1;
	int processId = -1;
	bool dirtyBit = false;
	system_clock::time_point timestamp;
};