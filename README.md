![Continuous Integration](https://github.com/njoy/dryad/workflows/Continuous%20Integration/badge.svg)

# dryad
A format agnostic nuclear data handler and interface.

# Configuration and external data

NJOY uses a configuration file to point to external data files on a user's system. For now, this is only used
for RIPL-3 discrete level energies and spin-parity assignments and AME2020 atomic mass data. For ease of usage
we have made this external data available in the [njoy-data](https://github.com/njoy/njoy-data) repository.

NJOY will look for a configuration file called `njoy.config` in the path pointed to by the environmental
variable `NJOY_DATAPATH`. When using the above mentioned data repository, the `NJOY_DATAPATH` environmental
variable should just point to the location of the data repository.

The following is a sample configuration file:
```
# NJOY configuration file
#
# The following properties are currently defined:
#   - ame2020 : the relative or absolute path and file name of the Atomic Mass Evaluation (2020 version).
#   - ripl3_levels : the relative or absolute path to the discrete level data of the RIPL-3 database (the
#                    directory where the zXXX.dat files can be found).
#                    When using a relative path, the path is relative to the path of this
#                    configuration file (as set on the NJOY_DATAPATH environmental variable).

ame2020 = ame/2020/mass_1.mas20.txt
ripl3_levels = ripl-3/levels
```

# Building the Python bindings

NJOY uses CMake to pull and build dependencies. Default build options provide python bindings for `dryad` 
and all other modules (`njoy.python` defaults to `ON`). On most Unix systems (non-Windows), assuming Python
and CMake can be found in the users PATH, building NJOY can be done by:

* Obtaining the source code
* Navigating to the source root directory, called `dryad`
* Running 

```bash
cmake -B <target_build_directory> -DCMAKE_BUILD_TYPE=Release
cmake --build <target_build_directory> -j8
```

The resulting Python module can then be used directly from the `<target_build_directory>/python` directory, or installed as usual.

On Windows, build commands depend more on your setup. Use command

```cmd
cmake -G
```
to find a generator string for the build system you intend to use. A generator string looks like 
"Visual Studio 18 2026" or "Ninja"

For a single-configuration build system like Ninja, builds are made with 

```cmd
cmake -G <generator string> -B <target_build_directory> -DCMAKE_BUILD_TYPE=Release
cmake --build <target_build_directory> -j8
```

and the Python module is built in `<target_build_directory>/python`

For multi-configuration build systems like MSBuild used by MSVC, builds are made with

```cmd
cmake -G <generator string> -B <target_build_directory> 
cmake --build <target_build_directory> --config Release -j8
```

and the Python module is built in `<target_build_directory>/python/Release`

To also build and run the C++ and Python unit test suite alongside the bindings, add `-Dnjoy.tests=ON` to the
CMake configuration step above.

Some tests and bindings rely on external RIPL-3 and AME2020 data, so make sure the `NJOY_DATAPATH` environment
variable is set as described in the [Configuration and external data](#configuration-and-external-data) section above.

# Documentation

Documentation is provided using [Sphinx](https://www.sphinx-doc.org/). The following Python packages need to be installed:

```python
pip install sphinx
pip install numpydoc
pip install pydata_sphinx_theme
```

The documentation is not built by default. To build the documentation after building `dryad`, in the `dryad/build` directory run:

```bash
make sphinx
```

This will build the HTML documentation within the `dryad/docs/build` directory.

To clean the documentation, move into the `dryad/docs` directory and run:

```bash
make clean
```

# Third-party dependencies

NJOY uses a number of third-party dependencies for various purposes such as floating point number parsing, matrix algebra, etc. The following is an overview of these third-party libraries with references and license information.

## Eigen

Eigen is a C++ template library for linear algebra and provides matrix and vector types, numerical solvers, and related algorithms. NJOY uses Eigen for matrix and vector representations used in resonance reconstruction and covariance data, eigenvalue decomposition algorithms, etc.

The Eigen source repository can be found [here](https://gitlab.com/libeigen/eigen) and is mirrored in the njoy organisation on GitHub [here](https://github.com/njoy/eigen). This mirror is required due to the way we handle third-party dependencies in our CMake configuration.

License: [Mozilla Public License (MPL 2.0)](https://gitlab.com/libeigen/eigen/-/blob/master/COPYING.MPL2)

## Fast_float

The fast_float library provides fast header-only implementations for the C++ std::from_chars functions which convert ASCII strings representing decimal values (e.g., 1.3e10) into binary types. It also provides an extension for fortran formatted strings. NJOY uses this library for the implementation of the std::from_chars functions since some standard library implementations do not provide them.

The fast_float source repository can be found [here](https://github.com/fastfloat/fast_float).

License: [Apache License, Version 2.0](https://github.com/fastfloat/fast_float/blob/main/LICENSE-APACHE) or [MIT license](https://github.com/fastfloat/fast_float/blob/main/LICENSE-MIT) or [BOOST software license](https://github.com/fastfloat/fast_float/blob/main/LICENSE-BOOST)

## pugixml

pugixml is a C++ library for XML file parsing and manipulation. NJOY uses this library for reading and writing GNDS XML files.

The pugixml source repository can be found [here](https://github.com/zeux/pugixml).

License: [MIT license](https://github.com/zeux/pugixml/blob/master/LICENSE.md)

## pybind11

pybind11 is a C++ library that exposes C++ types in Python and vice versa, mainly to create Python bindings of existing C++ code. NJOY uses this library for its Python bindings

The pybind11 source repository can be found [here](https://github.com/pybind/pybind11).

License: [BSD 3-Clause License](https://github.com/pybind/pybind11/blob/master/LICENSE)

## spdlog and fmt

spdlog is a C++ logging library which uses the fmt library for string formatting.

The spdlog source repository can be found [here](https://github.com/gabime/spdlog).

License: [MIT license](https://github.com/gabime/spdlog/blob/v1.x/LICENSE) for spdlog and [MIT license](https://raw.githubusercontent.com/fmtlib/fmt/master/LICENSE) for fmt.

## Catch-2

Catch2 is a unit testing framework for C++ used by NJOY for our C++ unit tests.

The Catch-2 source repository can be found [here](https://github.com/catchorg/Catch2).

License: [BOOST software license](https://github.com/catchorg/Catch2/blob/devel/LICENSE.txt)

# LICENSE
The software contained in this repository is covered under the associated [LICENSE](LICENSE) file.
