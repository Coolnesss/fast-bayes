require 'mkmf-rice'

$CXXFLAGS += " -std=c++11 "
create_makefile('fast_bayes/fast_bayes')
