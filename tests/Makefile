CXX=g++
CXXFLAGS=-g -std=c++11 -Og -I .. -W -Wall

all: tests

tests: range math

math: math.cc
	$(CXX) $(CXXFLAGS) -o math math.cc

range: range.cc
	$(CXX) $(CXXFLAGS) -o range range.cc
	