#include "bayes.h"
#include "../test/test_helper.h"
#include <iostream>

using namespace std;
typedef long long ll;

int main() {
    Bayes b;
    
    auto lol = read_data("test/data/20ng-train-all-terms.txt");

    for(auto a : lol) {
        b.observe(a.second, a.first);
    }

    cout << b.classify("make america great again") << endl;
}