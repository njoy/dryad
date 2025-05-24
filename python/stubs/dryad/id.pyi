"""
Identifiers for particles, elements, etc.
"""
from __future__ import annotations
import typing
__all__ = ['ElectronSubshellID', 'ElementID', 'LevelID', 'ParticleID', 'ReactionType']
class ElectronSubshellID:
    """
    The electron subshell identifier
    
    For more information on how to create instances of ElectronSubshellID, see the
    Jupyter notebook dryad-identifiers.ipynb under python/examples.
    """
    K: typing.ClassVar[int] = 534
    L1: typing.ClassVar[int] = 535
    L2: typing.ClassVar[int] = 536
    L3: typing.ClassVar[int] = 537
    M1: typing.ClassVar[int] = 538
    M2: typing.ClassVar[int] = 539
    M3: typing.ClassVar[int] = 540
    M4: typing.ClassVar[int] = 541
    M5: typing.ClassVar[int] = 542
    N1: typing.ClassVar[int] = 543
    N2: typing.ClassVar[int] = 544
    N3: typing.ClassVar[int] = 545
    N4: typing.ClassVar[int] = 546
    N5: typing.ClassVar[int] = 547
    N6: typing.ClassVar[int] = 548
    N7: typing.ClassVar[int] = 549
    O1: typing.ClassVar[int] = 550
    O2: typing.ClassVar[int] = 551
    O3: typing.ClassVar[int] = 552
    O4: typing.ClassVar[int] = 553
    O5: typing.ClassVar[int] = 554
    O6: typing.ClassVar[int] = 555
    O7: typing.ClassVar[int] = 556
    O8: typing.ClassVar[int] = 557
    O9: typing.ClassVar[int] = 558
    P1: typing.ClassVar[int] = 559
    P10: typing.ClassVar[int] = 568
    P11: typing.ClassVar[int] = 569
    P2: typing.ClassVar[int] = 560
    P3: typing.ClassVar[int] = 561
    P4: typing.ClassVar[int] = 562
    P5: typing.ClassVar[int] = 563
    P6: typing.ClassVar[int] = 564
    P7: typing.ClassVar[int] = 565
    P8: typing.ClassVar[int] = 566
    P9: typing.ClassVar[int] = 567
    Q1: typing.ClassVar[int] = 570
    Q10: typing.ClassVar[int] = 579
    Q11: typing.ClassVar[int] = 580
    Q12: typing.ClassVar[int] = 581
    Q13: typing.ClassVar[int] = 582
    Q2: typing.ClassVar[int] = 571
    Q3: typing.ClassVar[int] = 572
    Q4: typing.ClassVar[int] = 573
    Q5: typing.ClassVar[int] = 574
    Q6: typing.ClassVar[int] = 575
    Q7: typing.ClassVar[int] = 576
    Q8: typing.ClassVar[int] = 577
    Q9: typing.ClassVar[int] = 578
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
    def __str__(self) -> str:
        """
        Convenience function for printing the identifier
        """
    @property
    def name(self) -> str:
        """
        The subshell name
        """
    @property
    def number(self) -> int:
        """
        The subshell number
        """
    @property
    def symbol(self) -> str:
        """
        The subshell symbol
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
    def __str__(self) -> str:
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
    all: typing.ClassVar[int] = 151
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
    def __str__(self) -> str:
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
    
    The ParticleID can be used to identify the following particle types (the
    numbers between parentheses are the internal logic numbers assigned to them):
      - fundamental particles: g (0), e- (1), e+ (2), n (10), p (1001), d (1002),
        t (1003), h (2003), a (2004)
      - elements (z * 1000000)
      - nuclides (z * 1000000 + a * 1000 + l, with l = 0 .. 150 with 150 being
        defined as the continuum )
      - ions (z * 1000000 + s, with s = K(534) .. Q11(580) - basically the ENDF
        mt numbers for the subshell ionisation)
    
    Comparison operators are provided using the logical order given by the
    element number. A hash function and override for std::hash is also
    provided.
    
    For more information on how to create instances of ParticleID, see the
    Jupyter notebook dryad-identifiers.ipynb under python/examples.
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
    def __str__(self) -> str:
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
    @property
    def za(self) -> int:
        """
        The particle's za number
        """
class ReactionType:
    """
    The reaction type
    
    The ReactionType can be used to identify reaction types. For the moment, only
    registered types can be used. In the future, we will extend this so that users
    can create types other than the ones currently registered.
    
    For more information on how to create instances of ReactionType, see the
    Jupyter notebook dryad-identifiers.ipynb under python/examples.
    """
    @staticmethod
    def size() -> int:
        """
        The number of currently registered types
        """
    def __eq__(self, arg0: ReactionType) -> bool:
        ...
    def __ge__(self, arg0: ReactionType) -> bool:
        ...
    def __gt__(self, arg0: ReactionType) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, mt: int) -> None:
        """
        Initialise the reaction type
        
        Arguments:
            self   the reaction type
            mt     the mt number
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the reaction type
        
        Arguments:
            self     the reaction type
            string   the reaction type string
        """
    def __le__(self, arg0: ReactionType) -> bool:
        ...
    def __lt__(self, arg0: ReactionType) -> bool:
        ...
    def __ne__(self, arg0: ReactionType) -> bool:
        ...
    def __str__(self) -> str:
        """
        Convenience function for printing the identifier
        """
    def resolve(self, projectile: ParticleID, target: ParticleID) -> ParticleID:
        """
        Return the residual produced by this reaction type
        
        Arguments:
            self         the reaction type
            projectile   the projectile
            target       the target
        """
    @property
    def interaction_type(self) -> ...:
        """
        The interaction type (nuclear or atomic) associated to the reaction type
        """
    @property
    def is_compatible_with_endf(self) -> bool:
        """
        Flag to indicate whether or not the reaction type is compatible with ENDF
        """
    @property
    def is_special(self) -> bool:
        """
        Flag to indicate whether or not the reaction type is considered a special type
        
        A special type is a reaction type for which no outgoing particles types can be
        defined because it is a summation reaction or because the outgoing particles
        are not known due to complexity (e.g. anything or fission)
        """
    @property
    def level(self) -> int | None:
        """
        The level or subshell number for the residual
        """
    @property
    def mt(self) -> int | None:
        """
        The interaction type's mt number
        """
    @property
    def particles(self) -> list[tuple[ParticleID, int]] | None:
        """
        The reaction type's outgoing particles
        """
    @property
    def symbol(self) -> str:
        """
        The reaction type's symbol
        """
