# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TabulatedEnergyDistribution
from dryad import InterpolationType

class Test_dryad_TabulatedEnergyDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedEnergyDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            # verify content
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 0.   , chunk.energies[0] )
            self.assertAlmostEqual( 2.   , chunk.energies[1] )
            self.assertAlmostEqual( 3.   , chunk.energies[2] )
            self.assertAlmostEqual( 4.   , chunk.energies[3] )
            self.assertAlmostEqual( 0.   / normalisation, chunk.values[0] )
            self.assertAlmostEqual( 0.5  / normalisation, chunk.values[1] )
            self.assertAlmostEqual( 0.75 / normalisation, chunk.values[2] )
            self.assertAlmostEqual( 1.   / normalisation, chunk.values[3] )
            self.assertAlmostEqual( 3, chunk.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            pdf = chunk.pdf
            self.assertAlmostEqual(  0., pdf.lower_energy_limit )
            self.assertAlmostEqual(  4., pdf.upper_energy_limit )
            self.assertEqual( 4, len( pdf.energies ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( 0.   , pdf.energies[0] )
            self.assertAlmostEqual( 2.   , pdf.energies[1] )
            self.assertAlmostEqual( 3.   , pdf.energies[2] )
            self.assertAlmostEqual( 4.   , pdf.energies[3] )
            self.assertAlmostEqual( 0.   / normalisation, pdf.values[0] )
            self.assertAlmostEqual( 0.5  / normalisation, pdf.values[1] )
            self.assertAlmostEqual( 0.75 / normalisation, pdf.values[2] )
            self.assertAlmostEqual( 1.   / normalisation, pdf.values[3] )
            self.assertAlmostEqual( 3, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = chunk.cdf
            self.assertAlmostEqual(  0., cdf.lower_energy_limit )
            self.assertAlmostEqual(  4., cdf.upper_energy_limit )
            self.assertEqual( 4, len( cdf.energies ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( 0.   , cdf.energies[0] )
            self.assertAlmostEqual( 2.   , cdf.energies[1] )
            self.assertAlmostEqual( 3.   , cdf.energies[2] )
            self.assertAlmostEqual( 4.   , cdf.energies[3] )
            self.assertAlmostEqual( 0.    / normalisation, cdf.values[0] )
            self.assertAlmostEqual( 0.5   / normalisation, cdf.values[1] )
            self.assertAlmostEqual( 1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual( 2.    / normalisation, cdf.values[3] )
            self.assertAlmostEqual( 3, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.   / normalisation, chunk( energy = 0. ) )
            self.assertAlmostEqual( 0.5  / normalisation, chunk( energy = 2. ) )
            self.assertAlmostEqual( 0.75 / normalisation, chunk( energy = 3. ) )
            self.assertAlmostEqual( 1.   / normalisation, chunk( energy = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( energy = -5. ) )
            self.assertAlmostEqual( 0.0, chunk( energy =  5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 0.25  / normalisation, chunk( energy = 1.  ) )
            self.assertAlmostEqual( 0.875 / normalisation, chunk( energy = 3.5 ) )

            # verify average cosine
            self.assertAlmostEqual( 128. / 24. / normalisation, chunk.average_energy )

            # verify linearisation
            linear = chunk.linearise()

            pdf = linear.pdf
            self.assertAlmostEqual(  0., pdf.lower_energy_limit )
            self.assertAlmostEqual(  4., pdf.upper_energy_limit )
            self.assertEqual( 4, len( pdf.energies ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( 0.   , pdf.energies[0] )
            self.assertAlmostEqual( 2.   , pdf.energies[1] )
            self.assertAlmostEqual( 3.   , pdf.energies[2] )
            self.assertAlmostEqual( 4.   , pdf.energies[3] )
            self.assertAlmostEqual( 0.   / normalisation, pdf.values[0] )
            self.assertAlmostEqual( 0.5  / normalisation, pdf.values[1] )
            self.assertAlmostEqual( 0.75 / normalisation, pdf.values[2] )
            self.assertAlmostEqual( 1.   / normalisation, pdf.values[3] )
            self.assertAlmostEqual( 3, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = linear.cdf
            self.assertAlmostEqual(  0., cdf.lower_energy_limit )
            self.assertAlmostEqual(  4., cdf.upper_energy_limit )
            self.assertEqual( 4, len( cdf.energies ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( 0.   , cdf.energies[0] )
            self.assertAlmostEqual( 2.   , cdf.energies[1] )
            self.assertAlmostEqual( 3.   , cdf.energies[2] )
            self.assertAlmostEqual( 4.   , cdf.energies[3] )
            self.assertAlmostEqual( 0.    / normalisation, cdf.values[0] )
            self.assertAlmostEqual( 0.5   / normalisation, cdf.values[1] )
            self.assertAlmostEqual( 1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual( 2.    / normalisation, cdf.values[3] )
            self.assertAlmostEqual( 3, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

        # the data is given explicitly
        chunk1 = TabulatedEnergyDistribution( energies = [ 0., 2., 3., 4. ], values = [ 0., 0.5, 0.75, 1. ],
                                              interpolant = InterpolationType.LinearLinear, normalise = False )
        chunk2 = TabulatedEnergyDistribution( energies = [ 0., 2., 3., 4. ], values = [ 0., 0.5, 0.75, 1. ],
                                              interpolant = InterpolationType.LinearLinear, normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

    def test_comparison( self ) :

        left = TabulatedEnergyDistribution( [ 1., 3. ], [ 0.5, 0.5 ] )
        equal = TabulatedEnergyDistribution( [ 1., 3. ], [ 0.5, 0.5 ] )
        unnormalised = TabulatedEnergyDistribution( [ 1., 3. ], [ 1.0, 1.0 ], InterpolationType.LinearLinear, True )
        different = TabulatedEnergyDistribution( [ 1., 4. ], [ 0.25, 0.75 ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( True, ( left == unnormalised ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( False, ( left != unnormalised ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # the cosine and values vector are not of the same length
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistribution( energues = [ 1., 4. ], values = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()
