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

        particle = Particle( id = ParticleID.neutron(), mass = 1.008664,
                             spin = 0.5, parity = +1 )

        self.assertEqual( ParticleID.neutron(), particle.identifier )
        self.assertAlmostEqual( 1.008664, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertIsNone( particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle( id = ParticleID.proton(), mass = 1.007276,
                             spin = 0.5, parity = +1 )

        self.assertEqual( ParticleID.proton(), particle.identifier )
        self.assertAlmostEqual( 1.007276, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertIsNone( particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle( id = ParticleID( 'U235' ), mass = 235.0439299,
                             spin = 0., parity = +1, energy = 0 )

        self.assertEqual( ParticleID( 'U235' ), particle.identifier )
        self.assertAlmostEqual( 235.0439299, particle.mass )
        self.assertAlmostEqual( 0., particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertEqual( 0., particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertIsNone( particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle( id = ParticleID( 'U235_e1' ), mass = 235.0439299,
                             spin = 0., parity = +1, energy = 1e+6,
                             energy_uncertainty = 1e+3 )

        self.assertEqual( ParticleID( 'U235_e1' ), particle.identifier )
        self.assertAlmostEqual( 235.0439299, particle.mass )
        self.assertAlmostEqual( 0., particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertEqual( 1e+6, particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertIsNone( particle.mass_uncertainty )
        self.assertAlmostEqual( 1e+3, particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        # default particle instances

        particle = Particle.photon()
        self.assertEqual( ParticleID.photon(), particle.identifier )
        self.assertAlmostEqual( 0., particle.mass )
        self.assertAlmostEqual( 1.0, particle.spin )
        self.assertEqual( -1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0., particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.electron()
        self.assertEqual( ParticleID.electron(), particle.identifier )
        self.assertAlmostEqual( 5.485799090441e-4, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000097e-4, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.positron()
        self.assertEqual( ParticleID.positron(), particle.identifier )
        self.assertAlmostEqual( 5.485799090441e-4, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( -1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000097e-4, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.neutron()
        self.assertEqual( ParticleID.neutron(), particle.identifier )
        self.assertAlmostEqual( 1.008664916060, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.00000000040, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.proton()
        self.assertEqual( ParticleID.proton(), particle.identifier )
        self.assertAlmostEqual( 1.0072764665789, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.0000000000083, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.deuteron()
        self.assertEqual( ParticleID.deuteron(), particle.identifier )
        self.assertAlmostEqual( 2.013553212544, particle.mass )
        self.assertAlmostEqual( 1.0, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000015, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.triton()
        self.assertEqual( ParticleID.triton(), particle.identifier )
        self.assertAlmostEqual( 3.015500715970, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.00000000010, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.helion()
        self.assertEqual( ParticleID.helion(), particle.identifier )
        self.assertAlmostEqual( 3.014932246932, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000074, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.alpha()
        self.assertEqual( ParticleID.alpha(), particle.identifier )
        self.assertAlmostEqual( 4.001506179129, particle.mass )
        self.assertAlmostEqual( 0.0, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000062, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.photon() )
        self.assertEqual( ParticleID.photon(), particle.identifier )
        self.assertAlmostEqual( 0., particle.mass )
        self.assertAlmostEqual( 1.0, particle.spin )
        self.assertEqual( -1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0., particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.electron() )
        self.assertEqual( ParticleID.electron(), particle.identifier )
        self.assertAlmostEqual( 5.485799090441e-4, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000097e-4, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.positron() )
        self.assertEqual( ParticleID.positron(), particle.identifier )
        self.assertAlmostEqual( 5.485799090441e-4, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( -1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000097e-4, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.neutron() )
        self.assertEqual( ParticleID.neutron(), particle.identifier )
        self.assertAlmostEqual( 1.008664916060, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.00000000040, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.proton() )
        self.assertEqual( ParticleID.proton(), particle.identifier )
        self.assertAlmostEqual( 1.0072764665789, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.0000000000083, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.deuteron() )
        self.assertEqual( ParticleID.deuteron(), particle.identifier )
        self.assertAlmostEqual( 2.013553212544, particle.mass )
        self.assertAlmostEqual( 1.0, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000015, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.triton() )
        self.assertEqual( ParticleID.triton(), particle.identifier )
        self.assertAlmostEqual( 3.015500715970, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.00000000010, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.helion() )
        self.assertEqual( ParticleID.helion(), particle.identifier )
        self.assertAlmostEqual( 3.014932246932, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000074, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID.alpha() )
        self.assertEqual( ParticleID.alpha(), particle.identifier )
        self.assertAlmostEqual( 4.001506179129, particle.mass )
        self.assertAlmostEqual( 0.0, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 0.000000000062, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID( 'U235' ) )
        self.assertEqual( ParticleID( 'U235' ), particle.identifier )
        self.assertAlmostEqual( 235.043928117, particle.mass )
        self.assertAlmostEqual( 3.5, particle.spin )
        self.assertEqual( -1, particle.parity )
        self.assertAlmostEqual( 0., particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 1.198e-6, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID( 'U235_e1' ) )
        self.assertEqual( ParticleID( 'U235_e1' ), particle.identifier )
        self.assertAlmostEqual( 235.043928117, particle.mass )
        self.assertAlmostEqual( 0.5, particle.spin )
        self.assertEqual( +1, particle.parity )
        self.assertAlmostEqual( 76., particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertAlmostEqual( 1.198e-6, particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID( 'H' ) )
        self.assertEqual( ParticleID( 'H' ), particle.identifier )
        self.assertIsNone( particle.mass )
        self.assertIsNone( particle.spin )
        self.assertIsNone( particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertIsNone( particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

        particle = Particle.default_particle( ParticleID( 'H{1s1/2}' ) )
        self.assertEqual( ParticleID( 'H' ), particle.identifier )
        self.assertIsNone( particle.mass )
        self.assertIsNone( particle.spin )
        self.assertIsNone( particle.parity )
        self.assertIsNone( particle.energy )
        self.assertIsNone( particle.nuclear_mass )
        self.assertIsNone( particle.mass_uncertainty )
        self.assertIsNone( particle.energy_uncertainty )
        self.assertIsNone( particle.nuclear_mass_uncertainty )

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

        # the nuclear mass can be changed
        newmass = 235.
        original = None

        chunk.nuclear_mass = newmass

        self.assertEqual( newmass, chunk.nuclear_mass )

        chunk.nuclear_mass = original

        self.assertEqual( original, chunk.nuclear_mass )

        # the nuclear mass uncertainty can be changed
        newuncertainty = 1
        original = None

        chunk.nuclear_mass_uncertainty = newuncertainty

        self.assertEqual( newuncertainty, chunk.nuclear_mass_uncertainty )

        chunk.nuclear_mass_uncertainty = original

        self.assertEqual( original, chunk.nuclear_mass_uncertainty )

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
