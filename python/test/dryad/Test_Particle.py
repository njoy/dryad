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
        self.assertIsNone( neutron.energy )
        self.assertIsNone( neutron.mass_uncertainty )
        self.assertIsNone( neutron.energy_uncertainty )

        proton = Particle( id = ParticleID.proton(), mass = 1.007276,
                           spin = 0.5, parity = +1 )

        self.assertEqual( ParticleID.proton(), proton.identifier )
        self.assertAlmostEqual( 1.007276, proton.mass )
        self.assertAlmostEqual( 0.5, proton.spin )
        self.assertEqual( 1, proton.charge )
        self.assertEqual( 0, proton.excited_state )
        self.assertEqual( +1, proton.parity )
        self.assertIsNone( proton.energy )
        self.assertIsNone( proton.mass_uncertainty )
        self.assertIsNone( proton.energy_uncertainty )

        u235 = Particle( id = ParticleID( 'U235' ), mass = 235.0439299,
                         spin = 0., parity = +1, energy = 0 )

        self.assertEqual( ParticleID( 'U235' ), u235.identifier )
        self.assertAlmostEqual( 235.0439299, u235.mass )
        self.assertAlmostEqual( 0., u235.spin )
        self.assertEqual( 92, u235.charge )
        self.assertEqual( 0, u235.excited_state )
        self.assertEqual( +1, u235.parity )
        self.assertEqual( 0., u235.energy )
        self.assertIsNone( u235.mass_uncertainty )
        self.assertIsNone( u235.energy_uncertainty )

        u235_e1 = Particle( id = ParticleID( 'U235_e1' ), mass = 235.0439299,
                            spin = 0., parity = +1, energy = 1e+6,
                            energy_uncertainty = 1e+3 )

        self.assertEqual( ParticleID( 'U235_e1' ), u235_e1.identifier )
        self.assertAlmostEqual( 235.0439299, u235_e1.mass )
        self.assertAlmostEqual( 0., u235_e1.spin )
        self.assertEqual( 92, u235_e1.charge )
        self.assertEqual( 1, u235_e1.excited_state )
        self.assertEqual( +1, u235_e1.parity )
        self.assertEqual( 1e+6, u235_e1.energy )
        self.assertIsNone( u235_e1.mass_uncertainty )
        self.assertAlmostEqual( 1e+3, u235_e1.energy_uncertainty )


    def test_setter_functions( self ) :

        chunk = Particle( id = ParticleID( 'U235_e1' ), mass = 235.0439299,
                          spin = 0., parity = +1, energy = 1e+6,
                          mass_uncertainty = None, energy_uncertainty = 1e+3 )

        # the identifier can be changed
        newidentifier = ParticleID( 'U235' )
        original = ParticleID( 'U235_e1' )

        chunk.identifier = newidentifier

        self.assertEqual( newidentifier, chunk.identifier )

        chunk.identifier = original

        self.assertEqual( original, chunk.identifier )

        # the mass can be changed
        newmass = 235.
        original = 235.0439299

        chunk.mass = newmass

        self.assertEqual( newmass, chunk.mass )

        chunk.mass = original

        self.assertEqual( original, chunk.mass )

        # the mass uncertainty can be changed
        newuncertainty = 1
        original = None

        chunk.mass_uncertainty = newuncertainty

        self.assertEqual( newuncertainty, chunk.mass_uncertainty )

        chunk.mass_uncertainty = original

        self.assertEqual( original, chunk.mass_uncertainty )

        # the energy can be changed
        newenergy = 1e+6
        original = 1e+6

        chunk.energy = newenergy

        self.assertEqual( newenergy, chunk.energy )

        chunk.energy = original

        self.assertEqual( original, chunk.energy )

        # the energy uncertainty can be changed
        newuncertainty = None
        original = 1e+3

        chunk.energy_uncertainty = newuncertainty

        self.assertEqual( newuncertainty, chunk.energy_uncertainty )

        chunk.energy_uncertainty = original

        self.assertEqual( original, chunk.energy_uncertainty )

        # the spin can be changed
        newspin = 0.5
        original = 0

        chunk.spin = newspin

        self.assertEqual( newspin, chunk.spin )

        chunk.spin = original

        self.assertEqual( original, chunk.spin )

        # the parity can be changed
        newparity = -1
        original = +1

        chunk.parity = newparity

        self.assertEqual( newparity, chunk.parity )

        chunk.parity = original

        self.assertEqual( original, chunk.parity )

    def test_comparison( self ) :

        left = Particle( id = ParticleID.neutron(), mass = 1.008664,
                         spin = 0.5, parity = +1 )
        equal = Particle( id = ParticleID.neutron(), mass = 1.008664,
                          spin = 0.5, parity = +1 )
        different = Particle( id = ParticleID( 'U235_e1' ), mass = 235.0439299,
                              spin = 0., parity = +1, energy = 1e+6,
                              mass_uncertainty = None, energy_uncertainty = 1e+3 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
