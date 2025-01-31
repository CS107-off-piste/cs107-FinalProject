#!/bin/bash -e
# Folder structure:
# ================
# project_root
#   install            # install directory
#   OffPiste           # source code
#     core             # location of source code

set -euo pipefail

# =======================
# project directory paths
# =======================
CURRENT_PATH="$(pwd)"

cd ..
PROJECT_ROOT="$(pwd)"
cd ${CURRENT_PATH}

# ===============
# library sources
# ===============
MAL_DIRECTORY=${PROJECT_ROOT}/OffPiste
MAL_SO_NAME=OffPiste

# ======================
# folder directory paths
# ======================
INSTALL_DIRECTORY=${MAL_DIRECTORY}/install
INSTALL_MAL_DIRECTORY=${INSTALL_DIRECTORY}

BUILD_DIRECTORY=${MAL_DIRECTORY}/build
BUILD_MAL_DIRECTORY=${BUILD_DIRECTORY}

# =========================
# third party library paths
# =========================
INSTALL_3RD_PARTY_PATH=${PROJECT_ROOT}/install/3PL

# google test path
GTEST_DIRECTORY=${INSTALL_3RD_PARTY_PATH}/googletest

# ==================
# compiling defaults
# ==================
BUILD_MAL=1
BUILD_CLEAN=0
BUILD_TEST=1

# =================
# compiler defaults
# =================
CC=gcc
CXX=g++

C_FLAGS=
CXX_FLAGS=-std=c++14 # require modern c++
FC_FLAGS=

# =========================
# Coverage Flag
# - turns off optimizations
# =========================
COVERAGE=OFF

# ========================
# compiler option defaults
# ========================
BUILD_TYPE="Release"

# ========================
# compile into .so
# ========================
PACKAGE_MODULE=OFF

# ========================
# make and install command
# ========================
MAKE_CMD="make install"

# ==============
# print strings
# ==============
opt_str="[OPTION] "

eC="\x1B[0m"
rC="\x1B[0;41m"
gC="\x1B[0;42m"
yC="\x1B[0;33m"
GC="\x1B[1;32m"
mC="\x1B[0;43m"

help() {
    echo "Usage: $0 [OPTION]...[COMPILER OPTIONS]..."
    echo " "
    echo " This script builds the OffPiste Autodiff library. "
    echo " "
    echo "  [OPTION]:"
    echo "    --help    -h      displays this help message"
    echo "    --clean   -c      removes build directory: dg4est/builds/dg4est_{}"
    echo "    --release -opt    compile the project in optimized mode"
    echo "    --debug   -deb    compile the project in debug mode"
    echo " "
    echo "  [COMPILER OPTIONS]:"
    echo "     CC=<arg>     cc=<arg>    sets the C compiler"
    echo "    CXX=<arg>    cxx=<arg>    sets the C++ compiler"
    echo " "
    echo "      C_FLAGS=<arg>    c_flags=<arg>    sets the C compiler flags"
    echo "    CXX_FLAGS=<arg>  cxx_flags=<arg>    sets the C++ compiler flags"
    echo " "
    echo "  [Intel Flags]:"
    echo "     --avx     -avx         sets Intel AVX Instructions"
    echo "     --avx2    -avx2        sets Intel AVX-2 Instructions"
    echo "     --avx512  -avx512      sets Intel AVX-512 Instructions"
}
# ----------------------------- #
# Start the compilation process #
# ----------------------------- #
cd $PROJECT_ROOT

# ============
# parse inputs
# ============
for var in "$@"
do
  if [ "$var" == "--help" -o "$var" == "-help" -o "$var" == "-h" ]; then
    help
    exit 0

  elif [ "$var" == "--clean" -o "$var" == "-clean" -o "$var" == "-c" ]; then
    echo ${opt_str} "Clean and rebuild"
    BUILD_CLEAN=1
    BUILD_MAL=0

  elif [ "$var" == "--release" -o "$var" == "-release" -o "$var" == "-opt" ]; then
    echo ${opt_str} "Compiling in optimized mode"
    BUILD_SUFFIX="_release"
    BUILD_TYPE="Release"

  elif [ "$var" == "--debug" -o "$var" == "-debug" -o "$var" == "-deb" ]; then
    echo ${opt_str} "Compiling in debug mode"
    BUILD_SUFFIX="_debug"
    BUILD_TYPE="Debug"

  elif [ "$var" == "--testsOFF" -o "$var" == "-testsOFF" -o "$var" == "-toff" ]; then
    echo ${opt_str} "Turning off unit testing (google tests)"
    BUILD_TEST=0

  elif [ "${var:0:3}" == "CC=" -o "${var:0:3}" == "cc=" ]; then
    CC=${var:3}
    echo -e "[OPTION]       C Compiler: $yC$CC$eC"

  elif [ "${var:0:4}" == "CXX=" -o "${var:0:4}" == "cxx=" ]; then
    CXX=${var:4}
    echo -e "[OPTION]     CXX Compiler: $yC$CXX$eC"

  elif [ "${var:0:8}" == "C_FLAGS=" -o "${var:0:8}" == "c_flags=" ]; then
    C_FLAGS=${var:8}
    echo -e "[OPTION]       C Compiler Flags: $yC$C_FLAGS$eC"

  elif [ "${var:0:10}" == "CXX_FLAGS=" -o "${var:0:10}" == "cxx_flags=" ]; then
    CXX_FLAGS=${var:10}
    echo -e "[OPTION]     CXX Compiler Flags: $yC$CXX_FLAGS$eC"

  elif [ "$var" == "--AVX" -o "$var" == "-avx" ]; then
    C_FLAGS="${C_FLAGS} -xCore-AVX"
    CXX_FLAGS="${CXX_FLAGS} -xCore-AVX"
    FC_FLAGS="${FC_FLAGS} -xCore-AVX"

  elif [ "$var" == "--AVX2" -o "$var" == "-avx2" ]; then
    C_FLAGS="${C_FLAGS} -xCore-AVX2"
    CXX_FLAGS="${CXX_FLAGS} -xCore-AVX2"
    FC_FLAGS="${FC_FLAGS} -xCore-AVX2"

  elif [ "$var" == "--AVX512" -o "$var" == "-avx512" ]; then
    C_FLAGS="${C_FLAGS} -xCore-AVX512"
    CXX_FLAGS="${CXX_FLAGS} -xCore-AVX512"
    FC_FLAGS="${FC_FLAGS} -xCore-AVX512"

  elif [ "$var" == "--coverage" -o "$var" == "-coverage" -o "$var" == "-cov" ]; then
    COVERAGE=ON
    # must use gcc to generate gcov-compatible coverage data
    CC=gcc
    CXX=g++

  elif [ "$var" == "--build_so" -o "$var" == "-so" ]; then
    PACKAGE_MODULE=ON

  elif [ "$var" == "-go" ]; then
    CC=gcc
    CXX=g++

  elif [ "$var" == "-intel" ]; then
    CC=icc
    CXX=icpc

  fi
done

# =========================
# display command line args
# =========================
echo " "
echo "$0 $@"

# ----------------------------------------------------- #
# After reading in cmd arg options, set remaining paths #
# ----------------------------------------------------- #

# ======================================
# install/build location compiled source
# ======================================
COMPILE_INSTALL_MAL_DIRECTORY="${INSTALL_MAL_DIRECTORY}"
COMPILE_BUILD_MAL_DIRECTORY="${BUILD_MAL_DIRECTORY}"

# ==============
# compiler paths
# ==============
CC_PATH="`which $CC`"
CXX_PATH="`which $CXX`"

# ======================
# check source directory
# ======================
if [ ! -d "${MAL_DIRECTORY}" ]; then
  echo " "
  echo "Error:"
  echo "${MAL_DIRECTORY} does not exist."
  exit 1
fi

# =======================
# check install directory
# =======================
if [ ! -d "${INSTALL_DIRECTORY}" ]; then
  echo  "${INSTALL_DIRECTORY} does not exist. Making it..."
  mkdir "${INSTALL_DIRECTORY}"
fi

# ======================
# check builds directory
# ======================
if [ ! -d "${BUILD_DIRECTORY}" ]; then
  echo  "${BUILD_DIRECTORY} does not exist. Making it..."
  mkdir "${BUILD_DIRECTORY}"
fi

UNIT_TEST="OFF"
if [ ${BUILD_TEST} == 1 ]; then
  UNIT_TEST="ON"
  if [ ! -d "${GTEST_DIRECTORY}" ]; then
    echo " "
    echo "==================================="
    echo -e "OPTION: Unit Testing ${rC}OFF${eC}"
    echo "WARNING: Google Test was NOT found."
    echo "         Turning off unit testing."
    echo "==================================="
    UNIT_TEST="OFF"
  else
    echo " "
    echo "==============================="
    echo -e "OPTION: Unit Testing ${gC}ON${eC}"
    echo "        Google Test was found: "
    echo "     ../install/3PL/googletest"
    echo "==============================="
  fi
fi

# ===================================================================
if [ $BUILD_CLEAN == 1 ]; then
  echo " "
  echo "Clean: removing ${COMPILE_BUILD_MAL_DIRECTORY}"
  echo "Clean: removing ${COMPILE_INSTALL_MAL_DIRECTORY}"
  echo "Clean: removing coverage"
  echo " "
  rm -rf $COMPILE_BUILD_MAL_DIRECTORY
  rm -rf $COMPILE_INSTALL_MAL_DIRECTORY
  rm -rf $CURRENT_PATH/coverage
fi

# ===================================================================
COMPILE_FAIL=0
if [ $BUILD_MAL == 1 ]; then
  echo " "
  echo -e "${mC} ========== Building OffPiste ========= ${eC}"
  echo "   Compiling Options:"
  echo "          Build Type: ${BUILD_TYPE}"
  echo "    Install Location: ${COMPILE_INSTALL_MAL_DIRECTORY}"
  echo " Executable Location: ${COMPILE_BUILD_MAL_DIRECTORY}/bin"
  echo " "
  echo "                  CC: ${CC}"
  echo "                 CXX: ${CXX}"
  echo " "
  echo "             C Flags: ${C_FLAGS}"
  echo "           CXX Flags: ${CXX_FLAGS}"
  echo -e "${mC} ============================================== ${eC}"
  echo " "

  # move to the build directory
  cd $BUILD_DIRECTORY

  if [ ! -d $COMPILE_BUILD_MAL_DIRECTORY ]; then
    mkdir $COMPILE_BUILD_MAL_DIRECTORY
  fi
  cd $COMPILE_BUILD_MAL_DIRECTORY

  cmake -D CMAKE_C_COMPILER=${CC_PATH}                              \
        -D CMAKE_CXX_COMPILER=${CXX_PATH}                           \
        -D CMAKE_C_FLAGS=${C_FLAGS}                                 \
        -D CMAKE_CXX_FLAGS=${CXX_FLAGS}                             \
        -D CMAKE_INSTALL_PREFIX=${COMPILE_INSTALL_MAL_DIRECTORY}    \
        -D CMAKE_BUILD_TYPE=${BUILD_TYPE}                           \
        -D gtest_dir=${GTEST_DIRECTORY}                             \
        -D UNIT_TEST=${UNIT_TEST}                                   \
        -D COVERAGE=${COVERAGE}                                     \
        -D PACKAGE_MODULE=${PACKAGE_MODULE}                         \
        -G "Unix Makefiles" ${MAL_DIRECTORY} | tee cmake_config.out

  ${MAKE_CMD}
  cd ${CURRENT_PATH}

  if [ ! -d "${COMPILE_INSTALL_MAL_DIRECTORY}" ]; then
    echo "ERROR:"
    echo "${COMPILE_INSTALL_MAL_DIRECTORY} does not exist."
    COMPILE_FAIL=1
  fi

  if [ ${COMPILE_FAIL} == 0 ]; then
    echo " "
    echo " ============================================================ "
    echo -e " ${gC} OffPiste build successful! ${eC}"
    echo    "   Compiling Options:"
    echo    "          Build Type: ${BUILD_TYPE}"
    echo    "      Build Location: ${COMPILE_BUILD_MAL_DIRECTORY}"
    echo -e "                    : ${GC}make clean; make -j install${eC} in this directory"
    echo    "    Install Location: ${COMPILE_INSTALL_MAL_DIRECTORY}"
    echo    " "
    echo    "                  CC: ${CC}"
    echo    "                 CXX: ${CXX}"
    echo    " "
    echo    "            CC Flags: ${C_FLAGS}"
    echo    "           CXX Flags: ${CXX_FLAGS}"
    echo    " ============================================================ "
    echo    " "
  else
    echo " "
    echo         "================================"
    echo -e "${rC} OffPiste build FAILED! ${eC}"
    echo         "================================"
    echo " "
    exit 1
  fi
fi

if [ ${COVERAGE} == "ON" ]; then
    cd $CURRENT_PATH
    echo "Building code coverage..."
    source ./coverage.sh || exit 1
fi
# ===================================================================
echo -e " ${gC}Build Script Completed Successfully!${eC}"
