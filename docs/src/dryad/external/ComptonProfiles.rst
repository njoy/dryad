.. currentmodule:: njoy.dryad.external

ComptonProfiles
===============

Compton profiles are currently not part of any evaluated nuclear data library. This class
provides an interface to external sources of this type of data.

Currently we only have tabulated data based on Biggs, Mendelsohn and Mann
calculated profiles from the following reference:

F. Biggs, L. B. Mendelsohn, J. B. Mann, Hartree-Fock Compton profiles for the elements,
Atomic data and nuclear data table, 16, 201-309 (1975)

Methods
~~~~~~~

.. autosummary::
    :toctree: generated/

    ~ComptonProfiles.biggs_mendelsohn_mann_profiles
    ~ComptonProfiles.apply
