# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import Particle
from njoy.dryad import ParticleDatabase
from njoy.dryad.id import ParticleID

class Test_Particle( unittest.TestCase ) :
    """Unit test for the Particle class."""

    def test_component( self ) :

        chunk = ParticleDatabase( particles = [ Particle( ParticleID( 'n' ), 1.008664, 0.5, +1 ),
                                                Particle( ParticleID( 'p' ), 1.007276, 0.5, +1 ),
                                                Particle( ParticleID( 'U235' ), 235.0439299, 0., +1, 0. ),
                                                Particle( ParticleID( 'U235_e1' ), 235.0439299, 0., +1, 1e+6, None, 1e+3 ) ] )

        self.assertEqual( 4, chunk.number_particles )

        self.assertEqual( True, chunk.has_particle( ParticleID( 'n' ) ) )
        self.assertEqual( True, chunk.has_particle( ParticleID( 'p' ) ) )
        self.assertEqual( True, chunk.has_particle( ParticleID( 'U235' ) ) )
        self.assertEqual( True, chunk.has_particle( ParticleID( 'U235_e1' ) ) )
        self.assertEqual( False, chunk.has_particle( ParticleID( 'U235_e2' ) ) )

        neutron = chunk.particle( ParticleID( 'n' ) )
        self.assertEqual( ParticleID.neutron(), neutron.identifier )
        self.assertAlmostEqual( 1.008664, neutron.mass )
        self.assertAlmostEqual( 0.5, neutron.spin )
        self.assertEqual( 0, neutron.charge )
        self.assertEqual( 0, neutron.excited_state )
        self.assertEqual( +1, neutron.parity )
        self.assertIsNone( neutron.energy )
        self.assertIsNone( neutron.mass_uncertainty )
        self.assertIsNone( neutron.energy_uncertainty )

        proton = chunk.particle( ParticleID( 'p' ) )
        self.assertEqual( ParticleID.proton(), proton.identifier )
        self.assertAlmostEqual( 1.007276, proton.mass )
        self.assertAlmostEqual( 0.5, proton.spin )
        self.assertEqual( 1, proton.charge )
        self.assertEqual( 0, proton.excited_state )
        self.assertEqual( +1, proton.parity )
        self.assertIsNone( proton.energy )
        self.assertIsNone( proton.mass_uncertainty )
        self.assertIsNone( proton.energy_uncertainty )

        u235 = chunk.particle( ParticleID( 'U235' ) )
        self.assertEqual( ParticleID( 'U235' ), u235.identifier )
        self.assertAlmostEqual( 235.0439299, u235.mass )
        self.assertAlmostEqual( 0., u235.spin )
        self.assertEqual( 92, u235.charge )
        self.assertEqual( 0, u235.excited_state )
        self.assertEqual( +1, u235.parity )
        self.assertEqual( 0., u235.energy )
        self.assertIsNone( u235.mass_uncertainty )
        self.assertIsNone( u235.energy_uncertainty )

        u235_e1 = chunk.particle( ParticleID( 'U235_e1' ) )
        self.assertEqual( ParticleID( 'U235_e1' ), u235_e1.identifier )
        self.assertAlmostEqual( 235.0439299, u235_e1.mass )
        self.assertAlmostEqual( 0., u235_e1.spin )
        self.assertEqual( 92, u235_e1.charge )
        self.assertEqual( 1, u235_e1.excited_state )
        self.assertEqual( +1, u235_e1.parity )
        self.assertEqual( 1e+6, u235_e1.energy )
        self.assertIsNone( u235_e1.mass_uncertainty )
        self.assertAlmostEqual( 1e+3, u235_e1.energy_uncertainty )

if __name__ == '__main__' :

    unittest.main()
