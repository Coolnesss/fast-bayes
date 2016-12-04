#ifndef STOPWORDS
#define STOPWORDS
#include <unordered_set>
#include <fstream>
#include <iostream>
using namespace std;

inline unordered_set<string> read_stopwords(const string filename) {
    ios_base::sync_with_stdio(0);

    unordered_set<string> stopwords;
    ifstream stream(filename);
    string word;

    while(getline(stream, word)) {
        stopwords.insert(word);
    }

    stream.close();
    return stopwords;
}

#endif
