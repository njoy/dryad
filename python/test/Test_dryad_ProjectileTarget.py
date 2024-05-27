# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import ProjectileTarget
from dryad import Reaction
from dryad import TabulatedCrossSection
from dryad import InterpolationType

class Test_dryad_Reaction( unittest.TestCase ) :
    """Unit test for the Reaction class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # identifiers
            self.assertEqual( "n", chunk.projectile_identifier )
            self.assertEqual( "Fe56", chunk.target_identifier )

            # reactions
            reaction = chunk.reactions[0]
            self.assertEqual( "n,Fe56->n,Fe56", reaction.identifier )
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
            reaction = chunk.reactions[1]
            self.assertEqual( "n,Fe56->n,Fe56_e1", reaction.identifier )
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

        def verify_linearised_chunk( self, chunk ) :

            # identifiers
            self.assertEqual( "n", chunk.projectile_identifier )
            self.assertEqual( "Fe56", chunk.target_identifier )

            # reactions
            reaction = chunk.reactions[0]
            self.assertEqual( "n,Fe56->n,Fe56", reaction.identifier )
            self.assertAlmostEqual( 0, reaction.mass_difference_qvalue )
            self.assertAlmostEqual( 0, reaction.reaction_qvalue )
            self.assertEqual( 65, reaction.cross_section.number_points )
            self.assertEqual( 1, reaction.cross_section.number_regions )
            self.assertEqual( 65, len( reaction.cross_section.energies ) )
            self.assertEqual( 65, len( reaction.cross_section.values ) )
            self.assertEqual( 1, len( reaction.cross_section.boundaries ) )
            self.assertEqual( 1, len( reaction.cross_section.interpolants ) )
            self.assertAlmostEqual(  1e-5, reaction.cross_section.energies[0] )
            self.assertAlmostEqual(    5.0000075, reaction.cross_section.energies[16] )
            self.assertAlmostEqual(   10.000005, reaction.cross_section.energies[32] )
            self.assertAlmostEqual(   20., reaction.cross_section.energies[64] )
            self.assertAlmostEqual( 1000., reaction.cross_section.values[0] )
            self.assertAlmostEqual(  316.227766016838, reaction.cross_section.values[16] )
            self.assertAlmostEqual(  100., reaction.cross_section.values[32] )
            self.assertAlmostEqual(   10., reaction.cross_section.values[64] )
            self.assertEqual( 64, reaction.cross_section.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, reaction.cross_section.interpolants[0] )
            self.assertEqual( True, reaction.cross_section.is_linearised )
            reaction = chunk.reactions[1]
            self.assertEqual( "n,Fe56->n,Fe56_e1", reaction.identifier )
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
            self.assertEqual( True, chunk.is_linearised )

        # the data is given explicitly
        chunk = ProjectileTarget(
                    projectile = "n", target = "Fe56",
                    reactions = [ Reaction( "n,Fe56->n,Fe56", 0, 0,
                                            TabulatedCrossSection( [ 1e-5, 20. ], [ 1000., 10. ],
                                                                   InterpolationType.LogLinear ) ),
                                  Reaction( "n,Fe56->n,Fe56_e1", 0, -1,
                                            TabulatedCrossSection( [ 1., 20. ], [ 0., 100. ],
                                                                   InterpolationType.LinearLinear ) ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
