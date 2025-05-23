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
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'photon' )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'gamma' )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.photon()
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'x-ray' )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'e-' )
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( -1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( -1000, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'electron' )
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( -1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( -1000, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.electron()
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( -1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( -1000, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'e+' )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'positron' )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'beta+' )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'e-_anti' )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.positron()
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'n' )
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'neutron' )
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.neutron()
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'p' )
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'proton' )
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.proton()
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'd' )
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'deuteron' )
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.deuteron()
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 't' )
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1003, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'triton' )
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1003, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.triton()
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1003, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'h' )
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2003, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'helion' )
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2003, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.helion()
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2003, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'a' )
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 4, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2004, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID( 'alpha' )
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 4, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2004, id.za )
        self.assertEqual( None, id.subshell )

        id = ParticleID.alpha()
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 4, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2004, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size, ParticleID.size() )     # no additional identifiers

        id = ParticleID( 1001 )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 1, ParticleID.size() ) # registering H1 using integers

        id = ParticleID( 1001, 0 )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1' )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1_e0' )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1_e10' )
        self.assertEqual( 'H1_e10', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 2, ParticleID.size() ) # registering H1_e10 using a string

        id = ParticleID( 1001, 10 )
        self.assertEqual( 'H1_e10', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 2, ParticleID.size() ) # H1_e10 already registered

        id = ParticleID( 1001, LevelID.continuum )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 3, ParticleID.size() ) # registering H1[continuum] using integers

        id = ParticleID( 'H1[continuum]' )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H1_e150' )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H2[continuum]' )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 4, ParticleID.size() ) # registering H1[continuum] using a string

        id = ParticleID( 1002, LevelID.continuum )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 4, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H2_e150' )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 4, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 1001, LevelID.all )
        self.assertEqual( 'H1[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 5, ParticleID.size() ) # registering H1[continuum] using integers

        id = ParticleID( 'H1[all]' )
        self.assertEqual( 'H1[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 5, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H1_e151' )
        self.assertEqual( 'H1[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1001, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 5, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H2[all]' )
        self.assertEqual( 'H2[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 6, ParticleID.size() ) # registering H1[continuum] using a string

        id = ParticleID( 1002, LevelID.all )
        self.assertEqual( 'H2[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 6, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H2_e151' )
        self.assertEqual( 'H2[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1002, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 6, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 92236, 10 )
        self.assertEqual( 'U236_e10', id.symbol )
        self.assertEqual( 92, id.z )
        self.assertEqual( 236, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 92236, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 7, ParticleID.size() ) # registering U235_e10 using a string

        id = ParticleID( 'U236_e10' )
        self.assertEqual( 'U236_e10', id.symbol )
        self.assertEqual( 92, id.z )
        self.assertEqual( 236, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 92236, id.za )
        self.assertEqual( None, id.subshell )

        self.assertEqual( size + 7, ParticleID.size() ) # U235_e10 already registered

        id = ParticleID( 1000, ElectronSubshellID.K )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 8, ParticleID.size() ) # registering H{1s1/2} using integers

        id = ParticleID( 'H{1s1/2}' )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 8, ParticleID.size() ) # H{1s1/2} already registered

        id = ParticleID( 'H{K}' )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 8, ParticleID.size() ) # H{1s1/2} already registered

        id = ParticleID( 'He{1s1/2}' )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2000, id.za )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 9, ParticleID.size() ) # registering He{1s1/2} using a string

        id = ParticleID( 'He{K}' )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2000, id.za )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 9, ParticleID.size() ) # He{1s1/2} already registered

        id = ParticleID( 2000, ElectronSubshellID.K )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2000, id.za )
        self.assertEqual( ElectronSubshellID.K, id.subshell.number )

        self.assertEqual( size + 9, ParticleID.size() ) # He{1s1/2} already registered

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
        with self.assertRaises( IndexError ) : id = ParticleID( 'not a valid particle identifier' )
        with self.assertRaises( IndexError ) : id = ParticleID( -1000 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 1 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, LevelID.continuum )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, LevelID.all )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 152 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1001, -1 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1001, 152 )
        with self.assertRaises( IndexError ) : id = ParticleID( 'H_e0' )
        with self.assertRaises( IndexError ) : id = ParticleID( 'H_e1' )
        with self.assertRaises( IndexError ) : id = ParticleID( 'H1_e152' )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 533 )
        with self.assertRaises( IndexError ) : id = ParticleID( 1000, 583 )

if __name__ == '__main__' :

    unittest.main()