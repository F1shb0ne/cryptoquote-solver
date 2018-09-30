#pragma once

#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Dictionary {
private:
    static unsigned long TotalWordCount;
    static map<unsigned long, vector<string> > WordList;
public:
    static void Init(string wordlist);
    static string StripWord(string word);
    static bool ContainsWord(string word);
    static void DisplayWordsOfSize(int size);
    static void DisplayWordSizeHistogram();

};
