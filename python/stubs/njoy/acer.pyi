"""
Monte Carlo transport data file processing
"""
from __future__ import annotations
import njoy.dryad
__all__: list[str] = ['process_electron_photon_relaxation']
def process_electron_photon_relaxation(photoatomic: njoy.dryad.ProjectileTarget, electroatomic: njoy.dryad.ProjectileTarget, relaxation: njoy.dryad.AtomicRelaxation, filename: str, number: int, date: str, title: str) -> None:
    """
    Process data into an epr ace file
    
    Parameters
    ----------
        z : int
             the cosine values
        photoatomic : njoy.dryad.ProjectileTarget
             the photoatomic projectile-target data
        electroatomic : njoy.dryad.ProjectileTarget
             the electroatomic projectile-target data
        relaxation : njoy.dryad.AtomicRelaxation
             the atomic relaxation data
        filename : str
             the filename for the ace file
        number : int
             the extension number (above 0, less than 100)
        date : str
             the processing date
        title : str
             the ace file title
    """
