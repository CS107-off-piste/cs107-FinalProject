REPO_ROOT=$(shell pwd)/..
LIBRARY_PATH=${REPO_ROOT}/OffPiste/install/lib

compile_dependencies:
	@cd ..; ./config.sh -lib -testsOFF

run:
	@g++ -Wall example.cpp -o example.o -L${LIBRARY_PATH} -lOffPiste; LD_LIBRARY_PATH=${LIBRARY_PATH} ./example.o

clean:
	# Remove binaries
	@rm -f ./example.o
	# Remove compiled OffPiste Library
	@cd ..; ./config.sh -clean
