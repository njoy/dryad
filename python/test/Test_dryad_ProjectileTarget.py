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
from dryad.id import ParticleID

def verify_chunk( self, chunk ) :

    # identifiers
    self.assertEqual( ParticleID( 'n' ), chunk.projectile_identifier )
    self.assertEqual( ParticleID( 'Fe56' ), chunk.target_identifier )

    # interaction type
    self.assertEqual( InteractionType.Nuclear, chunk.interaction_type )

    # resonance parameters are not present
    self.assertEqual( None, chunk.resonances )

    # reactions are present
    self.assertEqual( 2, chunk.number_reactions )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->n,Fe56' ) )
    self.assertEqual( True, chunk.has_reaction( 'n,Fe56->n,Fe56_e1' ) )
    self.assertEqual( False, chunk.has_reaction( 'some unknown reaction' ) )

    # reactions[0] and reaction( 'n,Fe56->n,Fe56' )
    for reaction in [ chunk.reactions[0], chunk.reaction( 'n,Fe56->n,Fe56' ) ] :

        self.assertEqual( 'n,Fe56->n,Fe56', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual( False, reaction.is_linearised )
        self.assertAlmostEqual( 0, reaction.mass_difference_qvalue )
        self.assertAlmostEqual( 0, reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(  1e-5, reaction.cross_section.energies[0] )
        self.assertAlmostEqual(   20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual( 1000., reaction.cross_section.values[0] )
        self.assertAlmostEqual(   10., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LogLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( False, reaction.cross_section.is_linearised )

    # reactions[1] and reaction( 'n,Fe56->n,Fe56_e1' )
    for reaction in [ chunk.reactions[1], chunk.reaction( 'n,Fe56->n,Fe56_e1' ) ] :

        self.assertEqual( 'n,Fe56->n,Fe56_e1', reaction.identifier )
        self.assertEqual( ReactionCategory.Primary, reaction.category )
        self.assertEqual( False, reaction.is_summation_reaction )
        self.assertEqual( True, reaction.is_primary_reaction )
        self.assertEqual( False, reaction.has_products )
        self.assertEqual( True, reaction.is_linearised )
        self.assertAlmostEqual( 0, reaction.mass_difference_qvalue )
        self.assertAlmostEqual( -1, reaction.reaction_qvalue )
        self.assertEqual( 2, reaction.cross_section.number_points )
        self.assertEqual( 1, reaction.cross_section.number_regions )
        self.assertEqual( 2, len( reaction.cross_section.energies ) )
        self.assertEqual( 2, len( reaction.cross_section.values ) )
        self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
        self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
        self.assertAlmostEqual(   1., reaction.cross_section.energies[0] )
        self.assertAlmostEqual(  20., reaction.cross_section.energies[1] )
        self.assertAlmostEqual(   0., reaction.cross_section.values[0] )
        self.assertAlmostEqual( 100., reaction.cross_section.values[1] )
        self.assertEqual( 1, reaction.cross_section.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
        self.assertEqual( True, reaction.cross_section.is_linearised )

    # metadata
    self.assertEqual( False, chunk.is_linearised )

class Test_dryad_ProjectileTarget( unittest.TestCase ) :
    """Unit test for the ProjectileTarget class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk = ProjectileTarget(
                    projectile = ParticleID( 'n' ),
                    target = ParticleID( 'Fe56' ),
                    type = InteractionType.Nuclear,
                    reactions = [ Reaction( 'n,Fe56->n,Fe56',
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                   InterpolationType.LogLinear ),
                                            [],
                                            0, 0 ),
                                  Reaction( 'n,Fe56->n,Fe56_e1',
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 100. ],
                                                                   InterpolationType.LinearLinear ),
                                            [],
                                            0, -1 ) ] )

        verify_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = ProjectileTarget(
                    projectile = ParticleID( 'n' ),
                    target = ParticleID( 'Fe56' ),
                    type = InteractionType.Nuclear,
                    reactions = [ Reaction( 'n,Fe56->n,Fe56',
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                   InterpolationType.LogLinear ),
                                            [],
                                            0, 0 ),
                                  Reaction( 'n,Fe56->n,Fe56_e1',
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 100. ],
                                                                   InterpolationType.LinearLinear ),
                                            [],
                                            0, -1 ) ] )

        # the reaction data can be changed
        newreactions = [ Reaction( 'n,Fe56->n,Fe56_e2',
                                   TabulatedCrossSection( [ 5., 20. ], [ 0., 15. ],
                                                          InterpolationType.LogLog ),
                                   [],
                                   0, -1 ) ]
        original = [ Reaction( 'n,Fe56->n,Fe56',
                               TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                      InterpolationType.LogLinear ),
                               [],
                               0, 0 ),
                     Reaction( 'n,Fe56->n,Fe56_e1',
                               TabulatedCrossSection( [ 1., 20. ], [ 0., 100. ],
                                                      InterpolationType.LinearLinear ),
                               [],
                               0, -1 ) ]

        chunk.reactions = newreactions

        self.assertEqual( newreactions, chunk.reactions )
        self.assertEqual( 1, chunk.number_reactions )

        chunk.reactions = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = ProjectileTarget(
                   projectile = ParticleID( 'n' ),
                   target = ParticleID( 'Fe56' ),
                   type = InteractionType.Nuclear,
                   reactions = [ Reaction( 'n,Fe56->n,Fe56',
                                           TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                  InterpolationType.LogLinear ),
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
                                                                   InterpolationType.LogLinear ),
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
                                                                       InterpolationType.LogLinear ),
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
