REPO_ROOT=$(shell pwd)/..
LIBRARY_PATH=${REPO_ROOT}/OffPiste/install/lib
CXX_FLAGS=--std=c++14 # require c++14 or higher

compile_dependencies:
	@cd ..; ./config.sh -lib -testsOFF

run:
	@g++ ${CXX_FLAGS} -Wall example.cpp -o example.o -L${LIBRARY_PATH} -lOffPiste; LD_LIBRARY_PATH=${LIBRARY_PATH} ./example.o

clean:
	# Remove binaries
	@rm -f ./example.o
	# Remove compiled OffPiste Library
	@cd ..; ./config.sh -clean
