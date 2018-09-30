#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <csignal>

#include "dictionary.h"
#include "quote.h"
#include "crypto/letterset.h"
#include "crypto/solver.h"

using namespace std;
typedef struct {
    Quote* quote;
    LetterSet* letterSet;
    int threadId;
    int numSolutions;
    string name;
} SolverArgs;

void* SolverThread(void* args) {
    Quote* quote = ((SolverArgs*)args)->quote;
    LetterSet* letterSet = ((SolverArgs*)args)->letterSet;
    string name = ((SolverArgs*)args)->name;
    int threadId = ((SolverArgs*)args)->threadId;
    
    while (Solver::isEnabled()) {
        Solver::Solve(*quote, *letterSet, name, threadId);
        letterSet->Shuffle();
    }
    pthread_exit(NULL);
}

void BreakHandler(int signal) {
    cerr << "Caught SIGINT: Aborting..." << endl;
    Solver::Disable();
}

int main(int argc, char** argv) {

    if (argc != 4) {
        cerr << "Usage:" << endl << argv[0] << " dictionary-file puzzle-file id" << endl;
        return -1;
    }

    // Get number of cores
    int numCores = (int)sysconf(_SC_NPROCESSORS_ONLN);
    cerr << "Detected " << numCores << " cores" << endl;

    // Init dictionary from first cli argument
    Dictionary::Init(argv[1]);

    // Load cryptoquote from second argument
    Quote quote(argv[2]);

    cerr << endl << "Solving for:" << endl;
    quote.DisplayQuote();

    Solver::Init();

    // Register break handler
    signal(SIGINT, BreakHandler);
    signal(SIGTERM, BreakHandler);

    // Create a thread group; one per core
    pthread_t* ThreadGroup = new pthread_t[numCores];

    // Create letter sets for each thread
    LetterSet* LetterSets = new LetterSet[numCores];    
    
    // Prepare argument struct and start each thread
    SolverArgs* solverArgs = new SolverArgs[numCores];
    for (int i = 0; i < numCores; ++i) {
        solverArgs[i].quote = &quote;
        solverArgs[i].letterSet = &LetterSets[i];
        solverArgs[i].threadId = i;
        solverArgs[i].numSolutions = 3;
        solverArgs[i].name = argv[3];
        int resp = pthread_create(&ThreadGroup[i], NULL, SolverThread, &solverArgs[i]);
        if (resp != 0) {
            cerr << "pthread_create() failed with " << resp << endl;
            delete[] ThreadGroup;
            delete[] LetterSets;
            return 1;
        }
    }

    // Wait for threads to finish
    void* result;
    for (int i = 0; i < numCores; ++i) {
        int resp = pthread_join(ThreadGroup[i], &result);
        if (resp != 0) {
            cerr << "pthread_join() failed with " << resp << endl;
        }
    }

    delete[] ThreadGroup;
    delete[] LetterSets;

    Solver::Destroy();
    pthread_exit(NULL);
    return 0;
}

