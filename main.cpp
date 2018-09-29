#include <iostream>
#include <string>
#include <thread>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <windows.h>
#else
#include <csignal>
#endif

#include "dictionary.h"
#include "crypto/letterset.h"
#include "quote.h"
#include "crypto/solver.h"

using namespace std;

int numCores = thread::hardware_concurrency();
default_random_engine RandomEngine = std::default_random_engine{};
int solutionsPerThread = 0;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
BOOL CtrlHandler(DWORD fdwCtrlType) {
    switch (fdwCtrlType) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
        cout << "Caught break: Aborting..." << endl;
        Solver::Disable();
        return TRUE;
        break;
    default:
        break;
    }
    return FALSE;
}
#else
void BreakHandler(int s) {
    cout << "Caught SIGINT: Aborting..." << endl;
    Solver::Disable();
}
#endif

void SolverThread(int threadid, Quote* quote, LetterSet* letterSet) {

    int increment = 0;
    int iter = 1;

    if (solutionsPerThread > 0) {
        increment = 1;
        iter = solutionsPerThread;
    }
    for (int i = 0; i < iter; i += increment) {
        Solver::Solve(threadid, *quote, *letterSet);
        if (!Solver::isEnabled()) break;
        letterSet->Shuffle();
    }
}

int main(int argc, char** argv) {
    RandomEngine.seed((unsigned long)time(NULL));
    cout << numCores << " cores detected." << endl;

    if (argc != 4) {
        cout << "Usage:" << endl << argv[0] << " dictionary-file puzzle-file #tries-per-thread" << endl;
        return -1;
    }

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE)) {
        cout << "Warning: Unable to register break handler" << endl;
    }
#else
    signal(SIGINT, BreakHandler);
    signal(SIGTERM, BreakHandler);
    signal(SIGBREAK, BreakHandler);
#endif
    solutionsPerThread = std::stoi(argv[3]);
    Dictionary::Init(argv[1]);
    Quote quote(argv[2]);
    cout << endl << "Solving for:" << endl;
    quote.DisplayQuote();

    LetterSet* letterSets = new LetterSet[numCores];
    thread* ThreadGroup = new thread[numCores];

    // spin off a thread per core
    for (int i = 0; i < numCores; ++i) {
        letterSets[i].SetSeed((unsigned long)rand());
        ThreadGroup[i] = thread(SolverThread, i, &quote, &letterSets[i]);
    }

    // join
    for (int i = 0; i < numCores; ++i) {
        ThreadGroup[i].join();
    }

    delete[] letterSets;
    delete[] ThreadGroup;

    return 0;
}
