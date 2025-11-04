"""
Resonance data
"""
from __future__ import annotations
import dryad
import dryad.id
import typing
__all__: list[str] = ['BoundaryCondition', 'Channel', 'ChannelQuantumNumbers', 'ChannelRadii', 'CompoundSystem', 'CoulombPenetrability', 'CoulombPhaseShift', 'CoulombPhaseShiftDifference', 'CoulombShiftFactor', 'Formalism', 'HardSpherePenetrability', 'HardSpherePhaseShift', 'HardSphereShiftFactor', 'Kinematics', 'Particle', 'ParticlePair', 'ResonanceParameters', 'ResonanceTable', 'SpinGroup', 'TabulatedRadius', 'TabulatedWaveFunction']
class BoundaryCondition:
    """
    The boundary condition options
    
    Members:
    
      ShiftFactor
    
      Constant
    """
    Constant: typing.ClassVar[BoundaryCondition]  # value = <BoundaryCondition.Constant: 2>
    ShiftFactor: typing.ClassVar[BoundaryCondition]  # value = <BoundaryCondition.ShiftFactor: 1>
    __members__: typing.ClassVar[dict[str, BoundaryCondition]]  # value = {'ShiftFactor': <BoundaryCondition.ShiftFactor: 1>, 'Constant': <BoundaryCondition.Constant: 2>}
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
class Channel:
    """
    A resonance reaction channel
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: Channel) -> bool:
        ...
    @typing.overload
    def __init__(self, identifier: dryad.id.ChannelID, incident: ParticlePair, outgoing: ParticlePair | None, q_value: float, boundary: float | None, radii: ChannelRadii, wave_number: ... | ..., penetrability: float | HardSpherePenetrability | CoulombPenetrability | TabulatedWaveFunction, shift_factor: float | HardSphereShiftFactor | CoulombShiftFactor | TabulatedWaveFunction, phase_shift: float | HardSpherePhaseShift | CoulombPhaseShift | TabulatedWaveFunction, phase_shift_difference: float | CoulombPhaseShiftDifference) -> None:
        """
        Initialise the channel
        
        Arguments:
            self                     the channel
            identifier               the channel identifier
            incident                 the current incident particle pair
            outgoing                 the outgoing particle pair
            q_value                  the Q value associated with the transition from
                                     the incident to the outgoing particle pair
            boundary                 the boundary condition
            radii                    the channel radii for the calculation of the
                                     wave functions
            wave_number              the wave number of the channel
            penetrability            the penetrability of the channel
            shift_factor             the shift factor of the channel
            phase_shift              the phase shift of the channel
            phase_shift_difference   the phase shift difference of the channel
        """
    @typing.overload
    def __init__(self, identifier: dryad.id.ChannelID, incident: ParticlePair, outgoing: ParticlePair | None, qValue: float, boundary: float | None, radii: ChannelRadii, kinematics: Kinematics = ...) -> None:
        """
        Initialise the channel
        
        Arguments:
            self         the channel
            identifier   the channel identifier
            incident     the current incident particle pair
            outgoing     the outgoing particle pair
            q_value      the Q value associated with the transition from
                         the incident to the outgoing particle pair
            boundary     the boundary condition
            radii        the channel radii for the calculation of the
                         wave functions
            kinematics   the kinematics type applied to the channel (default is
                         non-relativistic)
        """
    @typing.overload
    def __init__(self, instance: Channel) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: Channel) -> bool:
        ...
    def is_below_threshold(self, energy: float) -> bool:
        """
        Return whether or not the energy is below the threshold for this channel
        
        The incident energy is below the threshold energy for the channel if
            energy * ratio + q < 0.0
        where energy is the incident energy, ratio is the mass ratio M / ( m + M )
        for the incident particle pair and q is the Q value for this channel.
        
        Arguments:
            self     the channel
            energy   the energy to be tested
        """
    def penetrability(self, energy: float) -> float:
        """
        Calculate the penetrability for the channel at a given energy
        
        Arguments:
            self     the channel
            energy   the energy (given in eV)
        """
    def phase_shift(self, energy: float) -> float:
        """
        Calculate the phase shift for the channel at a given energy
        
        Arguments:
            self     the channel
            energy   the energy (given in eV)
        """
    def phase_shift_difference(self, energy: float) -> float:
        """
        Calculate the phase shift difference for the channel at a given energy
        
        Arguments:
            self     the channel
            energy   the energy (given in eV)
        """
    def shift_factor(self, energy: float) -> float:
        """
        Calculate the shift factor for the channel at a given energy
        
        Arguments:
            self     the channel
            energy   the energy (given in eV)
        """
    def sommerfeld_parameter(self, energy: float) -> float:
        """
        Calculate the Sommerfeld parameter for the channel at a given energy
        
        The Sommerfeld parameter eta is an energy dependent quantity defined as
        follows:
           eta = z * Z * mu / ( 4 * pi * epsilon0 * hbar^2 * k )
        in which z and Z are the electrical charge of the particles in the
        particle pair, mu is the reduced mass of the particle pair, hbar is the
        Planck constant, k is the wave number and epsilon0 is the vacuum
        permittivity.
        
        Arguments:
            self     the channel
            energy   the energy (given in eV)
        """
    def wave_number(self, energy: float) -> float:
        """
        Calculate the channel wave number (given in fm^-1) at a given energy
        
        Arguments:
            self     the channel
            energy   the energy (given in eV)
        """
    @property
    def boundary_condition(self) -> float | None:
        """
        The boundary condition value (if defined)
        """
    @property
    def channel_radii(self) -> ChannelRadii:
        """
        The channel radii
        """
    @property
    def identifier(self) -> dryad.id.ChannelID:
        """
        The channel identifier
        """
    @property
    def incident_particle_pair(self) -> ParticlePair:
        """
        The incident particle pair
        """
    @property
    def is_incident_channel(self) -> bool:
        """
        Flag to indicate whether or not the channel is an incident channel
        """
    @property
    def kinematics_type(self) -> Kinematics:
        """
        The kinematics type applied to the channel
        """
    @property
    def outgoing_particle_pair(self) -> ParticlePair | None:
        """
        The outgoing particle pair (if defined)
        """
    @property
    def q_value(self) -> float:
        """
        The q value of the transition
        """
    @property
    def quantum_numbers(self) -> ChannelQuantumNumbers:
        """
        The quantum numbers of the channel
        """
    @property
    def reaction(self) -> dryad.id.ReactionID:
        """
        The reaction this channel contributes to
        """
    @property
    def statistical_spin_factor(self) -> float:
        """
        The statistical spin factor
        
        The statistical spin factor g of a channel is defined as follows:
           g = ( 2 * J + 1 ) / ( 2 * ia + 1 ) / ( 2 * ib + 1 )
        in which J is the total angular momentum of the channel and ia and ib
        are the spins of the particles in the outgoing particle pair.
        """
class ChannelQuantumNumbers:
    """
    The l,S,Jpi quantum numbers of a reaction channel
    
    The ChannelQuantumNumbers class contains the quantum numbers associated to
    a given reaction channel. Only channels that have the same Jpi contribute
    to the cross section for a spin group.
    
    When using comparison on the quantum numbers, we use a Jpi,l,s ordering.
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def allowed_channel_quantum_numbers(i: float, I: float, lmax: int) -> list[ChannelQuantumNumbers]:
        """
        Calculate possible combinations of channel quantum numbers
        
        Arguments:
            i      the spin of the incident particle
            I      the spin of the target nucleus
            lmax   the max value of the orbital angular momentum
        """
    @staticmethod
    def allowed_channel_spin_values(i: float, I: float) -> list[float]:
        """
        Calculate allowed values for the channel spin s
        
        The channel spin s can only have values between abs(i - I) and i + I
        where i is the spin of the incident particle (for a neutron that
        would be 0.5) and I is the spin of the target nucleus.
        
        Arguments:
            i   the spin of the incident particle
            I   the spin of the target nucleus
        """
    @staticmethod
    @typing.overload
    def allowed_total_angular_momentum_values(l: int, i: float, I: float) -> list[float]:
        """
        Calculate possible values for the total angular momentum J
        
        Arguments:
            l   the orbital angular momentum
            i   the spin of the incident particle
            I   the spin of the target nucleus
        """
    @staticmethod
    @typing.overload
    def allowed_total_angular_momentum_values(l: int, s: float) -> list[float]:
        """
        Calculate possible values for the total angular momentum J
        
        The total angular momentum J for a channel can only have values between
        abs(l - s) and l + s where l is the orbital momentum of the incoming wave
        and s is the channel spin (which in turn depends on the spin i of the
        incident particle and spin I of the target nucleus).
        
        Arguments:
            l   the orbital angular momentum
            s   the channel spin
        """
    def __eq__(self, arg0: ChannelQuantumNumbers) -> bool:
        ...
    def __ge__(self, arg0: ChannelQuantumNumbers) -> bool:
        ...
    def __gt__(self, arg0: ChannelQuantumNumbers) -> bool:
        ...
    @typing.overload
    def __init__(self, l: int, s: float, J: float, parity: int) -> None:
        """
        Initialise the channel quantum numbers
        
        Arguments:
            self     the quantum numbers
            l        the orbital angular momentum
            s        the channel spin
            J        the total angular momentum
            parity   the parity
        """
    @typing.overload
    def __init__(self, symbol: str) -> None:
        """
        Initialise the channel qunatum numbers
        
        Arguments:
            self     the quantum numbers
            symbol   the quantum numbers symbol
        """
    @typing.overload
    def __init__(self, instance: ChannelQuantumNumbers) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __le__(self, arg0: ChannelQuantumNumbers) -> bool:
        ...
    def __lt__(self, arg0: ChannelQuantumNumbers) -> bool:
        ...
    def __ne__(self, arg0: ChannelQuantumNumbers) -> bool:
        ...
    @property
    def orbital_angular_momentum(self) -> int:
        """
        The orbital angular momentum l of the channel
        """
    @property
    def parity(self) -> int:
        """
        The parity
        """
    @property
    def spin(self) -> float:
        """
        The channel spin
        """
    @property
    def total_angular_momentum(self) -> float:
        """
        The total angular momentum J of the channels
        """
class ChannelRadii:
    """
    Channel radii used in wave function calculations
    
    The penetrability P, shift factor S and phase shift phi require knowledge
    of the channel radius in their calculation. The ChannelRadii class provides
    these radii for each one of these.
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: ChannelRadii) -> bool:
        ...
    @typing.overload
    def __init__(self, radius: float | TabulatedRadius) -> None:
        """
        Initialise the channel radii
        
        Arguments:
            self     the radii
            radius   the channel radius to be used for P, S and phi
        """
    @typing.overload
    def __init__(self, true_radius: float | TabulatedRadius, effective_radius: float | TabulatedRadius) -> None:
        """
        Initialise the channel radii
        
        Arguments:
            self               the radii
            true_radius        the channel radius to be used for P and S
            effective_radius   the channel radius to be used for phi
        """
    @typing.overload
    def __init__(self, penetrability: float | TabulatedRadius, shift_factor: float | TabulatedRadius, phase_shift: float | TabulatedRadius) -> None:
        """
        Initialise the channel radii
        
        Arguments:
            self                  the radii
            penetrability         the channel radius to be used for P
            shift_factor          the channel radius to be used for S
            phase_shift           the channel radius to be used for phi
        """
    @typing.overload
    def __init__(self, instance: ChannelRadii) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: ChannelRadii) -> bool:
        ...
    def calculate_penetrability_radius(self, energy: float) -> float:
        """
        Return the channel radius for the penetrability P
        
        Arguments:
            self     the radii
            energy   the energy for which the radius must be given
        """
    def calculate_phase_shift_radius(self, energy: float) -> float:
        """
        Return the channel radius for the phase shift phi
        
        Arguments:
            self     the radii
            energy   the energy for which the radius must be given
        """
    def calculate_shift_factor_radius(self, energy: float) -> float:
        """
        Return the channel radius for the shift factor S
        
        Arguments:
            self     the radii
            energy   the energy for which the radius must be given
        """
    @property
    def has_phase_shift_radius(self) -> bool:
        """
        Flag indicating whether or not a phase shift radius is defined
        """
    @property
    def has_shift_factor_radius(self) -> bool:
        """
        Flag indicating whether or not a shift factor radius is defined
        """
    @property
    def penetrability_radius(self) -> float | TabulatedRadius:
        """
        The penetrability radius
        """
    @penetrability_radius.setter
    def penetrability_radius(self, arg1: float | TabulatedRadius) -> None:
        ...
    @property
    def phase_shift_radius(self) -> float | TabulatedRadius | None:
        """
        The phase shift radius
        """
    @phase_shift_radius.setter
    def phase_shift_radius(self, arg1: float | TabulatedRadius | None) -> None:
        ...
    @property
    def shift_factor_radius(self) -> float | TabulatedRadius | None:
        """
        The shift factor radius
        """
    @shift_factor_radius.setter
    def shift_factor_radius(self, arg1: float | TabulatedRadius | None) -> None:
        ...
class CompoundSystem:
    """
    The compound nucleus system
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: CompoundSystem) -> bool:
        ...
    @typing.overload
    def __init__(self, lower_energy: float, upper_energy: float, spin_groups: list[SpinGroup]) -> None:
        """
        Initialise the spin group
        
        Arguments:
            self           the compound system
            lower_energy   the lower energy limit for the compound system
            upper_energy   the upper energy limit for the compound system
            spin_groups    the spin groups that make up the compound system
        """
    @typing.overload
    def __init__(self, instance: CompoundSystem) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: CompoundSystem) -> bool:
        ...
    def cross_sections(self, energy: float) -> dict[dryad.id.ReactionID, float]:
        """
        Calculate the cross section values at a given energy
        
        Arguments:
            self     the spin group
            energy   the energy
        """
    @property
    def lower_energy_limit(self) -> float:
        """
        The lower energy limit
        """
    @lower_energy_limit.setter
    def lower_energy_limit(self, arg1: float) -> None:
        ...
    @property
    def spin_groups(self) -> list[SpinGroup]:
        """
        The spin groups that make up the compound system
        """
    @spin_groups.setter
    def spin_groups(self, arg1: list[SpinGroup]) -> None:
        ...
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit
        """
    @upper_energy_limit.setter
    def upper_energy_limit(self, arg1: float) -> None:
        ...
class CoulombPenetrability:
    """
    Coulomb penetrability functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, ratio: float, eta: float) -> float:
        """
        Evaluate the penetrability for a given ratio and eta value
        
        Arguments:
            self    the penetrability function
            ratio   the ratio value
            eta     the eta value
        """
    def __eq__(self, arg0: CoulombPenetrability) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_angular_momentum: int) -> None:
        """
        Initialise the Coulomb penetrability function
        
        Arguments:
            self                       the function
            orbital_angular_momentum   the value of the orbital momentum
        """
    @typing.overload
    def __init__(self, instance: CoulombPenetrability) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: CoulombPenetrability) -> bool:
        ...
    @property
    def orbital_angular_momentum(self) -> int:
        """
        The value of the orbital angular momentum
        """
class CoulombPhaseShift:
    """
    Coulomb phase shift functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, ratio: float, eta: float) -> float:
        """
        Evaluate the phase shift for a given ratio and eta value
        
        Arguments:
            self    the phase shift function
            ratio   the ratio value
            eta     the eta value
        """
    def __eq__(self, arg0: CoulombPhaseShift) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_angular_momentum: int) -> None:
        """
        Initialise the Coulomb phase shift function
        
        Arguments:
            self                       the function
            orbital_angular_momentum   the value of the orbital momentum
        """
    @typing.overload
    def __init__(self, instance: CoulombPhaseShift) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: CoulombPhaseShift) -> bool:
        ...
    @property
    def orbital_angular_momentum(self) -> int:
        """
        The value of the orbital angular momentum
        """
class CoulombPhaseShiftDifference:
    """
    Coulomb phase shift difference functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, eta: float) -> float:
        """
        Evaluate the phase shift difference for a given eta value
        
        Arguments:
            self    the phase shift function
            eta     the eta value
        """
    def __eq__(self, arg0: CoulombPhaseShiftDifference) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_angular_momentum: int) -> None:
        """
        Initialise the Coulomb phase shift difference function
        
        Arguments:
            self                       the function
            orbital_angular_momentum   the value of the orbital momentum
        """
    @typing.overload
    def __init__(self, instance: CoulombPhaseShiftDifference) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: CoulombPhaseShiftDifference) -> bool:
        ...
    @property
    def orbital_angular_momentum(self) -> int:
        """
        The value of the orbital angular momentum
        """
class CoulombShiftFactor:
    """
    Coulomb shift factor functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, ratio: float, eta: float) -> float:
        """
        Evaluate the shift factor for a given ratio and eta value
        
        Arguments:
            self    the shift factor function
            ratio   the ratio value
            eta     the eta value
        """
    def __eq__(self, arg0: CoulombShiftFactor) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_angular_momentum: int) -> None:
        """
        Initialise the Coulomb shift factor function
        
        Arguments:
            self                       the function
            orbital_angular_momentum   the value of the orbital momentum
        """
    @typing.overload
    def __init__(self, instance: CoulombShiftFactor) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: CoulombShiftFactor) -> bool:
        ...
    @property
    def orbital_angular_momentum(self) -> int:
        """
        The value of the orbital angular momentum
        """
class Formalism:
    """
    The resonance formalism
    
    Members:
    
      ReichMoore
    
      GeneralRMatrix
    """
    GeneralRMatrix: typing.ClassVar[Formalism]  # value = <Formalism.GeneralRMatrix: 2>
    ReichMoore: typing.ClassVar[Formalism]  # value = <Formalism.ReichMoore: 1>
    __members__: typing.ClassVar[dict[str, Formalism]]  # value = {'ReichMoore': <Formalism.ReichMoore: 1>, 'GeneralRMatrix': <Formalism.GeneralRMatrix: 2>}
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
class HardSpherePenetrability:
    """
    Hard sphere penetrability functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, ratio: float) -> float:
        """
        Evaluate the penetrability for a given ratio value
        
        Arguments:
            self    the penetrability function
            ratio   the ratio value
        """
    def __eq__(self, arg0: HardSpherePenetrability) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_angular_momentum: int) -> None:
        """
        Initialise the hard sphere penetrability function
        
        Arguments:
            self                       the function
            orbital_angular_momentum   the value of the orbital momentum
        """
    @typing.overload
    def __init__(self, instance: HardSpherePenetrability) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: HardSpherePenetrability) -> bool:
        ...
    @property
    def orbital_angular_momentum(self) -> int:
        """
        The value of the orbital angular momentum
        """
class HardSpherePhaseShift:
    """
    Hard sphere phase shift functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, ratio: float) -> float:
        """
        Evaluate the phase shift for a given ratio value
        
        Arguments:
            self    the phase shift function
            ratio   the ratio value
        """
    def __eq__(self, arg0: HardSpherePhaseShift) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_angular_momentum: int) -> None:
        """
        Initialise the hard sphere phase shift function
        
        Arguments:
            self                       the function
            orbital_angular_momentum   the value of the orbital momentum
        """
    @typing.overload
    def __init__(self, instance: HardSpherePhaseShift) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: HardSpherePhaseShift) -> bool:
        ...
    @property
    def orbital_angular_momentum(self) -> int:
        """
        The value of the orbital angular momentum
        """
class HardSphereShiftFactor:
    """
    Hard sphere shift factor functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, ratio: float) -> float:
        """
        Evaluate the shift factor for a given ratio value
        
        Arguments:
            self    the shift factor function
            ratio   the ratio value
        """
    def __eq__(self, arg0: HardSphereShiftFactor) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_angular_momentum: int) -> None:
        """
        Initialise the hard sphere shift factor function
        
        Arguments:
            self                       the function
            orbital_angular_momentum   the value of the orbital momentum
        """
    @typing.overload
    def __init__(self, instance: HardSphereShiftFactor) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: HardSphereShiftFactor) -> bool:
        ...
    @property
    def orbital_angular_momentum(self) -> int:
        """
        The value of the orbital angular momentum
        """
class Kinematics:
    """
    The kinematics option
    
    Members:
    
      NonRelativistic
    
      Relativistic
    """
    NonRelativistic: typing.ClassVar[Kinematics]  # value = <Kinematics.NonRelativistic: 0>
    Relativistic: typing.ClassVar[Kinematics]  # value = <Kinematics.Relativistic: 1>
    __members__: typing.ClassVar[dict[str, Kinematics]]  # value = {'NonRelativistic': <Kinematics.NonRelativistic: 0>, 'Relativistic': <Kinematics.Relativistic: 1>}
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
class Particle:
    """
    Particle information for resonance reconstruction
    
    The Particle class contains specific information for a particle as used
    during resonance reconstruction. The Particle has an atomic mass, an
    electrical charge, an excited state number, a spin and a parity (which is
    either + or -).
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: Particle) -> bool:
        ...
    @typing.overload
    def __init__(self, id: dryad.id.ParticleID, mass: float, spin: float, parity: int) -> None:
        """
        Initialise the particle information
        
        Arguments:
            self     the particle information
            id       the particle identifier
            mass     the atomic mass
            spin     the channel spin
            parity   the parity
        """
    @typing.overload
    def __init__(self, instance: Particle) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: Particle) -> bool:
        ...
    @property
    def charge(self) -> int:
        """
        The electrical charge of the particle (in units of the elementary charge)
        """
    @property
    def excited_state(self) -> int:
        """
        The excited state number of the particle
        """
    @property
    def identifier(self) -> dryad.id.ParticleID:
        """
        The particle identifier
        """
    @property
    def mass(self) -> float:
        """
        The atomic mass of the particle (in atomic mass units)
        """
    @property
    def parity(self) -> int:
        """
        The parity
        """
    @property
    def spin(self) -> float:
        """
        The particle spin
        """
class ParticlePair:
    """
    Particle information for resonance reconstruction
    
    A ParticlePair represents the two particles involved in a entrance or exit
    reaction channel (we assume that the reaction is a two-body reaction). The
    pair consists of a "light" incident or outgoing particle (e.g. a neutron,
    photon, alpha, etc.) and a "heavy" target or residual nucleus (e.g. H1,
    He4, U235, etc.).
    
    The ParticlePair class gives us access to information related to the
    pair of particles such as the mass ratio and the reduced mass.
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: ParticlePair) -> bool:
        ...
    @typing.overload
    def __init__(self, light_particle: Particle, heavy_particle: Particle) -> None:
        """
        Initialise the particle pair information
        
        Arguments:
            self             the particle pair information
            light_particle   the light particle
            heavy_particle   the heavy particle
        """
    @typing.overload
    def __init__(self, instance: ParticlePair) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: ParticlePair) -> bool:
        ...
    @property
    def heavy_particle(self) -> Particle:
        """
        The heavy particle in the particle pair
        """
    @property
    def light_particle(self) -> Particle:
        """
        The light particle in the particle pair
        """
    @property
    def mass_ratio(self) -> float:
        """
        The mass ratio of the particle pair (dimensionless)
        
        The mass ratio of the two particles is defined as follows:
           ratio = mb / ( ma + mb )
        in which ma and mb are the atomic mass values of the particles
        in the particle pair.
        """
    @property
    def reduced_mass(self) -> float:
        """
        The reduced mass of the particle pair (in atomic mass units)
        
        The reduced mass mu of the two particles is defined as follows:
           mu = ma * mb / ( ma + mb )
        in which ma and mb are the atomic mass values of the particles in the
        particle pair.
        """
class ResonanceParameters:
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: ResonanceParameters) -> bool:
        ...
    def __init__(self, resolved: list[CompoundSystem]) -> None:
        """
        Initialise the resonance parameters
        
        Arguments:
            self       the resonance parameters
            resolved   the resolved resonance compound systems
        """
    def __ne__(self, arg0: ResonanceParameters) -> bool:
        ...
    @property
    def resolved(self) -> list[CompoundSystem]:
        """
        The compound systems that make up the resolved resonance data
        """
    @resolved.setter
    def resolved(self, arg1: list[CompoundSystem]) -> None:
        ...
class ResonanceTable:
    """
    A table of parameters for a set of channels
    
    The table contains level energies and reduced width amplitudes,
    all given as column data.
    """
    __hash__: typing.ClassVar[None] = None
    def __add__(self, arg0: ResonanceTable) -> ResonanceTable:
        ...
    def __eq__(self, arg0: ResonanceTable) -> bool:
        ...
    def __iadd__(self, arg0: ResonanceTable) -> ResonanceTable:
        ...
    @typing.overload
    def __init__(self, channels: list[dryad.id.ChannelID], energies: list[float], amplitudes: list[list[float]]) -> None:
        """
        Initialise the table
        
        The energies and channels do not have to be sorted (they will be sorted
        upon construction).
        
        Arguments:
            self         the table
            channels     the channel identifiers (nc values, at least 1)
            energies     the level energies (ne values, at least 1)
            amplitudes   the reduced width amplitudes (nc arrays of ne values)
        """
    @typing.overload
    def __init__(self, channel: dryad.id.ChannelID, energies: list[float], amplitudes: list[float]) -> None:
        """
        Initialise the table
        
        The energies do not have to be sorted (they will be sorted upon construction).
        
        Arguments:
            self         the table
            channel      the channel identifier
            energies     the level energies
            amplitudes   the reduced width amplitudes
        """
    @typing.overload
    def __init__(self, instance: ResonanceTable) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: ResonanceTable) -> bool:
        ...
    def has_channel(self, channel: dryad.id.ChannelID) -> bool:
        """
        Return whether or not a channel is present
        
        Arguments:
            self      the table
            channel   the channel identifier
        """
    def has_energy(self, energy: float) -> bool:
        """
        Return whether or not an energy is present
        
        Arguments:
            self     the table
            energy   the energy value
        """
    @property
    def channels(self) -> list[dryad.id.ChannelID]:
        """
        The channel identifiers
        """
    @property
    def energies(self) -> list[float]:
        """
        The level energies
        """
    @property
    def number_channels(self) -> int:
        """
        The number of channels in the table
        """
    @property
    def number_energies(self) -> int:
        """
        The number of level energies in the table
        """
    @property
    def reduced_width_amplitudes(self) -> list[list[float]]:
        """
        The reduced width amplitudes
        """
class SpinGroup:
    """
    A spin group corresponding to a Jpi quantum number set
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: SpinGroup) -> bool:
        ...
    @typing.overload
    def __init__(self, channels: list[Channel], resonances: ResonanceTable, formalism: Formalism, boundary: BoundaryCondition) -> None:
        """
        Initialise the spin group
        
        If the channels are not sorted, they will get sorted through the order
        of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical
        sorting order).
        
        Arguments:
            self         the spin group
            channels     the channels in the spin group
            resonances   the resonance table of the spin group
            formalism    the r matrix formalism option to be applied
            boundary     the boundary condition option to be applied
        """
    @typing.overload
    def __init__(self, channels: list[tuple[Channel, ResonanceTable]], formalism: Formalism, boundary: BoundaryCondition) -> None:
        """
        Initialise the spin group
        
        If the channels are not sorted, they will get sorted through the order
        of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical
        sorting order).
        
        Arguments:
            self       the spin group
            channels   the channel data in the spin group
            formalism    the r matrix formalism option to be applied
            boundary     the boundary condition option to be applied
        """
    @typing.overload
    def __init__(self, instance: SpinGroup) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: SpinGroup) -> bool:
        ...
    def cross_sections(self, energy: float) -> dict[dryad.id.ReactionID, float]:
        """
        Calculate the cross section values at a given energy
        
        Arguments:
            self     the spin group
            energy   the energy
        """
    @property
    def boundary_condition(self) -> BoundaryCondition:
        """
        The boundary condition option
        """
    @property
    def channels(self) -> list[Channel]:
        """
        The channels in the spin group
        """
    @channels.setter
    def channels(self, arg1: list[Channel]) -> None:
        ...
    @property
    def formalism(self) -> Formalism:
        """
        The formalism
        """
    @property
    def parity(self) -> int:
        """
        The parity
        """
    @property
    def reactions(self) -> list[dryad.id.ReactionID]:
        """
        The reactions to which this spin group contributes
        """
    @property
    def resonance_table(self) -> ResonanceTable:
        """
        The resonance table of the spin group
        """
    @resonance_table.setter
    def resonance_table(self, arg1: ResonanceTable) -> None:
        ...
    @property
    def total_angular_momentum(self) -> float:
        """
        The total angular momentum J of the channels
        """
class TabulatedRadius:
    """
    A radius table
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedRadius:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedRadius) -> TabulatedRadius:
        ...
    def __call__(self, energy: float) -> float:
        """
        Evaluate the table for a given energy value
        
        Arguments:
            self      the table
            energy    the energy value
        """
    def __eq__(self, arg0: TabulatedRadius) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedRadius:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedRadius) -> TabulatedRadius:
        ...
    def __imul__(self, arg0: float) -> TabulatedRadius:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[dryad.InterpolationType]) -> None:
        """
        Initialise the radius table
        
        Arguments:
            self           the radius table
            energies       the energy values
            values         the radius values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: dryad.InterpolationType = ...) -> None:
        """
        Initialise the radius table
        
        Arguments:
            self           the radius table
            energies       the energy values
            values         the radius values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, instance: TabulatedRadius) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedRadius:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedRadius) -> TabulatedRadius:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedRadius:
        ...
    def __mul__(self, arg0: float) -> TabulatedRadius:
        ...
    def __ne__(self, arg0: TabulatedRadius) -> bool:
        ...
    def __neg__(self) -> TabulatedRadius:
        ...
    def __radd__(self, arg0: float) -> TabulatedRadius:
        ...
    def __rmul__(self, arg0: float) -> TabulatedRadius:
        ...
    def __rsub__(self, arg0: float) -> TabulatedRadius:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedRadius:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedRadius) -> TabulatedRadius:
        ...
    def __truediv__(self, arg0: float) -> TabulatedRadius:
        ...
    def linearise(self, tolerance: dryad.ToleranceConvergence = ...) -> TabulatedRadius:
        """
        Linearise the table
        
        Arguments:
            self        the table
            tolerance   the linearisation tolerance
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def energies(self) -> list[float]:
        """
        The energy values
        """
    @property
    def interpolants(self) -> list[dryad.InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the table is linearised
        """
    @property
    def lower_energy_limit(self) -> float:
        """
        The lower energy limit
        """
    @property
    def number_points(self) -> int:
        """
        The number of points in the table
        """
    @property
    def number_regions(self) -> int:
        """
        The number of interpolation regions in the table
        """
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit
        """
    @property
    def values(self) -> list[float]:
        """
        The radius values
        """
class TabulatedWaveFunction:
    """
    A tabulated function representing penetrability, shift or phase shift
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedWaveFunction) -> TabulatedWaveFunction:
        ...
    def __call__(self, ratio: float) -> float:
        """
        Evaluate the table for a given ratio value
        
        Arguments:
            self    the table
            ratio   the ratio value
        """
    def __eq__(self, arg0: TabulatedWaveFunction) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedWaveFunction) -> TabulatedWaveFunction:
        ...
    def __imul__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    @typing.overload
    def __init__(self, ratios: list[float], values: list[float], boundaries: list[int], interpolants: list[dryad.InterpolationType]) -> None:
        """
        Initialise the wave function table
        
        Arguments:
            self           the wave function table
            ratios.        the ratio values
            values         the wave function values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, ratios: list[float], values: list[float], interpolant: dryad.InterpolationType = ...) -> None:
        """
        Initialise the radius table
        
        Arguments:
            self           the radius table
            ratios         the ratio values
            values         the wave function values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, instance: TabulatedWaveFunction) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedWaveFunction) -> TabulatedWaveFunction:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    def __mul__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    def __ne__(self, arg0: TabulatedWaveFunction) -> bool:
        ...
    def __neg__(self) -> TabulatedWaveFunction:
        ...
    def __radd__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    def __rmul__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    def __rsub__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedWaveFunction) -> TabulatedWaveFunction:
        ...
    def __truediv__(self, arg0: float) -> TabulatedWaveFunction:
        ...
    def linearise(self, tolerance: dryad.ToleranceConvergence = ...) -> TabulatedWaveFunction:
        """
        Linearise the table
        
        Arguments:
            self        the table
            tolerance   the linearisation tolerance
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def interpolants(self) -> list[dryad.InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the table is linearised
        """
    @property
    def lower_ratio_limit(self) -> float:
        """
        The lower ratio limit
        """
    @property
    def number_points(self) -> int:
        """
        The number of points in the table
        """
    @property
    def number_regions(self) -> int:
        """
        The number of interpolation regions in the table
        """
    @property
    def ratios(self) -> list[float]:
        """
        The ratio values
        """
    @property
    def upper_ratio_limit(self) -> float:
        """
        The upper ratio limit
        """
    @property
    def values(self) -> list[float]:
        """
        The wave function values
        """
