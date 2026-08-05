"""
Thermal scattering data
"""
from __future__ import annotations
import njoy.dryad
import typing
__all__: list[str] = ['BraggEdgeData', 'CoherentElasticScattering', 'DebyeWallerIntegralData', 'IncoherentElasticAngularCdf', 'IncoherentElasticAngularDistribution', 'IncoherentElasticAngularPdf', 'IncoherentElasticCrossSection', 'IncoherentElasticScattering', 'IncoherentInelasticScattering', 'ScatteringKernel', 'ShortCollisionTimeScatteringKernel', 'TabulatedScatteringKernel', 'TabulatedScatteringKernelFunction']
class BraggEdgeData:
    """
    Bragg edge data for a single temperature
    
    The Bragg edge data consists of edge energies and structure
    factor values.
    
    Parameters
    ----------
        temperature : float
            the temperature
        energies : list of float
            the temperature
        values : list of float
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
    def cross_section(self, upper: float) -> ...:
        """
        Return the coherent elastic scattering cross section up to the given energy
        
        Parameters
        ----------
            upper : float
                the upper energy limit
        """
    @property
    def energies(self) -> list[float]:
        """
        The energies of the Bragg edges
        """
    @property
    def number_bragg_edges(self) -> int:
        """
        The number of Bragg edges
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the Bragg edge data
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
        lower : float
            the lower energy limit
        upper : float
            the upper energy limit
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
    def __init__(self, lower: float, upper: float, bragg_edges: list[BraggEdgeData]) -> None:
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
                the moderator temperature
        """
    def cross_section(self, temperature: float) -> ...:
        """
        Return the coherent elastic scattering cross section for a given temperature
        
        Parameters
        ----------
            temperature : float
                the moderator temperature for which the cross section is requested
        """
    def has_bragg_edge_data(self, temperature: float) -> bool:
        """
        Return whether or not there is Bragg edge data for a given temperature
        
        Parameters
        ----------
            temperature : float
                the moderator temperature
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
    def lower_energy_limit(self) -> float:
        """
        The lower energy limit
        """
    @lower_energy_limit.setter
    def lower_energy_limit(self, arg1: float) -> None:
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
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit
        """
    @upper_energy_limit.setter
    def upper_energy_limit(self, arg1: float) -> None:
        ...
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
    def has_value(self, temperature: float) -> bool:
        """
        Return whether or not there is a Debye-Waller integral value for a given temperature
        
        Parameters
        ----------
            temperature : float
                the temperature
        """
    def value(self, temperature: float) -> float:
        """
        Return the Debye-Waller integral value for a given temperature
        
        Parameters
        ----------
            temperature : float
                the temperature
        """
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
class IncoherentElasticAngularCdf:
    """
    Incoherent elastic thermal scattering angular distribution cdf
    
    Parameters
    ----------
        incident : float
            the incident energy
        debye_waller_integral : float
            the Debye-Waller integral value
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the angular distribution for a given cosine value
        
        Parameters
        ----------
            cosine : float
                the cosine value
        """
    def __copy__(self) -> IncoherentElasticAngularCdf:
        ...
    def __deepcopy__(self, arg0: dict) -> IncoherentElasticAngularCdf:
        ...
    def __eq__(self, arg0: IncoherentElasticAngularCdf) -> bool:
        ...
    def __init__(self, incident: float, debye_waller_integral: float) -> None:
        """
        Initialise the incoherent elastic scattering angular distribution cdf
        """
    def __ne__(self, arg0: IncoherentElasticAngularCdf) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001) -> ...:
        """
        Linearise the angular distribution
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    @property
    def debye_waller_integral(self) -> float:
        """
        The Debye-Waller integral value
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def lower_cosine_limit(self) -> float:
        """
        The lower cosine limit
        """
    @property
    def upper_cosine_limit(self) -> float:
        """
        The upper cosine limit
        """
class IncoherentElasticAngularDistribution:
    """
    Incoherent elastic thermal scattering angular distribution defined by an
    analytical pdf and cdf
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the pdf of the distribution for a given cosine value
        
        Parameters
        ----------
            cosine : float
                the cosine value
        """
    def __copy__(self) -> IncoherentElasticAngularDistribution:
        ...
    def __deepcopy__(self, arg0: dict) -> IncoherentElasticAngularDistribution:
        ...
    def __eq__(self, arg0: IncoherentElasticAngularDistribution) -> bool:
        ...
    def __init__(self, incident: float, debye_waller_integral: float) -> None:
        """
        Initialise the angular distribution
        
        Parameters
        ----------
            incident : float
                the incident energy
            debye_waller_integral : float
                the Debye-Waller integral value
        """
    def __ne__(self, arg0: IncoherentElasticAngularDistribution) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> ...:
        """
        Linearise the distribution
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
            normalise : bool, default False
                option to indicate whether or not to normalise
                all probability data (default: no normalisation)
        """
    def normalise(self) -> None:
        """
        Normalise the distribution
        """
    @property
    def average_cosine(self) -> float:
        """
        The average cosine defined by the distribution
        """
    @property
    def cdf(self) -> IncoherentElasticAngularCdf:
        """
        The cumulative distribution function (cdf) of the distribution
        """
    @property
    def debye_waller_integral(self) -> float:
        """
        The Debye-Waller integral value
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def pdf(self) -> IncoherentElasticAngularPdf:
        """
        The probability distribution function (pdf) of the distribution
        """
class IncoherentElasticAngularPdf:
    """
    Incoherent elastic thermal scattering angular distribution pdf
    
    Parameters
    ----------
        incident : float
            the incident energy
        debye_waller_integral : float
            the Debye-Waller integral value
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the angular distribution for a given cosine value
        
        Parameters
        ----------
            cosine : float
                the cosine value
        """
    def __copy__(self) -> IncoherentElasticAngularPdf:
        ...
    def __deepcopy__(self, arg0: dict) -> IncoherentElasticAngularPdf:
        ...
    def __eq__(self, arg0: IncoherentElasticAngularPdf) -> bool:
        ...
    def __init__(self, incident: float, debye_waller_integral: float) -> None:
        """
        Initialise the incoherent elastic scattering angular distribution pdf
        """
    def __ne__(self, arg0: IncoherentElasticAngularPdf) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001) -> ...:
        """
        Linearise the angular distribution
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    def normalise(self) -> None:
        """
        Normalise the distribution
        """
    @property
    def debye_waller_integral(self) -> float:
        """
        The Debye-Waller integral value
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def integral(self) -> float:
        """
        The integral of the distribution over its domain
        """
    @property
    def lower_cosine_limit(self) -> float:
        """
        The lower cosine limit
        """
    @property
    def mean(self) -> float:
        """
        The mean value of the distribution over its domain
        """
    @property
    def upper_cosine_limit(self) -> float:
        """
        The upper cosine limit
        """
class IncoherentElasticCrossSection:
    """
    Incoherent elastic thermal scattering cross section
    
    Parameters
    ----------
        lower : float
            the lower energy limit
        upper : float
            the upper energy limit
        xs : float
            the bound atom cross section
        debye_waller_integral : float
            the Debye-Waller integral value
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the cross section for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> IncoherentElasticCrossSection:
        ...
    def __deepcopy__(self, arg0: dict) -> IncoherentElasticCrossSection:
        ...
    def __eq__(self, arg0: IncoherentElasticCrossSection) -> bool:
        ...
    def __init__(self, lower: float, upper: float, xs: float, debye_waller_integral: float) -> None:
        """
        Initialise the incoherent elastic scattering cross section
        """
    def __ne__(self, arg0: IncoherentElasticCrossSection) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001) -> ...:
        """
        Linearise the cross section
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    @property
    def bound_cross_section(self) -> float:
        """
        The bound atom cross section value
        """
    @property
    def debye_waller_integral(self) -> float:
        """
        The Debye-Waller integral value
        """
    @property
    def lower_energy_limit(self) -> float:
        """
        The lower energy limit
        """
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit
        """
class IncoherentElasticScattering:
    """
    Incoherent elastic thermal scattering data
    
    Parameters
    ----------
        lower : float
            the lower energy limit
        upper : float
            the upper energy limit
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
    def __init__(self, lower: float, upper: float, xs: float, debye_waller_integral: DebyeWallerIntegralData) -> None:
        """
        Initialise the incoherent elastic scattering data
        """
    def __ne__(self, arg0: IncoherentElasticScattering) -> bool:
        ...
    def angular_distribution(self, incident: float, temperature: float) -> IncoherentElasticAngularDistribution:
        """
        Return the incoherent elastic scattering angular distribution for a given
        incident energy and temperature
        
        Parameters
        ----------
            incident : float
                the incident energy
            temperature : float
                the moderator temperature for which the angular distribution is requested
        """
    def cross_section(self, temperature: float) -> IncoherentElasticCrossSection:
        """
        Return the incoherent elastic scattering cross section for a given temperature
        
        Parameters
        ----------
            temperature : float
                the moderator temperature for which the cross section is requested
        """
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
    def lower_energy_limit(self) -> float:
        """
        The lower energy limit
        """
    @lower_energy_limit.setter
    def lower_energy_limit(self, arg1: float) -> None:
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
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit
        """
    @upper_energy_limit.setter
    def upper_energy_limit(self, arg1: float) -> None:
        ...
class IncoherentInelasticScattering:
    """
    Incoherent inelastic thermal scattering data
    
    Parameters
    ----------
        lower : float
            the lower energy limit
        upper : float
            the upper energy limit
        xs : float
            the bound atom cross section
        ratio : float
            the atomic mass ratio of the target to the projectile
        kernels : list of njoy.dryad.thermal.ScatteringKernel
            the scattering kernels
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> IncoherentInelasticScattering:
        ...
    def __deepcopy__(self, arg0: dict) -> IncoherentInelasticScattering:
        ...
    def __eq__(self, arg0: IncoherentInelasticScattering) -> bool:
        ...
    def __init__(self, lower: float, upper: float, xs: float, ratio: float, kernels: list[ScatteringKernel]) -> None:
        """
        Initialise the incoherent inelastic scattering data
        """
    def __ne__(self, arg0: IncoherentInelasticScattering) -> bool:
        ...
    def cross_section(self, temperature: float, tolerance: float = 0.001) -> ...:
        """
        Return the incoherent inelastic scattering cross section for a given temperature
        
        Parameters
        ----------
            temperature : float
                the moderator temperature for which the cross section is requested
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    def has_scattering_kernel(self, temperature: float) -> bool:
        """
        Return whether or not there is a scattering kernel for a given temperature
        
        Parameters
        ----------
            temperature : float
                the moderator temperature
        """
    def scattering_kernel(self, temperature: float) -> ScatteringKernel:
        """
        Return the scattering kernel for a given temperature
        
        Parameters
        ----------
            temperature : float
                the moderator temperature
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The ratio of the target mass to the projectile mass
        """
    @atomic_weight_ratio.setter
    def atomic_weight_ratio(self, arg1: float) -> None:
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
    def lower_energy_limit(self) -> float:
        """
        The lower energy limit
        """
    @lower_energy_limit.setter
    def lower_energy_limit(self, arg1: float) -> None:
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
    @property
    def scattering_kernels(self) -> list[ScatteringKernel]:
        """
        The scattering kernels
        """
    @scattering_kernels.setter
    def scattering_kernels(self, arg1: list[ScatteringKernel]) -> None:
        ...
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit
        """
    @upper_energy_limit.setter
    def upper_energy_limit(self, arg1: float) -> None:
        ...
class ScatteringKernel:
    """
    An S(a,b) scattering kernel using the short collision time approximation
    
    Parameters
    ----------
        moderator_temperature : float
            the moderator temperature
        effective_temperature : float
            the effective temperature
        table : njoy.dryad.thermal.TabulatedScatteringKernel
            the tabulated S(a,b) scattering kernel
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
    @typing.overload
    def __call__(self, incident: float, outgoing: float, cosine: float, ratio: float) -> float:
        """
        Evaluate the scattering kernel for a given incident energy, outgoing energy
        and cosine value
        
        Parameters
        ----------
            incident : float
                the incident energy value
            outgoing : float
                the outgoing energy value
            cosine : float
                the cosine value    ratio : float
                the atomic mass ratio of the target to the projectile
            a : float
                the momentum transfer value
            b : float
                the energy transfer value
        """
    @typing.overload
    def __call__(self, a: float, b: float) -> float:
        """
        Evaluate the scattering kernel for a given momentum and energy transfer value
        """
    def __copy__(self) -> ScatteringKernel:
        ...
    def __deepcopy__(self, arg0: dict) -> ScatteringKernel:
        ...
    def __eq__(self, arg0: ScatteringKernel) -> bool:
        ...
    @typing.overload
    def __init__(self, moderator_temperature: float, effective_temperature: float, table: TabulatedScatteringKernel) -> None:
        """
        Initialise the scattering kernel with a tabulated scattering kernel
        """
    @typing.overload
    def __init__(self, moderator_temperature: float, effective_temperature: float, energy_transfers: list[float], functions: list[TabulatedScatteringKernelFunction], boundaries: list[int], interpolants: list[njoy.dryad.InterpolationType]) -> None:
        """
        Initialise the scattering kernel with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, moderator_temperature: float, effective_temperature: float, energy_transfers: list[float], functions: list[TabulatedScatteringKernelFunction], interpolant: njoy.dryad.InterpolationType = ...) -> None:
        """
        Initialise the scattering kernel with a single interpolation zone
        """
    def __ne__(self, arg0: ScatteringKernel) -> bool:
        ...
    def angular_distribution(self, incident: float, outgoing: float, ratio: float, tolerance: float = 0.001) -> ...:
        """
        Return the incoherent inelastic scattering angular distribution for a
        given incident and outgoing energy
        
        Parameters
        ----------
            incident : float
                the incident energy value
            outgoing : float
                the outgoing energy value
            ratio : float
                the atomic mass ratio of the target to the projectile    tolerance : float, default 0.001
                the linearisation tolerance
        """
    def cross_section(self, lower: float, upper: float, xs: float, ratio: float, tolerance: float = 0.001) -> ...:
        """
        Return the incoherent inelastic scattering cross section
        
        Parameters
        ----------
            lower : float
                the lower energy limit
            upper : float
                the upper energy limit
            xs : float
                the bound cross section value
            ratio : float
                the atomic mass ratio of the target to the projectile    tolerance : float, default 0.001
                the linearisation tolerance
        """
    def cross_section_value(self, incident: float, xs: float, ratio: float, tolerance: float = 0.001) -> float:
        """
        Return the incoherent inelastic scattering cross section for a
        given incident energy
        
        Parameters
        ----------
            incident : float
                the incident energy value
            xs : float
                the bound cross section value
            ratio : float
                the atomic mass ratio of the target to the projectile    tolerance : float, default 0.001
                the linearisation tolerance
        """
    def energy_distribution(self, incident: float, ratio: float, tolerance: float = 0.001) -> ...:
        """
        Return the incoherent inelastic scattering energy distribution for a
        given incident energy
        
        Parameters
        ----------
            incident : float
                the incident energy value
            ratio : float
                the atomic mass ratio of the target to the projectile    tolerance : float, default 0.001
                the linearisation tolerance
        """
    def energy_transfer(self, incident: float, outgoing: float) -> float:
        """
        Evaluate the energy transfer for a given incident and outgoing energy
        
        Parameters
        ----------
            incident : float
                the incident energy value
            outgoing : float
                the outgoing energy value
        """
    def momentum_transfer(self, incident: float, outgoing: float, cosine: float, ratio: float) -> float:
        """
        Evaluate the momentum transfer for a given incident energy, outgoing energy
        and cosine value
        
        Parameters
        ----------
            incident : float
                the incident energy value
            outgoing : float
                the outgoing energy value
            cosine : float
                the cosine value    ratio : float
                the atomic mass ratio of the target to the projectile
        """
    @property
    def effective_temperature(self) -> float:
        """
        The effective temperature
        """
    @property
    def is_energy_transfer_symmetric(self) -> bool:
        """
        Flag to indicate whether or not the scattering kernel is symmetric along the energy transfer axis
        """
    @property
    def moderator_temperature(self) -> float:
        """
        The moderator temperature
        """
    @property
    def short_collision_time(self) -> ShortCollisionTimeScatteringKernel:
        """
        The short collision time approximation
        """
    @property
    def tabulated_scattering_kernel(self) -> TabulatedScatteringKernel:
        """
        The tabulated scattering kernel
        """
class ShortCollisionTimeScatteringKernel:
    """
    An S(a,b) scattering kernel using the short collision time approximation
    
    Parameters
    ----------
        moderator_temperature : float
            the moderator temperature
        effective_temperature : float
            the effective temperature
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, a: float, b: float) -> float:
        """
        Evaluate the scattering kernel for a given energy value
        
        Parameters
        ----------
            a : float
                the momentum transfer value
            b : float
                the energy transfer value
        """
    def __copy__(self) -> ShortCollisionTimeScatteringKernel:
        ...
    def __deepcopy__(self, arg0: dict) -> ShortCollisionTimeScatteringKernel:
        ...
    def __eq__(self, arg0: ShortCollisionTimeScatteringKernel) -> bool:
        ...
    def __init__(self, moderator_temperature: float, effective_temperature: float) -> None:
        """
        Initialise the scattering kernel
        """
    def __ne__(self, arg0: ShortCollisionTimeScatteringKernel) -> bool:
        ...
    @property
    def effective_temperature(self) -> float:
        """
        The effective temperature
        """
    @property
    def moderator_temperature(self) -> float:
        """
        The moderator temperature
        """
class TabulatedScatteringKernel:
    """
    An S(a,b) scattering kernel using tabulated scattering kernel functions
    
    Parameters
    ----------
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
            a : float
                the momentum transfer value
            b : float
                the energy transfer value
        """
    def __copy__(self) -> TabulatedScatteringKernel:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedScatteringKernel:
        ...
    def __eq__(self, arg0: TabulatedScatteringKernel) -> bool:
        ...
    @typing.overload
    def __init__(self, energy_transfers: list[float], functions: list[TabulatedScatteringKernelFunction], boundaries: list[int], interpolants: list[njoy.dryad.InterpolationType]) -> None:
        """
        Initialise the tabulated S(a,b) scattering kernel with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, energy_transfers: list[float], functions: list[TabulatedScatteringKernelFunction], interpolant: njoy.dryad.InterpolationType = ...) -> None:
        """
        Initialise the tabulated S(a,b) scattering kernel with a single interpolation zone
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
    def lower_energy_transfer_limit(self) -> float:
        """
        The lower energy transfer limit
        """
    @property
    def lower_momentum_transfer_limit(self) -> float:
        """
        The lower momentum transfer limit
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
    def upper_energy_transfer_limit(self) -> float:
        """
        The upper energy transfer limit
        """
    @property
    def upper_momentum_transfer_limit(self) -> float:
        """
        The upper momentum transfer limit
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
