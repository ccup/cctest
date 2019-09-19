# cctest: Modern C++ xUnit Test Framework

[cctest](http://github.com/wisdomcoda/cctest) is a simple, practical, and scalable xUnit Test Framework in Modern C++.

C/C++ are different languages from most modern ones. Writing tests for them has some very specific challenges. Therefore, simply clone ideas from xUnit frameworks for other languages does not work the best. Programmers have to suffer accidental complexities brought by most of existing frameworks.

**cctest** is designed for simplifying efforts of programers, in terms of development, maintenance, flexibility of test management, build & run-time strategy, and others.

### [Bazel](https://www.bazel.build)

#### Build

```bash
$ bazel build //ctest
$ bazel build //ctest:main
```

#### Test

```bash
$ bazel test //spec/...
```

### [CMake](https://www.cmake.org)

#### Build

```bash
$ mkdir build
$ cd build
$ cmake .. 
$ make
```

#### Test

```bash
$ make test
```

If you don't want to run test cases, you should close "CCTEST_RUN_TESTS" option.

```bash
$ cmake -DCCTEST_RUN_TESTS=off ..
```

#### Install

```bash
$ sudo make install
$ sudo ldconfig
```

#### Uninstall

```bash
$ cat install_manifest.txt | xargs echo sudo rm | sh
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
