"""
Format agnostic nuclear data interface
"""
from __future__ import annotations
import typing
from . import atomic
from . import covariance
from . import external
from . import id
from . import resonances
from . import thermal
__all__: list[str] = ['AtomicRelaxation', 'CoherentDistributionData', 'DistributionDataType', 'Documentation', 'IncoherentDistributionData', 'InteractionType', 'InterpolationType', 'IsotropicAngularDistributionFunction', 'IsotropicAngularDistributions', 'LegendreAngularDistribution', 'LegendreAngularDistributionFunction', 'LegendreAngularDistributions', 'MixedAngularDistribution', 'MixedAngularDistributions', 'MultiEnergyDistributions', 'Particle', 'ParticleDatabase', 'PolynomialMultiplicity', 'ProjectileTarget', 'Reaction', 'ReactionCategory', 'ReactionProduct', 'ReferenceFrame', 'TabulatedAngularDistribution', 'TabulatedAngularDistributionFunction', 'TabulatedAngularDistributions', 'TabulatedAverageCosine', 'TabulatedAverageEnergy', 'TabulatedComptonProfile', 'TabulatedComptonProfileFunction', 'TabulatedCrossSection', 'TabulatedEnergyDistribution', 'TabulatedEnergyDistributionFunction', 'TabulatedEnergyDistributions', 'TabulatedFormFactor', 'TabulatedMultiplicity', 'TabulatedScatteringFunction', 'ThermalScattering', 'TwoBodyDistributionData', 'UncorrelatedDistributionData', 'UniformAngularDistribution', 'UniformAngularDistributions', 'UniformDistributionType', 'UniformEnergyDistribution', 'UniformEnergyDistributions', 'atomic', 'covariance', 'external', 'id', 'resonances', 'thermal']
class AtomicRelaxation:
    """
    Atomic relaxation data for a given element
    
    Parameters
    ----------
        documentation : njoy.dryad.Documentation
            the documentation
        element : njoy.dryad.id.ElementID
            the element identifier
        subshells : list of njoy.dryad.atomic.ElectronSubshellConfiguration
            the electron subshell configuration data
        normalise : bool, default false
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def from_endf_file(filename: str, normalise: bool = False) -> AtomicRelaxation:
        """
        Create AtomicRelaxation data from an ENDF file
        
        If there are multiple materials in the ENDF file, only the first material
        will be transformed into a AtomicRelaxation.
        
        Parameters
        ----------
            filename : str
                the ENDF file name
            normalise : bool, default false
                option to indicate whether or not to normalise
                all probability data (default: no normalisation)
        """
    @staticmethod
    def from_gnds_file(filename: str, normalise: bool = False) -> AtomicRelaxation:
        """
        Create AtomicRelaxation data from a GNDS file
        
        Parameters
        ----------
            filename : str
                the GNDS file name
            normalise : bool, default false
                option to indicate whether or not to normalise
                all probability data (default: no normalisation)
        """
    def __copy__(self) -> AtomicRelaxation:
        ...
    def __deepcopy__(self, arg0: dict) -> AtomicRelaxation:
        ...
    def __eq__(self, arg0: AtomicRelaxation) -> bool:
        ...
    @typing.overload
    def __init__(self, documentation: Documentation, element: id.ElementID, subshells: list[atomic.ElectronSubshellConfiguration], normalise: bool = False) -> None:
        """
        Initialise the atomic relaxation data with documentation
        """
    @typing.overload
    def __init__(self, element: id.ElementID, subshells: list[atomic.ElectronSubshellConfiguration], normalise: bool = False) -> None:
        """
        Initialise the atomic relaxation data without documentation
        """
    def __ne__(self, arg0: AtomicRelaxation) -> bool:
        ...
    def calculate_transition_energies(self) -> None:
        """
        Calculate the transition energies for all transitions
        """
    def has_subshell(self, identifier: id.ElectronSubshellID) -> bool:
        """
        Return whether or not a subshell is present
        
        Parameters
        ----------
            identifier : njoy.dryad.id.ElectronSubshellID
                the electron subshell identifier
        """
    def normalise(self) -> None:
        """
        Normalise the transition probabilities
        """
    def subshell(self, identifier: id.ElectronSubshellID) -> atomic.ElectronSubshellConfiguration:
        """
        Return the requested subshell
        
        Parameters
        ----------
            identifier : njoy.dryad.id.ElectronSubshellID
                the electron subshell identifier
        """
    def to_endf_file(self, mat: int, filename: str) -> None:
        """
        Write the AtomicRelaxation data to an ENDF file
        
        Parameters
        ----------
            mat : int
                the ENDF mat number to be used
            filename : str
                the ENDF file name
        """
    @property
    def documentation(self) -> Documentation:
        """
        The documentation
        """
    @documentation.setter
    def documentation(self, arg1: Documentation) -> None:
        ...
    @property
    def element_identifier(self) -> id.ElementID:
        """
        The element identifier
        """
    @element_identifier.setter
    def element_identifier(self, arg1: id.ElementID) -> None:
        ...
    @property
    def number_subshells(self) -> int:
        """
        The number of subshells defined for this atom
        """
    @property
    def subshells(self) -> list[atomic.ElectronSubshellConfiguration]:
        """
        The electron shell configuration data
        """
    @subshells.setter
    def subshells(self, arg1: list[atomic.ElectronSubshellConfiguration]) -> None:
        ...
class CoherentDistributionData:
    """
    The distribution data for coherent scattering in photoatomic interactions
    
    This representation is only available for a photoatomic ProjectileTarget.
    
    In this representation, a scattering function S(x,Z) and two optional form factor
    functions are defined which together with the Thompson cross section determine the
    double differential cross section. The optional form factors are the real and
    complex part of the anomalous form factor. These are defined as optional because
    photoatomic MCNP data files produced in 2024 or earlier do not contain these form
    factors even though the photoatomic ENDF evaluations define them.
    
    This corresponds with the coherent scattering function data given in
    MF27 MT502 and the form factors in MF27 MT505 and MT506.
    
    Parameters
    ----------
        frame : njoy.dryad.ReferenceFrame
            the reference frame of the distribution data
        scattering : njoy.dryad.TabulatedScatteringFunction
            the scattering function
        real : njoy.dryad.TabulatedFormFactor
            the real part of the anomalous form factor
        imaginary : njoy.dryad.TabulatedFormFactor
            the imaginary part of the anomalous form factor
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> CoherentDistributionData:
        ...
    def __deepcopy__(self, arg0: dict) -> CoherentDistributionData:
        ...
    def __eq__(self, arg0: CoherentDistributionData) -> bool:
        ...
    @typing.overload
    def __init__(self, frame: ReferenceFrame, scattering: TabulatedScatteringFunction) -> None:
        """
        Initialise the coherent distribution data without anomalous form factors
        """
    @typing.overload
    def __init__(self, frame: ReferenceFrame, scattering: TabulatedScatteringFunction, real: TabulatedFormFactor, imaginary: TabulatedFormFactor) -> None:
        """
        Initialise the coherent distribution data with anomalous form factors
        """
    def __ne__(self, arg0: CoherentDistributionData) -> bool:
        ...
    @property
    def frame(self) -> ReferenceFrame:
        """
        The reference frame
        """
    @frame.setter
    def frame(self, arg1: ReferenceFrame) -> None:
        ...
    @property
    def has_anomalous_form_factor(self) -> bool:
        """
        Flag indicating whether or not the coherent distribution data has an anomalous form factor
        """
    @property
    def imaginary_anomalous_form_factor(self) -> TabulatedFormFactor | None:
        """
        The imaginary part of the anomalous form factor
        """
    @imaginary_anomalous_form_factor.setter
    def imaginary_anomalous_form_factor(self, arg1: TabulatedFormFactor | None) -> None:
        ...
    @property
    def real_anomalous_form_factor(self) -> TabulatedFormFactor | None:
        """
        The real part of the anomalous form factor
        """
    @real_anomalous_form_factor.setter
    def real_anomalous_form_factor(self, arg1: TabulatedFormFactor | None) -> None:
        ...
    @property
    def scattering_function(self) -> TabulatedScatteringFunction:
        """
        The scattering function
        """
    @scattering_function.setter
    def scattering_function(self, arg1: TabulatedScatteringFunction) -> None:
        ...
    @property
    def type(self) -> DistributionDataType:
        """
        The distribution data type
        """
class DistributionDataType:
    """
    The distribution data type of a reaction product
    
    This enum is used to differentiate between the various distribution data
    types that are available for a reaction product.
    
    Members:
    
      TwoBody : The distribution data is given as two body scattering
    
      Uncorrelated : The distribution data is uncorrelated
    
      Coherent : The distribution data is for coherent scattering for photoatomic interactions
    
      Incoherent : The distribution data is for incoherent scattering for photoatomic interactions
    """
    Coherent: typing.ClassVar[DistributionDataType]  # value = <DistributionDataType.Coherent: 2>
    Incoherent: typing.ClassVar[DistributionDataType]  # value = <DistributionDataType.Incoherent: 3>
    TwoBody: typing.ClassVar[DistributionDataType]  # value = <DistributionDataType.TwoBody: 0>
    Uncorrelated: typing.ClassVar[DistributionDataType]  # value = <DistributionDataType.Uncorrelated: 1>
    __members__: typing.ClassVar[dict[str, DistributionDataType]]  # value = {'TwoBody': <DistributionDataType.TwoBody: 0>, 'Uncorrelated': <DistributionDataType.Uncorrelated: 1>, 'Coherent': <DistributionDataType.Coherent: 2>, 'Incoherent': <DistributionDataType.Incoherent: 3>}
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
class Documentation:
    """
    Documentation associated to the dryad data
    
    Parameters
    ----------
        library : int, optional
            the library number
        version : tuple of int, optional
            the version numbers (major and minor)
        description : str, optional
            the description
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> Documentation:
        ...
    def __deepcopy__(self, arg0: dict) -> Documentation:
        ...
    def __eq__(self, arg0: Documentation) -> bool:
        ...
    @typing.overload
    def __init__(self) -> None:
        """
        Initialise the documentation with default values
        """
    @typing.overload
    def __init__(self, library: int | None = None, version: tuple[int, int] | None = None, description: str | None = None) -> None:
        """
        Initialise the documentation
        """
    def __ne__(self, arg0: Documentation) -> bool:
        ...
    @property
    def description(self) -> str | None:
        """
        The description
        """
    @description.setter
    def description(self, arg1: str | None) -> None:
        ...
    @property
    def library(self) -> int | None:
        """
        The library number
        """
    @library.setter
    def library(self, arg1: int | None) -> None:
        ...
    @property
    def version(self) -> tuple[int, int] | None:
        """
        The version numbers (major and minor)
        """
    @version.setter
    def version(self, arg1: tuple[int, int] | None) -> None:
        ...
class IncoherentDistributionData:
    """
    The distribution data for incoherent scattering in photoatomic interactions
    
    This representation is only available for a photoatomic ProjectileTarget.
    
    In this representation, a scattering function S(x,Z) is defined that
    together with the Klein-Nishina cross section determines the double
    differential cross section.
    
    This corresponds with the incoherent scattering function data given in MF27 MT504,
    supplemented with optional external Compton profile data.
    
    Parameters
    ----------
        frame : njoy.dryad.ReferenceFrame
            the reference frame of the distribution data
        scattering : njoy.dryad.TabulatedScatteringFunction
            the scattering function
        profiles : list of njoy.dryad.TabulatedComptonProfile
            the optional Compton profiles
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> IncoherentDistributionData:
        ...
    def __deepcopy__(self, arg0: dict) -> IncoherentDistributionData:
        ...
    def __eq__(self, arg0: IncoherentDistributionData) -> bool:
        ...
    def __init__(self, frame: ReferenceFrame, scattering: TabulatedScatteringFunction, profiles: list[TabulatedComptonProfile] | None = None) -> None:
        """
        Initialise the incoherent distribution data
        """
    def __ne__(self, arg0: IncoherentDistributionData) -> bool:
        ...
    @typing.overload
    def average_energy(self, energy: float, tolerance: float = 1e-08) -> float:
        """
        Calculate the average outgoing energy
        
        Parameters 
        ---------- 
            energy : float 
                the incident energy
            energies : list of float 
                the incident energies
            tolerance : float, default 1e-08
                the linearisation tolerance
        """
    @typing.overload
    def average_energy(self, energies: list[float], tolerance: float = 1e-08) -> list[float]:
        """
        Calculate the average outgoing energy
        """
    def normalise(self) -> None:
        """
        Normalise the Compton profiles
        """
    @property
    def compton_profiles(self) -> list[TabulatedComptonProfile] | None:
        """
        The Compton profiles
        """
    @compton_profiles.setter
    def compton_profiles(self, arg1: list[TabulatedComptonProfile] | None) -> None:
        ...
    @property
    def frame(self) -> ReferenceFrame:
        """
        The reference frame
        """
    @frame.setter
    def frame(self, arg1: ReferenceFrame) -> None:
        ...
    @property
    def has_compton_profiles(self) -> bool:
        """
        Flag indicating whether or not there are Compton profiles
        """
    @property
    def scattering_function(self) -> TabulatedScatteringFunction:
        """
        The scattering function
        """
    @scattering_function.setter
    def scattering_function(self, arg1: TabulatedScatteringFunction) -> None:
        ...
    @property
    def type(self) -> DistributionDataType:
        """
        The distribution data type
        """
class InteractionType:
    """
    The projectile-target interaction type
    
    This enum is used to differentiate between how the projectile interacts with
    the target. We currently distinguish nuclear and atomic interactions.
    
    Members:
    
      Nuclear : The projectile-target interaction is nuclear
    
      Atomic : The projectile-target interaction is atomic
    """
    Atomic: typing.ClassVar[InteractionType]  # value = <InteractionType.Atomic: 2>
    Nuclear: typing.ClassVar[InteractionType]  # value = <InteractionType.Nuclear: 1>
    __members__: typing.ClassVar[dict[str, InteractionType]]  # value = {'Nuclear': <InteractionType.Nuclear: 1>, 'Atomic': <InteractionType.Atomic: 2>}
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
class InterpolationType:
    """
    The interpolation type for tabulated data
    
    Members:
    
      Histogram : Constant or histogram interpolation
    
      LinearLinear : y is linear in x
    
      LinearLog : y is linear in ln(x)
    
      LogLinear : ln(y) is linear in x
    
      LogLog : ln(y) is linear in ln(x)
    """
    Histogram: typing.ClassVar[InterpolationType]  # value = <InterpolationType.Histogram: 1>
    LinearLinear: typing.ClassVar[InterpolationType]  # value = <InterpolationType.LinearLinear: 2>
    LinearLog: typing.ClassVar[InterpolationType]  # value = <InterpolationType.LinearLog: 3>
    LogLinear: typing.ClassVar[InterpolationType]  # value = <InterpolationType.LogLinear: 4>
    LogLog: typing.ClassVar[InterpolationType]  # value = <InterpolationType.LogLog: 5>
    __members__: typing.ClassVar[dict[str, InterpolationType]]  # value = {'Histogram': <InterpolationType.Histogram: 1>, 'LinearLinear': <InterpolationType.LinearLinear: 2>, 'LinearLog': <InterpolationType.LinearLog: 3>, 'LogLinear': <InterpolationType.LogLinear: 4>, 'LogLog': <InterpolationType.LogLog: 5>}
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
class IsotropicAngularDistributionFunction:
    """
    An isotropic angular distribution function
    
    In this distribution, all cosines are equally probable. The equivalent
    normalised tabulated distribution is 0.5 on the [-1, 1] domain and the
    equivalent Legendre distribution uses 0.5 as the P0 coefficient.
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the distribution for a given cosine value
        
        Parameters
        ----------
            cosine : float
                the cosine value
        """
    def __copy__(self) -> IsotropicAngularDistributionFunction:
        ...
    def __deepcopy__(self, arg0: dict) -> IsotropicAngularDistributionFunction:
        ...
    def __eq__(self, arg0: IsotropicAngularDistributionFunction) -> bool:
        ...
    def __init__(self, value: float = 0.5) -> None:
        """
        Initialise the isotropic angular distribution
        
        Parameters
        ----------
            value : float, default 0.5
                the value of the distribution (0.5 for a normalised distribution)
        """
    def __ne__(self, arg0: IsotropicAngularDistributionFunction) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> ...:
        """
        Linearise the distribution function
        
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
        Normalise the distribution function
        """
    def to_legendre_distribution(self) -> ...:
        """
        Convert to the equivalent Legendre distribution
        """
    def to_tabulated_distribution(self) -> ...:
        """
        Convert to the equivalent tabulated distribution
        """
    @property
    def integral(self) -> float:
        """
        The integral of the distribution function over its domain
        """
    @property
    def lower_cosine_limit(self) -> float:
        """
        The lower cosine limit
        """
    @property
    def mean(self) -> float:
        """
        The mean value of the distribution function over its domain
        """
    @property
    def upper_cosine_limit(self) -> float:
        """
        The upper cosine limit
        """
    @property
    def value(self) -> float:
        """
        The value of the distribution
        """
class IsotropicAngularDistributions:
    """
    All angular distributions are isotropic
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> IsotropicAngularDistributions:
        ...
    def __deepcopy__(self, arg0: dict) -> IsotropicAngularDistributions:
        ...
    def __eq__(self, arg0: IsotropicAngularDistributions) -> bool:
        ...
    def __init__(self) -> None:
        """
        Initialise the isotropic angular distributions
        """
    def __ne__(self, arg0: IsotropicAngularDistributions) -> bool:
        ...
class LegendreAngularDistribution:
    """
    An angular distribution defined by a pdf and cdf using a Legendre series expansion
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
    def __copy__(self) -> LegendreAngularDistribution:
        ...
    def __deepcopy__(self, arg0: dict) -> LegendreAngularDistribution:
        ...
    def __eq__(self, arg0: LegendreAngularDistribution) -> bool:
        ...
    def __init__(self, coefficients: list[float], normalise: bool = False) -> None:
        """
        Initialise the angular distribution
        
        Parameters
        ----------
            coefficients : list of float
                the coefficients of the Legendre series (from
                lowest to highest order coefficient)
            normalise : bool, default False
                option to indicate whether or not to normalise
                all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: LegendreAngularDistribution) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedAngularDistribution:
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
    def cdf(self) -> LegendreAngularDistributionFunction:
        """
        The cumulative distribution function (cdf) of the distribution
        """
    @property
    def coefficients(self) -> list[float]:
        """
        The coefficients
        """
    @property
    def pdf(self) -> LegendreAngularDistributionFunction:
        """
        The probability distribution function (pdf) of the distribution
        """
class LegendreAngularDistributionFunction:
    """
    An angular distribution function using a Legendre expansion defined by a
    set of coefficients
    
    Note: ENDF and GNDS Legendre expansions use Legendre moments for the angular
    distributions in MF4 and MF6 LAW=1 & LAW=2 so an additional ( 2 * n + 1 ) / 2
    factor for the coefficient of order n needs to be applied to obtain the series
    coefficients. This distribution function assumes those factors are already
    integrated in the coefficients.
    
    A distribution function does not have to normalised as this class can be used
    to represent both a pdf and cdf. Proper normalisation should be applied after
    construction using the normalise() function if required.
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    @typing.overload
    def __add__(self, arg0: LegendreAngularDistributionFunction) -> LegendreAngularDistributionFunction:
        ...
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the distribution for a given cosine value
        
        Parameters
        ----------
            cosine : float
                the cosine value
        """
    def __copy__(self) -> LegendreAngularDistributionFunction:
        ...
    def __deepcopy__(self, arg0: dict) -> LegendreAngularDistributionFunction:
        ...
    def __eq__(self, arg0: LegendreAngularDistributionFunction) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    @typing.overload
    def __iadd__(self, arg0: LegendreAngularDistributionFunction) -> LegendreAngularDistributionFunction:
        ...
    def __imul__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    def __init__(self, coefficients: list[float]) -> None:
        """
        Initialise the angular distribution
        
        Parameters
        ----------
            coefficients : list of float
                the coefficients of the Legendre series (from
                lowest to highest order coefficient)
        """
    @typing.overload
    def __isub__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    @typing.overload
    def __isub__(self, arg0: LegendreAngularDistributionFunction) -> LegendreAngularDistributionFunction:
        ...
    def __itruediv__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    def __mul__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    def __ne__(self, arg0: LegendreAngularDistributionFunction) -> bool:
        ...
    def __neg__(self) -> LegendreAngularDistributionFunction:
        ...
    def __radd__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    def __rmul__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    def __rsub__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: LegendreAngularDistributionFunction) -> LegendreAngularDistributionFunction:
        ...
    def __truediv__(self, arg0: float) -> LegendreAngularDistributionFunction:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedAngularDistributionFunction:
        """
        Linearise the series
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    def normalise(self) -> None:
        """
        Normalise the distribution function
        """
    @property
    def coefficients(self) -> list[float]:
        """
        The series coefficients
        """
    @property
    def integral(self) -> float:
        """
        The integral of the distribution function over its domain
        """
    @property
    def lower_cosine_limit(self) -> float:
        """
        The lower cosine limit
        """
    @property
    def mean(self) -> float:
        """
        The mean value of the distribution function over its domain
        """
    @property
    def order(self) -> int:
        """
        The series order
        """
    @property
    def upper_cosine_limit(self) -> float:
        """
        The upper cosine limit
        """
class LegendreAngularDistributions:
    """
    Angular distribution data given using Legendre expansions
    
    Parameters
    ----------
        grid : list of float
            the grid values
        distributions : list of njoy.dryad.LegendreAngularDistribution
            the angular distributions
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, value: float, cosine: float) -> float:
        """
        Evaluate the angular distribution for a given grid and cosine value
        
        Parameters
        ----------
            value : float
                the grid value
            cosine : float
                the cosine value
        """
    def __copy__(self) -> LegendreAngularDistributions:
        ...
    def __deepcopy__(self, arg0: dict) -> LegendreAngularDistributions:
        ...
    def __eq__(self, arg0: LegendreAngularDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[LegendreAngularDistribution], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the angular distributions with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[LegendreAngularDistribution], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the angular distributions with a single interpolation zone
        """
    def __ne__(self, arg0: LegendreAngularDistributions) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedAngularDistributions:
        """
        Linearise the distributions
        
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
        Normalise the distributions
        
        Note: all distributions should have the same integral over their domain
              to avoid changing the full distribution (ie the normalisation moves
              every distribution up or down by the same amount to avoid changing
              the full distribution shape).
        """
    @property
    def average_cosines(self) -> TabulatedAverageCosine:
        """
        The average cosine values
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def distributions(self) -> list[LegendreAngularDistribution]:
        """
        The associated distributions
        """
    @property
    def grid(self) -> list[float]:
        """
        The grid values for which distributions are given
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
class MixedAngularDistribution:
    """
    An angular distribution defined by a pdf that is an isotropic, legendre or
    tabulated distribution function
    
    Parameters
    ----------
        pdf : njoy.dryad.IsotropicAngularDistributionFunction, njoy.dryad.LegendreAngularDistributionFunction or njoy.dryad.TabulatedAngularDistributionFunction]
            the distribution function
        value : float
            the value of the distribution (0.5 for a normalised distribution)
        coefficients : list of float
            the coefficients of the Legendre series (from
            lowest to highest order coefficient)
        cosines : list of float
            the cosine values
        values : list of float
            the probability values
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
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
    def __copy__(self) -> MixedAngularDistribution:
        ...
    def __deepcopy__(self, arg0: dict) -> MixedAngularDistribution:
        ...
    def __eq__(self, arg0: MixedAngularDistribution) -> bool:
        ...
    @typing.overload
    def __init__(self, pdf: IsotropicAngularDistributionFunction | ... | TabulatedAngularDistributionFunction, normalise: bool = False) -> None:
        """
        Initialise the angular distribution
        """
    @typing.overload
    def __init__(self, value: float, normalise: bool = False) -> None:
        """
        Initialise the angular distribution as isotropic
        """
    @typing.overload
    def __init__(self, coefficients: list[float], normalise: bool = False) -> None:
        """
        Initialise the angular distribution with Legendre coefficients
        """
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the angular distribution with tabulated data with multiple
        interpolation zones
        """
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the angular distribution with tabulated data with a single
        interpolation zone
        """
    def __ne__(self, arg0: MixedAngularDistribution) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedAngularDistribution:
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
    def cdf(self) -> IsotropicAngularDistributionFunction | ... | TabulatedAngularDistributionFunction:
        """
        The cumulative distribution function (cdf) of the distribution
        """
    @property
    def pdf(self) -> IsotropicAngularDistributionFunction | ... | TabulatedAngularDistributionFunction:
        """
        The probability distribution function (pdf) of the distribution
        """
class MixedAngularDistributions:
    """
    Angular distribution data given using Legendre expansions
    
    Parameters
    ----------
        grid : list of float
            the grid values
        distributions : list of njoy.dryad.MixedAngularDistribution
            the angular distributions
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, value: float, cosine: float) -> float:
        """
        Evaluate the angular distribution for a given grid and cosine value
        
        Parameters
        ----------
            value : float
                the grid value
            cosine : float
                the cosine value
        """
    def __copy__(self) -> MixedAngularDistributions:
        ...
    def __deepcopy__(self, arg0: dict) -> MixedAngularDistributions:
        ...
    def __eq__(self, arg0: MixedAngularDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[MixedAngularDistribution], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the angular distributions with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[MixedAngularDistribution], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the angular distributions with a single interpolation zone
        """
    def __ne__(self, arg0: MixedAngularDistributions) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedAngularDistributions:
        """
        Linearise the distributions
        
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
        Normalise the distributions
        
        Note: all distributions should have the same integral over their domain
              to avoid changing the full distribution (ie the normalisation moves
              every distribution up or down by the same amount to avoid changing
              the full distribution shape).
        """
    @property
    def average_cosines(self) -> TabulatedAverageCosine:
        """
        The average cosine values
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def distributions(self) -> list[MixedAngularDistribution]:
        """
        The associated distributions
        """
    @property
    def grid(self) -> list[float]:
        """
        The grid values for which distributions are given
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
class MultiEnergyDistributions:
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: MultiEnergyDistributions) -> bool:
        ...
    def __ne__(self, arg0: MultiEnergyDistributions) -> bool:
        ...
class Particle:
    """
    Particle information
    
    The Particle class contains specific information for a particle:
    
      - a particle identifier
      - an optional atomic mass value (always for the ground state) and an
        optional uncertainty
      - an optional nuclear mass value (always for the ground state) and an
        optional uncertainty
      - an optional excited state energy value and an optional uncertainty
      - an optional spin and parity (which is either + or -)
    
    The data is stored in the following units:
    
      - atomic mass values are in atomic mass units
      - energy values are in eV
    
    Parameters
    ----------
        id : njoy.dryad.id.ParticleID
            the particle identifier
        mass : float, default None
            the atomic mass (default: None)
        nuclear_mass : float, default None
            the nuclear mass (default: None)
        spin : float, default None
            the particle spin (default: None)
        parity : int, default None
            the particle spin parity (default: None)
        energy : float, default None
            the excited state energy (default: None)
        mass_uncertainty : float, default None
            the uncertainty on the atomic mass value (default: None)
        nuclear_mass_uncertainty : float, default None
            the uncertainty on the nuclear mass value (default: None)
        energy_uncertainty : float, default None
            the uncertainty on the excited level energy value (default: None)
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def alpha() -> Particle:
        """
        The default particle instance for alphas
        """
    @staticmethod
    def default_particle(id: id.ParticleID) -> Particle:
        """
        The default particle instance for a given particle identifier
        
        This function creates a default particle instance for the given particle
        identifier. When relevant, the discrete level energies and spins-parity pairs
        from RIPL-3 and the atomic masses from AME-2020 are used.
        
        When more sources for the particle data become available, this function will
        provide options to select data from.
        
        When an atomic identifier (either with or without vacancies) is used, the
        elemental particle instance will be returned.
        
        Parameters
        ----------
            id : njoy.dryad.id.ParticleID
                the particle identifier
        """
    @staticmethod
    def deuteron() -> Particle:
        """
        The default particle instance for deuterons
        """
    @staticmethod
    def electron() -> Particle:
        """
        The default particle instance for electrons
        """
    @staticmethod
    def helion() -> Particle:
        """
        The default particle instance for helions
        """
    @staticmethod
    def neutron() -> Particle:
        """
        The default particle instance for neutrons
        """
    @staticmethod
    def photon() -> Particle:
        """
        The default particle instance for photons
        """
    @staticmethod
    def positron() -> Particle:
        """
        The default particle instance for positrons
        """
    @staticmethod
    def proton() -> Particle:
        """
        The default particle instance for protons
        """
    @staticmethod
    def triton() -> Particle:
        """
        The default particle instance for tritons
        """
    def __copy__(self) -> Particle:
        ...
    def __deepcopy__(self, arg0: dict) -> Particle:
        ...
    def __eq__(self, arg0: Particle) -> bool:
        ...
    def __init__(self, id: id.ParticleID, mass: float | None = None, spin: float | None = None, parity: int | None = None, energy: float | None = None, nuclear_mass: float | None = None, mass_uncertainty: float | None = None, nuclear_mass_uncertainty: float | None = None, energy_uncertainty: float | None = None) -> None:
        """
        Initialise the particle information
        """
    def __ne__(self, arg0: Particle) -> bool:
        ...
    @property
    def charge(self) -> int:
        """
        The electrical charge of the particle
        """
    @property
    def energy(self) -> float | None:
        """
        The excited state energy value of the particle
        """
    @energy.setter
    def energy(self, arg1: float | None) -> None:
        ...
    @property
    def energy_uncertainty(self) -> float | None:
        """
        The excited state energy uncertainty
        """
    @energy_uncertainty.setter
    def energy_uncertainty(self, arg1: float | None) -> None:
        ...
    @property
    def excited_state(self) -> int:
        """
        The excited state number of the particle
        """
    @property
    def identifier(self) -> id.ParticleID:
        """
        The particle identifier
        """
    @identifier.setter
    def identifier(self, arg1: id.ParticleID) -> None:
        ...
    @property
    def mass(self) -> float | None:
        """
        The atomic mass of the particle in the ground state
        """
    @mass.setter
    def mass(self, arg1: float | None) -> None:
        ...
    @property
    def mass_uncertainty(self) -> float | None:
        """
        The atomic mass uncertainty
        """
    @mass_uncertainty.setter
    def mass_uncertainty(self, arg1: float | None) -> None:
        ...
    @property
    def nuclear_mass(self) -> float | None:
        """
        The nuclear mass of the particle in the ground state
        """
    @nuclear_mass.setter
    def nuclear_mass(self, arg1: float | None) -> None:
        ...
    @property
    def nuclear_mass_uncertainty(self) -> float | None:
        """
        The nuclear mass uncertainty
        """
    @nuclear_mass_uncertainty.setter
    def nuclear_mass_uncertainty(self, arg1: float | None) -> None:
        ...
    @property
    def parity(self) -> int | None:
        """
        The particle spin parity
        """
    @parity.setter
    def parity(self, arg1: int | None) -> None:
        ...
    @property
    def spin(self) -> float | None:
        """
        The spin of the particle
        """
    @spin.setter
    def spin(self, arg1: float | None) -> None:
        ...
class ParticleDatabase:
    """
    The particle database
    
    Parameters
    ----------
        particles : list of njoy.dryad.Particle
            the particle information
        identifiers : list of njoy.dryad.id.ParticleID
            the particle identifiers
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> ParticleDatabase:
        ...
    def __deepcopy__(self, arg0: dict) -> ParticleDatabase:
        ...
    def __eq__(self, arg0: ParticleDatabase) -> bool:
        ...
    @typing.overload
    def __init__(self, particles: list[Particle]) -> None:
        """
        Initialise the particle database
        """
    @typing.overload
    def __init__(self, identifiers: list[id.ParticleID]) -> None:
        """
        Initialise the particle database
        """
    def __ne__(self, arg0: ParticleDatabase) -> bool:
        ...
    def has_particle(self, id: id.ParticleID) -> bool:
        """
        Return whether or not a particle is present
        
        Parameters
        ----------
            id : njoy.dryad.id.ParticleID
                the particle identifier
        """
    def particle(self, id: id.ParticleID) -> Particle:
        """
        Return the requested particle
        
        Parameters
        ----------
            id : njoy.dryad.id.ParticleID
                the particle identifier
        """
    @property
    def number_particles(self) -> int:
        """
        The number of particles
        """
    @property
    def particles(self) -> list[Particle]:
        """
        The available particles
        """
    @particles.setter
    def particles(self, arg1: list[Particle]) -> None:
        ...
class PolynomialMultiplicity:
    """
    A multiplicity given as a polynomial series
    
    Parameters
    ----------
        lower : float
            the lower energy limit
        upper : float
            the upper energy limit
        coefficients : list of float
            the coefficients of the polynomial series (from
            lowest to highest order coefficient)
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    @typing.overload
    def __add__(self, arg0: PolynomialMultiplicity) -> PolynomialMultiplicity:
        ...
    def __call__(self, energy: float) -> float:
        """
        Evaluate the multiplicity for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> PolynomialMultiplicity:
        ...
    def __deepcopy__(self, arg0: dict) -> PolynomialMultiplicity:
        ...
    def __eq__(self, arg0: PolynomialMultiplicity) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    @typing.overload
    def __iadd__(self, arg0: PolynomialMultiplicity) -> PolynomialMultiplicity:
        ...
    def __imul__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    def __init__(self, lower: float, upper: float, coefficients: list[float]) -> None:
        """
        Initialise the polynomial multiplicity
        """
    @typing.overload
    def __isub__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    @typing.overload
    def __isub__(self, arg0: PolynomialMultiplicity) -> PolynomialMultiplicity:
        ...
    def __itruediv__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    def __mul__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    def __ne__(self, arg0: PolynomialMultiplicity) -> bool:
        ...
    def __neg__(self) -> PolynomialMultiplicity:
        ...
    def __radd__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    def __rmul__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    def __rsub__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    @typing.overload
    def __sub__(self, arg0: PolynomialMultiplicity) -> PolynomialMultiplicity:
        ...
    def __truediv__(self, arg0: float) -> PolynomialMultiplicity:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedMultiplicity:
        """
        Linearise the series
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    @property
    def coefficients(self) -> list[float]:
        """
        The series coefficients
        """
    @property
    def lower_energy_limit(self) -> float:
        """
        The lower energy limit
        """
    @property
    def order(self) -> int:
        """
        The series order
        """
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit
        """
class ProjectileTarget:
    """
    Data associated to a given projectile and target
    
    Parameters
    ----------
        documentation : njoy.dryad.Documentation, optional
            the documentation
        projectile : njoy.dryad.id.ParticleID
            the projectile identifier
        target : njoy.dryad.id.ParticleID
            the target identifier
        type : njoy.dryad.InteractionType
            the interaction type
        reactions : list of njoy.dryad.Reaction
            the reaction data
        particles : njoy.dryad.ParticleDatabase, default None
            the optional particle data
        resonances : njoy.dryad.resonances.ResonanceParameters, default None
            the optional resonance parameters
        covariances : njoy.dryad.covariance.CovarianceData, default None
            the optional covariance data
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def from_ace_file(filename: str, normalise: bool = False) -> ProjectileTarget | tuple[ProjectileTarget, ProjectileTarget]:
        """
        Create ProjectileTarget data from an ACE file
        
        Most files will produce a single ProjectileTarget. The exception here is the
        photoatomic ACE file which may yield one ProjectileTarget (pre-eprdata) or two
        ProjectileTarget for eprdata files.
        
        Parameters
        ----------
            filename : str
                the ACE file name
            normalise : bool, default False
                option to indicate whether or not to normalise
                all probability data
        """
    @staticmethod
    def from_endf_file(filename: str, normalise: bool = False) -> ProjectileTarget:
        """
        Create ProjectileTarget data from an ENDF file
        
        If there are multiple materials in the ENDF file, only the first material
        will be transformed into a ProjectileTarget.
        
        Parameters
        ----------
            filename : str
                the ENDF file name
            normalise : bool, default False
                option to indicate whether or not to normalise
                all probability data
        """
    @staticmethod
    def from_gnds_file(filename: str, normalise: bool = False) -> ProjectileTarget:
        """
        Create ProjectileTarget data from a GNDS file
        
        Parameters
        ----------
            filename : str
                the GNDS file name
            normalise : bool, default False
                option to indicate whether or not to normalise
                all probability data
        """
    def __copy__(self) -> ProjectileTarget:
        ...
    def __deepcopy__(self, arg0: dict) -> ProjectileTarget:
        ...
    def __eq__(self, arg0: ProjectileTarget) -> bool:
        ...
    @typing.overload
    def __init__(self, documentation: Documentation, projectile: id.ParticleID, target: id.ParticleID, type: InteractionType, reactions: list[Reaction], particles: ParticleDatabase | None = None, resonances: resonances.ResonanceParameters | None = None, covariances: covariance.CovarianceData | None = None, normalise: bool = False) -> None:
        """
        Initialise the ProjectileTarget with documentation
        """
    @typing.overload
    def __init__(self, projectile: id.ParticleID, target: id.ParticleID, type: InteractionType, reactions: list[Reaction], particles: ParticleDatabase | None = None, resonances: resonances.ResonanceParameters | None = None, covariances: covariance.CovarianceData | None = None, normalise: bool = False) -> None:
        """
        Initialise the ProjectileTarget without documentation
        """
    def __ne__(self, arg0: ProjectileTarget) -> bool:
        ...
    def calculate_average_energy(self, tolerance: float = 1e-08) -> None:
        """
        Calculate average outgoing energies for all reaction products
        
        Parameters
        ----------
            tolerance : float, default 1e-08
                the integration tolerance
        """
    def calculate_summation_cross_sections(self, tolerance: float = 0.001) -> None:
        """
        Calculate summation cross sections
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    def has_reaction(self, id: id.ReactionID) -> bool:
        """
        Return whether or not a reaction is present
        
        Parameters
        ----------
            id : njoy.dryad.id.ReactionID
                the reaction identifier
        """
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    def reaction(self, id: id.ReactionID) -> Reaction:
        """
        Return the requested reaction
        
        Parameters
        ----------
            id : njoy.dryad.id.ReactionID
                the reaction identifier
        """
    def to_endf_file(self, mat: int, filename: str, use_reduced_width_amplitudes: bool = True) -> None:
        """
        Write the ProjectileTarget data to an ENDF file
        
        Parameters
        ----------
            mat : int
                the ENDF mat number to be used
            filename : str
                the ENDF file name
            use_reduced_width_amplitudes : bool, default True
                if there are resonances, use reduced width amplitudes
        """
    def unionise_cross_sections(self, exclude_summation: bool = False) -> None:
        """
        Unionise cross section data
        
        This function takes all cross section data and unionises the cross section
        grids. It does not linearise the data but reevaluates the data using the
        proper interpolation types of the cross section data.
        
        By default, summation cross sections are included in the unionisation process
        unless explicitly excluded by the user. Switching on the exclusion of summation
        cross sections may be useful when the user is going to recalculate the summation
        cross sections after unionisation.
        
        Parameters
        ----------
            exclude_summation : bool, default False
                option to exclude summation reactions in the unionisation
        """
    @property
    def covariance_data(self) -> covariance.CovarianceData | None:
        """
        The covariance data
        """
    @covariance_data.setter
    def covariance_data(self, arg1: covariance.CovarianceData | None) -> None:
        ...
    @property
    def documentation(self) -> Documentation:
        """
        The documentation
        """
    @documentation.setter
    def documentation(self, arg1: Documentation) -> None:
        ...
    @property
    def interaction_type(self) -> InteractionType:
        """
        The interaction type (atomic or nuclear)
        """
    @interaction_type.setter
    def interaction_type(self, arg1: InteractionType) -> None:
        ...
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions
        """
    @property
    def particle_data(self) -> ParticleDatabase | None:
        """
        The particle data
        """
    @particle_data.setter
    def particle_data(self, arg1: ParticleDatabase | None) -> None:
        ...
    @property
    def projectile_identifier(self) -> id.ParticleID:
        """
        The projectile identifier
        """
    @projectile_identifier.setter
    def projectile_identifier(self, arg1: id.ParticleID) -> None:
        ...
    @property
    def reactions(self) -> list[Reaction]:
        """
        The reactions
        """
    @reactions.setter
    def reactions(self, arg1: list[Reaction]) -> None:
        ...
    @property
    def resonances(self) -> resonances.ResonanceParameters | None:
        """
        The resonance parameters
        """
    @resonances.setter
    def resonances(self, arg1: resonances.ResonanceParameters | None) -> None:
        ...
    @property
    def target_identifier(self) -> id.ParticleID:
        """
        The target identifier
        """
    @target_identifier.setter
    def target_identifier(self, arg1: id.ParticleID) -> None:
        ...
class Reaction:
    """
    The data associated to a single reaction
    
    Parameters
    ----------
        id : njoy.dryad.id.ReactionID
            the reaction identifier
        xs : njoy.dryad.TabulatedCrossSection
            the cross section of the reaction
        products : list of njoy.dryad.ReactionProduct, default []
            the reaction products
        mass_q : float, default None
            the mass difference Q value (default: None)
        reaction_q : float, default None
            the reaction Q value (default: None)
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    
        partials : list of njoy.dryad.id.ReactionID
            the identifiers of the partials of the reaction
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> Reaction:
        ...
    def __deepcopy__(self, arg0: dict) -> Reaction:
        ...
    def __eq__(self, arg0: Reaction) -> bool:
        ...
    @typing.overload
    def __init__(self, id: id.ReactionID, xs: TabulatedCrossSection, products: list[ReactionProduct] = [], mass_q: float | None = None, reaction_q: float | None = None, normalise: bool = False) -> None:
        """
        Initialise a primary reaction
        """
    @typing.overload
    def __init__(self, id: id.ReactionID, partials: list[id.ReactionID], xs: TabulatedCrossSection, products: list[ReactionProduct] = [], normalise: bool = False) -> None:
        """
        Initialise a summation reaction
        
        Summation reactions do not have Q values associated to them. A cross section
        weighted Q value could be calculated using the partial reactions making
        up the summation reaction.
        """
    def __ne__(self, arg0: Reaction) -> bool:
        ...
    def calculate_average_energy(self, tolerance: float = 1e-08) -> None:
        """
        Calculate average outgoing energies for all reaction products
        
        Parameters
        ----------
            tolerance : float, default 1e-08
                the integration tolerance
        """
    @typing.overload
    def has_product(self, type: id.ParticleID) -> bool:
        """
        Return whether or not a reaction product type is present regardless of chain index
        
        Parameters
        ----------
            type : njoy.dryad.id.ParticleID
                the reaction product type
        """
    @typing.overload
    def has_product(self, type: id.ParticleID, chain: int) -> bool:
        """
        Return whether or not a reaction product type is present for a given chain index
        
        Parameters
        ----------
            type : njoy.dryad.id.ParticleID
                the reaction product type
            chain : int
                the reaction product chain index
        """
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    @typing.overload
    def number_products(self) -> int:
        """
        The total number of reaction products
        """
    @typing.overload
    def number_products(self, type: id.ParticleID) -> int:
        """
        The number of reaction products of a given type regardless of the chain index
        """
    @typing.overload
    def number_products(self, type: id.ParticleID, chain: int) -> int:
        """
        The number of reaction products of a given type for a given chain index
        """
    @typing.overload
    def product(self, type: id.ParticleID, index: int = 0) -> ReactionProduct:
        """
        Return a reaction product with a given type and index regardless of the chain index
        
        Parameters
        ----------
            type : njoy.dryad.id.ParticleID
                the reaction product type
            index : int, default 0
                the reaction product index
        """
    @typing.overload
    def product(self, type: id.ParticleID, chain: int, index: int) -> ReactionProduct:
        """
        Return a reaction product with a given type, chain index and index
        
        Parameters
        ----------
            type : njoy.dryad.id.ParticleID
                the reaction product type
            chain : int
                the reaction product chain index
            index : int
                the reaction product index
        """
    @property
    def category(self) -> ReactionCategory:
        """
        The reaction category
        """
    @property
    def cross_section(self) -> TabulatedCrossSection:
        """
        The cross section
        """
    @cross_section.setter
    def cross_section(self, arg1: TabulatedCrossSection) -> None:
        ...
    @property
    def has_products(self) -> bool:
        """
        Flag indicating whether or not there are reaction products defined
        """
    @property
    def identifier(self) -> id.ReactionID:
        """
        The reaction identifier
        """
    @identifier.setter
    def identifier(self, arg1: id.ReactionID) -> None:
        ...
    @property
    def is_primary_reaction(self) -> bool:
        """
        Flag to indicate whether or not the reaction is a primary reaction
        """
    @property
    def is_summation_reaction(self) -> bool:
        """
        Flag to indicate whether or not the reaction is a summation reaction
        """
    @property
    def mass_difference_qvalue(self) -> float | None:
        """
        The mass difference Q value
        """
    @mass_difference_qvalue.setter
    def mass_difference_qvalue(self, arg1: float | None) -> None:
        ...
    @property
    def number_partial_reactions(self) -> int:
        """
        The number of partial reactions that make up this reaction
        """
    @property
    def partial_reaction_identifiers(self) -> list[id.ReactionID] | None:
        """
        The summation reaction identifiers (not defined if this is a primary
        reaction)
        """
    @partial_reaction_identifiers.setter
    def partial_reaction_identifiers(self, arg1: list[id.ReactionID] | None) -> None:
        ...
    @property
    def products(self) -> list[ReactionProduct]:
        """
        The reaction products
        """
    @products.setter
    def products(self, arg1: list[ReactionProduct]) -> None:
        ...
    @property
    def reaction_qvalue(self) -> float | None:
        """
        The reaction Q value
        """
    @reaction_qvalue.setter
    def reaction_qvalue(self, arg1: float | None) -> None:
        ...
class ReactionCategory:
    """
    The reaction category
    
    This enum is used to differentiate reaction categories in the ProjectileTarget.
    We currently have two categories: primary and summation.
    
    Members:
    
      Primary : A primary independent reaction that contributes to the total cross section
    
      Summation : A summation reaction with or without reaction products that does not count towards the total cross section
    """
    Primary: typing.ClassVar[ReactionCategory]  # value = <ReactionCategory.Primary: 1>
    Summation: typing.ClassVar[ReactionCategory]  # value = <ReactionCategory.Summation: 2>
    __members__: typing.ClassVar[dict[str, ReactionCategory]]  # value = {'Primary': <ReactionCategory.Primary: 1>, 'Summation': <ReactionCategory.Summation: 2>}
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
class ReactionProduct:
    """
    The data associated to a single reaction product
    
    Parameters
    ----------
        product : njoy.dryad.id.ParticleID
            the reaction product identifier
        multiplicity : int, njoy.dryad.TabulatedMultiplicity or njoy.dryad.PolynomialMultiplicity
            the reaction product multiplicity
        distribution : default None
            the reaction product distribution data (default: None)
        average_cosine : njoy.dryad.TabulatedAverageCosine, default None
            the average reaction product cosine (default: None)
        average_energy : njoy.dryad.TabulatedAverageEnergy, default None
            the average reaction product energy (default: None)
        parent : njoy.dryad.id.ParticleID, default None
            the parent reaction product (default: None)
        chain : int, default 0
            the chain index of the reaction product (default: 0)
        normalise : bool, default False
            option to indicate whether or not to normalise all probability
            data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> ReactionProduct:
        ...
    def __deepcopy__(self, arg0: dict) -> ReactionProduct:
        ...
    def __eq__(self, arg0: ReactionProduct) -> bool:
        ...
    def __init__(self, product: id.ParticleID, multiplicity: int | TabulatedMultiplicity | PolynomialMultiplicity, distribution: TwoBodyDistributionData | UncorrelatedDistributionData | CoherentDistributionData | IncoherentDistributionData | None = None, average_cosine: TabulatedAverageCosine | None = None, average_energy: TabulatedAverageEnergy | None = None, parent: id.ParticleID | None = None, chain: int = 0, normalise: bool = False) -> None:
        """
        Initialise the reaction product
        """
    def __ne__(self, arg0: ReactionProduct) -> bool:
        ...
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    @property
    def average_cosine(self) -> TabulatedAverageCosine | None:
        """
        The average reaction product cosine
        """
    @average_cosine.setter
    def average_cosine(self, arg1: TabulatedAverageCosine | None) -> None:
        ...
    @property
    def average_energy(self) -> TabulatedAverageEnergy | None:
        """
        The average reaction product energy
        """
    @average_energy.setter
    def average_energy(self, arg1: TabulatedAverageEnergy | None) -> None:
        ...
    @property
    def chain_index(self) -> int:
        """
        The chain index of the reaction product
        """
    @chain_index.setter
    def chain_index(self, arg1: int) -> None:
        ...
    @property
    def distribution_data(self) -> TwoBodyDistributionData | UncorrelatedDistributionData | CoherentDistributionData | IncoherentDistributionData | None:
        """
        The distribution data
        """
    @distribution_data.setter
    def distribution_data(self, arg1: TwoBodyDistributionData | UncorrelatedDistributionData | CoherentDistributionData | IncoherentDistributionData | None) -> None:
        ...
    @property
    def has_average_cosine(self) -> bool:
        """
        Flag indicating whether or not the reaction product has average reaction product cosine data
        """
    @property
    def has_average_energy(self) -> bool:
        """
        Flag indicating whether or not the reaction product has average reaction product energy data
        """
    @property
    def has_distribution_data(self) -> bool:
        """
        Flag indicating whether or not the reaction product has distribution data
        """
    @property
    def multiplicity(self) -> int | TabulatedMultiplicity | PolynomialMultiplicity:
        """
        The multiplicity
        """
    @multiplicity.setter
    def multiplicity(self, arg1: int | TabulatedMultiplicity | PolynomialMultiplicity) -> None:
        ...
    @property
    def parent_identifier(self) -> id.ParticleID | None:
        """
        The parent product identifier
        """
    @parent_identifier.setter
    def parent_identifier(self, arg1: id.ParticleID | None) -> None:
        ...
    @property
    def product_identifier(self) -> id.ParticleID:
        """
        The reaction product identifier
        """
    @product_identifier.setter
    def product_identifier(self, arg1: id.ParticleID) -> None:
        ...
class ReferenceFrame:
    """
    The reference frame type
    
    This enum is used to differentiate reference frames for distribution data
    in the ProjectileTarget. We currently distinguish two different frames:
    centre of mass or laboratory.
    
    Members:
    
      Laboratory : The data is given in the laboratory frame of reference
    
      CentreOfMass : The data is given in the centre of mass frame of reference
    """
    CentreOfMass: typing.ClassVar[ReferenceFrame]  # value = <ReferenceFrame.CentreOfMass: 1>
    Laboratory: typing.ClassVar[ReferenceFrame]  # value = <ReferenceFrame.Laboratory: 0>
    __members__: typing.ClassVar[dict[str, ReferenceFrame]]  # value = {'Laboratory': <ReferenceFrame.Laboratory: 0>, 'CentreOfMass': <ReferenceFrame.CentreOfMass: 1>}
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
class TabulatedAngularDistribution:
    """
    An angular distribution defined by a pdf and cdf using tabulated data
    
    Parameters
    ----------
        cosines : list of float
            the cosine values
        values : list of float
            the probability values
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        pdf : njoy.dryad.TabulatedAngularDistributionFunction
            the probability distribution function
        cdf : njoy.dryad.TabulatedAngularDistributionFunction
            the cumulative distribution function
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
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
    def __copy__(self) -> TabulatedAngularDistribution:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedAngularDistribution:
        ...
    def __eq__(self, arg0: TabulatedAngularDistribution) -> bool:
        ...
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the angular distribution with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the angular distribution with a single interpolation zone
        """
    @typing.overload
    def __init__(self, pdf: TabulatedAngularDistributionFunction, normalise: bool = False) -> None:
        """
        Initialise the angular distribution using a pdf
        """
    @typing.overload
    def __init__(self, pdf: TabulatedAngularDistributionFunction, cdf: TabulatedAngularDistributionFunction) -> None:
        """
        Initialise the angular distribution using a pdf and cdf
        """
    def __ne__(self, arg0: TabulatedAngularDistribution) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedAngularDistribution:
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
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def cdf(self) -> TabulatedAngularDistributionFunction:
        """
        The cumulative distribution function (cdf) of the distribution
        """
    @property
    def cosines(self) -> list[float]:
        """
        The cosine values
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def pdf(self) -> TabulatedAngularDistributionFunction:
        """
        The probability distribution function (pdf) of the distribution
        """
    @property
    def values(self) -> list[float]:
        """
        The probability values
        """
class TabulatedAngularDistributionFunction:
    """
    An angular distribution function using tabulated data
    
    Parameters
    ----------
        cosines : list of float
            the cosine values
        values : list of float
            the probability values
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedAngularDistributionFunction) -> TabulatedAngularDistributionFunction:
        ...
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the distribution for a given cosine value
        
        Parameters
        ----------
            cosine : float
                the cosine value
        """
    def __copy__(self) -> TabulatedAngularDistributionFunction:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedAngularDistributionFunction:
        ...
    def __eq__(self, arg0: TabulatedAngularDistributionFunction) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedAngularDistributionFunction) -> TabulatedAngularDistributionFunction:
        ...
    def __imul__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the angular distribution function with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the angular distribution function with a single interpolation zone
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedAngularDistributionFunction) -> TabulatedAngularDistributionFunction:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    def __mul__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    def __ne__(self, arg0: TabulatedAngularDistributionFunction) -> bool:
        ...
    def __neg__(self) -> TabulatedAngularDistributionFunction:
        ...
    def __radd__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    def __rmul__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    def __rsub__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedAngularDistributionFunction) -> TabulatedAngularDistributionFunction:
        ...
    def __truediv__(self, arg0: float) -> TabulatedAngularDistributionFunction:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedAngularDistributionFunction:
        """
        Linearise the table
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    def normalise(self) -> None:
        """
        Normalise the distribution function
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def cosines(self) -> list[float]:
        """
        The cosine values
        """
    @property
    def cumulative_integral(self) -> list[float]:
        """
        The cumulative integral of the distribution function over its domain
        """
    @property
    def integral(self) -> float:
        """
        The integral of the distribution function over its domain
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the table is linearised
        """
    @property
    def lower_cosine_limit(self) -> float:
        """
        The lower cosine limit
        """
    @property
    def mean(self) -> float:
        """
        The mean value of the distribution function over its domain
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
    def upper_cosine_limit(self) -> float:
        """
        The upper cosine limit
        """
    @property
    def values(self) -> list[float]:
        """
        The probability values
        """
class TabulatedAngularDistributions:
    """
    Angular distribution data given as tabulated data
    
    Parameters
    ----------
        grid : list of float
            the grid values
        distributions : list of njoy.dryad.TabulatedAngularDistribution
            the angular distributions
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, value: float, cosine: float) -> float:
        """
        Evaluate the angular distribution for a given grid and cosine value
        
        Parameters
        ----------
            value : float
                the grid value
            cosine : float
                the cosine value
        """
    def __copy__(self) -> TabulatedAngularDistributions:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedAngularDistributions:
        ...
    def __eq__(self, arg0: TabulatedAngularDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[TabulatedAngularDistribution], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the angular distributions with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[TabulatedAngularDistribution], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the angular distributions with a single interpolation zone
        """
    def __ne__(self, arg0: TabulatedAngularDistributions) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedAngularDistributions:
        """
        Linearise the distributions
        
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
        Normalise the distributions
        
        Note: all distributions should have the same integral over their domain
              to avoid changing the full distribution (ie the normalisation moves
              every distribution up or down by the same amount to avoid changing
              the full distribution shape).
        """
    @property
    def average_cosines(self) -> TabulatedAverageCosine:
        """
        The average cosine values
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def distributions(self) -> list[TabulatedAngularDistribution]:
        """
        The associated distributions
        """
    @property
    def grid(self) -> list[float]:
        """
        The grid values for which distributions are given
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
class TabulatedAverageCosine:
    """
    An average cosine table
    
    Parameters
    ----------
        energies : list of float
            the energy values
        values : list of float
            the average cosine values
        boundaries : list of int, optional
            the boundaries of the interpolation regions
        interpolants : list of InterpolationType, optional
            the interpolation types of the interpolation regions
        interpolant : InterpolationType, default=LinearLinear
            the interpolation type for single-region tables
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedAverageCosine) -> TabulatedAverageCosine:
        ...
    def __call__(self, energy: float) -> float:
        """
        Evaluate the table for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> TabulatedAverageCosine:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedAverageCosine:
        ...
    def __eq__(self, arg0: TabulatedAverageCosine) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedAverageCosine) -> TabulatedAverageCosine:
        ...
    def __imul__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the average cosine table with multiple interpolation regions
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the average cosine table with single interpolation type
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedAverageCosine) -> TabulatedAverageCosine:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    def __mul__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    def __ne__(self, arg0: TabulatedAverageCosine) -> bool:
        ...
    def __neg__(self) -> TabulatedAverageCosine:
        ...
    def __radd__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    def __rmul__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    def __rsub__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedAverageCosine) -> TabulatedAverageCosine:
        ...
    def __truediv__(self, arg0: float) -> TabulatedAverageCosine:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedAverageCosine:
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
    def energies(self) -> list[float]:
        """
        The energy values
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
        The average cosine values
        """
class TabulatedAverageEnergy:
    """
    An average reaction product energy table
    
    Parameters
    ----------
        energies : list of float
            the energy values
        values : list of float
            the average energy values
        boundaries : list of int, optional
            the boundaries of the interpolation regions
        interpolants : list of InterpolationType, optional
            the interpolation types of the interpolation regions
        interpolant : InterpolationType, default=LinearLinear
            the interpolation type for single-region tables
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedAverageEnergy) -> TabulatedAverageEnergy:
        ...
    def __call__(self, energy: float) -> float:
        """
        Evaluate the table for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> TabulatedAverageEnergy:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedAverageEnergy:
        ...
    def __eq__(self, arg0: TabulatedAverageEnergy) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedAverageEnergy) -> TabulatedAverageEnergy:
        ...
    def __imul__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the average reaction product energy table with multiple interpolation regions
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the average reaction product energy table with a single interpolation region
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedAverageEnergy) -> TabulatedAverageEnergy:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    def __mul__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    def __ne__(self, arg0: TabulatedAverageEnergy) -> bool:
        ...
    def __neg__(self) -> TabulatedAverageEnergy:
        ...
    def __radd__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    def __rmul__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    def __rsub__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedAverageEnergy) -> TabulatedAverageEnergy:
        ...
    def __truediv__(self, arg0: float) -> TabulatedAverageEnergy:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedAverageEnergy:
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
    def energies(self) -> list[float]:
        """
        The energy values
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
        The average energy values
        """
class TabulatedComptonProfile:
    """
    A Compton profile for an electron subshell defined by a pdf and cdf using tabulated data
    
    Compton profiles are not available in standard evaluated nuclear data files. They are used for
    photoatomic transport data in Monte Carlo codes like MCNP, which currently get this data form
    external sources. 
    
    Parameters
    ----------
        subshell_identifier : njoy.dryad.id.ElectronSubshellID
            the electron subshell identifier
        momentum : list of float
            the momentum values
        values : list of float
            the probability values
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        normalise : bool, default false
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, momentum: float) -> float:
        """
        Evaluate the pdf of the Compton profile for a given momentum value 
        
        Parameters
        ----------
            momentum : float
                the momentum value
        """
    def __copy__(self) -> TabulatedComptonProfile:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedComptonProfile:
        ...
    def __eq__(self, arg0: TabulatedComptonProfile) -> bool:
        ...
    @typing.overload
    def __init__(self, subshell_identifier: id.ElectronSubshellID, momentum: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the compton profile with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, subshell_identifier: id.ElectronSubshellID, momentum: list[float], values: list[float], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the compton profile with a single interpolation zone
        """
    def __ne__(self, arg0: TabulatedComptonProfile) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedComptonProfile:
        """
        Linearise the distributions
        
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
    def average_momentum(self) -> float:
        """
        The average momentum defined by the distribution
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def cdf(self) -> TabulatedComptonProfileFunction:
        """
        The cumulative distribution function (cdf) of the distribution
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def momentum(self) -> list[float]:
        """
        The momentum values
        """
    @property
    def pdf(self) -> TabulatedComptonProfileFunction:
        """
        The probability distribution function (pdf) of the distribution
        """
    @property
    def subshell_identifier(self) -> id.ElectronSubshellID:
        """
        The electron subshell identifier
        """
    @property
    def values(self) -> list[float]:
        """
        The probability values
        """
class TabulatedComptonProfileFunction:
    """
    A Compton profile distribution using tabulated data
    
    Parameters
    ----------
        momentum : list of float
            the momentum values
        values : list of float
            the probability values
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        normalise : bool, default false
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedComptonProfileFunction) -> TabulatedComptonProfileFunction:
        ...
    def __call__(self, momentum: float) -> float:
        """
        Evaluate the Compton profile for a given momentum value
        
        Parameters
        ----------
            momentum : float
                the momentum value
        """
    def __copy__(self) -> TabulatedComptonProfileFunction:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedComptonProfileFunction:
        ...
    def __eq__(self, arg0: TabulatedComptonProfileFunction) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedComptonProfileFunction) -> TabulatedComptonProfileFunction:
        ...
    def __imul__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    @typing.overload
    def __init__(self, momentum: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the compton profile function with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, momentum: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the compton profile function with a single interpolation zone
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedComptonProfileFunction) -> TabulatedComptonProfileFunction:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    def __mul__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    def __ne__(self, arg0: TabulatedComptonProfileFunction) -> bool:
        ...
    def __neg__(self) -> TabulatedComptonProfileFunction:
        ...
    def __radd__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    def __rmul__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    def __rsub__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedComptonProfileFunction) -> TabulatedComptonProfileFunction:
        ...
    def __truediv__(self, arg0: float) -> TabulatedComptonProfileFunction:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedComptonProfileFunction:
        """
        Linearise the table
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    def normalise(self) -> None:
        """
        Normalise the distribution function
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def cumulative_integral(self) -> list[float]:
        """
        The cumulative integral of the Compton profile function over its domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the Compton profile function over its domain
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the table is linearised
        """
    @property
    def lower_momentum_limit(self) -> float:
        """
        The lower momentum limit
        """
    @property
    def momentum(self) -> list[float]:
        """
        The momentum values
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
    def upper_momentum_limit(self) -> float:
        """
        The upper momentum limit
        """
    @property
    def values(self) -> list[float]:
        """
        The probability values
        """
class TabulatedCrossSection:
    """
    A cross section table
    
    Parameters
    ----------
        energies : list of float
            the energy values
        values : list of float
            the cross section values
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedCrossSection:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedCrossSection) -> TabulatedCrossSection:
        ...
    def __call__(self, energy: float) -> float:
        """
        Evaluate the table for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> TabulatedCrossSection:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedCrossSection:
        ...
    def __eq__(self, arg0: TabulatedCrossSection) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedCrossSection:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedCrossSection) -> TabulatedCrossSection:
        ...
    def __imul__(self, arg0: float) -> TabulatedCrossSection:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the cross section table with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the cross section table with a single interpolation zone
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedCrossSection:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedCrossSection) -> TabulatedCrossSection:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedCrossSection:
        ...
    def __mul__(self, arg0: float) -> TabulatedCrossSection:
        ...
    def __ne__(self, arg0: TabulatedCrossSection) -> bool:
        ...
    def __neg__(self) -> TabulatedCrossSection:
        ...
    def __radd__(self, arg0: float) -> TabulatedCrossSection:
        ...
    def __rmul__(self, arg0: float) -> TabulatedCrossSection:
        ...
    def __rsub__(self, arg0: float) -> TabulatedCrossSection:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedCrossSection:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedCrossSection) -> TabulatedCrossSection:
        ...
    def __truediv__(self, arg0: float) -> TabulatedCrossSection:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedCrossSection:
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
    def energies(self) -> list[float]:
        """
        The energy values
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
        The cross section values
        """
class TabulatedEnergyDistribution:
    """
    An energy distribution defined by a pdf and cdf using tabulated data
    
    Parameters
    ----------
        energies : list of float
            the energy values
        values : list of float
            the probability values
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        pdf : njoy.dryad.TabulatedEnergyDistributionFunction
            the probability distribution function
        cdf : njoy.dryad.TabulatedEnergyDistributionFunction
            the cumulative distribution function
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, energy: float) -> float:
        """
        Evaluate the pdf of the distribution for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> TabulatedEnergyDistribution:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedEnergyDistribution:
        ...
    def __eq__(self, arg0: TabulatedEnergyDistribution) -> bool:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the energy distribution with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the energy distribution with a single interpolation zone
        """
    @typing.overload
    def __init__(self, pdf: TabulatedEnergyDistributionFunction, normalise: bool = False) -> None:
        """
        Initialise the energy distribution using a pdf
        """
    @typing.overload
    def __init__(self, pdf: TabulatedEnergyDistributionFunction, cdf: TabulatedEnergyDistributionFunction) -> None:
        """
        Initialise the energy distribution using a pdf and cdf
        """
    def __ne__(self, arg0: TabulatedEnergyDistribution) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedEnergyDistribution:
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
    def average_energy(self) -> float:
        """
        The average energy defined by the distribution
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def cdf(self) -> TabulatedEnergyDistributionFunction:
        """
        The cumulative distribution function (cdf) of the distribution
        """
    @property
    def energies(self) -> list[float]:
        """
        The energy values
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def pdf(self) -> TabulatedEnergyDistributionFunction:
        """
        The probability distribution function (pdf) of the distribution
        """
    @property
    def values(self) -> list[float]:
        """
        The probability values
        """
class TabulatedEnergyDistributionFunction:
    """
    An energy distribution function using tabulated data
    
    Parameters
    ----------
        energies : list of float
            the energy values
        values : list of float
            the probability values
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedEnergyDistributionFunction) -> TabulatedEnergyDistributionFunction:
        ...
    def __call__(self, energy: float) -> float:
        """
        Evaluate the distribution for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> TabulatedEnergyDistributionFunction:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedEnergyDistributionFunction:
        ...
    def __eq__(self, arg0: TabulatedEnergyDistributionFunction) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedEnergyDistributionFunction) -> TabulatedEnergyDistributionFunction:
        ...
    def __imul__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the energy distribution function with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the energy distribution function with a single interpolation zone
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedEnergyDistributionFunction) -> TabulatedEnergyDistributionFunction:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    def __mul__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    def __ne__(self, arg0: TabulatedEnergyDistributionFunction) -> bool:
        ...
    def __neg__(self) -> TabulatedEnergyDistributionFunction:
        ...
    def __radd__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    def __rmul__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    def __rsub__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedEnergyDistributionFunction) -> TabulatedEnergyDistributionFunction:
        ...
    def __truediv__(self, arg0: float) -> TabulatedEnergyDistributionFunction:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedEnergyDistributionFunction:
        """
        Linearise the table
        
        Parameters
        ----------
            tolerance : float, default 0.001
                the linearisation tolerance
        """
    def normalise(self) -> None:
        """
        Normalise the distribution function
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def cumulative_integral(self) -> list[float]:
        """
        The cumulative integral of the distribution function over its domain
        """
    @property
    def energies(self) -> list[float]:
        """
        The energy values
        """
    @property
    def integral(self) -> float:
        """
        The integral of the distribution function over its domain
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
    def mean(self) -> float:
        """
        The mean value of the distribution function over its domain
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
        The probability values
        """
class TabulatedEnergyDistributions:
    """
    Energy distribution data given as tabulated data
    
    Parameters
    ----------
        grid : list of float
            the grid values
        distributions : list of njoy.dryad.TabulatedEnergyDistribution
            the energy distributions
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear
            the interpolation type (default lin-lin)
        normalise : bool, default False
            option to indicate whether or not to normalise
            all probability data (default: no normalisation)
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, value: float, energy: float) -> float:
        """
        Evaluate the energy distribution for a given grid and energy value
        
        Parameters
        ----------
            value : float
                the grid value
            energy : float
                the energy value
        """
    def __copy__(self) -> TabulatedEnergyDistributions:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedEnergyDistributions:
        ...
    def __eq__(self, arg0: TabulatedEnergyDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[TabulatedEnergyDistribution], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the energy distributions with multiple interpolation zones
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[TabulatedEnergyDistribution], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the energy distributions with a single interpolation zone
        """
    def __ne__(self, arg0: TabulatedEnergyDistributions) -> bool:
        ...
    def linearise(self, tolerance: float = 0.001, normalise: bool = False) -> TabulatedEnergyDistributions:
        """
        Linearise the distributions
        
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
        Normalise the distributions
        
        Note: all distributions should have the same integral over their domain
              to avoid changing the full distribution (ie the normalisation moves
              every distribution up or down by the same amount to avoid changing
              the full distribution shape).
        """
    @property
    def average_energies(self) -> TabulatedAverageEnergy:
        """
        The average energy values
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def distributions(self) -> list[TabulatedEnergyDistribution]:
        """
        The associated distributions
        """
    @property
    def grid(self) -> list[float]:
        """
        The grid values for which distributions are given
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
class TabulatedFormFactor:
    """
    A form factor table
    
    Parameters
    ----------
        energies : list of float
            the energy values
        values : list of float
            the form factor values
        boundaries : list of int, optional
            the boundaries of the interpolation regions
        interpolants : list of InterpolationType, optional
            the interpolation types of the interpolation regions
        interpolant : InterpolationType, default=LinearLinear
            the interpolation type for single-region tables
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedFormFactor:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedFormFactor) -> TabulatedFormFactor:
        ...
    def __call__(self, energy: float) -> float:
        """
        Evaluate the table for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> TabulatedFormFactor:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedFormFactor:
        ...
    def __eq__(self, arg0: TabulatedFormFactor) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedFormFactor:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedFormFactor) -> TabulatedFormFactor:
        ...
    def __imul__(self, arg0: float) -> TabulatedFormFactor:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the form factor table with multiple interpolation regions
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the form factor table with a single interpolation region
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedFormFactor:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedFormFactor) -> TabulatedFormFactor:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedFormFactor:
        ...
    def __mul__(self, arg0: float) -> TabulatedFormFactor:
        ...
    def __ne__(self, arg0: TabulatedFormFactor) -> bool:
        ...
    def __neg__(self) -> TabulatedFormFactor:
        ...
    def __radd__(self, arg0: float) -> TabulatedFormFactor:
        ...
    def __rmul__(self, arg0: float) -> TabulatedFormFactor:
        ...
    def __rsub__(self, arg0: float) -> TabulatedFormFactor:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedFormFactor:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedFormFactor) -> TabulatedFormFactor:
        ...
    def __truediv__(self, arg0: float) -> TabulatedFormFactor:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedFormFactor:
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
    def energies(self) -> list[float]:
        """
        The energy values
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
        The form factor values
        """
class TabulatedMultiplicity:
    """
    A multiplicity table
    
    Parameters
    ----------
        energies : list of float
            the energy values
        values : list of float
            the multiplicity values
        boundaries : list of int, optional
            the boundaries of the interpolation regions
        interpolants : list of InterpolationType, optional
            the interpolation types of the interpolation regions
        interpolant : InterpolationType, default=LinearLinear
            the interpolation type for single-region tables
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedMultiplicity) -> TabulatedMultiplicity:
        ...
    def __call__(self, energy: float) -> float:
        """
        Evaluate the table for a given energy value
        
        Parameters
        ----------
            energy : float
                the energy value
        """
    def __copy__(self) -> TabulatedMultiplicity:
        ...
    def __deepcopy__(self, arg0: dict) -> TabulatedMultiplicity:
        ...
    def __eq__(self, arg0: TabulatedMultiplicity) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    @typing.overload
    def __iadd__(self, arg0: TabulatedMultiplicity) -> TabulatedMultiplicity:
        ...
    def __imul__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the multiplicity table with multiple interpolation regions
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the multiplicity table with single interpolation type
        """
    @typing.overload
    def __isub__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    @typing.overload
    def __isub__(self, arg0: TabulatedMultiplicity) -> TabulatedMultiplicity:
        ...
    def __itruediv__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    def __mul__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    def __ne__(self, arg0: TabulatedMultiplicity) -> bool:
        ...
    def __neg__(self) -> TabulatedMultiplicity:
        ...
    def __radd__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    def __rmul__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    def __rsub__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    @typing.overload
    def __sub__(self, arg0: TabulatedMultiplicity) -> TabulatedMultiplicity:
        ...
    def __truediv__(self, arg0: float) -> TabulatedMultiplicity:
        ...
    def linearise(self, tolerance: float = 0.001) -> TabulatedMultiplicity:
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
    def energies(self) -> list[float]:
        """
        The energy values
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
        The multiplicity values
        """
class TabulatedScatteringFunction:
    """
    A scattering function table
    
    Parameters
    ----------
        inverse_lengths : list of float
            the inverse length values
        values : list of float
            the scattering function values
        boundaries : list of int, optional
            the boundaries of the interpolation regions
        interpolants : list of InterpolationType, optional
            the interpolation types of the interpolation regions
        interpolant : InterpolationType, default=LinearLinear
            the interpolation type for single-region tables
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> TabulatedScatteringFunction:
        ...
    @typing.overload
    def __add__(self, arg0: TabulatedScatteringFunction) -> TabulatedScatteringFunction:
        ...
    @typing.overload
    def __call__(self, inverse_length: float) -> float:
        """
        Evaluate the table for a given inverse length value
        
        Parameters
        ----------
            inverse_length : float
                the inverse length value
        """
    @typing.overload
    def __call__(self, energy: float, cosine: float) -> float:
        """
        Evaluate the table for a given energy,cosine pair
        
        Parameters
        ----------
            energy : float
                the incident photon energy
            cosine : float
                the outgoing photon cosine
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
    def __init__(self, inverse_lengths: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the scattering function table with multiple interpolation regions
        """
    @typing.overload
    def __init__(self, inverse_lengths: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the scattering function table with single interpolation type
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
    def inverse_length(self, energy: float, cosine: float) -> float:
        """
        Calculate the inverse length value associated to an energy,cosine pair
        
        Parameters
        ----------
            energy : float
                the incident photon energy
            cosine : float
                the outgoing photon cosine
        """
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
    def interpolants(self) -> list[InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def inverse_lengths(self) -> list[float]:
        """
        The inverse length values
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the table is linearised
        """
    @property
    def lower_inverse_length_limit(self) -> float:
        """
        The lower inverse length limit
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
    def upper_inverse_length_limit(self) -> float:
        """
        The upper inverse length limit
        """
    @property
    def values(self) -> list[float]:
        """
        The scattering function values
        """
class ThermalScattering:
    """
    Thermal scattering data
    
    Parameters
    ----------
        documentation : njoy.dryad.Documentation
            the documentation associated to the thermal scattering data
        coherent : njoy.dryad.thermal.CoherentElasticScattering
            coherent elastic scattering data (default: none)    incoherent : njoy.dryad.thermal.IncoherentElasticScattering
            incoherent elastic scattering data (default: none)
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def from_endf_file(lower: float, upper: float, filename: str) -> ThermalScattering:
        """
        Create ThermalScattering data from an ENDF file
        
        If there are multiple materials in the ENDF file, only the first material
        will be transformed into a ThermalScattering instance.
        
        Parameters
        ----------
            lower : float
                the lower energy limit
            upper : float
                the upper energy limit
            filename : string
                the ENDF file name
        """
    @staticmethod
    def from_gnds_file(lower: float, upper: float, filename: str, style: str = 'eval') -> ThermalScattering:
        """
        Create ThermalScattering data from a GNDS file
        
        Parameters
        ----------
            lower : float
                the lower energy limit
            upper : float
                the upper energy limit
            filename : string
                the GNDS file name
            style : string
                the GNDS style to process (default is eval)
        """
    def __copy__(self) -> ThermalScattering:
        ...
    def __deepcopy__(self, arg0: dict) -> ThermalScattering:
        ...
    def __eq__(self, arg0: ThermalScattering) -> bool:
        ...
    @typing.overload
    def __init__(self, documentation: Documentation, coherent: thermal.CoherentElasticScattering | None = None, incoherent: thermal.IncoherentElasticScattering | None = None) -> None:
        """
        Initialise the thermal scattering data with documentation
        """
    @typing.overload
    def __init__(self, coherent: thermal.CoherentElasticScattering | None = None, incoherent: thermal.IncoherentElasticScattering | None = None) -> None:
        """
        Initialise the thermal scattering data without documentation
        """
    def __ne__(self, arg0: ThermalScattering) -> bool:
        ...
    def to_endf_file(self, za: int, mat: int, filename: str) -> None:
        """
        Write the ThermalScattering data to an ENDF file
        
        Parameters
        ----------
            za : int
                the ENDF za number to be used
            mat : int
                the ENDF mat number to be used
            filename : string
                the ENDF file name
        """
    @property
    def coherent_elastic_scattering(self) -> thermal.CoherentElasticScattering | None:
        """
        The coherent elastic data
        """
    @coherent_elastic_scattering.setter
    def coherent_elastic_scattering(self, arg1: thermal.CoherentElasticScattering | None) -> None:
        ...
    @property
    def documentation(self) -> Documentation:
        """
        The documentation
        """
    @documentation.setter
    def documentation(self, arg1: Documentation) -> None:
        ...
    @property
    def has_coherent_elastic_scattering(self) -> bool:
        """
        Return whether or not there is coherent elastic scattering
        """
    @property
    def has_elastic_scattering(self) -> bool:
        """
        Return whether or not there is elastic scattering (coherent and/or incoherent)
        """
    @property
    def has_incoherent_elastic_scattering(self) -> bool:
        """
        Return whether or not there is incoherent elastic scattering
        """
    @property
    def has_inelastic_scattering(self) -> bool:
        """
        Return whether or not there is inelastic scattering
        """
    @property
    def incoherent_elastic_scattering(self) -> thermal.IncoherentElasticScattering | None:
        """
        The incoherent elastic data
        """
    @incoherent_elastic_scattering.setter
    def incoherent_elastic_scattering(self, arg1: thermal.IncoherentElasticScattering | None) -> None:
        ...
class TwoBodyDistributionData:
    """
    The energy-angle distribution data for a two-body output channel
    
    In this representation, only the angular distributions as a function of
    incident energy is given and the outgoing particle's energy can be derived
    through kinematics.
    
    For incident neutron data, this corresponds with elastic and inelastic
    scattering data given in MF4 (none of these will have corresponding MF5
    data). In the more general MF6 representation, this corresponds with
    LAW = 2 (discrete two-body scattering). This is also the representation for
    elastic scattering data in MF26 for electro-atomic interactions.
    
    Parameters
    ----------
        frame : njoy.dryad.ReferenceFrame
            the reference frame of the distribution data
        angle : njoy.dryad.IsotropicAngularDistributions, njoy.dryad.LegendreAngularDistributions, or njoy.dryad.TabulatedAngularDistributions
            the angular distributions
        normalise : bool, default False
            option to indicate whether or not to normalise all probability data
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> TwoBodyDistributionData:
        ...
    def __deepcopy__(self, arg0: dict) -> TwoBodyDistributionData:
        ...
    def __eq__(self, arg0: TwoBodyDistributionData) -> bool:
        ...
    def __init__(self, frame: ReferenceFrame, angle: IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions | MixedAngularDistributions, normalise: bool = False) -> None:
        """
        Initialise the two-body distribution data
        """
    def __ne__(self, arg0: TwoBodyDistributionData) -> bool:
        ...
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    @property
    def angle(self) -> IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions | MixedAngularDistributions:
        """
        The angular distributions
        """
    @angle.setter
    def angle(self, arg1: IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions | MixedAngularDistributions) -> None:
        ...
    @property
    def frame(self) -> ReferenceFrame:
        """
        The reference frame
        """
    @frame.setter
    def frame(self, arg1: ReferenceFrame) -> None:
        ...
    @property
    def type(self) -> DistributionDataType:
        """
        The distribution data type
        """
class UncorrelatedDistributionData:
    """
    Uncorrelated energy and angle distribution data for a reaction product
    
    In this representation, there is no correlation given between the outgoing
    angle and energy of the reaction product. As a result, the angular and energy
    distributions of the reaction product depend only on the incident energy of the
    projectile.
    
    For incident neutron data, this is used for reactions that have both MF4 and MF5
    data. For reaction products given in MF6, this corresponds to LAW = 1 (continuum
    energy-angle distributions) in which the angular dependence is fully isotropic.
    This is also the representation for Brehmstrahlung and excitation data in MF26
    for electro-atomic interactions.
    
    Parameters
    ----------
        frame : njoy.dryad.ReferenceFrame
            the reference frame of the distribution data
        angle : njoy.dryad.IsotropicAngularDistributions, njoy.dryad.LegendreAngularDistributions, or njoy.dryad.TabulatedAngularDistributions
            the angular distributions
        energy : njoy.dryad.MultiEnergyDistributions or njoy.dryad.TabulatedEnergyDistributions
            the energy distributions
        normalise : bool, default False
            option to indicate whether or not to normalise all probability data
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> UncorrelatedDistributionData:
        ...
    def __deepcopy__(self, arg0: dict) -> UncorrelatedDistributionData:
        ...
    def __eq__(self, arg0: UncorrelatedDistributionData) -> bool:
        ...
    def __init__(self, frame: ReferenceFrame, angle: IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions | MixedAngularDistributions, energy: MultiEnergyDistributions | TabulatedEnergyDistributions, normalise: bool = False) -> None:
        """
        Initialise the uncorrelated distribution data
        """
    def __ne__(self, arg0: UncorrelatedDistributionData) -> bool:
        ...
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    @property
    def angle(self) -> IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions | MixedAngularDistributions:
        """
        The angular distributions
        """
    @angle.setter
    def angle(self, arg1: IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions | MixedAngularDistributions) -> None:
        ...
    @property
    def energy(self) -> MultiEnergyDistributions | TabulatedEnergyDistributions:
        """
        The energy distributions
        """
    @energy.setter
    def energy(self, arg1: MultiEnergyDistributions | TabulatedEnergyDistributions) -> None:
        ...
    @property
    def frame(self) -> ReferenceFrame:
        """
        The reference frame
        """
    @frame.setter
    def frame(self, arg1: ReferenceFrame) -> None:
        ...
    @property
    def type(self) -> DistributionDataType:
        """
        The distribution data type
        """
class UniformAngularDistribution:
    """
    A uniform or equally probable angular distribution
    
    The uniform distribution can be defined for discrete values
    (e.g. as used in inelastic thermal scattering ACE files) or
    cosine intervals (e.g. as used in older incident neutron ACE
    files).
    
    Parameters
    ----------
        cosines : list of float
            the cosine values
        type : njoy.dryad.UniformDistributionType
            the uniform distribution type
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> UniformAngularDistribution:
        ...
    def __deepcopy__(self, arg0: dict) -> UniformAngularDistribution:
        ...
    def __eq__(self, arg0: UniformAngularDistribution) -> bool:
        ...
    def __init__(self, cosines: list[float], type: UniformDistributionType) -> None:
        """
        Initialise the angular distribution
        """
    def __ne__(self, arg0: UniformAngularDistribution) -> bool:
        ...
    @property
    def average_cosine(self) -> float:
        """
        The average cosine defined by the distribution
        """
    @property
    def cosines(self) -> list[float]:
        """
        The cosine values for the distribution
        """
    @property
    def number_cosines(self) -> int:
        """
        The number of discrete cosines or intervals
        """
    @property
    def type(self) -> UniformDistributionType:
        """
        The distribution type
        """
class UniformAngularDistributions:
    """
    Angular distribution data given as uniform distributions
    
    Parameters
    ----------
        grid : list of float
            the grid values
        distributions : list of njoy.dryad.UniformAngularDistribution
            the associated distributions
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default LinearLinear
            the interpolation type
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> UniformAngularDistributions:
        ...
    def __deepcopy__(self, arg0: dict) -> UniformAngularDistributions:
        ...
    def __eq__(self, arg0: UniformAngularDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[UniformAngularDistribution], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the angular distributions with multiple interpolation regions
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[UniformAngularDistribution], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the angular distributions with a single interpolation region
        """
    def __ne__(self, arg0: UniformAngularDistributions) -> bool:
        ...
    @property
    def average_cosines(self) -> TabulatedAverageCosine:
        """
        The average cosine values
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def distributions(self) -> list[UniformAngularDistribution]:
        """
        The associated distributions
        """
    @property
    def grid(self) -> list[float]:
        """
        The grid values for which distributions are given
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
class UniformDistributionType:
    """
    The uniform distribution type
    
    This enum is used to differentiate uniform distribution types, either discrete
    values or intervals.
    
    Members:
    
      Discrete : The uniform distribution is given for discrete values
    
      Interval : The uniform distribution is given for intervals
    """
    Discrete: typing.ClassVar[UniformDistributionType]  # value = <UniformDistributionType.Discrete: 1>
    Interval: typing.ClassVar[UniformDistributionType]  # value = <UniformDistributionType.Interval: 2>
    __members__: typing.ClassVar[dict[str, UniformDistributionType]]  # value = {'Discrete': <UniformDistributionType.Discrete: 1>, 'Interval': <UniformDistributionType.Interval: 2>}
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
class UniformEnergyDistribution:
    """
    A uniform or equally probable energy distribution
    
    Parameters
    ----------
        energies : list of float
            the energy values
        type : njoy.dryad.UniformDistributionType
            the uniform distribution type
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> UniformEnergyDistribution:
        ...
    def __deepcopy__(self, arg0: dict) -> UniformEnergyDistribution:
        ...
    def __eq__(self, arg0: UniformEnergyDistribution) -> bool:
        ...
    def __init__(self, energies: list[float], type: UniformDistributionType) -> None:
        """
        Initialise the energy distribution
        """
    def __ne__(self, arg0: UniformEnergyDistribution) -> bool:
        ...
    @property
    def average_energy(self) -> float:
        """
        The average energy defined by the distribution
        """
    @property
    def energies(self) -> list[float]:
        """
        The energy values for the distribution
        """
    @property
    def number_energies(self) -> int:
        """
        The number of discrete energies or intervals
        """
    @property
    def type(self) -> UniformDistributionType:
        """
        The distribution type
        """
class UniformEnergyDistributions:
    """
    Energy distribution data given as uniform distributions
    
    Parameters
    ----------
        grid : list of float
            the grid values
        distributions : list of njoy.dryad.UniformEnergyDistribution
            the associated distributions
        boundaries : list of int
            the boundaries of the interpolation regions
        interpolants : list of njoy.dryad.InterpolationType
            the interpolation types of the interpolation regions
        interpolant : njoy.dryad.InterpolationType, default LinearLinear
            the interpolation type
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> UniformEnergyDistributions:
        ...
    def __deepcopy__(self, arg0: dict) -> UniformEnergyDistributions:
        ...
    def __eq__(self, arg0: UniformEnergyDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[UniformEnergyDistribution], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the energy distributions with multiple interpolation regions
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[UniformEnergyDistribution], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the energy distributions with a single interpolation region
        """
    def __ne__(self, arg0: UniformEnergyDistributions) -> bool:
        ...
    @property
    def average_energies(self) -> TabulatedAverageEnergy:
        """
        The average energy values
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def distributions(self) -> list[UniformEnergyDistribution]:
        """
        The associated distributions
        """
    @property
    def grid(self) -> list[float]:
        """
        The grid values for which distributions are given
        """
    @property
    def interpolants(self) -> list[InterpolationType]:
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
