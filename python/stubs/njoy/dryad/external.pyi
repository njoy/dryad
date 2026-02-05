"""
External data and models
"""
from __future__ import annotations
import njoy.dryad
__all__: list[str] = ['ComptonProfiles']
class ComptonProfiles:
    """
    Compton profile data and models
    
    Compton profiles are currently not available in standard evaluated nuclear data
    files. The ComptonProfiles class is basically going to contain factory functions
    to produce Compton profiles for a given atom, either based on external data or
    possibly model calculations.
    
    Currently we only have tabulated data based on Biggs, Mendelsohn and Mann
    calculated profiles from the following reference:
      F. Biggs, L. B. Mendelsohn, J. B. Mann,
      Hartree-Fock Compton profiles for the elements,
      Atomic data and nuclear data table, 16, 201-309 (1975)
    """
    @staticmethod
    def apply(pt: njoy.dryad.ProjectileTarget, normalise: bool) -> None:
        """
        Apply Compton profiles to a ProjectileTarget instance
        
        Parameters
        ----------
            pt : njoy.dryad.ProjectileTarget
                 projectile-target data to be modified
            normalise : bool, default false
                option to indicate whether or not to normalise
                all probability data (default: no normalisation)
        """
    @staticmethod
    def biggs_mendelsohn_mann_profiles(z: int, normalise: bool) -> list[njoy.dryad.TabulatedComptonProfile]:
        """
        Return Biggs, Mendelsohn and Mann Compton profiles for a given z number
        
        Parameters
        ----------
            z : int
                 the cosine values
            normalise : bool, default false
                option to indicate whether or not to normalise
                all probability data (default: no normalisation)
        """
