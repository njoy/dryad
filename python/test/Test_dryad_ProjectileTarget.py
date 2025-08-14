# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import ProjectileTarget
from dryad import Reaction
from dryad import TabulatedCrossSection
from dryad import InterpolationType
from dryad import InteractionType
from dryad import ReactionCategory
from dryad import DistributionDataType
from dryad import ReferenceFrame
from dryad import TabulatedAngularDistribution
from dryad import TabulatedAngularDistributions
from dryad import ReactionProduct
from dryad import TwoBodyDistributionData
from dryad.id import ParticleID

def verify_chunk( self, chunk, normalise ) :

    # documentation
    self.assertIsNone( chunk.documentation.awr )
    self.assertIsNone( chunk.documentation.library )
    self.assertIsNone( chunk.documentation.version )
    self.assertIsNone( chunk.documentation.description )

    # identifiers
    self.assertEqual( ParticleID( 'n' ), chunk.projectile_identifier )
    self.assertEqual( ParticleID( 'Fe56' ), chunk.target_identifier )

    # interaction type
    self.assertEqual( InteractionType.Nuclear, chunk.interaction_type )

    # resonance parameters are not present
    self.assertIsNone( chunk.resonances )

    # reactions are present
    self.assertEqual( 9, chunk.number_reactions )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->total' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->n,Fe56' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->2n,Fe55[all]' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->2n,Fe55' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->2n,Fe55_e1' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->3n,Fe54[all]' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->3n,Fe54' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->3n,Fe54_e1' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->a,Cr52[all]' ) )
    self.assertEqual( False, chunk.has_reaction( 'some unknown reaction' ) )

    # reactions[0] and reaction( 'n,Fe56->total' )
    for reaction in [ chunk.reactions[0], chunk.reaction( 'n,Fe56->total' ) ] :

        self.assertEqual( 'n,Fe56->total', reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 6, reaction.number_partial_reactions )
        self.assertEqual( 'n,Fe56->n,Fe56', reaction.partial_reaction_identifiers[0] )
        self.assertEqual( 'n,Fe56->2n,Fe55', reaction.partial_reaction_identifiers[1] )
        self.assertEqual( 'n,Fe56->2n,Fe55_e1', reaction.partial_reaction_identifiers[2] )
        self.assertEqual( 'n,Fe56->3n,Fe54', reaction.partial_reaction_identifiers[3] )
        self.assertEqual( 'n,Fe56->3n,Fe54_e1', reaction.partial_reaction_identifiers[4] )
        self.assertEqual( 'n,Fe56->a,Cr52[all]', reaction.partial_reaction_identifiers[5] )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1e-5, reaction.cross_section.energies[0] )
        self.assertAlmostEqual(   20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 1000001., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1000001., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.Histogram, reaction.cross_section.interpolants[0] )
        self.assertEqual( False, reaction.cross_section.is_linearised )

    # reactions[1] and reaction( 'n,Fe56->n,Fe56' )
    for reaction in [ chunk.reactions[1], chunk.reaction( 'n,Fe56->n,Fe56' ) ] :

        self.assertEqual( 'n,Fe56->n,Fe56', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( True, reaction.has_products )
        self.assertAlmostEqual( 0, reaction.mass_difference_qvalue )
        self.assertAlmostEqual( 0, reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual( 1e-5, reaction.cross_section.energies[0] )
        self.assertAlmostEqual(  20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 1000000, reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1000000, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )
        product = reaction.product( ParticleID( 'n' ) )
        self.assertEqual( 1, product.multiplicity )
        normalisation = 2.0 if normalise else 1.0
        data = product.distribution_data
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

    # reactions[2] and reaction( 'n,Fe56->2n,Fe55[all]' )
    for reaction in [ chunk.reactions[2], chunk.reaction( 'n,Fe56->2n,Fe55[all]' ) ] :

        self.assertEqual( 'n,Fe56->2n,Fe55[all]', reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( 'n,Fe56->2n,Fe55', reaction.partial_reaction_identifiers[0] )
        self.assertEqual( 'n,Fe56->2n,Fe55_e1', reaction.partial_reaction_identifiers[1] )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 3, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.Histogram, reaction.cross_section.interpolants[0] )
        self.assertEqual( False, reaction.cross_section.is_linearised )

    # reactions[3] and reaction( 'n,Fe56->2n,Fe55' )
    for reaction in [ chunk.reactions[3], chunk.reaction( 'n,Fe56->2n,Fe55' ) ] :

        self.assertEqual( 'n,Fe56->2n,Fe55', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -1., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0.     , reaction.cross_section.values[0] )
        self.assertAlmostEqual( 2.00001, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[4] and reaction( 'n,Fe56->2n,Fe55_e1' )
    for reaction in [ chunk.reactions[4], chunk.reaction( 'n,Fe56->2n,Fe55_e1' ) ] :

        self.assertEqual( 'n,Fe56->2n,Fe55_e1', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -1., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[5] and reaction( 'n,Fe56->3n,Fe54[all]' )
    for reaction in [ chunk.reactions[5], chunk.reaction( 'n,Fe56->3n,Fe54[all]' ) ] :

        self.assertEqual( 'n,Fe56->3n,Fe54[all]', reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( 'n,Fe56->3n,Fe54', reaction.partial_reaction_identifiers[0] )
        self.assertEqual( 'n,Fe56->3n,Fe54_e1', reaction.partial_reaction_identifiers[1] )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  5., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 5, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.Histogram, reaction.cross_section.interpolants[0] )
        self.assertEqual( False, reaction.cross_section.is_linearised )

    # reactions[6] and reaction( 'n,Fe56-3n,Fe54' )
    for reaction in [ chunk.reactions[6], chunk.reaction( 'n,Fe56->3n,Fe54' ) ] :

        self.assertEqual( 'n,Fe56->3n,Fe54', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -5., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  5., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0.     , reaction.cross_section.values[0] )
        self.assertAlmostEqual( 3.00001, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[7] and reaction( 'n,Fe56->3n,Fe54_e1' )
    for reaction in [ chunk.reactions[7], chunk.reaction( 'n,Fe56->3n,Fe54_e1' ) ] :

        self.assertEqual( 'n,Fe56->3n,Fe54_e1', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -5., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  5., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 2., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[8] and reaction( 'n,Fe56->a,Cr52[all]' )
    for reaction in [ chunk.reactions[8], chunk.reaction( 'n,Fe56->a,Cr52[all]' ) ] :

        self.assertEqual( 'n,Fe56->a,Cr52[all]', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual(  0., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual( 1e-5, reaction.cross_section.energies[0] )
        self.assertAlmostEqual(  20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

def verify_correct_summation( self, chunk ) :

    # documentation
    self.assertIsNone( chunk.documentation.awr )
    self.assertIsNone( chunk.documentation.library )
    self.assertIsNone( chunk.documentation.version )
    self.assertIsNone( chunk.documentation.description )

    # identifiers
    self.assertEqual( ParticleID( 'n' ), chunk.projectile_identifier )
    self.assertEqual( ParticleID( 'Fe56' ), chunk.target_identifier )

    # interaction type
    self.assertEqual( InteractionType.Nuclear, chunk.interaction_type )

    # resonance parameters are not present
    self.assertIsNone( chunk.resonances )

    # reactions are present
    self.assertEqual( 9, chunk.number_reactions )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->total' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->n,Fe56' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->2n,Fe55[all]' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->2n,Fe55' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->2n,Fe55_e1' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->3n,Fe54[all]' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->3n,Fe54' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->3n,Fe54_e1' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->a,Cr52[all]' ) )
    self.assertEqual( False, chunk.has_reaction( 'some unknown reaction' ) )

    # reactions[0] and reaction( 'n,Fe56->total' )
    for reaction in [ chunk.reactions[0], chunk.reaction( 'n,Fe56->total' ) ] :

        self.assertEqual( 'n,Fe56->total', reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 6, reaction.number_partial_reactions )
        self.assertEqual( 'n,Fe56->n,Fe56', reaction.partial_reaction_identifiers[0] )
        self.assertEqual( 'n,Fe56->2n,Fe55', reaction.partial_reaction_identifiers[1] )
        self.assertEqual( 'n,Fe56->2n,Fe55_e1', reaction.partial_reaction_identifiers[2] )
        self.assertEqual( 'n,Fe56->3n,Fe54', reaction.partial_reaction_identifiers[3] )
        self.assertEqual( 'n,Fe56->3n,Fe54_e1', reaction.partial_reaction_identifiers[4] )
        self.assertEqual( 'n,Fe56->a,Cr52[all]', reaction.partial_reaction_identifiers[5] )
        self.assertEqual( 4, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 4, len( reaction.cross_section.energies ) )
        self.assertEqual( 4, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1e-5, reaction.cross_section.energies[0] )
        self.assertAlmostEqual(    1., reaction.cross_section.energies[1] )
        self.assertAlmostEqual(    5., reaction.cross_section.energies[2] )
        self.assertAlmostEqual(   20., reaction.cross_section.energies[3] )
        self.assertAlmostEqual( 1000001., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1000001., reaction.cross_section.values[1] )
        self.assertAlmostEqual( 1000001. + 3.00001 / 19. * 4., reaction.cross_section.values[2] )
        self.assertAlmostEqual( 1000009.00002, reaction.cross_section.values[3] )
        self.assertEqual( 3, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[1] and reaction( 'n,Fe56->n,Fe56' )
    for reaction in [ chunk.reactions[1], chunk.reaction( 'n,Fe56->n,Fe56' ) ] :

        self.assertEqual( 'n,Fe56->n,Fe56', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( True, reaction.has_products )
        self.assertAlmostEqual( 0, reaction.mass_difference_qvalue )
        self.assertAlmostEqual( 0, reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual( 1e-5, reaction.cross_section.energies[0] )
        self.assertAlmostEqual(  20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 1000000, reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1000000, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[2] and reaction( 'n,Fe56->2n,Fe55[all]' )
    for reaction in [ chunk.reactions[2], chunk.reaction( 'n,Fe56->2n,Fe55[all]' ) ] :

        self.assertEqual( 'n,Fe56->2n,Fe55[all]', reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( 'n,Fe56->2n,Fe55', reaction.partial_reaction_identifiers[0] )
        self.assertEqual( 'n,Fe56->2n,Fe55_e1', reaction.partial_reaction_identifiers[1] )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 3.00001, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[3] and reaction( 'n,Fe56->2n,Fe55' )
    for reaction in [ chunk.reactions[3], chunk.reaction( 'n,Fe56->2n,Fe55' ) ] :

        self.assertEqual( 'n,Fe56->2n,Fe55', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -1., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0.     , reaction.cross_section.values[0] )
        self.assertAlmostEqual( 2.00001, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[4] and reaction( 'n,Fe56->2n,Fe55_e1' )
    for reaction in [ chunk.reactions[4], chunk.reaction( 'n,Fe56->2n,Fe55_e1' ) ] :

        self.assertEqual( 'n,Fe56->2n,Fe55_e1', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -1., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[5] and reaction( 'n,Fe56->3n,Fe54[all]' )
    for reaction in [ chunk.reactions[5], chunk.reaction( 'n,Fe56->3n,Fe54[all]' ) ] :

        self.assertEqual( 'n,Fe56->3n,Fe54[all]', reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( 'n,Fe56->3n,Fe54', reaction.partial_reaction_identifiers[0] )
        self.assertEqual( 'n,Fe56->3n,Fe54_e1', reaction.partial_reaction_identifiers[1] )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  5., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 5.00001, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[6] and reaction( 'n,Fe56-3n,Fe54' )
    for reaction in [ chunk.reactions[6], chunk.reaction( 'n,Fe56->3n,Fe54' ) ] :

        self.assertEqual( 'n,Fe56->3n,Fe54', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -5., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  5., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0.     , reaction.cross_section.values[0] )
        self.assertAlmostEqual( 3.00001, reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[7] and reaction( 'n,Fe56->3n,Fe54_e1' )
    for reaction in [ chunk.reactions[7], chunk.reaction( 'n,Fe56->3n,Fe54_e1' ) ] :

        self.assertEqual( 'n,Fe56->3n,Fe54_e1', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -5., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  5., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 2., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[8] and reaction( 'n,Fe56->a,Cr52[all]' )
    for reaction in [ chunk.reactions[8], chunk.reaction( 'n,Fe56->a,Cr52[all]' ) ] :

        self.assertEqual( 'n,Fe56->a,Cr52[all]', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual(  0., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual( 1e-5, reaction.cross_section.energies[0] )
        self.assertAlmostEqual(  20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

class Test_dryad_ProjectileTarget( unittest.TestCase ) :
    """Unit test for the ProjectileTarget class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk1 = ProjectileTarget(
                     projectile = ParticleID( 'n' ),
                     target = ParticleID( 'Fe56' ),
                     type = InteractionType.Nuclear,
                     reactions = [ Reaction( 'n,Fe56->total',
                                             [ 'n,Fe56->n,Fe56', 'n,Fe56->2n,Fe55[all]',
                                               'n,Fe56->3n,Fe54[all]', 'n,Fe56->a,Cr52[all]' ],
                                             TabulatedCrossSection( [ 1e-5, 20. ], [ 1000001., 1000001. ],
                                                                      InterpolationType.Histogram ),
                                             [] ),
                                   Reaction( 'n,Fe56->n,Fe56',
                                             TabulatedCrossSection( [ 1e-5, 20. ], [ 1e+6, 1e+6 ],
                                                                      InterpolationType.LinearLinear ),
                                             [ ReactionProduct( ParticleID( 'n' ), 1,
                                                                TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                         TabulatedAngularDistributions(
                                                                                           [ 1e-5, 20. ],
                                                                                           [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                             TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ) ],
                                             0, 0 ),
                                   Reaction( 'n,Fe56->2n,Fe55[all]',
                                             [ 'n,Fe56->2n,Fe55', 'n,Fe56->2n,Fe55_e1' ],
                                             TabulatedCrossSection( [ 1., 20. ], [ 0., 3. ],
                                                                      InterpolationType.Histogram ),
                                             [] ),
                                   Reaction( 'n,Fe56->2n,Fe55',
                                             TabulatedCrossSection( [ 1., 20. ], [ 0., 2.00001 ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, -1 ),
                                   Reaction( 'n,Fe56->2n,Fe55_e1',
                                             TabulatedCrossSection( [ 1., 20. ], [ 0., 1. ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, -1 ),
                                   Reaction( 'n,Fe56->3n,Fe54[all]',
                                             [ 'n,Fe56->3n,Fe54', 'n,Fe56->3n,Fe54_e1' ],
                                             TabulatedCrossSection( [ 5., 20. ], [ 0., 5. ],
                                                                      InterpolationType.Histogram ),
                                             [] ),
                                   Reaction( 'n,Fe56->3n,Fe54',
                                             TabulatedCrossSection( [ 5., 20. ], [ 0., 3.00001 ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, -5 ),
                                   Reaction( 'n,Fe56->3n,Fe54_e1',
                                             TabulatedCrossSection( [ 5., 20. ], [ 0., 2. ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, -5 ),
                                   Reaction( 'n,Fe56->a,Cr52[all]',
                                             TabulatedCrossSection( [ 1e-5, 20. ], [ 1., 1. ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, 0 ) ],
                     normalise = False )
        chunk2 = ProjectileTarget(
                     projectile = ParticleID( 'n' ),
                     target = ParticleID( 'Fe56' ),
                     type = InteractionType.Nuclear,
                     reactions = [ Reaction( 'n,Fe56->total',
                                             [ 'n,Fe56->n,Fe56', 'n,Fe56->2n,Fe55[all]',
                                               'n,Fe56->3n,Fe54[all]', 'n,Fe56->a,Cr52[all]' ],
                                             TabulatedCrossSection( [ 1e-5, 20. ], [ 1000001., 1000001. ],
                                                                      InterpolationType.Histogram ),
                                             [] ),
                                   Reaction( 'n,Fe56->n,Fe56',
                                             TabulatedCrossSection( [ 1e-5, 20. ], [ 1e+6, 1e+6 ],
                                                                      InterpolationType.LinearLinear ),
                                             [ ReactionProduct( ParticleID( 'n' ), 1,
                                                                TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                         TabulatedAngularDistributions(
                                                                                           [ 1e-5, 20. ],
                                                                                           [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                             TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ) ],
                                             0, 0 ),
                                   Reaction( 'n,Fe56->2n,Fe55[all]',
                                             [ 'n,Fe56->2n,Fe55', 'n,Fe56->2n,Fe55_e1' ],
                                             TabulatedCrossSection( [ 1., 20. ], [ 0., 3. ],
                                                                      InterpolationType.Histogram ),
                                             [] ),
                                   Reaction( 'n,Fe56->2n,Fe55',
                                             TabulatedCrossSection( [ 1., 20. ], [ 0., 2.00001 ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, -1 ),
                                   Reaction( 'n,Fe56->2n,Fe55_e1',
                                             TabulatedCrossSection( [ 1., 20. ], [ 0., 1. ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, -1 ),
                                   Reaction( 'n,Fe56->3n,Fe54[all]',
                                             [ 'n,Fe56->3n,Fe54', 'n,Fe56->3n,Fe54_e1' ],
                                             TabulatedCrossSection( [ 5., 20. ], [ 0., 5. ],
                                                                      InterpolationType.Histogram ),
                                             [] ),
                                   Reaction( 'n,Fe56->3n,Fe54',
                                             TabulatedCrossSection( [ 5., 20. ], [ 0., 3.00001 ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, -5 ),
                                   Reaction( 'n,Fe56->3n,Fe54_e1',
                                             TabulatedCrossSection( [ 5., 20. ], [ 0., 2. ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, -5 ),
                                   Reaction( 'n,Fe56->a,Cr52[all]',
                                             TabulatedCrossSection( [ 1e-5, 20. ], [ 1., 1. ],
                                                                      InterpolationType.LinearLinear ),
                                             [],
                                             0, 0 ) ],
                     normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

        chunk1.calculate_summation_cross_sections()
        chunk2.calculate_summation_cross_sections()

        verify_correct_summation( self, chunk1 )
        verify_correct_summation( self, chunk2 )

    def test_setter_functions( self ) :

        chunk = ProjectileTarget(
                    projectile = ParticleID( 'n' ),
                    target = ParticleID( 'Fe56' ),
                    type = InteractionType.Nuclear,
                    reactions = [ Reaction( 'n,Fe56->total',
                                            [ 'n,Fe56->n,Fe56', 'n,Fe56->2n,Fe55[all]',
                                              'n,Fe56->3n,Fe54[all]', 'n,Fe56->a,Cr52[all]' ],
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1000001., 1000001. ],
                                                                     InterpolationType.Histogram ),
                                            [] ),
                                  Reaction( 'n,Fe56->n,Fe56',
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1e+6, 1e+6 ],
                                                                     InterpolationType.LinearLinear ),
                                            [ ReactionProduct( ParticleID( 'n' ), 1,
                                                               TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                        TabulatedAngularDistributions(
                                                                                          [ 1e-5, 20. ],
                                                                                          [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                            TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ) ],
                                            0, 0 ),
                                  Reaction( 'n,Fe56->2n,Fe55[all]',
                                            [ 'n,Fe56->2n,Fe55', 'n,Fe56->2n,Fe55_e1' ],
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 3. ],
                                                                     InterpolationType.Histogram ),
                                            [] ),
                                  Reaction( 'n,Fe56->2n,Fe55',
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 2.00001 ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, -1 ),
                                  Reaction( 'n,Fe56->2n,Fe55_e1',
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 1. ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, -1 ),
                                  Reaction( 'n,Fe56->3n,Fe54[all]',
                                            [ 'n,Fe56->3n,Fe54', 'n,Fe56->3n,Fe54_e1' ],
                                            TabulatedCrossSection( [ 5., 20. ], [ 0., 5. ],
                                                                     InterpolationType.Histogram ),
                                            [] ),
                                  Reaction( 'n,Fe56->3n,Fe54',
                                            TabulatedCrossSection( [ 5., 20. ], [ 0., 3.00001 ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, -5 ),
                                  Reaction( 'n,Fe56->3n,Fe54_e1',
                                            TabulatedCrossSection( [ 5., 20. ], [ 0., 2. ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, -5 ),
                                  Reaction( 'n,Fe56->a,Cr52[all]',
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1., 1. ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, 0 ) ] )

        # the projectile identifier can be changed
        newprojectile = ParticleID.proton()
        original = ParticleID.neutron()

        chunk.projectile_identifier = newprojectile

        self.assertEqual( newprojectile, chunk.projectile_identifier )

        chunk.projectile_identifier = original

        verify_chunk( self, chunk, False )

        # the target identifier can be changed
        newtarget = ParticleID( 1001 )
        original = ParticleID( 26056 )

        chunk.target_identifier = newtarget

        self.assertEqual( newtarget, chunk.target_identifier )

        chunk.target_identifier = original

        verify_chunk( self, chunk, False )

        # the interaction type can be changed
        newtype = InteractionType.Atomic
        original = InteractionType.Nuclear

        chunk.interaction_type = newtype

        self.assertEqual( newtype, chunk.interaction_type )

        chunk.interaction_type = original

        verify_chunk( self, chunk, False )

        # the reaction data can be changed
        newreactions = [ Reaction( 'n,Fe56->n,Fe56_e2',
                                   TabulatedCrossSection( [ 5., 20. ], [ 0., 15. ],
                                                          InterpolationType.LogLog ),
                                   [],
                                   0, -1 ) ]
        original = [ Reaction( 'n,Fe56->total',
                               [ 'n,Fe56->n,Fe56', 'n,Fe56->2n,Fe55[all]',
                                 'n,Fe56->3n,Fe54[all]', 'n,Fe56->a,Cr52[all]' ],
                               TabulatedCrossSection( [ 1e-5, 20. ], [ 1000001., 1000001. ],
                                                        InterpolationType.Histogram ),
                               [] ),
                     Reaction( 'n,Fe56->n,Fe56',
                               TabulatedCrossSection( [ 1e-5, 20. ], [ 1e+6, 1e+6 ],
                                                        InterpolationType.LinearLinear ),
                               [ ReactionProduct( ParticleID( 'n' ), 1,
                                                                TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                         TabulatedAngularDistributions(
                                                                                           [ 1e-5, 20. ],
                                                                                           [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                             TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ) ],
                               0, 0 ),
                     Reaction( 'n,Fe56->2n,Fe55[all]',
                               [ 'n,Fe56->2n,Fe55', 'n,Fe56->2n,Fe55_e1' ],
                               TabulatedCrossSection( [ 1., 20. ], [ 0., 3. ],
                                                        InterpolationType.Histogram ),
                               [] ),
                     Reaction( 'n,Fe56->2n,Fe55',
                               TabulatedCrossSection( [ 1., 20. ], [ 0., 2.00001 ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, -1 ),
                     Reaction( 'n,Fe56->2n,Fe55_e1',
                               TabulatedCrossSection( [ 1., 20. ], [ 0., 1. ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, -1 ),
                     Reaction( 'n,Fe56->3n,Fe54[all]',
                               [ 'n,Fe56->3n,Fe54', 'n,Fe56->3n,Fe54_e1' ],
                               TabulatedCrossSection( [ 5., 20. ], [ 0., 5. ],
                                                        InterpolationType.Histogram ),
                               [] ),
                     Reaction( 'n,Fe56->3n,Fe54',
                               TabulatedCrossSection( [ 5., 20. ], [ 0., 3.00001 ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, -5 ),
                     Reaction( 'n,Fe56->3n,Fe54_e1',
                               TabulatedCrossSection( [ 5., 20. ], [ 0., 2. ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, -5 ),
                     Reaction( 'n,Fe56->a,Cr52[all]',
                               TabulatedCrossSection( [ 1e-5, 20. ], [ 1., 1. ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, 0 ) ]

        chunk.reactions = newreactions

        self.assertEqual( newreactions, chunk.reactions )
        self.assertEqual( 1, chunk.number_reactions )

        chunk.reactions = original

        verify_chunk( self, chunk, False )

    def test_comparison( self ) :

        left = ProjectileTarget(
                   projectile = ParticleID( 'n' ),
                   target = ParticleID( 'Fe56' ),
                   type = InteractionType.Nuclear,
                   reactions = [ Reaction( 'n,Fe56->n,Fe56',
                                           TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                  InterpolationType.Histogram ),
                                           [],
                                           0, 0 ),
                                 Reaction( 'n,Fe56->n,Fe56_e1',
                                           TabulatedCrossSection( [ 1., 20. ], [ 0., 100. ],
                                                                  InterpolationType.LinearLinear ),
                                           [],
                                           0, -1 ) ] )
        equal = ProjectileTarget(
                    projectile = ParticleID( 'n' ),
                    target = ParticleID( 'Fe56' ),
                    type = InteractionType.Nuclear,
                    reactions = [ Reaction( 'n,Fe56->n,Fe56',
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                   InterpolationType.Histogram ),
                                            [],
                                            0, 0 ),
                                  Reaction( 'n,Fe56->n,Fe56_e1',
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 100. ],
                                                                   InterpolationType.LinearLinear ),
                                            [],
                                            0, -1 ) ] )
        different = ProjectileTarget(
                        projectile = ParticleID( 'n' ),
                        target = ParticleID( 'Fe56' ),
                        type = InteractionType.Nuclear,
                        reactions = [ Reaction( 'n,Fe56->n,Fe56',
                                                TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                       InterpolationType.Histogram ),
                                                [],
                                                0, 0 ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
