# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TabulatedCrossSection
from dryad import InterpolationType

class Test_dryad_TabulatedCrossSection( unittest.TestCase ) :
    """Unit test for the TabulatedCrossSection class."""

    def test_component( self ) :

        def verify_chunk1( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 2., chunk.energies[1] )
            self.assertAlmostEqual( 3., chunk.energies[2] )
            self.assertAlmostEqual( 4., chunk.energies[3] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( energy = 1. ) )
            self.assertAlmostEqual( 3., chunk( energy = 2. ) )
            self.assertAlmostEqual( 2., chunk( energy = 3. ) )
            self.assertAlmostEqual( 1., chunk( energy = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( energy = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( energy = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( energy = 1.5 ) )
            self.assertAlmostEqual( 2.5, chunk( energy = 2.5 ) )
            self.assertAlmostEqual( 1.5, chunk( energy = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 4, len( linear.energies ) )
            self.assertEqual( 4, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 3, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( 1., linear.energies[0] )
            self.assertAlmostEqual( 2., linear.energies[1] )
            self.assertAlmostEqual( 3., linear.energies[2] )
            self.assertAlmostEqual( 4., linear.energies[3] )

            self.assertAlmostEqual( 4., linear.values[0] )
            self.assertAlmostEqual( 3., linear.values[1] )
            self.assertAlmostEqual( 2., linear.values[2] )
            self.assertAlmostEqual( 1., linear.values[3] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk2( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_limit )
            self.assertEqual( 5, len( chunk.energies ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 2., chunk.energies[1] )
            self.assertAlmostEqual( 2., chunk.energies[2] )
            self.assertAlmostEqual( 3., chunk.energies[3] )
            self.assertAlmostEqual( 4., chunk.energies[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( energy = 1. ) )
            self.assertAlmostEqual( 4., chunk( energy = 2. ) )
            self.assertAlmostEqual( 3., chunk( energy = 3. ) )
            self.assertAlmostEqual( 2., chunk( energy = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( energy = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( energy = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 3.5, chunk( energy = 1.5 ) )
            self.assertAlmostEqual( 3.5, chunk( energy = 2.5 ) )
            self.assertAlmostEqual( 2.5, chunk( energy = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 5, linear.number_points )
            self.assertEqual( 2, linear.number_regions )

            self.assertEqual( 5, len( linear.energies ) )
            self.assertEqual( 5, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual( 1, linear.boundaries[0] )
            self.assertEqual( 4, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( 1., linear.energies[0] )
            self.assertAlmostEqual( 2., linear.energies[1] )
            self.assertAlmostEqual( 2., linear.energies[2] )
            self.assertAlmostEqual( 3., linear.energies[3] )
            self.assertAlmostEqual( 4., linear.energies[4] )

            self.assertAlmostEqual( 4., linear.values[0] )
            self.assertAlmostEqual( 3., linear.values[1] )
            self.assertAlmostEqual( 4., linear.values[2] )
            self.assertAlmostEqual( 3., linear.values[3] )
            self.assertAlmostEqual( 2., linear.values[4] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk3( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 2., chunk.energies[1] )
            self.assertAlmostEqual( 3., chunk.energies[2] )
            self.assertAlmostEqual( 4., chunk.energies[3] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( energy = 1. ) )
            self.assertAlmostEqual( 3., chunk( energy = 2. ) )
            self.assertAlmostEqual( 2., chunk( energy = 3. ) )
            self.assertAlmostEqual( 1., chunk( energy = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( energy = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( energy = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( energy = 1.5 ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 2.44966028678679, chunk( energy = 2.5 ) )
            self.assertAlmostEqual( 1.46416306545103, chunk( energy = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 18, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 18, len( linear.energies ) )
            self.assertEqual( 18, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 17, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( 1.   , linear.energies[0] )
            self.assertAlmostEqual( 2.   , linear.energies[1] )
            self.assertAlmostEqual( 2.125, linear.energies[2] )
            self.assertAlmostEqual( 2.25 , linear.energies[3] )
            self.assertAlmostEqual( 2.375, linear.energies[4] )
            self.assertAlmostEqual( 2.5  , linear.energies[5] )
            self.assertAlmostEqual( 2.625, linear.energies[6] )
            self.assertAlmostEqual( 2.75 , linear.energies[7] )
            self.assertAlmostEqual( 2.875, linear.energies[8] )
            self.assertAlmostEqual( 3.   , linear.energies[9] )
            self.assertAlmostEqual( 3.125, linear.energies[10] )
            self.assertAlmostEqual( 3.25 , linear.energies[11] )
            self.assertAlmostEqual( 3.375, linear.energies[12] )
            self.assertAlmostEqual( 3.5  , linear.energies[13] )
            self.assertAlmostEqual( 3.625, linear.energies[14] )
            self.assertAlmostEqual( 3.75 , linear.energies[15] )
            self.assertAlmostEqual( 3.875, linear.energies[16] )
            self.assertAlmostEqual( 4.   , linear.energies[17] )

            self.assertAlmostEqual( 4.              , linear.values[0] )
            self.assertAlmostEqual( 3.              , linear.values[1] )
            self.assertAlmostEqual( 2.85048128530886, linear.values[2] )
            self.assertAlmostEqual( 2.70951129135145, linear.values[3] )
            self.assertAlmostEqual( 2.57616511633150, linear.values[4] )
            self.assertAlmostEqual( 2.44966028678679, linear.values[5] )
            self.assertAlmostEqual( 2.32932893596581, linear.values[6] )
            self.assertAlmostEqual( 2.21459646033567, linear.values[7] )
            self.assertAlmostEqual( 2.10496492439848, linear.values[8] )
            self.assertAlmostEqual( 2.              , linear.values[9] )
            self.assertAlmostEqual( 1.85810031827028, linear.values[10] )
            self.assertAlmostEqual( 1.72176678584324, linear.values[11] )
            self.assertAlmostEqual( 1.59057916034679, linear.values[12] )
            self.assertAlmostEqual( 1.46416306545103, linear.values[13] )
            self.assertAlmostEqual( 1.34218354996644, linear.values[14] )
            self.assertAlmostEqual( 1.22433973930853, linear.values[15] )
            self.assertAlmostEqual( 1.11036036428687, linear.values[16] )
            self.assertAlmostEqual( 1.              , linear.values[17] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk4( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_limit )
            self.assertEqual( 5, len( chunk.energies ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 2., chunk.energies[1] )
            self.assertAlmostEqual( 2., chunk.energies[2] )
            self.assertAlmostEqual( 3., chunk.energies[3] )
            self.assertAlmostEqual( 4., chunk.energies[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( energy = 1. ) )
            self.assertAlmostEqual( 4., chunk( energy = 2. ) )
            self.assertAlmostEqual( 3., chunk( energy = 3. ) )
            self.assertAlmostEqual( 2., chunk( energy = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( energy = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( energy = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( energy = 1.5 ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.44966028678679, chunk( energy = 2.5 ) )
            self.assertAlmostEqual( 2.46416306545103, chunk( energy = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 12, linear.number_points )
            self.assertEqual( 2, linear.number_regions )

            self.assertEqual( 12, len( linear.energies ) )
            self.assertEqual( 12, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual(  1, linear.boundaries[0] )
            self.assertEqual( 11, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( 1.   , linear.energies[0] )
            self.assertAlmostEqual( 2.   , linear.energies[1] )
            self.assertAlmostEqual( 2.   , linear.energies[2] )
            self.assertAlmostEqual( 2.125, linear.energies[3] )
            self.assertAlmostEqual( 2.25 , linear.energies[4] )
            self.assertAlmostEqual( 2.5  , linear.energies[5] )
            self.assertAlmostEqual( 2.75 , linear.energies[6] )
            self.assertAlmostEqual( 3.   , linear.energies[7] )
            self.assertAlmostEqual( 3.25 , linear.energies[8] )
            self.assertAlmostEqual( 3.5  , linear.energies[9] )
            self.assertAlmostEqual( 3.75 , linear.energies[10] )
            self.assertAlmostEqual( 4.   , linear.energies[11] )

            self.assertAlmostEqual( 4.              , linear.values[0] )
            self.assertAlmostEqual( 3.              , linear.values[1] )
            self.assertAlmostEqual( 4.              , linear.values[2] )
            self.assertAlmostEqual( 3.85048128530886, linear.values[3] )
            self.assertAlmostEqual( 3.70951129135145, linear.values[4] )
            self.assertAlmostEqual( 3.44966028678679, linear.values[5] )
            self.assertAlmostEqual( 3.21459646033567, linear.values[6] )
            self.assertAlmostEqual( 3.              , linear.values[7] )
            self.assertAlmostEqual( 2.72176678584324, linear.values[8] )
            self.assertAlmostEqual( 2.46416306545103, linear.values[9] )
            self.assertAlmostEqual( 2.22433973930853, linear.values[10] )
            self.assertAlmostEqual( 2.              , linear.values[11] )

            self.assertEqual( True, linear.is_linearised )

        # the data is given explicitly for data without boundaries
        chunk = TabulatedCrossSection( energies = [ 1., 2., 3., 4. ],
                                       values = [ 4., 3., 2., 1. ],
                                       interpolant = InterpolationType.LinearLinear )

        verify_chunk1( self, chunk )

        # the data is given explicitly for data without boundaries and a jump
        chunk = TabulatedCrossSection( energies = [ 1., 2., 2., 3., 4. ],
                                       values = [ 4., 3., 4., 3., 2. ],
                                       interpolant = InterpolationType.LinearLinear )

        verify_chunk2( self, chunk )

        # the data is given explicitly for data without a jump
        chunk = TabulatedCrossSection( energies = [ 1., 2., 3., 4. ],
                                       values = [ 4., 3., 2., 1. ],
                                       boundaries = [ 1, 3 ],
                                       interpolants = [ InterpolationType.LinearLinear,
                                                        InterpolationType.LinearLog ] )

        verify_chunk3( self, chunk )

        # the data is given explicitly for data with a jump
        chunk = TabulatedCrossSection( energies = [ 1., 2., 2., 3., 4. ],
                                       values = [ 4., 3., 4., 3., 2. ],
                                       boundaries = [ 1, 4 ],
                                       interpolants = [ InterpolationType.LinearLinear,
                                                        InterpolationType.LinearLog ] )

        verify_chunk4( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [], values = [] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [ 1. ], values = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [ 1., 2., 3., 4. ],
                                           values = [ 4., 3., 2. ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [ 1., 2., 3., 4. ],
                                           values = [ 4., 3., 2., 1. ],
                                           boundaries = [ 3 ],
                                           interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [ 1., 3., 2., 4. ],
                                           values = [ 4., 3., 2., 1. ] )

        # the x grid contains a triple x value
        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [ 1., 2., 2., 2., 3., 4. ],
                                           values = [ 4., 3., 3., 3., 2., 1. ] )

        # the x grid has a jump at the beginning
        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [ 1., 1., 3., 4. ],
                                           values = [ 4., 3., 1., 4. ] )

        # the x grid has a jump at the end
        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [ 1., 2., 4., 4. ],
                                           values = [ 4., 3., 1., 4. ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = TabulatedCrossSection( energies = [ 1., 2., 3., 4. ],
                                           values = [ 4., 3., 2., 1. ],
                                           boundaries = [ 2 ],
                                           interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()