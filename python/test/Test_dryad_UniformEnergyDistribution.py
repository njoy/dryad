# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import UniformEnergyDistribution
from dryad import UniformDistributionType

class Test_dryad_UniformEnergyDistribution( unittest.TestCase ) :
    """Unit test for the UniformEnergyDistribution class."""

    def test_component( self ) :

        def verify_discrete_chunk( self, chunk ) :

            # verify content
            self.assertEqual( UniformDistributionType.Discrete, chunk.type )
            self.assertEqual( 3, chunk.number_energies )

            self.assertAlmostEqual(  2., chunk.energies[0] )
            self.assertAlmostEqual(  3., chunk.energies[1] )
            self.assertAlmostEqual( 10., chunk.energies[2] )

            # the average energy can be calculated
            self.assertAlmostEqual( 5., chunk.average_energy )

        def verify_interval_chunk( self, chunk ) :

            # verify content
            self.assertEqual( UniformDistributionType.Interval, chunk.type )
            self.assertEqual( 4, chunk.number_energies )

            self.assertAlmostEqual(  0., chunk.energies[0] )
            self.assertAlmostEqual(  1., chunk.energies[1] )
            self.assertAlmostEqual(  4., chunk.energies[2] )
            self.assertAlmostEqual(  8., chunk.energies[3] )
            self.assertAlmostEqual( 10., chunk.energies[4] )

            # the average energy can be calculated
            self.assertAlmostEqual( 4.5, chunk.average_energy )

        # the data is given explicitly for a discrete energy distribution
        chunk = UniformEnergyDistribution( energies = [ 2., 3., 10. ], type = UniformDistributionType.Discrete )

        verify_discrete_chunk( self, chunk )

        # the data is given explicitly for an equally probable energy bin distribution
        chunk = UniformEnergyDistribution( energies = [ 0., 1., 4., 8., 10. ], type = UniformDistributionType.Interval )

        verify_interval_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # empty energies for a discrete distribution
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistribution( energies = [], type = UniformDistributionType.Discrete )

        # no or one energy for an interval distribution
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistribution( energies = [], type = UniformDistributionType.Interval )

        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistribution( energies = [ 1. ], type = UniformDistributionType.Interval )

if __name__ == '__main__' :

    unittest.main()
