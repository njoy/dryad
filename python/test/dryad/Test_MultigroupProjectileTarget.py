# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import MultigroupProjectileTarget
from njoy.dryad import MultigroupReaction
from njoy.dryad import MultigroupReactionProduct
from njoy.dryad import MultigroupCrossSection
from njoy.dryad import InteractionType
from njoy.dryad import ReactionCategory
from njoy.dryad.id import ReactionID
from njoy.dryad.id import ParticleID

def make_multigroup_projectile_target() :

    return MultigroupProjectileTarget(
               projectile = ParticleID( 'n' ),
               target = ParticleID( 'Fe56' ),
               type = InteractionType.Nuclear,
               reactions = [ MultigroupReaction( ReactionID( 'n,Fe56->total' ),
                                                 [ ReactionID( 'n,Fe56->n,Fe56' ),
                                                   ReactionID( 'n,Fe56->2n,Fe55[all]' ) ],
                                                 MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 5., 4., 4., 5. ] ) ),
                             MultigroupReaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                                 MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 4., 3., 2., 1. ] ),
                                                 [ MultigroupReactionProduct( ParticleID( 'n' ), 1 ) ],
                                                 0., 0. ),
                             MultigroupReaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ),
                                                 [ ReactionID( 'n,Fe56->2n,Fe55' ),
                                                   ReactionID( 'n,Fe56->2n,Fe55_e1' ) ],
                                                 MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 1., 1., 2., 4. ] ) ),
                             MultigroupReaction( ReactionID( 'n,Fe56->2n,Fe55' ),
                                                 MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 0., 0., 1., 2. ] ),
                                                 [], 0., -1. ),
                             MultigroupReaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                                 MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 0., 0., 0., 1. ] ),
                                                 [], 0., -1. ) ] )

def verify_chunk( self, chunk ) :

    # documentation
    self.assertIsNone( chunk.documentation.library )
    self.assertIsNone( chunk.documentation.version )
    self.assertIsNone( chunk.documentation.description )

    # identifiers
    self.assertEqual( ParticleID( 'n' ), chunk.projectile_identifier )
    self.assertEqual( ParticleID( 'Fe56' ), chunk.target_identifier )

    # interaction type
    self.assertEqual( InteractionType.Nuclear, chunk.interaction_type )

    # reactions are present
    self.assertEqual( 5, chunk.number_reactions )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->total' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->n,Fe56' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ) ) )
    self.assertEqual( False, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56' ) ) )

    # reactions
    reaction = chunk.reactions[0]
    self.assertEqual( ReactionID( 'n,Fe56->total' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Summation, reaction.category )
    self.assertEqual( False, reaction.is_primary_reaction )
    self.assertEqual( True, reaction.is_summation_reaction )
    self.assertIsNone( reaction.mass_difference_qvalue )
    self.assertIsNone( reaction.reaction_qvalue )
    self.assertEqual( 3, reaction.number_partial_reactions )
    self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.partial_reaction_identifiers[0] )
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[1] )
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[2] )
    self.assertEqual( False, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 5., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 4., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 4., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 5., reaction.cross_section.values[3] )

    reaction = chunk.reactions[1]
    self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Primary, reaction.category )
    self.assertEqual( True, reaction.is_primary_reaction )
    self.assertEqual( False, reaction.is_summation_reaction )
    self.assertAlmostEqual( 0., reaction.mass_difference_qvalue )
    self.assertAlmostEqual( 0., reaction.reaction_qvalue )
    self.assertEqual( 0, reaction.number_partial_reactions )
    self.assertEqual( True, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 4., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 3., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 2., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 1., reaction.cross_section.values[3] )
    product = reaction.product( ParticleID( 'n' ) )
    self.assertEqual( 1, product.multiplicity )

    reaction = chunk.reactions[2]
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55[all]' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Summation, reaction.category )
    self.assertEqual( False, reaction.is_primary_reaction )
    self.assertEqual( True, reaction.is_summation_reaction )
    self.assertIsNone( reaction.mass_difference_qvalue )
    self.assertIsNone( reaction.reaction_qvalue )
    self.assertEqual( 2, reaction.number_partial_reactions )
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[0] )
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[1] )
    self.assertEqual( False, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 1., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 1., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 2., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 4., reaction.cross_section.values[3] )

    reaction = chunk.reactions[3]
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Primary, reaction.category )
    self.assertEqual( True, reaction.is_primary_reaction )
    self.assertEqual( False, reaction.is_summation_reaction )
    self.assertAlmostEqual( 0., reaction.mass_difference_qvalue )
    self.assertAlmostEqual( -1., reaction.reaction_qvalue )
    self.assertEqual( 0, reaction.number_partial_reactions )
    self.assertEqual( False, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 1., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 2., reaction.cross_section.values[3] )

    reaction = chunk.reactions[4]
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Primary, reaction.category )
    self.assertEqual( True, reaction.is_primary_reaction )
    self.assertEqual( False, reaction.is_summation_reaction )
    self.assertAlmostEqual( 0., reaction.mass_difference_qvalue )
    self.assertAlmostEqual( -1., reaction.reaction_qvalue )
    self.assertEqual( 0, reaction.number_partial_reactions )
    self.assertEqual( False, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 0., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 1., reaction.cross_section.values[3] )

    reaction = chunk.reaction( ReactionID( 'n,Fe56->total' ) )
    self.assertEqual( ReactionID( 'n,Fe56->total' ), reaction.identifier )
    self.assertEqual( 3, reaction.number_partial_reactions )

    reaction = chunk.reaction( ReactionID( 'n,Fe56->n,Fe56' ) )
    self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.identifier )
    self.assertEqual( True, reaction.has_products )

    # covariance data
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

    # reactions are present
    self.assertEqual( 5, chunk.number_reactions )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->total' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->n,Fe56' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55' ) ) )
    self.assertEqual( True, chunk.has_reaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ) ) )
    self.assertEqual( False, chunk.has_reaction( ReactionID( 'n,Fe56->p,Mn56' ) ) )

    # reactions
    reaction = chunk.reactions[0]
    self.assertEqual( ReactionID( 'n,Fe56->total' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Summation, reaction.category )
    self.assertEqual( False, reaction.is_primary_reaction )
    self.assertEqual( True, reaction.is_summation_reaction )
    self.assertIsNone( reaction.mass_difference_qvalue )
    self.assertIsNone( reaction.reaction_qvalue )
    self.assertEqual( 3, reaction.number_partial_reactions )
    self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.partial_reaction_identifiers[0] )
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[1] )
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[2] )
    self.assertEqual( False, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 4., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 3., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 3., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 4., reaction.cross_section.values[3] )

    reaction = chunk.reactions[1]
    self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Primary, reaction.category )
    self.assertEqual( True, reaction.is_primary_reaction )
    self.assertEqual( False, reaction.is_summation_reaction )
    self.assertAlmostEqual( 0., reaction.mass_difference_qvalue )
    self.assertAlmostEqual( 0., reaction.reaction_qvalue )
    self.assertEqual( 0, reaction.number_partial_reactions )
    self.assertEqual( True, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 4., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 3., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 2., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 1., reaction.cross_section.values[3] )
    product = reaction.product( ParticleID( 'n' ) )
    self.assertEqual( 1, product.multiplicity )

    reaction = chunk.reactions[2]
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55[all]' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Summation, reaction.category )
    self.assertEqual( False, reaction.is_primary_reaction )
    self.assertEqual( True, reaction.is_summation_reaction )
    self.assertIsNone( reaction.mass_difference_qvalue )
    self.assertIsNone( reaction.reaction_qvalue )
    self.assertEqual( 2, reaction.number_partial_reactions )
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.partial_reaction_identifiers[0] )
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.partial_reaction_identifiers[1] )
    self.assertEqual( False, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 1., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 3., reaction.cross_section.values[3] )

    reaction = chunk.reactions[3]
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Primary, reaction.category )
    self.assertEqual( True, reaction.is_primary_reaction )
    self.assertEqual( False, reaction.is_summation_reaction )
    self.assertAlmostEqual( 0., reaction.mass_difference_qvalue )
    self.assertAlmostEqual( -1., reaction.reaction_qvalue )
    self.assertEqual( 0, reaction.number_partial_reactions )
    self.assertEqual( False, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 1., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 2., reaction.cross_section.values[3] )

    reaction = chunk.reactions[4]
    self.assertEqual( ReactionID( 'n,Fe56->2n,Fe55_e1' ), reaction.identifier )
    self.assertEqual( ReactionCategory.Primary, reaction.category )
    self.assertEqual( True, reaction.is_primary_reaction )
    self.assertEqual( False, reaction.is_summation_reaction )
    self.assertAlmostEqual( 0., reaction.mass_difference_qvalue )
    self.assertAlmostEqual( -1., reaction.reaction_qvalue )
    self.assertEqual( 0, reaction.number_partial_reactions )
    self.assertEqual( False, reaction.has_products )
    self.assertEqual( 4, reaction.cross_section.number_groups )
    self.assertAlmostEqual( 0., reaction.cross_section.values[0] )
    self.assertAlmostEqual( 0., reaction.cross_section.values[1] )
    self.assertAlmostEqual( 0., reaction.cross_section.values[2] )
    self.assertAlmostEqual( 1., reaction.cross_section.values[3] )

    reaction = chunk.reaction( ReactionID( 'n,Fe56->total' ) )
    self.assertEqual( ReactionID( 'n,Fe56->total' ), reaction.identifier )
    self.assertEqual( 3, reaction.number_partial_reactions )

    reaction = chunk.reaction( ReactionID( 'n,Fe56->n,Fe56' ) )
    self.assertEqual( ReactionID( 'n,Fe56->n,Fe56' ), reaction.identifier )
    self.assertEqual( True, reaction.has_products )

    # covariance data
    self.assertIsNone( chunk.covariance_data )

class Test_MultigroupProjectileTarget( unittest.TestCase ) :
    """Unit test for the MultigroupProjectileTarget class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk = make_multigroup_projectile_target()

        verify_chunk( self, chunk )

    def test_summation( self ) :

        chunk = make_multigroup_projectile_target()
        chunk.calculate_summation_cross_sections()

        verify_correct_summation( self, chunk )

    def test_setter_functions( self ) :

        chunk = make_multigroup_projectile_target()

        # the projectile identifier can be changed
        newprojectile = ParticleID.proton()
        original = ParticleID.neutron()

        chunk.projectile_identifier = newprojectile

        self.assertEqual( newprojectile, chunk.projectile_identifier )

        chunk.projectile_identifier = original

        verify_chunk( self, chunk )

        # the target identifier can be changed
        newtarget = ParticleID( 'H1' )
        original = ParticleID( 'Fe56' )

        chunk.target_identifier = newtarget

        self.assertEqual( newtarget, chunk.target_identifier )

        chunk.target_identifier = original

        verify_chunk( self, chunk )

        # the interaction type can be changed
        newtype = InteractionType.Atomic
        original = InteractionType.Nuclear

        chunk.interaction_type = newtype

        self.assertEqual( newtype, chunk.interaction_type )

        chunk.interaction_type = original

        verify_chunk( self, chunk )

        # the reaction data can be changed
        newreactions = [ MultigroupReaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                             MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 0., 0., 0., 1. ] ),
                                             [], 0., -1. ) ]
        original = [ MultigroupReaction( ReactionID( 'n,Fe56->total' ),
                                         [ ReactionID( 'n,Fe56->n,Fe56' ),
                                           ReactionID( 'n,Fe56->2n,Fe55[all]' ) ],
                                         MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 5., 4., 4., 5. ] ) ),
                     MultigroupReaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                         MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 4., 3., 2., 1. ] ),
                                         [ MultigroupReactionProduct( ParticleID( 'n' ), 1 ) ],
                                         0., 0. ),
                     MultigroupReaction( ReactionID( 'n,Fe56->2n,Fe55[all]' ),
                                         [ ReactionID( 'n,Fe56->2n,Fe55' ),
                                           ReactionID( 'n,Fe56->2n,Fe55_e1' ) ],
                                         MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 1., 1., 2., 4. ] ) ),
                     MultigroupReaction( ReactionID( 'n,Fe56->2n,Fe55' ),
                                         MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 0., 0., 1., 2. ] ),
                                         [], 0., -1. ),
                     MultigroupReaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                         MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 0., 0., 0., 1. ] ),
                                         [], 0., -1. ) ]

        chunk.reactions = newreactions

        self.assertEqual( newreactions, chunk.reactions )
        self.assertEqual( 1, chunk.number_reactions )

        chunk.reactions = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = MultigroupProjectileTarget(
                   projectile = ParticleID.neutron(),
                   target = ParticleID( 'Fe56' ),
                   type = InteractionType.Nuclear,
                   reactions = [ MultigroupReaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                                     MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 4., 3., 2., 1. ] ),
                                                     [], 0., 0. ) ] )
        equal = MultigroupProjectileTarget(
                    projectile = ParticleID.neutron(),
                    target = ParticleID( 'Fe56' ),
                    type = InteractionType.Nuclear,
                    reactions = [ MultigroupReaction( ReactionID( 'n,Fe56->n,Fe56' ),
                                                      MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 4., 3., 2., 1. ] ),
                                                      [], 0., 0. ) ] )
        different = MultigroupProjectileTarget(
                        projectile = ParticleID.neutron(),
                        target = ParticleID( 'Fe56' ),
                        type = InteractionType.Nuclear,
                        reactions = [ MultigroupReaction( ReactionID( 'n,Fe56->2n,Fe55_e1' ),
                                                          MultigroupCrossSection( [ 1., 2., 3., 4., 5. ], [ 0., 0., 0., 1. ] ),
                                                          [], 0., -1. ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
