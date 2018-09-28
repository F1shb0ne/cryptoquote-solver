#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class LetterSet {
    default_random_engine RandomEngine = std::default_random_engine {};

public:
    vector<char> Letters;

    LetterSet();
    void Shuffle();
    void DisplaySet();

    string Map(string);
    void SetSeed(unsigned long seed);

};
