# standard imports
import unittest

# third party imports

# local imports
from dryad.id import ReactionID
from dryad.id import ReactionType
from dryad.id import ParticleID
from dryad.covariance import LinearCombinationCovariance

class Test_dryad_covariance_LinearCombinationCovariance( unittest.TestCase ) :
    """Unit test for the LinearCombinationCovariance class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
            self.assertAlmostEqual( 2e+7, chunk.upper_energy_limit )
            self.assertEqual( 3, chunk.number_reactions )
            self.assertEqual( 3, len( chunk.reactions ) )
            self.assertEqual( 3, len( chunk.coefficients ) )
            self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.reactions[0] )
            self.assertEqual( ReactionID( 'n,U235->n,U235[all]' ), chunk.reactions[1] )
            self.assertEqual( ReactionID( 'n,U235->2n,U234[all]' ), chunk.reactions[2] )
            self.assertAlmostEqual(  0.1, chunk.coefficients[0] )
            self.assertAlmostEqual(  0.2, chunk.coefficients[1] )
            self.assertAlmostEqual(  0.3, chunk.coefficients[2] )

        n = ParticleID.neutron()
        u235 = ParticleID( 92235 )

        ReactionID( n, u235, ReactionType.elastic( n ) )
        ReactionID( n, u235, ReactionType( n, 4 ) )
        ReactionID( n, u235, ReactionType( n, 16 ) )

        # the data is given explicitly
        chunk = LinearCombinationCovariance( lower = 1e-5, upper = 2e+7,
                                             reactions = [ ReactionID( 'n,U235->n,U235' ),
                                                           ReactionID( 'n,U235->n,U235[all]' ),
                                                           ReactionID( 'n,U235->2n,U234[all]' ) ],
                                             coefficients = [ 0.1, 0.2, 0.3 ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        n = ParticleID.neutron()
        u235 = ParticleID( 92235 )

        ReactionID( n, u235, ReactionType.elastic( n ) )
        ReactionID( n, u235, ReactionType( n, 4 ) )
        ReactionID( n, u235, ReactionType( n, 16 ) )

        # the number of reactions and coefficients is not consistent or both are zero
        with self.assertRaises( Exception ) :

            chunk = LinearCombinationCovariance( lower = 1e-5, upper = 2e+7,
                                                 reactions = [],
                                                 coefficients = [ 0.1, 0.2, 0.3 ] )

        with self.assertRaises( Exception ) :

            chunk = LinearCombinationCovariance( lower = 1e-5, upper = 2e+7,
                                                 reactions = [ ReactionID( 'n,U235->n,U235' ),
                                                               ReactionID( 'n,U235->n,U235[all]' ),
                                                               ReactionID( 'n,U235->2n,U234[all]' ) ],
                                                 coefficients = [] )

        with self.assertRaises( Exception ) :

            chunk = LinearCombinationCovariance( lower = 1e-5, upper = 2e+7,
                                                 reactions = [],
                                                 coefficients = [] )

if __name__ == '__main__' :

    unittest.main()
