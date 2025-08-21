# standard imports
import unittest

# third party imports

# local imports
from dryad import InteractionType
from dryad.id import LevelID
from dryad.id import ParticleID
from dryad.id import ReactionType
from dryad.id import ReactionID

class Test_elementary_ReactionID( unittest.TestCase ) :
    """Unit test for the ReactionID class."""

    def test_values( self ) :

        g = ParticleID.photon()
        n = ParticleID.neutron()
        p = ParticleID.proton()
        d = ParticleID.deuteron()
        t = ParticleID.triton()
        h = ParticleID.helion()
        a = ParticleID.alpha()
        eminus = ParticleID.electron()
        eplus = ParticleID.positron()

        u = ParticleID( 92000 )
        u238 = ParticleID( 92238 )

        nuclear = InteractionType.Nuclear
        atomic = InteractionType.Atomic

        empty = {}

        id = ReactionID( n, u238, ReactionType( 1 ) )
        self.assertEqual( n, id.projectile )
        self.assertEqual( u238, id.target )
        self.assertIsNone( id.particles )
        self.assertIsNone( id.residual )
        self.assertEqual( ReactionType( 1 ), id.reaction_type )
        self.assertEqual( InteractionType.Nuclear, id.interaction_type )
        self.assertEqual( 'n,U238->total', id.symbol )
        self.assertEqual( id, ReactionID( 'n,U238->total' ) )

        id = ReactionID( n, u238, ReactionType.elastic( n ) )
        self.assertEqual( n, id.projectile )
        self.assertEqual( u238, id.target )
        self.assertEqual( { n : 1 }, id.particles )
        self.assertEqual( u238, id.residual )
        self.assertEqual( ReactionType( 50 ), id.reaction_type )
        self.assertEqual( InteractionType.Nuclear, id.interaction_type )
        self.assertEqual( 'n,U238->n,U238', id.symbol )
        self.assertEqual( id, ReactionID( 'n,U238->n,U238' ) )

        id = ReactionID( n, u238, ReactionType( 102 ) )
        self.assertEqual( n, id.projectile )
        self.assertEqual( u238, id.target )
        self.assertEqual( empty, id.particles )
        self.assertEqual( ParticleID( 92239, LevelID.all ), id.residual )
        self.assertEqual( ReactionType( 102 ), id.reaction_type )
        self.assertEqual( InteractionType.Nuclear, id.interaction_type )
        self.assertEqual( 'n,U238->g,U239[all]', id.symbol )
        self.assertEqual( id, ReactionID( 'n,U238->g,U239[all]' ) )

        id = ReactionID( n, u238, ReactionType( 199 ) )
        self.assertEqual( n, id.projectile )
        self.assertEqual( u238, id.target )
        self.assertEqual( { a : 1, p : 2, n : 3 }, id.particles )
        self.assertEqual( ParticleID( 88230, LevelID.all ), id.residual )
        self.assertEqual( ReactionType( 199 ), id.reaction_type )
        self.assertEqual( InteractionType.Nuclear, id.interaction_type )
        self.assertEqual( 'n,U238->3n,2p,a,Ra230[all]', id.symbol )
        self.assertEqual( id, ReactionID( 'n,U238->3n,2p,a,Ra230[all]' ) )

        id = ReactionID( eminus, u, ReactionType( 525 ) )
        self.assertEqual( eminus, id.projectile )
        self.assertEqual( u, id.target )
        self.assertEqual( { eminus : 1 }, id.particles )
        self.assertEqual( u, id.residual )
        self.assertEqual( ReactionType( 525 ), id.reaction_type )
        self.assertEqual( InteractionType.Atomic, id.interaction_type )
        self.assertEqual( 'e-,U->e-,U[large-angle-scattering]', id.symbol )
        self.assertEqual( id, ReactionID( 'e-,U->e-,U[large-angle-scattering]' ) )

        id = ReactionID( eminus, u, ReactionType( 526 ) )
        self.assertEqual( eminus, id.projectile )
        self.assertEqual( u, id.target )
        self.assertEqual( { eminus : 1 }, id.particles )
        self.assertEqual( u, id.residual )
        self.assertEqual( ReactionType( 526 ), id.reaction_type )
        self.assertEqual( InteractionType.Atomic, id.interaction_type )
        self.assertEqual( 'e-,U->e-,U[total-scattering]', id.symbol )
        self.assertEqual( id, ReactionID( 'e-,U->e-,U[total-scattering]' ) )

    def test_comparison( self ) :

        n = ParticleID.neutron()
        p = ParticleID.proton()
        u238 = ParticleID( 92238 )

        id1 = ReactionID( n, u238, ReactionType( n, 52 ) )
        id2 = ReactionID( p, u238, ReactionType( n, 52 ) )

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

        n = ParticleID.neutron()
        u238 = ParticleID( 92238 )
        pu239 = ParticleID( 94239 )

        id1 = ReactionID( n, u238, ReactionType( 1 ) )
        id2 = ReactionID( n, pu239, ReactionType( 18 ) )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ ReactionID( 'n,U238->total' ) ], '1' )
        self.assertEqual( map[ ReactionID( 'n,Pu239->fission(t)' ) ], '2' )

    def test_failures( self ) :

        pass

        # n = ParticleID.neutron()

        # # illegal values
        # with self.assertRaises( ValueError ) : id = ReactionType( 'not a reaction type symbol' )
        # with self.assertRaises( ValueError ) : id = ReactionType( -1000 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 2 )      # 2 has no meaning without knowing the incident particle type
        # with self.assertRaises( ValueError ) : id = ReactionType( n, 534 ) # ionisation has no meaning for particles other than photons and electrons

        # with self.assertRaises( ValueError ) : id = ReactionType( 534 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 535 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 536 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 537 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 538 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 539 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 540 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 541 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 542 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 543 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 544 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 545 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 546 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 547 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 548 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 549 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 550 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 551 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 552 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 553 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 554 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 555 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 556 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 557 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 558 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 559 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 560 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 561 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 562 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 563 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 564 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 565 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 566 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 567 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 568 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 569 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 570 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 571 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 572 )
        # with self.assertRaises( ValueError ) : id = ReactionType( 522 )

if __name__ == '__main__' :

    unittest.main()