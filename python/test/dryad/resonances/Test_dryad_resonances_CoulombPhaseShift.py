# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.resonances import CoulombPhaseShift

class Test_dryad_resonances_CoulombPhaseShift( unittest.TestCase ) :
    """Unit test for the CoulombPhaseShift class."""

    def test_component( self ) :

        phaseShift = CoulombPhaseShift( 0 )

        self.assertEqual( 0, phaseShift.orbital_angular_momentum )
        phaseShift( 1., 1. )

        phaseShift = CoulombPhaseShift( 1 )

        self.assertEqual( 1, phaseShift.orbital_angular_momentum )
        phaseShift( 1., 1. )

        phaseShift = CoulombPhaseShift( 2 )

        self.assertEqual( 2, phaseShift.orbital_angular_momentum )
        phaseShift( 1., 1. )

        phaseShift = CoulombPhaseShift( 3 )

        self.assertEqual( 3, phaseShift.orbital_angular_momentum )
        phaseShift( 1., 1. )

        phaseShift = CoulombPhaseShift( 4 )

        self.assertEqual( 4, phaseShift.orbital_angular_momentum )
        phaseShift( 1., 1. )

if __name__ == '__main__' :

    unittest.main()
