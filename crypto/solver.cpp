#include <iostream>
#include <vector>

#include "../dictionary.h"
#include "solver.h"

using namespace std;

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
                //cout << threadid << ": << " << "Largest words solved: " << largestWordsSolved << endl;
            }

            letterSet.Shuffle();
            currentSolution.clear();
            solvedWordIndex = 0;
        }
    }

    // Solution found
    cout << threadid << ": ";
    for (string word : currentSolution) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}
