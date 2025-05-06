# standard imports
import unittest

# third party imports

# local imports
from dryad.id import ElectronSubshellID
from dryad.id import ElementID
from dryad.id import LevelID
from dryad.id import ParticleID

class Test_elementary_ParticleID( unittest.TestCase ) :
    """Unit test for the Level class."""

    def test_values( self ) :

        size = ParticleID.size()

        id = ParticleID( 'g' )
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'photon' )
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'gamma' )
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.photon()
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'x-ray' )
        self.assertEqual( 0, id.number )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'e-' )
        self.assertEqual( 1, id.number )
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'electron' )
        self.assertEqual( 1, id.number )
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.electron()
        self.assertEqual( 1, id.number )
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'e+' )
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'positron' )
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'beta+' )
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'e-_anti' )
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.positron()
        self.assertEqual( 2, id.number )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'n' )
        self.assertEqual( 10, id.number )
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'neutron' )
        self.assertEqual( 10, id.number )
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.neutron()
        self.assertEqual( 10, id.number )
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'p' )
        self.assertEqual( 1001, id.number )
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'proton' )
        self.assertEqual( 1001, id.number )
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.proton()
        self.assertEqual( 1001, id.number )
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'd' )
        self.assertEqual( 1002, id.number )
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 2, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'deuteron' )
        self.assertEqual( 1002, id.number )
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 2, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.deuteron()
        self.assertEqual( 1002, id.number )
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 2, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 't' )
        self.assertEqual( 1003, id.number )
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 3, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'triton' )
        self.assertEqual( 1003, id.number )
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 3, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.triton()
        self.assertEqual( 1003, id.number )
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 3, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'h' )
        self.assertEqual( 2003, id.number )
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 3, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'helion' )
        self.assertEqual( 2003, id.number )
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 3, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.helion()
        self.assertEqual( 2003, id.number )
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 3, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'a' )
        self.assertEqual( 2004, id.number )
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 4, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'alpha' )
        self.assertEqual( 2004, id.number )
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 4, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        id = ParticleID.alpha()
        self.assertEqual( 2004, id.number )
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 4, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size, ParticleID.size() )     # no additional identifiers

        id = ParticleID( 1001 )
        self.assertEqual( 1001000, id.number )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 1, ParticleID.size() ) # registering H1 using integers

        id = ParticleID( 1001, 0 )
        self.assertEqual( 1001000, id.number )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1' )
        self.assertEqual( 1001000, id.number )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1_e0' )
        self.assertEqual( 1001000, id.number )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1_e10' )
        self.assertEqual( 1001010, id.number )
        self.assertEqual( 'H1_e10', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 10, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 2, ParticleID.size() ) # registering H1_e10 using a string

        id = ParticleID( 1001, 10 )
        self.assertEqual( 1001010, id.number )
        self.assertEqual( 'H1_e10', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( 10, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 2, ParticleID.size() ) # H1_e10 already registered

        id = ParticleID( 1001, LevelID.continuum )
        self.assertEqual( 1001150, id.number )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( LevelID.continuum, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 3, ParticleID.size() ) # registering H1[continuum] using integers

        id = ParticleID( 'H1[continuum]' )
        self.assertEqual( 1001150, id.number )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 1, id.mass )
        self.assertEqual( LevelID.continuum, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H2[continuum]' )
        self.assertEqual( 1002150, id.number )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 2, id.mass )
        self.assertEqual( LevelID.continuum, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 4, ParticleID.size() ) # registering H1[continuum] using a string

        id = ParticleID( 1002, LevelID.continuum )
        self.assertEqual( 1002150, id.number )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 2, id.mass )
        self.assertEqual( LevelID.continuum, id.level.number )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 4, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 1000, ElectronSubshellID.K )
        self.assertEqual( 1000534, id.number )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 5, ParticleID.size() ) # registering H{1s1/2} using integers

        id = ParticleID( 'H{1s1/2}' )
        self.assertEqual( 1000534, id.number )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 5, ParticleID.size() ) # H{1s1/2} already registered

        id = ParticleID( 'H{K}' )
        self.assertEqual( 1000534, id.number )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 5, ParticleID.size() ) # H{1s1/2} already registered

        id = ParticleID( 'He{1s1/2}' )
        self.assertEqual( 2000534, id.number )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 6, ParticleID.size() ) # registering He{1s1/2} using a string

        id = ParticleID( 'He{K}' )
        self.assertEqual( 2000534, id.number )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 6, ParticleID.size() ) # He{1s1/2} already registered

        id = ParticleID( 2000, ElectronSubshellID.K )
        self.assertEqual( 2000534, id.number )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.element.number )
        self.assertEqual( 0, id.mass )
        self.assertEqual( 0, id.level.number )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 6, ParticleID.size() ) # He{1s1/2} already registered

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
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 1 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, LevelID.continuum )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 151 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1001, 151 )
        with self.assertRaises( IndexError ) : id = ParticleID( 'H_e0' )
        with self.assertRaises( IndexError ) : id = ParticleID( 'H_e1' )
        with self.assertRaises( IndexError ) : id = ParticleID( 'H1_e151' )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 533 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 581 )

if __name__ == '__main__' :

    unittest.main()