## Software Organisation

### What will the directory structure look like?

The project's main directories are:

* `OffPiste/` which contains the C++ source files, header files, and tests for the core automatic differentiation library.
    * `OffPiste/core/src` contains the source code for OffPiste library
    * `OffPiste/core/tests` contains unit and functional tests for the OffPiste library 
    * `OffPiste/include` contains the header files for the OffPiste library
    * `OffPiste/coverage` contains information relating to the coverage of the unit and functional tests
    * `OffPiste/install` contains the  
* `docs/` which contains files such as this one, documenting the library and development process. 
    * `docs/doxygen` contains html documentation for the `AutoDiff` library's functions.
* `3PL` contains 3rd party components. At present, this is Google test.

### What are the basic modules

The core module is in `OffPiste/core/src`. This is where the source code for the automatic differentiation is held. 

The tests are [insert]

The root directory also has a `./config.sh` file. This is a shell script that reads in a user's command and executes actions (such as compiling the library, generating documentation, or generating coverage information). `./config.sh` delegates some functionality to `OffPiste/config.sh` and `OffPiste/coverage.sh`.

Compilation is handled through `CMake`, using the `CMakeLists.txt` files in `OffPiste` and its subdirectories. 

### Where do tests live

As described above, tests are located in `OffPiste/core/tests`.

As described in the `README.md`, tests are run with the command 

```
$ ./config.sh
```

which will also compile the 3rd party libraries and source code. 

### How can a person install your library?

A user can install our library by cloning the repository from github and running

```
./config.sh
```

to compile the components. 

<hr/>