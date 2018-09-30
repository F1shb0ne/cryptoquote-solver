#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>

#include "../dictionary.h"
#include "solver.h"

using namespace std;

mutex m;
bool Solver::Enabled = true;

bool Solver::isEnabled() {
    return Enabled;
}

void Solver::Disable() {
    m.lock();
    Enabled = false;
    m.unlock();
}

double Solver::Solve(int threadid, Quote &quote, LetterSet &letterSet) {
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
            break;
        }
    }

    // Solution found
    stringstream ss;
    ss << threadid;
    ss << ": ";
    for (string word : currentSolution) {
        ss << word;
        ss << " ";
    }
    ss << endl;
    cout << ss.str();

    return 0;
}
