This gives an overview of some of the specifics to take into account when writing the python
documentation so that sphinx can properly render the documentation correctly.

The documentation is written using the numpydoc style.

1. An empty line is required before the following:
   - the parameter block before the argument documentation
   - a list of items

   This basically means that you need to use two '\n' characters on the previous line.

   For example (parameter block):
   ```
    "Verify whether or not a given particle is present\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "        the particle identifier"
   ```

   For example (list of items):
   ```
    "The MassEntry class contains specific information from the atomic mass\n"
    "evaluations:\n\n"
    "  - a particle identifier\n"
    "  - mass excess and uncertainty (in eV)\n"
    "  - binding energy per nucleon and uncertainty (in eV)\n"
    "  - beta decay energy and uncertainty (in eV)\n"
    "  - atomic mass and uncertainty (in amu)\n\n"
   ```