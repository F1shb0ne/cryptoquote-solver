#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "letterset.h"

using namespace std;


LetterSet::LetterSet() {
    for (int i = 0; i < 26; ++i) {
        Letters.push_back('a' + (char)i);
    }
}

void LetterSet::Shuffle() {
    random_shuffle(Letters.begin(), Letters.end());
}

void LetterSet::DisplaySet() {
    for (int i = 0; i < 26; ++i) {
        cout << Letters[i];
    }
    cout << endl;
}

string LetterSet::Map(string word) {
    stringstream ss;

    for (int i = 0; i < word.length(); ++i) {
        char c = word[i];
        ss << Letters[c - 'a'];
    }
    return ss.str();
}

void LetterSet::SetSeed(unsigned long seed) {
    Seed = seed;
    srand(Seed);
}

