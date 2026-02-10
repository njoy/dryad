# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.resonances import Particle
from njoy.dryad.resonances import ParticlePair
from njoy.dryad.resonances import ChannelRadii
from njoy.dryad.resonances import Channel
from njoy.dryad.resonances import ResonanceTable
from njoy.dryad.resonances import Formalism
from njoy.dryad.resonances import BoundaryCondition
from njoy.dryad.resonances import SpinGroup
from njoy.dryad.resonances import CompoundSystem
from njoy.dryad.id import ChannelID
from njoy.dryad.id import ParticleID
from njoy.dryad.id import ReactionID

def verify_chunk( self, chunk ) :

    neutron_mass = 1.00866491574

    photon = ParticleID.photon()
    neutron = ParticleID.neutron()
    proton = ParticleID.proton()
    cl35 = ParticleID( 'Cl35' )
    cl36 = ParticleID( 'Cl36[all]' )
    s35 = ParticleID( 'S35' )

    photon_pair = ParticlePair( Particle( photon, 0, 1, +1 ),
                                Particle( cl36, 35.65932 * neutron_mass, 0, +1 ) )
    neutron_pair = ParticlePair( Particle( neutron, neutron_mass, 0.5, +1 ),
                                 Particle( cl35, 34.66845 * neutron_mass, 1.5, +1 ) )
    proton_pair = ParticlePair( Particle( proton, .9986235 * neutron_mass, 0.5, +1 ),
                                Particle( s35, 34.66863 * neutron_mass, 1.5, +1 ) )

    zero_radii = ChannelRadii( 0., 0. )
    radii1 = ChannelRadii( 4.822220, 4.888750 )
    radii2 = ChannelRadii( 4.822220, 3.667980 )

    # * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    # content verification
    # * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
    self.assertAlmostEqual( 2e+3, chunk.upper_energy_limit )

    self.assertEqual( 3, len( chunk.reactions ) )
    self.assertEqual( ReactionID( 'n,Cl35->g,Cl36[all]' ), chunk.reactions[0] )
    self.assertEqual( ReactionID( 'n,Cl35->n,Cl35'      ), chunk.reactions[1] )
    self.assertEqual( ReactionID( 'n,Cl35->p,S35'       ), chunk.reactions[2] )

    groups = chunk.spin_groups

    # spin groups
    self.assertEqual( 6, len( groups ) )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 0
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[0]

    # channels
    channels = spingroup.channels

    self.assertEqual( 2, len( channels ) )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 0, channel 0: capture (eliminated)
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel0 = channels[0]
    self.assertEqual( ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ), channel0.identifier )
    self.assertEqual( False, channel0.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel0.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( photon_pair, channel0.outgoing_particle_pair )

    # radii
    self.assertEqual( zero_radii, channel0.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel0.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel0.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 0, channel 1: elastic
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel1 = channels[1]
    self.assertEqual( ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ), channel1.identifier )
    self.assertEqual( True, channel1.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel1.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( neutron_pair, channel1.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel1.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel1.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel1.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 0, resonance table
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    table = spingroup.resonance_table
    self.assertEqual( 2, table.number_channels )
    self.assertEqual( 1, table.number_energies )

    energies = table.energies
    self.assertAlmostEqual( 1, energies[0] )

    resonances = table.reduced_width_amplitudes
    self.assertAlmostEqual( 2, resonances[0][0] )
    self.assertAlmostEqual( 3, resonances[1][0] )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 1
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[1]

    # channels
    channels = spingroup.channels

    self.assertEqual( 5, len( channels ) )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 1, channel 0: capture (eliminated)
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel0 = channels[0]
    self.assertEqual( ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ), channel0.identifier )
    self.assertEqual( False, channel0.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel0.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( photon_pair, channel0.outgoing_particle_pair )

    # radii
    self.assertEqual( zero_radii, channel0.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel0.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel0.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 1, channel 1: elastic
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel1 = channels[1]
    self.assertEqual( ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ), channel1.identifier )
    self.assertEqual( True, channel1.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel1.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( neutron_pair, channel1.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel1.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel1.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel1.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 1, channel 2: proton emission
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel2 = channels[3]
    self.assertEqual( ChannelID( "n,Cl35->p,S35{1,1,1-}" ), channel2.identifier )
    self.assertEqual( False, channel2.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel2.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( proton_pair, channel2.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel2.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel2.boundary_condition )

    # Q value
    self.assertAlmostEqual( 615220, channel2.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 1, channel 3: elastic
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel3 = channels[2]
    self.assertEqual( ChannelID( "n,Cl35->n,Cl35{1,2,1-}" ), channel3.identifier )
    self.assertEqual( True, channel3.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel3.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( neutron_pair, channel3.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel3.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel3.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0, channel3.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 1, channel 4: proton emission
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel4 = channels[4]
    self.assertEqual( ChannelID( "n,Cl35->p,S35{1,2,1-}" ), channel4.identifier )
    self.assertEqual( False, channel4.is_incident_channel )

      # incident particle pair
    self.assertEqual( neutron_pair, channel4.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( proton_pair, channel4.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel4.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel4.boundary_condition )

    # Q value
    self.assertAlmostEqual( 615220, channel4.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 1, resonance table
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    table = spingroup.resonance_table
    self.assertEqual( 5, table.number_channels )
    self.assertEqual( 1, table.number_energies )

    energies = table.energies
    self.assertAlmostEqual( 11, energies[0] )

    resonances = table.reduced_width_amplitudes
    self.assertAlmostEqual( 12, resonances[0][0] )
    self.assertAlmostEqual( 13, resonances[1][0] )
    self.assertAlmostEqual( 14, resonances[2][0] )
    self.assertAlmostEqual( 15, resonances[3][0] )
    self.assertAlmostEqual( 16, resonances[4][0] )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 2
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[2]

    # channels
    channels = spingroup.channels

    self.assertEqual( 3, len( channels ) )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 2, channel 0: capture (eliminated)
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel0 = channels[0]
    self.assertEqual( ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ), channel0.identifier )
    self.assertEqual( False, channel0.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel0.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( photon_pair, channel0.outgoing_particle_pair )

    # radii
    self.assertEqual( zero_radii, channel0.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel0.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel0.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 2, channel 1: elastic
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel1 = channels[1]
    self.assertEqual( ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ), channel1.identifier )
    self.assertEqual( True, channel1.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel1.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( neutron_pair, channel1.outgoing_particle_pair )

    # radii
    self.assertEqual( radii2, channel1.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel1.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel1.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 2, channel 2: proton emission
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel2 = channels[2]
    self.assertEqual( ChannelID( "n,Cl35->p,S35{0,1,1+}" ), channel2.identifier )
    self.assertEqual( False, channel2.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel2.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( proton_pair, channel2.outgoing_particle_pair )

    # radii
    self.assertEqual( radii2, channel2.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel2.boundary_condition )

    # Q value
    self.assertAlmostEqual( 615220, channel2.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 2, resonance table
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    table = spingroup.resonance_table
    self.assertEqual( 3, table.number_channels )
    self.assertEqual( 1, table.number_energies )

    energies = table.energies
    self.assertAlmostEqual( 21, energies[0] )

    resonances = table.reduced_width_amplitudes
    self.assertAlmostEqual( 22, resonances[0][0] )
    self.assertAlmostEqual( 23, resonances[1][0] )
    self.assertAlmostEqual( 24, resonances[2][0] )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 3
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[3]

    # channels
    channels = spingroup.channels

    self.assertEqual( 5, len( channels ) )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 3, channel 0: capture (eliminated)
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel0 = channels[0]
    self.assertEqual( ChannelID( "n,Cl35->g,Cl36[all]{1,0,2-}" ), channel0.identifier )
    self.assertEqual( False, channel0.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel0.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( photon_pair, channel0.outgoing_particle_pair )

    # radii
    self.assertEqual( zero_radii, channel0.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel0.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel0.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 3, channel 1: elastic
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel1 = channels[1]
    self.assertEqual( ChannelID( "n,Cl35->n,Cl35{1,1,2-}" ), channel1.identifier )
    self.assertEqual( True, channel1.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel1.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( neutron_pair, channel1.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel1.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel1.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel1.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 3, channel 2: proton emission
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel2 = channels[3]
    self.assertEqual( ChannelID( "n,Cl35->p,S35{1,1,2-}" ), channel2.identifier )
    self.assertEqual( False, channel2.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel2.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( proton_pair, channel2.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel2.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel2.boundary_condition )

    # Q value
    self.assertAlmostEqual( 615220, channel2.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 3, channel 3: elastic
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel3 = channels[2]
    self.assertEqual( ChannelID( "n,Cl35->n,Cl35{1,2,2-}" ), channel3.identifier )
    self.assertEqual( True, channel3.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel3.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( neutron_pair, channel3.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel3.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel3.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel3.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 3, channel 4: proton emission
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel4 = channels[4]
    self.assertEqual( ChannelID( "n,Cl35->p,S35{1,2,2-}" ), channel4.identifier )
    self.assertEqual( False, channel4.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel4.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( proton_pair, channel4.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel4.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel4.boundary_condition )

    # Q value
    self.assertAlmostEqual( 615220, channel4.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 3, resonance table
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    table = spingroup.resonance_table
    self.assertEqual( 5, table.number_channels )
    self.assertEqual( 1, table.number_energies )

    energies = table.energies
    self.assertAlmostEqual( 31, energies[0] )

    resonances = table.reduced_width_amplitudes
    self.assertAlmostEqual( 32, resonances[0][0] )
    self.assertAlmostEqual( 33, resonances[1][0] )
    self.assertAlmostEqual( 34, resonances[2][0] )
    self.assertAlmostEqual( 35, resonances[3][0] )
    self.assertAlmostEqual( 36, resonances[4][0] )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 4
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[4]

    # channels
    channels = spingroup.channels

    self.assertEqual( 3, len( channels ) )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 4, channel 0: capture (eliminated)
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel0 = channels[0]
    self.assertEqual( ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ), channel0.identifier )
    self.assertEqual( False, channel0.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel0.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( photon_pair, channel0.outgoing_particle_pair )

    # radii
    self.assertEqual( zero_radii, channel0.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel0.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel0.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 4, channel 1: elastic
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel1 = channels[1]
    self.assertEqual( ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ), channel1.identifier )
    self.assertEqual( True, channel1.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel1.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( neutron_pair, channel1.outgoing_particle_pair )

    # radii
    self.assertEqual( radii2, channel1.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel1.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel1.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 4, channel 2: proton emission
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel2 = channels[2]
    self.assertEqual( ChannelID( "n,Cl35->p,S35{0,2,2+}" ), channel2.identifier )
    self.assertEqual( False, channel2.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel2.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( proton_pair, channel2.outgoing_particle_pair )

    # radii
    self.assertEqual( radii2, channel2.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel2.boundary_condition )

    # Q value
    self.assertAlmostEqual( 615220, channel2.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 4, resonance table
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    table = spingroup.resonance_table
    self.assertEqual( 3, table.number_channels )
    self.assertEqual( 1, table.number_energies )

    energies = table.energies
    self.assertAlmostEqual( 41, energies[0] )

    resonances = table.reduced_width_amplitudes
    self.assertAlmostEqual( 42, resonances[0][0] )
    self.assertAlmostEqual( 43, resonances[1][0] )
    self.assertAlmostEqual( 44, resonances[2][0] )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # spin group 5
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    spingroup = groups[5]

    # channels
    channels = spingroup.channels

    self.assertEqual( 3, len( channels ) )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 5, channel 0: capture (eliminated)
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel0 = channels[0]
    self.assertEqual( ChannelID( "n,Cl35->g,Cl36[all]{1,0,3-}" ), channel0.identifier )
    self.assertEqual( False, channel0.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel0.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( photon_pair, channel0.outgoing_particle_pair )

    # radii
    self.assertEqual( zero_radii, channel0.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel0.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0.0, channel0.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 5, channel 1: elastic
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel1 = channels[1]
    self.assertEqual( ChannelID( "n,Cl35->n,Cl35{1,2,3-}" ), channel1.identifier )
    self.assertEqual( True, channel1.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel1.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( neutron_pair, channel1.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel1.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel1.boundary_condition )

    # Q value
    self.assertAlmostEqual( 0, channel1.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 5, channel 2: proton emission
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    channel2 = channels[2]
    self.assertEqual( ChannelID( "n,Cl35->p,S35{1,2,3-}" ), channel2.identifier )
    self.assertEqual( False, channel2.is_incident_channel )

    # incident particle pair
    self.assertEqual( neutron_pair, channel2.incident_particle_pair )

    # outgoing particle pair
    self.assertEqual( proton_pair, channel2.outgoing_particle_pair )

    # radii
    self.assertEqual( radii1, channel2.channel_radii )

    # boundary conditions
    self.assertEqual( None, channel2.boundary_condition )

    # Q value
    self.assertAlmostEqual( 615220, channel2.q_value )

    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
    # spin group 5, resonance table
    # - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

    table = spingroup.resonance_table
    self.assertEqual( 3, table.number_channels )
    self.assertEqual( 1, table.number_energies )

    energies = table.energies
    self.assertAlmostEqual( 51, energies[0] )

    resonances = table.reduced_width_amplitudes
    self.assertAlmostEqual( 52, resonances[0][0] )
    self.assertAlmostEqual( 53, resonances[1][0] )
    self.assertAlmostEqual( 54, resonances[2][0] )

class Test_CompoundSystem( unittest.TestCase ) :
    """Unit test for the CompoundSystem class."""

    def test_component( self ) :

        neutron_mass = 1.00866491574

        photon = ParticleID.photon()
        neutron = ParticleID.neutron()
        proton = ParticleID.proton()
        cl35 = ParticleID( 'Cl35' )
        cl36 = ParticleID( 'Cl36[all]' )
        s35 = ParticleID( 'S35' )

        photon_pair = ParticlePair( Particle( photon, 0, 1, +1 ),
                                    Particle( cl36, 35.65932 * neutron_mass, 0, +1 ) )
        neutron_pair = ParticlePair( Particle( neutron, neutron_mass, 0.5, +1 ),
                                     Particle( cl35, 34.66845 * neutron_mass, 1.5, +1 ) )
        proton_pair = ParticlePair( Particle( proton, .9986235 * neutron_mass, 0.5, +1 ),
                                    Particle( s35, 34.66863 * neutron_mass, 1.5, +1 ) )

        zero_radii = ChannelRadii( 0., 0. )
        radii1 = ChannelRadii( 4.822220, 4.888750 )
        radii2 = ChannelRadii( 4.822220, 3.667980 )

        formalism = Formalism.ReichMoore
        boundary = BoundaryCondition.ShiftFactor

        spingroup0 = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ),
                                           neutron_pair, photon_pair, 0., None,
                                           zero_radii ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ) ],
                                ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ) ],
                                                [ 1. ], [ [ 2. ], [ 3. ] ] ),
                                formalism, boundary )
        spingroup1 = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,1-}' ),
                                           neutron_pair, photon_pair, 0., None,
                                           zero_radii ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,1,1-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{1,1,1-}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,2,1-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{1,2,1-}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii1 ) ],
                                ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,1,1-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,2,1-}' ),
                                                  ChannelID( 'n,Cl35->p,S35{1,2,1-}' ) ],
                                                [ 11. ], [ [ 12. ], [ 13. ], [ 14. ], [ 15. ], [ 16. ] ] ),
                                formalism, boundary )
        spingroup2 = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                           neutron_pair, photon_pair, 0., None,
                                           zero_radii ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii2 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{0,1,1+}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii2 ) ],
                                ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                                  ChannelID( 'n,Cl35->p,S35{0,1,1+}' ) ],
                                                [ 21. ], [ [ 22. ], [ 23. ], [ 24. ] ] ),
                                formalism, boundary )
        spingroup3 = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,2-}' ),
                                           neutron_pair, photon_pair, 0., None,
                                           zero_radii ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,1,2-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{1,1,2-}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,2,2-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{1,2,2-}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii1 ) ],
                                ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{1,0,2-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,1,2-}' ),
                                                  ChannelID( 'n,Cl35->p,S35{1,1,2-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,2,2-}' ),
                                                  ChannelID( 'n,Cl35->p,S35{1,2,2-}' ) ],
                                                [ 31. ], [ [ 32. ], [ 33. ], [ 34. ], [ 35. ], [ 36. ] ] ),
                                formalism, boundary )
        spingroup4 = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,2+}' ),
                                           neutron_pair, photon_pair, 0., None,
                                           zero_radii ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{0,2,2+}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii2 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{0,2,2+}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii2 ) ],
                                ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,2+}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{0,2,2+}' ),
                                                  ChannelID( 'n,Cl35->p,S35{0,2,2+}' ) ],
                                                [ 41. ], [ [ 42. ], [ 43. ], [ 44. ] ] ),
                                formalism, boundary )
        spingroup5 = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,3-}' ),
                                           neutron_pair, photon_pair, 0., None,
                                           zero_radii ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,2,3-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{1,2,3-}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii1 ) ],
                                ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{1,0,3-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,2,3-}' ),
                                                  ChannelID( 'n,Cl35->p,S35{1,2,3-}' ) ],
                                                [ 51. ], [ [ 52. ], [ 53. ], [ 54. ] ] ),
                                formalism, boundary )

        chunk = CompoundSystem( 1e-5, 2e+3,
                                [ spingroup0, spingroup1, spingroup2, spingroup3, spingroup4, spingroup5 ] )

        verify_chunk( self, chunk )

        chunk = CompoundSystem( 1e-5, 2e+3,
                                [ spingroup5, spingroup4, spingroup3, spingroup2, spingroup1, spingroup0 ] )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        neutron_mass = 1.00866491574

        photon = ParticleID.photon()
        neutron = ParticleID.neutron()
        proton = ParticleID.proton()
        cl35 = ParticleID( 'Cl35' )
        cl36 = ParticleID( 'Cl36[all]' )
        s35 = ParticleID( 'S35' )

        photon_pair = ParticlePair( Particle( photon, 0, 1, +1 ),
                                    Particle( cl36, 35.65932 * neutron_mass, 0, +1 ) )
        neutron_pair = ParticlePair( Particle( neutron, neutron_mass, 0.5, +1 ),
                                     Particle( cl35, 34.66845 * neutron_mass, 1.5, +1 ) )
        proton_pair = ParticlePair( Particle( proton, .9986235 * neutron_mass, 0.5, +1 ),
                                    Particle( s35, 34.66863 * neutron_mass, 1.5, +1 ) )

        zero_radii = ChannelRadii( 0., 0. )
        radii1 = ChannelRadii( 4.822220, 4.888750 )
        radii2 = ChannelRadii( 4.822220, 3.667980 )

        formalism = Formalism.ReichMoore
        boundary = BoundaryCondition.ShiftFactor

        spingroup0 = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ),
                                           neutron_pair, photon_pair, 0., None,
                                           zero_radii ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ) ],
                                ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ) ],
                                                [ 1. ], [ [ 2. ], [ 3. ] ] ),
                                formalism, boundary )
        spingroup1 = SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{1,0,1-}' ),
                                           neutron_pair, photon_pair, 0., None,
                                           zero_radii ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,1,1-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{1,1,1-}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->n,Cl35{1,2,1-}' ),
                                           neutron_pair, neutron_pair, 0., None,
                                           radii1 ),
                                  Channel( ChannelID( 'n,Cl35->p,S35{1,2,1-}' ),
                                           neutron_pair, proton_pair, 615220, None,
                                           radii1 ) ],
                                ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{1,0,0-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,1,0-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,1,1-}' ),
                                                  ChannelID( 'n,Cl35->n,Cl35{1,2,1-}' ),
                                                  ChannelID( 'n,Cl35->p,S35{1,2,1-}' ) ],
                                                [ 11. ], [ [ 12. ], [ 13. ], [ 14. ], [ 15. ], [ 16. ] ] ),
                                formalism, boundary )

        left = CompoundSystem( 1e-5, 2e+3, [ spingroup0 ] )
        equal = CompoundSystem( 1e-5, 2e+3, [ spingroup0 ]  )
        different = CompoundSystem( 1e-5, 2e+3, [ spingroup1 ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
