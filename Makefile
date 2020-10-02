CXX=g++
RM=rm -f

SRCS=hello_world.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
OUTFILE=hello_world.o
GCOV_CXX_FLAGS += -fprofile-arcs -ftest-coverage # flags necssary for gcov

hello:
	$(CXX) $(GCOV_CXX_FLAGS) -o $(OUTFILE) $(SRCS)

clean:
	$(RM) $(OUTFILE)
