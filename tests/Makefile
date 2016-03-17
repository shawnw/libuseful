CXX=g++
CXXFLAGS=-g -std=c++14 -Og -I .. -W -Wall

all: tests

tests: range math sort wordcount

math: math.cc
	$(CXX) $(CXXFLAGS) -o math math.cc

range: range.cc
	$(CXX) $(CXXFLAGS) -o range range.cc
	
sort: sort.cc
	$(CXX) $(CXXFLAGS) -o sort sort.cc
	
split: split.cc
	$(CXX) $(CXXFLAGS) -o split split.cc
	
wordcount: wordcount.cc
	$(CXX) $(CXXFLAGS) -o wordcount wordcount.cc
	