CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCDIR = src

main: child $(SRCDIR)/main.cpp $(SRCDIR)/isPipeEmpty.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/main.cpp $(SRCDIR)/isPipeEmpty.cpp -o main
child: $(SRCDIR)/child.cpp 
	$(CXX) $(CXXFLAGS) $(SRCDIR)/child.cpp -o child