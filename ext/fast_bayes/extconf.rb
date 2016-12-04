require 'mkmf-rice'

$CXXFLAGS += " -std=c++11 "
$CXXFLAGS += " -Ofast "
$CXXFLAGS += " -g0 "
create_makefile('fast_bayes/fast_bayes')
