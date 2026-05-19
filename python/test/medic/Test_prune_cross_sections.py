# standard imports
import unittest

# third party imports

# local imports
from njoy.medic import prune_cross_sections

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

def make_projectile_target() :

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
               resonances = None )

def verify_chunk( self, chunk ) :

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
        self.assertAlmostEqual(    4., reaction.cross_section.energies[0] )
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
        self.assertAlmostEqual(   4., reaction.cross_section.energies[0] )
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
        self.assertAlmostEqual(  4., reaction.cross_section.energies[0] )
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
        self.assertAlmostEqual(  4., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 2.00001 / 19. * 3., reaction.cross_section.values[0] )
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
        self.assertAlmostEqual(  4., reaction.cross_section.energies[0] )
        self.assertAlmostEqual( 20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 3. / 19., reaction.cross_section.values[0] )
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
        self.assertAlmostEqual(   4., reaction.cross_section.energies[0] )
        self.assertAlmostEqual(  20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 1., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

class Test_prune_cross_sections( unittest.TestCase ) :
    """Unit test for the prune_cross_sections function."""

    def test_component( self ) :

        chunk = make_projectile_target()
        prune_cross_sections( 4, 20, chunk )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
