require 'benchmark'
require './bayes_classifier'

d = IO.read("../test/data/20ng-train-all-terms.txt")
training = d.split("\n").map{|x| x.split("\t")}

d = IO.read("../test/data/20ng-test-all-terms.txt")
test = d.split("\n").map{|x| x.split("\t")}

puts Benchmark.measure {
    b = BayesClassifier.new
    training.each do |t|
        b.observe(t[1], t.first)
    end
    test.each do |t|
        b.classify(t[1])
    end
}
