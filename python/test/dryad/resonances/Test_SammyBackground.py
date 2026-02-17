# standard imports
import unittest
import sys

# third party imports
import numpy as np

# local imports
from njoy.dryad.resonances import SammyBackground

class Test_SammyBackground( unittest.TestCase ) :
    """Unit test for the SammyBackground class."""

    def test_component( self ) :

        chunk = SammyBackground( polynomial_coefficients = [ -0.043, 2.8e-8, 0 ],
                                 logarithmic_coefficients = [  0.01, 0. ],
                                 lower_singularity = 0.,
                                 upper_singularity = 9.55e5 )

        self.assertAlmostEqual( 3, len( chunk.polynomial_coefficients ) )
        self.assertAlmostEqual( 2, len( chunk.logarithmic_coefficients ) )

        self.assertAlmostEqual( -0.043, chunk.polynomial_coefficients[0] )
        self.assertAlmostEqual( 2.8e-8, chunk.polynomial_coefficients[1] )
        self.assertAlmostEqual( 0.    , chunk.polynomial_coefficients[2] )
        self.assertAlmostEqual( 0.01  , chunk.logarithmic_coefficients[0] )
        self.assertAlmostEqual( 0.    , chunk.logarithmic_coefficients[1] )
        self.assertAlmostEqual( 0.    , chunk.logarithmic_coefficients[1] )
        self.assertAlmostEqual( 0.    , chunk.lower_singularity )
        self.assertAlmostEqual( 9.55e5, chunk.upper_singularity )

        self.assertAlmostEqual( -0.043 + 2.8e-8 - 0.01 * np.log( 9.55e5 - 1. / 1. ), chunk( 1. ) )

if __name__ == '__main__' :

    unittest.main()
