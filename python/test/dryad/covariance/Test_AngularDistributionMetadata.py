# standard imports
import unittest

# third party imports

# local imports
from njoy.dryad.covariance import AngularDistributionMetadata
from njoy.dryad.id import ReactionID
from njoy.dryad.id import EnergyGroup

class Test_AngularDistributionMetadata( unittest.TestCase ) :
    """Unit test for the AngularDistributionMetadata class."""

    def test_metadata( self ) :

        reaction1 = ReactionID( 'n,U235->n(0)' )
        reaction2 = ReactionID( 'n,U235->n(1)' )
        group1 = EnergyGroup( 1e-5, 1e+6 )
        group2 = EnergyGroup( 1e+6, 2e+7 )

        # valid metadata for a covariance matrix for product multiplicities
        chunk = AngularDistributionMetadata(
                    reactions = [ ReactionID( 'n,U235->n(0)' ), ReactionID( 'n,U235->n(1)' ) ],
                    energies = [ 1e-5, 1e+6, 2e+7 ],
                    moments = [ 1, 2, 3, 4 ] )

        # verify content
        self.assertEqual( 2, len( chunk.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n(0)' ), chunk.reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,U235->n(1)' ), chunk.reaction_identifiers[1] )

        self.assertEqual( 3, len( chunk.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.energies[0] )
        self.assertAlmostEqual( 1e+6, chunk.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.energies[2] )

        self.assertEqual( 4, len( chunk.moments ) )
        self.assertEqual( 1, chunk.moments[0] )
        self.assertEqual( 2, chunk.moments[1] )
        self.assertEqual( 3, chunk.moments[2] )
        self.assertEqual( 4, chunk.moments[3] )

        self.assertEqual( 16, len( chunk.keys ) )
        self.assertEqual( ( reaction1, 1, group1 ), chunk.keys[0] )
        self.assertEqual( ( reaction1, 1, group2 ), chunk.keys[1] )
        self.assertEqual( ( reaction1, 2, group1 ), chunk.keys[2] )
        self.assertEqual( ( reaction1, 2, group2 ), chunk.keys[3] )
        self.assertEqual( ( reaction1, 3, group1 ), chunk.keys[4] )
        self.assertEqual( ( reaction1, 3, group2 ), chunk.keys[5] )
        self.assertEqual( ( reaction1, 4, group1 ), chunk.keys[6] )
        self.assertEqual( ( reaction1, 4, group2 ), chunk.keys[7] )
        self.assertEqual( ( reaction2, 1, group1 ), chunk.keys[8] )
        self.assertEqual( ( reaction2, 1, group2 ), chunk.keys[9] )
        self.assertEqual( ( reaction2, 2, group1 ), chunk.keys[10] )
        self.assertEqual( ( reaction2, 2, group2 ), chunk.keys[11] )
        self.assertEqual( ( reaction2, 3, group1 ), chunk.keys[12] )
        self.assertEqual( ( reaction2, 3, group2 ), chunk.keys[13] )
        self.assertEqual( ( reaction2, 4, group1 ), chunk.keys[14] )
        self.assertEqual( ( reaction2, 4, group2 ), chunk.keys[15] )

        # valid keys
        chunk = AngularDistributionMetadata(
                    keys = [ ( reaction1, 1, group1 ),
                             ( reaction1, 1, group2 ),
                             ( reaction1, 2, group1 ),
                             ( reaction1, 2, group2 ),
                             ( reaction1, 3, group1 ),
                             ( reaction1, 3, group2 ),
                             ( reaction1, 4, group1 ),
                             ( reaction1, 4, group2 ),
                             ( reaction2, 1, group1 ),
                             ( reaction2, 1, group2 ),
                             ( reaction2, 2, group1 ),
                             ( reaction2, 2, group2 ),
                             ( reaction2, 3, group1 ),
                             ( reaction2, 3, group2 ),
                             ( reaction2, 4, group1 ),
                             ( reaction2, 4, group2 ) ] )

        # verify content
        self.assertEqual( 2, len( chunk.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n(0)' ), chunk.reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,U235->n(1)' ), chunk.reaction_identifiers[1] )

        self.assertEqual( 3, len( chunk.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.energies[0] )
        self.assertAlmostEqual( 1e+6, chunk.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.energies[2] )

        self.assertEqual( 4, len( chunk.moments ) )
        self.assertEqual( 1, chunk.moments[0] )
        self.assertEqual( 2, chunk.moments[1] )
        self.assertEqual( 3, chunk.moments[2] )
        self.assertEqual( 4, chunk.moments[3] )

        self.assertEqual( 16, len( chunk.keys ) )
        self.assertEqual( ( reaction1, 1, group1 ), chunk.keys[0] )
        self.assertEqual( ( reaction1, 1, group2 ), chunk.keys[1] )
        self.assertEqual( ( reaction1, 2, group1 ), chunk.keys[2] )
        self.assertEqual( ( reaction1, 2, group2 ), chunk.keys[3] )
        self.assertEqual( ( reaction1, 3, group1 ), chunk.keys[4] )
        self.assertEqual( ( reaction1, 3, group2 ), chunk.keys[5] )
        self.assertEqual( ( reaction1, 4, group1 ), chunk.keys[6] )
        self.assertEqual( ( reaction1, 4, group2 ), chunk.keys[7] )
        self.assertEqual( ( reaction2, 1, group1 ), chunk.keys[8] )
        self.assertEqual( ( reaction2, 1, group2 ), chunk.keys[9] )
        self.assertEqual( ( reaction2, 2, group1 ), chunk.keys[10] )
        self.assertEqual( ( reaction2, 2, group2 ), chunk.keys[11] )
        self.assertEqual( ( reaction2, 3, group1 ), chunk.keys[12] )
        self.assertEqual( ( reaction2, 3, group2 ), chunk.keys[13] )
        self.assertEqual( ( reaction2, 4, group1 ), chunk.keys[14] )
        self.assertEqual( ( reaction2, 4, group2 ), chunk.keys[15] )

if __name__ == '__main__' :

    unittest.main()
