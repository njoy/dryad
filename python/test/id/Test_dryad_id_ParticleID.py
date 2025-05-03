# standard imports
import unittest

# third party imports

# local imports
from dryad.id import LevelID
from dryad.id import ParticleID

class Test_elementary_ParticleID( unittest.TestCase ) :
    """Unit test for the Level class."""

    def test_values( self ) :

        size = ParticleID.size()

        id = ParticleID( 'g' )
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )

        id = ParticleID( 'photon' )
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )

        id = ParticleID( 'gamma' )
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )

        id = ParticleID( 'x-ray' )
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )

        id = ParticleID( 'e-' )
        self.assertEqual( 1, id.number )
        self.assertEqual( 'e-', id.symbol )

        id = ParticleID( 'electron' )
        self.assertEqual( 1, id.number )
        self.assertEqual( 'e-', id.symbol )

        id = ParticleID( 'e+' )
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )

        id = ParticleID( 'positron' )
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )

        id = ParticleID( 'beta+' )
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )

        id = ParticleID( 'e-_anti' )
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )

        id = ParticleID( 'n' )
        self.assertEqual( 10, id.number )
        self.assertEqual( 'n', id.symbol )

        id = ParticleID( 'neutron' )
        self.assertEqual( 10, id.number )
        self.assertEqual( 'n', id.symbol )

        id = ParticleID( 'p' )
        self.assertEqual( 1001, id.number )
        self.assertEqual( 'p', id.symbol )

        id = ParticleID( 'proton' )
        self.assertEqual( 1001, id.number )
        self.assertEqual( 'p', id.symbol )

        id = ParticleID( 'd' )
        self.assertEqual( 1002, id.number )
        self.assertEqual( 'd', id.symbol )

        id = ParticleID( 'deuteron' )
        self.assertEqual( 1002, id.number )
        self.assertEqual( 'd', id.symbol )

        id = ParticleID( 't' )
        self.assertEqual( 1003, id.number )
        self.assertEqual( 't', id.symbol )

        id = ParticleID( 'triton' )
        self.assertEqual( 1003, id.number )
        self.assertEqual( 't', id.symbol )

        id = ParticleID( 'h' )
        self.assertEqual( 2003, id.number )
        self.assertEqual( 'h', id.symbol )

        id = ParticleID( 'helion' )
        self.assertEqual( 2003, id.number )
        self.assertEqual( 'h', id.symbol )

        id = ParticleID( 'a' )
        self.assertEqual( 2004, id.number )
        self.assertEqual( 'a', id.symbol )

        id = ParticleID( 'alpha' )
        self.assertEqual( 2004, id.number )
        self.assertEqual( 'a', id.symbol )

        self.assertEqual( size, ParticleID.size() )     # no additional identifiers

        id = ParticleID( 1001 )
        self.assertEqual( 1001000, id.number )
        self.assertEqual( 'H1', id.symbol )

        self.assertEqual( size + 1, ParticleID.size() ) # registering H1

        id = ParticleID( 1001, 0 )
        self.assertEqual( 1001000, id.number )
        self.assertEqual( 'H1', id.symbol )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1' )
        self.assertEqual( 1001000, id.number )
        self.assertEqual( 'H1', id.symbol )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1_e0' )
        self.assertEqual( 1001000, id.number )
        self.assertEqual( 'H1', id.symbol )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 1001, 10 )
        self.assertEqual( 1001010, id.number )
        self.assertEqual( 'H1_e10', id.symbol )

        self.assertEqual( size + 2, ParticleID.size() ) # H1_e10 already registered

        id = ParticleID( 'H1_e10' )
        self.assertEqual( 1001010, id.number )
        self.assertEqual( 'H1_e10', id.symbol )

        self.assertEqual( size + 2, ParticleID.size() ) # H1_e10 already registered

        id = ParticleID( 1001, LevelID.continuum )
        self.assertEqual( 1001150, id.number )
        self.assertEqual( 'H1[continuum]', id.symbol )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H1[continuum]' )
        self.assertEqual( 1001150, id.number )
        self.assertEqual( 'H1[continuum]', id.symbol )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] already registered

    def test_comparison( self ) :

        id1 = ParticleID( 92235 )
        id2 = ParticleID( 92235, 10 )

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

        id1 = ParticleID( 92235 )
        id2 = ParticleID( 92235, 10 )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ ParticleID( 92235 ) ], '1' )
        self.assertEqual( map[ ParticleID( 92235, 10 ) ], '2' )

    def test_failures( self ) :

        # illegal values
        with self.assertRaises( IndexError ) : id = ParticleID( 'not a valid level number' )
        with self.assertRaises( IndexError ) : id = ParticleID( -1000 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 151 )
        with self.assertRaises( IndexError ) : id = ParticleID( 'H1_e151' )

if __name__ == '__main__' :

    unittest.main()