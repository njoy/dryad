# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.external.ame import MassEntry
from njoy.dryad.id import ParticleID

class Test_MassEntry( unittest.TestCase ) :
    """Unit test for the MassEntry class."""

    def test_component( self ) :

        # Hydrogen-1 (AME 2020 values)
        h1 = MassEntry( id = ParticleID( 'H1' ),
                        mass_excess = 7288971.064,
                        mass_excess_uncertainty = 0.013,
                        binding_energy = 0.0,
                        binding_energy_uncertainty = 0.0,
                        mass = 1.007825031898,
                        mass_uncertainty = 0.000000000014 )

        self.assertEqual( ParticleID( 'H1' ), h1.identifier )
        self.assertAlmostEqual( 7288971.064, h1.mass_excess )
        self.assertAlmostEqual( 0.013, h1.mass_excess_uncertainty )
        self.assertAlmostEqual( 0.0, h1.binding_energy )
        self.assertAlmostEqual( 0.0, h1.binding_energy_uncertainty )
        self.assertIsNone( h1.beta_decay_energy )
        self.assertIsNone( h1.beta_decay_energy_uncertainty )
        self.assertAlmostEqual( 1.007825031898, h1.atomic_mass )
        self.assertAlmostEqual( 0.000000000014, h1.atomic_mass_uncertainty )

    def test_setter_functions( self ) :

        chunk = MassEntry( id = ParticleID( 'H1' ),
                           mass_excess = 7288971.064,
                           mass_excess_uncertainty = 0.013,
                           binding_energy = 0.0,
                           binding_energy_uncertainty = 0.0,
                           mass = 1.007825031898,
                           mass_uncertainty = 0.000000000014 )

        # the identifier can be changed
        newidentifier = ParticleID( 'H2' )
        original = ParticleID( 'H1' )

        chunk.identifier = newidentifier

        self.assertEqual( newidentifier, chunk.identifier )

        chunk.identifier = original

        self.assertEqual( original, chunk.identifier )

        # the mass excess can be changed
        newvalue = 13135720.0  # H2 value
        original = 7288971.064

        chunk.mass_excess = newvalue

        self.assertEqual( newvalue, chunk.mass_excess )

        chunk.mass_excess = original

        self.assertEqual( original, chunk.mass_excess )

        # the mass excess uncertainty can be changed
        newuncertainty = 2.0
        original = 0.013

        chunk.mass_excess_uncertainty = newuncertainty

        self.assertEqual( newuncertainty, chunk.mass_excess_uncertainty )

        chunk.mass_excess_uncertainty = original

        self.assertEqual( original, chunk.mass_excess_uncertainty )

        # the binding energy can be changed
        newvalue = 1112283.0
        original = 0.0

        chunk.binding_energy = newvalue

        self.assertEqual( newvalue, chunk.binding_energy )

        chunk.binding_energy = original

        self.assertEqual( original, chunk.binding_energy )

        # the binding energy uncertainty can be changed
        newuncertainty = 0.5
        original = 0.0

        chunk.binding_energy_uncertainty = newuncertainty

        self.assertEqual( newuncertainty, chunk.binding_energy_uncertainty )

        chunk.binding_energy_uncertainty = original

        self.assertEqual( original, chunk.binding_energy_uncertainty )

        # the beta decay energy can be changed
        newvalue = 1000000.0
        original = None

        chunk.beta_decay_energy = newvalue

        self.assertEqual( newvalue, chunk.beta_decay_energy )

        chunk.beta_decay_energy = original

        self.assertEqual( original, chunk.beta_decay_energy )

        # the beta decay energy uncertainty can be changed
        newuncertainty = 1000.0
        original = None

        chunk.beta_decay_energy_uncertainty = newuncertainty

        self.assertEqual( newuncertainty, chunk.beta_decay_energy_uncertainty )

        chunk.beta_decay_energy_uncertainty = original

        self.assertEqual( original, chunk.beta_decay_energy_uncertainty )

        # the atomic mass can be changed
        newmass = 1.008
        original = 1.007825031898

        chunk.atomic_mass = newmass

        self.assertEqual( newmass, chunk.atomic_mass )

        chunk.atomic_mass = original

        self.assertEqual( original, chunk.atomic_mass )

        # the atomic mass uncertainty can be changed
        newuncertainty = 2.0e-10
        original = 0.000000000014

        chunk.atomic_mass_uncertainty = newuncertainty

        self.assertEqual( newuncertainty, chunk.atomic_mass_uncertainty )

        chunk.atomic_mass_uncertainty = original

        self.assertEqual( original, chunk.atomic_mass_uncertainty )

    def test_comparison( self ) :

        left = MassEntry( id = ParticleID( 'H1' ),
                          mass_excess = 7288971.064,
                          mass_excess_uncertainty = 0.013,
                          binding_energy = 0.0,
                          binding_energy_uncertainty = 0.0,
                          mass = 1.007825031898,
                          mass_uncertainty = 0.000000000014 )
        equal = MassEntry( id = ParticleID( 'H1' ),
                           mass_excess = 7288971.064,
                           mass_excess_uncertainty = 0.013,
                           binding_energy = 0.0,
                           binding_energy_uncertainty = 0.0,
                           mass = 1.007825031898,
                           mass_uncertainty = 0.000000000014 )
        different = MassEntry( id = ParticleID( 'H2' ),
                               mass_excess = 13135720.0,
                               mass_excess_uncertainty = 2.0,
                               binding_energy = 1112283.0,
                               binding_energy_uncertainty = 0.5,
                               mass = 2.01410177812,
                               mass_uncertainty = 4.0e-11 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()