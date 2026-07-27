"""
Identifiers for particles, elements, etc.
"""
from __future__ import annotations
import njoy.dryad
import typing
__all__: list[str] = ['ChannelID', 'ElectronSubshellID', 'ElementID', 'EnergyGroup', 'LevelID', 'ParticleID', 'ReactionID', 'ReactionType']
class ChannelID:
    """
    The channel identifier, with associated reaction and quantum numbers
    
    When using comparison on the channel identifier, we use a Jpi,l,s,reaction,partial
    ordering.
    
    Parameters
    ----------
        reaction : njoy.dryad.id.ReactionID
            the reaction
        quantum_numbers : njoy.dryad.resonances.ChannelQuantumNumbers
            the channel quantum numbers
        partial : int, optional
            the optional partial index
        symbol : str
            the channel symbol
    """
    def __copy__(self) -> ChannelID:
        ...
    def __deepcopy__(self, arg0: dict) -> ChannelID:
        ...
    def __eq__(self, arg0: ChannelID) -> bool:
        ...
    def __ge__(self, arg0: ChannelID) -> bool:
        ...
    def __gt__(self, arg0: ChannelID) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, reaction: ReactionID, quantum_numbers: ..., partial: int | None = None) -> None:
        """
        Initialise the channel identifier with a reaction and quantum numbers
        """
    @typing.overload
    def __init__(self, symbol: str) -> None:
        """
        Initialise the channel identifier from a symbol string
        """
    def __le__(self, arg0: ChannelID) -> bool:
        ...
    def __lt__(self, arg0: ChannelID) -> bool:
        ...
    def __ne__(self, arg0: ChannelID) -> bool:
        ...
    def __str__(self) -> str:
        """
        Convenience function for printing the identifier
        """
    @property
    def partial(self) -> int | None:
        """
        The partial number (if defined)
        """
    @property
    def quantum_numbers(self) -> ...:
        """
        The quantum numbers
        """
    @property
    def reaction(self) -> ReactionID:
        """
        The reaction
        """
    @property
    def symbol(self) -> str:
        """
        The channel identifier's symbol
        """
class ElectronSubshellID:
    """
    The electron subshell identifier, with associated symbol and aliases
    
    Parameters
    ----------
        number : int 
            the subshell number
        string : str 
            the subshell symbol, name or alternative name
    
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
    def __copy__(self) -> ElectronSubshellID:
        ...
    def __deepcopy__(self, arg0: dict) -> ElectronSubshellID:
        ...
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
        Initialise the subshell identifier using the subshell number
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the subshell identifier using the subshell symbol, name or alternative name
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
    def azimuthal_quantum_number(self) -> int:
        """
        The subshell azimuthal quantum number
        """
    @property
    def is_non_relativistic(self) -> bool:
        """
        Flag to indicate whether or not the subshell identifier is non-relativistic
        """
    @property
    def is_relativistic(self) -> bool:
        """
        Flag to indicate whether or not the subshell identifier is relativistic
        """
    @property
    def mt(self) -> int | None:
        """
        The subshell mt number (if defined)
        """
    @property
    def principal_quantum_number(self) -> int:
        """
        The subshell principal quantum number
        """
    @property
    def symbol(self) -> str:
        """
        The subshell symbol
        """
    @property
    def total_angular_momentum(self) -> float | None:
        """
        The subshell total angular momentum
        """
class ElementID:
    """
    The element identifier, with associated element symbol, name and aliases
    
    Comparison operators are provided using the logical order given by the
    element number.
    
    Parameters
    ----------
        number : int
            the element number
        string : str
            the element symbol, name or alternative name
    """
    def __copy__(self) -> ElementID:
        ...
    def __deepcopy__(self, arg0: dict) -> ElementID:
        ...
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
        Initialise the element identifier using an element number
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the element identifier using an element symbol, name or alternative name
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
class EnergyGroup:
    """
    An energy group defined by two energy values
    
    Parameters
    ----------
        lower : float
            the lower energy value of the group
        upper : float
            the upper energy value of the group
    """
    def __copy__(self) -> EnergyGroup:
        ...
    def __deepcopy__(self, arg0: dict) -> EnergyGroup:
        ...
    def __eq__(self, arg0: EnergyGroup) -> bool:
        ...
    def __ge__(self, arg0: EnergyGroup) -> bool:
        ...
    def __gt__(self, arg0: EnergyGroup) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    def __init__(self, lower: float, upper: float) -> None:
        """
        Initialise the energy group
        """
    def __le__(self, arg0: EnergyGroup) -> bool:
        ...
    def __lt__(self, arg0: EnergyGroup) -> bool:
        ...
    def __ne__(self, arg0: EnergyGroup) -> bool:
        ...
    @property
    def lower_energy(self) -> float:
        """
        The lower energy value
        """
    @property
    def upper_energy(self) -> float:
        """
        The upper energy value
        """
class LevelID:
    """
    The excited state or level identifier
    
    Comparison operators are provided using the logical order given by the
    level number.
    
    Parameters
    ----------
        number : int
            the level number
        string : str
            the level symbol
    """
    all: typing.ClassVar[int] = 999
    continuum: typing.ClassVar[int] = 998
    def __copy__(self) -> LevelID:
        ...
    def __deepcopy__(self, arg0: dict) -> LevelID:
        ...
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
        Initialise the level identifier using a level number
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the level identifier using a level symbol
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
    The particle identifier, with associated symbol and aliases
    
    Comparison operators are provided using the logical order given by the
    element number.
    
    For more information on how to create instances of ParticleID, see the
    Jupyter notebook dryad-identifiers.ipynb under python/examples.
    
    Parameters
    ----------
        element_identifier : njoy.dryad.id.ElementID 
               the particle element 
        mass : int 
               the particle mass number 
        level_identifier : njoy.dryad.id.LevelID 
               he particle level 
        vacancy_identifier : njoy.dryad.id.ElectronSubshellID 
            the identifier of the subshell with an electron vacancy 
        vacancy_identifiers : list of njoy.dryad.id.ElectronSubshellID 
            the identifiers of the subshells with electron vacancies 
        string : str 
            Initialise the particle identifier with the particle symbol, name or alternative 
    
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
    def nuclide(za: int, level: int = 0) -> ParticleID:
        """
        Create a particle identifier for a nuclide
        
        Parameters
        ----------
            za : int 
                the za number of the nuclide 
            level : int, default 0 
                the level number of the nuclide. the default value 0 indicates the ground state
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
    def __copy__(self) -> ParticleID:
        ...
    def __deepcopy__(self, arg0: dict) -> ParticleID:
        ...
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
    def __init__(self, element_identifier: ElementID, mass: int, level_identifier: LevelID) -> None:
        """
        Initialise a nuclear particle identifier with a level number
        """
    @typing.overload
    def __init__(self, element_identifier: ElementID, vacancy_identifier: ElectronSubshellID) -> None:
        """
        Initialise the particle identifier for an atom with a single electron vacancy
        """
    @typing.overload
    def __init__(self, element_identifier: ElementID, vacancy_identifiers: list[ElectronSubshellID]) -> None:
        """
        Initialise the particle identifier for an atom with multiple electron vacancies
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the particle identifier with the particle symbol, name or alternative
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
    def ground_state(self) -> ParticleID:
        """
        Return the identifier for the particle's ground state
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
    def symbol(self) -> str:
        """
        The particle's symbol
        """
    @property
    def vacancies(self) -> list[ElectronSubshellID] | None:
        """
        The identifiers of the subshells that have vacancies
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
class ReactionID:
    """
    The reaction identifier, with associated symbols, aliases, particles, etc.
    
    Parameters
    ----------
        projectile : njoy.dryad.id.ParticleID
            the projectile
        target : njoy.dryad.id.ParticleID
            the target
        type : njoy.dryad.id.ReactionType or int or str
            the reaction type, mt number, or string representing the reaction type
        symbol : str
            the reaction symbol
    """
    def __copy__(self) -> ReactionID:
        ...
    def __deepcopy__(self, arg0: dict) -> ReactionID:
        ...
    def __eq__(self, arg0: ReactionID) -> bool:
        ...
    def __ge__(self, arg0: ReactionID) -> bool:
        ...
    def __gt__(self, arg0: ReactionID) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, projectile: ParticleID, target: ParticleID, type: ReactionType) -> None:
        """
        Initialise the reaction identifier with a projectile, target and reaction type
        """
    @typing.overload
    def __init__(self, projectile: ParticleID, target: ParticleID, mt: int) -> None:
        """
        Initialise the reaction identifier with a projectile, target and mt number
        """
    @typing.overload
    def __init__(self, projectile: ParticleID, target: ParticleID, type: str) -> None:
        """
        Initialise the reaction identifier with an reaction type string
        """
    @typing.overload
    def __init__(self, symbol: str) -> None:
        """
        Initialise the reaction identifier from a symbol string
        """
    def __le__(self, arg0: ReactionID) -> bool:
        ...
    def __lt__(self, arg0: ReactionID) -> bool:
        ...
    def __ne__(self, arg0: ReactionID) -> bool:
        ...
    def __str__(self) -> str:
        """
        Convenience function for printing the identifier
        """
    @property
    def interaction_type(self) -> njoy.dryad.InteractionType:
        """
        The interaction type (nuclear or atomic) associated to the reaction
        """
    @property
    def is_compatible_with_endf(self) -> bool:
        """
        Flag to indicate whether or not the reaction is compatible with ENDF
        """
    @property
    def mt(self) -> int | None:
        """
        The reaction's mt number (if defined)
        """
    @property
    def particles(self) -> dict[ParticleID, int] | None:
        """
        The outgoing particles (excluding the residual)
        """
    @property
    def projectile(self) -> ParticleID:
        """
        The projectile
        """
    @property
    def reaction_type(self) -> ReactionType:
        """
        The reaction type associated to the reaction
        """
    @property
    def residual(self) -> ParticleID | None:
        """
        The residual
        """
    @property
    def symbol(self) -> str:
        """
        The reaction identifier's symbol
        """
    @property
    def target(self) -> ParticleID:
        """
        The target
        """
class ReactionType:
    """
    The reaction types, with associated symbol, aliases, particles, etc.
    
    The ReactionType can be used to identify reaction types. For the moment, only
    registered types can be used. In the future, we will extend this so that users
    can create types other than the ones currently registered.
    
    For more information on how to create instances of ReactionType, see the
    Jupyter notebook dryad-identifiers.ipynb under python/examples.
    
    Parameters
    ----------
        mt : int
            the mt number
        projectile : njoy.dryad.id.ParticleID
            the projectile
        level : int, default=0
            the level number of the target or residual
        particles : dict
            the outgoing particles (excluding the residual)
        string : str
            the reaction type string
    """
    @staticmethod
    def elastic(projectile: ParticleID, level: int = 0) -> ReactionType:
        """
        The elastic reaction type
        
        Parameters
        ----------
            projectile : njoy.dryad.id.ParticleID
                the projectile
            level : int, default=0
                the level number of the target
        """
    @staticmethod
    def size() -> int:
        """
        The number of currently registered types
        """
    @staticmethod
    def total(type: njoy.dryad.InteractionType = ...) -> ReactionType:
        """
        The total reaction type
        
        Parameters
        ----------
            type : njoy.dryad.InteractionType, default=InteractionType.Nuclear
                the interaction type (nuclear or atomic)
        """
    def __copy__(self) -> ReactionType:
        ...
    def __deepcopy__(self, arg0: dict) -> ReactionType:
        ...
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
        Initialise the reaction type using an mt number
        """
    @typing.overload
    def __init__(self, projectile: ParticleID, mt: int, level: int = 0) -> None:
        """
        Initialise the reaction type using a projectile and level number
        """
    @typing.overload
    def __init__(self, particles: dict[ParticleID, int], level: int) -> None:
        """
        Initialise the reaction type using outgoing particles and a level
        """
    @typing.overload
    def __init__(self, string: str) -> None:
        """
        Initialise the reaction type from a string
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
        
        Parameters
        ----------
            projectile : njoy.dryad.id.ParticleID
                the projectile
            target : njoy.dryad.id.ParticleID
                the target
        """
    @property
    def interaction_type(self) -> njoy.dryad.InteractionType:
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
        The reaction type's mt number
        """
    @property
    def particles(self) -> dict[ParticleID, int] | None:
        """
        The reaction type's outgoing particles
        """
    @property
    def symbol(self) -> str:
        """
        The reaction type's symbol
        """
