require "spec_helper"

describe FastBayes do
  it "has a version number" do
    expect(FastBayes::VERSION).not_to be nil
  end

  it "can call basic functionality in Ruby" do
    b = FastBayes.new
    b.observe "This is a good sentence", "good"
    b.observe "This is a bad sentence", "bad"
    expect(b.classify("good")).to eq "good"
  end

  it "can observe and classify a big amount of data" do
    d = IO.read("ext/test/data/20ng-train-all-terms.txt")
    training = d.split("\n").map{|x| x.split("\t")}

    d = IO.read("ext/test/data/20ng-test-all-terms.txt")
    test = d.split("\n").map{|x| x.split("\t")}
    test = test.shuffle

    b = FastBayes.new
    training.each do |t|
        b.observe(t[1], t.first)
    end

    errors = 0
    n = 1000

    test.take(n).each do |t|
        errors = errors + 1 if b.classify(t[1]) != t.first
    end

    expect((errors / n)).to be <= 0.7
  end
end
