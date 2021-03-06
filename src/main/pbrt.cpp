
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


// main/pbrt.cpp*
#include "stdafx.h"
#include "api.h"
#include "probes.h"
#include "parser.h"
#include "parallel.h"

#ifdef PBRT_IS_WINDOWS
#include <tchar.h>
void enterBackgroundMode() {
	if(!SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS))
	{
		Warning("Failed to enter idle processing mode.");
		return;
	}

	Info("Enter idle processing mode.");
}

void exitBackgroundMode() {
	if(!SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS))
	{
		Warning("Failed to exit idle processing mode.");
		return;
	}

	Info("Exit idle processing mode.");
}
#endif

// main program
int main(int argc, char *argv[]) {
#ifdef PBRT_IS_WINDOWS
	_set_abort_behavior(0, _CALL_REPORTFAULT);
#endif

#ifndef NDEBUG
	// Wait for debugger to attach
	printf("Please attach debugger. Press Enter to continue...");
	getchar();
#endif
    Options options;
    vector<string> filenames;
    // Process command-line arguments
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--ncores")) options.nCores = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--outfile")) options.imageFile = argv[++i];
        else if (!strcmp(argv[i], "--quick")) options.quickRender = true;
        else if (!strcmp(argv[i], "--quiet")) options.quiet = true;
        else if (!strcmp(argv[i], "--verbose")) options.verbose = true;
        else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            printf("usage: pbrt [--ncores n] [--outfile filename] [--quick] [--quiet] "
                   "[--verbose] [--help] <filename.pbrt> ...\n");
            return 0;
        }
		else if (!strcmp(argv[i], "--foreground")) options.foreground = true;
        else filenames.push_back(argv[i]);
    }
#ifndef NDEBUG
	// Use single thread for debugging
	//options.nCores = 1;
	//Warning("Using 1 working thread for debugging sessions.");
#endif

    // Print welcome banner
    if (!options.quiet) {
        printf("pbrt version %s of %s at %s [Detected %d core(s)]\n",
               PBRT_VERSION, __DATE__, __TIME__, NumSystemCores());
        printf("Copyright (c)1998-2012 Matt Pharr and Greg Humphreys.\n");
        printf("The source code to pbrt (but *not* the book contents) is covered by the BSD License.\n");
        printf("See the file LICENSE.txt for the conditions of the license.\n");
        fflush(stdout);
    }
    pbrtInit(options);

#ifdef PBRT_IS_WINDOWS
	// Reduce impact to foreground processes
	if (!options.foreground)
		enterBackgroundMode();
	else
		Warning("Rendering as a foreground process. System performance might degrade.");
#endif
    // Process scene description
    PBRT_STARTED_PARSING();
    if (filenames.size() == 0) {
        // Parse scene from standard input
        ParseFile("-");
    } else {
        // Parse scene from input files
        for (u_int i = 0; i < filenames.size(); i++)
            if (!ParseFile(filenames[i]))
                Error("Couldn't open scene file \"%s\"", filenames[i].c_str());
    }

#ifdef PBRT_IS_WINDOWS
	if (!options.foreground)
		exitBackgroundMode();
#endif
    
    pbrtCleanup();
    return 0;
}


