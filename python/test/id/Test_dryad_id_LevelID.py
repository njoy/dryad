# standard imports
import unittest

# third party imports

# local imports
from dryad.id import LevelID

class Test_elementary_LevelID( unittest.TestCase ) :
    """Unit test for the Level class."""

    def test_values( self ) :

        id = LevelID( 0 )
        self.assertEqual( 0, id.number )
        self.assertEqual( '', id.symbol )

        id = LevelID( '_e0' )
        self.assertEqual( 0, id.number )
        self.assertEqual( '', id.symbol )

        id = LevelID( 1 )
        self.assertEqual( 1, id.number )
        self.assertEqual( '_e1', id.symbol )

        id = LevelID( '_e1' )
        self.assertEqual( 1, id.number )
        self.assertEqual( '_e1', id.symbol )

        continuum = LevelID.continuum

        id = LevelID( continuum )
        self.assertEqual( continuum, id.number )
        self.assertEqual( '[continuum]', id.symbol )

        id = LevelID( '[continuum]' )
        self.assertEqual( continuum, id.number )
        self.assertEqual( '[continuum]', id.symbol )

        all = LevelID.all

        id = LevelID( all )
        self.assertEqual( all, id.number )
        self.assertEqual( '[all]', id.symbol )

        id = LevelID( '[all]' )
        self.assertEqual( all, id.number )
        self.assertEqual( '[all]', id.symbol )

    def test_comparison( self ) :

        id1 = LevelID( 0 )
        id2 = LevelID( 1 )

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

        id1 = LevelID( 0 )
        id2 = LevelID( 1 )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ LevelID( 0 ) ], '1' )
        self.assertEqual( map[ LevelID( 1 ) ], '2' )

    def test_failures( self ) :

        # illegal values
        with self.assertRaises( IndexError ) : id = LevelID( 'not a valid level number' )
        with self.assertRaises( IndexError ) : id = LevelID( -1 )
        with self.assertRaises( IndexError ) : id = LevelID( 152 )

if __name__ == '__main__' :

    unittest.main()