"""
Correcting and updating data
"""
from __future__ import annotations
import njoy.dryad
__all__: list[str] = ['prune_cross_section', 'prune_cross_sections']
def prune_cross_section(lower_energy: float, upper_energy: float, xs: njoy.dryad.TabulatedCrossSection) -> None:
    """
    Prune cross section data
    
    Arguments:
        lower_energy   the new lower energy limit
        upper_energy   the new upper energy limit
        xs             the cross section table to be modified
    """
def prune_cross_sections(lower_energy: float, upper_energy: float, xs: njoy.dryad.ProjectileTarget) -> None:
    """
    Prune cross section data
    
    Arguments:
        lower_energy   the new lower energy limit
        upper_energy   the new upper energy limit
        pt             the projectile-target data to be modified
    """
