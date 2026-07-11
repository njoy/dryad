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

## LICENSE
The software contained in this repository is covered under the associated [LICENSE](LICENSE) file.
