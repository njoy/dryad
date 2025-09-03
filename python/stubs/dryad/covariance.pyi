"""
Covariance data components
"""
from __future__ import annotations
import dryad.id
import numpy
import typing
__all__ = ['CrossSectionCovarianceBlock', 'CrossSectionMetadata', 'LinearCombinationCovariance', 'ScalingType', 'VarianceScaling', 'is_square', 'is_symmetric']
class CrossSectionCovarianceBlock:
    """
    A cross section covariance matrix block
    """
    @typing.overload
    def __init__(self, metadata: CrossSectionMetadata, covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True, scaling: VarianceScaling | None = None) -> None:
        """
        Initialise a diagonal cross section covariance block
        
        Arguments:
            self          the covariance block
            metadata      the metadata associated with the covariance block
            covariances   the covariance matrix
            relative      the relative covariance flag (default is true)
            scaling       the variance scaling information (default is none)
        """
    @typing.overload
    def __init__(self, row_metadata: CrossSectionMetadata, column_metadata: CrossSectionMetadata, covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True) -> None:
        """
        Initialise a diagonal cross section covariance block
        
        Arguments:
            self               the covariance block
            row_metadata       the row metadata
            column_metadata    the column metadata
            covariances        the covariance matrix
            relative           the relative covariance flag (default is true)
        """
    @typing.overload
    def __init__(self, instance: CrossSectionCovarianceBlock) -> None:
        """
        Initialise a copy
        
        Arguments:
            instance    the instance to be copied
        """
    @typing.overload
    def __init__(self, projectile: dryad.id.ParticleID, target: dryad.id.ParticleID, reaction: dryad.id.ReactionID, energies: list[float], covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True, scaling: VarianceScaling | None = None) -> None:
        """
        Initialise a diagonal cross section covariance block
        
        Arguments:
            self          the covariance block
            projectile    the projectile identifier
            target        the target identifier
            reaction      the reaction identifier
            energies      the energy boundaries
            covariances   the covariance matrix
            relative      the relative covariance flag (default is true)
            scaling       the variance scaling information (default is none)
        """
    @typing.overload
    def __init__(self, row_projectile: dryad.id.ParticleID, row_target: dryad.id.ParticleID, row_reaction: dryad.id.ReactionID, row_energies: list[float], column_projectile: dryad.id.ParticleID, column_target: dryad.id.ParticleID, column_reaction: dryad.id.ReactionID, column_energies: list[float], covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True) -> None:
        """
        Initialise an off-diagonal cross section covariance block
        
        Arguments:
            self                 the covariance block
            row_projectile       the row projectile identifier
            row_target           the row target identifier
            row_reaction         the row reaction identifier
            row_energies         the row energy boundaries
            column_projectile    the column projectile identifier
            column_target        the column target identifier
            column_reaction      the column reaction identifier
            column_energies      the column energy boundaries
            covariances          the covariance matrix
            relative             the relative covariance flag (default is true)
        """
    @typing.overload
    def calculate_correlations(self) -> None:
        """
        Calculate the correlations (for covariance blocks on the diagonal)
        
        The correlations can only be calculated without input of the standard
        deviations for covariance blocks on the diagonal of the covariance matrix.
        When this method is called on an off diagonal block, the method has no effect.
        Standard deviations will be calculated and stored as well.
        """
    @typing.overload
    def calculate_correlations(self, row_deviations: list[float], column_deviations: list[float]) -> None:
        """
        Calculate the correlations (for off diagonal covariance blocks)
        
        The correlations can only be calculated with input of the standard deviations
        for covariance blocks that are off diagonal in the covariance matrix.
        Standard deviations will not be stored.
        
        Arguments:
            self                 the covariance block
            row_deviations       the standard deviations to be applied to each row
            column_deviations    the standard deviations to be applied to each column
        """
    def calculate_eigenvalues(self) -> None:
        """
        Calculate the eigenvalues from the covariances
        
        The eigenvalues can only be calculated from covariance blocks on the
        diagonal of the covariance matrix. When this function is called on an
        off diagonal block, the function has no effect.
        """
    def calculate_standard_deviations(self) -> None:
        """
        Calculate the standard deviations from the covariances
        
        The standard deviations can only be calculated from covariance blocks on the
        diagonal of the covariance matrix. When this function is called on an
        off diagonal block, the function has no effect.
        """
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
    def covariances(self) -> numpy.ndarray[numpy.float64[m, n]] | None:
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
    def is_absolute_block(self) -> bool:
        """
        Flag to indicate whether or not this covariance block is absolute or not
        """
    @property
    def is_diagonal_block(self) -> bool:
        """
        Flag to indicate whether or not this covariance block is a diagonal block
        """
    @property
    def is_off_diagonal_block(self) -> bool:
        """
        Flag to indicate whether or not this covariance block is an off-diagonal block
        """
    @property
    def is_relative_block(self) -> bool:
        """
        Flag to indicate whether or not this covariance block is relative or not
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
    Metadata for the rows or columns of a covariance matrix block for cross section data
    """
    @typing.overload
    def __init__(self, projectile: dryad.id.ParticleID, target: dryad.id.ParticleID, reaction: dryad.id.ReactionID, energies: list[float]) -> None:
        """
        Initialise the meta data
        
        Arguments:
            self         the meta data
            projectile   the projectile identifier
            target       the target identifier
            reaction     the reaction identifier
            energies     the energy boundaries
        """
    @typing.overload
    def __init__(self, instance: CrossSectionMetadata) -> None:
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
    def number_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def projectile_identifier(self) -> dryad.id.ParticleID:
        """
        The projectile identifier
        """
    @property
    def reaction_identifier(self) -> dryad.id.ReactionID:
        """
        The reaction identifier
        """
    @property
    def target_identifier(self) -> dryad.id.ParticleID:
        """
        The target identifier
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
