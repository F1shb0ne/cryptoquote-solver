#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include "dictionary.h"

using namespace std;

unsigned long Dictionary::TotalWordCount = 0;
map<unsigned long, vector<string>> Dictionary::WordList;

void Dictionary::Init(string wordlist) {
    stringstream ss;
    ifstream wordListFile(wordlist);
    string word;
    unsigned long wordLength;
    unsigned long rawWordCount = 0;
    map<unsigned long, set<string>> WordSet;

    cout << "Processing " << wordlist << "... ";
    while(getline(wordListFile, word)) {
        ++rawWordCount;
        string newWord = StripWord(word);
        wordLength = newWord.length();
        if (wordLength == 0) continue;

        if (WordSet.find(wordLength) == WordSet.end()) {
            WordSet[wordLength] = set<string>();
        }
        if (newWord.length() > 0) {
            WordSet[wordLength].insert(newWord);
        }
    }

    cout << rawWordCount << " entries." << endl;

    // Populate actual word list (get out of set collection to faster vector)
    cout << "Building dictionary... ";
    for (map<unsigned long, set<string>>::const_iterator it = WordSet.begin(); it != WordSet.end(); ++it) {
        unsigned long numWords = it->second.size();
        TotalWordCount += numWords;

        WordList[it->first] = vector<string>();
        for (string entry : it->second) {
            WordList[it->first].push_back(entry);
        }
    }
    cout << "Done." << endl << "Dictionary contains " << TotalWordCount << " unique words" << endl;
}

string Dictionary::StripWord(string word) {

    stringstream ss;

    for (char c : word) {
        c |= 32; // ensure lowercase
        if (c >= 'a' && c <= 'z') {
            ss << c;
        } else if (c == '\'') {
            continue;
        } else {
            return ss.str();
        }
    }
    return ss.str();
}

void Dictionary::DisplayWordsOfSize(int size) {

    int cols = 0;
    cout << endl;
    for (string word : WordList[(unsigned long)size]) {
        if (cols >= 230) {
            cout << endl;
            cols = 0;
        }
        cout << word << " ";
        cols += size + 1;
    }
    cout << endl;
}

void Dictionary::DisplayWordSizeHistogram() {
    for (map<unsigned long, vector<string>>::const_iterator it = WordList.begin(); it != WordList.end(); ++it) {
        unsigned long numWords = it->second.size();
        TotalWordCount += numWords;
        cout << "Length " << it->first << ": " << numWords << " words." << endl;
    }
}

bool Dictionary::ContainsWord(string word) {
    unsigned long wordsize = word.size();
    vector<string>& dict = WordList[wordsize];
    return find(dict.begin(), dict.end(), word) != dict.end();
}
