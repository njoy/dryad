# standard imports
import unittest

# third party imports

# local imports
from njoy.dryad.id import ElectronSubshellID
from njoy.dryad.id import ElementID
from njoy.dryad.id import LevelID
from njoy.dryad.id import ParticleID

class Test_ParticleID( unittest.TestCase ) :
    """Unit test for the ParticleID class."""

    def test_values( self ) :

        size = ParticleID.size()

        id = ParticleID( 'g' )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'photon' )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'gamma' )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.photon()
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'x-ray' )
        self.assertEqual( 'g', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 0, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'e-' )
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( -1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( -1000, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'electron' )
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( -1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( -1000, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.electron()
        self.assertEqual( 'e-', id.symbol )
        self.assertEqual( -1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( -1000, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'e+' )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'positron' )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'beta+' )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'e-_anti' )
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.positron()
        self.assertEqual( 'e+', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'n' )
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'neutron' )
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.neutron()
        self.assertEqual( 'n', id.symbol )
        self.assertEqual( 0, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'p' )
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'proton' )
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.proton()
        self.assertEqual( 'p', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'd' )
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'deuteron' )
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.deuteron()
        self.assertEqual( 'd', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 't' )
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1003, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'triton' )
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1003, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.triton()
        self.assertEqual( 't', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1003, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'h' )
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2003, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'helion' )
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2003, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.helion()
        self.assertEqual( 'h', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 3, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2003, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'a' )
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 4, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2004, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID( 'alpha' )
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 4, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2004, id.za )
        self.assertIsNone( id.vacancies )

        id = ParticleID.alpha()
        self.assertEqual( 'a', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 4, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2004, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size, ParticleID.size() )     # no additional identifiers

        id = ParticleID( ElementID( 1 ), 1, LevelID( 0 ) )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 is new

        id = ParticleID.nuclide( 1001 )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID.nuclide( 1001, 0 )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1' )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1_e0' )
        self.assertEqual( 'H1', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 1, ParticleID.size() ) # H1 already registered

        id = ParticleID( 'H1_e10' )
        self.assertEqual( 'H1_e10', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 2, ParticleID.size() ) # H1_e10 is new

        id = ParticleID.nuclide( 1001, 10 )
        self.assertEqual( 'H1_e10', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 2, ParticleID.size() ) # H1_e10 already registered

        id = ParticleID( ElementID( 1 ), 1, LevelID( 10 ) )
        self.assertEqual( 'H1_e10', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 2, ParticleID.size() ) # H1_e10 already registered

        id = ParticleID( ElementID( 1 ), 1, LevelID( LevelID.continuum ) )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] is new

        id = ParticleID( 'H1[continuum]' )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID.nuclide( 1001, LevelID.continuum  )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H1_e150' )
        self.assertEqual( 'H1[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 3, ParticleID.size() ) # H1[continuum] already registered

        id = ParticleID( 'H2[continuum]' )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 4, ParticleID.size() ) # H2[continuum] is new

        id = ParticleID( ElementID( 1 ), 2, LevelID( LevelID.continuum ) )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 4, ParticleID.size() ) # H2[continuum] already registered

        id = ParticleID.nuclide( 1002, LevelID.continuum )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 4, ParticleID.size() ) # H2[continuum] already registered

        id = ParticleID( 'H2_e150' )
        self.assertEqual( 'H2[continuum]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.continuum, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 4, ParticleID.size() ) # H2[continuum] already registered

        id = ParticleID( ElementID( 1 ), 1, LevelID( LevelID.all ) )
        self.assertEqual( 'H1[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 5, ParticleID.size() ) # H1[all] is new

        id = ParticleID.nuclide( 1001, LevelID.all )
        self.assertEqual( 'H1[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 5, ParticleID.size() ) # H1[all] already registered

        id = ParticleID( 'H1[all]' )
        self.assertEqual( 'H1[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 5, ParticleID.size() ) # H1[all] already registered

        id = ParticleID( 'H1_e151' )
        self.assertEqual( 'H1[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 1, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1001, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 5, ParticleID.size() ) # H1[all] already registered

        id = ParticleID( 'H2[all]' )
        self.assertEqual( 'H2[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 6, ParticleID.size() ) # H2[all] is new

        id = ParticleID.nuclide( 1002, LevelID.all )
        self.assertEqual( 'H2[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 6, ParticleID.size() ) # H2[all] already registered

        id = ParticleID( ElementID( 1 ), 2, LevelID( LevelID.all ) )
        self.assertEqual( 'H2[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 6, ParticleID.size() ) # H2[all] already registered

        id = ParticleID( 'H2_e151' )
        self.assertEqual( 'H2[all]', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 2, id.a )
        self.assertEqual( LevelID.all, id.e )
        self.assertEqual( 1002, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 6, ParticleID.size() ) # H2[all] already registered

        id = ParticleID.nuclide( 92236, 10 )
        self.assertEqual( 'U236_e10', id.symbol )
        self.assertEqual( 92, id.z )
        self.assertEqual( 236, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 92236, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 7, ParticleID.size() ) # U235_e10 is new

        id = ParticleID( ElementID( 92 ), 236, LevelID( 10 ) )
        self.assertEqual( 'U236_e10', id.symbol )
        self.assertEqual( 92, id.z )
        self.assertEqual( 236, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 92236, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 7, ParticleID.size() ) # U235_e10 already registered

        id = ParticleID( 'U236_e10' )
        self.assertEqual( 'U236_e10', id.symbol )
        self.assertEqual( 92, id.z )
        self.assertEqual( 236, id.a )
        self.assertEqual( 10, id.e )
        self.assertEqual( 92236, id.za )
        self.assertIsNone( id.vacancies )

        self.assertEqual( size + 7, ParticleID.size() ) # U235_e10 already registered

        id = ParticleID( ElementID( 1 ), ElectronSubshellID( 'K' ) )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 8, ParticleID.size() ) # H{1s1/2} is new

        id = ParticleID( 'H{1s1/2}' )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 8, ParticleID.size() ) # H{1s1/2} already registered

        id = ParticleID( 'H{1s}' )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 8, ParticleID.size() ) # H{1s1/2} already registered

        id = ParticleID( 'H{1s+}' )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 8, ParticleID.size() ) # H{1s1/2} already registered

        id = ParticleID( 'H{K}' )
        self.assertEqual( 'H{1s1/2}', id.symbol )
        self.assertEqual( 1, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 1000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 8, ParticleID.size() ) # H{1s1/2} already registered

        id = ParticleID( 'He{1s1/2}' )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 9, ParticleID.size() ) # He{1s1/2} is new

        id = ParticleID( 'He{1s}' )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 9, ParticleID.size() ) # He{1s1/2} already registered

        id = ParticleID( 'He{1s+}' )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 9, ParticleID.size() ) # He{1s1/2} already registered

        id = ParticleID( 'He{K}' )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 9, ParticleID.size() ) # He{1s1/2} already registered

        id = ParticleID( ElementID( 2 ), ElectronSubshellID( 'K' ) )
        self.assertEqual( 'He{1s1/2}', id.symbol )
        self.assertEqual( 2, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 2000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ) ], id.vacancies )

        self.assertEqual( size + 9, ParticleID.size() ) # He{1s1/2} already registered

        id = ParticleID( ElementID( 8 ), [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ] )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} is new

        id = ParticleID( 'O{1s1/2,2s1/2}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s1/2,2s}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s1/2,2s+}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s1/2,L1}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s,2s1/2}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s,2s}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s,2s+}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s,L1}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s+,2s1/2}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s+,2s}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s+,2s+}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{1s+,L1}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{K,2s1/2}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{K,2s}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{K,2s+}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'O{K,L1}' )
        self.assertEqual( 'O{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 8, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 8000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 10, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'Fe{K,L1}' )
        self.assertEqual( 'Fe{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 26, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 26000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 11, ParticleID.size() ) # O{1s1/2,2s1/2} is new

        id = ParticleID( ElementID( 26 ), [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ] )
        self.assertEqual( 'Fe{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 26, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 26000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 11, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

        id = ParticleID( 'Fe{1s1/2,2s1/2}' )
        self.assertEqual( 'Fe{1s1/2,2s1/2}', id.symbol )
        self.assertEqual( 26, id.z )
        self.assertEqual( 0, id.a )
        self.assertEqual( 0, id.e )
        self.assertEqual( 26000, id.za )
        self.assertEqual( [ ElectronSubshellID( 'K' ), ElectronSubshellID( 'L1' ) ], id.vacancies )

        self.assertEqual( size + 11, ParticleID.size() ) # O{1s1/2,2s1/2} already registered

    def test_comparison( self ) :

        # not using hydrogen like in C++ for this test due to it causing a failure in
        # test_values because this function gets called before test_values, so H1 is
        # already registered when test_values actually runs

        fundamental = ParticleID( 'n' )
        element = ParticleID( 'Li' )
        ion = ParticleID( 'Li{1s1/2}' )
        nuclide = ParticleID( 'Li7' )
        excited = ParticleID( 'Li7_e1' )
        next = ParticleID( 'Be' )

        self.assertEqual( fundamental < element, True )
        self.assertEqual( element < ion, True )
        self.assertEqual( ion < nuclide, True )
        self.assertEqual( nuclide < excited, True )
        self.assertEqual( excited < next, True )

        id1 = ParticleID( 'U235' )
        id2 = ParticleID( 'U235_e10' )

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

        id1 = ParticleID( 'U235' )
        id2 = ParticleID( 'U235_e10' )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ ParticleID( 'U235' ) ], '1' )
        self.assertEqual( map[ ParticleID( 'U235_e10' ) ], '2' )

    def test_failures( self ) :

        # illegal values
        with self.assertRaises( ValueError ) : id = ParticleID( 'not a valid particle identifier' )
        with self.assertRaises( ValueError ) : id = ParticleID( 'H_e0' )
        with self.assertRaises( ValueError ) : id = ParticleID( 'H_e1' )
        with self.assertRaises( ValueError ) : id = ParticleID( 'H1_e152' )

if __name__ == '__main__' :

    unittest.main()