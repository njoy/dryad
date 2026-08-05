.. currentmodule:: njoy.dryad.thermal

ScatteringKernel
================

An S(a,b) scattering kernel combining a tabulated kernel with the short collision time approximation.

Constructor
~~~~~~~~~~~
.. autosummary::
    :toctree:  generated/

    ScatteringKernel

Read-only Attributes
~~~~~~~~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/

    ~ScatteringKernel.effective_temperature
    ~ScatteringKernel.is_energy_transfer_symmetric
    ~ScatteringKernel.moderator_temperature
    ~ScatteringKernel.short_collision_time
    ~ScatteringKernel.tabulated_scattering_kernel

Methods
~~~~~~~

.. autosummary::
    :toctree: generated/

    ~ScatteringKernel.energy_transfer
    ~ScatteringKernel.momentum_transfer
    ~ScatteringKernel.__call__
    ~ScatteringKernel.angular_distribution
    ~ScatteringKernel.energy_distribution
    ~ScatteringKernel.cross_section
    ~ScatteringKernel.cross_section_value
