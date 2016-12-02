#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "bayes.h"

using namespace Rice;
// This is a dummy class that gets wrapped into a Ruby class

class FastBayes {
    private:
        Bayes b;

    public:

        FastBayes() {};

        void observe(string label, string data) {
            b.observe(label, data);
        }

        string classify(string data) {
            return b.classify(data);
        }
};


extern "C"

void Init_fast_bayes() {
    Data_Type<FastBayes> rb_cbayes =
    define_class<FastBayes>("FastBayes")
    .define_constructor(Constructor<FastBayes>())
    .define_method("observe", &FastBayes::observe)
    .define_method("classify", &FastBayes::classify);
}
