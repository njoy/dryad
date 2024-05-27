# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import Reaction
from dryad import TabulatedCrossSection
from dryad import InterpolationType

class Test_dryad_Reaction( unittest.TestCase ) :
    """Unit test for the Reaction class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # reaction identifier
            self.assertEqual( 'n,Fe56->n,Fe56_e1', chunk.identifier )

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

            # metadata
            self.assertEqual( False, chunk.is_linearised )

        def verify_linearised_chunk( self, chunk ) :

            # reaction identifier
            self.assertEqual( 'n,Fe56->n,Fe56_e1', chunk.identifier )

            # cross section
            self.assertEqual( 12, chunk.cross_section.number_points )
            self.assertEqual( 2, chunk.cross_section.number_regions )
            self.assertEqual( 12, len( chunk.cross_section.energies ) )
            self.assertEqual( 12, len( chunk.cross_section.values ) )
            self.assertEqual( 2, len( chunk.cross_section.boundaries ) )
            self.assertEqual( 2, len( chunk.cross_section.interpolants ) )
            self.assertAlmostEqual( 1.   , chunk.cross_section.energies[0] )
            self.assertAlmostEqual( 2.   , chunk.cross_section.energies[1] )
            self.assertAlmostEqual( 2.   , chunk.cross_section.energies[2] )
            self.assertAlmostEqual( 2.125, chunk.cross_section.energies[3] )
            self.assertAlmostEqual( 2.25 , chunk.cross_section.energies[4] )
            self.assertAlmostEqual( 2.5  , chunk.cross_section.energies[5] )
            self.assertAlmostEqual( 2.75 , chunk.cross_section.energies[6] )
            self.assertAlmostEqual( 3.   , chunk.cross_section.energies[7] )
            self.assertAlmostEqual( 3.25 , chunk.cross_section.energies[8] )
            self.assertAlmostEqual( 3.5  , chunk.cross_section.energies[9] )
            self.assertAlmostEqual( 3.75 , chunk.cross_section.energies[10] )
            self.assertAlmostEqual( 4.   , chunk.cross_section.energies[11] )
            self.assertAlmostEqual( 4.              , chunk.cross_section.values[0] )
            self.assertAlmostEqual( 3.              , chunk.cross_section.values[1] )
            self.assertAlmostEqual( 4.              , chunk.cross_section.values[2] )
            self.assertAlmostEqual( 3.85048128530886, chunk.cross_section.values[3] )
            self.assertAlmostEqual( 3.70951129135145, chunk.cross_section.values[4] )
            self.assertAlmostEqual( 3.44966028678679, chunk.cross_section.values[5] )
            self.assertAlmostEqual( 3.21459646033567, chunk.cross_section.values[6] )
            self.assertAlmostEqual( 3.              , chunk.cross_section.values[7] )
            self.assertAlmostEqual( 2.72176678584324, chunk.cross_section.values[8] )
            self.assertAlmostEqual( 2.46416306545103, chunk.cross_section.values[9] )
            self.assertAlmostEqual( 2.22433973930853, chunk.cross_section.values[10] )
            self.assertAlmostEqual( 2.              , chunk.cross_section.values[11] )
            self.assertEqual( 1, chunk.cross_section.boundaries[0] )
            self.assertEqual( 11, chunk.cross_section.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.cross_section.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.cross_section.interpolants[1] )
            self.assertEqual( True, chunk.cross_section.is_linearised )

            # metadata
            self.assertEqual( True, chunk.is_linearised )

        # the data is given explicitly
        chunk = Reaction( id = 'n,Fe56->n,Fe56_e1', mass_q = 0, reaction_q = -1,
                          xs = TabulatedCrossSection ( [ 1., 2., 2., 3., 4. ],
                                                       [ 4., 3., 4., 3., 2. ],
                                                       [ 1, 4 ],
                                                       [ InterpolationType.LinearLinear,
                                                         InterpolationType.LinearLog ] ) )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
