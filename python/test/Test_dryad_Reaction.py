# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import Reaction
from dryad import ReactionProduct
from dryad import TabulatedCrossSection
from dryad import InterpolationType
from dryad import ReactionCategory
from dryad import DistributionDataType
from dryad import ReferenceFrame
from dryad import TabulatedAngularDistribution
from dryad import TabulatedAngularDistributions
from dryad import TwoBodyDistributionData
from dryad.id import ParticleID

def verify_chunk( self, chunk, normalise ) :

    # reaction identifier
    self.assertEqual( 'n,Fe56->n,Fe56_e1', chunk.identifier )

    # metadata
    self.assertEqual( True, chunk.has_products )

    # reaction category
    self.assertEqual( ReactionCategory.Primary, chunk.category )
    self.assertEqual( False, chunk.is_summation_reaction )
    self.assertEqual( True, chunk.is_primary_reaction )

    # partial identifiers
    self.assertEqual( 0, chunk.number_partial_reactions )
    self.assertEqual( None, chunk.partial_reaction_identifiers )

    # q values
    self.assertAlmostEqual( 0, chunk.mass_difference_qvalue )
    self.assertAlmostEqual( -1, chunk.reaction_qvalue )

    # cross section
    self.assertEqual( 5, chunk.cross_section.number_points )
    self.assertEqual( 2, chunk.cross_section.number_regions )
    self.assertEqual( 5, len( chunk.cross_section.energies ) )
    self.assertEqual( 5, len( chunk.cross_section.values ) )
    self.assertEqual( 2, len( chunk.cross_section.boundaries ) )
    self.assertEqual( 2, len( chunk.cross_section.interpolants ) )
    self.assertAlmostEqual( 1., chunk.cross_section.energies[0] )
    self.assertAlmostEqual( 2., chunk.cross_section.energies[1] )
    self.assertAlmostEqual( 2., chunk.cross_section.energies[2] )
    self.assertAlmostEqual( 3., chunk.cross_section.energies[3] )
    self.assertAlmostEqual( 4., chunk.cross_section.energies[4] )
    self.assertAlmostEqual( 4., chunk.cross_section.values[0] )
    self.assertAlmostEqual( 3., chunk.cross_section.values[1] )
    self.assertAlmostEqual( 4., chunk.cross_section.values[2] )
    self.assertAlmostEqual( 3., chunk.cross_section.values[3] )
    self.assertAlmostEqual( 2., chunk.cross_section.values[4] )
    self.assertEqual( 1, chunk.cross_section.boundaries[0] )
    self.assertEqual( 4, chunk.cross_section.boundaries[1] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.cross_section.interpolants[0] )
    self.assertEqual( InterpolationType.LinearLog, chunk.cross_section.interpolants[1] )
    self.assertEqual( False, chunk.cross_section.is_linearised )

    # reaction products
    self.assertEqual( True, chunk.has_product( ParticleID( 'n' ) ) )
    self.assertEqual( True, chunk.has_product( ParticleID( 'g' ) ) )
    self.assertEqual( False, chunk.has_product( ParticleID( 'h' ) ) )
    self.assertEqual( 3, len( chunk.products ) )
    self.assertEqual( 3, chunk.number_products() )
    self.assertEqual( 1, chunk.number_products( ParticleID( 'n' ) ) )
    self.assertEqual( 2, chunk.number_products( ParticleID( 'g' ) ) )
    self.assertEqual( 0, chunk.number_products( ParticleID( 'h' ) ) )

    self.assertEqual( 1, chunk.product( ParticleID( 'n' ) ).multiplicity )
    self.assertEqual( 1, chunk.product( ParticleID( 'n' ), 0 ).multiplicity )
    self.assertEqual( 2, chunk.product( ParticleID( 'g' ) ).multiplicity )
    self.assertEqual( 2, chunk.product( ParticleID( 'g' ), 0 ).multiplicity )
    self.assertEqual( 3, chunk.product( ParticleID( 'g' ), 1 ).multiplicity )

    normalisation = 2.0 if normalise else 1.0
    data = chunk.product( ParticleID( 'n' ) ).distribution_data
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

    with self.assertRaises( RuntimeError ) : product = chunk.product( ParticleID( 'n' ), 1 )
    with self.assertRaises( RuntimeError ) : product = chunk.product( ParticleID( 'h' ) )
    with self.assertRaises( RuntimeError ) : product = chunk.product( ParticleID( 'h' ), 1 )

def verify_summation_chunk( self, chunk ) :

    # reaction identifier
    self.assertEqual( 'n,Fe56->total', chunk.identifier )

    # metadata
    self.assertEqual( False, chunk.has_products )

    # reaction category
    self.assertEqual( ReactionCategory.Summation, chunk.category )
    self.assertEqual( True, chunk.is_summation_reaction )
    self.assertEqual( False, chunk.is_primary_reaction )

    # partial identifiers
    self.assertEqual( 2, chunk.number_partial_reactions )
    self.assertEqual( 2, len( chunk.partial_reaction_identifiers ) )
    self.assertEqual( 'n,Fe56->elastic', chunk.partial_reaction_identifiers[0] )
    self.assertEqual( 'n,Fe56->2n,Fe56', chunk.partial_reaction_identifiers[1] )

    # q values
    self.assertEqual( None, chunk.mass_difference_qvalue )
    self.assertEqual( None, chunk.reaction_qvalue )

    # cross section
    self.assertEqual( 5, chunk.cross_section.number_points )
    self.assertEqual( 2, chunk.cross_section.number_regions )
    self.assertEqual( 5, len( chunk.cross_section.energies ) )
    self.assertEqual( 5, len( chunk.cross_section.values ) )
    self.assertEqual( 2, len( chunk.cross_section.boundaries ) )
    self.assertEqual( 2, len( chunk.cross_section.interpolants ) )
    self.assertAlmostEqual( 1., chunk.cross_section.energies[0] )
    self.assertAlmostEqual( 2., chunk.cross_section.energies[1] )
    self.assertAlmostEqual( 2., chunk.cross_section.energies[2] )
    self.assertAlmostEqual( 3., chunk.cross_section.energies[3] )
    self.assertAlmostEqual( 4., chunk.cross_section.energies[4] )
    self.assertAlmostEqual( 4., chunk.cross_section.values[0] )
    self.assertAlmostEqual( 3., chunk.cross_section.values[1] )
    self.assertAlmostEqual( 4., chunk.cross_section.values[2] )
    self.assertAlmostEqual( 3., chunk.cross_section.values[3] )
    self.assertAlmostEqual( 2., chunk.cross_section.values[4] )
    self.assertEqual( 1, chunk.cross_section.boundaries[0] )
    self.assertEqual( 4, chunk.cross_section.boundaries[1] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.cross_section.interpolants[0] )
    self.assertEqual( InterpolationType.LinearLog, chunk.cross_section.interpolants[1] )
    self.assertEqual( False, chunk.cross_section.is_linearised )

    # reaction products
    self.assertEqual( False, chunk.has_product( ParticleID( 'n' ) ) )
    self.assertEqual( False, chunk.has_product( ParticleID( 'g' ) ) )
    self.assertEqual( 0, len( chunk.products ) )

class Test_dryad_Reaction( unittest.TestCase ) :
    """Unit test for the Reaction class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk1 = Reaction( id = 'n,Fe56->n,Fe56_e1',
                           mass_q = 0, reaction_q = -1,
                           xs = TabulatedCrossSection ( [ 1., 2., 2., 3., 4. ],
                                                        [ 4., 3., 4., 3., 2. ],
                                                        [ 1, 4 ],
                                                        [ InterpolationType.LinearLinear,
                                                          InterpolationType.LinearLog ] ),
                           products = [ ReactionProduct( ParticleID( 'n' ), 1,
                                                         TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                  TabulatedAngularDistributions(
                                                                                    [ 1e-5, 20. ],
                                                                                    [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                      TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ),
                                        ReactionProduct( ParticleID( 'g' ), 2 ),
                                        ReactionProduct( ParticleID( 'g' ), 3 ) ],
                           normalise = False )
        chunk2 = Reaction( id = 'n,Fe56->n,Fe56_e1',
                           mass_q = 0, reaction_q = -1,
                           xs = TabulatedCrossSection ( [ 1., 2., 2., 3., 4. ],
                                                        [ 4., 3., 4., 3., 2. ],
                                                        [ 1, 4 ],
                                                        [ InterpolationType.LinearLinear,
                                                          InterpolationType.LinearLog ] ),
                           products = [ ReactionProduct( ParticleID( 'n' ), 1,
                                        TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                 TabulatedAngularDistributions(
                                                                   [ 1e-5, 20. ],
                                                                   [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                     TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ),
                                        ReactionProduct( ParticleID( 'g' ), 2 ),
                                        ReactionProduct( ParticleID( 'g' ), 3 ) ],
                           normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

        # the data is given explicitly for a summation reaction
        chunk = Reaction( id = 'n,Fe56->total',
                          partials = [ 'n,Fe56->elastic', 'n,Fe56->2n,Fe56' ],
                          xs = TabulatedCrossSection ( [ 1., 2., 2., 3., 4. ],
                                                       [ 4., 3., 4., 3., 2. ],
                                                       [ 1, 4 ],
                                                       [ InterpolationType.LinearLinear,
                                                         InterpolationType.LinearLog ] ) )

        verify_summation_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = Reaction( id = 'n,Fe56->n,Fe56_e1',
                          mass_q = 0, reaction_q = -1,
                          xs = TabulatedCrossSection ( [ 1., 2., 2., 3., 4. ],
                                                       [ 4., 3., 4., 3., 2. ],
                                                       [ 1, 4 ],
                                                       [ InterpolationType.LinearLinear,
                                                         InterpolationType.LinearLog ] ),
                          products = [ ReactionProduct( ParticleID( 'n' ), 1,
                                                        TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                 TabulatedAngularDistributions(
                                                                                   [ 1e-5, 20. ],
                                                                                   [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                     TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ),
                                       ReactionProduct( ParticleID( 'g' ), 2 ),
                                       ReactionProduct( ParticleID( 'g' ), 3 ) ] )

        # the reaction identifier can be changed
        newid = 'n,Fe56->n,Fe56_e40'
        original = 'n,Fe56->n,Fe56_e1'

        chunk.identifier = newid

        self.assertEqual( newid, chunk.identifier )

        chunk.identifier = original

        verify_chunk( self, chunk, False )

        # the partial reaction identifiers can be changed
        newpartials = [ 'n,Fe56->elastic', 'n,Fe56->2n,Fe55' ]
        original = None

        chunk.partial_reaction_identifiers = newpartials

        self.assertEqual( newpartials, chunk.partial_reaction_identifiers )
        self.assertEqual( ReactionCategory.Summation, chunk.category )
        self.assertEqual( False, chunk.is_primary_reaction )
        self.assertEqual( True, chunk.is_summation_reaction )

        chunk.partial_reaction_identifiers = original

        verify_chunk( self, chunk, False )

        # the q values can be changed
        newmassq = 2
        originalmassq = 0
        newreactionq = -2
        originalreactionq = -1

        chunk.mass_difference_qvalue = newmassq
        chunk.reaction_qvalue = newreactionq

        self.assertEqual( newmassq, chunk.mass_difference_qvalue )
        self.assertEqual( newreactionq, chunk.reaction_qvalue )

        chunk.mass_difference_qvalue = originalmassq
        chunk.reaction_qvalue = originalreactionq

        verify_chunk( self, chunk, False )

        # the cross section can be changed
        newxs = TabulatedCrossSection( [ 1., 4. ], [ 1., 4. ] )
        original = TabulatedCrossSection( [ 1., 2., 2., 3., 4. ],
                                          [ 4., 3., 4., 3., 2. ],
                                          [ 1, 4 ],
                                          [ InterpolationType.LinearLinear,
                                            InterpolationType.LinearLog ] )

        chunk.cross_section = newxs

        self.assertEqual( newxs, chunk.cross_section )

        chunk.cross_section = original

        verify_chunk( self, chunk, False )

        # the products can be changed
        newproducts = [ ReactionProduct( ParticleID( 'n' ), 1 ) ]
        original = [ ReactionProduct( ParticleID( 'n' ), 1,
                                      TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                               TabulatedAngularDistributions(
                                                                 [ 1e-5, 20. ],
                                                                 [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                   TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ),
                     ReactionProduct( ParticleID( 'g' ), 2 ),
                     ReactionProduct( ParticleID( 'g' ), 3 ) ]

        chunk.products = newproducts

        self.assertEqual( newproducts, chunk.products )
        self.assertEqual( 1, chunk.number_products() )

        chunk.products = original

        verify_chunk( self, chunk, False )

    def test_comparison( self ) :

        left = Reaction( id = 'n,Fe56->n,Fe56_e1',
                         mass_q = 0, reaction_q = -1,
                         xs = TabulatedCrossSection ( [ 1., 2., 2., 3., 4. ],
                                                      [ 4., 3., 4., 3., 2. ],
                                                      [ 1, 4 ],
                                                      [ InterpolationType.LinearLinear,
                                                        InterpolationType.LinearLog ] ),
                         products = [ ReactionProduct( ParticleID( 'n' ), 1 ),
                                      ReactionProduct( ParticleID( 'g' ), 2 ),
                                      ReactionProduct( ParticleID( 'g' ), 3 ) ] )
        equal = Reaction( id = 'n,Fe56->n,Fe56_e1',
                          mass_q = 0, reaction_q = -1,
                          xs = TabulatedCrossSection ( [ 1., 2., 2., 3., 4. ],
                                                       [ 4., 3., 4., 3., 2. ],
                                                       [ 1, 4 ],
                                                       [ InterpolationType.LinearLinear,
                                                         InterpolationType.LinearLog ] ),
                          products = [ ReactionProduct( ParticleID( 'n' ), 1 ),
                                       ReactionProduct( ParticleID( 'g' ), 2 ),
                                       ReactionProduct( ParticleID( 'g' ), 3 ) ] )
        different = Reaction( id = 'n,Fe56->total',
                              partials = [ 'n,Fe56->elastic', 'n,Fe56->2n,Fe56' ],
                              xs = TabulatedCrossSection ( [ 1., 2., 2., 3., 4. ],
                                                           [ 4., 3., 4., 3., 2. ],
                                                           [ 1, 4 ],
                                                           [ InterpolationType.LinearLinear,
                                                             InterpolationType.LinearLog ] ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
