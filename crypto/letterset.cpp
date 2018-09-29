#include <iostream>
#include <sstream>
#include <ctime>
#include "letterset.h"

using namespace std;

LetterSet::LetterSet() {
    RandomEngine.seed((unsigned long)time(NULL));

    for (int i = 0; i < 26; ++i) {
        Letters.push_back('a' + (char)i);
    }
    Shuffle();
}

void LetterSet::Shuffle() {
    shuffle(begin(Letters), end(Letters), RandomEngine);
}

void LetterSet::DisplaySet() {
    for (int i = 0; i < 26; ++i) {
        cout << Letters[i];
    }
    cout << endl;
}

string LetterSet::Map(string word) {
    stringstream ss;

    for (char c : word) {
        ss << Letters[c - 'a'];
    }
    return ss.str();
}

void LetterSet::SetSeed(unsigned long seed) {
    RandomEngine.seed(seed);
}
