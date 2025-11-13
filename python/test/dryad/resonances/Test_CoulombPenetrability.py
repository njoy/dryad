# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.resonances import CoulombPenetrability

class Test_dryad_resonances_CoulombPenetrability( unittest.TestCase ) :
    """Unit test for the CoulombPenetrability class."""

    def test_component( self ) :

        penetrability = CoulombPenetrability( 0 )

        self.assertEqual( 0, penetrability.orbital_angular_momentum )
        penetrability( 1., 1. )

        penetrability = CoulombPenetrability( 1 )

        self.assertEqual( 1, penetrability.orbital_angular_momentum )
        penetrability( 1., 1. )

        penetrability = CoulombPenetrability( 2 )

        self.assertEqual( 2, penetrability.orbital_angular_momentum )
        penetrability( 1., 1. )

        penetrability = CoulombPenetrability( 3 )

        self.assertEqual( 3, penetrability.orbital_angular_momentum )
        penetrability( 1., 1. )

        penetrability = CoulombPenetrability( 4 )

        self.assertEqual( 4, penetrability.orbital_angular_momentum )
        penetrability( 1., 1. )

if __name__ == '__main__' :

    unittest.main()
