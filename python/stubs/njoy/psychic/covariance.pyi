"""
Covariance data verification
"""
from __future__ import annotations
import njoy.dryad.covariance
import njoy.psychic
import typing
__all__: list[str] = ['BoundedCorrelations', 'DiagonalCorrelations', 'EigenvalueRatio', 'PositiveSemiDefinite', 'PositiveVariances', 'TestSuite']
class BoundedCorrelations:
    """
    Test to verify if all correlation values are between -1 and 1
    
    Parameters
    ----------
        tolerance : float, default 1e-10
             the comparison tolerance
    """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.CrossSectionCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix has correlations between -1 and 1
        
        The test returns the following status values:
          - Success : the correlations are between -1 and 1
          - Warning : the correlations are between -1 and 1, taking into account a tolerance
          - Fail : the correlations matrix are outside the -1 and 1 range
          - Skipped : the test was skipped
        
        The smallest and largest correlation values are available for the Warning and Fail state.
        
        Parameters
        ----------
            covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix
                the covariance matrix instance to be tested
        """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix has correlations between -1 and 1
        """
    def __init__(self, tolerance: float = 1e-10) -> None:
        """
        Initialise the test
        """
    @property
    def largest_correlation(self) -> float | None:
        """
        The largest correlation value that was found
        """
    @largest_correlation.setter
    def largest_correlation(self, arg1: float | None) -> None:
        ...
    @property
    def name(self) -> str:
        """
        The test name
        """
    @property
    def smallest_correlation(self) -> float | None:
        """
        The smallest correlation value that was found
        """
    @smallest_correlation.setter
    def smallest_correlation(self, arg1: float | None) -> None:
        ...
    @property
    def status(self) -> njoy.psychic.TestStatus | None:
        """
        The test status
        """
    @status.setter
    def status(self, arg1: njoy.psychic.TestStatus | None) -> None:
        ...
    @property
    def tolerance(self) -> float:
        """
        The comparison tolerance
        """
class DiagonalCorrelations:
    """
    Test to verify if all diagonal correlation values are equal to 1
    
    Parameters
    ----------
        tolerance : float, default 1e-10
             the comparison tolerance
    """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.CrossSectionCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix has diagonal correlations equal to 1
        
        The test returns the following status values:
          - Success : all diagonal correlations are equal to 1
          - Warning : all diagonal correlations are equal to 1, taking into account a tolerance
          - Fail : not all diagonal correlations are equal to 1
          - Skipped : the test was skipped
        
        Parameters
        ----------
            covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix
                the covariance matrix instance to be tested
        """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix has diagonal correlations equal to 1
        """
    def __init__(self, tolerance: float = 1e-10) -> None:
        """
        Initialise the test
        """
    @property
    def name(self) -> str:
        """
        The test name
        """
    @property
    def status(self) -> njoy.psychic.TestStatus | None:
        """
        The test status
        """
    @status.setter
    def status(self, arg1: njoy.psychic.TestStatus | None) -> None:
        ...
    @property
    def tolerance(self) -> float:
        """
        The comparison tolerance
        """
class EigenvalueRatio:
    """
    Test to verify if the positive eigenvalue ratio looks reasonable
    
    Parameters
    ----------
        ratio : float, default 1e-8
             the smallest allowable positive eigenvalue ratio
    """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.CrossSectionCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix has a reasonable eigenvalue ratio
        
        The test returns the following status values:
          - Success : the eigenvalue ratio is larger than or equal to the tolerance
          - Fail    : the eigenvalue ratio is smaller than the tolerance
          - Skipped : the test was skipped
        
        The smallest and largest positive eigenvalue and their ratio is always available.
        
        Parameters
        ----------
            covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix
                the covariance matrix instance to be tested
        """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix has a reasonable eigenvalue ratio
        """
    def __init__(self, ratio: float = 1e-08) -> None:
        """
        Initialise the test
        """
    @property
    def eigenvalue_tatio(self) -> float | None:
        """
        The positive eigenvalue ratio
        """
    @eigenvalue_tatio.setter
    def eigenvalue_tatio(self, arg1: float | None) -> None:
        ...
    @property
    def largest_positive_eigenvalue(self) -> float | None:
        """
        The largest positive eigenvalue that was found
        """
    @largest_positive_eigenvalue.setter
    def largest_positive_eigenvalue(self, arg1: float | None) -> None:
        ...
    @property
    def name(self) -> str:
        """
        The test name
        """
    @property
    def smallest_acceptable_ratio(self) -> float:
        """
        The  smallest acceptable eigenvalue ratio
        """
    @property
    def smallest_positive_eigenvalue(self) -> float | None:
        """
        The smallest positive eigenvalue that was found
        """
    @smallest_positive_eigenvalue.setter
    def smallest_positive_eigenvalue(self, arg1: float | None) -> None:
        ...
    @property
    def status(self) -> njoy.psychic.TestStatus | None:
        """
        The test status
        """
    @status.setter
    def status(self, arg1: njoy.psychic.TestStatus | None) -> None:
        ...
class PositiveSemiDefinite:
    """
    Test to verify if a covariance matrix is positive semi-definite
    
    Parameters
    ----------
        negative : float, default -1e-10
             the largest allowed negative eigenvalue
    """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.CrossSectionCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix is positive semi-definite
        
        A covariance matrix is positive semi-definite if it is a square symmetric matrix
        that has eigenvalues that are larger than or equal to zero. Construction of
        on-diagonal covariance matrices already requires square and symmetric matrices so
        this particular aspect is not tested here.
        
        The test returns the following status values:
          - Success : the covariance matrix is positive semi-definite
          - Warning : the covariance matrix is can be considered positive semi-definite by accepting small negative eigenvalues
          - Fail : the on-diagonal covariance matrix is not positive semi-definite
          - Skipped : the test was skipped
        
        The largest negative eigenvalue is available for the Warning and Fail state.
        
        Parameters
        ----------
            covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix
                the covariance matrix instance to be tested
        """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix is positive semi-definite
        """
    def __init__(self, negative: float = -1e-10) -> None:
        """
        Initialise the test
        """
    @property
    def allowed_negative_eigen_value(self) -> float:
        """
        The largest allowed negative eigenvalue
        """
    @property
    def largest_negative_eigen_value(self) -> float | None:
        """
        The largest negative eigenvalue that was found
        """
    @largest_negative_eigen_value.setter
    def largest_negative_eigen_value(self, arg1: float | None) -> None:
        ...
    @property
    def name(self) -> str:
        """
        The test name
        """
    @property
    def status(self) -> njoy.psychic.TestStatus | None:
        """
        The test status
        """
    @status.setter
    def status(self, arg1: njoy.psychic.TestStatus | None) -> None:
        ...
class PositiveVariances:
    """
    Test to verify if all variances are strictly positive
    """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.CrossSectionCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix has variances that are strictly positive
        
        The test returns the following status values:
          - Success : all variances are strictly positive
          - Warning : all variances are positive
          - Fail : soem of the variances seem to be negative
          - Skipped : the test was skipped
        
        Parameters
        ----------
            covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix
                the covariance matrix instance to be tested
        """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix has variances that are strictly positive
        """
    def __init__(self) -> None:
        """
        Initialise the test
        """
    @property
    def name(self) -> str:
        """
        The test name
        """
    @property
    def status(self) -> njoy.psychic.TestStatus | None:
        """
        The test status
        """
    @status.setter
    def status(self, arg1: njoy.psychic.TestStatus | None) -> None:
        ...
class TestSuite:
    """
    A comprehensive covariance test suite
    
    Parameters
    ----------
        tolerance : float, default 1e-10
             the comparison tolerance
        negative : float, default -1e-10
             the largest allowed negative eigenvalue
    """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.CrossSectionCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Perform the test suite on the provided covariance matrix
        
        Parameters
        ----------
            covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix
                the covariance matrix instance to be tested
        """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Perform the test suite on the provided covariance matrix
        """
    def __init__(self, tolerance: float = 1e-10, negative: float = -1e-10) -> None:
        """
        Initialise the test suite
        """
    @property
    def allowed_negative_eigen_value(self) -> float:
        """
        The largest allowed negative eigenvalue
        """
    @property
    def bounded_correlations(self) -> BoundedCorrelations:
        """
        The correlations between -1 and 1 test
        """
    @property
    def diagonal_correlations(self) -> DiagonalCorrelations:
        """
        The diagonal correlations are all 1 test
        """
    @property
    def name(self) -> str:
        """
        The test name
        """
    @property
    def positive_semi_definite(self) -> PositiveSemiDefinite:
        """
        The positive semi-definite test
        """
    @property
    def positive_variances(self) -> PositiveVariances:
        """
        The positive variance test
        """
    @property
    def status(self) -> njoy.psychic.TestStatus | None:
        """
        The test status
        """
    @status.setter
    def status(self, arg1: njoy.psychic.TestStatus | None) -> None:
        ...
    @property
    def tolerance(self) -> float:
        """
        The comparison tolerance
        """
