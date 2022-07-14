
# Fill in the path to your Repl folder root
# default is the current directory; if you are in the repl folder, then no changes
# are needed for this path

REPL_PATH=./

# put in the source and executable file names
# multiple source files are separated by spaces
# Modify it to reflect your application's source files

SRCS = CxxTest.cpp

#
# executable name -- modify to your executable name
#
EXE  = CxxTest

#
# Everything below that should not have to change ever.
#

export CURLHOME=${REPL_PATH}/curl

export BRIDGES_CXXFLAGS=-I${REPL_PATH}/bridges-cxx-install/include -I${CURLHOME}/include/

export BRIDGES_LDFLAGS=-L${REPL_PATH}/bridges-cxx-install/lib -L${CURLHOME}/lib/

export BRIDGES_CXX=clang++
export BRIDGES_CC=clang++
export BRIDGES_LD=clang++

export LD_LIBRARY_PATH:=${CURLHOME}/lib:${LD_LIBRARY_PATH}


CXX=$(BRIDGES_CXX)
LD=$(BRIDGES_LD)
CC=$(BRIDGES_CC)

TARGET =  all 

OBJS = $(SRCS:.cpp=.o)

CXXFLAGS = -g  -std=c++14 $(BRIDGES_CXXFLAGS)

LDFLAGS = -g $(BRIDGES_LDFLAGS) -pthread
LIBS =  -lcurl -lbridges 

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(LDFLAGS) $(LIBS)

.SUFFIXES: .cpp

.cpp.o:  
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(EXE)
	./$(EXE)

run: $(EXE)
	./$(EXE)

	

clean:
	-rm $(OBJS)
	-rm $(EXE)

