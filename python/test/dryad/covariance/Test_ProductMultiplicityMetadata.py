# standard imports
import unittest

# third party imports

# local imports
import numpy
from njoy.dryad.covariance import ProductMultiplicityMetadata
from njoy.dryad.id import ParticleID
from njoy.dryad.id import ReactionID
from njoy.dryad.id import EnergyGroup

class Test_ProductMultiplicityMetadata( unittest.TestCase ) :
    """Unit test for the ProductMultiplicityMetadata class."""

    def test_metadata( self ) :

        reaction1 = ReactionID( 'n,U235->n,U235_e0' )
        reaction2 = ReactionID( 'n,U235->2n,U234[all]' )
        group1 = EnergyGroup( 1e-5, 1e+6 )
        group2 = EnergyGroup( 1e+6, 2e+7 )
        product1 = ParticleID( 'Y99' )
        product2 = ParticleID( 'Mo99' )
        product3 = ParticleID( 'Pr148' )
        product4 = ParticleID( 'Pr148_e1' )

        # valid metadata for a covariance matrix for product multiplicities
        chunk = ProductMultiplicityMetadata(
                    reactions = [ ReactionID( 'n,U235->n,U235_e0' ), ReactionID( 'n,U235->2n,U234[all]' ) ],
                    energies = [ 1e-5, 1e+6, 2e+7 ],
                    products = [ ParticleID( 'Y99' ), ParticleID( 'Mo99' ),
                                 ParticleID( 'Pr148' ), ParticleID( 'Pr148_e1' ) ] )

        # verify content
        self.assertEqual( 2, len( chunk.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n,U235_e0' ), chunk.reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,U235->2n,U234[all]' ), chunk.reaction_identifiers[1] )

        self.assertEqual( 3, len( chunk.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.energies[0] )
        self.assertAlmostEqual( 1e+6, chunk.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.energies[2] )

        self.assertEqual( 4, len( chunk.product_identifiers ) )
        self.assertEqual( ParticleID( 'Y99' ), chunk.product_identifiers[0] )
        self.assertEqual( ParticleID( 'Mo99' ), chunk.product_identifiers[1] )
        self.assertEqual( ParticleID( 'Pr148' ), chunk.product_identifiers[2] )
        self.assertEqual( ParticleID( 'Pr148_e1' ), chunk.product_identifiers[3] )

        self.assertEqual( 16, len( chunk.keys ) )
        self.assertEqual( ( reaction1, group1, product1 ), chunk.keys[0] )
        self.assertEqual( ( reaction1, group1, product2 ), chunk.keys[1] )
        self.assertEqual( ( reaction1, group1, product3 ), chunk.keys[2] )
        self.assertEqual( ( reaction1, group1, product4 ), chunk.keys[3] )
        self.assertEqual( ( reaction1, group2, product1 ), chunk.keys[4] )
        self.assertEqual( ( reaction1, group2, product2 ), chunk.keys[5] )
        self.assertEqual( ( reaction1, group2, product3 ), chunk.keys[6] )
        self.assertEqual( ( reaction1, group2, product4 ), chunk.keys[7] )
        self.assertEqual( ( reaction2, group1, product1 ), chunk.keys[8] )
        self.assertEqual( ( reaction2, group1, product2 ), chunk.keys[9] )
        self.assertEqual( ( reaction2, group1, product3 ), chunk.keys[10] )
        self.assertEqual( ( reaction2, group1, product4 ), chunk.keys[11] )
        self.assertEqual( ( reaction2, group2, product1 ), chunk.keys[12] )
        self.assertEqual( ( reaction2, group2, product2 ), chunk.keys[13] )
        self.assertEqual( ( reaction2, group2, product3 ), chunk.keys[14] )
        self.assertEqual( ( reaction2, group2, product4 ), chunk.keys[15] )

        # valid keys
        chunk = ProductMultiplicityMetadata(
                    keys = [ ( reaction1, group1, product1 ),
                             ( reaction1, group1, product2 ),
                             ( reaction1, group1, product3 ),
                             ( reaction1, group1, product4 ),
                             ( reaction1, group2, product1 ),
                             ( reaction1, group2, product2 ),
                             ( reaction1, group2, product3 ),
                             ( reaction1, group2, product4 ),
                             ( reaction2, group1, product1 ),
                             ( reaction2, group1, product2 ),
                             ( reaction2, group1, product3 ),
                             ( reaction2, group1, product4 ),
                             ( reaction2, group2, product1 ),
                             ( reaction2, group2, product2 ),
                             ( reaction2, group2, product3 ),
                             ( reaction2, group2, product4 ) ] )

        # verify content
        self.assertEqual( 2, len( chunk.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n,U235_e0' ), chunk.reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,U235->2n,U234[all]' ), chunk.reaction_identifiers[1] )

        self.assertEqual( 3, len( chunk.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.energies[0] )
        self.assertAlmostEqual( 1e+6, chunk.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.energies[2] )

        self.assertEqual( 4, len( chunk.product_identifiers ) )
        self.assertEqual( ParticleID( 'Y99' ), chunk.product_identifiers[0] )
        self.assertEqual( ParticleID( 'Mo99' ), chunk.product_identifiers[1] )
        self.assertEqual( ParticleID( 'Pr148' ), chunk.product_identifiers[2] )
        self.assertEqual( ParticleID( 'Pr148_e1' ), chunk.product_identifiers[3] )

        self.assertEqual( 16, len( chunk.keys ) )
        self.assertEqual( ( reaction1, group1, product1 ), chunk.keys[0] )
        self.assertEqual( ( reaction1, group1, product2 ), chunk.keys[1] )
        self.assertEqual( ( reaction1, group1, product3 ), chunk.keys[2] )
        self.assertEqual( ( reaction1, group1, product4 ), chunk.keys[3] )
        self.assertEqual( ( reaction1, group2, product1 ), chunk.keys[4] )
        self.assertEqual( ( reaction1, group2, product2 ), chunk.keys[5] )
        self.assertEqual( ( reaction1, group2, product3 ), chunk.keys[6] )
        self.assertEqual( ( reaction1, group2, product4 ), chunk.keys[7] )
        self.assertEqual( ( reaction2, group1, product1 ), chunk.keys[8] )
        self.assertEqual( ( reaction2, group1, product2 ), chunk.keys[9] )
        self.assertEqual( ( reaction2, group1, product3 ), chunk.keys[10] )
        self.assertEqual( ( reaction2, group1, product4 ), chunk.keys[11] )
        self.assertEqual( ( reaction2, group2, product1 ), chunk.keys[12] )
        self.assertEqual( ( reaction2, group2, product2 ), chunk.keys[13] )
        self.assertEqual( ( reaction2, group2, product3 ), chunk.keys[14] )
        self.assertEqual( ( reaction2, group2, product4 ), chunk.keys[15] )

if __name__ == '__main__' :

    unittest.main()
