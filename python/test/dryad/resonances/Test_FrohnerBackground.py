# standard imports
import unittest
import sys

# third party imports
import numpy as np

# local imports
from njoy.dryad.resonances import FrohnerBackground

class Test_FrohnerBackground( unittest.TestCase ) :
    """Unit test for the FrohnerBackground class."""

    def test_component( self ) :

        chunk = FrohnerBackground( distant_level_parameter = 1.,
                                   pole_strength = 2.,
                                   average_radiation_width = 3.,
                                   lower_singularity = 0.,
                                   upper_singularity = 9.55e5 )

        self.assertAlmostEqual( 1.    , chunk.distant_level_parameter )
        self.assertAlmostEqual( 2.    , chunk.pole_strength )
        self.assertAlmostEqual( 3.    , chunk.average_radiation_width )
        self.assertAlmostEqual( 0.    , chunk.lower_singularity )
        self.assertAlmostEqual( 9.55e5, chunk.upper_singularity )

        self.assertAlmostEqual( -3.291862565897340E+00 + 3.350877192982460E-05j, chunk( 1e+5 ) )

if __name__ == '__main__' :

    unittest.main()
