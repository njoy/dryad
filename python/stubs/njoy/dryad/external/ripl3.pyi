"""
RIPL-3 data
"""
from __future__ import annotations
import njoy.dryad.id
import typing
__all__: list[str] = ['LevelEntry', 'Levels']
class LevelEntry:
    """
    RIPL-3 level entry information
    
    The LevelEntry class contains level information for a particle from the
    RIPL-3 database:
      - a particle identifier
      - an optional level energy value
      - an optional spin value
      - an optional parity (which is either +1 or -1)
      - an optional half life value
    
    The data is stored in the following units:
      - energy values are in eV
      - half life values are in seconds
    
    Parameters
    ----------
        id : njoy.dryad.id.ParticleID
             the particle identifier
        energy : float, default None
            the level energy (default: None)
        spin : float, default None
            the level spin (default: None)
        parity : int, default None
            the level spin parity (default: None)
        half_life : float, default None
            the level half life (default: None)
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> LevelEntry:
        ...
    def __deepcopy__(self, arg0: dict) -> LevelEntry:
        ...
    def __eq__(self, arg0: LevelEntry) -> bool:
        ...
    def __init__(self, id: njoy.dryad.id.ParticleID, energy: float | None = None, spin: float | None = None, parity: int | None = None, half_life: float | None = None) -> None:
        """
        Initialise the level entry information
        """
    def __ne__(self, arg0: LevelEntry) -> bool:
        ...
    @property
    def energy(self) -> float | None:
        """
        The level energy value
        """
    @energy.setter
    def energy(self, arg1: float | None) -> None:
        ...
    @property
    def half_life(self) -> float | None:
        """
        The level half life
        """
    @half_life.setter
    def half_life(self, arg1: float | None) -> None:
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
    def parity(self) -> int | None:
        """
        The level spin parity
        """
    @parity.setter
    def parity(self, arg1: int | None) -> None:
        ...
    @property
    def spin(self) -> float | None:
        """
        The spin of the level
        """
    @spin.setter
    def spin(self, arg1: float | None) -> None:
        ...
class Levels:
    """
    RIPL-3 level data
    
    The Levels class allows a user to interact with the  nuclear levels part of the RIPL-3
    database.
    """
    @staticmethod
    def has_particle(id: njoy.dryad.id.ParticleID) -> bool:
        """
        Verify whether or not a given particle is present
        
        Parameters
        ----------
            id : njoy.dryad.id.ParticleID
                 the particle identifier
        """
    @staticmethod
    def level(id: njoy.dryad.id.ParticleID) -> LevelEntry:
        """
        Retrieve a level entry for a given particle
        
        Parameters
        ----------
            id : njoy.dryad.id.ParticleID
                 the particle identifier
        """
    @staticmethod
    def size() -> int:
        """
        Return the current size of the RIPL-3 levels data
        """
