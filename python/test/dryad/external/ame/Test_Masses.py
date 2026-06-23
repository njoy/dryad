# standard imports
import unittest
import os
import sys

# third party imports

# local imports
from njoy.dryad.external.ame import Masses
from njoy.dryad.id import ParticleID

class Test_Masses( unittest.TestCase ) :
    """Unit test for the Masses class."""

    def test_predefined_particles( self ) :

        self.assertEqual(    0, Masses.size() )

        data = Masses.entry( ParticleID( 'H1' ) )
        self.assertEqual( ParticleID( 'H1' ), data.identifier )
        self.assertAlmostEqual( 7288971.064, data.mass_excess )
        self.assertAlmostEqual( 0.013, data.mass_excess_uncertainty )
        self.assertAlmostEqual( 0.0, data.binding_energy )
        self.assertAlmostEqual( 0.0, data.binding_energy_uncertainty )
        self.assertIsNone( data.beta_decay_energy )
        self.assertIsNone( data.beta_decay_energy_uncertainty )
        self.assertAlmostEqual( 1.007825031898, data.atomic_mass )
        self.assertAlmostEqual( 0.000000000014, data.atomic_mass_uncertainty )

        self.assertEqual( 3557, Masses.size() )

        data = Masses.entry( ParticleID( 'He3' ) )
        self.assertEqual( ParticleID( 'He3' ), data.identifier )
        self.assertAlmostEqual( 14931218.88, data.mass_excess )
        self.assertAlmostEqual( 0.06, data.mass_excess_uncertainty )
        self.assertAlmostEqual( 2572680.44, data.binding_energy )
        self.assertAlmostEqual( 0.15, data.binding_energy_uncertainty )
        self.assertAlmostEqual( -13736000, data.beta_decay_energy )
        self.assertAlmostEqual( 2000000, data.beta_decay_energy_uncertainty )
        self.assertAlmostEqual( 3.01602932197, data.atomic_mass )
        self.assertAlmostEqual( 0.00000000006, data.atomic_mass_uncertainty )

if __name__ == '__main__' :

    unittest.main()
