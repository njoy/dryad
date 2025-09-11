# standard imports
import unittest

# third party imports

# local imports
from dryad.id import EnergyGroup

class Test_elementary_EnergyGroup( unittest.TestCase ) :
    """Unit test for the Level class."""

    def test_values( self ) :

        id = EnergyGroup( 1e-5, 100. )
        self.assertAlmostEqual( 1e-5, id.lower_energy )
        self.assertAlmostEqual( 100., id.upper_energy )

    def test_comparison( self ) :

        id1 = EnergyGroup( 1e-5, 100. )
        id2 = EnergyGroup( 1e-5, 2e+7 )

        self.assertEqual( id1 <  id1, False )
        self.assertEqual( id1 <= id1, True )
        self.assertEqual( id1 >  id1, False )
        self.assertEqual( id1 >= id1, True )
        self.assertEqual( id1 == id1, True )
        self.assertEqual( id1 != id1, False )
        self.assertEqual( id1 <  id2, True )
        self.assertEqual( id1 <= id2, True )
        self.assertEqual( id1 >  id2, False )
        self.assertEqual( id1 >= id2, False )
        self.assertEqual( id1 == id2, False )
        self.assertEqual( id1 != id2, True )
        self.assertEqual( id2 <  id1, False )
        self.assertEqual( id2 <= id1, False )
        self.assertEqual( id2 >  id1, True )
        self.assertEqual( id2 >= id1, True )
        self.assertEqual( id2 == id1, False )
        self.assertEqual( id2 != id1, True )

    def test_key( self ) :

        id1 = EnergyGroup( 1e-5, 100. )
        id2 = EnergyGroup( 1e-5, 1e-7 )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ EnergyGroup( 1e-5, 100. ) ], '1' )
        self.assertEqual( map[ EnergyGroup( 1e-5, 1e-7 ) ], '2' )

if __name__ == '__main__' :

    unittest.main()