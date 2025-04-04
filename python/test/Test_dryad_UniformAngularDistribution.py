# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import UniformAngularDistribution
from dryad import UniformDistributionType

class Test_dryad_UniformAngularDistribution( unittest.TestCase ) :
    """Unit test for the UniformAngularDistribution class."""

    def test_component( self ) :

        def verify_discrete_chunk( self, chunk ) :

            # verify content
            self.assertEqual( UniformDistributionType.Discrete, chunk.type )
            self.assertEqual( 3, chunk.number_cosines )

            self.assertAlmostEqual( -0.25, chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.55, chunk.cosines[2] )

            # the average cosine can be calculated
            self.assertAlmostEqual( 0.1, chunk.average_cosine )

        def verify_interval_chunk( self, chunk ) :

            # verify content
            self.assertEqual( UniformDistributionType.Interval, chunk.type )
            self.assertEqual( 4, chunk.number_cosines )

            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual( -0.25, chunk.cosines[1] )
            self.assertAlmostEqual(  0.  , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[3] )
            self.assertAlmostEqual(  1.  , chunk.cosines[4] )

            # the average cosine can be calculated
            self.assertAlmostEqual( 0.0625, chunk.average_cosine )

        # the data is given explicitly for a discrete cosine distribution
        chunk = UniformAngularDistribution( cosines = [ -0.25, 0., 0.55 ], type = UniformDistributionType.Discrete )

        verify_discrete_chunk( self, chunk )

        # the data is given explicitly for equally probable cosine bin distribution
        chunk = UniformAngularDistribution( cosines = [ -1., -0.25, 0., 0.5, 1.0 ], type = UniformDistributionType.Interval )

        verify_interval_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # empty cosines for a discrete distribution
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistribution( cosines = [], type = UniformDistributionType.Discrete )

        # no or one cosine for an interval distribution
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistribution( cosines = [], type = UniformDistributionType.Interval )

        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistribution( cosines = [ 1. ], type = UniformDistributionType.Interval )

if __name__ == '__main__' :

    unittest.main()
