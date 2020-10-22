## Software Organisation

### What will the directory structure look like?

The project's main directories will be:

* `src/` which will contain our C++ source files,
* `test/` which will contain tests, and
* `docs/` which will contain files such as this one, which relate to documenting our development process. Documentation will also be stored here.

### What external modules do you plan on including? What is their basic functionality?

At this stage, we do not intend to rely on any external modules. However, we will use standard C++ headers, such as `<cmath>` and the various STL classes for `strings` and I/O.

### Where will your test suite live? Will you use TravisCI? CodeCov?

As described above, we intend to have a separate `test/` directory in which test files will be placed. Our intention is to use [Google's C++ testing library](https://github.com/google/googletest).

We have already set up TravisCI and CodeCov as part of the previous Milestone. We will update our `travis.yml` and `Makefile` to automate the running of tests following pushes to the project repository.

### How will you distribute your package (e.g. PyPI)?

Unfortunately, C++ does not have a well-established and widely-used package index like PyPI. However, we intend to investigate, and consider distributing the package through [Conan](https://conan.io/), a C++ package manager.

We will also make a pre-built dynamically linked library version of project available in the repository. 

### How will you package your software?

In the root directory of this repository, we have set up a `Makefile` for compiling and testing our source code. We will continue to augment this file as the project progresses.

### Other considerations?

We plan to use Doxygen to generate documentation from inline comments in our source code.