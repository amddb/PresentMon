/*
Copyright 2017 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <map>
#include <mutex>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "CommandLine.hpp"
#include "..\PresentData\SwapChainData.hpp"

struct ProcessInfo {
    std::string mModuleName;
    std::map<uint64_t, SwapChainData> mChainMap;
	uint64_t mLastRefreshTicks; // GetTickCount64
	FILE *mOutputFile;          // Used if -multi_csv
	bool mTargetProcess;
};

struct FilePath {
    char mDrive[_MAX_DRIVE] = {};
    char mDirectory[_MAX_DIR] = {};
    char mName[_MAX_FNAME] = {};
    char mExt[_MAX_EXT] = {};
};

struct PresentMonData {
	char mCaptureTimeStr[18] = "";
    const CommandLineArgs *mArgs = nullptr;
    uint64_t mStartupQpcTime = 0;
    FilePath mOutputFilePath;
    FILE *mOutputFile = nullptr;
    std::map<uint32_t, ProcessInfo> mProcessMap;
	std::map<std::string, FILE* > mProcessOutputFiles;
    std::map<uint32_t, FILE*> mOutputFileMap; // for multi_csv option
    uint32_t mTerminationProcessCount = 0;
};

void EtwConsumingThread(const CommandLineArgs& args);

void PresentMon_Init(const CommandLineArgs& args, PresentMonData& data);
void PresentMon_Update(PresentMonData& data, std::vector<std::shared_ptr<PresentEvent>>& presents, uint64_t perfFreq);
void PresentMon_Shutdown(PresentMonData& data, bool log_corrupted);

bool EtwThreadsShouldQuit();
void PostStopRecording();
void PostQuitProcess();

