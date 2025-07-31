# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import UncorrelatedDistributionData
from dryad import DistributionDataType
from dryad import ReferenceFrame
from dryad import InterpolationType
from dryad import IsotropicAngularDistributions
from dryad import LegendreAngularDistribution
from dryad import LegendreAngularDistributions
from dryad import TabulatedAngularDistribution
from dryad import TabulatedAngularDistributions
from dryad import TabulatedEnergyDistribution
from dryad import TabulatedEnergyDistributions

def verify_isotropic_and_tabulated_chunk( self, chunk ) :

    self.assertEqual( DistributionDataType.Uncorrelated, chunk.type )
    self.assertEqual( ReferenceFrame.CentreOfMass, chunk.frame )

    self.assertEqual( True, isinstance( chunk.angle, IsotropicAngularDistributions ) )

    self.assertEqual( True, isinstance( chunk.energy, TabulatedEnergyDistributions ) )

    self.assertEqual( 2, chunk.energy.number_points )
    self.assertEqual( 1, chunk.energy.number_regions )
    self.assertEqual( 2, len( chunk.energy.grid ) )
    self.assertEqual( 2, len( chunk.energy.distributions ) )
    self.assertEqual( 1, len( chunk.energy.boundaries ) )
    self.assertEqual( 1, len( chunk.energy.interpolants ) )
    self.assertAlmostEqual( 1e-5, chunk.energy.grid[0] )
    self.assertAlmostEqual( 20. , chunk.energy.grid[1] )
    self.assertEqual( 2, len( chunk.energy.distributions[0].pdf.energies ) )
    self.assertEqual( 2, len( chunk.energy.distributions[0].pdf.values ) )
    self.assertEqual( 2, len( chunk.energy.distributions[1].pdf.energies ) )
    self.assertEqual( 2, len( chunk.energy.distributions[1].pdf.values ) )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[0].pdf.energies[0] )
    self.assertAlmostEqual( 20.  , chunk.energy.distributions[0].pdf.energies[1] )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[0].pdf.values[0] )
    self.assertAlmostEqual(  0.1 , chunk.energy.distributions[0].pdf.values[1] )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[1].pdf.energies[0] )
    self.assertAlmostEqual( 20.  , chunk.energy.distributions[1].pdf.energies[1] )
    self.assertAlmostEqual(  0.05, chunk.energy.distributions[1].pdf.values[0] )
    self.assertAlmostEqual(  0.05, chunk.energy.distributions[1].pdf.values[1] )
    self.assertEqual( None, chunk.energy.distributions[0].cdf )
    self.assertEqual( None, chunk.energy.distributions[1].cdf )
    self.assertEqual( 1, chunk.energy.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.energy.interpolants[0] )

def verify_legendre_and_tabulated_chunk( self, chunk ) :

    self.assertEqual( DistributionDataType.Uncorrelated, chunk.type )
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

    self.assertEqual( 2, chunk.energy.number_points )
    self.assertEqual( 1, chunk.energy.number_regions )
    self.assertEqual( 2, len( chunk.energy.grid ) )
    self.assertEqual( 2, len( chunk.energy.distributions ) )
    self.assertEqual( 1, len( chunk.energy.boundaries ) )
    self.assertEqual( 1, len( chunk.energy.interpolants ) )
    self.assertAlmostEqual( 1e-5, chunk.energy.grid[0] )
    self.assertAlmostEqual( 20. , chunk.energy.grid[1] )
    self.assertEqual( 2, len( chunk.energy.distributions[0].pdf.energies ) )
    self.assertEqual( 2, len( chunk.energy.distributions[0].pdf.values ) )
    self.assertEqual( 2, len( chunk.energy.distributions[1].pdf.energies ) )
    self.assertEqual( 2, len( chunk.energy.distributions[1].pdf.values ) )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[0].pdf.energies[0] )
    self.assertAlmostEqual( 20.  , chunk.energy.distributions[0].pdf.energies[1] )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[0].pdf.values[0] )
    self.assertAlmostEqual(  0.1 , chunk.energy.distributions[0].pdf.values[1] )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[1].pdf.energies[0] )
    self.assertAlmostEqual( 20.  , chunk.energy.distributions[1].pdf.energies[1] )
    self.assertAlmostEqual(  0.05, chunk.energy.distributions[1].pdf.values[0] )
    self.assertAlmostEqual(  0.05, chunk.energy.distributions[1].pdf.values[1] )
    self.assertEqual( None, chunk.energy.distributions[0].cdf )
    self.assertEqual( None, chunk.energy.distributions[1].cdf )
    self.assertEqual( 1, chunk.energy.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.energy.interpolants[0] )

def verify_tabulated_and_tabulated_chunk( self, chunk ) :

    self.assertEqual( DistributionDataType.Uncorrelated, chunk.type )
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

    self.assertEqual( 2, chunk.energy.number_points )
    self.assertEqual( 1, chunk.energy.number_regions )
    self.assertEqual( 2, len( chunk.energy.grid ) )
    self.assertEqual( 2, len( chunk.energy.distributions ) )
    self.assertEqual( 1, len( chunk.energy.boundaries ) )
    self.assertEqual( 1, len( chunk.energy.interpolants ) )
    self.assertAlmostEqual( 1e-5, chunk.energy.grid[0] )
    self.assertAlmostEqual( 20. , chunk.energy.grid[1] )
    self.assertEqual( 2, len( chunk.energy.distributions[0].pdf.energies ) )
    self.assertEqual( 2, len( chunk.energy.distributions[0].pdf.values ) )
    self.assertEqual( 2, len( chunk.energy.distributions[1].pdf.energies ) )
    self.assertEqual( 2, len( chunk.energy.distributions[1].pdf.values ) )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[0].pdf.energies[0] )
    self.assertAlmostEqual( 20.  , chunk.energy.distributions[0].pdf.energies[1] )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[0].pdf.values[0] )
    self.assertAlmostEqual(  0.1 , chunk.energy.distributions[0].pdf.values[1] )
    self.assertAlmostEqual(  0.  , chunk.energy.distributions[1].pdf.energies[0] )
    self.assertAlmostEqual( 20.  , chunk.energy.distributions[1].pdf.energies[1] )
    self.assertAlmostEqual(  0.05, chunk.energy.distributions[1].pdf.values[0] )
    self.assertAlmostEqual(  0.05, chunk.energy.distributions[1].pdf.values[1] )
    self.assertEqual( None, chunk.energy.distributions[0].cdf )
    self.assertEqual( None, chunk.energy.distributions[1].cdf )
    self.assertEqual( 1, chunk.energy.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.energy.interpolants[0] )

class Test_dryad_UncorrelatedDistributionData( unittest.TestCase ) :
    """Unit test for the UncorrelatedDistributionData class."""

    def test_component( self ) :

        # the data is given explicitly for isotropic distributions
        chunk = UncorrelatedDistributionData( frame = ReferenceFrame.CentreOfMass,
                                              angle = IsotropicAngularDistributions(),
                                              energy = TabulatedEnergyDistributions(
                                                         [ 1e-5, 20. ],
                                                         [ TabulatedEnergyDistribution( [ 0., 20. ], [ 0., 0.1 ] ),
                                                           TabulatedEnergyDistribution( [ 0., 20. ], [ 0.05, 0.05 ] ) ] ) )

        verify_isotropic_and_tabulated_chunk( self, chunk )

        # the data is given explicitly for Legendre distributions
        chunk = UncorrelatedDistributionData( frame = ReferenceFrame.CentreOfMass,
                                              angle = LegendreAngularDistributions(
                                                       [ 1e-5, 20. ],
                                                       [ LegendreAngularDistribution( [ 0.5 ] ),
                                                         LegendreAngularDistribution( [ 0.5, 0.1 ] ) ] ),
                                              energy = TabulatedEnergyDistributions(
                                                         [ 1e-5, 20. ],
                                                         [ TabulatedEnergyDistribution( [ 0., 20. ], [ 0., 0.1 ] ),
                                                           TabulatedEnergyDistribution( [ 0., 20. ], [ 0.05, 0.05 ] ) ] ) )

        verify_legendre_and_tabulated_chunk( self, chunk )

        # the data is given explicitly for tabulated distributions
        chunk = UncorrelatedDistributionData( frame = ReferenceFrame.CentreOfMass,
                                              angle = TabulatedAngularDistributions(
                                                        [ 1e-5, 20. ],
                                                        [ TabulatedAngularDistribution( [ -1., +1. ], [ 0.5, 0.5 ] ),
                                                          TabulatedAngularDistribution( [ -1., +1. ], [ 0.4, 0.6 ] ) ] ),
                                              energy = TabulatedEnergyDistributions(
                                                         [ 1e-5, 20. ],
                                                         [ TabulatedEnergyDistribution( [ 0., 20. ], [ 0., 0.1 ] ),
                                                           TabulatedEnergyDistribution( [ 0., 20. ], [ 0.05, 0.05 ] ) ] ) )

        verify_tabulated_and_tabulated_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = UncorrelatedDistributionData( frame = ReferenceFrame.CentreOfMass,
                                              angle = IsotropicAngularDistributions(),
                                              energy = TabulatedEnergyDistributions(
                                                         [ 1e-5, 20. ],
                                                         [ TabulatedEnergyDistribution( [ 0., 20. ], [ 0., 0.1 ] ),
                                                           TabulatedEnergyDistribution( [ 0., 20. ], [ 0.05, 0.05 ] ) ] ) )

        # the referenceframe can be changed
        newframe = ReferenceFrame.Laboratory
        original = ReferenceFrame.CentreOfMass

        chunk.frame = newframe

        self.assertEqual( newframe, chunk.frame )

        chunk.frame = original

        verify_isotropic_and_tabulated_chunk( self, chunk )

        # the distribution data can be changed
        newangle = LegendreAngularDistributions(
                       [ 1e-5, 20. ],
                       [ LegendreAngularDistribution( [ 0.5 ] ),
                         LegendreAngularDistribution( [ 0.5, 0.1 ] ) ] )
        newenergy = TabulatedEnergyDistributions( [ 1e-5, 20. ],
                                                  [ TabulatedEnergyDistribution( [ 0., 10. ], [ 0., 0.1 ] ),
                                                    TabulatedEnergyDistribution( [ 0., 10. ], [ 0.05, 0.05 ] ) ] )
        originalangle = IsotropicAngularDistributions()
        originalenergy = TabulatedEnergyDistributions( [ 1e-5, 20. ],
                                                       [ TabulatedEnergyDistribution( [ 0., 20. ], [ 0., 0.1 ] ),
                                                         TabulatedEnergyDistribution( [ 0., 20. ], [ 0.05, 0.05 ] ) ] )

        chunk.angle = newangle
        chunk.energy = newenergy

        self.assertEqual( newangle, chunk.angle )
        self.assertEqual( newenergy, chunk.energy )

        chunk.angle = originalangle
        chunk.energy = originalenergy

        verify_isotropic_and_tabulated_chunk( self, chunk )

    def test_comparison( self ) :

        left = UncorrelatedDistributionData( ReferenceFrame.CentreOfMass,
                                             IsotropicAngularDistributions(),
                                             TabulatedEnergyDistributions( [ 1e-5, 20. ],
                                                                           [ TabulatedEnergyDistribution( [ 0., 20. ], [ 0., 0.1 ] ),
                                                                             TabulatedEnergyDistribution( [ 0., 20. ], [ 0.05, 0.05 ] ) ] ) )
        equal = UncorrelatedDistributionData( ReferenceFrame.CentreOfMass,
                                              IsotropicAngularDistributions(),
                                              TabulatedEnergyDistributions( [ 1e-5, 20. ],
                                                                            [ TabulatedEnergyDistribution( [ 0., 20. ], [ 0., 0.1 ] ),
                                                                              TabulatedEnergyDistribution( [ 0., 20. ], [ 0.05, 0.05 ] ) ] ) )
        different = UncorrelatedDistributionData( ReferenceFrame.CentreOfMass,
                                                  TabulatedAngularDistributions( [ 1e-5, 20. ],
                                                                                 [ TabulatedAngularDistribution( [ -1., 1. ], [ 0.5, 0.5 ] ),
                                                                                   TabulatedAngularDistribution( [ -1., 1. ], [ 0.5, 0.5 ] ) ] ),
                                                  TabulatedEnergyDistributions( [ 1e-5, 20. ],
                                                                                [ TabulatedEnergyDistribution( [ 0., 20. ], [ 0.5, 0.5 ] ),
                                                                                  TabulatedEnergyDistribution( [ 0., 20. ], [ 0.05, 0.05 ] ) ] ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
