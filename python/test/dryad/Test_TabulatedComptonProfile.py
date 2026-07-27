# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import TabulatedComptonProfile
from njoy.dryad import InterpolationType
from njoy.dryad.id import ElectronSubshellID

class Test_TabulatedComptonProfile( unittest.TestCase ) :
    """Unit test for the TabulatedComptonProfile class."""

    def test_component( self ) :

        def verify_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            # verify content
            self.assertEqual( ElectronSubshellID( '1s1/2' ), chunk.subshell_identifier )

            self.assertEqual( 4, len( chunk.momentum ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 0.  , chunk.momentum[0] )
            self.assertAlmostEqual( 1.  , chunk.momentum[1] )
            self.assertAlmostEqual( 1.5 , chunk.momentum[2] )
            self.assertAlmostEqual( 2.  , chunk.momentum[3] )
            self.assertAlmostEqual( 0.  / normalisation, chunk.values[0] )
            self.assertAlmostEqual( 1.  / normalisation, chunk.values[1] )
            self.assertAlmostEqual( 1.5 / normalisation, chunk.values[2] )
            self.assertAlmostEqual( 2.  / normalisation, chunk.values[3] )
            self.assertAlmostEqual( 3, chunk.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            pdf = chunk.pdf
            self.assertAlmostEqual(  0., pdf.lower_momentum_limit )
            self.assertAlmostEqual(  2., pdf.upper_momentum_limit )
            self.assertEqual( 4, len( pdf.momentum ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( 0.  , pdf.momentum[0] )
            self.assertAlmostEqual( 1.  , pdf.momentum[1] )
            self.assertAlmostEqual( 1.5 , pdf.momentum[2] )
            self.assertAlmostEqual( 2.  , pdf.momentum[3] )
            self.assertAlmostEqual( 0.  / normalisation, pdf.values[0] )
            self.assertAlmostEqual( 1.  / normalisation, pdf.values[1] )
            self.assertAlmostEqual( 1.5 / normalisation, pdf.values[2] )
            self.assertAlmostEqual( 2.  / normalisation, pdf.values[3] )
            self.assertAlmostEqual( 3, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = chunk.cdf
            self.assertAlmostEqual( 0., cdf.lower_momentum_limit )
            self.assertAlmostEqual( 2., cdf.upper_momentum_limit )
            self.assertEqual( 4, len( cdf.momentum ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( 0.  , cdf.momentum[0] )
            self.assertAlmostEqual( 1.  , cdf.momentum[1] )
            self.assertAlmostEqual( 1.5 , cdf.momentum[2] )
            self.assertAlmostEqual( 2.  , cdf.momentum[3] )
            self.assertAlmostEqual( 0.    / normalisation, cdf.values[0] )
            self.assertAlmostEqual( 0.5   / normalisation, cdf.values[1] )
            self.assertAlmostEqual( 1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual( 2.    / normalisation, cdf.values[3] )
            self.assertAlmostEqual( 3, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

            self.assertAlmostEqual( 2.0 / normalisation, pdf.integral )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.  / normalisation, chunk( momentum = 0. ) )
            self.assertAlmostEqual( 1.  / normalisation, chunk( momentum = 1. ) )
            self.assertAlmostEqual( 1.5 / normalisation, chunk( momentum = 1.5 ) )
            self.assertAlmostEqual( 2.  / normalisation, chunk( momentum = 2. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( momentum = -5. ) )
            self.assertAlmostEqual( 0.0, chunk( momentum =  5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 0.5  / normalisation, chunk( momentum = 0.5 ) )
            self.assertAlmostEqual( 1.75 / normalisation, chunk( momentum = 1.75 ) )

            # verify average momentum - always the mean value even for unnormalised distributions
            self.assertAlmostEqual( 8. / 3. / 2., chunk.average_momentum )

            # verify linearisation
            linear = chunk.linearise()

            pdf = linear.pdf
            self.assertAlmostEqual( 0., pdf.lower_momentum_limit )
            self.assertAlmostEqual( 2., pdf.upper_momentum_limit )
            self.assertEqual( 4, len( pdf.momentum ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( 0.  , pdf.momentum[0] )
            self.assertAlmostEqual( 1.  , pdf.momentum[1] )
            self.assertAlmostEqual( 1.5 , pdf.momentum[2] )
            self.assertAlmostEqual( 2.  , pdf.momentum[3] )
            self.assertAlmostEqual( 0.  / normalisation, pdf.values[0] )
            self.assertAlmostEqual( 1.  / normalisation, pdf.values[1] )
            self.assertAlmostEqual( 1.5 / normalisation, pdf.values[2] )
            self.assertAlmostEqual( 2.  / normalisation, pdf.values[3] )
            self.assertAlmostEqual( 3, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = linear.cdf
            self.assertAlmostEqual( 0., cdf.lower_momentum_limit )
            self.assertAlmostEqual( 2., cdf.upper_momentum_limit )
            self.assertEqual( 4, len( cdf.momentum ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( 0.  , cdf.momentum[0] )
            self.assertAlmostEqual( 1.  , cdf.momentum[1] )
            self.assertAlmostEqual( 1.5 , cdf.momentum[2] )
            self.assertAlmostEqual( 2.  , cdf.momentum[3] )
            self.assertAlmostEqual( 0.    / normalisation, cdf.values[0] )
            self.assertAlmostEqual( 0.5   / normalisation, cdf.values[1] )
            self.assertAlmostEqual( 1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual( 2.    / normalisation, cdf.values[3] )
            self.assertAlmostEqual( 3, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

        # the data is given explicitly using a normalised table
        chunk1 = TabulatedComptonProfile( subshell_identifier = ElectronSubshellID( '1s' ),
                                          momentum = [ 0., 1., 1.5, 2. ], values = [ 0., 1., 1.5, 2. ],
                                          normalise = False )
        chunk2 = TabulatedComptonProfile( subshell_identifier = ElectronSubshellID( '1s' ),
                                          momentum = [ 0., 1., 1.5, 2. ], values = [ 0., 1., 1.5, 2. ],
                                          normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

    def test_comparison( self ) :

        left = TabulatedComptonProfile( ElectronSubshellID( '1s' ),[ 0., 2. ], [ 0.5, 0.5 ] )
        equal = TabulatedComptonProfile( ElectronSubshellID( '1s' ),[ 0., 2. ], [ 0.5, 0.5 ] )
        unnormalised = TabulatedComptonProfile( ElectronSubshellID( '1s' ),[ 0., 2. ], [ 1., 1. ], InterpolationType.LinearLinear, True )
        different = TabulatedComptonProfile( ElectronSubshellID( '2s' ),[ 0., 2. ], [ 0.25, 0.75 ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( True, ( left == unnormalised ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( False, ( left != unnormalised ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # the momentum and values vector are not of the same length
        with self.assertRaises( Exception ) :

            chunk = TabulatedComptonProfile( ElectronSubshellID( '1s' ), momentum = [ 0., 2. ], values = [ 0., 0.5, 0.75, 1. ] )

if __name__ == '__main__' :

    unittest.main()
