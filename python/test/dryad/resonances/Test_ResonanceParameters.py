# standard imports
import unittest

# third party imports

# local imports
from njoy.dryad import Particle
from njoy.dryad.resonances import ParticlePair
from njoy.dryad.resonances import ChannelRadii
from njoy.dryad.resonances import Channel
from njoy.dryad.resonances import ResonanceTable
from njoy.dryad.resonances import Formalism
from njoy.dryad.resonances import BoundaryCondition
from njoy.dryad.resonances import SpinGroup
from njoy.dryad.resonances import CompoundSystem
from njoy.dryad.resonances import UnresolvedChannel
from njoy.dryad.resonances import UnresolvedResonanceTable
from njoy.dryad.resonances import UnresolvedSpinGroup
from njoy.dryad.resonances import UnresolvedCompoundSystem
from njoy.dryad.resonances import TabulatedAverageWidths
from njoy.dryad.resonances import TabulatedLevelSpacing
from njoy.dryad.resonances import ResonanceParameters
from njoy.dryad.id import ChannelID
from njoy.dryad.id import ParticleID
from njoy.dryad.id import ReactionID

class Test_ResonanceParameters( unittest.TestCase ) :
    """Unit test for the ResonanceParameters class."""

    def test_component( self ) :

        neutron_mass = 1.00866491574

        photon = ParticleID.photon()
        neutron = ParticleID.neutron()
        cl35 = ParticleID( 'Cl35' )
        cl36 = ParticleID( 'Cl36[all]' )

        photon_pair = ParticlePair( Particle( photon, 0, 1, +1 ),
                                    Particle( cl36, 35.65932 * neutron_mass, 0, +1 ) )
        neutron_pair = ParticlePair( Particle( neutron, neutron_mass, 0.5, +1 ),
                                     Particle( cl35, 34.66845 * neutron_mass, 1.5, +1 ) )

        zero_radii = ChannelRadii( 0., 0. )
        resolved_radii = ChannelRadii( 4.822220, 3.667980 )

        spingroup = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                          neutron_pair, photon_pair, 0., None,
                                          zero_radii, False ),
                                 Channel( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                          neutron_pair, neutron_pair, 0., None,
                                          resolved_radii ) ],
                               ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                                 ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ) ],
                                               [ 1. ], [ [ 2. ], [ 3. ] ] ),
                               Formalism.ReichMoore, BoundaryCondition.ShiftFactor )

        resolved = CompoundSystem( 1e-5, 1e+4, [ spingroup ] )

        capture_pair = ParticlePair( Particle( photon, 0, 1, +1 ),
                                     Particle( ParticleID( 'Cl36' ), 35.9683050031, 0, +1 ) )
        elastic_pair = ParticlePair( Particle( neutron, 1.00866491574, 0.5, +1 ),
                                     Particle( cl35, 34.9688491981, 1.5, +1 ) )

        capture_radii = ChannelRadii( 0. )
        unresolved_radii = ChannelRadii( 4.822220, 3.667980 )

        capture = UnresolvedChannel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                     elastic_pair, capture_pair,
                                     0., None, capture_radii )
        elastic = UnresolvedChannel( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                     elastic_pair, elastic_pair,
                                     0., None, unresolved_radii )

        table = UnresolvedResonanceTable(
                    channels = [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                 ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ) ],
                    average_widths = [ TabulatedAverageWidths( [ 1e+4, 1e+6 ], [ 0.1, 0.4 ] ),
                                       TabulatedAverageWidths( [ 1e+4, 1e+6 ], [ 1.1, 1.4 ] ) ],
                    level_spacings = TabulatedLevelSpacing( [ 1e+4, 1e+6 ], [ 10., 40. ] ) )

        unresolved_spingroup = UnresolvedSpinGroup( [ capture, elastic ], table )

        unresolved = UnresolvedCompoundSystem( 1e+4, 1e+6, [ unresolved_spingroup ] )

        # resolved data only, without the unresolved argument
        chunk = ResonanceParameters( [ resolved ] )

        self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
        self.assertAlmostEqual( 1e+4, chunk.upper_energy_limit )

        radii = chunk.radii
        self.assertEqual( False, radii.has_shift_factor_radius )
        self.assertEqual( True, radii.has_phase_shift_radius )
        self.assertEqual( True, isinstance( radii.penetrability_radius, float ) )
        self.assertAlmostEqual( 4.822220, radii.penetrability_radius )
        self.assertEqual( None, radii.shift_factor_radius )
        self.assertEqual( True, isinstance( radii.phase_shift_radius, float ) )
        self.assertAlmostEqual( 3.667980, radii.phase_shift_radius )

        self.assertEqual( 1, len( chunk.resolved ) )
        self.assertEqual( resolved, chunk.resolved[0] )
        self.assertAlmostEqual( 1e-5, chunk.resolved[0].lower_energy_limit )
        self.assertAlmostEqual( 1e+4, chunk.resolved[0].upper_energy_limit )

        self.assertEqual( None, chunk.unresolved )

        self.assertEqual( 2, len( chunk.reactions ) )
        self.assertEqual( ReactionID( 'n,Cl35->g,Cl36[all]' ), chunk.reactions[0] )
        self.assertEqual( ReactionID( 'n,Cl35->n,Cl35' ), chunk.reactions[1] )

        # resolved and unresolved data
        chunk = ResonanceParameters( [ resolved ], unresolved )

        self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
        self.assertAlmostEqual( 1e+6, chunk.upper_energy_limit )

        radii = chunk.radii
        self.assertEqual( False, radii.has_shift_factor_radius )
        self.assertEqual( True, radii.has_phase_shift_radius )
        self.assertEqual( True, isinstance( radii.penetrability_radius, float ) )
        self.assertAlmostEqual( 4.822220, radii.penetrability_radius )
        self.assertEqual( None, radii.shift_factor_radius )
        self.assertEqual( True, isinstance( radii.phase_shift_radius, float ) )
        self.assertAlmostEqual( 3.667980, radii.phase_shift_radius )

        self.assertEqual( 1, len( chunk.resolved ) )
        self.assertEqual( resolved, chunk.resolved[0] )

        self.assertEqual( True, chunk.unresolved is not None )
        self.assertEqual( unresolved, chunk.unresolved )
        self.assertAlmostEqual( 1e+4, chunk.unresolved.lower_energy_limit )
        self.assertAlmostEqual( 1e+6, chunk.unresolved.upper_energy_limit )

        self.assertEqual( 2, len( chunk.reactions ) )
        self.assertEqual( ReactionID( 'n,Cl35->g,Cl36[all]' ), chunk.reactions[0] )
        self.assertEqual( ReactionID( 'n,Cl35->n,Cl35' ), chunk.reactions[1] )

        # multiple resolved compound systems
        lower = CompoundSystem( 1e-5, 1e+3, [ spingroup ] )
        upper = CompoundSystem( 1e+3, 1e+4, [ spingroup ] )

        chunk = ResonanceParameters( [ lower, upper ], unresolved )

        self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
        self.assertAlmostEqual( 1e+6, chunk.upper_energy_limit )

        radii = chunk.radii
        self.assertEqual( False, radii.has_shift_factor_radius )
        self.assertEqual( True, radii.has_phase_shift_radius )
        self.assertEqual( True, isinstance( radii.penetrability_radius, float ) )
        self.assertAlmostEqual( 4.822220, radii.penetrability_radius )
        self.assertEqual( None, radii.shift_factor_radius )
        self.assertEqual( True, isinstance( radii.phase_shift_radius, float ) )
        self.assertAlmostEqual( 3.667980, radii.phase_shift_radius )

        self.assertEqual( 2, len( chunk.resolved ) )
        self.assertAlmostEqual( 1e-5, chunk.resolved[0].lower_energy_limit )
        self.assertAlmostEqual( 1e+3, chunk.resolved[1].lower_energy_limit )

        self.assertEqual( True, chunk.unresolved is not None )

        self.assertEqual( 2, len( chunk.reactions ) )
        self.assertEqual( ReactionID( 'n,Cl35->g,Cl36[all]' ), chunk.reactions[0] )
        self.assertEqual( ReactionID( 'n,Cl35->n,Cl35' ), chunk.reactions[1] )

        # unresolved data only
        chunk = ResonanceParameters( [], unresolved )

        self.assertAlmostEqual( 1e+4, chunk.lower_energy_limit )
        self.assertAlmostEqual( 1e+6, chunk.upper_energy_limit )

        radii = chunk.radii
        self.assertEqual( False, radii.has_shift_factor_radius )
        self.assertEqual( True, radii.has_phase_shift_radius )
        self.assertEqual( True, isinstance( radii.penetrability_radius, float ) )
        self.assertAlmostEqual( 4.822220, radii.penetrability_radius )
        self.assertEqual( None, radii.shift_factor_radius )
        self.assertEqual( True, isinstance( radii.phase_shift_radius, float ) )
        self.assertAlmostEqual( 3.667980, radii.phase_shift_radius )

        self.assertEqual( 0, len( chunk.resolved ) )

        self.assertEqual( True, chunk.unresolved is not None )
        self.assertEqual( unresolved, chunk.unresolved )

        self.assertEqual( 2, len( chunk.reactions ) )
        self.assertEqual( ReactionID( 'n,Cl35->g,Cl36[all]' ), chunk.reactions[0] )
        self.assertEqual( ReactionID( 'n,Cl35->n,Cl35' ), chunk.reactions[1] )

        # channel radii only
        chunk = ResonanceParameters( 1e-5, 5e+5, ChannelRadii( 4.3 ) )

        self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
        self.assertAlmostEqual( 5e+5, chunk.upper_energy_limit )

        radii = chunk.radii
        self.assertEqual( False, radii.has_shift_factor_radius )
        self.assertEqual( False, radii.has_phase_shift_radius )
        self.assertEqual( True, isinstance( radii.penetrability_radius, float ) )
        self.assertAlmostEqual( 4.3, radii.penetrability_radius )
        self.assertEqual( None, radii.shift_factor_radius )
        self.assertEqual( None, radii.phase_shift_radius )

        self.assertEqual( 0, len( chunk.resolved ) )
        self.assertEqual( None, chunk.unresolved )

    def test_comparison( self ) :

        neutron_mass = 1.00866491574

        photon = ParticleID.photon()
        neutron = ParticleID.neutron()
        cl35 = ParticleID( 'Cl35' )
        cl36 = ParticleID( 'Cl36[all]' )

        photon_pair = ParticlePair( Particle( photon, 0, 1, +1 ),
                                    Particle( cl36, 35.65932 * neutron_mass, 0, +1 ) )
        neutron_pair = ParticlePair( Particle( neutron, neutron_mass, 0.5, +1 ),
                                     Particle( cl35, 34.66845 * neutron_mass, 1.5, +1 ) )

        zero_radii = ChannelRadii( 0., 0. )
        resolved_radii = ChannelRadii( 4.822220, 3.667980 )

        spingroup = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                          neutron_pair, photon_pair, 0., None,
                                          zero_radii, False ),
                                 Channel( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                          neutron_pair, neutron_pair, 0., None,
                                          resolved_radii ) ],
                               ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                                 ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ) ],
                                               [ 1. ], [ [ 2. ], [ 3. ] ] ),
                               Formalism.ReichMoore, BoundaryCondition.ShiftFactor )

        # a resolved compound system with the resonance at 2 eV instead of 1 eV
        other_spingroup = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                               neutron_pair, photon_pair, 0., None,
                                               zero_radii, False ),
                                      Channel( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                               neutron_pair, neutron_pair, 0., None,
                                               resolved_radii ) ],
                                    ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                                      ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ) ],
                                                    [ 2. ], [ [ 2. ], [ 3. ] ] ),
                                    Formalism.ReichMoore, BoundaryCondition.ShiftFactor )

        resolved = CompoundSystem( 1e-5, 1e+4, [ spingroup ] )
        other_resolved = CompoundSystem( 1e-5, 1e+4, [ other_spingroup ] )

        # a resolved compound system with the same spin group but a different
        # upper energy limit
        resolved_limits = CompoundSystem( 1e-5, 5e+3, [ spingroup ] )

        capture_pair = ParticlePair( Particle( photon, 0, 1, +1 ),
                                     Particle( ParticleID( 'Cl36' ), 35.9683050031, 0, +1 ) )
        elastic_pair = ParticlePair( Particle( neutron, 1.00866491574, 0.5, +1 ),
                                     Particle( cl35, 34.9688491981, 1.5, +1 ) )

        capture_radii = ChannelRadii( 0. )
        unresolved_radii = ChannelRadii( 4.822220, 3.667980 )

        capture = UnresolvedChannel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                     elastic_pair, capture_pair,
                                     0., None, capture_radii )
        elastic = UnresolvedChannel( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                     elastic_pair, elastic_pair,
                                     0., None, unresolved_radii )

        table = UnresolvedResonanceTable(
                    channels = [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                 ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ) ],
                    average_widths = [ TabulatedAverageWidths( [ 1e+4, 1e+6 ], [ 0.1, 0.4 ] ),
                                       TabulatedAverageWidths( [ 1e+4, 1e+6 ], [ 1.1, 1.4 ] ) ],
                    level_spacings = TabulatedLevelSpacing( [ 1e+4, 1e+6 ], [ 10., 40. ] ) )

        unresolved_spingroup = UnresolvedSpinGroup( [ capture, elastic ], table )

        unresolved = UnresolvedCompoundSystem( 1e+4, 1e+6, [ unresolved_spingroup ] )

        # an unresolved compound system with a different level spacing
        other_table = UnresolvedResonanceTable(
                          channels = [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                       ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ) ],
                          average_widths = [ TabulatedAverageWidths( [ 1e+4, 1e+6 ], [ 0.1, 0.4 ] ),
                                             TabulatedAverageWidths( [ 1e+4, 1e+6 ], [ 1.1, 1.4 ] ) ],
                          level_spacings = TabulatedLevelSpacing( [ 1e+4, 1e+6 ], [ 20., 80. ] ) )

        other_unresolved = UnresolvedCompoundSystem( 1e+4, 1e+6,
                                                      [ UnresolvedSpinGroup( [ capture, elastic ], other_table ) ] )

        # an unresolved compound system with the same spin group but a
        # different upper energy limit
        unresolved_limits = UnresolvedCompoundSystem( 1e+4, 5e+5, [ unresolved_spingroup ] )

        left = ResonanceParameters( [ resolved ], unresolved )
        equal = ResonanceParameters( [ resolved ], unresolved )
        different_resolved = ResonanceParameters( [ other_resolved ], unresolved )
        different_unresolved = ResonanceParameters( [ resolved ], other_unresolved )
        resolved_only = ResonanceParameters( [ resolved ] )
        unresolved_only = ResonanceParameters( [], unresolved )
        limits = ResonanceParameters( [ resolved ], unresolved_limits )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different_resolved ) )
        self.assertEqual( False, ( left == different_unresolved ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different_resolved ) )
        self.assertEqual( True, ( left != different_unresolved ) )

        self.assertEqual( False, ( left == limits ) )
        self.assertEqual( True, ( left != limits ) )

if __name__ == '__main__' :

    unittest.main()
