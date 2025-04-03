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
            self.assertAlmostEqual(  0., pdf.lower_energy_limit )
            self.assertAlmostEqual(  4., pdf.upper_energy_limit )
            self.assertEqual( 4, len( pdf.energies ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertAlmostEqual( 0.   , pdf.energies[0] )
            self.assertAlmostEqual( 2.   , pdf.energies[1] )
            self.assertAlmostEqual( 3.   , pdf.energies[2] )
            self.assertAlmostEqual( 4.   , pdf.energies[3] )
            self.assertAlmostEqual( 0.   , pdf.values[0] )
            self.assertAlmostEqual( 0.25 , pdf.values[1] )
            self.assertAlmostEqual( 0.375, pdf.values[2] )
            self.assertAlmostEqual( 0.5  , pdf.values[3] )

            self.assertEqual( False, chunk.has_cdf )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.   , chunk( energy = 0. ) )
            self.assertAlmostEqual( 0.25 , chunk( energy = 2. ) )
            self.assertAlmostEqual( 0.375, chunk( energy = 3. ) )
            self.assertAlmostEqual( 0.5  , chunk( energy = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( energy = -5. ) )
            self.assertAlmostEqual( 0.0, chunk( energy =  5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 0.125 , chunk( energy = 1.  ) )
            self.assertAlmostEqual( 0.4375, chunk( energy = 3.5 ) )

        # the data is given explicitly using a normalised table
        chunk = TabulatedEnergyDistribution( energies = [ 0., 2., 3., 4. ], values = [ 0., 0.25, 0.375, 0.5 ] )

        verify_chunk( self, chunk )

        # the data is given explicitly using an unnormalised table
        chunk = TabulatedEnergyDistribution( energies = [ 0., 2., 3., 4. ], values = [ 0., 0.5, 0.75, 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the cosine and values vector are not of the same length
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistribution( energues = [ 1., 4. ], values = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()
