# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TabulatedEnergyDistribution

class Test_dryad_TabulatedEnergyDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedEnergyDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            pdf = chunk.pdf
            self.assertAlmostEqual(  1., pdf.lower_energy_limit )
            self.assertAlmostEqual(  4., pdf.upper_energy_limit )
            self.assertEqual( 4, len( pdf.energies ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertAlmostEqual( 1., pdf.energies[0] )
            self.assertAlmostEqual( 2., pdf.energies[1] )
            self.assertAlmostEqual( 3., pdf.energies[2] )
            self.assertAlmostEqual( 4., pdf.energies[3] )
            self.assertAlmostEqual( 4., pdf.values[0] )
            self.assertAlmostEqual( 3., pdf.values[1] )
            self.assertAlmostEqual( 2., pdf.values[2] )
            self.assertAlmostEqual( 1., pdf.values[3] )

            self.assertEqual( False, chunk.has_cdf )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( energy = 1. ) )
            self.assertAlmostEqual( 3., chunk( energy = 2. ) )
            self.assertAlmostEqual( 2., chunk( energy = 3. ) )
            self.assertAlmostEqual( 1., chunk( energy = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( energy = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( energy = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( energy = 1.5 ) )
            self.assertAlmostEqual( 2.5, chunk( energy = 2.5 ) )
            self.assertAlmostEqual( 1.5, chunk( energy = 3.5 ) )

        # the data is given explicitly using a normalised series
        chunk = TabulatedEnergyDistribution( energies = [ 1., 2., 3., 4. ], values = [ 4., 3., 2., 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the cosine and values vector are not of the same length
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistribution( energues = [ 1., 4. ], values = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()
