# standard imports
import unittest

# third party imports

# local imports
from njoy.dryad.covariance import CrossSectionMetadata
from njoy.dryad.id import ReactionID
from njoy.dryad.id import EnergyGroup

class Test_CrossSectionMetadata( unittest.TestCase ) :
    """Unit test for the CrossSectionMetadata class."""

    def test_metadata( self ) :

        reaction1 = ReactionID( 'n,U235->n,U235_e0' )
        reaction2 = ReactionID( 'n,U235->2n,U234[all]' )
        reaction3 = ReactionID( 'n,U235->3n,U233[all]' )
        group1 = EnergyGroup( 1e-5, 1e+6 )
        group2 = EnergyGroup( 1e+6, 2e+7 )

        # valid metadata for a covariance matrix for product multiplicities
        chunk = CrossSectionMetadata(
                    reactions = [ ReactionID( 'n,U235->n,U235_e0' ),
                                  ReactionID( 'n,U235->2n,U234[all]' ),
                                  ReactionID( 'n,U235->3n,U233[all]' ) ],
                    energies = [ 1e-5, 1e+6, 2e+7 ] )

        # verify content
        self.assertEqual( 3, len( chunk.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n,U235_e0' ), chunk.reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,U235->2n,U234[all]' ), chunk.reaction_identifiers[1] )
        self.assertEqual( ReactionID( 'n,U235->3n,U233[all]' ), chunk.reaction_identifiers[2] )

        self.assertEqual( 3, len( chunk.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.energies[0] )
        self.assertAlmostEqual( 1e+6, chunk.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.energies[2] )

        self.assertEqual( 6, len( chunk.keys ) )
        self.assertEqual( ( reaction1, group1 ), chunk.keys[0] )
        self.assertEqual( ( reaction1, group2 ), chunk.keys[1] )
        self.assertEqual( ( reaction2, group1 ), chunk.keys[2] )
        self.assertEqual( ( reaction2, group2 ), chunk.keys[3] )
        self.assertEqual( ( reaction3, group1 ), chunk.keys[4] )
        self.assertEqual( ( reaction3, group2 ), chunk.keys[5] )

        # valid keys
        chunk = CrossSectionMetadata(
                    keys = [ ( reaction1, group1 ),
                             ( reaction1, group2 ),
                             ( reaction2, group1 ),
                             ( reaction2, group2 ),
                             ( reaction3, group1 ),
                             ( reaction3, group2 ) ] )

        # verify content
        self.assertEqual( 3, len( chunk.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n,U235_e0' ), chunk.reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,U235->2n,U234[all]' ), chunk.reaction_identifiers[1] )
        self.assertEqual( ReactionID( 'n,U235->3n,U233[all]' ), chunk.reaction_identifiers[2] )

        self.assertEqual( 3, len( chunk.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.energies[0] )
        self.assertAlmostEqual( 1e+6, chunk.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.energies[2] )

        self.assertEqual( 6, len( chunk.keys ) )
        self.assertEqual( ( reaction1, group1 ), chunk.keys[0] )
        self.assertEqual( ( reaction1, group2 ), chunk.keys[1] )
        self.assertEqual( ( reaction2, group1 ), chunk.keys[2] )
        self.assertEqual( ( reaction2, group2 ), chunk.keys[3] )
        self.assertEqual( ( reaction3, group1 ), chunk.keys[4] )
        self.assertEqual( ( reaction3, group2 ), chunk.keys[5] )

if __name__ == '__main__' :

    unittest.main()
