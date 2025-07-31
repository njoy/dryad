# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import IncoherentDistributionData
from dryad import DistributionDataType
from dryad import ReferenceFrame
from dryad import InterpolationType
from dryad import TabulatedScatteringFunction

def verify_chunk( self, chunk ) :

    self.assertEqual( DistributionDataType.Incoherent, chunk.type )
    self.assertEqual( ReferenceFrame.CentreOfMass, chunk.frame )

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

class Test_dryad_IncoherentDistributionData( unittest.TestCase ) :
    """Unit test for the IncoherentDistributionData class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk = IncoherentDistributionData( frame = ReferenceFrame.CentreOfMass,
                                            scattering = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 2., 1. ] ) )

        verify_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = IncoherentDistributionData( frame = ReferenceFrame.CentreOfMass,
                                            scattering = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 2., 1. ] ) )

        # the reference frame can be changed
        newframe = ReferenceFrame.Laboratory
        original = ReferenceFrame.CentreOfMass

        chunk.frame = newframe

        self.assertEqual( newframe, chunk.frame )

        chunk.frame = original

        verify_chunk( self, chunk )

        # the scattering function can be changed
        newfunction = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 4., 2. ] )
        original = TabulatedScatteringFunction( [ 1., 1e+6 ], [ 2., 1. ] )

        chunk.scattering_function = newfunction

        self.assertEqual( newfunction, chunk.scattering_function )

        chunk.scattering_function = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = IncoherentDistributionData( ReferenceFrame.CentreOfMass,
                                           TabulatedScatteringFunction( [ 0., 1e+6 ], [ 2., 1. ] ) )
        equal = IncoherentDistributionData( ReferenceFrame.CentreOfMass,
                                            TabulatedScatteringFunction( [ 0., 1e+6 ], [ 2., 1. ] ) )
        different = IncoherentDistributionData( ReferenceFrame.CentreOfMass,
                                                TabulatedScatteringFunction( [ 0., 1e+7 ], [ 2., 1. ] ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
