"""
Covariance functions
"""
from __future__ import annotations
import njoy.dryad.covariance
import typing
__all__: list[str] = ['prune_small_eigenvalues']
@typing.overload
def prune_small_eigenvalues(eigenvalue: float, covariance: njoy.dryad.covariance.CrossSectionCovarianceMatrix) -> None:
    """
    Prune eigenvalues below a given value from the covariance matrix
    
    Parameters
    ----------
        eigenvalue : float
            the smallest allowed eigenvalue
        covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix
            the covariance matrix to be modified
    """
@typing.overload
def prune_small_eigenvalues(eigenvalue: float, covariance: njoy.dryad.covariance.AngularDistributionCovarianceMatrix) -> None:
    """
    Prune eigenvalues below a given value from the covariance matrix
    """
@typing.overload
def prune_small_eigenvalues(eigenvalue: float, covariance: njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix) -> None:
    """
    Prune eigenvalues below a given value from the covariance matrix
    """
