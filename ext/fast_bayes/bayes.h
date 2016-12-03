#ifndef bayes
#define bayes

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <limits>
#include <cmath>
#include <sstream>
#include "stopwords.h"

using namespace std;
typedef long long ll;

class Bayes {

    private:
        // For each label, the count of each word seen with that label
        map<string, unordered_map<string, ll>> word_counts;
        // amount of each label overall
        map<string, ll> priori_counts;
        // Total amount of observations recorded
        ll count = 0;
        // Total amounts of each term
        unordered_map<string, ll> term_counts;
        // Use english by default, TODO add option to use different ones
        string default_stopwords = "ext/fast_bayes/stopwords/en";
        unordered_set<string> stopwords;

        double smoothing = 0.00000000000001;

        double estimate_priori(string label) {
            return (priori_counts[label] / (double) count);
        }

        // Occurences of term in class divided by sum of all occurences of term
        double estimate_term(string term, string label) {
            return (word_counts[label][term] + smoothing) / ((smoothing * term_counts.size()) + term_counts[term]);
        }

        vector<string> tokenize_string(string data) {
            vector<string> v;
            string buf;
            stringstream ss(data);
            while(ss >> buf) v.push_back(buf);
            return v;
        }

    public:
        Bayes() {
            stopwords = read_stopwords(default_stopwords);
        }

        // Add a new observation
        void observe(string data, string label) {
            priori_counts[label]++;
            count++;
            for(string term : tokenize_string(data)) {
                if (stopwords.count(term)) continue;
                word_counts[label][term]++;
                term_counts[term]++;
            }
        }

        string classify(string data) {
            string best_class;
            double best_score = -numeric_limits<double>::infinity();

            for(auto label_pair : priori_counts) {
                string label = label_pair.first;

                // Score for a single label given the data
                double score = log(estimate_priori(label));
                vector<string> terms = tokenize_string(data);
                for(string term : terms) {
                    score += log(estimate_term(term, label));
                }

                if (score >= best_score) {
                    best_score = score;
                    best_class = label;
                }
            }
            return best_class;
        }
};

#endif
