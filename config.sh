#!/bin/bash -e

# ================== #
# compiling defaults
# ================== #
BUILD_3PL=0
BUILD_LIB=0
BUILD_TYPE=0
CLEAN_DIST=0
CLEAN=0
COVERAGE=0
DOCUMENTATION_GEN=0
FORMAT=0
# ============== #
# print strings
# ============== #
opt_str="[OPTION] "

eC="\x1B[0m"
bC="\x1B[0;34m"
GC="\x1B[1;32m"
yC="\x1B[0;33m"
aC="\x1B[0;96m"
rC="\x1B[0;41m"
gC="\x1B[0;32m"
oC="\x1B[3;93m"
mC="\x1B[0;43m"

logo() {
    echo    " _______  _______  _______  _______  ___   _______  _______  _______ "
    echo -e "|       ||       ||       ||       ||   | |       ||       ||       |"
    echo -e "|   _   ||    ___||    ___||    _  ||   | |  _____||_     _||    ___|"
    echo -e "|  | |  ||   |___ |   |___ |   |_| ||   | | |_____   |   |  |   |___ "
    echo -e "|  |_|  ||    ___||    ___||    ___||   | |_____  |  |   |  |    ___|"
    echo -e "|       ||   |    |   |    |   |    |   |  _____| |  |   |  |   |___ "
    echo -e "|_______||___|    |___|    |___|    |___| |_______|  |___|  |_______|"
    echo
    echo -e " ${GC} >>>>>>  Easy Build Option:   ./config.sh    <<<<<<${eC}"
    echo -e " ===================================================================="
}

help() {
    echo " "
    echo -e "${GC} Usage:${eC} $0 [OPTIONS]"
    echo " "
    echo -e " ${aC}Recommended Options:${eC}"
    echo -e "    Default: ${gC}./config.sh${eC}"
    echo -e "    Is equivalent to: ${gC}./config.sh -lib -3pl CC=gcc CXX=g++${eC}"
    echo " "
    echo -e " ${aC}Options List:${eC}"
    echo "  [OPTION]:"
    echo "    --3pl       -3pl    build the 3rd party libraries:  gtest"
    echo "    --library   -lib    build OffPiste"
    echo " "
    echo "    --help      -h      displays this help message"
    echo "    --clean     -c      removes local build directories"
    echo "    --distclean -dc     removes builds and install directories"
    echo "    --release   -opt    compile the project in optimized mode"
    echo "    --debug     -deb    compile the project in debug mode"
    echo "    --testsOFF  -toff   disable running tests after compilation (google tests)"
    echo "    --gen-docs  -docs   generate documentation using Doxygen"
    echo "    --format    -form   format source files in OffPiste/ using clang-format"
    echo "    --coverage  -cov    generate code coverage report for unit tests using lcov"
    echo "    --build_so  -so     compile the library into .so (rather than .dylib) on Mac"
    echo " "
    echo "  [COMPILER OPTIONS]:"
    echo "     CC=<arg>   cc=<arg>    sets the C compiler"
    echo "    CXX=<arg>  cxx=<arg>    sets the C++ compiler"
    echo " "
    echo "      C_FLAGS=<arg>    c_flags=<arg>    sets the C compiler flags"
    echo "    CXX_FLAGS=<arg>  cxx_flags=<arg>    sets the C++ compiler flags"
    echo " "
    echo "  [Intel Compiler Flags]:"
    echo "     --avx     -avx         sets Intel AVX Instructions"
    echo "     --avx2    -avx2        sets Intel AVX-2 Instructions"
    echo "     --avx512  -avx512      sets Intel AVX-512 Instructions"
    echo "     --mkl     -mkl         sets Intel MKL Library"
    echo " "
    echo "  [3PL OPTIONS]:"
    echo "    --ALL3P   -all3p  compile all 3rd party libraries"
    echo "    --GTEST   -gtest  compile google test"
    echo " "
}

# ============ #
# parse inputs
# ============ #

logo

for var in "$@"
do
  if [ "$var" == "--help" -o "$var" == "-help" -o "$var" == "-h" ]; then
    help
    exit 0

  elif [ "$var" == "--distclean" -o "$var" == "-distclean" -o "$var" == "-dc" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    echo ${opt_str} "Cleaning the distribution..."
    CLEAN_DIST=1

  elif [ "$var" == "--clean" -o "$var" == "-clean" -o "$var" == "-c" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    echo ${opt_str} "Cleaning ..."
    CLEAN=1

  elif [ "$var" == "--3pl" -o "$var" == "-3pl" -o "$var" == "-3pl" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    BUILD_3PL=1

  elif [ "$var" == "--GTEST" -o "$var" == "-gtest" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    BUILD_3PL=1

  elif [ "$var" == "--library" -o "$var" == "-lib" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    BUILD_LIB=1

  elif [ "$var" == "--release" -o "$var" == "-release" -o "$var" == "-opt" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    BUILD_TYPE=0

  elif [ "$var" == "--debug" -o "$var" == "-debug" -o "$var" == "-deb" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    BUILD_TYPE=1

  elif [ "$var" == "--coverage" -o "$var" == "-coverage" -o "$var" == "-cov" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    COVERAGE=1

  elif [ "$var" == "--gen-docs" -o "$var" == "-gen-docs" -o "$var" == "-docs" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    DOCUMENTATION_GEN=1

  elif [ "$var" == "--format" -o "$var" == "-form" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"
    FORMAT=1

  elif [ "$var" == "--clean" -o "$var" == "-clean" -o "$var" == "-c" -o \
         "$var" == "--testsOFF" -o "$var" == "-testsOFF" -o "$var" == "-toff" -o \
         "${var:0:3}" == "CC=" -o "${var:0:3}" == "cc=" -o \
         "${var:0:4}" == "CXX=" -o "${var:0:4}" == "cxx=" -o \
         "${var:0:8}" == "C_FLAGS=" -o "${var:0:8}" == "c_flags=" -o \
         "${var:0:10}" == "CXX_FLAGS=" -o "${var:0:10}" == "cxx_flags=" -o \
         "${var}" == "--avx" -o  "${var}" == "-avx" -o \
         "${var}" == "--avx2" -o  "${var}" == "-avx2" -o \
         "${var}" == "--avx512" -o  "${var}" == "-avx512" -o \
         "$var" == "--ALL3PL" -o "$var" == "--all3pl" -o "$var" == "-all3pl" -o \
         "$var" == "--GTEST" -o "$var" == "-gtest" -o \
         "$var" == "--coverage" -o "$var" == "-coverage" -o "$var" == "-cov" -o \
         "${var}" == "-go" ]; then
    echo -e "Found known argument: ${gC}$var${eC}"

  else
    echo -e "${oC}Unknown option:${eC}  ${rC}$var${eC}"
    echo "See available options: ./config.sh --help"

  fi
done

# ========================= #
# display command line args
# ========================= #
echo "$0 $@"
cmd_args="${@:1}"

# =================================================================== #
if [ $CLEAN_DIST == 1 ]; then
  rm -rf install
  CLEAN=1
  exit 0
fi

if [ $CLEAN == 1 ]; then
    rm -rf builds

    # clean up OffPiste sub-folder
    cd OffPiste
    ./config.sh --clean || exit 1
    cd ..
    exit 0
fi
# =================================================================== #

# =================================================================== #
if [ $BUILD_LIB == 0 -a $BUILD_3PL == 0 -a $COVERAGE == 0 -a $DOCUMENTATION_GEN == 0 -a $FORMAT == 0 -a $CLEAN == 0 ]; then
  # by default, if no options are set, build OffPiste and 3PL
  BUILD_3PL=1
  BUILD_LIB=1
fi

if [ $BUILD_3PL == 1 ]; then
  echo "==================================="
  echo "Building the 3rd Party Libraries..."
  echo "==================================="

  cd 3PL
  ./build_3PL.sh $cmd_args || exit 1
  cd ..
fi

if [ $BUILD_LIB == 1 ]; then
  echo "============================"
  echo "Building OffPiste..."
  echo "============================"

  cd OffPiste
  ./config.sh $cmd_args || exit 1
  cd ..
fi

if [ $COVERAGE == 1 ]; then
  echo "============================"
  echo "Building Coverage generation"
  echo "============================"

  cd OffPiste
  ./config.sh --coverage || exit 1
  cd ..
fi

if [ $DOCUMENTATION_GEN == 1 ]; then
  echo "============================"
  echo "Building Docs using Doxygen"
  echo "============================"
  # run doxygen
  doxygen Doxyfile
fi

if [ $FORMAT == 1 ]; then
  echo "========================================"
  echo "Formatting source code with clang-format"
  echo "========================================"

  # find all .cpp, .hpp, .cc, .cxx files in OffPiste/core
  # and run clang-format using the .clang-format file in the project root directory
  find OffPiste/core \( -name '*.hpp' -or -name '*.cpp' \) -print -exec clang-format -style=file -i '{}' \;

  # repeat for files in OffPiste/include
  find OffPiste/include \( -name '*.hpp' -or -name '*.cpp' \) -print -exec clang-format -style=file -i '{}' \;

fi

echo "======================================"
echo -e "${gC} Finished Successfully...${eC}"
echo "======================================"
exit 0
