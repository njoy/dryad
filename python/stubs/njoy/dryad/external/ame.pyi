"""
Atomic mass evaluation data
"""
from __future__ import annotations
import njoy.dryad.id
import typing
__all__: list[str] = ['MassEntry', 'Masses']
class MassEntry:
    """
    Mass entry information from the Atomic Mass Evaluation
    
    The MassEntry class contains specific information from the atomic mass
    evaluations:
      - a particle identifier
      - mass excess and uncertainty (in eV)
      - binding energy per nucleon and uncertainty (in eV)
      - beta decay energy and uncertainty (in eV)
      - atomic mass and uncertainty (in amu)
    
    Parameters
    ----------
        id : njoy.dryad.id.ParticleID
            the particle identifier
        mass_excess : float, default None
            the mass excess (default: None)
        mass_excess_uncertainty : float, default None
            the mass excess uncertainty (default: None)
        binding_energy : float, default None
            the binding energy per nucleon (default: None)
        binding_energy_uncertainty : float, default None
            the binding energy per nucleon uncertainty (default: None)
        beta_decay_energy : float, default None
            the beta decay energy (default: None)
        beta_decay_energy_uncertainty : float, default None
            the beta decay energy uncertainty (default: None)
        mass : float, default None
            the atomic mass (default: None)
        mass_uncertainty : float, default None
            the atomic mass uncertainty (default: None)
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> MassEntry:
        ...
    def __deepcopy__(self, arg0: dict) -> MassEntry:
        ...
    def __eq__(self, arg0: MassEntry) -> bool:
        ...
    def __init__(self, id: njoy.dryad.id.ParticleID, mass_excess: float | None = None, mass_excess_uncertainty: float | None = None, binding_energy: float | None = None, binding_energy_uncertainty: float | None = None, beta_decay_energy: float | None = None, beta_decay_energy_uncertainty: float | None = None, mass: float | None = None, mass_uncertainty: float | None = None) -> None:
        """
        Initialise the mass entry information
        """
    def __ne__(self, arg0: MassEntry) -> bool:
        ...
    @property
    def atomic_mass(self) -> float | None:
        """
        The atomic mass
        """
    @atomic_mass.setter
    def atomic_mass(self, arg1: float | None) -> None:
        ...
    @property
    def atomic_mass_uncertainty(self) -> float | None:
        """
        The atomic mass uncertainty
        """
    @atomic_mass_uncertainty.setter
    def atomic_mass_uncertainty(self, arg1: float | None) -> None:
        ...
    @property
    def beta_decay_energy(self) -> float | None:
        """
        The beta decay energy
        """
    @beta_decay_energy.setter
    def beta_decay_energy(self, arg1: float | None) -> None:
        ...
    @property
    def beta_decay_energy_uncertainty(self) -> float | None:
        """
        The beta decay energy uncertainty
        """
    @beta_decay_energy_uncertainty.setter
    def beta_decay_energy_uncertainty(self, arg1: float | None) -> None:
        ...
    @property
    def binding_energy(self) -> float | None:
        """
        The binding energy per nucleon
        """
    @binding_energy.setter
    def binding_energy(self, arg1: float | None) -> None:
        ...
    @property
    def binding_energy_uncertainty(self) -> float | None:
        """
        The binding energy per nucleon uncertainty
        """
    @binding_energy_uncertainty.setter
    def binding_energy_uncertainty(self, arg1: float | None) -> None:
        ...
    @property
    def identifier(self) -> njoy.dryad.id.ParticleID:
        """
        The particle identifier
        """
    @identifier.setter
    def identifier(self, arg1: njoy.dryad.id.ParticleID) -> None:
        ...
    @property
    def mass_excess(self) -> float | None:
        """
        The mass excess
        """
    @mass_excess.setter
    def mass_excess(self, arg1: float | None) -> None:
        ...
    @property
    def mass_excess_uncertainty(self) -> float | None:
        """
        The mass excess uncertainty
        """
    @mass_excess_uncertainty.setter
    def mass_excess_uncertainty(self, arg1: float | None) -> None:
        ...
class Masses:
    """
    AME2020 mass data
    
    The Masses class allows a user to interact with the AME2020 mass data.
    """
    @staticmethod
    def entry(id: njoy.dryad.id.ParticleID) -> MassEntry:
        """
        Retrieve a mass entry for a given particle
        
        Parameters
        ----------
            id : njoy.dryad.id.ParticleID
                the particle identifier
        """
    @staticmethod
    def has_entry(id: njoy.dryad.id.ParticleID) -> bool:
        """
        Verify whether or not a given particle is present
        
        Parameters
        ----------
            id : njoy.dryad.id.ParticleID
                the particle identifier
        """
    @staticmethod
    def size() -> int:
        """
        Return the current size of the AME2020 mass data
        """
