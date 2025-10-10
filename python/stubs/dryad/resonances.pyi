"""
Resonance data
"""
from __future__ import annotations
import dryad
import typing
__all__: list[str] = ['ResonanceParameters', 'TabulatedRadius', 'TabulatedWaveFunction']
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
