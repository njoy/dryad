# standard imports
import unittest
from copy import copy
import sys

# third party imports

# local imports
from njoy.dryad.thermal import TabulatedScatteringKernelFunction
from njoy.dryad.thermal import TabulatedScatteringKernel
from njoy.dryad import InterpolationType

class Test_TabulatedScatteringKernel( unittest.TestCase ) :
    """Unit test for the TabulatedScatteringKernel class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            self.assertAlmostEqual( 1., chunk.lower_energy_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., chunk.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_momentum_transfer_limit )

            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.energy_transfers ) )
            self.assertEqual( 4, len( chunk.functions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energy_transfers[0] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[1] )
            self.assertAlmostEqual( 3., chunk.energy_transfers[2] )
            self.assertAlmostEqual( 4., chunk.energy_transfers[3] )
            self.assertEqual( 2, len( chunk.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[0].values ) )
            self.assertEqual( 2, len( chunk.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[1].values ) )
            self.assertEqual( 2, len( chunk.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[2].values ) )
            self.assertEqual( 2, len( chunk.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[3].values ) )
            self.assertAlmostEqual( 0., chunk.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[3].momentum_transfers[1] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[0] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[1] )
            self.assertAlmostEqual( 0.52, chunk.functions[1].values[0] )
            self.assertAlmostEqual( 0.48, chunk.functions[1].values[1] )
            self.assertAlmostEqual( 0.48, chunk.functions[2].values[0] )
            self.assertAlmostEqual( 0.52, chunk.functions[2].values[1] )
            self.assertAlmostEqual( 0.2 , chunk.functions[3].values[0] )
            self.assertAlmostEqual( 0.8 , chunk.functions[3].values[1] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_curated )

            # evaluate

            # values of b in the b grid
            self.assertAlmostEqual( 0.5 , chunk( 3., 1. ) )
            self.assertAlmostEqual( 0.49, chunk( 3., 2. ) )
            self.assertAlmostEqual( 0.51, chunk( 3., 3. ) )
            self.assertAlmostEqual( 0.65, chunk( 3., 4. ) )

            # values of b outside the b grid
            self.assertAlmostEqual( 0., chunk( 3.0, 0. ) )
            self.assertAlmostEqual( 0., chunk( 3.5, 5. ) )

            # values of x inside the x grid
            self.assertAlmostEqual( 0.495, chunk( 3., 1.5 ) )
            self.assertAlmostEqual( 0.5 , chunk( 3., 2.5 ) )
            self.assertAlmostEqual( 0.58 , chunk( 3., 3.5 ) )

            # linearisation
            linear = chunk.linearise()

            self.assertAlmostEqual( 1., linear.lower_energy_transfer_limit )
            self.assertAlmostEqual( 4., linear.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., linear.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., linear.upper_momentum_transfer_limit )

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )
            self.assertEqual( 4, len( linear.energy_transfers ) )
            self.assertEqual( 4, len( linear.functions ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )
            self.assertAlmostEqual( 1., linear.energy_transfers[0] )
            self.assertAlmostEqual( 2., linear.energy_transfers[1] )
            self.assertAlmostEqual( 3., linear.energy_transfers[2] )
            self.assertAlmostEqual( 4., linear.energy_transfers[3] )
            self.assertEqual( True, linear.functions[0].is_linearised )
            self.assertEqual( True, linear.functions[1].is_linearised )
            self.assertEqual( True, linear.functions[2].is_linearised )
            self.assertEqual( True, linear.functions[3].is_linearised )
            self.assertEqual( 2, len( linear.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( linear.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( linear.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( linear.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( linear.functions[0].values ) )
            self.assertEqual( 2, len( linear.functions[1].values ) )
            self.assertEqual( 2, len( linear.functions[2].values ) )
            self.assertEqual( 2, len( linear.functions[3].values ) )
            self.assertAlmostEqual( 0., linear.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4., linear.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0., linear.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 4., linear.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 0., linear.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4., linear.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0., linear.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual( 4., linear.functions[3].momentum_transfers[1] )
            self.assertAlmostEqual( 0.5 , linear.functions[0].values[0] )
            self.assertAlmostEqual( 0.5 , linear.functions[0].values[1] )
            self.assertAlmostEqual( 0.52, linear.functions[1].values[0] )
            self.assertAlmostEqual( 0.48, linear.functions[1].values[1] )
            self.assertAlmostEqual( 0.48, linear.functions[2].values[0] )
            self.assertAlmostEqual( 0.52, linear.functions[2].values[1] )
            self.assertAlmostEqual( 0.2 , linear.functions[3].values[0] )
            self.assertAlmostEqual( 0.8 , linear.functions[3].values[1] )
            self.assertEqual( 3, linear.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

        def verify_chunk_with_jump_curated( self, chunk ) :

            self.assertAlmostEqual( 1., chunk.lower_energy_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., chunk.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_momentum_transfer_limit )

            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.energy_transfers ) )
            self.assertEqual( 5, len( chunk.functions ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energy_transfers[0] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[1] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[2] )
            self.assertAlmostEqual( 3., chunk.energy_transfers[3] )
            self.assertAlmostEqual( 4., chunk.energy_transfers[4] )
            self.assertEqual( 2, len( chunk.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[0].values ) )
            self.assertEqual( 2, len( chunk.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[1].values ) )
            self.assertEqual( 2, len( chunk.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[2].values ) )
            self.assertEqual( 2, len( chunk.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[3].values ) )
            self.assertEqual( 2, len( chunk.functions[4].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[4].values ) )
            self.assertAlmostEqual( 0., chunk.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[3].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[4].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[4].momentum_transfers[1] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[0] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[1] )
            self.assertAlmostEqual( 0.52, chunk.functions[1].values[0] )
            self.assertAlmostEqual( 0.48, chunk.functions[1].values[1] )
            self.assertAlmostEqual( 0.51, chunk.functions[2].values[0] )
            self.assertAlmostEqual( 0.49, chunk.functions[2].values[1] )
            self.assertAlmostEqual( 0.48, chunk.functions[3].values[0] )
            self.assertAlmostEqual( 0.52, chunk.functions[3].values[1] )
            self.assertAlmostEqual( 0.2 , chunk.functions[4].values[0] )
            self.assertAlmostEqual( 0.8 , chunk.functions[4].values[1] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk_with_jump_not_curated( self, chunk ) :

            self.assertAlmostEqual( 1., chunk.lower_energy_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., chunk.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_momentum_transfer_limit )

            self.assertEqual( 6, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 6, len( chunk.energy_transfers ) )
            self.assertEqual( 6, len( chunk.functions ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energy_transfers[0] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[1] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[2] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[3] )
            self.assertAlmostEqual( 3., chunk.energy_transfers[4] )
            self.assertAlmostEqual( 4., chunk.energy_transfers[5] )
            self.assertEqual( 2, len( chunk.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[0].values ) )
            self.assertEqual( 2, len( chunk.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[1].values ) )
            self.assertEqual( 2, len( chunk.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[2].values ) )
            self.assertEqual( 2, len( chunk.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[3].values ) )
            self.assertEqual( 2, len( chunk.functions[4].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[4].values ) )
            self.assertEqual( 2, len( chunk.functions[5].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[5].values ) )
            self.assertAlmostEqual( 0., chunk.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[3].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[4].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[4].momentum_transfers[1] )
            self.assertAlmostEqual( 0., chunk.functions[5].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[5].momentum_transfers[1] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[0] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[1] )
            self.assertAlmostEqual( 0.52, chunk.functions[1].values[0] )
            self.assertAlmostEqual( 0.48, chunk.functions[1].values[1] )
            self.assertAlmostEqual( 0.5 , chunk.functions[2].values[0] )
            self.assertAlmostEqual( 0.5 , chunk.functions[2].values[1] )
            self.assertAlmostEqual( 0.51, chunk.functions[3].values[0] )
            self.assertAlmostEqual( 0.49, chunk.functions[3].values[1] )
            self.assertAlmostEqual( 0.48, chunk.functions[4].values[0] )
            self.assertAlmostEqual( 0.52, chunk.functions[4].values[1] )
            self.assertAlmostEqual( 0.2 , chunk.functions[5].values[0] )
            self.assertAlmostEqual( 0.8 , chunk.functions[5].values[1] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_curated )

        def verify_chunk_with_distribution_jump_curated( self, chunk ) :

            self.assertAlmostEqual( 1., chunk.lower_energy_transfer_limit )
            self.assertAlmostEqual( 3., chunk.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., chunk.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_momentum_transfer_limit )

            self.assertEqual( 3, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 3, len( chunk.energy_transfers ) )
            self.assertEqual( 3, len( chunk.functions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energy_transfers[0] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[1] )
            self.assertAlmostEqual( 3., chunk.energy_transfers[2] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_curated )

            # function 0: no jump
            self.assertEqual( 2, len( chunk.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[0].values ) )
            self.assertEqual( 1, len( chunk.functions[0].boundaries ) )
            self.assertEqual( 1, len( chunk.functions[0].interpolants ) )
            self.assertAlmostEqual( 0., chunk.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0.5, chunk.functions[0].values[0] )
            self.assertAlmostEqual( 0.5, chunk.functions[0].values[1] )
            self.assertEqual( 1, chunk.functions[0].boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.functions[0].interpolants[0] )
            self.assertEqual( True, chunk.functions[0].is_linearised )
            self.assertEqual( True, chunk.functions[0].is_curated )

            # function 1: jump with the extraneous point removed
            self.assertEqual( 5, len( chunk.functions[1].momentum_transfers ) )
            self.assertEqual( 5, len( chunk.functions[1].values ) )
            self.assertEqual( 2, len( chunk.functions[1].boundaries ) )
            self.assertEqual( 2, len( chunk.functions[1].interpolants ) )
            self.assertAlmostEqual( 0., chunk.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 1., chunk.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 2., chunk.functions[1].momentum_transfers[2] )
            self.assertAlmostEqual( 2., chunk.functions[1].momentum_transfers[3] )
            self.assertAlmostEqual( 4., chunk.functions[1].momentum_transfers[4] )
            self.assertAlmostEqual( 0., chunk.functions[1].values[0] )
            self.assertAlmostEqual( 1., chunk.functions[1].values[1] )
            self.assertAlmostEqual( 2., chunk.functions[1].values[2] )
            self.assertAlmostEqual( 1., chunk.functions[1].values[3] )
            self.assertAlmostEqual( 2., chunk.functions[1].values[4] )
            self.assertEqual( 2, chunk.functions[1].boundaries[0] )
            self.assertEqual( 4, chunk.functions[1].boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.functions[1].interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.functions[1].interpolants[1] )
            self.assertEqual( True, chunk.functions[1].is_linearised )
            self.assertEqual( True, chunk.functions[1].is_curated )

            # function 2: no jump
            self.assertEqual( 2, len( chunk.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[2].values ) )
            self.assertEqual( 1, len( chunk.functions[2].boundaries ) )
            self.assertEqual( 1, len( chunk.functions[2].interpolants ) )
            self.assertAlmostEqual( 0., chunk.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0.2, chunk.functions[2].values[0] )
            self.assertAlmostEqual( 0.8, chunk.functions[2].values[1] )
            self.assertEqual( 1, chunk.functions[2].boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.functions[2].interpolants[0] )
            self.assertEqual( True, chunk.functions[2].is_linearised )
            self.assertEqual( True, chunk.functions[2].is_curated )

        def verify_chunk_with_distribution_jump_not_curated( self, chunk ) :

            self.assertAlmostEqual( 1., chunk.lower_energy_transfer_limit )
            self.assertAlmostEqual( 3., chunk.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., chunk.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_momentum_transfer_limit )

            self.assertEqual( 3, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 3, len( chunk.energy_transfers ) )
            self.assertEqual( 3, len( chunk.functions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energy_transfers[0] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[1] )
            self.assertAlmostEqual( 3., chunk.energy_transfers[2] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( False, chunk.is_curated )    # the grid is curated but function 1 is not

            # function 0: no jump
            self.assertEqual( 2, len( chunk.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[0].values ) )
            self.assertEqual( 1, len( chunk.functions[0].boundaries ) )
            self.assertEqual( 1, len( chunk.functions[0].interpolants ) )
            self.assertAlmostEqual( 0., chunk.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0.5, chunk.functions[0].values[0] )
            self.assertAlmostEqual( 0.5, chunk.functions[0].values[1] )
            self.assertEqual( 1, chunk.functions[0].boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.functions[0].interpolants[0] )
            self.assertEqual( True, chunk.functions[0].is_linearised )
            self.assertEqual( True, chunk.functions[0].is_curated )

            # function 1: jump with the extraneous point still present
            self.assertEqual( 6, len( chunk.functions[1].momentum_transfers ) )
            self.assertEqual( 6, len( chunk.functions[1].values ) )
            self.assertEqual( 2, len( chunk.functions[1].boundaries ) )
            self.assertEqual( 2, len( chunk.functions[1].interpolants ) )
            self.assertAlmostEqual( 0., chunk.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 1., chunk.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 2., chunk.functions[1].momentum_transfers[2] )
            self.assertAlmostEqual( 2., chunk.functions[1].momentum_transfers[3] )
            self.assertAlmostEqual( 2., chunk.functions[1].momentum_transfers[4] )
            self.assertAlmostEqual( 4., chunk.functions[1].momentum_transfers[5] )
            self.assertAlmostEqual( 0., chunk.functions[1].values[0] )
            self.assertAlmostEqual( 1., chunk.functions[1].values[1] )
            self.assertAlmostEqual( 2., chunk.functions[1].values[2] )
            self.assertAlmostEqual( 3., chunk.functions[1].values[3] )
            self.assertAlmostEqual( 1., chunk.functions[1].values[4] )
            self.assertAlmostEqual( 2., chunk.functions[1].values[5] )
            self.assertEqual( 2, chunk.functions[1].boundaries[0] )
            self.assertEqual( 5, chunk.functions[1].boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.functions[1].interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.functions[1].interpolants[1] )
            self.assertEqual( True, chunk.functions[1].is_linearised )
            self.assertEqual( False, chunk.functions[1].is_curated )

            # function 2: no jump
            self.assertEqual( 2, len( chunk.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[2].values ) )
            self.assertEqual( 1, len( chunk.functions[2].boundaries ) )
            self.assertEqual( 1, len( chunk.functions[2].interpolants ) )
            self.assertAlmostEqual( 0., chunk.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4., chunk.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0.2, chunk.functions[2].values[0] )
            self.assertAlmostEqual( 0.8, chunk.functions[2].values[1] )
            self.assertEqual( 1, chunk.functions[2].boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.functions[2].interpolants[0] )
            self.assertEqual( True, chunk.functions[2].is_linearised )
            self.assertEqual( True, chunk.functions[2].is_curated )

        # linearised data without boundaries and no jumps

        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                           interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk )

        # linearised data with a jump that consist of more than 2 points (curate is not requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump are kept. boundaries always point to the first point
        # in the jump, regardless of curation.

        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 2., 2., 3., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.51, 0.49 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] )

        original = copy( chunk )

        # a TabulatedScatteringKernel can be constructed and members can be tested
        verify_chunk_with_jump_not_curated( self, chunk )

        # the table can be curated on demand and the extraneous points are removed
        chunk.curate()

        verify_chunk_with_jump_curated( self, chunk )

        # the table can be linearised and the extraneous point in the jump is removed
        chunk = copy( original )
        linear = chunk.linearise()

        verify_chunk_with_jump_curated( self, linear )

        # linearised data with a jump that consist of more than 2 points (curate is requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump are kept. boundaries always point to the first point
        # in the jump, regardless of curation.

        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 2., 2., 3., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.51, 0.49 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                           interpolant = InterpolationType.LinearLinear,
                                           curate = True )

        # a TabulatedScatteringKernel can be constructed and members can be tested
        verify_chunk_with_jump_curated( self, chunk )

        # calling curate() again on an already curated table does not change anything
        chunk.curate()

        verify_chunk_with_jump_curated( self, chunk )

        # linearised data with a jump that consist of more than 2 points in one of the functions (curate is not requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump of a function are kept. curation of the
        # functions removes them.

        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 1., 2., 2., 2., 4. ], [ 0., 1., 2., 3., 1., 2. ] ),    # <-- jump of 3 x values
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] )

        original = copy( chunk )

        # a TabulatedScatteringKernel can be constructed and members can be tested
        verify_chunk_with_distribution_jump_not_curated( self, chunk )

        # the table can be curated on demand and the extraneous points are removed
        chunk.curate()

        verify_chunk_with_distribution_jump_curated( self, chunk )

        # the table can be linearised and the extraneous point in the jump is removed
        chunk = copy( original )
        linear = chunk.linearise()

        verify_chunk_with_distribution_jump_curated( self, linear )

        # linearised data with a jump that consist of more than 2 points in one of the functions (curate is requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump of a function are kept. curation of the
        # functions removes them.

        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 1., 2., 2., 2., 4. ], [ 0., 1., 2., 3., 1., 2. ] ),    # <-- jump of 3 x values
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                           interpolant = InterpolationType.LinearLinear,
                                           curate = True )

        # a TabulatedScatteringKernel can be constructed and members can be tested
        verify_chunk_with_distribution_jump_curated( self, chunk )

        # calling curate() again on an already curated table does not change anything
        chunk.curate()

        verify_chunk_with_distribution_jump_curated( self, chunk )

        # data with a jump at the beginning
        # note: at construction time, the first point is removed

        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 1., 2., 3., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 1. ], [ 0.1, 0.1 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] )

        # a TabulatedScatteringKernel can be constructed and members can be tested
        verify_chunk( self, chunk )

        # data with a jump at the end
        # note: at construction time, the last point is removed

        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 1. ], [ 0.1, 0.1 ] ) ] )

        # a TabulatedScatteringKernel can be constructed and members can be tested
        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = TabulatedScatteringKernel( [ 1., 2., 3., 4. ],
                                          [ TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.5, 0.5 ] ),
                                            TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.49, 0.51 ] ),
                                            TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.4, 0.6 ] ),
                                            TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )
        equal = TabulatedScatteringKernel( [ 1., 2., 3., 4. ],
                                           [ TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.5, 0.5 ] ),
                                             TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.49, 0.51 ] ),
                                             TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.4, 0.6 ] ),
                                             TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )
        different = TabulatedScatteringKernel( [ 1., 4. ],
                                               [ TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.5, 0.5 ] ),
                                                 TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or f(y) energyTransfers
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [],
                                               functions = [] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1. ],
                                               functions = [] )

        # the x and f(y) energyTransfers do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.1, 0.9 ] ) ],
                                               boundaries = [ 3 ],
                                               interpolants = [] )

        # the energyTransfers is not sorted
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 3., 2., 4. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.1, 0.9 ] ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.1, 0.9 ] ) ],
                                               boundaries = [ 2 ],
                                               interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
