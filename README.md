# FastBayes

A fast implementation of the naive Bayes classification algorithm. Written in C++ with an interface for Ruby using [Rice](https://github.com/jasonroelofs/rice).

Performs text classification with no separate training step needed, the cost of training is split between classification and observation. This is especially useful when data is an online stream, as the system can gradually improve.

FastBayes supports any number of classes and they don't need to be added in advance.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'fast_bayes'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install fast_bayes

## Usage

```ruby
[1] pry(main)> require 'fast_bayes'
=> true
[2] pry(main)> b = FastBayes.new
=> #<FastBayes:0x00000002cb5d98>
[3] pry(main)> b.observe "This sentence is good", "Good"
=> nil
[4] pry(main)> b.observe "This sentence is bad", "Bad"
=> nil
[5] pry(main)> b.classify "good stuff"
=> "Good"
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/Coolnesss/fast-bayes.


## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
