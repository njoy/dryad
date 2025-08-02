# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TabulatedEnergyDistribution
from dryad import TabulatedEnergyDistributions
from dryad import InterpolationType

class Test_dryad_TabulatedEnergyDistributions( unittest.TestCase ) :
    """Unit test for the TabulatedEnergyDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            # verify content
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.grid ) )
            self.assertEqual( 4, len( chunk.distributions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 3., chunk.grid[2] )
            self.assertAlmostEqual( 4., chunk.grid[3] )
            self.assertEqual( 2, len( chunk.distributions[0].pdf.energies ) )
            self.assertEqual( 2, len( chunk.distributions[0].pdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[1].pdf.energies ) )
            self.assertEqual( 2, len( chunk.distributions[1].pdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[2].pdf.energies ) )
            self.assertEqual( 2, len( chunk.distributions[2].pdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[3].pdf.energies ) )
            self.assertEqual( 2, len( chunk.distributions[3].pdf.values ) )
            self.assertAlmostEqual( 0.  , chunk.distributions[0].pdf.energies[0] )
            self.assertAlmostEqual( 4.  , chunk.distributions[0].pdf.energies[1] )
            self.assertAlmostEqual( 0.  , chunk.distributions[1].pdf.energies[0] )
            self.assertAlmostEqual( 4.  , chunk.distributions[1].pdf.energies[1] )
            self.assertAlmostEqual( 0.  , chunk.distributions[2].pdf.energies[0] )
            self.assertAlmostEqual( 4.  , chunk.distributions[2].pdf.energies[1] )
            self.assertAlmostEqual( 0.  , chunk.distributions[3].pdf.energies[0] )
            self.assertAlmostEqual( 4.  , chunk.distributions[3].pdf.energies[1] )
            self.assertAlmostEqual( 0.5  / normalisation, chunk.distributions[0].pdf.values[0] )
            self.assertAlmostEqual( 0.5  / normalisation, chunk.distributions[0].pdf.values[1] )
            self.assertAlmostEqual( 0.52 / normalisation, chunk.distributions[1].pdf.values[0] )
            self.assertAlmostEqual( 0.48 / normalisation, chunk.distributions[1].pdf.values[1] )
            self.assertAlmostEqual( 0.48 / normalisation, chunk.distributions[2].pdf.values[0] )
            self.assertAlmostEqual( 0.52 / normalisation, chunk.distributions[2].pdf.values[1] )
            self.assertAlmostEqual( 0.2  / normalisation, chunk.distributions[3].pdf.values[0] )
            self.assertAlmostEqual( 0.8  / normalisation, chunk.distributions[3].pdf.values[1] )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.energies ) )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[1].cdf.energies ) )
            self.assertEqual( 2, len( chunk.distributions[1].cdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[2].cdf.energies ) )
            self.assertEqual( 2, len( chunk.distributions[2].cdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[3].cdf.energies ) )
            self.assertEqual( 2, len( chunk.distributions[3].cdf.values ) )
            self.assertAlmostEqual( 0.  , chunk.distributions[0].cdf.energies[0] )
            self.assertAlmostEqual( 4.  , chunk.distributions[0].cdf.energies[1] )
            self.assertAlmostEqual( 0.  , chunk.distributions[1].cdf.energies[0] )
            self.assertAlmostEqual( 4.  , chunk.distributions[1].cdf.energies[1] )
            self.assertAlmostEqual( 0.  , chunk.distributions[2].cdf.energies[0] )
            self.assertAlmostEqual( 4.  , chunk.distributions[2].cdf.energies[1] )
            self.assertAlmostEqual( 0.  , chunk.distributions[3].cdf.energies[0] )
            self.assertAlmostEqual( 4.  , chunk.distributions[3].cdf.energies[1] )
            self.assertAlmostEqual( 0.0 / normalisation, chunk.distributions[0].cdf.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, chunk.distributions[0].cdf.values[1] )
            self.assertAlmostEqual( 0.0 / normalisation, chunk.distributions[1].cdf.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, chunk.distributions[1].cdf.values[1] )
            self.assertAlmostEqual( 0.0 / normalisation, chunk.distributions[2].cdf.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, chunk.distributions[2].cdf.values[1] )
            self.assertAlmostEqual( 0.0 / normalisation, chunk.distributions[3].cdf.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, chunk.distributions[3].cdf.values[1] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            # verify evaluation
            self.assertAlmostEqual( 0.5  / normalisation, chunk( 1., 3. ) )
            self.assertAlmostEqual( 0.49 / normalisation, chunk( 2., 3. ) )
            self.assertAlmostEqual( 0.51 / normalisation, chunk( 3., 3. ) )
            self.assertAlmostEqual( 0.65 / normalisation, chunk( 4., 3. ) )

            self.assertAlmostEqual( 0.    , chunk( 0., 3. ) )
            self.assertAlmostEqual( 0.    , chunk( 5., 3. ) )

            self.assertAlmostEqual( 0.495 / normalisation, chunk( 1.5, 3. ) )
            self.assertAlmostEqual( 0.5   / normalisation, chunk( 2.5, 3. ) )
            self.assertAlmostEqual( 0.58  / normalisation, chunk( 3.5, 3. ) )

            # verify average energies
            energies = chunk.average_energies
            self.assertAlmostEqual( 1., energies.lower_energy_limit )
            self.assertAlmostEqual( 4., energies.upper_energy_limit )
            self.assertEqual( 4, energies.number_points )
            self.assertEqual( 1, energies.number_regions )
            self.assertEqual( 4, len( energies.energies ) )
            self.assertEqual( 4, len( energies.values ) )
            self.assertEqual( 1, len( energies.boundaries ) )
            self.assertEqual( 1, len( energies.interpolants ) )
            self.assertAlmostEqual( 1., energies.energies[0] )
            self.assertAlmostEqual( 2., energies.energies[1] )
            self.assertAlmostEqual( 3., energies.energies[2] )
            self.assertAlmostEqual( 4., energies.energies[3] )
            self.assertAlmostEqual( 2. * 2.           / normalisation, energies.values[0] )
            self.assertAlmostEqual( 2. * 1184. / 600. / normalisation, energies.values[1] )
            self.assertAlmostEqual( 2. * 1216. / 600. / normalisation, energies.values[2] )
            self.assertAlmostEqual( 2. * 2.4          / normalisation, energies.values[3] )
            self.assertEqual( 3, energies.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, energies.interpolants[0] )
            self.assertEqual( True, energies.is_linearised )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )
            self.assertEqual( 4, len( linear.grid ) )
            self.assertEqual( 4, len( linear.distributions ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )
            self.assertAlmostEqual( 1., linear.grid[0] )
            self.assertAlmostEqual( 2., linear.grid[1] )
            self.assertAlmostEqual( 3., linear.grid[2] )
            self.assertAlmostEqual( 4., linear.grid[3] )
            self.assertEqual( True, linear.distributions[0].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[1].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[2].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[3].pdf.is_linearised )
            self.assertEqual( 2, len( linear.distributions[0].pdf.energies ) )
            self.assertEqual( 2, len( linear.distributions[1].pdf.energies ) )
            self.assertEqual( 2, len( linear.distributions[2].pdf.energies ) )
            self.assertEqual( 2, len( linear.distributions[3].pdf.energies ) )
            self.assertEqual( 2, len( linear.distributions[0].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[1].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[2].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[3].pdf.values ) )
            self.assertAlmostEqual(  0.  , linear.distributions[0].pdf.energies[0] )
            self.assertAlmostEqual(  4.  , linear.distributions[0].pdf.energies[1] )
            self.assertAlmostEqual(  0.  , linear.distributions[1].pdf.energies[0] )
            self.assertAlmostEqual(  4.  , linear.distributions[1].pdf.energies[1] )
            self.assertAlmostEqual(  0.  , linear.distributions[2].pdf.energies[0] )
            self.assertAlmostEqual(  4.  , linear.distributions[2].pdf.energies[1] )
            self.assertAlmostEqual(  0.  , linear.distributions[3].pdf.energies[0] )
            self.assertAlmostEqual(  4.  , linear.distributions[3].pdf.energies[1] )
            self.assertAlmostEqual(  0.5  / normalisation, linear.distributions[0].pdf.values[0] )
            self.assertAlmostEqual(  0.5  / normalisation, linear.distributions[0].pdf.values[1] )
            self.assertAlmostEqual(  0.52 / normalisation, linear.distributions[1].pdf.values[0] )
            self.assertAlmostEqual(  0.48 / normalisation, linear.distributions[1].pdf.values[1] )
            self.assertAlmostEqual(  0.48 / normalisation, linear.distributions[2].pdf.values[0] )
            self.assertAlmostEqual(  0.52 / normalisation, linear.distributions[2].pdf.values[1] )
            self.assertAlmostEqual(  0.2  / normalisation, linear.distributions[3].pdf.values[0] )
            self.assertAlmostEqual(  0.8  / normalisation, linear.distributions[3].pdf.values[1] )
            self.assertEqual( True, linear.distributions[0].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[1].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[2].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[3].cdf.is_linearised )
            self.assertEqual( 2, len( linear.distributions[0].cdf.energies ) )
            self.assertEqual( 2, len( linear.distributions[1].cdf.energies ) )
            self.assertEqual( 2, len( linear.distributions[2].cdf.energies ) )
            self.assertEqual( 2, len( linear.distributions[3].cdf.energies ) )
            self.assertEqual( 2, len( linear.distributions[0].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[1].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[2].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[3].cdf.values ) )
            self.assertAlmostEqual(  0.  , linear.distributions[0].cdf.energies[0] )
            self.assertAlmostEqual(  4.  , linear.distributions[0].cdf.energies[1] )
            self.assertAlmostEqual(  0.  , linear.distributions[1].cdf.energies[0] )
            self.assertAlmostEqual(  4.  , linear.distributions[1].cdf.energies[1] )
            self.assertAlmostEqual(  0.  , linear.distributions[2].cdf.energies[0] )
            self.assertAlmostEqual(  4.  , linear.distributions[2].cdf.energies[1] )
            self.assertAlmostEqual(  0.  , linear.distributions[3].cdf.energies[0] )
            self.assertAlmostEqual(  4.  , linear.distributions[3].cdf.energies[1] )
            self.assertAlmostEqual(  0.0 / normalisation, linear.distributions[0].cdf.values[0] )
            self.assertAlmostEqual(  2.0 / normalisation, linear.distributions[0].cdf.values[1] )
            self.assertAlmostEqual(  0.0 / normalisation, linear.distributions[1].cdf.values[0] )
            self.assertAlmostEqual(  2.0 / normalisation, linear.distributions[1].cdf.values[1] )
            self.assertAlmostEqual(  0.0 / normalisation, linear.distributions[2].cdf.values[0] )
            self.assertAlmostEqual(  2.0 / normalisation, linear.distributions[2].cdf.values[1] )
            self.assertAlmostEqual(  0.0 / normalisation, linear.distributions[3].cdf.values[0] )
            self.assertAlmostEqual(  2.0 / normalisation, linear.distributions[3].cdf.values[1] )

            self.assertEqual( 3, linear.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

        # the data is given explicitly
        chunk1 = TabulatedEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                                distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                  TabulatedEnergyDistribution( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                                  TabulatedEnergyDistribution( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                                  TabulatedEnergyDistribution( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                                interpolant = InterpolationType.LinearLinear, normalise = False )
        chunk2 = TabulatedEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                                distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                  TabulatedEnergyDistribution( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                                  TabulatedEnergyDistribution( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                                  TabulatedEnergyDistribution( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                                interpolant = InterpolationType.LinearLinear, normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk2, True )
        verify_chunk( self, chunk2, True )

    def test_comparison( self ) :

        left = TabulatedEnergyDistributions( [ 1., 2., 3., 4. ],
                                             [ TabulatedEnergyDistribution( [ 1., 3. ], [ 0.5, 0.5 ] ),
                                               TabulatedEnergyDistribution( [ 1., 3. ], [ 0.49, 0.51 ] ),
                                               TabulatedEnergyDistribution( [ 1., 3. ], [ 0.4, 0.6 ] ),
                                               TabulatedEnergyDistribution( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )
        equal = TabulatedEnergyDistributions( [ 1., 2., 3., 4. ],
                                              [ TabulatedEnergyDistribution( [ 1., 3. ], [ 0.5, 0.5 ] ),
                                                TabulatedEnergyDistribution( [ 1., 3. ], [ 0.49, 0.51 ] ),
                                                TabulatedEnergyDistribution( [ 1., 3. ], [ 0.4, 0.6 ] ),
                                                TabulatedEnergyDistribution( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )
        unnormalised = TabulatedEnergyDistributions( [ 1., 2., 3., 4. ],
                                                     [ TabulatedEnergyDistribution( [ 1., 3. ], [ 1.0, 1.0 ] ),
                                                       TabulatedEnergyDistribution( [ 1., 3. ], [ 0.49, 0.51 ] ),
                                                       TabulatedEnergyDistribution( [ 1., 3. ], [ 0.4, 0.6 ] ),
                                                       TabulatedEnergyDistribution( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )
        different = TabulatedEnergyDistributions( [ 1., 4. ],
                                                  [ TabulatedEnergyDistribution( [ 1., 3. ], [ 1.0, 1.0 ] ),
                                                    TabulatedEnergyDistribution( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )

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

        # there are not enough values in the x or f(y) grid
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [], distributions = [] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1. ],
                                                  distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [],
                                                   distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1. ], distributions = [] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                                  distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                                  distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 4. ], [ 0.1, 0.9 ] ) ],
                                                  boundaries = [ 3 ],
                                                  interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1., 3., 2., 4. ],
                                                  distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 4. ], [ 0.1, 0.9 ] ) ] )

        # the x grid contains a triple x value
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1., 2., 2., 2., 4. ],
                                                  distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 2., 4. ], [ 0.45, 0.5, 0.65 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 4. ], [ 0.1, 0.9 ] ) ] )

        # the x grid has a jump at the beginning
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1., 1., 3., 4. ],
                                                  distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 4. ], [ 0.1, 0.9 ] ) ] )

        # the x grid has a jump at the end
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1., 2., 4., 4. ],
                                                  distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 4. ], [ 0.1, 0.9 ] ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = TabulatedEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                                  distributions = [ TabulatedEnergyDistribution( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                                    TabulatedEnergyDistribution( [ 0., 4. ], [ 0.1, 0.9 ] ) ],
                                                  boundaries = [ 2 ],
                                                  interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
