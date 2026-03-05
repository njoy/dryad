"""
Thermal scattering data
"""
from __future__ import annotations
import njoy.dryad
import typing
__all__: list[str] = ['BraggEdgeData', 'CoherentElasticScattering', 'DebyeWallerIntegralData', 'IncoherentElasticScattering', 'TabulatedScatteringKernel', 'TabulatedScatteringKernelFunction']
class BraggEdgeData:
    """
    Bragg edge data for a single temperature
    
    Parameters
    ----------
        temperature : float
             the temperature
        energies : list of float
             the temperature
        values : list of floatfloat
             the structure factor values
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> BraggEdgeData:
        ...
    def __deepcopy__(self, arg0: dict) -> BraggEdgeData:
        ...
    def __eq__(self, arg0: BraggEdgeData) -> bool:
        ...
    def __init__(self, temperature: float, energies: list[float], values: list[float]) -> None:
        """
        Initialise the Bragg edge data
        """
    def __ne__(self, arg0: BraggEdgeData) -> bool:
        ...
    @property
    def energies(self) -> list[float]:
        """
        The energies of the Bragg edges
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the Bradd edge data
        """
    @property
    def values(self) -> list[float]:
        """
        The structure factor values
        """
class CoherentElasticScattering:
    """
    Coherent elastic thermal scattering data
    
    Parameters
    ----------
        bragg_edges : list of njoy.dryad.thermal.BraggEdgeData
             the Bragg edge data
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> CoherentElasticScattering:
        ...
    def __deepcopy__(self, arg0: dict) -> CoherentElasticScattering:
        ...
    def __eq__(self, arg0: CoherentElasticScattering) -> bool:
        ...
    def __init__(self, bragg_edges: list[BraggEdgeData]) -> None:
        """
        Initialise the coherent elastic scattering data
        """
    def __ne__(self, arg0: CoherentElasticScattering) -> bool:
        ...
    def bragg_edge_data(self, temperature: float) -> BraggEdgeData:
        """
        Return the Bragg edge data for a given temperature
        
        Parameters
        ----------
            temperature : float
                 the temperature
        """
    def has_bragg_edge_data(self, temperature: float) -> bool:
        """
        Return whether or not there is Bragg edge data for a given temperature
        
        Parameters
        ----------
            temperature : float
                 the temperature
        """
    @property
    def bragg_edges(self) -> list[BraggEdgeData]:
        """
        The Bragg edge data
        """
    @bragg_edges.setter
    def bragg_edges(self, arg1: list[BraggEdgeData]) -> None:
        ...
    @property
    def moderator_temperatures(self) -> list[float]:
        """
        The moderator temperature values
        """
    @property
    def number_moderator_temperatures(self) -> int:
        """
        The moderator temperature values
        """
class DebyeWallerIntegralData:
    """
    A Debye-Waller integral table
    
    Temperature values are assumed to be in K and the integral values are assumed to be in 1/eV.
    
    Parameters
    ----------
        temperatures : list of float
             the temperature values
        values : list of float
             the intergal values
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> DebyeWallerIntegralData:
        ...
    def __deepcopy__(self, arg0: dict) -> DebyeWallerIntegralData:
        ...
    def __eq__(self, arg0: DebyeWallerIntegralData) -> bool:
        ...
    def __init__(self, temperatures: list[float], values: list[float]) -> None:
        """
        Initialise the Debye-Waller integral data
        """
    def __ne__(self, arg0: DebyeWallerIntegralData) -> bool:
        ...
    @property
    def temperatures(self) -> list[float]:
        """
        The temperature values
        """
    @property
    def values(self) -> list[float]:
        """
        The integral values
        """
class IncoherentElasticScattering:
    """
    Incoherent elastic thermal scattering data
    
    Parameters
    ----------
        xs : float
             the bound atom cross section
        debye_waller_integral : njoy.dryad.thermal.DebyeWallerIntegralData
             the Debye-Waller integral data
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> IncoherentElasticScattering:
        ...
    def __deepcopy__(self, arg0: dict) -> IncoherentElasticScattering:
        ...
    def __eq__(self, arg0: IncoherentElasticScattering) -> bool:
        ...
    def __init__(self, xs: float, debye_waller_integral: DebyeWallerIntegralData) -> None:
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
    def debye_waller_integral(self) -> DebyeWallerIntegralData:
        """
        The Debye-Waller integral data
        """
    @debye_waller_integral.setter
    def debye_waller_integral(self, arg1: DebyeWallerIntegralData) -> None:
        ...
    @property
    def moderator_temperatures(self) -> list[float]:
        """
        The moderator temperature values
        """
    @property
    def number_moderator_temperatures(self) -> int:
        """
        The moderator temperature values
        """
class TabulatedScatteringKernel:
    """
    An S(a,b) scattering kernel using tabulated scattering kernel functions
    
    Parameters
    ----------
        moderator_temperature : float
             the moderator temperature
        effective_temperature : float
             the effective temperature used in the SCT approximation
        energy_transfers : list of float
             the energy transfer values
        functions : list of njoy.dryad.thermal.TabulatedScatteringKernelFunction
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
    def __copy__(self) -> TabulatedScatteringKernel:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedScatteringKernel:
        ...
    def __eq__(self, arg0: TabulatedScatteringKernel) -> bool:
        ...
    @typing.overload
    def __init__(self, moderator_temperature: float, effective_temperature: float, energy_transfers: list[float], functions: list[TabulatedScatteringKernelFunction], boundaries: list[int], interpolants: list[njoy.dryad.InterpolationType]) -> None:
        """
        Initialise the S(a,b) scattering kernel with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, moderator_temperature: float, effective_temperature: float, energy_transfers: list[float], functions: list[TabulatedScatteringKernelFunction], interpolant: njoy.dryad.InterpolationType = ...) -> None:
        """
        Initialise the S(a,b) scattering kernel with a single interpolation zone
        """
    def __ne__(self, arg0: TabulatedScatteringKernel) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedScatteringKernel:
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
    def effective_temperature(self) -> float:
        """
        The effective temperature used for the short collision time approximation
        """
    @property
    def energy_transfers(self) -> list[float]:
        """
        The energy transfer values for which scattering functions are given
        """
    @property
    def functions(self) -> list[TabulatedScatteringKernelFunction]:
        """
        The associated scattering functions
        """
    @property
    def interpolants(self) -> list[njoy.dryad.InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def moderator_temperature(self) -> float:
        """
        The moderator temperature
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
class TabulatedScatteringKernelFunction:
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
    def __add__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedScatteringKernelFunction) -> TabulatedScatteringKernelFunction:
        ...
    def __call__(self, momentum_transfer: float) -> float:
        """
        Evaluate the scattering function for a given momentum transfer value
        
        Parameters
        ----------
            momentum_transfer : float
                the momentum transfer value
        """
    def __copy__(self) -> TabulatedScatteringKernelFunction:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedScatteringKernelFunction:
        ...
    def __eq__(self, arg0: TabulatedScatteringKernelFunction) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedScatteringKernelFunction) -> TabulatedScatteringKernelFunction:
        ...
    def __imul__(self, arg0: float) -> TabulatedScatteringKernelFunction:
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
    def __isub__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedScatteringKernelFunction) -> TabulatedScatteringKernelFunction:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    def __mul__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    def __ne__(self, arg0: TabulatedScatteringKernelFunction) -> bool:
        ...
    def __neg__(self) -> TabulatedScatteringKernelFunction:
        ...
    def __radd__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    def __rmul__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    def __rsub__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedScatteringKernelFunction) -> TabulatedScatteringKernelFunction:
        ...
    def __truediv__(self, arg0: float) -> TabulatedScatteringKernelFunction:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedScatteringKernelFunction:
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
