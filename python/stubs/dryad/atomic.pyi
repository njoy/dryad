"""
Atomic relaxation data components
"""
from __future__ import annotations
import dryad.id
import typing
__all__ = ['ElectronSubshellConfiguration', 'NonRadiativeTransitionData', 'RadiativeTransitionData', 'TransitionType']
class ElectronSubshellConfiguration:
    """
    Electron subshell configuration information
    
    This class contains the following information for an electron subshell:
      - the subshell identifier (K, L1, L2, L3, etc.)
      - the subshell binding energy (in eV)
      - the electron population, i.e. the number of electrons in the subshell
        when the atom is neutral (given as a floating point number)
      - the decay modes or transitions that can fill a hole in this shell
    
    If there are transitions defined, the transition probabilities are
    can be normalised to 1 upon construction.
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: ElectronSubshellConfiguration) -> bool:
        ...
    @typing.overload
    def __init__(self, id: dryad.id.ElectronSubshellID, energy: float, population: float) -> None:
        """
        Initialise the subshell configuration
        
        Arguments:
            self           the subshell configuration data
            id             the electron subshell identifier
            energy         the electron subshell binding energy
            population     the electron subshell population when the atom is neutral
        """
    @typing.overload
    def __init__(self, id: dryad.id.ElectronSubshellID, energy: float, population: float, radiative: list[RadiativeTransitionData], non_radiative: list[NonRadiativeTransitionData], normalise: bool = False) -> None:
        """
        Initialise the subshell configuration
        
        Arguments:
            self           the subshell configuration data
            id             the electron subshell identifier
            energy         the electron subshell binding energy
            population     the electron subshell population when the atom is neutral
            radiative      the radiative transitions that are available
            nonradiative   the non-radiative transitions that are available
            normalise      option to indicate whether or not to normalise
                           all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: ElectronSubshellConfiguration) -> bool:
        ...
    def normalise(self) -> None:
        """
        Normalise the transition probabilities
        """
    @property
    def binding_energy(self) -> float:
        """
        The electron subshell binding energy
        """
    @binding_energy.setter
    def binding_energy(self, arg1: float) -> None:
        ...
    @property
    def has_non_radiative_transitions(self) -> bool:
        """
        Flag to indicate whether or not non-radiative transitions are available
        """
    @property
    def has_radiative_transitions(self) -> bool:
        """
        Flag to indicate whether or not radiative transitions are available
        """
    @property
    def has_transitions(self) -> bool:
        """
        Flag to indicate whether or not transitions are available
        """
    @property
    def identifier(self) -> dryad.id.ElectronSubshellID:
        """
        The electron subshell identifier
        """
    @property
    def non_radiative_transitions(self) -> list[NonRadiativeTransitionData]:
        """
        The available non-radiative transitions to this subshell
        """
    @non_radiative_transitions.setter
    def non_radiative_transitions(self, arg1: list[NonRadiativeTransitionData]) -> None:
        ...
    @property
    def number_non_radiative_transitions(self) -> int:
        """
        The number of available non-radiative transitions
        """
    @property
    def number_radiative_transitions(self) -> int:
        """
        The number of available radiative transitions
        """
    @property
    def number_transitions(self) -> int:
        """
        The number of available transitions
        """
    @property
    def population(self) -> float:
        """
        The electron subshell population when the atom is neutral
        """
    @population.setter
    def population(self, arg1: float) -> None:
        ...
    @property
    def radiative_transitions(self) -> list[RadiativeTransitionData]:
        """
        The available radiative transitions to this subshell
        """
    @radiative_transitions.setter
    def radiative_transitions(self, arg1: list[RadiativeTransitionData]) -> None:
        ...
    @property
    def total_non_radiative_probability(self) -> float:
        """
        The total non-radiative probability
        """
    @property
    def total_radiative_probability(self) -> float:
        """
        The total radiative probability
        """
class NonRadiativeTransitionData:
    """
    A non-radiative transition in atomic relaxation
    
    In a non-radiative transition, an electron from another shell fills a
    vacancy in the current shell while another electron () is emitted. The
    energy of the emitted electron is equal to the binding energy of the
    subshell with the vacancy minus the binding energy of the subshell from
    which the electron filling the vacancy originated from and the subshell
    from which the emitted electron came from.
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: NonRadiativeTransitionData) -> bool:
        ...
    @typing.overload
    def __init__(self, originating_shell: dryad.id.ElectronSubshellID, emitting_shell: dryad.id.ElectronSubshellID, probability: float) -> None:
        """
        Initialise the non-radiative transition data without transition energy
        
        Arguments:
            self                the radiative transition data
            originating_shell   the identifier of the subshell from which the
                                vacancy filling electron originated
            emitting_shell      the identifier of the subshell from which the
                                emitted electron originated
            probability         the probability of the transition
        """
    @typing.overload
    def __init__(self, originating_shell: dryad.id.ElectronSubshellID, emitting_shell: dryad.id.ElectronSubshellID, probability: float, energy: float) -> None:
        """
        Initialise the non-radiative transition data with transition energy
        
        Arguments:
            self                the radiative transition data
            originating_shell   the identifier of the subshell from which the
                                vacancy filling electron originated
            emitting_shell      the identifier of the subshell from which the
                                emitted electron originated
            probability         the probability of the transition
            energy              the energy of the emitted electron
        """
    def __ne__(self, arg0: NonRadiativeTransitionData) -> bool:
        ...
    @property
    def emitting_shell(self) -> dryad.id.ElectronSubshellID:
        """
        The identifier of the subshell from which the emitted electron originated
        """
    @property
    def energy(self) -> float | None:
        """
        The energy of the emitted electron
        """
    @energy.setter
    def energy(self, arg1: float | None) -> None:
        ...
    @property
    def originating_shell(self) -> dryad.id.ElectronSubshellID:
        """
        The identifier of the subshell from which the electron filling the vacancy originated
        """
    @property
    def probability(self) -> float:
        """
        The transition probability
        """
    @probability.setter
    def probability(self, arg1: float) -> None:
        ...
    @property
    def type(self) -> TransitionType:
        """
        The transition type
        """
class RadiativeTransitionData:
    """
    A radiative transition in atomic relaxation
    
    In a radiative transition, an electron from another shell fills a
    vacancy in the current shell while emitting a photon. The energy of
    the emitted photon is equal to the difference in binding energies
    between the subshell with the vacancy and the subshell from which the
    electron filling the vacancy originated from.
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: RadiativeTransitionData) -> bool:
        ...
    @typing.overload
    def __init__(self, originating_shell: dryad.id.ElectronSubshellID, probability: float) -> None:
        """
        Initialise the radiative transition data without transition energy
        
        Arguments:
            self                the radiative transition data
            originating_shell   the identifier of the subshell from which the
                                vacancy filling electron originated
            probability         the probability of the transition
        """
    @typing.overload
    def __init__(self, originating_shell: dryad.id.ElectronSubshellID, probability: float, energy: float) -> None:
        """
        Initialise the radiative transition data with transition energy
        
        Arguments:
            self                the radiative transition data
            originating_shell   the identifier of the subshell from which the
                                vacancy filling electron originated
            probability         the probability of the transition
            energy              the energy of the emitted photon
        """
    def __ne__(self, arg0: RadiativeTransitionData) -> bool:
        ...
    @property
    def energy(self) -> float | None:
        """
        The energy of the emitted photon
        """
    @energy.setter
    def energy(self, arg1: float | None) -> None:
        ...
    @property
    def originating_shell(self) -> dryad.id.ElectronSubshellID:
        """
        The identifier of the subshell from which the electron filling the vacancy originated
        """
    @property
    def probability(self) -> float:
        """
        The transition probability
        """
    @probability.setter
    def probability(self, arg1: float) -> None:
        ...
    @property
    def type(self) -> TransitionType:
        """
        The transition type
        """
class TransitionType:
    """
    The type of transition in an atomic relaxation
    
    Members:
    
      Radiative
    
      NonRadiative
    """
    NonRadiative: typing.ClassVar[TransitionType]  # value = <TransitionType.NonRadiative: 1>
    Radiative: typing.ClassVar[TransitionType]  # value = <TransitionType.Radiative: 0>
    __members__: typing.ClassVar[dict[str, TransitionType]]  # value = {'Radiative': <TransitionType.Radiative: 0>, 'NonRadiative': <TransitionType.NonRadiative: 1>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
