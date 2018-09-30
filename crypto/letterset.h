#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class LetterSet {
private:
    unsigned long Seed;

public:
    vector<char> Letters;

    LetterSet();
    LetterSet(unsigned long seed);
    void Shuffle();
    void DisplaySet();

    string Map(string);
    void SetSeed(unsigned long seed);

};
