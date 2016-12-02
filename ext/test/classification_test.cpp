#define CATCH_CONFIG_MAIN

#include <fstream> 
#include <iostream>
#include "catch.hpp"
#include "../src/bayes.h"
#include "test_helper.h"
#include <algorithm>
#include <chrono>

using namespace std;

TEST_CASE( "Gives a legitimate binary classification" ) {
    Bayes b;
    
    b.observe("Best sentence ever!", "Good");
    b.observe("I love school!", "Good");
    b.observe("good stuff guys", "Good");
    b.observe("bad guy", "Bad");

    REQUIRE(b.classify("this is a good sentence") == "Good");

}


TEST_CASE("Is able to classify big data") {
    Bayes b;

    auto training = read_data("test/data/20ng-train-all-terms.txt");
    auto test = read_data("test/data/20ng-test-all-terms.txt");

    auto start = std::chrono::high_resolution_clock::now();
    for(pair<string, string> label_data : training) {
        b.observe(label_data.second, label_data.first);
    }
    ll errors = 0;    
    int n = test.size();
    for(int i = 0; i < n; i++) {
        pair<string, string> label_data = test[i];

        string label = b.classify(label_data.second);
        if (label != label_data.first) errors++;
    } 

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end-start;
    cout << "Time " << diff.count() << endl;
    REQUIRE((errors / (1.0*n)) < 0.80);
}