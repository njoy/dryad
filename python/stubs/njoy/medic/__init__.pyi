"""
Correcting and updating data
"""
from __future__ import annotations
import njoy.dryad
from . import covariance
__all__: list[str] = ['covariance', 'prune_cross_section', 'prune_cross_sections']
def prune_cross_section(lower_energy: float, upper_energy: float, xs: njoy.dryad.TabulatedCrossSection) -> None:
    """
    Prune cross section data
    
    Parameters
    ----------
        lower_energy : float
            the new lower energy limit
        upper_energy : float
            the new upper energy limit
        xs : njoy.dryad.TabulatedCrossSection
            the cross section table to be modified
    """
def prune_cross_sections(lower_energy: float, upper_energy: float, pt: njoy.dryad.ProjectileTarget) -> None:
    """
    Prune cross section data
    
    Parameters
    ----------
        lower_energy : float
            the new lower energy limit
        upper_energy : float
            the new upper energy limit
        pt : njoy.dryad.ProjectileTarget
            the projectile-target data to be modified
    """
