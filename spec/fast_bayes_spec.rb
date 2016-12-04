require "spec_helper"

describe FastBayes do
  $r_error = 1
  $n_error = 1

  after(:all) do
    puts "Reuters dataset error was #{$r_error}"
    puts "Newspaper dataset error was #{$n_error}"
  end

  def read_data(filename)
     IO.read(filename).split("\n").map{|x| x.split("\t")}
  end

  def observe_and_classify(training, test)
    b = FastBayes.new
    training.each do |t|
        b.observe(t[1], t.first)
    end

    errors = 0
    n = 1000

    test.take(n).each do |t|
        errors = errors + 1 if b.classify(t[1]) != t.first
    end
    errors / (n*1.0)
  end

  it "has a version number" do
    expect(FastBayes::VERSION).not_to be nil
  end

  it "can call basic functionality in Ruby" do
    b = FastBayes.new
    b.observe "This is a good sentence", "good"
    b.observe "This is a bad sentence", "bad"
    expect(b.classify("good")).to eq "good"
  end



  it "can observe and classify the r8 dataset" do
    training = read_data("ext/test/data/r8-train-all-terms.txt")
    test = read_data("ext/test/data/r8-test-all-terms.txt")
    test = test.shuffle
    err_rate = observe_and_classify(training, test)
    $r_error = err_rate
    expect(err_rate).to be <= 0.3
  end

  it "can observe and classify the 20ng dataset" do
    training = read_data("ext/test/data/20ng-train-all-terms.txt")
    test = read_data("ext/test/data/20ng-test-all-terms.txt")
    test = test.shuffle

    err_rate = observe_and_classify(training, test)
    $n_error = err_rate
    expect(err_rate).to be <= 0.5
  end
end
