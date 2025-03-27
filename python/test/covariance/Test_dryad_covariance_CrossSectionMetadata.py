# standard imports
import unittest

# third party imports

# local imports
from dryad.covariance import CrossSectionMetadata

class Test_dryad_covariance_CrossSectionMetadata( unittest.TestCase ) :
    """Unit test for the CrossSectionMetadata class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 'n', chunk.projectile_identifier )
            self.assertEqual( 'U235', chunk.target_identifier )
            self.assertEqual( '2', chunk.reaction_identifier )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 3, chunk.number_groups )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 1.  , chunk.energies[1] )
            self.assertAlmostEqual( 1e+6, chunk.energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.energies[3] )

        # the data is given explicitly
        chunk = CrossSectionMetadata( projectile = 'n', target = 'U235', reaction = '2',
                                      energies = [ 1e-5, 1., 1e+6, 2e+7 ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the energy grid does not have at least 2 elements
        with self.assertRaises( Exception ) :

            chunk = CrossSectionMetadata( projectile = 'n', target = 'U235', reaction = '2',
                                          energies = [ 1e-5 ] )

        # the energy grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = CrossSectionMetadata( projectile = 'n', target = 'U235', reaction = '2',
                                          energies = [ 2e+7, 1e+6, 1., 1e-5 ] )

        # the energy grid has duplicate points
        with self.assertRaises( Exception ) :

            chunk = CrossSectionMetadata( projectile = 'n', target = 'U235', reaction = '2',
                                          energies = [ 1e-5, 1., 1., 2e+7 ] )

if __name__ == '__main__' :

    unittest.main()
