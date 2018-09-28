#include <fstream>
#include <sstream>
#include "quote.h"

Quote::Quote(string FileName) {
    stringstream ss;

    fstream infile(FileName, fstream::in);

    while (infile.good()) {
        char c = (char)infile.get();
        c |= 32; // ensure lowercase
        if (c >= 'a' && c <= 'z') {
            ss << c;
        } else if (c == '\'') {
            // concatenate contractions
            continue;
        } else {
            // space or something else; break to new word
            string newWord = ss.str();
            ss.str("");
            if (newWord.length() > 0) {
                WordList.push_back(newWord);
            }
        }
    }

    // finish last word if present
    string newWord = ss.str();
    if (newWord.length() > 0) {
        WordList.push_back(newWord);
    }

}

void Quote::DisplayQuote() {

    for (string word : WordList) {
        cout << word << " ";
    }
    cout << endl;

}

string Quote::GetWordIndex(int index) {
    return WordList[index];
}
