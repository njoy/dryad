"""
Covariance data components
"""
from __future__ import annotations
import njoy.dryad
import njoy.dryad.id
import numpy
import typing
__all__: list[str] = ['AngularDistributionCovarianceData', 'AngularDistributionCovarianceMatrix', 'AngularDistributionMetadata', 'CovarianceData', 'CrossSectionCovarianceData', 'CrossSectionCovarianceMatrix', 'CrossSectionMetadata', 'LinearCombinationCovariance', 'ProductMultiplicityCovarianceMatrix', 'ProductMultiplicityMetadata', 'ScalingType', 'VarianceScaling']
class AngularDistributionCovarianceData:
    """
    The angular distribution covariance data
    
    Parameters
    ----------
        matrices : list of njoy.dryad.covariance.AngularDistributionCovarianceData 
             the covariance matrices
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def from_gendf_file(projectile: njoy.dryad.id.ParticleID, target: njoy.dryad.id.ParticleID, frame: njoy.dryad.ReferenceFrame, filename: str) -> AngularDistributionCovarianceData | None:
        """
        Create CrossSectionCovarianceData data from an ERRORR GENDF file
        
        If there are multiple materials in the GENDF file, only the first material
        will be transformed into a ProjectileTarget.
        
        Parameters
        ----------
            projectile : njoy.dryad.id.ParticleID
                 the projectile identifier
            target : njoy.dryad.id.ParticleID
                 the target identifier
            frame : njoy.dryad.ReferenceFrame
                 the reference frame of the projectile target
            filename : str
                 the GENDF file name
        """
    def __copy__(self) -> AngularDistributionCovarianceData:
        ...
    def __deepcopy__(self, arg0: dict) -> AngularDistributionCovarianceData:
        ...
    def __eq__(self, arg0: AngularDistributionCovarianceData) -> bool:
        ...
    def __init__(self, matrices: list[AngularDistributionCovarianceMatrix]) -> None:
        """
        Initialise the covariance data
        """
    def __ne__(self, arg0: AngularDistributionCovarianceData) -> bool:
        ...
    @typing.overload
    def covariance_matrix(self, row: njoy.dryad.id.ReactionID, column: njoy.dryad.id.ReactionID) -> AngularDistributionCovarianceMatrix | list[AngularDistributionCovarianceMatrix]:
        """
        Return the covariance data for a row and column reaction pair
        
        Parameters
        ----------
            row : njoy.dryad.id.ReactionID
                 the row reaction identifier
            column : njoy.dryad.id.ReactionID
                 the column reaction identifier
        """
    @typing.overload
    def covariance_matrix(self, id: njoy.dryad.id.ReactionID) -> AngularDistributionCovarianceMatrix | list[AngularDistributionCovarianceMatrix]:
        """
        Return the covariance data for a reaction
        
        Parameters
        ----------
            id : njoy.dryad.id.ReactionID
                 the reaction identifier
        """
    @typing.overload
    def has_covariance_matrix(self, row: njoy.dryad.id.ReactionID, column: njoy.dryad.id.ReactionID) -> bool:
        """
        Return whether or not a given reaction pair has covariance data
        
        Parameters
        ----------
            row : njoy.dryad.id.ReactionID
                 the row reaction identifier
            column : njoy.dryad.id.ReactionID
                 the column reaction identifier
        """
    @typing.overload
    def has_covariance_matrix(self, id: njoy.dryad.id.ReactionID) -> bool:
        """
        Return whether or not a given reaction has covariance data
        
        Parameters
        ----------
            id : njoy.dryad.id.ReactionID
                 the reaction identifier
        """
    @property
    def covariances(self) -> list[AngularDistributionCovarianceMatrix | list[AngularDistributionCovarianceMatrix]]:
        """
        The covariance data
        """
    @property
    def number_covariance_matrices(self) -> int:
        """
        The number of covariance blocks
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions for which covariance data is available
        """
    @property
    def reaction_identifiers(self) -> list[njoy.dryad.id.ReactionID]:
        """
        The reaction identifiers for which covariance data is available
        """
class AngularDistributionCovarianceMatrix:
    """
    A covariance matrix for angular distributions
    """
    def __copy__(self) -> AngularDistributionCovarianceMatrix:
        ...
    def __deepcopy__(self, arg0: dict) -> AngularDistributionCovarianceMatrix:
        ...
    @typing.overload
    def __init__(self, metadata: AngularDistributionMetadata, covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True, frame: njoy.dryad.ReferenceFrame = ...) -> None:
        """
        Initialise an on-diagonal angular distribution covariance matrix
        
        Arguments:
            self          the covariance matrix
            metadata      the row and column metadata
            covariances   the covariance matrix
            relative      the relative covariance flag (default is true)
            frame         the reference frame of the covariance data (default is Lab)
        """
    @typing.overload
    def __init__(self, row_metadata: AngularDistributionMetadata, column_metadata: AngularDistributionMetadata, covariances: numpy.ndarray[numpy.float64[m, n]], relative: bool = True, frame: njoy.dryad.ReferenceFrame = ...) -> None:
        """
        Initialise an off-diagonal angular distribution covariance matrix
        
        Arguments:
            self             the covariance matrix
            row_metadata     the row metadata
            column_metadata  the column metadata
            covariances      the covariance matrix
            relative         the relative covariance flag (default is true)
            frame            the reference frame of the covariance data (default is Lab)
        """
    @typing.overload
    def __init__(self, metadata: AngularDistributionMetadata, deviations: list[float], correlations: numpy.ndarray[numpy.float64[m, n]], relative: bool = True, frame: njoy.dryad.ReferenceFrame = ...) -> None:
        """
        Initialise an on-diagonal angular distribution correlation matrix
        
        Arguments:
            self           the covariance matrix
            metadata       the row and column metadata
            deviations     the standard deviations
            correlations   the correlation matrix
            relative       the relative covariance flag (default is true)
            frame          the reference frame of the covariance data (default is Lab)
        """
    @typing.overload
    def __init__(self, row_metadata: AngularDistributionMetadata, column_metadata: AngularDistributionMetadata, row_deviations: list[float], column_deviations: list[float], correlations: numpy.ndarray[numpy.float64[m, n]], relative: bool = True, frame: njoy.dryad.ReferenceFrame = ...) -> None:
        """
        Initialise an off-diagonal angular distribution correlation matrix
        
        Arguments:
            self               the covariance matrix
            row_metadata       the row metadata
            column_metadata    the column metadata
            row_deviations     the standard deviations to be applied to each row
            column_deviations  the standard deviations to be applied to each column
            correlations       the correlation matrix
            relative           the relative covariance flag (default is true)
            frame              the reference frame of the covariance data (default is Lab)
        """
    @typing.overload
    def __init__(self, metadata: AngularDistributionMetadata, eigenvalues: list[float], eigenvectors: list[numpy.ndarray[numpy.float64[m, 1]]], relative: bool = True, frame: njoy.dryad.ReferenceFrame = ...) -> None:
        """
        Initialise an on-diagonal angular distribution covariance matrix using eigenvalues
        and eigenvectors
        
        Arguments:
            self           the covariance matrix
            metadata       the row and column metadata
            eigenvalues    the eigenvalues
            eigenvectors   the associated eigenvectors
            relative       the relative covariance flag (default is true)
            frame         the reference frame of the covariance data (default is Lab)
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
    @typing.overload
    def calculate_covariances(self) -> None:
        """
        Calculate the covariances (for on diagonal blocks)
        
        The covariances can be calculated without input of the standard
        deviations for blocks on the diagonal of the matrix.
        
        When this method is called on an off diagonal block, the method has no effect.
        
        When this method is called on a block that has no correlations, the method
        has no effect.
        """
    @typing.overload
    def calculate_covariances(self, row_deviations: list[float], column_deviations: list[float]) -> None:
        """
        Calculate the covariances (for off diagonal matrices)
        
        The covariances can only be calculated with input of the standard deviations
        for blocks that are off diagonal in the matrix. Standard deviations will not
        be stored.
        
        When this method is called on a block that has no correlations, the method
        has no effect.
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
    def extract(self, reaction: njoy.dryad.id.ReactionID | None, moment: int | None, group: njoy.dryad.id.EnergyGroup | None) -> AngularDistributionCovarianceMatrix:
        ...
    @typing.overload
    def extract(self, row_reaction: njoy.dryad.id.ReactionID | None, row_moment: int | None, row_group: njoy.dryad.id.EnergyGroup | None, col_reaction: njoy.dryad.id.ReactionID | None, col_moment: int | None, col_group: njoy.dryad.id.EnergyGroup | None) -> AngularDistributionCovarianceMatrix:
        ...
    @property
    def column_metadata(self) -> AngularDistributionMetadata:
        """
        The column metadata
        """
    @property
    def correlations(self) -> numpy.ndarray[numpy.float64[m, n]] | None:
        """
        The correlation matrix
        """
    @correlations.setter
    def correlations(self, arg1: numpy.ndarray[numpy.float64[m, n]]) -> None:
        ...
    @property
    def covariances(self) -> numpy.ndarray[numpy.float64[m, n]]:
        """
        The covariance matrix
        """
    @covariances.setter
    def covariances(self, arg1: numpy.ndarray[numpy.float64[m, n]]) -> None:
        ...
    @property
    def eigendata(self) -> tuple[list[float] | None, list[numpy.ndarray[numpy.float64[m, 1]]] | None]:
        """
        The eigenvalues and eigenvectors
        """
    @eigendata.setter
    def eigendata(self, arg1: tuple[list[float] | None, list[numpy.ndarray[numpy.float64[m, 1]]] | None]) -> None:
        ...
    @property
    def eigenvalues(self) -> list[float] | None:
        """
        The eigenvalues
        """
    @property
    def eigenvectors(self) -> list[numpy.ndarray[numpy.float64[m, 1]]] | None:
        """
        The eigenvectors
        """
    @property
    def frame(self) -> njoy.dryad.ReferenceFrame:
        """
        The reference frame
        """
    @frame.setter
    def frame(self, arg1: njoy.dryad.ReferenceFrame) -> None:
        ...
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
    def row_metadata(self) -> AngularDistributionMetadata:
        """
        The row metadata
        """
    @property
    def standard_deviations(self) -> list[float] | None:
        """
        The standard deviations
        """
    @standard_deviations.setter
    def standard_deviations(self, arg1: list[float] | None) -> None:
        ...
class AngularDistributionMetadata:
    """
    Covariance metadata for angular distributions
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> AngularDistributionMetadata:
        ...
    def __deepcopy__(self, arg0: dict) -> AngularDistributionMetadata:
        ...
    def __eq__(self, arg0: AngularDistributionMetadata) -> bool:
        ...
    @typing.overload
    def __init__(self, reactions: list[njoy.dryad.id.ReactionID], moments: list[int], energies: list[float]) -> None:
        """
        Initialise the angular distribution covariance metadata
        
        Arguments:
            self          the covariance metadata
            reactions     the reaction identifiers
            moments       the Legendre moments
            energies      the group structure
        """
    @typing.overload
    def __init__(self, reaction: njoy.dryad.id.ReactionID, moment: int, energies: list[float]) -> None:
        """
        Initialise the angular distribution covariance metadata
        
        Arguments:
            self          the covariance metadata
            reaction      the reaction identifier
            moment        the Legendre moment
            energies      the group structure
        """
    @typing.overload
    def __init__(self, keys: list[tuple[njoy.dryad.id.ReactionID, int, njoy.dryad.id.EnergyGroup]]) -> None:
        """
        Initialise the angular distribution covariance metadata
        
        Arguments:
            self   the covariance metadata
            keys   the metadata keys
        """
    def __ne__(self, arg0: AngularDistributionMetadata) -> bool:
        ...
    @property
    def energies(self) -> list[float]:
        """
        The energy group boundaries
        """
    @property
    def keys(self) -> list[tuple[njoy.dryad.id.ReactionID, int, njoy.dryad.id.EnergyGroup]]:
        """
        The metadata keys
        """
    @property
    def moments(self) -> list[int]:
        """
        The Legendre moments
        """
    @property
    def reaction_identifiers(self) -> list[njoy.dryad.id.ReactionID]:
        """
        The reaction identifiers
        """
class CovarianceData:
    """
    The covariance data
    
    Parameters
    ----------
        xs : njoy.dryad.covariance.CrossSectionCovarianceData 
             the cross section covariance data
        angular : njoy.dryad.covariance.AngularDistributionCovarianceData 
             the angular distribution covariance data
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> CovarianceData:
        ...
    def __deepcopy__(self, arg0: dict) -> CovarianceData:
        ...
    def __eq__(self, arg0: CovarianceData) -> bool:
        ...
    def __init__(self, xs: CrossSectionCovarianceData | None, angular: AngularDistributionCovarianceData | None) -> None:
        """
        Initialise the covariance data
        """
    def __ne__(self, arg0: CovarianceData) -> bool:
        ...
    @property
    def angular_distribution(self) -> AngularDistributionCovarianceData | None:
        """
        The angular distribution covariances
        """
    @property
    def cross_section(self) -> CrossSectionCovarianceData | None:
        """
        The cross section covariances
        """
    @property
    def has_angular_distribution_covariances(self) -> bool:
        """
        Return whether or not there are angular distribution covariances
        """
    @property
    def has_cross_section_covariances(self) -> bool:
        """
        Return whether or not there are cross section covariances
        """
class CrossSectionCovarianceData:
    """
    The cross section covariance data
    
    Parameters
    ----------
        matrices : list of njoy.dryad.covariance. 
             the covariance matrices
    """
    __hash__: typing.ClassVar[None] = None
    @staticmethod
    def from_gendf_file(projectile: njoy.dryad.id.ParticleID, target: njoy.dryad.id.ParticleID, relative: bool, filename: str) -> CrossSectionCovarianceData | None:
        """
        Create CrossSectionCovarianceData data from an ERRORR GENDF file
        
        If there are multiple materials in the GENDF file, only the first material
        will be transformed into a ProjectileTarget.
        
        Parameters
        ----------
            projectile : njoy.dryad.id.ParticleID
                 the projectile identifier
            target : njoy.dryad.id.ParticleID
                 the target identifier
            relative : bool
                 the flag to indicate whether or not the covariance data is relative
            filename : str
                 the GENDF file name
        """
    def __copy__(self) -> CrossSectionCovarianceData:
        ...
    def __deepcopy__(self, arg0: dict) -> CrossSectionCovarianceData:
        ...
    def __eq__(self, arg0: CrossSectionCovarianceData) -> bool:
        ...
    def __init__(self, matrices: list[CrossSectionCovarianceMatrix]) -> None:
        """
        Initialise the covariance data
        """
    def __ne__(self, arg0: CrossSectionCovarianceData) -> bool:
        ...
    @typing.overload
    def covariance_matrix(self, row: njoy.dryad.id.ReactionID, column: njoy.dryad.id.ReactionID) -> CrossSectionCovarianceMatrix | list[CrossSectionCovarianceMatrix]:
        """
        Return the covariance data for a row and column reaction pair
        
        Parameters
        ----------
            row : njoy.dryad.id.ReactionID
                 the row reaction identifier
            column : njoy.dryad.id.ReactionID
                 the column reaction identifier
        """
    @typing.overload
    def covariance_matrix(self, id: njoy.dryad.id.ReactionID) -> CrossSectionCovarianceMatrix | list[CrossSectionCovarianceMatrix]:
        """
        Return the covariance data for a reaction
        
        Parameters
        ----------
            id : njoy.dryad.id.ReactionID
                 the reaction identifier
        """
    @typing.overload
    def has_covariance_matrix(self, row: njoy.dryad.id.ReactionID, column: njoy.dryad.id.ReactionID) -> bool:
        """
        Return whether or not a given reaction pair has covariance data
        
        Parameters
        ----------
            row : njoy.dryad.id.ReactionID
                 the row reaction identifier
            column : njoy.dryad.id.ReactionID
                 the column reaction identifier
        """
    @typing.overload
    def has_covariance_matrix(self, id: njoy.dryad.id.ReactionID) -> bool:
        """
        Return whether or not a given reaction has covariance data
        
        Parameters
        ----------
            id : njoy.dryad.id.ReactionID
                 the reaction identifier
        """
    @property
    def covariances(self) -> list[CrossSectionCovarianceMatrix | list[CrossSectionCovarianceMatrix]]:
        """
        The covariance data
        """
    @property
    def number_covariance_matrices(self) -> int:
        """
        The number of covariance blocks
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions for which covariance data is available
        """
    @property
    def reaction_identifiers(self) -> list[njoy.dryad.id.ReactionID]:
        """
        The reaction identifiers for which covariance data is available
        """
class CrossSectionCovarianceMatrix:
    """
    A cross section covariance matrix
    """
    def __copy__(self) -> CrossSectionCovarianceMatrix:
        ...
    def __deepcopy__(self, arg0: dict) -> CrossSectionCovarianceMatrix:
        ...
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
    def __init__(self, metadata: CrossSectionMetadata, eigenvalues: list[float], eigenvectors: list[numpy.ndarray[numpy.float64[m, 1]]], relative: bool = True, scaling: VarianceScaling | None = None) -> None:
        """
        Initialise an on-diagonal cross section covariance matrix using eigenvalues
        and eigenvectors
        
        Arguments:
            self           the covariance matrix
            metadata       the row and column metadata
            eigenvalues    the eigenvalues
            eigenvectors   the associated eigenvectors
            relative       the relative covariance flag (default is true)
            scaling        the variance scaling information (default is none)
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
    @typing.overload
    def calculate_covariances(self) -> None:
        """
        Calculate the covariances (for on diagonal blocks)
        
        The covariances can be calculated without input of the standard
        deviations for blocks on the diagonal of the matrix.
        
        When this method is called on an off diagonal block, the method has no effect.
        
        When this method is called on a block that has no correlations, the method
        has no effect.
        """
    @typing.overload
    def calculate_covariances(self, row_deviations: list[float], column_deviations: list[float]) -> None:
        """
        Calculate the covariances (for off diagonal matrices)
        
        The covariances can only be calculated with input of the standard deviations
        for blocks that are off diagonal in the matrix. Standard deviations will not
        be stored.
        
        When this method is called on a block that has no correlations, the method
        has no effect.
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
    def extract(self, reaction: njoy.dryad.id.ReactionID | None, group: njoy.dryad.id.EnergyGroup | None) -> CrossSectionCovarianceMatrix:
        ...
    @typing.overload
    def extract(self, row_reaction: njoy.dryad.id.ReactionID | None, row_group: njoy.dryad.id.EnergyGroup | None, col_reaction: njoy.dryad.id.ReactionID | None, col_group: njoy.dryad.id.EnergyGroup | None) -> CrossSectionCovarianceMatrix:
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
    @correlations.setter
    def correlations(self, arg1: numpy.ndarray[numpy.float64[m, n]]) -> None:
        ...
    @property
    def covariances(self) -> numpy.ndarray[numpy.float64[m, n]]:
        """
        The covariance matrix
        """
    @covariances.setter
    def covariances(self, arg1: numpy.ndarray[numpy.float64[m, n]]) -> None:
        ...
    @property
    def eigendata(self) -> tuple[list[float] | None, list[numpy.ndarray[numpy.float64[m, 1]]] | None]:
        """
        The eigenvalues and eigenvectors
        """
    @eigendata.setter
    def eigendata(self, arg1: tuple[list[float] | None, list[numpy.ndarray[numpy.float64[m, 1]]] | None]) -> None:
        ...
    @property
    def eigenvalues(self) -> list[float] | None:
        """
        The eigenvalues
        """
    @property
    def eigenvectors(self) -> list[numpy.ndarray[numpy.float64[m, 1]]] | None:
        """
        The eigenvectors
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
    @standard_deviations.setter
    def standard_deviations(self, arg1: list[float] | None) -> None:
        ...
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
    def __copy__(self) -> CrossSectionMetadata:
        ...
    def __deepcopy__(self, arg0: dict) -> CrossSectionMetadata:
        ...
    def __eq__(self, arg0: CrossSectionMetadata) -> bool:
        ...
    @typing.overload
    def __init__(self, reactions: list[njoy.dryad.id.ReactionID], energies: list[float]) -> None:
        """
        Initialise the cross section covariance metadata
        
        Arguments:
            self          the covariance metadata
            reactions     the reaction identifiers
            energies      the group structure
        """
    @typing.overload
    def __init__(self, reaction: njoy.dryad.id.ReactionID, energies: list[float]) -> None:
        """
        Initialise the cross section covariance metadata
        
        Arguments:
            self          the covariance metadata
            reaction      the reaction identifier
            energies      the group structure
        """
    @typing.overload
    def __init__(self, keys: list[tuple[njoy.dryad.id.ReactionID, njoy.dryad.id.EnergyGroup]]) -> None:
        """
        Initialise the cross section covariance metadata
        
        Arguments:
            self   the covariance metadata
            keys   the metadata keys
        """
    def __ne__(self, arg0: CrossSectionMetadata) -> bool:
        ...
    @property
    def energies(self) -> list[float]:
        """
        The energy group boundaries
        """
    @property
    def keys(self) -> list[tuple[njoy.dryad.id.ReactionID, njoy.dryad.id.EnergyGroup]]:
        """
        The metadata keys
        """
    @property
    def reaction_identifiers(self) -> list[njoy.dryad.id.ReactionID]:
        """
        The reaction identifiers
        """
class LinearCombinationCovariance:
    """
    Covariance data for a reaction defined as a linear combination of other reactions' covariance data
    """
    def __copy__(self) -> LinearCombinationCovariance:
        ...
    def __deepcopy__(self, arg0: dict) -> LinearCombinationCovariance:
        ...
    def __init__(self, lower: float, upper: float, reactions: list[njoy.dryad.id.ReactionID], coefficients: list[float]) -> None:
        """
        Initialise the derived covariance
        
        Arguments:
            self           the derived covariance
            lower          the lower energy limit
            upper          the upper energy limit
            reactions      the reactions in the linear combination
            coefficients   the coefficients of the linear combination
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
    def reactions(self) -> list[njoy.dryad.id.ReactionID]:
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
    def __copy__(self) -> ProductMultiplicityCovarianceMatrix:
        ...
    def __deepcopy__(self, arg0: dict) -> ProductMultiplicityCovarianceMatrix:
        ...
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
    def __init__(self, metadata: ProductMultiplicityMetadata, eigenvalues: list[float], eigenvectors: list[numpy.ndarray[numpy.float64[m, 1]]], relative: bool = True) -> None:
        """
        Initialise an on-diagonal product multiplicity covariance matrix using eigenvalues
        and eigenvectors
        
        Arguments:
            self           the covariance matrix
            metadata       the row and column metadata
            eigenvalues    the eigenvalues
            eigenvectors   the associated eigenvectors
            relative       the relative covariance flag (default is true)
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
    @typing.overload
    def calculate_covariances(self) -> None:
        """
        Calculate the covariances (for on diagonal blocks)
        
        The covariances can be calculated without input of the standard
        deviations for blocks on the diagonal of the matrix.
        
        When this method is called on an off diagonal block, the method has no effect.
        
        When this method is called on a block that has no correlations, the method
        has no effect.
        """
    @typing.overload
    def calculate_covariances(self, row_deviations: list[float], column_deviations: list[float]) -> None:
        """
        Calculate the covariances (for off diagonal matrices)
        
        The covariances can only be calculated with input of the standard deviations
        for blocks that are off diagonal in the matrix. Standard deviations will not
        be stored.
        
        When this method is called on a block that has no correlations, the method
        has no effect.
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
    def extract(self, reaction: njoy.dryad.id.ReactionID | None, group: njoy.dryad.id.EnergyGroup | None, product: njoy.dryad.id.ParticleID | None) -> ProductMultiplicityCovarianceMatrix:
        ...
    @typing.overload
    def extract(self, row_reaction: njoy.dryad.id.ReactionID | None, row_group: njoy.dryad.id.EnergyGroup | None, row_product: njoy.dryad.id.ParticleID | None, col_reaction: njoy.dryad.id.ReactionID | None, col_group: njoy.dryad.id.EnergyGroup | None, col_product: njoy.dryad.id.ParticleID | None) -> ProductMultiplicityCovarianceMatrix:
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
    @correlations.setter
    def correlations(self, arg1: numpy.ndarray[numpy.float64[m, n]]) -> None:
        ...
    @property
    def covariances(self) -> numpy.ndarray[numpy.float64[m, n]]:
        """
        The covariance matrix
        """
    @covariances.setter
    def covariances(self, arg1: numpy.ndarray[numpy.float64[m, n]]) -> None:
        ...
    @property
    def eigendata(self) -> tuple[list[float] | None, list[numpy.ndarray[numpy.float64[m, 1]]] | None]:
        """
        The eigenvalues and eigenvectors
        """
    @eigendata.setter
    def eigendata(self, arg1: tuple[list[float] | None, list[numpy.ndarray[numpy.float64[m, 1]]] | None]) -> None:
        ...
    @property
    def eigenvalues(self) -> list[float] | None:
        """
        The eigenvalues
        """
    @property
    def eigenvectors(self) -> list[numpy.ndarray[numpy.float64[m, 1]]] | None:
        """
        The eigenvectors
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
    @standard_deviations.setter
    def standard_deviations(self, arg1: list[float] | None) -> None:
        ...
class ProductMultiplicityMetadata:
    """
    Covariance metadata for product multiplicities
    """
    __hash__: typing.ClassVar[None] = None
    def __copy__(self) -> ProductMultiplicityMetadata:
        ...
    def __deepcopy__(self, arg0: dict) -> ProductMultiplicityMetadata:
        ...
    def __eq__(self, arg0: ProductMultiplicityMetadata) -> bool:
        ...
    @typing.overload
    def __init__(self, reactions: list[njoy.dryad.id.ReactionID], energies: list[float], products: list[njoy.dryad.id.ParticleID]) -> None:
        """
        Initialise the product multiplicity covariance metadata
        
        Arguments:
            self          the covariance metadata
            reactions     the reaction identifiers
            energies      the group structure
            products      the product identifiers
        """
    @typing.overload
    def __init__(self, keys: list[tuple[njoy.dryad.id.ReactionID, njoy.dryad.id.EnergyGroup, njoy.dryad.id.ParticleID]]) -> None:
        """
        Initialise the product multiplicity covariance metadata
        
        Arguments:
            self   the covariance metadata
            keys   the metadata keys
        """
    def __ne__(self, arg0: ProductMultiplicityMetadata) -> bool:
        ...
    @property
    def energies(self) -> list[float]:
        """
        The energy group boundaries
        """
    @property
    def keys(self) -> list[tuple[njoy.dryad.id.ReactionID, njoy.dryad.id.EnergyGroup, njoy.dryad.id.ParticleID]]:
        """
        The metadata keys
        """
    @property
    def product_identifiers(self) -> list[njoy.dryad.id.ParticleID]:
        """
        The reaction product identifiers
        """
    @property
    def reaction_identifiers(self) -> list[njoy.dryad.id.ReactionID]:
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
    def __copy__(self) -> VarianceScaling:
        ...
    def __deepcopy__(self, arg0: dict) -> VarianceScaling:
        ...
    def __init__(self, type: ScalingType, energies: list[float], factors: list[float]) -> None:
        """
        Initialise the metadata
        
        Arguments:
            self        the variance scaling information
            type        the scaling procedure type
            energies    the energy boundaries
            factors     the scaling factors
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
