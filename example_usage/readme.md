This folder gives an example of using the `OffPiste` library, in the file `example.cpp` and the accompanying `makefile`.

The `include/` and `lib/` subdirectories are a snapshot of the `OffPiste` library. You should update these by re-compiling the `OffPiste` library as described in the project root's `README.md`. i.e.:

```bash
# compile OffPiste library into OffPiste/install
$ .config.sh -lib -so -testsOFF

# copy OffPiste library into the example project folder
$ cp -r OffPiste/install/ example_usage/
```

The example project can be compiled with:

```bash
$ make example # compile example project
$ ./example.out # run example project
```