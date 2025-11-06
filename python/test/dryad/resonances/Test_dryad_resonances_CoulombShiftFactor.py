# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.resonances import CoulombShiftFactor

class Test_dryad_resonances_CoulombShiftFactor( unittest.TestCase ) :
    """Unit test for the CoulombShiftFactor class."""

    def test_component( self ) :

        shiftFactor = CoulombShiftFactor( 0 )

        self.assertEqual( 0, shiftFactor.orbital_angular_momentum )
        shiftFactor( 1., 1. )

        shiftFactor = CoulombShiftFactor( 1 )

        self.assertEqual( 1, shiftFactor.orbital_angular_momentum )
        shiftFactor( 1., 1. )

        shiftFactor = CoulombShiftFactor( 2 )

        self.assertEqual( 2, shiftFactor.orbital_angular_momentum )
        shiftFactor( 1., 1. )

        shiftFactor = CoulombShiftFactor( 3 )

        self.assertEqual( 3, shiftFactor.orbital_angular_momentum )
        shiftFactor( 1., 1. )

        shiftFactor = CoulombShiftFactor( 4 )

        self.assertEqual( 4, shiftFactor.orbital_angular_momentum )
        shiftFactor( 1., 1. )

if __name__ == '__main__' :

    unittest.main()
