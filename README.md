# cctest: Modern C++ xUnit Test Framework

[cctest](http://github.com/wisdomcoda/cctest) is a simple, practical, and scalable xUnit Test Framework in Modern C++.

C/C++ are different languages from most modern ones. Writing tests for them has some very specific challenges. Therefore, simply clone ideas from xUnit frameworks for other languages does not work the best. Programmers have to suffer accidental complexities brought by most of existing frameworks.

**cctest** is designed for simplifying efforts of programers, in terms of development, maintenance, flexibility of test management, build & run-time strategy, and others.

## Build

- [bazel](https://www.bazel.build)
- [cmake](https://www.cmake.org)

### Bazel

```bash
$ bazel test //spec/...
```

### CMake

```bash
$ mkdir build
$ cd build
$ cmake .. 
$ make
$ make test
```

If you don't want run test cases, you can close "CCTEST_RUN_TESTS" option.

```bash
$ cmake -DCCTEST_RUN_TESTS=off ..
```

## Docker

You can build develop image based ubuntu 18.04.

```bash
$ sudo docker build -t ubuntu18.04-dev:1.0 -f dockerfiles/Dockerfile.devel .
```

And start docker container.

```bash
$ sudo docker run -v `pwd`:/root/cctest -it --name cctest ubuntu18.04-dev:1.0
```
