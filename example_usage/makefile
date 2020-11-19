REPO_ROOT=$(shell pwd)/..
LIBRARY_PATH=${REPO_ROOT}/OffPiste/install/lib

compile_dependencies:
	@cd ..; ./config.sh -3pl -lib

run:
	@g++ -Wall example.cpp -o example -L${LIBRARY_PATH} -lOffPiste; LD_LIBRARY_PATH=${LIBRARY_PATH} ./example

clean:
	@rm ./example