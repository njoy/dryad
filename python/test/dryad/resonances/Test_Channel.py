# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import Particle
from njoy.dryad.resonances import Channel
from njoy.dryad.resonances import ChannelQuantumNumbers
from njoy.dryad.resonances import ChannelRadii
from njoy.dryad.resonances import ParticlePair
from njoy.dryad.resonances import Kinematics
from njoy.dryad.id import ChannelID
from njoy.dryad.id import ReactionID
from njoy.dryad.id import ParticleID

class Test_Channel( unittest.TestCase ) :
    """Unit test for the Channel class."""

    def test_component( self ) :

        # identifiers
        elasticID = ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' )
        inelasticID = ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' )
        captureID = ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' )
        protonID = ChannelID( 'n,Cl35->p,S35{0,1,1+}' )

        elasticRID = ReactionID( 'n,Cl35->n,Cl35' )
        inelasticRID = ReactionID( 'n,Cl35->n,Cl35_e1' )
        captureRID = ReactionID( 'n,Cl35->g,Cl36[all]' )
        protonRID = ReactionID( 'n,Cl35->p,S35' )

        elasticNumbers = ChannelQuantumNumbers( 0, 1, 1, +1 )
        inelasticNumbers = ChannelQuantumNumbers( 0, 1, 1, +1 )
        captureNumbers = ChannelQuantumNumbers( 0, 0, 1, +1 )
        protonNumbers = ChannelQuantumNumbers( 0, 1, 1, +1 )

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

        energy = 1e-5

        capture = Channel( captureID, elasticPair, capturePair,
                           captureQ, captureBoundary, captureRadii )
        elastic = Channel( elasticID, elasticPair, elasticPair,
                           elasticQ, elasticBoundary, elasticRadii )
        inelastic = Channel( inelasticID, elasticPair, inelasticPair,
                             inelasticQ, inelasticBoundary, inelasticRadii )
        proton = Channel( protonID, elasticPair, protonPair,
                          protonQ, protonBoundary, protonRadii )

        # photon channel, not an incident channel, no threshold
        self.assertEqual( captureID, capture.identifier )
        self.assertEqual( captureRID, capture.reaction )
        self.assertEqual( captureNumbers, capture.quantum_numbers )
        self.assertEqual( elasticPair, capture.incident_particle_pair )
        self.assertEqual( capturePair, capture.outgoing_particle_pair )
        self.assertAlmostEqual( captureQ, capture.q_value )
        self.assertIsNone( capture.boundary_condition )
        self.assertEqual( captureRadii, capture.channel_radii )
        self.assertEqual( False, capture.is_incident_channel )
        self.assertAlmostEqual( 1., capture.statistical_spin_factor )
        self.assertEqual( False, capture.is_below_threshold( energy ) )
        self.assertEqual( Kinematics.NonRelativistic, capture.kinematics_type )
        self.assertAlmostEqual( 0., capture.wave_number( energy ) )
        self.assertAlmostEqual( 0., capture.sommerfeld_parameter( energy ) )
        self.assertAlmostEqual( 1., capture.penetrability( energy ) )
        self.assertAlmostEqual( 0., capture.shift_factor( energy ) )
        self.assertAlmostEqual( 0., capture.phase_shift( energy ) )
        self.assertAlmostEqual( 0., capture.phase_shift_difference( energy ) )

        # neutron channel, incident channel, no threshold
        self.assertEqual( elasticID, elastic.identifier )
        self.assertEqual( elasticRID, elastic.reaction )
        self.assertEqual( elasticNumbers, elastic.quantum_numbers )
        self.assertEqual( elasticPair, elastic.incident_particle_pair )
        self.assertEqual( elasticPair, elastic.outgoing_particle_pair )
        self.assertAlmostEqual( elasticQ, elastic.q_value )
        self.assertIsNone( elastic.boundary_condition )
        self.assertEqual( elasticRadii, elastic.channel_radii )
        self.assertEqual( True, elastic.is_incident_channel )
        self.assertAlmostEqual( 0.375, elastic.statistical_spin_factor )
        self.assertEqual( False, elastic.is_below_threshold( energy ) )
        self.assertEqual( Kinematics.NonRelativistic, elastic.kinematics_type )
        self.assertAlmostEqual( 6.752152278684156e-7, elastic.wave_number( energy ) )
        self.assertAlmostEqual( 0., elastic.sommerfeld_parameter( energy ) )
        self.assertAlmostEqual( 3.256036376131631e-6, elastic.penetrability( energy ) )
        self.assertAlmostEqual( 0., elastic.shift_factor( energy ) )
        self.assertAlmostEqual( 2.476675951516791e-6, elastic.phase_shift( energy ) )
        self.assertAlmostEqual( 0., elastic.phase_shift_difference( energy ) )

        # neutron channel, not incident channel, threshold
        self.assertEqual( inelasticID, inelastic.identifier )
        self.assertEqual( inelasticRID, inelastic.reaction )
        self.assertEqual( inelasticNumbers, inelastic.quantum_numbers )
        self.assertEqual( elasticPair, inelastic.incident_particle_pair )
        self.assertEqual( inelasticPair, inelastic.outgoing_particle_pair )
        self.assertAlmostEqual( inelasticQ, inelastic.q_value )
        self.assertIsNone( inelastic.boundary_condition )
        self.assertEqual( elasticRadii, inelastic.channel_radii )
        self.assertEqual( False, inelastic.is_incident_channel )
        self.assertAlmostEqual( 0.375, inelastic.statistical_spin_factor )
        self.assertEqual( True, inelastic.is_below_threshold( energy ) )
        self.assertEqual( Kinematics.NonRelativistic, inelastic.kinematics_type )
        self.assertAlmostEqual( 0.2391648503730464, inelastic.wave_number( energy ) )
        self.assertAlmostEqual( 0., inelastic.sommerfeld_parameter( energy ) )
        self.assertAlmostEqual( 1.153305524765912, inelastic.penetrability( energy ) )
        self.assertAlmostEqual( 0., inelastic.shift_factor( energy ) )
        self.assertAlmostEqual( 8.772518878713266e-1, inelastic.phase_shift( energy ) )
        self.assertAlmostEqual( 0., inelastic.phase_shift_difference( energy ) )

        # proton channel, not an incident channel, no threshold
        self.assertEqual( protonID, proton.identifier )
        self.assertEqual( protonRID, proton.reaction )
        self.assertEqual( protonNumbers, proton.quantum_numbers )
        self.assertEqual( elasticPair, proton.incident_particle_pair )
        self.assertEqual( protonPair, proton.outgoing_particle_pair )
        self.assertAlmostEqual( protonQ, proton.q_value )
        self.assertIsNone( proton.boundary_condition )
        self.assertEqual( elasticRadii, proton.channel_radii )
        self.assertEqual( False, proton.is_incident_channel )
        self.assertAlmostEqual( 0.375, proton.statistical_spin_factor )
        self.assertEqual( False, proton.is_below_threshold( energy ) )
        self.assertEqual( Kinematics.NonRelativistic, proton.kinematics_type )
        self.assertAlmostEqual( 0.1697421616532552, proton.wave_number( energy ) )
        self.assertAlmostEqual( 3.179105369595768, proton.sommerfeld_parameter( energy ) )
        self.assertAlmostEqual(  2.896705590727021e-5, proton.penetrability( energy ) )
        self.assertAlmostEqual( -1.872686299035523   , proton.shift_factor( energy ) )
        self.assertAlmostEqual(  2.168669356291763e-6, proton.phase_shift( energy ) )
        self.assertAlmostEqual( 0., proton.phase_shift_difference( energy ) )

    def test_comparison( self ) :

        # identifiers
        elasticID = ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' )
        inelasticID = ChannelID( 'n,Cl35->n,Cl35_e1{0,1,1+}' )

        # particles
        n = Particle( ParticleID.neutron(), 1.00866491574, 0.5, +1 )
        cl35 = Particle( ParticleID( 'Cl35' ), 34.9688491981, 1.5, +1 )
        cl35_e1 = Particle( ParticleID( 'Cl35_e1' ), 34.9688491981, 1.5, +1 )

        # particle pairs
        elasticPair = ParticlePair( n, cl35 )
        inelasticPair = ParticlePair( n, cl35_e1 )

        # Q values
        elasticQ = 0.0
        inelasticQ = -1.219440e+6

        # boundary conditions
        elasticBoundary = None
        inelasticBoundary = None

        # channel radii
        elasticRadii = ChannelRadii( 4.822220, 3.667980 )
        inelasticRadii = ChannelRadii( 4.822220, 3.667980 )

        left = Channel( elasticID, elasticPair, elasticPair,
                        elasticQ, elasticBoundary, elasticRadii )
        equal = Channel( elasticID, elasticPair, elasticPair,
                         elasticQ, elasticBoundary, elasticRadii )
        different = Channel( inelasticID, elasticPair, inelasticPair,
                             inelasticQ, inelasticBoundary, inelasticRadii )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
