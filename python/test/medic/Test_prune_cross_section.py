# standard imports
import unittest

# third party imports

# local imports
from njoy.medic import prune_cross_section
from njoy.dryad import InterpolationType
from njoy.dryad import TabulatedCrossSection

def create_tabulated_cross_section() :

    return TabulatedCrossSection( [ 1., 2., 3., 3., 4., 5., 6. ],
                                  [ 11., 12., 13., 23., 24., 25., 26. ],
                                  [ 3, 6 ],
                                  [ InterpolationType.LinearLinear, InterpolationType.LogLog ] )

class Test_prune_cross_section( unittest.TestCase ) :
    """Unit test for the prune_cross_section function."""

    def test_component( self ) :

        # it can be pruned to a lower energy limit present in the energies (no jump)
        table = create_tabulated_cross_section()
        prune_cross_section( lower_energy = 2., upper_energy = 6., xs = table )

        self.assertEqual( 6, table.number_points )
        self.assertEqual( 2, table.number_regions )
        self.assertEqual( 6, len( table.energies ) )
        self.assertEqual( 6, len( table.values ) )
        self.assertEqual( 2, len( table.boundaries ) )
        self.assertEqual( 2, len( table.interpolants ) )

        self.assertAlmostEqual( 2., table.energies[0] )
        self.assertAlmostEqual( 3., table.energies[1] )
        self.assertAlmostEqual( 3., table.energies[2] )
        self.assertAlmostEqual( 4., table.energies[3] )
        self.assertAlmostEqual( 5., table.energies[4] )
        self.assertAlmostEqual( 6., table.energies[5] )
        self.assertAlmostEqual( 12., table.values[0] )
        self.assertAlmostEqual( 13., table.values[1] )
        self.assertAlmostEqual( 23., table.values[2] )
        self.assertAlmostEqual( 24., table.values[3] )
        self.assertAlmostEqual( 25., table.values[4] )
        self.assertAlmostEqual( 26., table.values[5] )

        self.assertEqual( 1, table.boundaries[0] )
        self.assertEqual( 5, table.boundaries[1] )
        self.assertEqual( InterpolationType.LinearLinear, table.interpolants[0] )
        self.assertEqual( InterpolationType.LogLog, table.interpolants[1] )

        # it can be pruned to a lower energy limit present in the energies (a jump)
        table = create_tabulated_cross_section()
        prune_cross_section( lower_energy = 3., upper_energy = 6., xs = table )

        self.assertEqual( 4, table.number_points )
        self.assertEqual( 1, table.number_regions )
        self.assertEqual( 4, len( table.energies ) )
        self.assertEqual( 4, len( table.values ) )
        self.assertEqual( 1, len( table.boundaries ) )
        self.assertEqual( 1, len( table.interpolants ) )

        self.assertAlmostEqual( 3., table.energies[0] )
        self.assertAlmostEqual( 4., table.energies[1] )
        self.assertAlmostEqual( 5., table.energies[2] )
        self.assertAlmostEqual( 6., table.energies[3] )
        self.assertAlmostEqual( 23., table.values[0] )
        self.assertAlmostEqual( 24., table.values[1] )
        self.assertAlmostEqual( 25., table.values[2] )
        self.assertAlmostEqual( 26., table.values[3] )

        self.assertEqual( 3, table.boundaries[0] )
        self.assertEqual( InterpolationType.LogLog, table.interpolants[0] )

        # it can be pruned to a lower energy limit not present in the energies
        table = create_tabulated_cross_section()
        prune_cross_section( lower_energy = 2.5, upper_energy = 6., xs = table )

        self.assertEqual( 6, table.number_points )
        self.assertEqual( 2, table.number_regions )
        self.assertEqual( 6, len( table.energies ) )
        self.assertEqual( 6, len( table.values ) )
        self.assertEqual( 2, len( table.boundaries ) )
        self.assertEqual( 2, len( table.interpolants ) )

        self.assertAlmostEqual( 2.5, table.energies[0] )
        self.assertAlmostEqual( 3. , table.energies[1] )
        self.assertAlmostEqual( 3. , table.energies[2] )
        self.assertAlmostEqual( 4. , table.energies[3] )
        self.assertAlmostEqual( 5. , table.energies[4] )
        self.assertAlmostEqual( 6. , table.energies[5] )
        self.assertAlmostEqual( 12.5, table.values[0] )
        self.assertAlmostEqual( 13. , table.values[1] )
        self.assertAlmostEqual( 23. , table.values[2] )
        self.assertAlmostEqual( 24. , table.values[3] )
        self.assertAlmostEqual( 25. , table.values[4] )
        self.assertAlmostEqual( 26. , table.values[5] )

        self.assertEqual( 1, table.boundaries[0] )
        self.assertEqual( 5, table.boundaries[1] )
        self.assertEqual( InterpolationType.LinearLinear, table.interpolants[0] )
        self.assertEqual( InterpolationType.LogLog, table.interpolants[1] )

        # it can be pruned to an upper energy limit present in the energies
        table = create_tabulated_cross_section()
        prune_cross_section( lower_energy = 1., upper_energy = 3., xs = table )

        self.assertEqual( 3, table.number_points )
        self.assertEqual( 1, table.number_regions )
        self.assertEqual( 3, len( table.energies ) )
        self.assertEqual( 3, len( table.values ) )
        self.assertEqual( 1, len( table.boundaries ) )
        self.assertEqual( 1, len( table.interpolants ) )

        self.assertAlmostEqual( 1., table.energies[0] )
        self.assertAlmostEqual( 2., table.energies[1] )
        self.assertAlmostEqual( 3., table.energies[2] )
        self.assertAlmostEqual( 11., table.values[0] )
        self.assertAlmostEqual( 12., table.values[1] )
        self.assertAlmostEqual( 13., table.values[2] )

        self.assertEqual( 2, table.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, table.interpolants[0] )

        # it can be pruned to an upper energy limit not present in the energies
        table = create_tabulated_cross_section()
        prune_cross_section( lower_energy = 1., upper_energy = 2.5, xs = table )

        self.assertEqual( 3, table.number_points )
        self.assertEqual( 1, table.number_regions )
        self.assertEqual( 3, len( table.energies ) )
        self.assertEqual( 3, len( table.values ) )
        self.assertEqual( 1, len( table.boundaries ) )
        self.assertEqual( 1, len( table.interpolants ) )

        self.assertAlmostEqual( 1. , table.energies[0] )
        self.assertAlmostEqual( 2. , table.energies[1] )
        self.assertAlmostEqual( 2.5, table.energies[2] )
        self.assertAlmostEqual( 11. , table.values[0] )
        self.assertAlmostEqual( 12. , table.values[1] )
        self.assertAlmostEqual( 12.5, table.values[2] )

        self.assertEqual( 2, table.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, table.interpolants[0] )

        # it can be pruned
        table = create_tabulated_cross_section()
        prune_cross_section( lower_energy = 1.5, upper_energy = 2.5, xs = table )

        self.assertEqual( 3, table.number_points )
        self.assertEqual( 1, table.number_regions )
        self.assertEqual( 3, len( table.energies ) )
        self.assertEqual( 3, len( table.values ) )
        self.assertEqual( 1, len( table.boundaries ) )
        self.assertEqual( 1, len( table.interpolants ) )

        self.assertAlmostEqual( 1.5, table.energies[0] )
        self.assertAlmostEqual( 2. , table.energies[1] )
        self.assertAlmostEqual( 2.5, table.energies[2] )
        self.assertAlmostEqual( 11.5, table.values[0] )
        self.assertAlmostEqual( 12. , table.values[1] )
        self.assertAlmostEqual( 12.5, table.values[2] )

        self.assertEqual( 2, table.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, table.interpolants[0] )

if __name__ == '__main__' :

    unittest.main()
