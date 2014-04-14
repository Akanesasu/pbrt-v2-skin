
/*
    pbrt source code Copyright(c) 1998-2012 Matt Pharr and Greg Humphreys.

    This file is part of pbrt.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PBRT_CORE_PROGRESSREPORTER_H
#define PBRT_CORE_PROGRESSREPORTER_H

// core/progressreporter.h*
#include "pbrt.h"

// IProgressReporter Interface
class IProgressReporter {
public:
    // IProgressReporter Public Methods
    virtual ~IProgressReporter() = 0;
	virtual void Update(int num = 1) {};
	virtual void Done() {};
};

// PseudoProgressReporter Interface
class PseudoProgressReporter : public IProgressReporter {
public:
	static IProgressReporter& GetInstance() { return instance; }
private:
	static PseudoProgressReporter instance;
};

// ProgressReporter Declarations
class ProgressReporter : public IProgressReporter {
public:
    // ProgressReporter Public Methods
    ProgressReporter(int totalWork, const string &title,
                     int barLength = -1);
    ~ProgressReporter();
    void Update(int num = 1) override;
    void Done() override;
private:
    // ProgressReporter Private Data
    const int totalWork;
    int workDone, plussesPrinted, totalPlusses;
    Timer *timer;
    FILE *outFile;
    char *buf, *curSpace;
    Mutex *mutex;
};


extern int TerminalWidth();

#endif // PBRT_CORE_PROGRESSREPORTER_H
