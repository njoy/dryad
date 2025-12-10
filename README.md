![Continuous Integration](https://github.com/njoy/dryad/workflows/Continuous%20Integration/badge.svg)

# dryad
A format agnostic nuclear data handler and interface.

# Documentation

Documentation is provided using [Sphinx](https://www.sphinx-doc.org/). The following Python packages need to be installed: 

```python
pip install sphinx
pip install numpydoc
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
