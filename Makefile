# Make Setting
#
MAKEFILE = Makefile

# C++ Setting
#
CXX = g++
CXXFLAGS = -std=c++11

# Debug Setting
#
DBGFLG = -g -DDEBUG

# Project Setting
#
VERSION=1.0
DISTDIR=$(top)DNA_Hairpin_Structure-$(VERSION)
TAR = DNA_Hairpin
SRCS = Hairpin.cpp FASTA.cpp DNAArg.cpp main.cpp
OBJS = $(SRCS:%.cpp=%.o)

$(TAR) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(DBGFLG) $(CPPFLAGS) $^ -o $@

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(DBGFLG) $< -o $@

.PHONY: all clean dep

all: dep $(TAR)

clean :
	@echo "remove all"
	@rm -rf $(OBJS) $(TAR)
	@rm -rf *~

dep : $(MAKEFILE)
	@echo "make dependency"
	@gcc -MM $(SRCS) > depend

-include depend
# End of Makefile
