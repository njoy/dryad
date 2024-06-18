# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import ReactionProduct
from dryad import TabulatedMultiplicity
from dryad import InterpolationType
from dryad import ReactionType

class Test_dryad_ReactionProduct( unittest.TestCase ) :
    """Unit test for the ReactionProduct class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # reaction product identifier
            self.assertEqual( 'n', chunk.identifier )

            # multiplicity
            self.assertEqual( True, isinstance( chunk.multiplicity, int ) )
            self.assertEqual( 1, chunk.multiplicity )

            # metadata
            self.assertEqual( True, chunk.is_linearised )

        def verify_tabulated_chunk( self, chunk ) :

            # reaction product identifier
            self.assertEqual( 'n', chunk.identifier )

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

            # metadata
            self.assertEqual( False, chunk.is_linearised )

        def verify_tabulated_linearised_chunk( self, chunk ) :

            # reaction product identifier
            self.assertEqual( 'n', chunk.identifier )

            # multiplicity
            self.assertEqual( True, isinstance( chunk.multiplicity, TabulatedMultiplicity ) )
            self.assertEqual( 12, chunk.multiplicity.number_points )
            self.assertEqual( 2, chunk.multiplicity.number_regions )
            self.assertEqual( 12, len( chunk.multiplicity.energies ) )
            self.assertEqual( 12, len( chunk.multiplicity.values ) )
            self.assertEqual( 2, len( chunk.multiplicity.boundaries ) )
            self.assertEqual( 2, len( chunk.multiplicity.interpolants ) )
            self.assertAlmostEqual( 1.   , chunk.multiplicity.energies[0] )
            self.assertAlmostEqual( 2.   , chunk.multiplicity.energies[1] )
            self.assertAlmostEqual( 2.   , chunk.multiplicity.energies[2] )
            self.assertAlmostEqual( 2.125, chunk.multiplicity.energies[3] )
            self.assertAlmostEqual( 2.25 , chunk.multiplicity.energies[4] )
            self.assertAlmostEqual( 2.5  , chunk.multiplicity.energies[5] )
            self.assertAlmostEqual( 2.75 , chunk.multiplicity.energies[6] )
            self.assertAlmostEqual( 3.   , chunk.multiplicity.energies[7] )
            self.assertAlmostEqual( 3.25 , chunk.multiplicity.energies[8] )
            self.assertAlmostEqual( 3.5  , chunk.multiplicity.energies[9] )
            self.assertAlmostEqual( 3.75 , chunk.multiplicity.energies[10] )
            self.assertAlmostEqual( 4.   , chunk.multiplicity.energies[11] )
            self.assertAlmostEqual( 4.              , chunk.multiplicity.values[0] )
            self.assertAlmostEqual( 3.              , chunk.multiplicity.values[1] )
            self.assertAlmostEqual( 4.              , chunk.multiplicity.values[2] )
            self.assertAlmostEqual( 3.85048128530886, chunk.multiplicity.values[3] )
            self.assertAlmostEqual( 3.70951129135145, chunk.multiplicity.values[4] )
            self.assertAlmostEqual( 3.44966028678679, chunk.multiplicity.values[5] )
            self.assertAlmostEqual( 3.21459646033567, chunk.multiplicity.values[6] )
            self.assertAlmostEqual( 3.              , chunk.multiplicity.values[7] )
            self.assertAlmostEqual( 2.72176678584324, chunk.multiplicity.values[8] )
            self.assertAlmostEqual( 2.46416306545103, chunk.multiplicity.values[9] )
            self.assertAlmostEqual( 2.22433973930853, chunk.multiplicity.values[10] )
            self.assertAlmostEqual( 2.              , chunk.multiplicity.values[11] )
            self.assertEqual( 1, chunk.multiplicity.boundaries[0] )
            self.assertEqual( 11, chunk.multiplicity.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.multiplicity.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.multiplicity.interpolants[1] )
            self.assertEqual( True, chunk.multiplicity.is_linearised )

            # metadata
            self.assertEqual( True, chunk.is_linearised )

        # the data is given explicitly using an integer multiplicity
        chunk = ReactionProduct( id = 'n', multiplicity = 1 )

        verify_chunk( self, chunk )

        # it can be linearised
        linear = chunk.linearise()

        verify_chunk( self, linear )

        # it can be linearised
        copy = chunk
        verify_chunk( self, copy )
        copy.linearise_inplace()

        verify_chunk( self, copy )

        # the data is given explicitly using a tabulated multiplicity
        chunk = ReactionProduct( id = 'n',
                                 multiplicity = TabulatedMultiplicity ( [ 1., 2., 2., 3., 4. ],
                                                                        [ 4., 3., 4., 3., 2. ],
                                                                        [ 1, 4 ],
                                                                        [ InterpolationType.LinearLinear,
                                                                          InterpolationType.LinearLog ] ) )

        verify_tabulated_chunk( self, chunk )

        # it can be linearised
        linear = chunk.linearise()

        verify_tabulated_linearised_chunk( self, linear )

        # it can be linearised
        copy = chunk
        verify_tabulated_chunk( self, copy )
        copy.linearise_inplace()

        verify_tabulated_linearised_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()