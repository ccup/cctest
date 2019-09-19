# cctest examples

## Bazel

```
$ cd cctest/examples
$ bazel test //stlspec/...
$ bazel test //simple/...
```

```
$ bazel-bin/stlspec/queue_spec
$ bazel-bin/stlspec/stack_spec
$ bazel-bin/simple/simple_test
```

## CMake

```
$ cd cctest/examples
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make test
```

```
$ stlspec/stlspec_test 
$ simple/simple_test
```
