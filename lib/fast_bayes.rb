require "fast_bayes/version"
require 'fast-stemmer'
require "fast_bayes/fast_bayes"

class FastBayes

  # Stem all words, this is a lot slower (TODO this fast)
  def observe_better(data, label)
    newdata = ""
    data.split(" ").each do |i|
      newdata += (i.stem + " ")
    end
    observe(newdata, label)
  end

  # Stem all words, this is a lot slower (TODO this fast)
  def classify_better(data)
    newdata = ""
    data.split(" ").each do |i|
      newdata += (i.stem + " ")
    end
    classify(newdata)
  end

end
