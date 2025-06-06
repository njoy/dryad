# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TwoBodyDistributionData
from dryad import DistributionDataType
from dryad import ReferenceFrame
from dryad import InterpolationType
from dryad import IsotropicAngularDistributions
from dryad import LegendreAngularDistribution
from dryad import LegendreAngularDistributions
from dryad import TabulatedAngularDistribution
from dryad import TabulatedAngularDistributions

class Test_dryad_TwoBodyDistributionData( unittest.TestCase ) :
    """Unit test for the TwoBodyDistributionData class."""

    def test_component( self ) :

        def verify_isotropic_chunk( self, chunk ) :

            self.assertEqual( DistributionDataType.TwoBody, chunk.type )
            self.assertEqual( ReferenceFrame.CentreOfMass, chunk.frame )

            self.assertEqual( True, isinstance( chunk.angle, IsotropicAngularDistributions ) )

        def verify_legendre_chunk( self, chunk ) :

            self.assertEqual( DistributionDataType.TwoBody, chunk.type )
            self.assertEqual( ReferenceFrame.CentreOfMass, chunk.frame )

            self.assertEqual( True, isinstance( chunk.angle, LegendreAngularDistributions ) )

            self.assertEqual( 2, chunk.angle.number_points )
            self.assertEqual( 1, chunk.angle.number_regions )
            self.assertEqual( 2, len( chunk.angle.grid ) )
            self.assertEqual( 2, len( chunk.angle.distributions ) )
            self.assertEqual( 1, len( chunk.angle.boundaries ) )
            self.assertEqual( 1, len( chunk.angle.interpolants ) )
            self.assertAlmostEqual( 1e-5, chunk.angle.grid[0] )
            self.assertAlmostEqual( 20. , chunk.angle.grid[1] )
            self.assertEqual( 1, len( chunk.angle.distributions[0].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.angle.distributions[1].pdf.coefficients ) )
            self.assertAlmostEqual( 0.5, chunk.angle.distributions[0].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.5, chunk.angle.distributions[1].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.1, chunk.angle.distributions[1].pdf.coefficients[1] )
            self.assertEqual( 2, len( chunk.angle.distributions[0].cdf.coefficients ) )
            self.assertEqual( 3, len( chunk.angle.distributions[1].cdf.coefficients ) )
            self.assertAlmostEqual( 0.5               , chunk.angle.distributions[0].cdf.coefficients[0] )
            self.assertAlmostEqual( 0.5               , chunk.angle.distributions[0].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.4666666666666666, chunk.angle.distributions[1].cdf.coefficients[0] )
            self.assertAlmostEqual( 0.5               , chunk.angle.distributions[1].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.0333333333333333, chunk.angle.distributions[1].cdf.coefficients[2] )
            self.assertEqual( 1, chunk.angle.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.angle.interpolants[0] )

        def verify_tabulated_chunk( self, chunk ) :

            self.assertEqual( DistributionDataType.TwoBody, chunk.type )
            self.assertEqual( ReferenceFrame.CentreOfMass, chunk.frame )

            self.assertEqual( True, isinstance( chunk.angle, TabulatedAngularDistributions ) )

            self.assertEqual( 2, chunk.angle.number_points )
            self.assertEqual( 1, chunk.angle.number_regions )
            self.assertEqual( 2, len( chunk.angle.grid ) )
            self.assertEqual( 2, len( chunk.angle.distributions ) )
            self.assertEqual( 1, len( chunk.angle.boundaries ) )
            self.assertEqual( 1, len( chunk.angle.interpolants ) )
            self.assertAlmostEqual( 1e-5, chunk.angle.grid[0] )
            self.assertAlmostEqual( 20. , chunk.angle.grid[1] )
            self.assertEqual( 2, len( chunk.angle.distributions[0].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.angle.distributions[0].pdf.values ) )
            self.assertEqual( 2, len( chunk.angle.distributions[1].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.angle.distributions[1].pdf.values ) )
            self.assertAlmostEqual( -1.  , chunk.angle.distributions[0].pdf.cosines[0] )
            self.assertAlmostEqual(  1.  , chunk.angle.distributions[0].pdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.angle.distributions[0].pdf.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.angle.distributions[0].pdf.values[1] )
            self.assertAlmostEqual( -1.  , chunk.angle.distributions[1].pdf.cosines[0] )
            self.assertAlmostEqual(  1.  , chunk.angle.distributions[1].pdf.cosines[1] )
            self.assertAlmostEqual(  0.4 , chunk.angle.distributions[1].pdf.values[0] )
            self.assertAlmostEqual(  0.6 , chunk.angle.distributions[1].pdf.values[1] )
            self.assertEqual( None, chunk.angle.distributions[0].cdf )
            self.assertEqual( None, chunk.angle.distributions[1].cdf )
            self.assertEqual( 1, chunk.angle.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.angle.interpolants[0] )

        # the data is given explicitly for isotropic distributions
        chunk = TwoBodyDistributionData( frame = ReferenceFrame.CentreOfMass,
                                         angle = IsotropicAngularDistributions() )

        verify_isotropic_chunk( self, chunk )

        # the data is given explicitly for Legendre distributions
        chunk = TwoBodyDistributionData( frame = ReferenceFrame.CentreOfMass,
                                         angle = LegendreAngularDistributions(
                                                   [ 1e-5, 20. ],
                                                   [ LegendreAngularDistribution( [ 0.5 ] ),
                                                     LegendreAngularDistribution( [ 0.5, 0.1 ] ) ] ) )

        verify_legendre_chunk( self, chunk )

        # the data is given explicitly for tabulated distributions
        chunk = TwoBodyDistributionData( frame = ReferenceFrame.CentreOfMass,
                                         angle = TabulatedAngularDistributions(
                                                   [ 1e-5, 20. ],
                                                   [ TabulatedAngularDistribution( [ -1., +1. ], [ 0.5, 0.5 ] ),
                                                     TabulatedAngularDistribution( [ -1., +1. ], [ 0.4, 0.6 ] ) ] ) )

        verify_tabulated_chunk( self, chunk )

    def test_comparison( self ) :

        left = TwoBodyDistributionData( ReferenceFrame.CentreOfMass, IsotropicAngularDistributions() )
        equal = TwoBodyDistributionData( ReferenceFrame.CentreOfMass, IsotropicAngularDistributions() )
        different = TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                             LegendreAngularDistributions( [ 1e-5, 20. ],
                                                                           [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                             LegendreAngularDistribution( [ 0.5, 0.1 ] ) ] ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
