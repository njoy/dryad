# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.resonances import TabulatedRadius
from njoy.dryad.resonances import ChannelRadii

class Test_ChannelRadii( unittest.TestCase ) :
    """Unit test for the ChannelRadii class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk = ChannelRadii( radius = .1 )

        self.assertEqual( False, chunk.has_shift_factor_radius )
        self.assertEqual( False, chunk.has_phase_shift_radius )
        self.assertAlmostEqual( .1, chunk.penetrability_radius )
        self.assertIsNone( None, chunk.shift_factor_radius )
        self.assertIsNone( None, chunk.phase_shift_radius )

        self.assertAlmostEqual( .1, chunk.calculate_penetrability_radius( energy = 1e-5 ) )
        self.assertAlmostEqual( .1, chunk.calculate_shift_factor_radius( energy = 1e-5 ) )
        self.assertAlmostEqual( .1, chunk.calculate_phase_shift_radius( energy = 1e-5 ) )

        # the data is given explicitly
        chunk = ChannelRadii( true_radius = .2, effective_radius = .3 )

        self.assertEqual( False, chunk.has_shift_factor_radius )
        self.assertEqual( True, chunk.has_phase_shift_radius )
        self.assertAlmostEqual( .2, chunk.penetrability_radius )
        self.assertAlmostEqual( None, chunk.shift_factor_radius )
        self.assertAlmostEqual( .3, chunk.phase_shift_radius )

        self.assertAlmostEqual( .2, chunk.calculate_penetrability_radius( energy = 1e-5 ) )
        self.assertAlmostEqual( .2, chunk.calculate_shift_factor_radius( energy = 1e-5 ) )
        self.assertAlmostEqual( .3, chunk.calculate_phase_shift_radius( energy = 1e-5 ) )

        # the data is given explicitly
        chunk = ChannelRadii( penetrability = .4, shift_factor = .5, phase_shift = .6 )

        self.assertEqual( True, chunk.has_shift_factor_radius )
        self.assertEqual( True, chunk.has_phase_shift_radius )
        self.assertAlmostEqual( .4, chunk.penetrability_radius )
        self.assertAlmostEqual( .5, chunk.shift_factor_radius )
        self.assertAlmostEqual( .6, chunk.phase_shift_radius )

        self.assertAlmostEqual( .4, chunk.calculate_penetrability_radius( energy = 1e-5 ) )
        self.assertAlmostEqual( .5, chunk.calculate_shift_factor_radius( energy = 1e-5 ) )
        self.assertAlmostEqual( .6, chunk.calculate_phase_shift_radius( energy = 1e-5 ) )

    def test_curation( self ) :

        # the data is given explicitly
        chunk = ChannelRadii( penetrability = TabulatedRadius( [ 1e-5, 1., 1., 1., 2e+7 ], [ 0.4, 0.4, 0.45, 0.5, 0.5 ] ),   # <-- discontinuity with 3 points
                              shift_factor = TabulatedRadius( [ 1e-5, 2., 2., 2., 2e+7 ], [ 0.5, 0.5, 0.55, 0.6, 0.6 ] ),    # <-- discontinuity with 3 points
                              phase_shift = TabulatedRadius( [ 1e-5, 3., 3., 3., 2e+7 ], [ 0.6, 0.6, 0.65, 0.7, 0.7 ] ) )    # <-- discontinuity with 3 points

        # the tabulated data is not curated
        self.assertEqual( False, chunk.penetrability_radius.is_curated )
        self.assertEqual( False, chunk.shift_factor_radius.is_curated )
        self.assertEqual( False, chunk.phase_shift_radius.is_curated )

        # the tabulated data can be curated
        chunk.curate()

        self.assertEqual( True, chunk.penetrability_radius.is_curated )
        self.assertEqual( True, chunk.shift_factor_radius.is_curated )
        self.assertEqual( True, chunk.phase_shift_radius.is_curated )

        # the data is given explicitly using constant radii
        chunk = ChannelRadii( .1 )

        # curating does not change anything
        chunk.curate()

        self.assertAlmostEqual( .1, chunk.penetrability_radius )
        self.assertEqual( None, chunk.shift_factor_radius )
        self.assertEqual( None, chunk.phase_shift_radius )
        self.assertAlmostEqual( .1, chunk.calculate_penetrability_radius( energy = 1e-5 ) )

    def test_setter_functions( self ) :

        chunk = ChannelRadii( .1 )

        # the penetrability radius can be changed
        newradius = .3
        original = .1

        chunk.penetrability_radius = newradius

        self.assertEqual( newradius, chunk.penetrability_radius )

        chunk.penetrability_radius = original

        self.assertEqual( original, chunk.penetrability_radius )

        # the shift factor radius can be changed
        newradius = .3
        original = None

        chunk.shift_factor_radius = newradius

        self.assertEqual( newradius, chunk.shift_factor_radius )

        chunk.shift_factor_radius = original

        self.assertEqual( original, chunk.shift_factor_radius )

        # the phase shift radius can be changed
        newradius = .3
        original = None

        chunk.phase_shift_radius = newradius

        self.assertEqual( newradius, chunk.phase_shift_radius )

        chunk.phase_shift_radius = original

        self.assertEqual( original, chunk.phase_shift_radius )

    def test_comparison( self ) :

        left = ChannelRadii( .1 )
        equal = ChannelRadii( .1 )
        different = ChannelRadii( .2 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
