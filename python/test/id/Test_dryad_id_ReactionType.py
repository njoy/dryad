# standard imports
import unittest

# third party imports

# local imports
from dryad import InteractionType
from dryad.id import ElectronSubshellID
from dryad.id import LevelID
from dryad.id import ParticleID
from dryad.id import ReactionType

class Test_elementary_ReactionType( unittest.TestCase ) :
    """Unit test for the ReactionType class."""

    def test_values( self ) :

        n = ParticleID.neutron()
        p = ParticleID.proton()
        d = ParticleID.deuteron()
        t = ParticleID.triton()
        h = ParticleID.helion()
        a = ParticleID.alpha()
        eminus = ParticleID.electron()
        eplus = ParticleID.positron()

        nuclear = InteractionType.Nuclear
        atomic = InteractionType.Atomic

        empty = []

        id = ReactionType( 1 )
        self.assertEqual( 1, id.mt )
        self.assertEqual( nuclear, id.interaction_type )
        self.assertEqual( 'total', id.symbol )
        self.assertEqual( None, id.particles )
        self.assertEqual( None, id.level )
        self.assertEqual( True, id.is_special )
        self.assertEqual( True, id.is_compatible_with_endf )
        self.assertEqual( id, ReactionType( 'total' ) )
        self.assertEqual( id, ReactionType( 'total[nuclear]' ) )

    def test_key( self ) :

        id1 = ReactionType( 50 )
        id2 = ReactionType( 600 )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ ReactionType( 50 ) ], '1' )
        self.assertEqual( map[ ReactionType( 600 ) ], '2' )

    def test_failures( self ) :

        # illegal values
        with self.assertRaises( IndexError ) : id = ReactionType( 'not a reaction type symbol' )
        with self.assertRaises( IndexError ) : id = ReactionType( -1000 )
        with self.assertRaises( IndexError ) : id = ReactionType( 2 ) # 2 has no meaning without knowing the incident particle type

if __name__ == '__main__' :

    unittest.main()