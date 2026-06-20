"""
Linearisation, unionisation and resonance reconstruction
"""
from __future__ import annotations
import njoy.dryad
__all__: list[str] = ['calculate_summation_cross_sections', 'unionise_cross_sections']
def calculate_summation_cross_sections(pt: njoy.dryad.ProjectileTarget, tolerance: float = 0.001) -> None:
    """
    Calculate summation cross sections
    
    This function recalculates the cross section of all summation reactions of
    a ProjectileTarget instance. It does so by linearising the cross sections of
    the partials (if required) and summing them together.
    
    Parameters
    ----------
        pt : njoy.dryad.ProjectileTarget
            the projectile-target data to be modified
        tolerance : float, default 0.001
            the linearisation tolerance (default: 0.1%)
    """
def unionise_cross_sections(pt: njoy.dryad.ProjectileTarget, exclude_summation: bool = False) -> None:
    """
    Unionise cross section data in a ProjectileTarget instance
    
    This function takes all cross section data in the ProjectileTarget
    instance and unionises the cross section grids. It does not linearise
    the data but reevaluates the data using the proper interpolation types
    of the cross section data.
    
    By default, summation cross sections are included in the unionisation process
    unless explicitly excluded by the user. Switching on the exclusion of summation
    cross sections may be useful when the user is going to recalculate the summation
    cross sections after unionisation.
    
    Parameters
    ----------
        pt : njoy.dryad.ProjectileTarget
            the projectile-target data to be modified
        exclude_summation : bool, default False
            option to exclude summation reactions in the unionisation
    """
