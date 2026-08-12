# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import Particle
from njoy.dryad.resonances import ParticlePair
from njoy.dryad.resonances import ChannelRadii
from njoy.dryad.resonances import UnresolvedChannel
from njoy.dryad.resonances import UnresolvedResonanceTable
from njoy.dryad.resonances import UnresolvedSpinGroup
from njoy.dryad.resonances import UnresolvedCompoundSystem
from njoy.dryad.resonances import TabulatedAverageWidths, TabulatedLevelSpacing
from njoy.dryad.id import ChannelID
from njoy.dryad.id import ParticleID
from njoy.dryad.id import ReactionID

def make_spin_groups() :

    g = Particle( ParticleID.photon(), 0, 1, +1 )
    n = Particle( ParticleID.neutron(), 1.00866491574, 0.5, +1 )
    p = Particle( ParticleID.proton(), 1.00727646662, 0.5, +1 )
    cl36 = Particle( ParticleID( 'Cl36' ), 35.9683050031, 0, +1 )
    cl35 = Particle( ParticleID( 'Cl35' ), 34.9688491981, 1.5, +1 )
    cl35_e1 = Particle( ParticleID( 'Cl35_e1' ), 34.9688491981, 1.5, +1 )
    s35 = Particle( ParticleID( 'S35' ), 34.9690307578, 1.5, +1 )

    elastic_pair = ParticlePair( n, cl35 )
    inelastic_pair = ParticlePair( n, cl35_e1 )
    capture_pair = ParticlePair( g, cl36 )
    proton_pair = ParticlePair( p, s35 )

    elastic_q = 0.0
    inelastic_q = -1.219440e+6
    capture_q = 0.0
    proton_q = 6.150729e+5

    # channel radii
    radii = ChannelRadii( 4.822220, 3.667980 )
    capture_radii = ChannelRadii( 0. )

    energies = [ 1., 2., 3., 4. ]

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group Jpi = 1+, l = 0
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    capture = UnresolvedChannel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                 elastic_pair, capture_pair,
                                 capture_q, None, capture_radii )
    elastic = UnresolvedChannel( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                 elastic_pair, elastic_pair,
                                 elastic_q, None, radii )
    inelastic = UnresolvedChannel( ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' ),
                                   elastic_pair, inelastic_pair,
                                   inelastic_q, None, radii )
    proton = UnresolvedChannel( ChannelID( 'n,Cl35->p,S35{0,1,1+}' ),
                                elastic_pair, proton_pair,
                                proton_q, None, radii )

    table = UnresolvedResonanceTable(
                channels = [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                             ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                             ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' ),
                             ChannelID( 'n,Cl35->p,S35{0,1,1+}' ) ],
                average_widths = [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
                                   TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ),
                                   TabulatedAverageWidths( energies, [ 0.31, 0.32, 0.33, 0.34 ] ),
                                   TabulatedAverageWidths( energies, [ 0.41, 0.42, 0.43, 0.44 ] ) ],
                level_spacings = TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] ) )

    group1p = UnresolvedSpinGroup( [ capture, elastic, inelastic, proton ], table )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group Jpi = 2+, l = 0
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    capture = UnresolvedChannel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,2+}' ),
                                 elastic_pair, capture_pair,
                                 capture_q, None, capture_radii )
    elastic = UnresolvedChannel( ChannelID( 'n,Cl35->n,Cl35{0,2,2+}' ),
                                 elastic_pair, elastic_pair,
                                 elastic_q, None, radii )
    proton = UnresolvedChannel( ChannelID( 'n,Cl35->p,S35{0,2,2+}' ),
                                elastic_pair, proton_pair,
                                proton_q, None, radii )

    table = UnresolvedResonanceTable(
                channels = [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,2+}' ),
                             ChannelID( 'n,Cl35->n,Cl35{0,2,2+}' ),
                             ChannelID( 'n,Cl35->p,S35{0,2,2+}' ) ],
                average_widths = [ TabulatedAverageWidths( energies, [ 0.51, 0.52, 0.53, 0.54 ] ),
                                   TabulatedAverageWidths( energies, [ 0.61, 0.62, 0.63, 0.64 ] ),
                                   TabulatedAverageWidths( energies, [ 0.71, 0.72, 0.73, 0.74 ] ) ],
                level_spacings = TabulatedLevelSpacing( energies, [ 20., 21., 22., 23. ] ) )

    group2p = UnresolvedSpinGroup( [ capture, elastic, proton ], table )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group Jpi = 0-, l = 1
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    capture = UnresolvedChannel( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ),
                                 elastic_pair, capture_pair,
                                 capture_q, None, capture_radii )
    elastic = UnresolvedChannel( ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ),
                                 elastic_pair, elastic_pair,
                                 elastic_q, None, radii )

    table = UnresolvedResonanceTable(
                channels = [ ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ),
                             ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ) ],
                average_widths = [ TabulatedAverageWidths( energies, [ 0.81, 0.82, 0.83, 0.84 ] ),
                                   TabulatedAverageWidths( energies, [ 0.91, 0.92, 0.93, 0.94 ] ) ],
                level_spacings = TabulatedLevelSpacing( energies, [ 30., 31., 32., 33. ] ) )

    group0m = UnresolvedSpinGroup( [ capture, elastic ], table )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group Jpi = 1-, l = 1
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    capture = UnresolvedChannel( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,1-}' ),
                                 elastic_pair, capture_pair,
                                 capture_q, None, capture_radii )
    elastic = UnresolvedChannel( ChannelID( 'n,Cl35->n,Cl35{1,1,1-}' ),
                                 elastic_pair, elastic_pair,
                                 elastic_q, None, radii )
    proton = UnresolvedChannel( ChannelID( 'n,Cl35->p,S35{1,1,1-}' ),
                                elastic_pair, proton_pair,
                                proton_q, None, radii )

    table = UnresolvedResonanceTable(
                channels = [ ChannelID( 'n,Cl35->g,Cl36[all]{1,0,1-}' ),
                             ChannelID( 'n,Cl35->n,Cl35{1,1,1-}' ),
                             ChannelID( 'n,Cl35->p,S35{1,1,1-}' ) ],
                average_widths = [ TabulatedAverageWidths( energies, [ 1.11, 1.12, 1.13, 1.14 ] ),
                                   TabulatedAverageWidths( energies, [ 1.21, 1.22, 1.23, 1.24 ] ),
                                   TabulatedAverageWidths( energies, [ 1.31, 1.32, 1.33, 1.34 ] ) ],
                level_spacings = TabulatedLevelSpacing( energies, [ 40., 41., 42., 43. ] ) )

    group1m = UnresolvedSpinGroup( [ capture, elastic, proton ], table )

    return group1p, group2p, group0m, group1m

def verify_chunk( self, chunk ) :

    # * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    # content verification
    # * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
    self.assertAlmostEqual( 2e+3, chunk.upper_energy_limit )

    self.assertEqual( 4, len( chunk.reactions ) )
    self.assertEqual( ReactionID( 'n,Cl35->g,Cl36[all]' ), chunk.reactions[0] )
    self.assertEqual( ReactionID( 'n,Cl35->n,Cl35'      ), chunk.reactions[1] )
    self.assertEqual( ReactionID( 'n,Cl35->n,Cl35_e1'   ), chunk.reactions[2] )
    self.assertEqual( ReactionID( 'n,Cl35->p,S35'       ), chunk.reactions[3] )

    groups = chunk.spin_groups

    self.assertEqual( 4, len( groups ) )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 0: Jpi = 0-, l = 1
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[0]

    self.assertAlmostEqual( 0, spingroup.total_angular_momentum )
    self.assertEqual( -1, spingroup.parity )

    channels = spingroup.channels
    self.assertEqual( 2, len( channels ) )
    self.assertEqual( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ), channels[0].identifier )
    self.assertEqual( ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ), channels[1].identifier )

    self.assertEqual( 2, len( spingroup.reactions ) )
    self.assertEqual( ReactionID( 'n,Cl35->g,Cl36[all]' ), spingroup.reactions[0] )
    self.assertEqual( ReactionID( 'n,Cl35->n,Cl35'      ), spingroup.reactions[1] )

    table = spingroup.resonance_table
    self.assertEqual( 2, table.number_channels )
    self.assertAlmostEqual( 30., table.spacings.values[0] )
    self.assertAlmostEqual( 0.81, table.channel_widths( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ) ).values[0] )
    self.assertAlmostEqual( 0.91, table.channel_widths( ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ) ).values[0] )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 1: Jpi = 1-, l = 1
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[1]

    self.assertAlmostEqual( 1, spingroup.total_angular_momentum )
    self.assertEqual( -1, spingroup.parity )

    channels = spingroup.channels
    self.assertEqual( 3, len( channels ) )
    self.assertEqual( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,1-}' ), channels[0].identifier )
    self.assertEqual( ChannelID( 'n,Cl35->n,Cl35{1,1,1-}' ), channels[1].identifier )
    self.assertEqual( ChannelID( 'n,Cl35->p,S35{1,1,1-}' ), channels[2].identifier )

    table = spingroup.resonance_table
    self.assertEqual( 3, table.number_channels )
    self.assertAlmostEqual( 40., table.spacings.values[0] )
    self.assertAlmostEqual( 1.11, table.channel_widths( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,1-}' ) ).values[0] )
    self.assertAlmostEqual( 1.21, table.channel_widths( ChannelID( 'n,Cl35->n,Cl35{1,1,1-}' ) ).values[0] )
    self.assertAlmostEqual( 1.31, table.channel_widths( ChannelID( 'n,Cl35->p,S35{1,1,1-}' ) ).values[0] )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 2: Jpi = 1+, l = 0
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[2]

    self.assertAlmostEqual( 1, spingroup.total_angular_momentum )
    self.assertEqual( +1, spingroup.parity )

    channels = spingroup.channels
    self.assertEqual( 4, len( channels ) )
    self.assertEqual( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ), channels[0].identifier )
    self.assertEqual( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ), channels[1].identifier )
    self.assertEqual( ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' ), channels[2].identifier )
    self.assertEqual( ChannelID( 'n,Cl35->p,S35{0,1,1+}' ), channels[3].identifier )

    self.assertEqual( 4, len( spingroup.reactions ) )

    table = spingroup.resonance_table
    self.assertEqual( 4, table.number_channels )
    self.assertAlmostEqual( 10., table.spacings.values[0] )
    self.assertAlmostEqual( 0.11, table.channel_widths( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ) ).values[0] )
    self.assertAlmostEqual( 0.21, table.channel_widths( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ) ).values[0] )
    self.assertAlmostEqual( 0.31, table.channel_widths( ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' ) ).values[0] )
    self.assertAlmostEqual( 0.41, table.channel_widths( ChannelID( 'n,Cl35->p,S35{0,1,1+}' ) ).values[0] )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 3: Jpi = 2+, l = 0
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[3]

    self.assertAlmostEqual( 2, spingroup.total_angular_momentum )
    self.assertEqual( +1, spingroup.parity )

    channels = spingroup.channels
    self.assertEqual( 3, len( channels ) )
    self.assertEqual( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,2+}' ), channels[0].identifier )
    self.assertEqual( ChannelID( 'n,Cl35->n,Cl35{0,2,2+}' ), channels[1].identifier )
    self.assertEqual( ChannelID( 'n,Cl35->p,S35{0,2,2+}' ), channels[2].identifier )

    table = spingroup.resonance_table
    self.assertEqual( 3, table.number_channels )
    self.assertAlmostEqual( 20., table.spacings.values[0] )
    self.assertAlmostEqual( 0.51, table.channel_widths( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,2+}' ) ).values[0] )
    self.assertAlmostEqual( 0.61, table.channel_widths( ChannelID( 'n,Cl35->n,Cl35{0,2,2+}' ) ).values[0] )
    self.assertAlmostEqual( 0.71, table.channel_widths( ChannelID( 'n,Cl35->p,S35{0,2,2+}' ) ).values[0] )

class Test_UnresolvedCompoundSystem( unittest.TestCase ) :

    def test_component( self ) :

        group1p, group2p, group0m, group1m = make_spin_groups()

        # sorted spin groups
        chunk = UnresolvedCompoundSystem( 1e-5, 2e+3,
                                          [ group0m, group1m, group1p, group2p ] )

        verify_chunk( self, chunk )

        # unsorted spin groups - should be sorted on construction
        chunk = UnresolvedCompoundSystem( 1e-5, 2e+3,
                                          [ group2p, group1p, group1m, group0m ] )

        verify_chunk( self, chunk )

        # keyword arguments
        chunk = UnresolvedCompoundSystem( lower_energy = 1e-5,
                                          upper_energy = 2e+3,
                                          spin_groups = [ group1p, group0m, group2p, group1m ] )

        verify_chunk( self, chunk )

    def test_setters( self ) :

        group1p, group2p, group0m, group1m = make_spin_groups()

        chunk = UnresolvedCompoundSystem( 1e-5, 2e+3, [ group0m, group1p ] )

        chunk.lower_energy_limit = 1e-4
        chunk.upper_energy_limit = 5e+3

        self.assertAlmostEqual( 1e-4, chunk.lower_energy_limit )
        self.assertAlmostEqual( 5e+3, chunk.upper_energy_limit )

        # the spin groups are sorted when they are set as well
        chunk.spin_groups = [ group2p, group1m ]

        self.assertEqual( 2, len( chunk.spin_groups ) )
        self.assertAlmostEqual( 1, chunk.spin_groups[0].total_angular_momentum )
        self.assertEqual( -1, chunk.spin_groups[0].parity )
        self.assertAlmostEqual( 2, chunk.spin_groups[1].total_angular_momentum )
        self.assertEqual( +1, chunk.spin_groups[1].parity )

    def test_copy( self ) :

        import copy

        group1p, group2p, group0m, group1m = make_spin_groups()

        chunk = UnresolvedCompoundSystem( 1e-5, 2e+3,
                                          [ group0m, group1m, group1p, group2p ] )

        shallow = copy.copy( chunk )
        deep = copy.deepcopy( chunk )

        verify_chunk( self, shallow )
        verify_chunk( self, deep )

        self.assertEqual( True, ( chunk == shallow ) )
        self.assertEqual( True, ( chunk == deep ) )

    def test_comparison( self ) :

        group1p, group2p, group0m, group1m = make_spin_groups()

        left = UnresolvedCompoundSystem( 1e-5, 2e+3, [ group0m ] )
        equal = UnresolvedCompoundSystem( 1e-5, 2e+3, [ group0m ] )
        different_groups = UnresolvedCompoundSystem( 1e-5, 2e+3, [ group1p ] )
        different_limits = UnresolvedCompoundSystem( 1e-5, 1e+3, [ group0m ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different_groups ) )
        self.assertEqual( False, ( left == different_limits ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different_groups ) )
        self.assertEqual( True, ( left != different_limits ) )

if __name__ == '__main__' :

    unittest.main()
