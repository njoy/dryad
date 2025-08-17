# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import ReactionProduct
from dryad import TabulatedMultiplicity
from dryad import InterpolationType
from dryad import ReferenceFrame
from dryad import TabulatedAverageEnergy
from dryad import TwoBodyDistributionData
from dryad import IsotropicAngularDistributions
from dryad import TabulatedAngularDistribution
from dryad import TabulatedAngularDistributions
from dryad import DistributionDataType
from dryad.id import ParticleID

def verify_chunk( self, chunk, normalise ) :

    # reaction product identifier
    self.assertEqual( ParticleID.neutron(), chunk.identifier )

    # multiplicity
    self.assertEqual( True, isinstance( chunk.multiplicity, int ) )
    self.assertEqual( 1, chunk.multiplicity )

    # average reaction product energy
    self.assertIsNone( chunk.average_energy )

    # distribution data
    normalisation = 2.0 if normalise else 1.0
    data = chunk.distribution_data
    self.assertEqual( DistributionDataType.TwoBody, data.type )
    self.assertEqual( ReferenceFrame.CentreOfMass, data.frame )
    self.assertEqual( True, isinstance( data.angle, TabulatedAngularDistributions ) )
    self.assertEqual( 2, data.angle.number_points )
    self.assertEqual( 1, data.angle.number_regions )
    self.assertEqual( 2, len( data.angle.grid ) )
    self.assertEqual( 2, len( data.angle.distributions ) )
    self.assertEqual( 1, len( data.angle.boundaries ) )
    self.assertEqual( 1, len( data.angle.interpolants ) )
    self.assertAlmostEqual( 1e-5, data.angle.grid[0] )
    self.assertAlmostEqual( 20. , data.angle.grid[1] )
    self.assertEqual( 2, len( data.angle.distributions[0].pdf.cosines ) )
    self.assertEqual( 2, len( data.angle.distributions[0].pdf.values ) )
    self.assertEqual( 2, len( data.angle.distributions[1].pdf.cosines ) )
    self.assertEqual( 2, len( data.angle.distributions[1].pdf.values ) )
    self.assertAlmostEqual( -1.  , data.angle.distributions[0].pdf.cosines[0] )
    self.assertAlmostEqual(  1.  , data.angle.distributions[0].pdf.cosines[1] )
    self.assertAlmostEqual(  1. / normalisation, data.angle.distributions[0].pdf.values[0] )
    self.assertAlmostEqual(  1. / normalisation, data.angle.distributions[0].pdf.values[1] )
    self.assertAlmostEqual( -1.  , data.angle.distributions[1].pdf.cosines[0] )
    self.assertAlmostEqual(  1.  , data.angle.distributions[1].pdf.cosines[1] )
    self.assertAlmostEqual(  0.8 / normalisation, data.angle.distributions[1].pdf.values[0] )
    self.assertAlmostEqual(  1.2 / normalisation, data.angle.distributions[1].pdf.values[1] )
    self.assertEqual( 2, len( data.angle.distributions[0].cdf.cosines ) )
    self.assertEqual( 2, len( data.angle.distributions[0].cdf.values ) )
    self.assertEqual( 2, len( data.angle.distributions[1].cdf.cosines ) )
    self.assertEqual( 2, len( data.angle.distributions[1].cdf.values ) )
    self.assertAlmostEqual( -1.  , data.angle.distributions[0].cdf.cosines[0] )
    self.assertAlmostEqual(  1.  , data.angle.distributions[0].cdf.cosines[1] )
    self.assertAlmostEqual(  0. / normalisation, data.angle.distributions[0].cdf.values[0] )
    self.assertAlmostEqual(  2. / normalisation, data.angle.distributions[0].cdf.values[1] )
    self.assertAlmostEqual( -1.  , data.angle.distributions[1].cdf.cosines[0] )
    self.assertAlmostEqual(  1.  , data.angle.distributions[1].cdf.cosines[1] )
    self.assertAlmostEqual(  0. / normalisation, data.angle.distributions[1].cdf.values[0] )
    self.assertAlmostEqual(  2. / normalisation, data.angle.distributions[1].cdf.values[1] )
    self.assertEqual( 1, data.angle.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, data.angle.interpolants[0] )

    # metadata
    self.assertEqual( False, chunk.has_average_energy )
    self.assertEqual( True, chunk.has_distribution_data )

def verify_tabulated_chunk( self, chunk, normalise ) :

    # reaction product identifier
    self.assertEqual( ParticleID.neutron(), chunk.identifier )

    # multiplicity
    self.assertEqual( True, isinstance( chunk.multiplicity, TabulatedMultiplicity ) )
    self.assertEqual( 5, chunk.multiplicity.number_points )
    self.assertEqual( 2, chunk.multiplicity.number_regions )
    self.assertEqual( 5, len( chunk.multiplicity.energies ) )
    self.assertEqual( 5, len( chunk.multiplicity.values ) )
    self.assertEqual( 2, len( chunk.multiplicity.boundaries ) )
    self.assertEqual( 2, len( chunk.multiplicity.interpolants ) )
    self.assertAlmostEqual( 1., chunk.multiplicity.energies[0] )
    self.assertAlmostEqual( 2., chunk.multiplicity.energies[1] )
    self.assertAlmostEqual( 2., chunk.multiplicity.energies[2] )
    self.assertAlmostEqual( 3., chunk.multiplicity.energies[3] )
    self.assertAlmostEqual( 4., chunk.multiplicity.energies[4] )
    self.assertAlmostEqual( 4., chunk.multiplicity.values[0] )
    self.assertAlmostEqual( 3., chunk.multiplicity.values[1] )
    self.assertAlmostEqual( 4., chunk.multiplicity.values[2] )
    self.assertAlmostEqual( 3., chunk.multiplicity.values[3] )
    self.assertAlmostEqual( 2., chunk.multiplicity.values[4] )
    self.assertEqual( 1, chunk.multiplicity.boundaries[0] )
    self.assertEqual( 4, chunk.multiplicity.boundaries[1] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.multiplicity.interpolants[0] )
    self.assertEqual( InterpolationType.LinearLog, chunk.multiplicity.interpolants[1] )
    self.assertEqual( False, chunk.multiplicity.is_linearised )

    # average reaction product energy
    self.assertIsNone( chunk.average_energy )

    # distribution data
    normalisation = 2.0 if normalise else 1.0
    data = chunk.distribution_data
    self.assertEqual( DistributionDataType.TwoBody, data.type )
    self.assertEqual( ReferenceFrame.CentreOfMass, data.frame )
    self.assertEqual( True, isinstance( data.angle, TabulatedAngularDistributions ) )
    self.assertEqual( 2, data.angle.number_points )
    self.assertEqual( 1, data.angle.number_regions )
    self.assertEqual( 2, len( data.angle.grid ) )
    self.assertEqual( 2, len( data.angle.distributions ) )
    self.assertEqual( 1, len( data.angle.boundaries ) )
    self.assertEqual( 1, len( data.angle.interpolants ) )
    self.assertAlmostEqual( 1e-5, data.angle.grid[0] )
    self.assertAlmostEqual( 20. , data.angle.grid[1] )
    self.assertEqual( 2, len( data.angle.distributions[0].pdf.cosines ) )
    self.assertEqual( 2, len( data.angle.distributions[0].pdf.values ) )
    self.assertEqual( 2, len( data.angle.distributions[1].pdf.cosines ) )
    self.assertEqual( 2, len( data.angle.distributions[1].pdf.values ) )
    self.assertAlmostEqual( -1.  , data.angle.distributions[0].pdf.cosines[0] )
    self.assertAlmostEqual(  1.  , data.angle.distributions[0].pdf.cosines[1] )
    self.assertAlmostEqual(  1. / normalisation, data.angle.distributions[0].pdf.values[0] )
    self.assertAlmostEqual(  1. / normalisation, data.angle.distributions[0].pdf.values[1] )
    self.assertAlmostEqual( -1.  , data.angle.distributions[1].pdf.cosines[0] )
    self.assertAlmostEqual(  1.  , data.angle.distributions[1].pdf.cosines[1] )
    self.assertAlmostEqual(  0.8 / normalisation, data.angle.distributions[1].pdf.values[0] )
    self.assertAlmostEqual(  1.2 / normalisation, data.angle.distributions[1].pdf.values[1] )
    self.assertEqual( 2, len( data.angle.distributions[0].cdf.cosines ) )
    self.assertEqual( 2, len( data.angle.distributions[0].cdf.values ) )
    self.assertEqual( 2, len( data.angle.distributions[1].cdf.cosines ) )
    self.assertEqual( 2, len( data.angle.distributions[1].cdf.values ) )
    self.assertAlmostEqual( -1.  , data.angle.distributions[0].cdf.cosines[0] )
    self.assertAlmostEqual(  1.  , data.angle.distributions[0].cdf.cosines[1] )
    self.assertAlmostEqual(  0. / normalisation, data.angle.distributions[0].cdf.values[0] )
    self.assertAlmostEqual(  2. / normalisation, data.angle.distributions[0].cdf.values[1] )
    self.assertAlmostEqual( -1.  , data.angle.distributions[1].cdf.cosines[0] )
    self.assertAlmostEqual(  1.  , data.angle.distributions[1].cdf.cosines[1] )
    self.assertAlmostEqual(  0. / normalisation, data.angle.distributions[1].cdf.values[0] )
    self.assertAlmostEqual(  2. / normalisation, data.angle.distributions[1].cdf.values[1] )
    self.assertEqual( 1, data.angle.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, data.angle.interpolants[0] )

    # metadata
    self.assertEqual( False, chunk.has_average_energy )
    self.assertEqual( True, chunk.has_distribution_data )

class Test_dryad_ReactionProduct( unittest.TestCase ) :
    """Unit test for the ReactionProduct class."""

    def test_component( self ) :

        # the data is given explicitly using an integer multiplicity
        chunk1 = ReactionProduct( id = ParticleID.neutron(), multiplicity = 1,
                                  distribution = TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                          TabulatedAngularDistributions(
                                                                            [ 1e-5, 20. ],
                                                                            [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                              TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ),
                                  normalise = False )
        chunk2 = ReactionProduct( id = ParticleID.neutron(), multiplicity = 1,
                                  distribution = TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                          TabulatedAngularDistributions(
                                                                            [ 1e-5, 20. ],
                                                                            [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                              TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ),
                                  normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

        # the data is given explicitly using a tabulated multiplicity
        chunk1 = ReactionProduct( id = ParticleID.neutron(),
                                  multiplicity = TabulatedMultiplicity ( [ 1., 2., 2., 3., 4. ],
                                                                         [ 4., 3., 4., 3., 2. ],
                                                                         [ 1, 4 ],
                                                                         [ InterpolationType.LinearLinear,
                                                                           InterpolationType.LinearLog ] ),
                                  distribution = TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                          TabulatedAngularDistributions(
                                                                            [ 1e-5, 20. ],
                                                                            [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                              TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ),
                                  normalise = False )
        chunk2 = ReactionProduct( id = ParticleID.neutron(),
                                  multiplicity = TabulatedMultiplicity ( [ 1., 2., 2., 3., 4. ],
                                                                         [ 4., 3., 4., 3., 2. ],
                                                                         [ 1, 4 ],
                                                                         [ InterpolationType.LinearLinear,
                                                                           InterpolationType.LinearLog ] ),
                                  distribution = TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                          TabulatedAngularDistributions(
                                                                            [ 1e-5, 20. ],
                                                                            [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                              TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ),
                                  normalise = True )

        verify_tabulated_chunk( self, chunk1, False )
        verify_tabulated_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_tabulated_chunk( self, chunk1, True )
        verify_tabulated_chunk( self, chunk2, True )

    def test_setter_functions( self ) :

        chunk = ReactionProduct( id = ParticleID.neutron(), multiplicity = 1,
                                 distribution = TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                         TabulatedAngularDistributions(
                                                                           [ 1e-5, 20. ],
                                                                           [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                             TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) )

        # the product identifier can be changed
        newid = ParticleID.proton()
        original = ParticleID.neutron()

        chunk.identifier = newid

        self.assertEqual( newid, chunk.identifier )

        chunk.identifier = original

        verify_chunk( self, chunk, False )

        # the multiplicity can be changed
        newmultiplicity = TabulatedMultiplicity ( [ 1., 2., 2., 3., 4. ],
                                                  [ 4., 3., 4., 3., 2. ],
                                                  [ 1, 4 ],
                                                  [ InterpolationType.LinearLinear,
                                                    InterpolationType.LinearLog ] )
        original = 1

        chunk.multiplicity = newmultiplicity

        verify_tabulated_chunk( self, chunk, False )

        chunk.multiplicity = original

        verify_chunk( self, chunk, False )

        # the distribution data can be changed
        newdistribution = TwoBodyDistributionData( ReferenceFrame.CentreOfMass, IsotropicAngularDistributions() )
        original = TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                            TabulatedAngularDistributions(
                                              [ 1e-5, 20. ],
                                              [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) )

        chunk.distribution_data = newdistribution

        self.assertEqual( newdistribution, chunk.distribution_data )

        chunk.distribution_data = original

        verify_chunk( self, chunk, False )

        # the average energy can be changed
        newaverage = TabulatedAverageEnergy( [ 1., 2., 2., 3., 4. ],
                                             [ 4., 3., 4., 3., 2. ],
                                             [ 1, 4 ],
                                             [ InterpolationType.LinearLinear,
                                               InterpolationType.LinearLog ] )
        original = None

        chunk.average_energy = newaverage

        self.assertEqual( newaverage, chunk.average_energy )

        chunk.average_energy = original

        verify_chunk( self, chunk, False )

    def test_comparison( self ) :

        left = ReactionProduct( ParticleID.neutron(), 1 )
        equal = ReactionProduct( ParticleID.neutron(), 1 )
        different = ReactionProduct( ParticleID.proton(), 1,
                                     TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                              IsotropicAngularDistributions() ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
