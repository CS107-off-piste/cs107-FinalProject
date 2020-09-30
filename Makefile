CXX=g++
RM=rm -f

SRCS=hello.cc
OBJS=$(subst .cc,.o,$(SRCS))
OUTFILE=hello_world.o

hello:
	$(CXX) -o $(OUTFILE) hello_world.cpp

clean:
	$(RM) $(OUTFILE)
