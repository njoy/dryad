"""
Covariance data components
"""
from __future__ import annotations
import dryad.id
import numpy
import typing
__all__: list[str] = ['CrossSectionCovarianceMatrix', 'CrossSectionMetadata', 'LinearCombinationCovariance', 'ProductMultiplicityCovarianceMatrix', 'ProductMultiplicityMetadata', 'ScalingType', 'VarianceScaling', 'is_square', 'is_symmetric']
class CrossSectionCovarianceMatrix:
    """
    A cross section covariance matrix
    """
    @typing.overload
    def __init__(self, metadata: CrossSectionMetadata, covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True, scaling: VarianceScaling | None = None) -> None:
        """
        Initialise an on-diagonal cross section covariance matrix
        
        Arguments:
            self          the covariance matrix
            metadata      the row and column metadata
            covariances   the covariance matrix
            relative      the relative covariance flag (default is true)
            scaling       the variance scaling information (default is none)
        """
    @typing.overload
    def __init__(self, row_metadata: CrossSectionMetadata, column_metadata: CrossSectionMetadata, covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True) -> None:
        """
        Initialise an off-diagonal cross section covariance matrix
        
        Arguments:
            self             the covariance matrix
            row_metadata     the row metadata
            column_metadata  the column metadata
            covariances      the covariance matrix
            relative         the relative covariance flag (default is true)
        """
    @typing.overload
    def __init__(self, metadata: CrossSectionMetadata, deviations: list[float], correlations: numpy.ndarray[numpy.float64[m, n]], relative: bool = True, scaling: VarianceScaling | None = None) -> None:
        """
        Initialise an on-diagonal cross section correlation matrix
        
        Arguments:
            self           the covariance matrix
            metadata       the row and column metadata
            deviations     the standard deviations
            correlations   the correlation matrix
            relative       the relative covariance flag (default is true)
            scaling        the variance scaling information (default is none)
        """
    @typing.overload
    def __init__(self, row_metadata: CrossSectionMetadata, column_metadata: CrossSectionMetadata, row_deviations: list[float], column_deviations: list[float], correlations: numpy.ndarray[numpy.float64[m, n]], relative: bool = True) -> None:
        """
        Initialise an off-diagonal cross section correlation matrix
        
        Arguments:
            self               the covariance matrix
            row_metadata       the row metadata
            column_metadata    the column metadata
            row_deviations     the standard deviations to be applied to each row
            column_deviations  the standard deviations to be applied to each column
            correlations       the correlation matrix
            relative           the relative covariance flag (default is true)
        """
    @typing.overload
    def __init__(self, instance: CrossSectionCovarianceMatrix) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    @typing.overload
    def calculate_correlations(self) -> None:
        """
        Calculate the correlations (for on diagonal matrices)
        
        The correlations can be calculated without input of the standard
        deviations for matrices on the diagonal of the full matrix. Standard
        deviations will be calculated and stored as well.
        When this method is called on an off diagonal matrix, the method has
        no effect.
        """
    @typing.overload
    def calculate_correlations(self, row_deviations: list[float], column_deviations: list[float]) -> None:
        """
        Calculate the correlations (for off diagonal matrices)
        
        The correlations can only be calculated with input of the standard deviations
        for covariance matrices that are off diagonal in the full covariance matrix.
        Standard deviations will not be stored.
        
        Arguments:
            self                the covariance matrix
            row_deviations      the standard deviations to be applied to each row
            column_deviations   the standard deviations to be applied to each column
        """
    def calculate_eigenvalues(self) -> None:
        """
        Calculate the eigenvalues from the covariances
        
        The eigenvalues can only be calculated from matrices on the diagonal
        of the full matrix. When this function is called on an off diagonal matrix,
        the function has no effect.
        """
    def calculate_standard_deviations(self) -> None:
        """
        Calculate the standard deviations from the covariances
        
        The standard deviations can only be calculated from covariance matrices on the
        diagonal of the full covariance matrix. When this function is called on an
        off diagonal matrix, the function has no effect.
        """
    @typing.overload
    def extract(self, reaction: dryad.id.ReactionID | None, group: dryad.id.EnergyGroup | None) -> CrossSectionCovarianceMatrix:
        ...
    @typing.overload
    def extract(self, row_reaction: dryad.id.ReactionID | None, row_group: dryad.id.EnergyGroup | None, col_reaction: dryad.id.ReactionID | None, col_group: dryad.id.EnergyGroup | None) -> CrossSectionCovarianceMatrix:
        ...
    @property
    def column_metadata(self) -> CrossSectionMetadata:
        """
        The column metadata
        """
    @property
    def correlations(self) -> numpy.ndarray[numpy.float64[m, n]] | None:
        """
        The correlation matrix
        """
    @property
    def covariances(self) -> numpy.ndarray[numpy.float64[m, n]]:
        """
        The covariance matrix
        """
    @property
    def eigenvalues(self) -> list[float] | None:
        """
        The eigenvalues
        """
    @property
    def has_variance_scaling(self) -> bool:
        """
        Flag indicating whether or not the covariance block has variance scaling information
        """
    @property
    def is_absolute_matrix(self) -> bool:
        """
        Flag to indicate whether or not this covariance matrix is absolute or not
        """
    @property
    def is_off_diagonal(self) -> bool:
        """
        Flag to indicate whether or not this covariance matrix is off-diagonal
        """
    @property
    def is_on_diagonal(self) -> bool:
        """
        Flag to indicate whether or not this covariance matrix is on-diagonal
        """
    @property
    def is_relative_matrix(self) -> bool:
        """
        Flag to indicate whether or not this covariance matrix is relative or not
        """
    @property
    def row_metadata(self) -> CrossSectionMetadata:
        """
        The row metadata
        """
    @property
    def standard_deviations(self) -> list[float] | None:
        """
        The standard deviations
        """
    @property
    def variance_scaling(self) -> VarianceScaling | None:
        """
        The variance scaling information
        
         If this type of information is given, it will be for an on-diagonal covariance block.
        """
class CrossSectionMetadata:
    """
    Covariance metadata for cross sections
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: CrossSectionMetadata) -> bool:
        ...
    @typing.overload
    def __init__(self, reactions: list[dryad.id.ReactionID], energies: list[float]) -> None:
        """
        Initialise the product multiplicity covariance metadata
        
        Arguments:
            self          the covariance metadata
            reactions     the reaction identifiers
            energies      the group structure
        """
    @typing.overload
    def __init__(self, keys: list[tuple[dryad.id.ReactionID, dryad.id.EnergyGroup]]) -> None:
        """
        Initialise the product multiplicity covariance metadata
        
        Arguments:
            self   the covariance metadata
            keys   the metadata keys
        """
    @typing.overload
    def __init__(self, instance: CrossSectionMetadata) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: CrossSectionMetadata) -> bool:
        ...
    @property
    def energies(self) -> list[float]:
        """
        The energy group boundaries
        """
    @property
    def keys(self) -> list[tuple[dryad.id.ReactionID, dryad.id.EnergyGroup]]:
        """
        The metadata keys
        """
    @property
    def reaction_identifiers(self) -> list[dryad.id.ReactionID]:
        """
        The reaction identifiers
        """
class LinearCombinationCovariance:
    """
    Covariance data for a reaction defined as a linear combination of other reactions' covariance data
    """
    @typing.overload
    def __init__(self, lower: float, upper: float, reactions: list[dryad.id.ReactionID], coefficients: list[float]) -> None:
        """
        Initialise the derived covariance
        
        Arguments:
            self           the derived covariance
            lower          the lower energy limit
            upper          the upper energy limit
            reactions      the reactions in the linear combination
            coefficients   the coefficients of the linear combination
        """
    @typing.overload
    def __init__(self, instance: LinearCombinationCovariance) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    @property
    def coefficients(self) -> list[float]:
        """
        The coefficients for the linear combination
        """
    @property
    def lower_energy_limit(self) -> float:
        """
        The lower energy limit
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions
        """
    @property
    def reactions(self) -> list[dryad.id.ReactionID]:
        """
        The reactions in the linear combination
        """
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit
        """
class ProductMultiplicityCovarianceMatrix:
    """
    A covariance matrix for product multiplicities
    """
    @typing.overload
    def __init__(self, metadata: ProductMultiplicityMetadata, covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True) -> None:
        """
        Initialise an on-diagonal product multiplicity covariance matrix
        
        Arguments:
            self          the covariance matrix
            metadata      the row and column metadata
            covariances   the covariance matrix
            relative      the relative covariance flag (default is true)
        """
    @typing.overload
    def __init__(self, row_metadata: ProductMultiplicityMetadata, column_metadata: ProductMultiplicityMetadata, covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True) -> None:
        """
        Initialise an off-diagonal product multiplicity covariance matrix
        
        Arguments:
            self             the covariance matrix
            row_metadata     the row metadata
            column_metadata  the column metadata
            covariances      the covariance matrix
            relative         the relative covariance flag (default is true)
        """
    @typing.overload
    def __init__(self, metadata: ProductMultiplicityMetadata, deviations: list[float], correlations: numpy.ndarray[numpy.float64[m, n]], relative: bool = True) -> None:
        """
        Initialise an on-diagonal product multiplicity correlation matrix
        
        Arguments:
            self           the covariance matrix
            metadata       the row and column metadata
            deviations     the standard deviations
            correlations   the correlation matrix
            relative       the relative covariance flag (default is true)
        """
    @typing.overload
    def __init__(self, row_metadata: ProductMultiplicityMetadata, column_metadata: ProductMultiplicityMetadata, row_deviations: list[float], column_deviations: list[float], correlations: numpy.ndarray[numpy.float64[m, n]], relative: bool = True) -> None:
        """
        Initialise an off-diagonal product multiplicity correlation matrix
        
        Arguments:
            self               the covariance matrix
            row_metadata       the row metadata
            column_metadata    the column metadata
            row_deviations     the standard deviations to be applied to each row
            column_deviations  the standard deviations to be applied to each column
            correlations       the correlation matrix
            relative           the relative covariance flag (default is true)
        """
    @typing.overload
    def __init__(self, instance: ProductMultiplicityCovarianceMatrix) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    @typing.overload
    def calculate_correlations(self) -> None:
        """
        Calculate the correlations (for on diagonal matrices)
        
        The correlations can be calculated without input of the standard
        deviations for matrices on the diagonal of the full matrix. Standard
        deviations will be calculated and stored as well.
        When this method is called on an off diagonal matrix, the method has
        no effect.
        """
    @typing.overload
    def calculate_correlations(self, row_deviations: list[float], column_deviations: list[float]) -> None:
        """
        Calculate the correlations (for off diagonal matrices)
        
        The correlations can only be calculated with input of the standard deviations
        for covariance matrices that are off diagonal in the full covariance matrix.
        Standard deviations will not be stored.
        
        Arguments:
            self                the covariance matrix
            row_deviations      the standard deviations to be applied to each row
            column_deviations   the standard deviations to be applied to each column
        """
    def calculate_eigenvalues(self) -> None:
        """
        Calculate the eigenvalues from the covariances
        
        The eigenvalues can only be calculated from matrices on the diagonal
        of the full matrix. When this function is called on an off diagonal matrix,
        the function has no effect.
        """
    def calculate_standard_deviations(self) -> None:
        """
        Calculate the standard deviations from the covariances
        
        The standard deviations can only be calculated from covariance matrices on the
        diagonal of the full covariance matrix. When this function is called on an
        off diagonal matrix, the function has no effect.
        """
    @typing.overload
    def extract(self, reaction: dryad.id.ReactionID | None, group: dryad.id.EnergyGroup | None, product: dryad.id.ParticleID | None) -> ProductMultiplicityCovarianceMatrix:
        ...
    @typing.overload
    def extract(self, row_reaction: dryad.id.ReactionID | None, row_group: dryad.id.EnergyGroup | None, row_product: dryad.id.ParticleID | None, col_reaction: dryad.id.ReactionID | None, col_group: dryad.id.EnergyGroup | None, col_product: dryad.id.ParticleID | None) -> ProductMultiplicityCovarianceMatrix:
        ...
    @property
    def column_metadata(self) -> ProductMultiplicityMetadata:
        """
        The column metadata
        """
    @property
    def correlations(self) -> numpy.ndarray[numpy.float64[m, n]] | None:
        """
        The correlation matrix
        """
    @property
    def covariances(self) -> numpy.ndarray[numpy.float64[m, n]]:
        """
        The covariance matrix
        """
    @property
    def eigenvalues(self) -> list[float] | None:
        """
        The eigenvalues
        """
    @property
    def is_absolute_matrix(self) -> bool:
        """
        Flag to indicate whether or not this covariance matrix is absolute or not
        """
    @property
    def is_off_diagonal(self) -> bool:
        """
        Flag to indicate whether or not this covariance matrix is off-diagonal
        """
    @property
    def is_on_diagonal(self) -> bool:
        """
        Flag to indicate whether or not this covariance matrix is on-diagonal
        """
    @property
    def is_relative_matrix(self) -> bool:
        """
        Flag to indicate whether or not this covariance matrix is relative or not
        """
    @property
    def row_metadata(self) -> ProductMultiplicityMetadata:
        """
        The row metadata
        """
    @property
    def standard_deviations(self) -> list[float] | None:
        """
        The standard deviations
        """
class ProductMultiplicityMetadata:
    """
    Covariance metadata for product multiplicities
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: ProductMultiplicityMetadata) -> bool:
        ...
    @typing.overload
    def __init__(self, reactions: list[dryad.id.ReactionID], energies: list[float], products: list[dryad.id.ParticleID]) -> None:
        """
        Initialise the product multiplicity covariance metadata
        
        Arguments:
            self          the covariance metadata
            reactions     the reaction identifiers
            energies      the group structure
            products      the product identifiers
        """
    @typing.overload
    def __init__(self, keys: list[tuple[dryad.id.ReactionID, dryad.id.EnergyGroup, dryad.id.ParticleID]]) -> None:
        """
        Initialise the product multiplicity covariance metadata
        
        Arguments:
            self   the covariance metadata
            keys   the metadata keys
        """
    @typing.overload
    def __init__(self, instance: ProductMultiplicityMetadata) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    def __ne__(self, arg0: ProductMultiplicityMetadata) -> bool:
        ...
    @property
    def energies(self) -> list[float]:
        """
        The energy group boundaries
        """
    @property
    def keys(self) -> list[tuple[dryad.id.ReactionID, dryad.id.EnergyGroup, dryad.id.ParticleID]]:
        """
        The metadata keys
        """
    @property
    def product_identifiers(self) -> list[dryad.id.ParticleID]:
        """
        The reaction product identifiers
        """
    @property
    def reaction_identifiers(self) -> list[dryad.id.ReactionID]:
        """
        The reaction identifiers
        """
class ScalingType:
    """
    The variance scaling type
    
    Members:
    
      Inverse
    
      Direct
    """
    Direct: typing.ClassVar[ScalingType]  # value = <ScalingType.Direct: 2>
    Inverse: typing.ClassVar[ScalingType]  # value = <ScalingType.Inverse: 1>
    __members__: typing.ClassVar[dict[str, ScalingType]]  # value = {'Inverse': <ScalingType.Inverse: 1>, 'Direct': <ScalingType.Direct: 2>}
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
class VarianceScaling:
    """
    Variance scaling information
    
    Some ENDF evaluations provide variance scaling information for cross section
    covariances. Each factor value for a given group characterises an uncorrelated
    contribution to the absolute variance of the cross section averaged over any
    energy subgroup that includes a portion of the energy interval over which the
    factor is defined.
    """
    @typing.overload
    def __init__(self, type: ScalingType, energies: list[float], factors: list[float]) -> None:
        """
        Initialise the metadata
        
        Arguments:
            self        the variance scaling information
            type        the scaling procedure type
            energies    the energy boundaries
            factors     the scaling factors
        """
    @typing.overload
    def __init__(self, instance: VarianceScaling) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    @property
    def energies(self) -> list[float]:
        """
        The energy boundaries
        """
    @property
    def factors(self) -> list[float]:
        """
        The scaling factors
        """
    @property
    def number_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def type(self) -> ScalingType:
        """
        The scaling procedure type
        """
def is_square(arg0: numpy.ndarray[numpy.float64[m, n]]) -> bool:
    """
    Return whether or not a matrix is square
    """
def is_symmetric(arg0: numpy.ndarray[numpy.float64[m, n]]) -> bool:
    """
    Return whether or not a matrix is symmetric
    """
