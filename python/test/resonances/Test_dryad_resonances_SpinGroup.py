# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.resonances import Particle
from dryad.resonances import ParticlePair
from dryad.resonances import ChannelRadii
from dryad.resonances import Channel
from dryad.resonances import ResonanceTable
from dryad.resonances import SpinGroup
from dryad.id import ChannelID
from dryad.id import ParticleID
from dryad.id import ReactionID

def verify_chunk( self, chunk ) :

    # identifiers
    elasticID = ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' )
    inelasticID = ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' )
    captureID = ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' )
    protonID = ChannelID( 'n,Cl35->p,S35{0,1,1+}' )

    # particles
    g = Particle( ParticleID.photon(), 0, 1, +1 )
    n = Particle( ParticleID.neutron(), 1.00866491574, 0.5, +1 )
    p = Particle( ParticleID.proton(), 1.00727646662, 0.5, +1 )
    cl36 = Particle( ParticleID( 'Cl36' ), 35.9683050031, 0, +1 )
    cl35 = Particle( ParticleID( 'Cl35' ), 34.9688491981, 1.5, +1 )
    cl35_e1 = Particle( ParticleID( 'Cl35_e1' ), 34.9688491981, 1.5, +1 )
    s35 = Particle( ParticleID( 'S35' ), 34.9690307578, 1.5, +1 )

    # particle pairs
    elasticPair = ParticlePair( n, cl35 )
    inelasticPair = ParticlePair( n, cl35_e1 )
    capturePair = ParticlePair( g, cl36 )
    protonPair = ParticlePair( p, s35 )

    # Q values
    elasticQ = 0.0
    inelasticQ = -1.219440e+6
    captureQ = 0.0
    protonQ = 6.150729e+5

    # boundary conditions
    elasticBoundary = None
    inelasticBoundary = None
    captureBoundary = None
    protonBoundary = None

    # channel radii
    elasticRadii = ChannelRadii( 4.822220, 3.667980 )
    inelasticRadii = ChannelRadii( 4.822220, 3.667980 )
    captureRadii = ChannelRadii( 0. )
    protonRadii = ChannelRadii( 4.822220, 3.667980 )

    # channels
    capture = Channel( captureID, elasticPair, capturePair,
                       captureQ, captureBoundary, captureRadii )
    elastic = Channel( elasticID, elasticPair, elasticPair,
                       elasticQ, elasticBoundary, elasticRadii )
    inelastic = Channel( inelasticID, elasticPair, inelasticPair,
                         inelasticQ, inelasticBoundary, inelasticRadii )
    proton = Channel( protonID, elasticPair, protonPair,
                     protonQ, protonBoundary, protonRadii )

    # resonance tables
    table = ResonanceTable( [ ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                              ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' ),
                              ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                              ChannelID( 'n,Cl35->p,S35{0,1,1+}' ) ],
                            [ 1., 2., 3., 4. ],
                            [ [ 11., 12., 13., 14. ],
                              [ 21., 22., 23., 24. ],
                              [ 31., 32., 33., 34. ],
                              [ 41., 42., 43., 44. ] ] )

    self.assertEqual( 1, chunk.total_angular_momentum )
    self.assertEqual( +1, chunk.parity )

    self.assertEqual( 4, len( chunk.reactions ) )
    self.assertEqual( ReactionID( 'n,Cl35->g,Cl36[all]' ), chunk.reactions[0] )
    self.assertEqual( ReactionID( 'n,Cl35->n,Cl35' ), chunk.reactions[1] )
    self.assertEqual( ReactionID( 'n,Cl35->n,Cl35_e1' ), chunk.reactions[2] )
    self.assertEqual( ReactionID( 'n,Cl35->p,S35' ), chunk.reactions[3] )

    self.assertEqual( capture, chunk.channels[0] )
    self.assertEqual( elastic, chunk.channels[1] )
    self.assertEqual( inelastic, chunk.channels[2] )
    self.assertEqual( proton, chunk.channels[3] )

    self.assertEqual( table, chunk.resonance_table )

class Test_dryad_resonances_ResonanceTable( unittest.TestCase ) :
    """Unit test for the ResonanceTable class."""

    def test_component( self ) :

        # identifiers
        elasticID = ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' )
        inelasticID = ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' )
        captureID = ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' )
        protonID = ChannelID( 'n,Cl35->p,S35{0,1,1+}' )

        # particles
        g = Particle( ParticleID.photon(), 0, 1, +1 )
        n = Particle( ParticleID.neutron(), 1.00866491574, 0.5, +1 )
        p = Particle( ParticleID.proton(), 1.00727646662, 0.5, +1 )
        cl36 = Particle( ParticleID( 'Cl36' ), 35.9683050031, 0, +1 )
        cl35 = Particle( ParticleID( 'Cl35' ), 34.9688491981, 1.5, +1 )
        cl35_e1 = Particle( ParticleID( 'Cl35_e1' ), 34.9688491981, 1.5, +1 )
        s35 = Particle( ParticleID( 'S35' ), 34.9690307578, 1.5, +1 )

        # particle pairs
        elasticPair = ParticlePair( n, cl35 )
        inelasticPair = ParticlePair( n, cl35_e1 )
        capturePair = ParticlePair( g, cl36 )
        protonPair = ParticlePair( p, s35 )

        # Q values
        elasticQ = 0.0
        inelasticQ = -1.219440e+6
        captureQ = 0.0
        protonQ = 6.150729e+5

        # boundary conditions
        elasticBoundary = None
        inelasticBoundary = None
        captureBoundary = None
        protonBoundary = None

        # channel radii
        elasticRadii = ChannelRadii( 4.822220, 3.667980 )
        inelasticRadii = ChannelRadii( 4.822220, 3.667980 )
        captureRadii = ChannelRadii( 0. )
        protonRadii = ChannelRadii( 4.822220, 3.667980 )

        # channels
        capture = Channel( captureID, elasticPair, capturePair,
                           captureQ, captureBoundary, captureRadii )
        elastic = Channel( elasticID, elasticPair, elasticPair,
                           elasticQ, elasticBoundary, elasticRadii )
        inelastic = Channel( inelasticID, elasticPair, inelasticPair,
                             inelasticQ, inelasticBoundary, inelasticRadii )
        proton = Channel( protonID, elasticPair, protonPair,
                         protonQ, protonBoundary, protonRadii )

        # resonance tables
        table = ResonanceTable( [ ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                  ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' ),
                                  ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                  ChannelID( 'n,Cl35->p,S35{0,1,1+}' ) ],
                                [ 1., 2., 3., 4. ],
                                [ [ 11., 12., 13., 14. ],
                                  [ 21., 22., 23., 24. ],
                                  [ 31., 32., 33., 34. ],
                                  [ 41., 42., 43., 44. ] ] )
        captureTable = ResonanceTable( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                       [ 1., 2., 3., 4. ],
                                       [ 11., 12., 13., 14. ] )
        elasticTable = ResonanceTable( ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' ),
                                       [ 1., 2., 3., 4. ],
                                       [ 21., 22., 23., 24. ] )
        inelasticTable = ResonanceTable( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                         [ 1., 2., 3., 4. ],
                                         [ 31., 32., 33., 34. ] )
        protonTable = ResonanceTable( ChannelID( 'n,Cl35->p,S35{0,1,1+}' ),
                                      [ 1., 2., 3., 4. ],
                                      [ 41., 42., 43., 44. ] )

        chunk = SpinGroup( [ capture, elastic, inelastic, proton ], table )

        verify_chunk( self, chunk )

        chunk = SpinGroup( [ ( capture, captureTable ), ( elastic, elasticTable ),
                             ( inelastic, inelasticTable ), ( proton, protonTable ) ] )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        # identifiers
        elasticID = ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' )
        inelasticID = ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' )
        captureID = ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' )
        protonID = ChannelID( 'n,Cl35->p,S35{0,1,1+}' )

        # particles
        g = Particle( ParticleID.photon(), 0, 1, +1 )
        n = Particle( ParticleID.neutron(), 1.00866491574, 0.5, +1 )
        p = Particle( ParticleID.proton(), 1.00727646662, 0.5, +1 )
        cl36 = Particle( ParticleID( 'Cl36' ), 35.9683050031, 0, +1 )
        cl35 = Particle( ParticleID( 'Cl35' ), 34.9688491981, 1.5, +1 )
        cl35_e1 = Particle( ParticleID( 'Cl35_e1' ), 34.9688491981, 1.5, +1 )
        s35 = Particle( ParticleID( 'S35' ), 34.9690307578, 1.5, +1 )

        # particle pairs
        elasticPair = ParticlePair( n, cl35 )
        inelasticPair = ParticlePair( n, cl35_e1 )
        capturePair = ParticlePair( g, cl36 )
        protonPair = ParticlePair( p, s35 )

        # Q values
        elasticQ = 0.0
        inelasticQ = -1.219440e+6
        captureQ = 0.0
        protonQ = 6.150729e+5

        # boundary conditions
        elasticBoundary = None
        inelasticBoundary = None
        captureBoundary = None
        protonBoundary = None

        # channel radii
        elasticRadii = ChannelRadii( 4.822220, 3.667980 )
        inelasticRadii = ChannelRadii( 4.822220, 3.667980 )
        captureRadii = ChannelRadii( 0. )
        protonRadii = ChannelRadii( 4.822220, 3.667980 )

        # channels
        capture = Channel( captureID, elasticPair, capturePair,
                           captureQ, captureBoundary, captureRadii )
        elastic = Channel( elasticID, elasticPair, elasticPair,
                           elasticQ, elasticBoundary, elasticRadii )
        inelastic = Channel( inelasticID, elasticPair, inelasticPair,
                             inelasticQ, inelasticBoundary, inelasticRadii )
        proton = Channel( protonID, elasticPair, protonPair,
                         protonQ, protonBoundary, protonRadii )

        # resonance tables
        table1 = ResonanceTable( [ ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                   ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' ),
                                   ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                   ChannelID( 'n,Cl35->p,S35{0,1,1+}' ) ],
                                 [ 1., 2., 3., 4. ],
                                 [ [ 11., 12., 13., 14. ],
                                   [ 21., 22., 23., 24. ],
                                   [ 31., 32., 33., 34. ],
                                   [ 41., 42., 43., 44. ] ] )
        table2 = ResonanceTable( [ ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                   ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                   ChannelID( 'n,Cl35->p,S35{0,1,1+}' ) ],
                                 [ 1., 2., 3., 4. ],
                                 [ [ 11., 12., 13., 14. ],
                                   [ 31., 32., 33., 34. ],
                                   [ 41., 42., 43., 44. ] ] )


        left = SpinGroup( [ capture, elastic, inelastic, proton ], table1 )
        equal = SpinGroup( [ capture, elastic, inelastic, proton ], table1 )
        different = SpinGroup( [ capture, elastic, inelastic ], table2 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
