# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.resonances import ParticlePair
from dryad.resonances import Particle
from dryad.id import ParticleID

class Test_dryad_resonances_Particle( unittest.TestCase ) :
    """Unit test for the Particle class."""

    def test_component( self ) :

        neutron = Particle( id = ParticleID.neutron(), mass = 1.008664,
                            spin = 0.5, parity = +1 )
        u235 = Particle( id = ParticleID( 'U235' ), mass = 235.0439299,
                         spin = 0., parity = +1 )

        pair = ParticlePair( neutron, u235 )

        self.assertEqual( ParticleID.neutron(), pair.particle.identifier )
        self.assertAlmostEqual( 1.008664, pair.particle.mass )
        self.assertAlmostEqual( 0.5, pair.particle.spin )
        self.assertEqual( 0, pair.particle.charge )
        self.assertEqual( +1, pair.particle.parity )

        self.assertEqual( ParticleID( 'U235' ), pair.residual.identifier )
        self.assertAlmostEqual( 235.0439299, pair.residual.mass )
        self.assertAlmostEqual( 0., pair.residual.spin )
        self.assertEqual( 92, pair.residual.charge )
        self.assertEqual( +1, pair.residual.parity )

        self.assertAlmostEqual( 235.0439299 / ( 1.008664 + 235.0439299 ), pair.mass_ratio )
        self.assertAlmostEqual( 1.008664 * 235.0439299 / ( 1.008664 + 235.0439299 ), pair.reduced_mass )

    def test_comparison( self ) :

        neutron = Particle( id = ParticleID.neutron(), mass = 1.008664,
                            spin = 0.5, parity = +1 )
        proton = Particle( id = ParticleID.neutron(), mass = 1.007276,
                           spin = 0.5, parity = +1 )
        u235 = Particle( id = ParticleID( 'U235' ), mass = 235.0439299,
                         spin = 0., parity = +1 )

        left = ParticlePair( neutron, u235 )
        equal = ParticlePair( neutron, u235 )
        different = ParticlePair( proton, u235 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
