require 'benchmark'
require '../lib/fast_bayes/fast_bayes'
require 'classifier-reborn' # Install from rubygems

# Read newspaper data
# Data from http://ana.cachopo.org/datasets-for-single-label-text-categorization
d = IO.read("../ext/test/data/20ng-train-all-terms.txt")
training = d.split("\n").map{|x| x.split("\t")}

d = IO.read("../ext/test/data/20ng-test-all-terms.txt")
test = d.split("\n").map{|x| x.split("\t")}
test = test.shuffle

# Classify 1000 random test data
n = test.size


# FastBayes
puts Benchmark.measure {
  b = FastBayes.new
  # Train all the training samples
  training.each do |t|
      b.observe(t[1], t.first)
  end

  errors = 0

  # Classify random test data
  test.take(n).each do |t|
      errors = errors + 1 if b.classify(t[1]) != t.first
  end
  puts "Error rate #{(errors / (n*1.0))}"
}

# ClassifierReborn
puts Benchmark.measure {
  classifier =  ClassifierReborn::Bayes.new auto_categorize: true
  training.each do |t|
    classifier.train t.first, t[1]
  end

  errors = 0

  test.take(n).each do |t|
      errors = errors + 1 if classifier.classify(t[1]).downcase != t.first
  end
  puts "Error rate #{(errors / (n*1.0))}"
}
