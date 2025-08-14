# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import CoherentDistributionData
from dryad import DistributionDataType
from dryad import ReferenceFrame
from dryad import InterpolationType
from dryad import TabulatedScatteringFunction
from dryad import TabulatedFormFactor

def verify_chunk_without_anomolous_form_factor( self, chunk ) :

    self.assertEqual( DistributionDataType.Coherent, chunk.type )
    self.assertEqual( ReferenceFrame.CentreOfMass, chunk.frame )
    self.assertEqual( False, chunk.has_anomolous_form_factor )

    self.assertAlmostEqual( 1.  , chunk.scattering_function.lower_inverse_length_limit )
    self.assertAlmostEqual( 1e+6, chunk.scattering_function.upper_inverse_length_limit )
    self.assertEqual( 2, chunk.scattering_function.number_points )
    self.assertEqual( 1, chunk.scattering_function.number_regions )
    self.assertEqual( 2, len( chunk.scattering_function.inverse_lengths ) )
    self.assertEqual( 2, len( chunk.scattering_function.values ) )
    self.assertEqual( 1, len( chunk.scattering_function.boundaries ) )
    self.assertEqual( 1, len( chunk.scattering_function.interpolants ) )
    self.assertAlmostEqual( 1.  , chunk.scattering_function.inverse_lengths[0] )
    self.assertAlmostEqual( 1e+6, chunk.scattering_function.inverse_lengths[1] )
    self.assertAlmostEqual( 2., chunk.scattering_function.values[0] )
    self.assertAlmostEqual( 1., chunk.scattering_function.values[1] )
    self.assertEqual( 1, chunk.scattering_function.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.scattering_function.interpolants[0] )
    self.assertEqual( True, chunk.scattering_function.is_linearised )

    self.assertAlmostEqual( None, chunk.real_anomolous_form_factor )
    self.assertAlmostEqual( None, chunk.imaginary_anomolous_form_factor )

def verify_chunk_with_anomolous_form_factor( self, chunk ) :

    self.assertEqual( DistributionDataType.Coherent, chunk.type )
    self.assertEqual( ReferenceFrame.CentreOfMass, chunk.frame )
    self.assertEqual( True, chunk.has_anomolous_form_factor )

    self.assertAlmostEqual( 1.  , chunk.scattering_function.lower_inverse_length_limit )
    self.assertAlmostEqual( 1e+6, chunk.scattering_function.upper_inverse_length_limit )
    self.assertEqual( 2, chunk.scattering_function.number_points )
    self.assertEqual( 1, chunk.scattering_function.number_regions )
    self.assertEqual( 2, len( chunk.scattering_function.inverse_lengths ) )
    self.assertEqual( 2, len( chunk.scattering_function.values ) )
    self.assertEqual( 1, len( chunk.scattering_function.boundaries ) )
    self.assertEqual( 1, len( chunk.scattering_function.interpolants ) )
    self.assertAlmostEqual( 1.  , chunk.scattering_function.inverse_lengths[0] )
    self.assertAlmostEqual( 1e+6, chunk.scattering_function.inverse_lengths[1] )
    self.assertAlmostEqual( 2., chunk.scattering_function.values[0] )
    self.assertAlmostEqual( 1., chunk.scattering_function.values[1] )
    self.assertEqual( 1, chunk.scattering_function.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.scattering_function.interpolants[0] )
    self.assertEqual( True, chunk.scattering_function.is_linearised )

    factor = chunk.real_anomolous_form_factor
    self.assertAlmostEqual( 1., factor.lower_energy_limit )
    self.assertAlmostEqual( 2e+7, factor.upper_energy_limit )
    self.assertEqual( 2, factor.number_points )
    self.assertEqual( 1, factor.number_regions )
    self.assertEqual( 2, len( factor.energies ) )
    self.assertEqual( 2, len( factor.values ) )
    self.assertEqual( 1, len( factor.boundaries ) )
    self.assertEqual( 1, len( factor.interpolants ) )
    self.assertAlmostEqual( 1., factor.energies[0] )
    self.assertAlmostEqual( 2e+7, factor.energies[1] )
    self.assertAlmostEqual( 1., factor.values[0] )
    self.assertAlmostEqual( 2., factor.values[1] )
    self.assertEqual( 1, factor.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, factor.interpolants[0] )
    self.assertEqual( True, factor.is_linearised )

    factor = chunk.imaginary_anomolous_form_factor
    self.assertAlmostEqual( 1., factor.lower_energy_limit )
    self.assertAlmostEqual( 2e+7, factor.upper_energy_limit )
    self.assertEqual( 2, factor.number_points )
    self.assertEqual( 1, factor.number_regions )
    self.assertEqual( 2, len( factor.energies ) )
    self.assertEqual( 2, len( factor.values ) )
    self.assertEqual( 1, len( factor.boundaries ) )
    self.assertEqual( 1, len( factor.interpolants ) )
    self.assertAlmostEqual( 1., factor.energies[0] )
    self.assertAlmostEqual( 2e+7, factor.energies[1] )
    self.assertAlmostEqual( 0.5, factor.values[0] )
    self.assertAlmostEqual( 0.6, factor.values[1] )
    self.assertEqual( 1, factor.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, factor.interpolants[0] )
    self.assertEqual( True, factor.is_linearised )

class Test_dryad_CoherentDistributionData( unittest.TestCase ) :
    """Unit test for the CoherentDistributionData class."""

    def test_component( self ) :

        # the data is given explicitly without an anomolous form factor
        chunk = CoherentDistributionData( frame = ReferenceFrame.CentreOfMass,
                                          scattering = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 2., 1. ] ) )

        verify_chunk_without_anomolous_form_factor( self, chunk )

        # the data is given explicitly with an anomolous form factor
        chunk = CoherentDistributionData( frame = ReferenceFrame.CentreOfMass,
                                          scattering = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 2., 1. ] ),
                                          real = TabulatedFormFactor( [ 1., 2e+7 ], [ 1., 2. ] ),
                                          imaginary = TabulatedFormFactor( [ 1., 2e+7 ], [ 0.5, 0.6 ] ) )

        verify_chunk_with_anomolous_form_factor( self, chunk )

    def test_setter_functions( self ) :

        chunk = CoherentDistributionData( frame = ReferenceFrame.CentreOfMass,
                                          scattering = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 2., 1. ] ) )

        # the referenceframe can be changed
        newframe = ReferenceFrame.Laboratory
        original = ReferenceFrame.CentreOfMass

        chunk.frame = newframe

        self.assertEqual( newframe, chunk.frame )

        chunk.frame = original

        verify_chunk_without_anomolous_form_factor( self, chunk )

        # the scattering function can be changed
        newfunction = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 4., 2. ] )
        original = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 2., 1. ] )

        chunk.scattering_function = newfunction

        self.assertEqual( newfunction, chunk.scattering_function )

        chunk.scattering_function = original

        verify_chunk_without_anomolous_form_factor( self, chunk )

        # the form factor can be changed
        newrealfactor = TabulatedFormFactor( [ 1., 2e+7 ], [ 1., 2. ] )
        newimaginaryfactor = TabulatedFormFactor( [ 1., 2e+7 ], [ 0.5, 0.6 ] )
        original = None

        chunk.real_anomolous_form_factor = newrealfactor
        chunk.imaginary_anomolous_form_factor = newimaginaryfactor

        verify_chunk_with_anomolous_form_factor( self, chunk )

        chunk.real_anomolous_form_factor = original
        chunk.imaginary_anomolous_form_factor = original

        verify_chunk_without_anomolous_form_factor( self, chunk )

    def test_comparison( self ) :

        left = CoherentDistributionData( ReferenceFrame.CentreOfMass,
                                         TabulatedScatteringFunction( [ 0., 1e+6 ], [ 2., 1. ] ) )
        equal = CoherentDistributionData( ReferenceFrame.CentreOfMass,
                                          TabulatedScatteringFunction( [ 0., 1e+6 ], [ 2., 1. ] ) )
        different = CoherentDistributionData( ReferenceFrame.CentreOfMass,
                                              TabulatedScatteringFunction( [ 0., 1e+7 ], [ 2., 1. ] ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
