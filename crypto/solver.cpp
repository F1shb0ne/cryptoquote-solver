#include <iostream>
#include <vector>

#include "../dictionary.h"
#include "solver.h"

using namespace std;

pthread_mutex_t Solver::mutex;

bool Solver::Enabled = true;

void Solver::Init() {
    pthread_mutex_init(&mutex, NULL);
}

void Solver::Destroy() {
    pthread_mutex_destroy(&mutex);
}

bool Solver::isEnabled() {
    return Enabled;
}

void Solver::Disable() {
    pthread_mutex_lock(&mutex);
    Enabled = false;
    pthread_mutex_unlock(&mutex);
}

double Solver::Solve(Quote &quote, LetterSet &letterSet, string name, int threadId) {

    int solvedWordIndex = 0;
    int totalWords = (int)quote.WordList.size();
    int largestWordsSolved = 0;

    vector<string> currentSolution;

    while (solvedWordIndex != totalWords) {
        string unscrambledWord = letterSet.Map(quote.GetWordIndex(solvedWordIndex));
        if (Dictionary::ContainsWord(unscrambledWord)) {
            currentSolution.push_back(unscrambledWord);
            ++solvedWordIndex;
        } else {
            if (solvedWordIndex > largestWordsSolved) {
                largestWordsSolved = solvedWordIndex;
            }
            letterSet.Shuffle();
            currentSolution.clear();
            solvedWordIndex = 0;
        }
        if (!Enabled) {
            return 0;
        }
    }

    // Solution found
    cout << "(" << name << "-" << threadId << "): ";
    for (vector<string>::const_iterator it = currentSolution.begin(); it != currentSolution.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
