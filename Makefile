CXX=g++
RM=rm -f

SRCS=hello_world.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
OUTFILE=hello_world.o
GCOV_CXX_FLAGS += -fprofile-arcs -ftest-coverage # flags necessary for gcov
TESTOUTFILES += *.gcda *.gcno

hello:
	$(CXX) $(GCOV_CXX_FLAGS) -o $(OUTFILE) $(SRCS)

test:
	# run test file
	./$(OUTFILE)
	# generate code coverage information
	./get_code_cov.sh

clean:
	$(RM) $(OUTFILE) $(TESTOUTFILES)
