#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Quote {
private:

public:
    vector<string> WordList;

    Quote(string FileName);

    void DisplayQuote();
    string GetWordIndex(int index);

};
