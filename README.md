## Docker Instructions

If you have [Docker](https://www.docker.com/) installed, you can run this
in your terminal, when the Dockerfile is inside the `.devcontainer` directory:

```bash
docker build -f ./.devcontainer/Dockerfile --tag=theater_booker:latest .
docker run -it theater_booker:latest
```

This command will put you in a `bash` session in a Ubuntu 20.04 Docker container,
with all of the tools listed in the [Dependencies](https://github.com/GeoDTN/theater_booker/blob/master/README_dependencies.md) section already installed.
Additionally, you will have `g++-11` and `clang++-13` installed as the default
versions of `g++` and `clang++`.

If you want to build this container using some other versions of gcc and clang,
you may do so with the `GCC_VER` and `LLVM_VER` arguments:

```bash
docker build --tag=theater_booker:latest --build-arg GCC_VER=10 --build-arg LLVM_VER=11 .
```

The CC and CXX environment variables are set to GCC version 11 by default.
If you wish to use clang as your default CC and CXX environment variables, you
may do so like this:

```bash
docker build --tag=theater_booker:latest --build-arg USE_CLANG=1 .
```

You will be logged in as root, so you will see the `#` symbol as your prompt.
You will be in a directory that contains a copy of the `cpp_theater_booker`;
any changes you make to your local copy will not be updated in the Docker image
until you rebuild it.
If you need to mount your local copy directly in the Docker image, see
[Docker volumes docs](https://docs.docker.com/storage/volumes/).
TLDR:

```bash
docker run -it \
	-v absolute_path_on_host_machine:absolute_path_in_guest_container \
	theater_booker:latest
```
## Or open in devcontainer, open terminal in project directory and can use either of the following commands
You can configure and build  using the following commands:

```bash
/theater_booker# mkdir build
/theater_booker# cmake -S . -B ./build
/theater_booker# cmake --build ./build
```

You can configure and build using `clang-13`, without rebuilding the container,
with these commands:

```bash
/theater_booker# mkdir build
/theater_booker# CC=clang CXX=clang++ cmake -S . -B ./build
/theater_booker# cmake --build ./build
```
The project executable[in this case theater_booker] is in build directory.
And the unit test executable is in build/unit_tests directory. 
The `ccmake` tool is also installed; you can substitute `ccmake` for `cmake` to
configure the project interactively.
All of the tools this project supports are installed in the Docker image;
enabling them is as simple as flipping a switch using the `ccmake` interface.
Be aware that some of the sanitizers conflict with each other, so be sure to
run them separately.

## conan :
Run the following commands
```bash
/theater_booker# mkdir build 
/theater_booker# conan install . --output-folder=build --build=missing --build=gtest/1.15.0
/theater_booker# conan build . --output-folder=build --build=missing
/theater_booker# cd build
/theater_booker# cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
/theater_booker# make
/theater_booker# ./theater_booker        ## run application executable
/theater_booker# cd unit_tests
/theater_booker# ./theater_booker_tests   ## run unit tests executable 

```
## doxygen_documentation_generator
To automate generation of doxgen documentation and dependeny(call graph)
use the following commands
```bash
/theater_booker# chmod +x doxygen_documentation_generator.sh 
/theater_booker# sh doxygen_documentation_generator.sh
```
The documentation will be written to docs/html. 
In this case, to /workspaces/theater_booker/docs/html 

