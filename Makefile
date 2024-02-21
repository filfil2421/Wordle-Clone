# Filip Maletic (250866829)
# CS 3307A Individual Assignment
# October 3, 2023
# This is the makefile for the wordle application to make building easy for the user.
# I just edited the provided makefile in the hello application to make it work in this case.

# You might need to adjust WT_BASE to wherever Wt was installed. /usr/local is the default.

CXX = g++
WT_BASE = /usr/local
CXXFLAGS = --std=c++14 -I$(WT_BASE)/include
LDFLAGS = -L$(WT_BASE)/lib -Wl,-rpath,$(WT_BASE)/lib -lwthttp -lwt -lboost_thread -lboost_atomic -lboost_filesystem

# Identifies my code base to be building. Headers are listed under DEPS, and objects under OBJS.

DEPS = WordleApplication.h
OBJS = main.o WordleApplication.o

# How do we build objects?

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# How do we build the executable?

wordle: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# How do we clean up after ourselves?

clean:
	rm -f wordle $(OBJS)