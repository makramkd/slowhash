# slowhash

A hash table library. Not particularly fast.

## Building

This project uses [bazel](https://www.bazel.build/) to build.

```
bazel build //src/lib:slowhash
```

## Run unit tests

This project uses [bazel](https://www.bazel.build/) to run unit tests.

```
bazel test --test_output=all tests
```
