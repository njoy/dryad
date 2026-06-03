# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.external.ripl3 import Levels
from njoy.dryad.id import ParticleID

class Test_Levels( unittest.TestCase ) :
    """Unit test for the Levels class."""

    def test_predefined_particles( self ) :

        # photon
        photon = Levels.level( ParticleID.photon() )

        self.assertEqual( ParticleID.photon(), photon.identifier )
        self.assertIsNone( photon.energy )
        self.assertAlmostEqual( 1.0, photon.spin )
        self.assertEqual( -1, photon.parity )
        self.assertIsNone( photon.half_life )

        # neutron
        neutron = Levels.level( ParticleID.neutron() )

        self.assertEqual( ParticleID.neutron(), neutron.identifier )
        self.assertIsNone( neutron.energy )
        self.assertAlmostEqual( 0.5, neutron.spin )
        self.assertEqual( 1, neutron.parity )
        self.assertIsNone( neutron.half_life )

        # proton
        proton = Levels.level( ParticleID.proton() )

        self.assertEqual( ParticleID.proton(), proton.identifier )
        self.assertIsNone( proton.energy )
        self.assertAlmostEqual( 0.5, proton.spin )
        self.assertEqual( 1, proton.parity )
        self.assertIsNone( proton.half_life )

        # deuteron
        deuteron = Levels.level( ParticleID.deuteron() )

        self.assertEqual( ParticleID.deuteron(), deuteron.identifier )
        self.assertIsNone( deuteron.energy )
        self.assertAlmostEqual( 1.0, deuteron.spin )
        self.assertEqual( 1, deuteron.parity )
        self.assertIsNone( deuteron.half_life )

        # triton
        triton = Levels.level( ParticleID.triton() )

        self.assertEqual( ParticleID.triton(), triton.identifier )
        self.assertIsNone( triton.energy )
        self.assertAlmostEqual( 0.5, triton.spin )
        self.assertEqual( 1, triton.parity )
        self.assertIsNone( triton.half_life )

        # helion
        helion = Levels.level( ParticleID.helion() )

        self.assertEqual( ParticleID.helion(), helion.identifier )
        self.assertIsNone( helion.energy )
        self.assertAlmostEqual( 0.5, helion.spin )
        self.assertEqual( 1, helion.parity )
        self.assertIsNone( helion.half_life )

        # alpha
        alpha = Levels.level( ParticleID.alpha() )

        self.assertEqual( ParticleID.alpha(), alpha.identifier )
        self.assertIsNone( alpha.energy )
        self.assertAlmostEqual( 0.0, alpha.spin )
        self.assertEqual( 1, alpha.parity )
        self.assertIsNone( alpha.half_life )

    def test_non_existent_particle( self ) :

        u235 = ParticleID( 'U235' )

        with self.assertRaises( Exception ) :

            Levels.level( u235 )

if __name__ == '__main__' :

    unittest.main()
