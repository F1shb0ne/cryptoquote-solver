#include <iostream>
#include <thread>
#include "dictionary.h"
#include "crypto/letterset.h"
#include "quote.h"
#include "crypto/solver.h"

using namespace std;

int numCores = thread::hardware_concurrency();
default_random_engine RandomEngine = std::default_random_engine {};
int solutionsPerThread = 0;

void SolverThread(int threadid, Quote* quote, LetterSet* letterSet) {

    int increment = 0;
    int iter = 1;

    if (solutionsPerThread > 0) {
        increment = 1;
        iter = solutionsPerThread;
    }
    for (int i = 0; i < iter; i += increment) {
        Solver::Solve(threadid, *quote, *letterSet);
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

    solutionsPerThread = std::stoi(argv[3]);

    Dictionary::Init(argv[1]);

    Quote quote(argv[2]);
    cout << endl << "Solving for:" << endl;
    quote.DisplayQuote();

    LetterSet letterSets[numCores];
    thread ThreadGroup[numCores];

    // spin off a thread per core
    for (int i = 0; i < numCores; ++i) {
        letterSets[i].SetSeed((unsigned long)rand());
        ThreadGroup[i] = thread(SolverThread, i, &quote, &letterSets[i]);
    }

    // join
    for (int i = 0; i < numCores; ++i) {
        ThreadGroup[i].join();
    }

    return 0;
}
