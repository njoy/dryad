from __future__ import annotations
import typing
from . import atomic
from . import covariance
from . import id
from . import resonances
__all__ = ['AtomicRelaxation', 'CoherentDistributionData', 'DistributionDataType', 'Documentation', 'IncoherentDistributionData', 'InteractionType', 'InterpolationType', 'IsotropicAngularDistributions', 'LegendreAngularDistribution', 'LegendreAngularDistributionFunction', 'LegendreAngularDistributions', 'MultiEnergyDistributions', 'PolynomialMultiplicity', 'ProjectileTarget', 'Reaction', 'ReactionCategory', 'ReactionProduct', 'ReferenceFrame', 'TabulatedAngularDistribution', 'TabulatedAngularDistributionFunction', 'TabulatedAngularDistributions', 'TabulatedAverageCosine', 'TabulatedAverageEnergy', 'TabulatedCrossSection', 'TabulatedEnergyDistribution', 'TabulatedEnergyDistributionFunction', 'TabulatedEnergyDistributions', 'TabulatedFormFactor', 'TabulatedMultiplicity', 'TabulatedScatteringFunction', 'ToleranceConvergence', 'TwoBodyDistributionData', 'UncorrelatedDistributionData', 'UniformAngularDistribution', 'UniformAngularDistributions', 'UniformDistributionType', 'UniformEnergyDistribution', 'UniformEnergyDistributions', 'atomic', 'covariance', 'id', 'resonances']
class AtomicRelaxation:
    """
    Atomic relaxation data for a given element
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def from_endf_file(filename: str, normalise: bool = False) -> AtomicRelaxation:
        """
        Create AtomicRelaxation data from an ENDF file
        
        If there are multiple materials in the ENDF file, only the first material
        will be transformed into a AtomicRelaxation.
        
        Arguments:
            filename    the ENDF file name
            normalise   option to indicate whether or not to normalise
                        all probability data (default: no normalisation)
        """
    @staticmethod
    def from_gnds_file(filename: str, normalise: bool = False) -> AtomicRelaxation:
        """
        Create AtomicRelaxation data from a GNDS file
        
        Arguments:
            filename    the GNDS file name
            normalise   option to indicate whether or not to normalise
                        all probability data (default: no normalisation)
        """
    def __eq__(self, arg0: AtomicRelaxation) -> bool:
        ...
    @typing.overload
    def __init__(self, documentation: Documentation, element: id.ElementID, subshells: list[atomic.ElectronSubshellConfiguration], normalise: bool = False) -> None:
        """
        Initialise the atomic relaxation data
        
        Arguments:
            self            the reaction
            documentation   the documentation
            element         the element identifier
            subshells       the electron subshell configuration data
            normalise       option to indicate whether or not to normalise
                            all probability data (default: no normalisation)
        """
    @typing.overload
    def __init__(self, element: id.ElementID, subshells: list[atomic.ElectronSubshellConfiguration], normalise: bool = False) -> None:
        """
        Initialise the atomic relaxation data
        
        Arguments:
            self        the reaction
            element     the element identifier
            subshells   the electron subshell configuration data
            normalise   option to indicate whether or not to normalise
                        all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: AtomicRelaxation) -> bool:
        ...
    def calculate_transition_energies(self) -> None:
        """
        Calculate the transition energies for all transitions
        """
    def has_subshell(self, arg0: id.ElectronSubshellID) -> bool:
        """
        Return whether or not a subshell is present
        
        Arguments:
            self   the AtomicRelaxation data
            id     the electron subshell identifier
        """
    def normalise(self) -> None:
        """
        Normalise the transition probabilities
        """
    def subshell(self, arg0: id.ElectronSubshellID) -> atomic.ElectronSubshellConfiguration:
        """
        Return the requested subshell
        
        Arguments:
            self   the AtomicRelaxation data
            id     the electron subshell identifier
        """
    def to_endf_file(self, filename: str) -> None:
        """
        Write the AtomicRelaxation data to an ENDF file
        
        Arguments:
            self        the atomic relaxation data
            filename    the ENDF file name
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
    
    In this representation, a scattering function S(x,Z) and two optional form factor
    functions are defined which together with the Thompson cross section determine the
    double differential cross section.
    
    This corresponds with the coherent scattering function data given in MF27 MT502 and
    the form factors in MF27 MT505 and MT506.
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: CoherentDistributionData) -> bool:
        ...
    @typing.overload
    def __init__(self, frame: ReferenceFrame, scattering: TabulatedScatteringFunction) -> None:
        """
        Initialise the coherent distribution data without anomolous form factors
        
        Arguments:
            self         the reaction product distribution data
            frame        the reference frame of the distribution data
            scattering   the scattering function
        """
    @typing.overload
    def __init__(self, frame: ReferenceFrame, scattering: TabulatedScatteringFunction, real: TabulatedFormFactor, imaginary: TabulatedFormFactor) -> None:
        """
        Initialise the coherent distribution data with anomolous form factors
        
        Arguments:
            self         the reaction product distribution data
            frame        the reference frame of the distribution data
            scattering   the scattering function
            real         the real part of the anamolous form factor
            imaginary    the imaginary part of the anamolous form factor
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
    def has_anomolous_form_factor(self) -> bool:
        """
        Flag indicating whether or not the coherent distribution data has an anomolous
        form factor
        """
    @property
    def imaginary_anomolous_form_factor(self) -> TabulatedFormFactor | None:
        """
        The imaginary part of the anomolous form factor
        """
    @imaginary_anomolous_form_factor.setter
    def imaginary_anomolous_form_factor(self, arg1: TabulatedFormFactor | None) -> None:
        ...
    @property
    def real_anomolous_form_factor(self) -> TabulatedFormFactor | None:
        """
        The real part of the anomolous form factor
        """
    @real_anomolous_form_factor.setter
    def real_anomolous_form_factor(self, arg1: TabulatedFormFactor | None) -> None:
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
    The distribution data type for a reaction product
    
    Members:
    
      TwoBody
    
      Uncorrelated
    
      Coherent
    
      Incoherent
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
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: Documentation) -> bool:
        ...
    def __init__(self, awr: float | None, library: int | None, version: tuple[int, int] | None, description: str | None) -> None:
        """
        Initialise the documentation
        
        Arguments:
            self          the documentation
            awr           the atomic weight ratio
            library       the library number
            version       the version number
            description   the description
        """
    def __ne__(self, arg0: Documentation) -> bool:
        ...
    @property
    def awr(self) -> float | None:
        """
        The atomic weight ratio
        """
    @awr.setter
    def awr(self, arg1: float | None) -> None:
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
        The library
        """
    @library.setter
    def library(self, arg1: int | None) -> None:
        ...
    @property
    def version(self) -> tuple[int, int] | None:
        """
        The version
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
    
    This corresponds with the incoherent scattering function data given in MF27 MT504.
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: IncoherentDistributionData) -> bool:
        ...
    def __init__(self, frame: ReferenceFrame, scattering: TabulatedScatteringFunction) -> None:
        """
        Initialise the incoherent distribution data
        
        Arguments:
            self         the reaction product distribution data
            frame        the reference frame of the distribution data
            scattering   the scattering function
        """
    def __ne__(self, arg0: IncoherentDistributionData) -> bool:
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
    
    Members:
    
      Atomic
    
      Nuclear
    """
    Atomic: typing.ClassVar[InteractionType]  # value = <InteractionType.Atomic: 1>
    Nuclear: typing.ClassVar[InteractionType]  # value = <InteractionType.Nuclear: 2>
    __members__: typing.ClassVar[dict[str, InteractionType]]  # value = {'Atomic': <InteractionType.Atomic: 1>, 'Nuclear': <InteractionType.Nuclear: 2>}
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
    The interpolation types
    
    Members:
    
      Histogram
    
      LinearLinear
    
      LinearLog
    
      LogLinear
    
      LogLog
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
class IsotropicAngularDistributions:
    """
    The angular distribution data is fully isotropic
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: IsotropicAngularDistributions) -> bool:
        ...
    def __init__(self) -> None:
        """
        Initialise the component
        
        Arguments:
            self   the component
        """
    def __ne__(self, arg0: IsotropicAngularDistributions) -> bool:
        ...
class LegendreAngularDistribution:
    """
    An angular distribution defined by a pdf and cdf using a Legendre series
    expansion
    
    The pdf is normalised to 1 upon construction and the associated cdf is
    calculated upon construction (after the pdf has been normalised).
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the pdf of the distribution for a given cosine value
        
        Arguments:
            self      the angular distribution
            cosine    the cosine value
        """
    def __eq__(self, arg0: LegendreAngularDistribution) -> bool:
        ...
    def __init__(self, coefficients: list[float], normalise: bool = False) -> None:
        """
        Initialise the angular distribution
        
        Arguments:
            self           the angular distribution
            coefficients   the coefficients of the Legendre series (from
                           lowest to highest order coefficient) for the pdf
            normalise      option to indicate whether or not to normalise
                           all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: LegendreAngularDistribution) -> bool:
        ...
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedAngularDistribution:
        """
        Linearise the distribution
        
        Arguments:
            self        the angular distribution
            tolerance   the linearisation tolerance
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
        Evaluate the table for a given cosine value
        
        Arguments:
            self      the table
            cosine    the cosine value
        """
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
        
        Arguments:
            self           the angular distribution
            coefficients   the coefficients of the Legendre series (from
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedAngularDistributionFunction:
        """
        Linearise the distribution function
        
        Arguments:
            self        the distribution function
            tolerance   the linearisation tolerance
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
        The integral (zeroth order moment) of the distribution function over its domain
        """
    @property
    def lower_cosine_limit(self) -> float:
        """
        The lower cosine limit
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the distribution function over its domain
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
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, value: float, cosine: float) -> float:
        """
        Evaluate the angular distributions
        
        Arguments:
            self      the angular distributions
            value     the grid value
            cosine    the cosine value
        """
    def __eq__(self, arg0: LegendreAngularDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[LegendreAngularDistribution], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the angular distributions
        
        Arguments:
            self            the angular distributions
            grid            the grid values
            distributions   the distributions
            boundaries      the boundaries of the interpolation regions
            interpolants    the interpolation types of the interpolation regions,
                            see InterpolationType for all interpolation types
            normalise       option to indicate whether or not to normalise
                            all probability data (default: no normalisation)
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[LegendreAngularDistribution], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the angular distributions
        
        Arguments:
            self            the angular distributions
            grid            the grid values
            distributions   the distributions
            interpolant     the interpolation type (default lin-lin),
                            see InterpolationType for all interpolation types
            normalise      option to indicate whether or not to normalise
                           all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: LegendreAngularDistributions) -> bool:
        ...
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedAngularDistributions:
        """
        Linearise the distribution
        
        Arguments:
            self        the angular distributions
            tolerance   the linearisation tolerance
        """
    def normalise(self) -> None:
        """
        Normalise the distributions
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
class MultiEnergyDistributions:
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: MultiEnergyDistributions) -> bool:
        ...
    def __ne__(self, arg0: MultiEnergyDistributions) -> bool:
        ...
class PolynomialMultiplicity:
    """
    A multiplicity given as a polynomial series
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
        
        Arguments:
            self      the multiplicity
            energy    the energy value
        """
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
        Initialise the multiplicity table
        
        Arguments:
            self           the multiplicity
            lower          the lower limit of the domain
            upper          the upper limit of the domain
            coefficients   the coefficients of the polynomial series (from
                           lowest to highest order coefficient)
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedMultiplicity:
        """
        Linearise the distribution function
        
        Arguments:
            self        the distribution function
            tolerance   the linearisation tolerance
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
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def from_ace_file(filename: str) -> ProjectileTarget | tuple[ProjectileTarget, ProjectileTarget]:
        """
        Create ProjectileTarget data from an ACE file
        
        Most files will produce a single ProjectileTarget. The exception here is the
        photoatomic ACE file which may yield one ProjectileTarget (pre-eprdata) or two
        ProjectileTarget for eprdata files.
        
        Arguments:
            filename   the ENDF file name
        """
    @staticmethod
    def from_endf_file(filename: str, normalise: bool = False) -> ProjectileTarget:
        """
        Create ProjectileTarget data from an ENDF file
        
        If there are multiple materials in the ENDF file, only the first material
        will be transformed into a ProjectileTarget.
        
        Arguments:
            filename    the ENDF file name
            normalise   option to indicate whether or not to normalise
                        all probability data (default: no normalisation)
        """
    @staticmethod
    def from_gnds_file(filename: str, normalise: bool = False) -> ProjectileTarget:
        """
        Create ProjectileTarget data from a GNDS file
        
        Arguments:
            filename    the GNDS file name
            normalise   option to indicate whether or not to normalise
                        all probability data (default: no normalisation)
        """
    def __eq__(self, arg0: ProjectileTarget) -> bool:
        ...
    @typing.overload
    def __init__(self, documentation: Documentation, projectile: id.ParticleID, target: id.ParticleID, type: InteractionType, reactions: list[Reaction], normalise: bool = False) -> None:
        """
        Initialise the ProjectileTarget
        
        Arguments:
            self            the reaction
            documentation   the documentation
            projectile      the particle identifier
            target          the target identifier
            type            the interaction type
            reactions       the reaction data
            normalise       option to indicate whether or not to normalise
                            all probability data (default: no normalisation)
        """
    @typing.overload
    def __init__(self, projectile: id.ParticleID, target: id.ParticleID, type: InteractionType, reactions: list[Reaction], normalise: bool = False) -> None:
        """
        Initialise the ProjectileTarget
        
        Arguments:
            self         the reaction
            projectile   the particle identifier
            target       the target identifier
            type         the interaction type
            reactions    the reaction data
            normalise    option to indicate whether or not to normalise
                         all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: ProjectileTarget) -> bool:
        ...
    def calculate_summation_cross_sections(self, tolerance: ToleranceConvergence = ...) -> None:
        """
        Calculate summation cross sections
        
        Arguments:
            self        the ProjectileTarget data
            tolerance   the linearisation tolerance
        """
    def has_reaction(self, id: str) -> bool:
        """
        Return whether or not a reaction is present
        
        Arguments:
            self   the ProjectileTarget data
            id     the reaction identifier
        """
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    def reaction(self, id: str) -> Reaction:
        """
        Return the requested reaction
        
        Arguments:
            self   the ProjectileTarget data
            id     the reaction identifier
        """
    def to_endf_file(self, mat: int, filename: str) -> None:
        """
        Write the AtomicRelaxation data to an ENDF file
        
        Arguments:
            self        the atomic relaxation data
            mat         the ENDF mat number to be used
            filename    the ENDF file name
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
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: Reaction) -> bool:
        ...
    @typing.overload
    def __init__(self, id: str, xs: TabulatedCrossSection, products: list[ReactionProduct] = [], mass_q: float | None = None, reaction_q: float | None = None, normalise: bool = False) -> None:
        """
        Initialise a primary reaction
        
        Arguments:
            self         the reaction
            id           the reaction identifier
            xs           the cross section of the reaction
            products     the reaction products
            mass_q       the mass difference Q value (optional)
            reaction_q   the reaction Q value (optional)
            normalise    option to indicate whether or not to normalise
                         all probability data (default: no normalisation)
        """
    @typing.overload
    def __init__(self, id: str, partials: list[str], xs: TabulatedCrossSection, products: list[ReactionProduct] = [], normalise: bool = False) -> None:
        """
        Initialise a summation reaction
        
        Summation reactions do not have Q values associated to them. A cross section
        weighted Q value could be calculated using the partial reactions making
        up the summation reaction.
        
        Arguments:
            self        the reaction
            id          the reaction identifier
            partials    the identifiers of the partials of the reaction
            xs          the cross section of the reaction
            products    the reaction products associated to the summation reaction
                        (defaults to no reaction products)
            normalise   option to indicate whether or not to normalise
                        all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: Reaction) -> bool:
        ...
    def has_product(self, type: id.ParticleID) -> bool:
        """
        Return whether or not a reaction product type is present
        
        Arguments:
            self   the reaction
            type   the reaction product type
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
        The number of reaction products of a given type
        """
    def product(self, type: id.ParticleID, index: int = 0) -> ReactionProduct:
        """
        Return a reaction product with a given type and index
        
        Arguments:
            self    the reaction
            type    the reaction product type
            index   the reaction product index (default is zero)
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
    def identifier(self) -> str:
        """
        The reaction identifier
        """
    @identifier.setter
    def identifier(self, arg1: str) -> None:
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
    def partial_reaction_identifiers(self) -> list[str] | None:
        """
        The summation reaction identifiers (not defined if this is a primary
        reaction)
        """
    @partial_reaction_identifiers.setter
    def partial_reaction_identifiers(self, arg1: list[str] | None) -> None:
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
    
    Members:
    
      Primary
    
      Summation
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
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: ReactionProduct) -> bool:
        ...
    def __init__(self, id: id.ParticleID, multiplicity: int | TabulatedMultiplicity | PolynomialMultiplicity, distribution: TwoBodyDistributionData | UncorrelatedDistributionData | CoherentDistributionData | IncoherentDistributionData | None = None, average_energy: TabulatedAverageEnergy | None = None, normalise: bool = False) -> None:
        """
        Initialise the reaction
        
        Arguments:
            self             the reaction
            id               the reaction product identifier
            multiplicity     the reaction product multiplicity
            distribution     the optional reaction product distribution data
            average_energy   the optional average reaction product energy
            normalise        option to indicate whether or not to normalise
                             all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: ReactionProduct) -> bool:
        ...
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    @property
    def average_energy(self) -> TabulatedAverageEnergy | None:
        """
        The average reaction product energy
        """
    @average_energy.setter
    def average_energy(self, arg1: TabulatedAverageEnergy | None) -> None:
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
    def identifier(self) -> id.ParticleID:
        """
        The reaction product identifier
        """
    @identifier.setter
    def identifier(self, arg1: id.ParticleID) -> None:
        ...
    @property
    def multiplicity(self) -> int | TabulatedMultiplicity | PolynomialMultiplicity:
        """
        The multiplicity
        """
    @multiplicity.setter
    def multiplicity(self, arg1: int | TabulatedMultiplicity | PolynomialMultiplicity) -> None:
        ...
class ReferenceFrame:
    """
    The reference frame used to describe data
    
    Members:
    
      Laboratory
    
      CentreOfMass
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
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, cosine: float) -> float:
        """
        Evaluate the pdf of the distribution for a given cosine value
        
        Arguments:
            self      the distribution
            cosine    the cosine value
        """
    def __eq__(self, arg0: TabulatedAngularDistribution) -> bool:
        ...
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the angular distribution
        
        Arguments:
            self           the angular distribution
            cosines        the cosine values
            values         the probability values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
            normalise      option to indicate whether or not to normalise
                           all probability data (default: no normalisation)
        """
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the angular distribution
        
        Arguments:
            self           the angular distribution
            cosines        the cosine values
            values         the probability values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
            normalise      option to indicate whether or not to normalise
                           all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: TabulatedAngularDistribution) -> bool:
        ...
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedAngularDistribution:
        """
        Linearise the distribution
        
        Arguments:
            self        the angular distribution
            tolerance   the linearisation tolerance
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
        Evaluate the table for a given cosine value
        
        Arguments:
            self      the table
            cosine    the cosine value
        """
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
        Initialise the angular distribution function
        
        Arguments:
            self           the angular distribution function
            cosines        the cosine values
            values         the probability values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, cosines: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the angular distribution function
        
        Arguments:
            self           the angular distribution function
            cosines        the cosine values
            values         the probability values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedAngularDistributionFunction:
        """
        Linearise the table
        
        Arguments:
            self        the table
            tolerance   the linearisation tolerance
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
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the distribution function over its domain
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
        The mean (first order raw moment) of the distribution function over its domain
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
    Angular distribution data given as tables
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, value: float, cosine: float) -> float:
        """
        Evaluate the angular distributions
        
        Arguments:
            self      the table
            value     the grid value
            cosine    the cosine value
        """
    def __eq__(self, arg0: TabulatedAngularDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[TabulatedAngularDistribution], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the angular distributions
        
        Arguments:
            self            the angular distribution table
            grid            the grid values
            distributions   the distributions
            boundaries      the boundaries of the interpolation regions
            interpolants    the interpolation types of the interpolation regions,
                            see InterpolationType for all interpolation types
            normalise       option to indicate whether or not to normalise
                            all probability data (default: no normalisation)
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[TabulatedAngularDistribution], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the angular distributions
        
        Arguments:
            self            the multiplicity table
            grid            the grid values
            distributions   the distributions
            interpolant     the interpolation type (default lin-lin),
                            see InterpolationType for all interpolation types
            normalise       option to indicate whether or not to normalise
                            all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: TabulatedAngularDistributions) -> bool:
        ...
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedAngularDistributions:
        """
        Linearise the distribution
        
        Arguments:
            self        the angular distributions
            tolerance   the linearisation tolerance
        """
    def normalise(self) -> None:
        """
        Normalise the distributions
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
        
        Arguments:
            self      the table
            energy    the energy value
        """
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
        Initialise the average cosine table
        
        Arguments:
            self           the average cosine table
            energies       the energy values
            values         the average cosine values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the average cosine table
        
        Arguments:
            self           the average cosine table
            energies       the energy values
            values         the average energy values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedAverageCosine:
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
        
        Arguments:
            self      the table
            energy    the energy value
        """
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
        Initialise the average reaction product energy table
        
        Arguments:
            self           the average reaction product energy table
            energies       the energy values
            values         the average energy values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the average reaction product energy table
        
        Arguments:
            self           the average reaction product energy table
            energies       the energy values
            values         the average energy values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedAverageEnergy:
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
class TabulatedCrossSection:
    """
    A cross section table
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
        
        Arguments:
            self      the table
            energy    the energy value
        """
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
        Initialise the cross section table
        
        Arguments:
            self           the cross section table
            energies       the energy values
            values         the cross section values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the cross section table
        
        Arguments:
            self           the cross section table
            energies       the energy values
            values         the cross section values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedCrossSection:
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
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, energy: float) -> float:
        """
        Evaluate the pdf of the distribution for a given energy value
        
        Arguments:
            self      the distribution
            energy    the energy value
        """
    def __eq__(self, arg0: TabulatedEnergyDistribution) -> bool:
        ...
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the energy distribution
        
        Arguments:
            self           the energy distribution
            energies       the energy values
            values         the probability values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
            normalise      option to indicate whether or not to normalise
                           all probability data (default: no normalisation)
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the energy distribution
        
        Arguments:
            self           the energy distribution
            energies       the energy values
            values         the probability values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
            normalise      option to indicate whether or not to normalise
                           all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: TabulatedEnergyDistribution) -> bool:
        ...
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedEnergyDistribution:
        """
        Linearise the distribution
        
        Arguments:
            self        the energy distribution
            tolerance   the linearisation tolerance
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
        The cosine values
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
        Evaluate the table for a given energy value
        
        Arguments:
            self      the table
            energy    the energy value
        """
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
        Initialise the energy distribution function
        
        Arguments:
            self           the energy distribution function
            energies       the energy values
            values         the cross section values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the energy distribution function
        
        Arguments:
            self           the energy distribution function
            energies       the energy values
            values         the cross section values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedEnergyDistributionFunction:
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
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the distribution function over its domain
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
        The mean (first order raw moment) of the distribution function over its domain
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
    Energy distribution data given as tables
    """
    __hash__: typing.ClassVar[None] = None
    def __call__(self, value: float, cosine: float) -> float:
        """
        Evaluate the energy distributions
        
        Arguments:
            self      the table
            value     the grid value
            energy    the energy value
        """
    def __eq__(self, arg0: TabulatedEnergyDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[TabulatedEnergyDistribution], boundaries: list[int], interpolants: list[InterpolationType], normalise: bool = False) -> None:
        """
        Initialise the energy distributions
        
        Arguments:
            self            the energy distribution table
            grid            the grid values
            distributions   the distributions
            boundaries      the boundaries of the interpolation regions
            interpolants    the interpolation types of the interpolation regions,
                            see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[TabulatedEnergyDistribution], interpolant: InterpolationType = ..., normalise: bool = False) -> None:
        """
        Initialise the energy distributions
        
        Arguments:
            self            the multiplicity table
            grid            the grid values
            distributions   the distributions
            interpolant     the interpolation type (default lin-lin),
                            see InterpolationType for all interpolation types
        """
    def __ne__(self, arg0: TabulatedEnergyDistributions) -> bool:
        ...
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedEnergyDistributions:
        """
        Linearise the distribution
        
        Arguments:
            self        the energy distributions
            tolerance   the linearisation tolerance
        """
    def normalise(self) -> None:
        """
        Normalise the distributions
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
        
        Arguments:
            self      the table
            energy    the energy value
        """
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
        Initialise the form factor table
        
        Arguments:
            self           the form factor table
            energies       the energy values
            values         the form factor values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the form factor table
        
        Arguments:
            self           the form factor table
            energies       the energy values
            values         the form factor values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedFormFactor:
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
        
        Arguments:
            self      the table
            energy    the energy value
        """
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
        Initialise the multiplicity table
        
        Arguments:
            self           the multiplicity table
            energies       the energy values
            values         the multiplicity values
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions,
                           see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the multiplicity table
        
        Arguments:
            self           the multiplicity table
            energies       the energy values
            values         the multiplicity values
            interpolant    the interpolation type (default lin-lin),
                           see InterpolationType for all interpolation types
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedMultiplicity:
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
        
        Arguments:
            self              the table
            inverse_length    the inverse length value
        """
    @typing.overload
    def __call__(self, energy: float, cosine: float) -> float:
        """
        Evaluate the table for a given energy,cosine pair
        
        Arguments:
            self     the table
            energy   the incident photon energy
            cosine   the outgoing photon cosine
        """
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
        Initialise the scattering function table
        
        Arguments:
            self              the scattering function table
            inverse_lengths   the inverse length values
            values            the scattering function values
            boundaries        the boundaries of the interpolation regions
            interpolants      the interpolation types of the interpolation regions,
                              see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, inverse_lengths: list[float], values: list[float], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the scattering function table
        
        Arguments:
            self              the scattering function table
            inverse_lengths   the inverse length values
            values            the scattering function values
            interpolant       the interpolation type (default lin-lin),
                              see InterpolationType for all interpolation types
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
    def linearise(self, tolerance: ToleranceConvergence = ...) -> TabulatedScatteringFunction:
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
    def interpolants(self) -> list[InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def inverse_length(self, arg1: float, arg2: float) -> float:
        """
        The inverse length value associated to an energy,cosine pair
        
        Arguments:
            self     the table
            energy   the incident photon energy
            cosine   the outgoing photon cosine
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
class ToleranceConvergence:
    """
    A convergence functor using a single tolerance
    
    This functor class can be used to ensure convergence of the linearisation
    process using a relative tolerance and absolute difference threshold.
    With this functor, a trial value and reference value are considered
    converged if:
      abs( trial - reference ) < ( abs( trial ) + abs( reference ) ) * tolerance
    
    For very small values (when ( abs( trial ) + abs( reference ) ) * tolerance
    is smaller than the threshold value), a trial value and reference value
    are considered converged if:
      abs( trial - reference ) < threshold
    """
    def __call__(self, trial: float, reference: float, xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
        """
        Test the convergence of the linearisation
        
        Arguments:
            self         the convergence functor
            trial        the trial value to be tested
            reference    the reference value to be tested against
            xLeft        the left value on the x interval
            xRight       the right value on the x interval
            yLeft        the left value on the y interval
            yRight       the right value on the y interval
        """
    def __init__(self, tolerance: float = 0.001, threshold: float = 1e-10) -> None:
        """
        Initialise the convergence functor
        
        Arguments:
            self        the functor
            tolerance   the linearisation tolerance (default 0.1 %)
            threshold   the lowest allowed absolute difference (default 1e-10)
        """
    @property
    def threshold(self) -> float:
        """
        The linearisation threshold
        """
    @property
    def tolerance(self) -> float:
        """
        The linearisation tolerance
        """
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
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: TwoBodyDistributionData) -> bool:
        ...
    def __init__(self, frame: ReferenceFrame, angle: IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions, normalise: bool = False) -> None:
        """
        Initialise the two-body distribution data
        
        Arguments:
            self        the reaction product distribution data
            frame       the reference frame of the distribution data
            angle       the angular distributions
            normalise   option to indicate whether or not to normalise
                        all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: TwoBodyDistributionData) -> bool:
        ...
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    @property
    def angle(self) -> IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions:
        """
        The angular distributions
        """
    @angle.setter
    def angle(self, arg1: IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions) -> None:
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
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: UncorrelatedDistributionData) -> bool:
        ...
    def __init__(self, frame: ReferenceFrame, angle: IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions, energy: MultiEnergyDistributions | TabulatedEnergyDistributions, normalise: bool = False) -> None:
        """
        Initialise the uncorrelated distribution data
        
        Arguments:
            self        the reaction product distribution data
            frame       the reference frame of the distribution data
            angle       the angular distributions
            energy      the energy distributions
            normalise   option to indicate whether or not to normalise
                        all probability data (default: no normalisation)
        """
    def __ne__(self, arg0: UncorrelatedDistributionData) -> bool:
        ...
    def normalise(self) -> None:
        """
        Normalise the distribution data
        """
    @property
    def angle(self) -> IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions:
        """
        The angular distributions
        """
    @angle.setter
    def angle(self, arg1: IsotropicAngularDistributions | LegendreAngularDistributions | TabulatedAngularDistributions) -> None:
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
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: UniformAngularDistribution) -> bool:
        ...
    def __init__(self, cosines: list[float], type: UniformDistributionType) -> None:
        """
        Initialise the angular distribution
        
        Arguments:
            self       the angular distribution
            cosines    the cosine values
            type       the uniform distribution type
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
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: UniformAngularDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[UniformAngularDistribution], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the angular distributions
        
        Arguments:
            self            the angular distribution table
            grid            the grid values
            distributions   the distributions
            boundaries      the boundaries of the interpolation regions
            interpolants    the interpolation types of the interpolation regions,
                            see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[UniformAngularDistribution], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the angular distributions
        
        Arguments:
            self            the multiplicity table
            grid            the grid values
            distributions   the distributions
            interpolant     the interpolation type (default lin-lin),
                            see InterpolationType for all interpolation types
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
    
    Members:
    
      Discrete
    
      Interval
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
    A uniform or equally probably energy distribution
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: UniformEnergyDistribution) -> bool:
        ...
    def __init__(self, energies: list[float], type: UniformDistributionType) -> None:
        """
        Initialise the energy distribution
        
        Arguments:
            self       the energy distribution
            energies   the energy values
            type       the uniform distribution type
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
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: UniformEnergyDistributions) -> bool:
        ...
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[UniformEnergyDistribution], boundaries: list[int], interpolants: list[InterpolationType]) -> None:
        """
        Initialise the energy distributions
        
        Arguments:
            self            the energy distribution table
            grid            the grid values
            distributions   the distributions
            boundaries      the boundaries of the interpolation regions
            interpolants    the interpolation types of the interpolation regions,
                            see InterpolationType for all interpolation types
        """
    @typing.overload
    def __init__(self, grid: list[float], distributions: list[UniformEnergyDistribution], interpolant: InterpolationType = ...) -> None:
        """
        Initialise the energy distributions
        
        Arguments:
            self            the multiplicity table
            grid            the grid values
            distributions   the distributions
            interpolant     the interpolation type (default lin-lin),
                            see InterpolationType for all interpolation types
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
