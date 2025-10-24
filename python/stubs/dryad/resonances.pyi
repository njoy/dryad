"""
Resonance data
"""
from __future__ import annotations
import dryad
import typing
__all__: list[str] = ['ChannelQuantumNumbers', 'ChannelRadii', 'CoulombPhaseShiftDifference', 'HardSpherePenetrability', 'HardSpherePhaseShift', 'HardSphereShiftFactor', 'ResonanceParameters', 'TabulatedRadius', 'TabulatedWaveFunction']
class ChannelQuantumNumbers:
    """
    The l,S,Jpi quantum numbers of a reaction channel
    
    The ChannelQuantumNumbers class contains the quantum numbers associated to
    a given reaction channel. Only channels that have the same Jpi contribute
    to the cross section of a given reaction.
    """
    __hash__: typing.ClassVar[None] = None
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
        The total angular momentum J for a channel can only have values between
        abs(abs(l - I) - i) and l + I +i where l is the orbital angular momentum
        of the incoming wave, i is the spin of the incident particle and I is the
        spin of the target nucleus.
        
        Arguments:
            l   the orbital angular momentum
            i   the spin of the incident particle
            I   the spin of the target nucleus
        """
    @staticmethod
    @typing.overload
    def allowed_total_angular_momentum_values(l: int, s: float) -> list[float]:
        """
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
            true_radius        the channel radius to be used for P and S    effective_radius   the channel radius to be used for phi
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
class CoulombPhaseShiftDifference:
    """
    Coulomb phase shift difference functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the phase shift difference for a given eta value
        
        Arguments:
            self    the phase shift function
            eta     the eta value
        """
    def __eq__(self, arg0: CoulombPhaseShiftDifference) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_momentum: int) -> None:
        """
        Initialise the Coulomb phase shift difference function
        
        Arguments:
            self               the function
            orbital_momentum   the value of the orbital momentum
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
class HardSpherePenetrability:
    """
    Hardsphere penetrability functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the penetrability for a given ratio value
        
        Arguments:
            self    the penetrability function
            ratio   the ratio value
        """
    def __eq__(self, arg0: HardSpherePenetrability) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_momentum: int) -> None:
        """
        Initialise the hard sphere penetrability function
        
        Arguments:
            self               the function
            orbital_momentum   the value of the orbital momentum
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
    Hardsphere phase shift functions
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the phase shift for a given ratio value
        
        Arguments:
            self    the phase shift function
            ratio   the ratio value
        """
    def __eq__(self, arg0: HardSpherePhaseShift) -> bool:
        ...
    @typing.overload
    def __init__(self, orbital_momentum: int) -> None:
        """
        Initialise the hard sphere phase shift function
        
        Arguments:
            self               the function
            orbital_momentum   the value of the orbital momentum
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
    def __init__(self, orbital_momentum: int) -> None:
        """
        Initialise the hard sphere shift factor function
        
        Arguments:
            self               the function
            orbital_momentum   the value of the orbital momentum
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
class ResonanceParameters:
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: ResonanceParameters) -> bool:
        ...
    def __ne__(self, arg0: ResonanceParameters) -> bool:
        ...
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
