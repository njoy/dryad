"""
Covariance data verification
"""
from __future__ import annotations
import njoy.dryad.covariance
import njoy.psychic
import typing
__all__: list[str] = ['IsPositiveSemiDefinite']
class IsPositiveSemiDefinite:
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
          - Success : the on-diagonal covariance matrix is positive semi-definite
          - Warning : the on-diagonal covariance matrix is can be considered positive
                      semi-definite by accepting small negative eigenvalues
          - Fail : the on-diagonal covariance matrix is not positive semi-definite
          - Skipped : the covariance matrix provided is not on-diagonal (ie its eigenvalues)
                      cannot be calculated
        
        The largest negative eigenvalue is available for the Warning and Fail state.
        Parameters
        ----------
            covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix
                the covariance matrix instance to be tested
        """
    @typing.overload
    def __call__(self, covariance: njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix) -> njoy.psychic.TestStatus | None:
        """
        Verify if the provided covariance matrix is positive semi-definite
        
        A covariance matrix is positive semi-definite if it is a square symmetric matrix
        that has eigenvalues that are larger than or equal to zero. Construction of
        on-diagonal covariance matrices already requires square and symmetric matrices so
        this particular aspect is not tested here.
        
        The test returns the following status values:
          - Success : the on-diagonal covariance matrix is positive semi-definite
          - Warning : the on-diagonal covariance matrix is can be considered positive
                      semi-definite by accepting small negative eigenvalues
          - Fail : the on-diagonal covariance matrix is not positive semi-definite
          - Skipped : the covariance matrix provided is not on-diagonal (ie its eigenvalues)
                      cannot be calculated
        
        The largest negative eigenvalue is available for the Warning and Fail state.
        Parameters
        ----------
            covariance : njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix
                the covariance matrix instance to be tested
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
