"""
Correcting and updating data
"""
from __future__ import annotations
import njoy.dryad
from . import covariance
__all__: list[str] = ['covariance', 'curate_compton_profiles', 'prune_cross_section', 'prune_cross_sections']
def curate_compton_profiles(photoatomic: njoy.dryad.ProjectileTarget, relaxation: njoy.dryad.AtomicRelaxation) -> None:
    """
    Curate the Compton profile data
    
    This function ensures that the Compton profile data in the incoherent
    scattering function and the atomic relaxation data are consistent. The
    following operations are performed on the Compton profile data:
      - when the Compton profile data contains a subshell that is not present
        in the atomic relaxation data, that profile is removed
      - when the atomic relaxation data contains subshells that are not present
        in the Compton profiles, then the Compton profile for the missing subshell
        is set to the one with the same principal and azimuthal quantum number
        that is already present
    
    Parameters
    ----------
        photoatomic : njoy.dryad.ProjectileTarget
            the photoatomic projectile-target data to be curated
        relaxation : njoy.dryad.AtomicRelaxation
            the atomic relaxation data
    """
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
