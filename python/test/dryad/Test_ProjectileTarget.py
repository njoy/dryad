# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import ProjectileTarget
from njoy.dryad import Reaction
from njoy.dryad import TabulatedCrossSection
from njoy.dryad import InterpolationType
from njoy.dryad import InteractionType
from njoy.dryad import ReactionCategory
from njoy.dryad.id import ReactionID
from njoy.dryad import DistributionDataType
from njoy.dryad import ReferenceFrame
from njoy.dryad import TabulatedAngularDistribution
from njoy.dryad import TabulatedAngularDistributions
from njoy.dryad import ReactionProduct
from njoy.dryad import TwoBodyDistributionData
from njoy.dryad.id import ParticleID
from njoy.dryad.id import ChannelID
from njoy.dryad import TabulatedMultiplicity
from njoy.dryad import Particle
from njoy.dryad.resonances import ParticlePair
from njoy.dryad.resonances import ChannelRadii
from njoy.dryad.resonances import Channel
from njoy.dryad.resonances import ResonanceTable
from njoy.dryad.resonances import Formalism
from njoy.dryad.resonances import BoundaryCondition
from njoy.dryad.resonances import SpinGroup
from njoy.dryad.resonances import CompoundSystem
from njoy.dryad.resonances import ResonanceParameters
from njoy.dryad.resonances import TabulatedRadius

def make_projectile_target( normalise ) :

    return ProjectileTarget(
               projectile = ParticleID( 'n' ),
               target = ParticleID( 'Fe56' ),
               type = InteractionType.Nuclear,
               reactions = [ Reaction( ReactionID( 'n,Fe56->total' ),
                                       [ ReactionID( 'n,Fe56->n,Fe56' ), ReactionID( 'n,Fe56->2n,Fe55[all]' ),
                                         ReactionID( 'n,Fe56->p,Mn56[all]' ), ReactionID( 'n,Fe56->a,Cr53[all]' ) ],
                                       TabulatedCrossSection( [ 1e-5, 20. ], [ 1000001., 1000001. ],
                                                                InterpolationType.Histogram ),
                                       [] ),
                             Reaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                       TabulatedCrossSection( [ 1e-5, 20. ], [ 1e+6, 1e+6 ],
                                                                InterpolationType.LinearLinear ),
                                       [ ReactionProduct( ParticleID( 'n' ), 1,
                                                          TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                   TabulatedAngularDistributions(
                                                                                     [ 1e-5, 20. ],
                                                                                     [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                       TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ) ],
                                       0, 0 ),
                             Reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ),
                                       [ ReactionID( 'n,Fe56->2n,Fe55' ),
                                        ReactionID( 'n,Fe56->2n,Fe55_e1' ) ],
                                       TabulatedCrossSection( [ 1., 20. ], [ 0., 3. ],
                                                                InterpolationType.Histogram ),
                                       [] ),
                             Reaction( ReactionID( 'n,Fe56->2n,Fe55' ),
                                       TabulatedCrossSection( [ 1., 20. ], [ 0., 2.00001 ],
                                                                InterpolationType.LinearLinear ),
                                       [],
                                       0, -1 ),
                             Reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                       TabulatedCrossSection( [ 1., 20. ], [ 0., 1. ],
                                                                InterpolationType.LinearLinear ),
                                       [],
                                       0, -1 ),
                             Reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ),
                                       [ ReactionID( 'n,Fe56->p,Mn56' ),
                                        ReactionID( 'n,Fe56->p,Mn56_e1' ) ],
                                       TabulatedCrossSection( [ 5., 20. ], [ 0., 5. ],
                                                                InterpolationType.Histogram ),
                                       [] ),
                             Reaction( ReactionID( 'n,Fe56->p,Mn56' ),
                                       TabulatedCrossSection( [ 5., 20. ], [ 0., 3.00001 ],
                                                                InterpolationType.LinearLinear ),
                                       [],
                                       0, -5 ),
                             Reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ),
                                       TabulatedCrossSection( [ 5., 20. ], [ 0., 2. ],
                                                                InterpolationType.LinearLinear ),
                                       [],
                                       0, -5 ),
                             Reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ),
                                       TabulatedCrossSection( [ 1e-5, 20. ], [ 1., 1. ],
                                                                InterpolationType.LinearLinear ),
                                       [],
                                       0, 0 ) ],
               resonances = None,
               normalise = normalise )

def verify_chunk( self, chunk, normalise ) :

    # documentation
    self.assertIsNone( chunk.documentation.library )
    self.assertIsNone( chunk.documentation.version )
    self.assertIsNone( chunk.documentation.description )

    # identifiers
    self.assertEqual( ParticleID( 'n' ), chunk.projectile_identifier )
    self.assertEqual( ParticleID( 'Fe56' ), chunk.target_identifier )

    # interaction type
    self.assertEqual( InteractionType.Nuclear, chunk.interaction_type )

    # particle data is not present
    self.assertIsNone( chunk.particle_data )

    # resonance parameters are not present
    self.assertIsNone( chunk.resonances )

    # reactions are present
    self.assertEqual( 9, chunk.number_reactions )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->total' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->n,Fe56' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ) ) )
    #self.assertEqual( False, chunk.has_reaction( 'some unknown reaction' ) )

    # reactions[0] and reaction( 'n,Fe56->total' )
    for reaction in [ chunk.reactions[0], chunk.reaction( ReactionID( 'n,Fe56->total' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->total' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 6, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[1] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[2] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.partial_reaction_identifiers[3] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.partial_reaction_identifiers[4] )
        self.assertEqual( ReactionID( 'n,Fe56->a,Cr53[all]' ), reaction.partial_reaction_identifiers[5] )
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
    for reaction in [ chunk.reactions[1], chunk.reaction( ReactionID( 'n,Fe56->n,Fe56' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.identifier )
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
    for reaction in [ chunk.reactions[2], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55[all]' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[1] )
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
    for reaction in [ chunk.reactions[3], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.identifier )
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
    for reaction in [ chunk.reactions[4], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.identifier )
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

    # reactions[5] and reaction( 'n,Fe56->p,Mn56[all]' )
    for reaction in [ chunk.reactions[5], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56[all]' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.partial_reaction_identifiers[1] )
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

    # reactions[6] and reaction( 'n,Fe56->p,Mn56' )
    for reaction in [ chunk.reactions[6], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.identifier )
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

    # reactions[7] and reaction( 'n,Fe56->p,Mn56_e1' )
    for reaction in [ chunk.reactions[7], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.identifier )
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

    # reactions[8] and reaction( 'n,Fe56->a,Cr53[all]' )
    for reaction in [ chunk.reactions[8], chunk.reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->a,Cr53[all]' ), reaction.identifier )
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

def verify_correct_unionisation( self, chunk, exclude ) :

    # documentation
    self.assertIsNone( chunk.documentation.library )
    self.assertIsNone( chunk.documentation.version )
    self.assertIsNone( chunk.documentation.description )

    # identifiers
    self.assertEqual( ParticleID( 'n' ), chunk.projectile_identifier )
    self.assertEqual( ParticleID( 'Fe56' ), chunk.target_identifier )

    # interaction type
    self.assertEqual( InteractionType.Nuclear, chunk.interaction_type )

    # particle data is not present
    self.assertIsNone( chunk.particle_data )

    # resonance parameters are not present
    self.assertIsNone( chunk.resonances )

    # reactions are present
    self.assertEqual( 9, chunk.number_reactions )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->total' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->n,Fe56' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ) ) )
    #self.assertEqual( False, chunk.has_reaction( 'some unknown reaction' ) ) )

    # reactions[0] and reaction( 'n,Fe56->total' )
    for reaction in [ chunk.reactions[0], chunk.reaction( ReactionID( 'n,Fe56->total' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->total' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 6, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[1] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[2] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.partial_reaction_identifiers[3] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.partial_reaction_identifiers[4] )
        self.assertEqual( ReactionID( 'n,Fe56->a,Cr53[all]' ), reaction.partial_reaction_identifiers[5] )
        if exclude :

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

        else :

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
            self.assertAlmostEqual( 1000001., reaction.cross_section.values[2] )
            self.assertAlmostEqual( 1000001., reaction.cross_section.values[3] )
            self.assertEqual( 3, reaction.cross_section.boundaries[0] )
            self.assertEqual( InterpolationType.Histogram, reaction.cross_section.interpolants[0] )
            self.assertEqual( False, reaction.cross_section.is_linearised )

    # reactions[1] and reaction( 'n,Fe56->n,Fe56' )
    for reaction in [ chunk.reactions[1], chunk.reaction( ReactionID( 'n,Fe56->n,Fe56' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( True, reaction.has_products )
        self.assertAlmostEqual( 0, reaction.mass_difference_qvalue )
        self.assertAlmostEqual( 0, reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
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
        self.assertAlmostEqual( 1000000., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1000000., reaction.cross_section.values[1] )
        self.assertAlmostEqual( 1000000., reaction.cross_section.values[2] )
        self.assertAlmostEqual( 1000000., reaction.cross_section.values[3] )
        self.assertEqual( 3, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[2] and reaction( 'n,Fe56->2n,Fe55[all]' )
    for reaction in [ chunk.reactions[2], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55[all]' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[1] )
        if exclude :

            self.assertEqual( 2, reaction.cross_section.number_points )
            self.assertEqual( 1, reaction.cross_section.number_regions )
            self.assertEqual( 2, len( reaction.cross_section.energies ) )
            self.assertEqual( 2, len( reaction.cross_section.values ) )
            self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
            self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
            self.assertAlmostEqual(  1., reaction.cross_section.energies[0] )
            self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
            self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
            self.assertAlmostEqual( 3., reaction.cross_section.values[1] )
            self.assertEqual( 1, reaction.cross_section.boundaries[0] )
            self.assertEqual( InterpolationType.Histogram, reaction.cross_section.interpolants[0] )
            self.assertEqual( False, reaction.cross_section.is_linearised )

        else :

            self.assertEqual( 2, reaction.cross_section.number_regions )
            self.assertEqual( 4, len( reaction.cross_section.energies ) )
            self.assertEqual( 4, len( reaction.cross_section.values ) )
            self.assertEqual( 2, len( reaction.cross_section.boundaries ) )
            self.assertEqual( 2, len( reaction.cross_section.interpolants ) )
            self.assertAlmostEqual(  1e-5, reaction.cross_section.energies[0] )
            self.assertAlmostEqual(    1., reaction.cross_section.energies[1] )
            self.assertAlmostEqual(    5., reaction.cross_section.energies[2] )
            self.assertAlmostEqual(   20., reaction.cross_section.energies[3] )
            self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
            self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
            self.assertAlmostEqual( 0., reaction.cross_section.values[2] )
            self.assertAlmostEqual( 3., reaction.cross_section.values[3] )
            self.assertEqual( 1, reaction.cross_section.boundaries[0] )
            self.assertEqual( 3, reaction.cross_section.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
            self.assertEqual( InterpolationType.Histogram, reaction.cross_section.interpolants[1] )
            self.assertEqual( False, reaction.cross_section.is_linearised )

    # reactions[3] and reaction( 'n,Fe56->2n,Fe55' )
    for reaction in [ chunk.reactions[3], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -1., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 4, len( reaction.cross_section.energies ) )
        self.assertEqual( 4, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1e-5, reaction.cross_section.energies[0] )
        self.assertAlmostEqual(    1., reaction.cross_section.energies[1] )
        self.assertAlmostEqual(    5., reaction.cross_section.energies[2] )
        self.assertAlmostEqual(   20., reaction.cross_section.energies[3] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
        self.assertAlmostEqual( 2.00001 / 19. * 4., reaction.cross_section.values[2] )
        self.assertAlmostEqual( 2.00001, reaction.cross_section.values[3] )
        self.assertEqual( 3, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[4] and reaction( 'n,Fe56->2n,Fe55_e1' )
    for reaction in [ chunk.reactions[4], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -1., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
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
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
        self.assertAlmostEqual( 1. / 19. * 4., reaction.cross_section.values[2] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[3] )
        self.assertEqual( 3, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[5] and reaction( 'n,Fe56->p,Mn56[all]' )
    for reaction in [ chunk.reactions[5], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56[all]' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.partial_reaction_identifiers[1] )
        if exclude :

            self.assertEqual( 2, reaction.cross_section.number_points )
            self.assertEqual( 1, reaction.cross_section.number_regions )
            self.assertEqual( 2, len( reaction.cross_section.energies ) )
            self.assertEqual( 2, len( reaction.cross_section.values ) )
            self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
            self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
            self.assertAlmostEqual(  5., reaction.cross_section.energies[0] )
            self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
            self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
            self.assertAlmostEqual( 5., reaction.cross_section.values[1] )
            self.assertEqual( 1, reaction.cross_section.boundaries[0] )
            self.assertEqual( InterpolationType.Histogram, reaction.cross_section.interpolants[0] )
            self.assertEqual( False, reaction.cross_section.is_linearised )

        else :

            self.assertEqual( 4, reaction.cross_section.number_points )
            self.assertEqual( 2, reaction.cross_section.number_regions )
            self.assertEqual( 4, len( reaction.cross_section.energies ) )
            self.assertEqual( 4, len( reaction.cross_section.values ) )
            self.assertEqual( 2, len( reaction.cross_section.boundaries ) )
            self.assertEqual( 2, len( reaction.cross_section.interpolants ) )
            self.assertAlmostEqual(  1e-5, reaction.cross_section.energies[0] )
            self.assertAlmostEqual(    1., reaction.cross_section.energies[1] )
            self.assertAlmostEqual(    5., reaction.cross_section.energies[2] )
            self.assertAlmostEqual(   20., reaction.cross_section.energies[3] )
            self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
            self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
            self.assertAlmostEqual( 0., reaction.cross_section.values[2] )
            self.assertAlmostEqual( 5., reaction.cross_section.values[3] )
            self.assertEqual( 2, reaction.cross_section.boundaries[0] )
            self.assertEqual( 3, reaction.cross_section.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
            self.assertEqual( InterpolationType.Histogram, reaction.cross_section.interpolants[1] )
            self.assertEqual( False, reaction.cross_section.is_linearised )


    # reactions[6] and reaction( 'n,Fe56->p,Mn56' )
    for reaction in [ chunk.reactions[6], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -5., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
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
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[2] )
        self.assertAlmostEqual( 3.00001, reaction.cross_section.values[3] )
        self.assertEqual( 3, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[7] and reaction( 'n,Fe56->p,Mn56_e1' )
    for reaction in [ chunk.reactions[7], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual( -5., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
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
        self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
        self.assertAlmostEqual( 0., reaction.cross_section.values[2] )
        self.assertAlmostEqual( 2., reaction.cross_section.values[3] )
        self.assertEqual( 3, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # reactions[8] and reaction( 'n,Fe56->a,Cr53[all]' )
    for reaction in [ chunk.reactions[8], chunk.reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->a,Cr53[all]' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual(  0., reaction.mass_difference_qvalue )
        self.assertEqual(  0., reaction.reaction_qvalue )
        self.assertEqual( 0, reaction.number_partial_reactions )
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
        self.assertAlmostEqual( 1., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[1] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[2] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[3] )
        self.assertEqual( 3, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    self.assertIsNone( chunk.covariance_data )

def verify_correct_summation( self, chunk ) :

    # documentation
    self.assertIsNone( chunk.documentation.library )
    self.assertIsNone( chunk.documentation.version )
    self.assertIsNone( chunk.documentation.description )

    # identifiers
    self.assertEqual( ParticleID( 'n' ), chunk.projectile_identifier )
    self.assertEqual( ParticleID( 'Fe56' ), chunk.target_identifier )

    # interaction type
    self.assertEqual( InteractionType.Nuclear, chunk.interaction_type )

    # particle database is not present
    self.assertIsNone( chunk.resonances )

    # resonance parameters are not present
    self.assertIsNone( chunk.resonances )

    # reactions are present
    self.assertEqual( 9, chunk.number_reactions )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->total' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->n,Fe56' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ) ) )
    #self.assertEqual( False, chunk.has_reaction( 'some unknown reaction' ) ) )

    # reactions[0] and reaction( 'n,Fe56->total' )
    for reaction in [ chunk.reactions[0], chunk.reaction( ReactionID( 'n,Fe56->total' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->total' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 6, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[1] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[2] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.partial_reaction_identifiers[3] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.partial_reaction_identifiers[4] )
        self.assertEqual( ReactionID( 'n,Fe56->a,Cr53[all]' ), reaction.partial_reaction_identifiers[5] )
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
    for reaction in [ chunk.reactions[1], chunk.reaction( ReactionID( 'n,Fe56->n,Fe56' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.identifier )
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
    for reaction in [ chunk.reactions[2], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55[all]' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[1] )
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
    for reaction in [ chunk.reactions[3], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.identifier )
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
    for reaction in [ chunk.reactions[4], chunk.reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.identifier )
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

    # reactions[5] and reaction( 'n,Fe56->p,Mn56[all]' )
    for reaction in [ chunk.reactions[5], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56[all]' ), reaction.identifier )
        self.assertEqual( ReactionCategory.Summation, reaction.category )
        self.assertEqual( True, reaction.is_summation_reaction )
        self.assertEqual( False, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertIsNone( reaction.mass_difference_qvalue )
        self.assertIsNone( reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.number_partial_reactions )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.partial_reaction_identifiers[0] )
        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.partial_reaction_identifiers[1] )
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

    # reactions[6] and reaction( 'n,Fe56->p,Mn56' )
    for reaction in [ chunk.reactions[6], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56' ), reaction.identifier )
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

    # reactions[7] and reaction( 'n,Fe56->p,Mn56_e1' )
    for reaction in [ chunk.reactions[7], chunk.reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->p,Mn56_e1' ), reaction.identifier )
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

    # reactions[8] and reaction( 'n,Fe56->a,Cr53[all]' )
    for reaction in [ chunk.reactions[8], chunk.reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ) ) ] :

        self.assertEqual( ReactionID( 'n,Fe56->a,Cr53[all]' ), reaction.identifier )
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

class Test_ProjectileTarget( unittest.TestCase ) :
    """Unit test for the ProjectileTarget class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk1 = make_projectile_target( False )
        chunk2 = make_projectile_target( True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

    def test_unionisation( self ) :

        chunk = make_projectile_target( False )
        chunk.unionise_cross_sections( False )

        verify_correct_unionisation( self, chunk, False )

        chunk = make_projectile_target( False )
        chunk.unionise_cross_sections( True )

        verify_correct_unionisation( self, chunk, True )

    def test_summation( self ) :

        chunk = make_projectile_target( False )
        chunk.calculate_summation_cross_sections()

        verify_correct_summation( self, chunk )

    def test_curation( self ) :

        # the data is given explicitly
        chunk = ProjectileTarget( projectile = ParticleID( 'n' ),
                                  target = ParticleID( 'Fe56' ),
                                  type = InteractionType.Nuclear,
                                  reactions = [ Reaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                                          TabulatedCrossSection( [ 1., 2., 2., 2., 4. ],    # <-- discontinuity with 3 points
                                                                                 [ 4., 3., 4., 5., 2. ] ),
                                                          [ ReactionProduct( ParticleID( 'n' ), TabulatedMultiplicity( [ 1., 2., 2., 2., 4. ],    # <-- discontinuity with 3 points
                                                                                                                       [ 1., 1., 2., 1., 1. ] ) ) ] ),
                                                Reaction( ReactionID( 'n,Fe56->g,Fe57[all]' ),
                                                          TabulatedCrossSection( [ 1., 3., 3., 3., 4. ],    # <-- discontinuity with 3 points
                                                                                 [ 4., 3., 4., 5., 2. ] ),
                                                          [ ReactionProduct( ParticleID( 'g' ), TabulatedMultiplicity( [ 1., 3., 3., 3., 4. ],    # <-- discontinuity with 3 points
                                                                                                                       [ 1., 2., 3., 4., 5. ] ) ) ] ) ] )

        # the tabulated data is not curated
        self.assertEqual( False, chunk.reactions[0].cross_section.is_curated )
        self.assertEqual( False, chunk.reactions[0].products[0].multiplicity.is_curated )
        self.assertEqual( False, chunk.reactions[1].cross_section.is_curated )
        self.assertEqual( False, chunk.reactions[1].products[0].multiplicity.is_curated )

        # the tabulated data can be curated
        chunk.curate()

        self.assertEqual( True, chunk.reactions[0].cross_section.is_curated )
        self.assertEqual( True, chunk.reactions[0].products[0].multiplicity.is_curated )
        self.assertEqual( True, chunk.reactions[1].cross_section.is_curated )
        self.assertEqual( True, chunk.reactions[1].products[0].multiplicity.is_curated )

        # the data is given explicitly with resonance parameters
        neutron_mass = 1.00866491574
        photon_pair = ParticlePair( Particle( ParticleID.photon(), 0, 1, +1 ),
                                    Particle( ParticleID( 'Cl36[all]' ), 35.65932 * neutron_mass, 0, +1 ) )
        neutron_pair = ParticlePair( Particle( ParticleID.neutron(), neutron_mass, 0.5, +1 ),
                                     Particle( ParticleID( 'Cl35' ), 34.66845 * neutron_mass, 1.5, +1 ) )

        resonances = ResonanceParameters(
                       [ CompoundSystem( 1e-5, 1e+4,
                                         [ SpinGroup( [ Channel( ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                                                 neutron_pair, photon_pair, 0., None,
                                                                 ChannelRadii( 0. ), False ),
                                                        Channel( ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ),
                                                                 neutron_pair, neutron_pair, 0., None,
                                                                 ChannelRadii( TabulatedRadius( [ 1e-5, 1., 1., 1., 2e+7 ],    # <-- discontinuity with 3 points
                                                                                                [ 4., 4., 4.5, 5., 5. ] ) ) ) ],
                                                      ResonanceTable( [ ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' ),
                                                                        ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' ) ],
                                                                      [ 1. ], [ [ 2. ], [ 3. ] ] ),
                                                      Formalism.ReichMoore, BoundaryCondition.ShiftFactor ) ] ) ] )

        chunk = ProjectileTarget( projectile = ParticleID( 'n' ),
                                  target = ParticleID( 'Cl35' ),
                                  type = InteractionType.Nuclear,
                                  reactions = [ Reaction( ReactionID( 'n,Cl35->n,Cl35' ),
                                                          TabulatedCrossSection( [ 1., 2., 2., 2., 4. ],    # <-- discontinuity with 3 points
                                                                                 [ 4., 3., 4., 5., 2. ] ) ) ],
                                  resonances = resonances )

        # the tabulated data is not curated
        channel = chunk.resonances.resolved[0].spin_groups[0].channels[1]
        self.assertEqual( False, channel.channel_radii.penetrability_radius.is_curated )
        self.assertEqual( False, chunk.reactions[0].cross_section.is_curated )

        # the tabulated data can be curated
        chunk.curate()

        channel = chunk.resonances.resolved[0].spin_groups[0].channels[1]
        self.assertEqual( True, channel.channel_radii.penetrability_radius.is_curated )
        self.assertEqual( True, chunk.reactions[0].cross_section.is_curated )

    def test_setter_functions( self ) :

        chunk = ProjectileTarget(
                    projectile = ParticleID( 'n' ),
                    target = ParticleID( 'Fe56' ),
                    type = InteractionType.Nuclear,
                    reactions = [ Reaction( ReactionID( 'n,Fe56->total' ),
                                            [ ReactionID( 'n,Fe56->n,Fe56' ),
                                              ReactionID( 'n,Fe56->2n,Fe55[all]' ),
                                              ReactionID( 'n,Fe56->p,Mn56[all]' ),
                                              ReactionID( 'n,Fe56->a,Cr53[all]' ) ],
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1000001., 1000001. ],
                                                                     InterpolationType.Histogram ),
                                            [] ),
                                  Reaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1e+6, 1e+6 ],
                                                                     InterpolationType.LinearLinear ),
                                            [ ReactionProduct( ParticleID( 'n' ), 1,
                                                               TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                        TabulatedAngularDistributions(
                                                                                          [ 1e-5, 20. ],
                                                                                          [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                            TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ) ],
                                            0, 0 ),
                                  Reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ),
                                            [ ReactionID( 'n,Fe56->2n,Fe55' ),
                                              ReactionID( 'n,Fe56->2n,Fe55_e1' ) ],
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 3. ],
                                                                     InterpolationType.Histogram ),
                                            [] ),
                                  Reaction( ReactionID( 'n,Fe56->2n,Fe55' ),
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 2.00001 ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, -1 ),
                                  Reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 1. ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, -1 ),
                                  Reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ),
                                            [ ReactionID( 'n,Fe56->p,Mn56' ),
                                              ReactionID( 'n,Fe56->p,Mn56_e1' ) ],
                                            TabulatedCrossSection( [ 5., 20. ], [ 0., 5. ],
                                                                     InterpolationType.Histogram ),
                                            [] ),
                                  Reaction( ReactionID( 'n,Fe56->p,Mn56' ),
                                            TabulatedCrossSection( [ 5., 20. ], [ 0., 3.00001 ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, -5 ),
                                  Reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ),
                                            TabulatedCrossSection( [ 5., 20. ], [ 0., 2. ],
                                                                     InterpolationType.LinearLinear ),
                                            [],
                                            0, -5 ),
                                  Reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ),
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
        newtarget = ParticleID( "H1" )
        original = ParticleID( "Fe56" )

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
        newreactions = [ Reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                   TabulatedCrossSection( [ 5., 20. ], [ 0., 15. ],
                                                          InterpolationType.LogLog ),
                                   [],
                                   0, -1 ) ]
        original = [ Reaction( ReactionID( 'n,Fe56->total' ),
                               [ ReactionID( 'n,Fe56->n,Fe56' ),
                                 ReactionID( 'n,Fe56->2n,Fe55[all]' ),
                                 ReactionID( 'n,Fe56->p,Mn56[all]' ),
                                 ReactionID( 'n,Fe56->a,Cr53[all]' ) ],
                               TabulatedCrossSection( [ 1e-5, 20. ], [ 1000001., 1000001. ],
                                                        InterpolationType.Histogram ),
                               [] ),
                     Reaction( ReactionID( 'n,Fe56->n,Fe56' ),
                               TabulatedCrossSection( [ 1e-5, 20. ], [ 1e+6, 1e+6 ],
                                                        InterpolationType.LinearLinear ),
                               [ ReactionProduct( ParticleID( 'n' ), 1,
                                                                TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                                                         TabulatedAngularDistributions(
                                                                                           [ 1e-5, 20. ],
                                                                                           [ TabulatedAngularDistribution( [ -1., +1. ], [ 1., 1. ] ),
                                                                                             TabulatedAngularDistribution( [ -1., +1. ], [ 0.8, 1.2 ] ) ] ) ) ) ],
                               0, 0 ),
                     Reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ),
                               [ ReactionID( 'n,Fe56->2n,Fe55' ),
                                 ReactionID( 'n,Fe56->2n,Fe55_e1' ) ],
                               TabulatedCrossSection( [ 1., 20. ], [ 0., 3. ],
                                                        InterpolationType.Histogram ),
                               [] ),
                     Reaction( ReactionID( 'n,Fe56->2n,Fe55' ),
                               TabulatedCrossSection( [ 1., 20. ], [ 0., 2.00001 ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, -1 ),
                     Reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                               TabulatedCrossSection( [ 1., 20. ], [ 0., 1. ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, -1 ),
                     Reaction( ReactionID( 'n,Fe56->p,Mn56[all]' ),
                               [ ReactionID( 'n,Fe56->p,Mn56' ),
                                 ReactionID( 'n,Fe56->p,Mn56_e1' ) ],
                               TabulatedCrossSection( [ 5., 20. ], [ 0., 5. ],
                                                        InterpolationType.Histogram ),
                               [] ),
                     Reaction( ReactionID( 'n,Fe56->p,Mn56' ),
                               TabulatedCrossSection( [ 5., 20. ], [ 0., 3.00001 ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, -5 ),
                     Reaction( ReactionID( 'n,Fe56->p,Mn56_e1' ),
                               TabulatedCrossSection( [ 5., 20. ], [ 0., 2. ],
                                                        InterpolationType.LinearLinear ),
                               [],
                               0, -5 ),
                     Reaction( ReactionID( 'n,Fe56->a,Cr53[all]' ),
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
                   reactions = [ Reaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                           TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                  InterpolationType.Histogram ),
                                           [],
                                           0, 0 ),
                                 Reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                           TabulatedCrossSection( [ 1., 20. ], [ 0., 100. ],
                                                                  InterpolationType.LinearLinear ),
                                           [],
                                           0, -1 ) ] )
        equal = ProjectileTarget(
                    projectile = ParticleID( 'n' ),
                    target = ParticleID( 'Fe56' ),
                    type = InteractionType.Nuclear,
                    reactions = [ Reaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                   InterpolationType.Histogram ),
                                            [],
                                            0, 0 ),
                                  Reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 100. ],
                                                                   InterpolationType.LinearLinear ),
                                            [],
                                            0, -1 ) ] )
        different = ProjectileTarget(
                        projectile = ParticleID( 'n' ),
                        target = ParticleID( 'Fe56' ),
                        type = InteractionType.Nuclear,
                        reactions = [ Reaction( ReactionID( 'n,Fe56->n,Fe56' ),
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
