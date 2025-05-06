"""
Identifiers for particles, elements, etc.
"""
from __future__ import annotations
import typing
__all__ = ['ElectronSubshellID', 'ElementID', 'LevelID', 'ParticleID']
class ElectronSubshellID:
    """
    The electron subshell identifier
    """
    K: typing.ClassVar[int] = 534
    L1: typing.ClassVar[int] = 535
    L2: typing.ClassVar[int] = 536
    L3: typing.ClassVar[int] = 537
    M1: typing.ClassVar[int] = 535
    M2: typing.ClassVar[int] = 536
    M3: typing.ClassVar[int] = 537
    M4: typing.ClassVar[int] = 536
    M5: typing.ClassVar[int] = 537
    N1: typing.ClassVar[int] = 535
    N2: typing.ClassVar[int] = 536
    N3: typing.ClassVar[int] = 537
    N4: typing.ClassVar[int] = 536
    N5: typing.ClassVar[int] = 537
    N6: typing.ClassVar[int] = 536
    N7: typing.ClassVar[int] = 537
    O1: typing.ClassVar[int] = 535
    O2: typing.ClassVar[int] = 536
    O3: typing.ClassVar[int] = 537
    O4: typing.ClassVar[int] = 536
    O5: typing.ClassVar[int] = 537
    O6: typing.ClassVar[int] = 536
    O7: typing.ClassVar[int] = 537
    O8: typing.ClassVar[int] = 536
    O9: typing.ClassVar[int] = 537
    P1: typing.ClassVar[int] = 535
    P10: typing.ClassVar[int] = 536
    P11: typing.ClassVar[int] = 537
    P2: typing.ClassVar[int] = 536
    P3: typing.ClassVar[int] = 537
    P4: typing.ClassVar[int] = 536
    P5: typing.ClassVar[int] = 537
    P6: typing.ClassVar[int] = 536
    P7: typing.ClassVar[int] = 537
    P8: typing.ClassVar[int] = 536
    P9: typing.ClassVar[int] = 537
    Q1: typing.ClassVar[int] = 535
    Q10: typing.ClassVar[int] = 536
    Q11: typing.ClassVar[int] = 537
    Q2: typing.ClassVar[int] = 536
    Q3: typing.ClassVar[int] = 537
    Q4: typing.ClassVar[int] = 536
    Q5: typing.ClassVar[int] = 537
    Q6: typing.ClassVar[int] = 536
    Q7: typing.ClassVar[int] = 537
    Q8: typing.ClassVar[int] = 536
    Q9: typing.ClassVar[int] = 537
    def __eq__(self, arg0: ElectronSubshellID) -> bool:
        ...
    def __ge__(self, arg0: ElectronSubshellID) -> bool:
        ...
    def __gt__(self, arg0: ElectronSubshellID) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, number: int) -> None:
        """
        Initialise the subshell identifier
        
        Arguments:
            self     the identifier
            number   the subshell number
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the subshell identifier
        
        Arguments:
            self     the identifier
            string   the subshell symbol, name or alternative name
        """
    def __le__(self, arg0: ElectronSubshellID) -> bool:
        ...
    def __lt__(self, arg0: ElectronSubshellID) -> bool:
        ...
    def __ne__(self, arg0: ElectronSubshellID) -> bool:
        ...
    def __repr__(self) -> str:
        """
        Convenience function for printing the identifier
        """
    @property
    def name(self) -> str:
        """
        The element name
        """
    @property
    def number(self) -> int:
        """
        The element number
        """
    @property
    def symbol(self) -> str:
        """
        The element symbol
        """
class ElementID:
    """
    The element identifier
    """
    def __eq__(self, arg0: ElementID) -> bool:
        ...
    def __ge__(self, arg0: ElementID) -> bool:
        ...
    def __gt__(self, arg0: ElementID) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, number: int) -> None:
        """
        Initialise the element identifier
        
        Arguments:
            self     the identifier
            number   the element number
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the element identifier
        
        Arguments:
            self     the identifier
            string   the element symbol, name or alternative name
        """
    def __le__(self, arg0: ElementID) -> bool:
        ...
    def __lt__(self, arg0: ElementID) -> bool:
        ...
    def __ne__(self, arg0: ElementID) -> bool:
        ...
    def __repr__(self) -> str:
        """
        Convenience function for printing the identifier
        """
    @property
    def name(self) -> str:
        """
        The element name
        """
    @property
    def number(self) -> int:
        """
        The element number
        """
    @property
    def symbol(self) -> str:
        """
        The element symbol
        """
class LevelID:
    """
    The level identifier
    """
    continuum: typing.ClassVar[int] = 150
    def __eq__(self, arg0: LevelID) -> bool:
        ...
    def __ge__(self, arg0: LevelID) -> bool:
        ...
    def __gt__(self, arg0: LevelID) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, number: int) -> None:
        """
        Initialise the level identifier
        
        Arguments:
            self     the identifier
            number   the level number
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the level identifier
        
        Arguments:
            self     the identifier
            string   the level symbol
        """
    def __le__(self, arg0: LevelID) -> bool:
        ...
    def __lt__(self, arg0: LevelID) -> bool:
        ...
    def __ne__(self, arg0: LevelID) -> bool:
        ...
    def __repr__(self) -> str:
        """
        Convenience function for printing the identifier
        """
    @property
    def number(self) -> int:
        """
        The level number
        """
    @property
    def symbol(self) -> str:
        """
        The level symbol
        """
class ParticleID:
    """
    The particle identifier
    """
    @staticmethod
    def alpha() -> ParticleID:
        """
        The particle identifier for alphas
        """
    @staticmethod
    def deuteron() -> ParticleID:
        """
        The particle identifier for deuterons
        """
    @staticmethod
    def electron() -> ParticleID:
        """
        The particle identifier for electrons
        """
    @staticmethod
    def helion() -> ParticleID:
        """
        The particle identifier for helions
        """
    @staticmethod
    def neutron() -> ParticleID:
        """
        The particle identifier for neutrons
        """
    @staticmethod
    def photon() -> ParticleID:
        """
        The particle identifier for photons
        """
    @staticmethod
    def positron() -> ParticleID:
        """
        The particle identifier for positrons
        """
    @staticmethod
    def proton() -> ParticleID:
        """
        The particle identifier for protons
        """
    @staticmethod
    def size() -> int:
        """
        The number of currently registered identifiers
        """
    @staticmethod
    def triton() -> ParticleID:
        """
        The particle identifier for tritons
        """
    def __eq__(self, arg0: ParticleID) -> bool:
        ...
    def __ge__(self, arg0: ParticleID) -> bool:
        ...
    def __gt__(self, arg0: ParticleID) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, za: int, number: int = 0) -> None:
        """
        Initialise the particle identifier
        
        Arguments:
            self     the identifier
            za       the particle za number
            number   the particle level number or subshell number (default is zero)
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the particle identifier
        
        Arguments:
            self     the identifier
            string   the particle symbol, name or alternative
        """
    def __le__(self, arg0: ParticleID) -> bool:
        ...
    def __lt__(self, arg0: ParticleID) -> bool:
        ...
    def __ne__(self, arg0: ParticleID) -> bool:
        ...
    def __repr__(self) -> str:
        """
        Convenience function for printing the identifier
        """
    @property
    def a(self) -> int:
        """
        The particle's mass number
        """
    @property
    def e(self) -> int:
        """
        The particle's level number
        """
    @property
    def number(self) -> int:
        """
        The particle number
        """
    @property
    def subshell(self) -> ElectronSubshellID | None:
        """
        The particle's subshell
        """
    @property
    def symbol(self) -> str:
        """
        The particle's symbol
        """
    @property
    def z(self) -> int:
        """
        The particle's element number
        """
