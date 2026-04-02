# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import Particle
from njoy.dryad.id import ParticleID

class Test_Particle( unittest.TestCase ) :
    """Unit test for the Particle class."""

    def test_component( self ) :

        neutron = Particle( id = ParticleID.neutron(), mass = 1.008664,
                            spin = 0.5, parity = +1 )

        self.assertEqual( ParticleID.neutron(), neutron.identifier )
        self.assertAlmostEqual( 1.008664, neutron.mass )
        self.assertAlmostEqual( 0.5, neutron.spin )
        self.assertEqual( 0, neutron.charge )
        self.assertEqual( 0, neutron.excited_state )
        self.assertEqual( +1, neutron.parity )

        proton = Particle( id = ParticleID.proton(), mass = 1.007276,
                           spin = 0.5, parity = +1 )

        self.assertEqual( ParticleID.proton(), proton.identifier )
        self.assertAlmostEqual( 1.007276, proton.mass )
        self.assertAlmostEqual( 0.5, proton.spin )
        self.assertEqual( 1, proton.charge )
        self.assertEqual( 0, proton.excited_state )
        self.assertEqual( +1, proton.parity )

        u235 = Particle( id = ParticleID( 'U235' ), mass = 235.0439299,
                         spin = 0., parity = +1 )

        self.assertEqual( ParticleID( 'U235' ), u235.identifier )
        self.assertAlmostEqual( 235.0439299, u235.mass )
        self.assertAlmostEqual( 0., u235.spin )
        self.assertEqual( 92, u235.charge )
        self.assertEqual( 0, u235.excited_state )
        self.assertEqual( +1, u235.parity )

        u235_e1 = Particle( id = ParticleID( 'U235_e1' ), mass = 235.0439299,
                            spin = 0., parity = +1 )

        self.assertEqual( ParticleID( 'U235_e1' ), u235_e1.identifier )
        self.assertAlmostEqual( 235.0439299, u235_e1.mass )
        self.assertAlmostEqual( 0., u235_e1.spin )
        self.assertEqual( 92, u235_e1.charge )
        self.assertEqual( 1, u235_e1.excited_state )
        self.assertEqual( +1, u235_e1.parity )

    def test_comparison( self ) :

        left = Particle( id = ParticleID.neutron(), mass = 1.008664,
                         spin = 0.5, parity = +1 )
        equal = Particle( id = ParticleID.neutron(), mass = 1.008664,
                          spin = 0.5, parity = +1 )
        different = Particle( id = ParticleID.proton(), mass = 1.007276,
                              spin = 0.5, parity = +1 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
