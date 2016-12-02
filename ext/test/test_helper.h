#ifndef test_helper
#define test_helper

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


// Returns a vector of <label, data> pairs
vector<pair<string, string>> read_data(string filename) {
    ios_base::sync_with_stdio(0);

    vector<pair<string,string>> labeled_data;
    ifstream stream(filename);
    string stuff;

    while(getline(stream, stuff)) {
        string line = stuff.substr(0, stuff.find('\n'));
        string label = line.substr(0, line.find('	'));
        string data = line.substr(line.find('	'), line.size());
        labeled_data.push_back({label, data});
    }
    
    stream.close();
    return labeled_data;
}

#endif