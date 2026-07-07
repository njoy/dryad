# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import Particle
from njoy.dryad import ParticleDatabase
from njoy.dryad.id import ParticleID

def verify_chunk( self, chunk ) :

    self.assertEqual( 4, chunk.number_particles )

    self.assertEqual( True, chunk.has_particle( ParticleID( 'n' ) ) )
    self.assertEqual( True, chunk.has_particle( ParticleID( 'p' ) ) )
    self.assertEqual( True, chunk.has_particle( ParticleID( 'U235' ) ) )
    self.assertEqual( True, chunk.has_particle( ParticleID( 'U235_e1' ) ) )
    self.assertEqual( False, chunk.has_particle( ParticleID( 'U235_e2' ) ) )

    particle = chunk.particle( ParticleID( 'n' ) )
    self.assertEqual( ParticleID.neutron(), particle.identifier )
    self.assertAlmostEqual( 1.008664916060, particle.mass )
    self.assertAlmostEqual( 0.5, particle.spin )
    self.assertEqual( +1, particle.parity )
    self.assertIsNone( particle.energy )
    self.assertIsNone( particle.nuclear_mass )
    self.assertAlmostEqual( 0.00000000040, particle.mass_uncertainty )
    self.assertIsNone( particle.energy_uncertainty )
    self.assertIsNone( particle.nuclear_mass_uncertainty )

    particle = chunk.particle( ParticleID( 'p' ) )
    self.assertEqual( ParticleID.proton(), particle.identifier )
    self.assertAlmostEqual( 1.0072764665789, particle.mass )
    self.assertAlmostEqual( 0.5, particle.spin )
    self.assertEqual( +1, particle.parity )
    self.assertIsNone( particle.energy )
    self.assertIsNone( particle.nuclear_mass )
    self.assertAlmostEqual( 0.0000000000083, particle.mass_uncertainty )
    self.assertIsNone( particle.energy_uncertainty )
    self.assertIsNone( particle.nuclear_mass_uncertainty )

    particle = chunk.particle( ParticleID( 'U235' ) )
    self.assertEqual( ParticleID( 'U235' ), particle.identifier )
    self.assertAlmostEqual( 235.043928117, particle.mass )
    self.assertAlmostEqual( 3.5, particle.spin )
    self.assertEqual( -1, particle.parity )
    self.assertAlmostEqual( 0., particle.energy )
    self.assertIsNone( particle.nuclear_mass )
    self.assertAlmostEqual( 1.198e-6, particle.mass_uncertainty )
    self.assertIsNone( particle.energy_uncertainty )
    self.assertIsNone( particle.nuclear_mass_uncertainty )

    particle = chunk.particle( ParticleID( 'U235_e1' ) )
    self.assertEqual( ParticleID( 'U235_e1' ), particle.identifier )
    self.assertAlmostEqual( 235.043928117, particle.mass )
    self.assertAlmostEqual( 0.5, particle.spin )
    self.assertEqual( +1, particle.parity )
    self.assertAlmostEqual( 76., particle.energy )
    self.assertIsNone( particle.nuclear_mass )
    self.assertAlmostEqual( 1.198e-6, particle.mass_uncertainty )
    self.assertIsNone( particle.energy_uncertainty )
    self.assertIsNone( particle.nuclear_mass_uncertainty )

class Test_Particle( unittest.TestCase ) :
    """Unit test for the Particle class."""

    def test_component( self ) :

        chunk = ParticleDatabase( particles = [ Particle.default_particle( ParticleID( 'U235' ) ),
                                                Particle.default_particle( ParticleID( 'U235_e1' ) ),
                                                Particle.neutron(),
                                                Particle.proton() ] )

        verify_chunk( self, chunk )

        chunk = ParticleDatabase( identifiers = [ ParticleID( 'U235' ), ParticleID( 'U235_e1' ),
                                                  ParticleID.neutron(), ParticleID.neutron(), # duplicate, will be removed
                                                  ParticleID.proton(), ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
