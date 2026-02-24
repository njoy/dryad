"""
Thermal scattering data
"""
from __future__ import annotations
import njoy.dryad
import typing
__all__: list[str] = ['IncoherentElasticScattering', 'InelasticScattering', 'TabulatedDebyeWallerIntegral', 'TabulatedEffectiveTemperature', 'TabulatedScatteringFunction', 'TabulatedScatteringFunctions']
class IncoherentElasticScattering:
    """
    Incoherent elastic thermal scattering data
    
    Parameters
    ----------
        xs : float
             the bound atom cross section
        debye_waller_integral : njoy.dryad.thermal.TabulatedDebyeWallerIntegral
             the Debye-Waller integral data
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> IncoherentElasticScattering:
        ...
    def __deepcopy__(self, arg0: dict) -> IncoherentElasticScattering:
        ...
    def __eq__(self, arg0: IncoherentElasticScattering) -> bool:
        ...
    def __init__(self, xs: float, debye_waller_integral: TabulatedDebyeWallerIntegral) -> None:
        """
        Initialise the incoherent elastic scattering data
        """
    def __ne__(self, arg0: IncoherentElasticScattering) -> bool:
        ...
    @property
    def bound_cross_section(self) -> float:
        """
        The bound atom cross section value
        """
    @bound_cross_section.setter
    def bound_cross_section(self, arg1: float) -> None:
        ...
    @property
    def debye_waller_integral(self) -> TabulatedDebyeWallerIntegral:
        """
        The Debye-Waller integral data
        """
    @debye_waller_integral.setter
    def debye_waller_integral(self, arg1: TabulatedDebyeWallerIntegral) -> None:
        ...
class InelasticScattering:
    """
    Inelastic thermal scattering data
    
    Parameters
    ----------
        xs : float
             the bound atom cross section
        self_scatter : njoy.dryad.thermal.TabulatedScatteringFunctions
             the self-scattering S(a,b) function
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> InelasticScattering:
        ...
    def __deepcopy__(self, arg0: dict) -> InelasticScattering:
        ...
    def __eq__(self, arg0: InelasticScattering) -> bool:
        ...
    def __init__(self, xs: float, self_scatter: TabulatedScatteringFunctions) -> None:
        """
        Initialise the inelastic scattering data
        """
    def __ne__(self, arg0: InelasticScattering) -> bool:
        ...
    @property
    def bound_cross_section(self) -> float:
        """
        The bound atom cross section value
        """
    @bound_cross_section.setter
    def bound_cross_section(self, arg1: float) -> None:
        ...
    @property
    def self_scattering_function(self) -> TabulatedScatteringFunctions:
        """
        The self-scattering S(a,b) function
        """
    @self_scattering_function.setter
    def self_scattering_function(self, arg1: TabulatedScatteringFunctions) -> None:
        ...
class TabulatedDebyeWallerIntegral:
    """
    A Debye-Waller integral table
    
    Temperature values are assumed to be in K and the integral values are assumed to be in 1/eV.
    
    Parameters
    ----------
        temperatures : list of float
             the temperature values
        values : list of float
             the intergal values
        boundaries : list of int
             the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
             the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
             the interpolation type (default lin-lin)
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedDebyeWallerIntegral) -> TabulatedDebyeWallerIntegral:
        ...
    def __call__(self, temperature: float) -> float:
        """
        Evaluate the integral for a given temperature value
        
        Parameters
        ----------
            temperature : float
                the temperature value
        """
    def __copy__(self) -> TabulatedDebyeWallerIntegral:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedDebyeWallerIntegral:
        ...
    def __eq__(self, arg0: TabulatedDebyeWallerIntegral) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedDebyeWallerIntegral) -> TabulatedDebyeWallerIntegral:
        ...
    def __imul__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    @typing.overload
    def __init__(self, temperatures: list[float], values: list[float], boundaries: list[int], interpolants: list[njoy.dryad.InterpolationType]) -> None:
        """
        Initialise the Debye-Waller integral table with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, temperatures: list[float], values: list[float], interpolant: njoy.dryad.InterpolationType = ...) -> None:
        """
        Initialise the Debye-Waller integral table with a single interpolation zone
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedDebyeWallerIntegral) -> TabulatedDebyeWallerIntegral:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    def __mul__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    def __ne__(self, arg0: TabulatedDebyeWallerIntegral) -> bool:
        ...
    def __neg__(self) -> TabulatedDebyeWallerIntegral:
        ...
    def __radd__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    def __rmul__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    def __rsub__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedDebyeWallerIntegral) -> TabulatedDebyeWallerIntegral:
        ...
    def __truediv__(self, arg0: float) -> TabulatedDebyeWallerIntegral:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedDebyeWallerIntegral:
        """
        Linearise the table
        
        Parameters
        ----------
            tolerance : float, default 0.001
                 the linearisation tolerance
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def interpolants(self) -> list[njoy.dryad.InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the table is linearised
        """
    @property
    def lower_temperature_limit(self) -> float:
        """
        The lower temperature limit
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
    def temperatures(self) -> list[float]:
        """
        The temperature values
        """
    @property
    def upper_temperature_limit(self) -> float:
        """
        The upper temperature limit
        """
    @property
    def values(self) -> list[float]:
        """
        The integral values
        """
class TabulatedEffectiveTemperature:
    """
    An effective temperature table
    
    This is a table of effective temperatures (given in K) for the short collision-time
    approximation given as a function of moderator temperature (given in K) for a scattering
    atom.
    
    Parameters
    ----------
        moderator_temperatures : list of float
             the moderator temperature values
        values : list of float
             the effective temperature values
        boundaries : list of int
             the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
             the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
             the interpolation type (default lin-lin)
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedEffectiveTemperature) -> TabulatedEffectiveTemperature:
        ...
    def __call__(self, moderator_temperature: float) -> float:
        """
        Evaluate the effective temperature for a given moderator temperature value
        
        Parameters
        ----------
            moderator_temperature : float
                the moderator temperature value
        """
    def __copy__(self) -> TabulatedEffectiveTemperature:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedEffectiveTemperature:
        ...
    def __eq__(self, arg0: TabulatedEffectiveTemperature) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedEffectiveTemperature) -> TabulatedEffectiveTemperature:
        ...
    def __imul__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    @typing.overload
    def __init__(self, moderator_temperatures: list[float], values: list[float], boundaries: list[int], interpolants: list[njoy.dryad.InterpolationType]) -> None:
        """
        Initialise the effective temperature table with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, moderator_temperatures: list[float], values: list[float], interpolant: njoy.dryad.InterpolationType = ...) -> None:
        """
        Initialise the effective temperature table with a single interpolation zone
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedEffectiveTemperature) -> TabulatedEffectiveTemperature:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    def __mul__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    def __ne__(self, arg0: TabulatedEffectiveTemperature) -> bool:
        ...
    def __neg__(self) -> TabulatedEffectiveTemperature:
        ...
    def __radd__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    def __rmul__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    def __rsub__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedEffectiveTemperature) -> TabulatedEffectiveTemperature:
        ...
    def __truediv__(self, arg0: float) -> TabulatedEffectiveTemperature:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedEffectiveTemperature:
        """
        Linearise the table
        
        Parameters
        ----------
            tolerance : float, default 0.001
                 the linearisation tolerance
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def interpolants(self) -> list[njoy.dryad.InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the table is linearised
        """
    @property
    def lower_moderator_temperature_limit(self) -> float:
        """
        The lower moderator temperature limit
        """
    @property
    def moderator_temperatures(self) -> list[float]:
        """
        The moderator temperature values
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
    def upper_moderator_temperature_limit(self) -> float:
        """
        The upper moderator temperature limit
        """
    @property
    def values(self) -> list[float]:
        """
        The effective temperatur values
        """
class TabulatedScatteringFunction:
    """
    A tabulated scattering function S(alpha)
    
    Parameters
    ----------
        momentum_transfers : list of float
             the momentum transfer values
        values : list of float
             the scattering function values
        boundaries : list of int
             the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
             the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
             the interpolation type (default lin-lin)
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedScatteringFunction) -> TabulatedScatteringFunction:
        ...
    def __call__(self, momentum_transfer: float) -> float:
        """
        Evaluate the scattering function for a given momentum transfer value
        
        Parameters
        ----------
            momentum_transfer : float
                the momentum transfer value
        """
    def __copy__(self) -> TabulatedScatteringFunction:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedScatteringFunction:
        ...
    def __eq__(self, arg0: TabulatedScatteringFunction) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedScatteringFunction) -> TabulatedScatteringFunction:
        ...
    def __imul__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    @typing.overload
    def __init__(self, momentum_transfers: list[float], values: list[float], boundaries: list[int], interpolants: list[njoy.dryad.InterpolationType]) -> None:
        """
        Initialise the scattering function table with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, momentum_transfers: list[float], values: list[float], interpolant: njoy.dryad.InterpolationType = ...) -> None:
        """
        Initialise the scattering function table with a single interpolation zone
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedScatteringFunction) -> TabulatedScatteringFunction:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    def __mul__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    def __ne__(self, arg0: TabulatedScatteringFunction) -> bool:
        ...
    def __neg__(self) -> TabulatedScatteringFunction:
        ...
    def __radd__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    def __rmul__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    def __rsub__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedScatteringFunction) -> TabulatedScatteringFunction:
        ...
    def __truediv__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedScatteringFunction:
        """
        Linearise the table
        
        Parameters
        ----------
            tolerance : float, default 0.001
                 the linearisation tolerance
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def interpolants(self) -> list[njoy.dryad.InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the table is linearised
        """
    @property
    def lower_momentum_transfer_limit(self) -> float:
        """
        The lower momentum transfer limit
        """
    @property
    def momentum_transfers(self) -> list[float]:
        """
        The momentum transfer values
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
    def upper_momentum_transfer_limit(self) -> float:
        """
        The upper momentum transfer limit
        """
    @property
    def values(self) -> list[float]:
        """
        The scattering function values
        """
class TabulatedScatteringFunctions:
    """
    An S(a,b) scattering kernel using tabulated scattering functions
    
    Parameters
    ----------
        energy_transfers : list of float
             the energy transfer values
        functions : list of njoy.dryad.thermal.TabulatedScatteringFunction
             the tabulated S(a) scattering functions
        boundaries : list of int
             the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
             the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
             the interpolation type (default lin-lin)
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, value: float, cosine: float) -> float:
        """
        Evaluate the S(a,b) scattering kernel for a given energy and momentum transfer value
        
        Parameters
        ----------
            b : float
                the energy transfer value
            a : float
                the momentum transfer value
        """
    def __copy__(self) -> TabulatedScatteringFunctions:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedScatteringFunctions:
        ...
    def __eq__(self, arg0: TabulatedScatteringFunctions) -> bool:
        ...
    @typing.overload
    def __init__(self, energy_transfers: list[float], functions: list[TabulatedScatteringFunction], boundaries: list[int], interpolants: list[njoy.dryad.InterpolationType]) -> None:
        """
        Initialise the S(a,b) scattering kernel with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, energy_transfers: list[float], functions: list[TabulatedScatteringFunction], interpolant: njoy.dryad.InterpolationType = ...) -> None:
        """
        Initialise the S(a,b) scattering kernel with a single interpolation zone
        """
    def __ne__(self, arg0: TabulatedScatteringFunctions) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedScatteringFunctions:
        """
        Linearise the S(a,b) scattering kernel
        
        Parameters
        ----------
            tolerance : float, default 0.001
                 the linearisation tolerance
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def energy_transfers(self) -> list[float]:
        """
        The energy transfer values for which scattering functions are given
        """
    @property
    def functions(self) -> list[TabulatedScatteringFunction]:
        """
        The associated scattering functions
        """
    @property
    def interpolants(self) -> list[njoy.dryad.InterpolationType]:
        """
        The interpolation types of the interpolation regions
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
