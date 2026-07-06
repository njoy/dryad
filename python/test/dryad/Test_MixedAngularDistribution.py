# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import MixedAngularDistribution
from njoy.dryad import IsotropicAngularDistributionFunction
from njoy.dryad import LegendreAngularDistributionFunction
from njoy.dryad import TabulatedAngularDistributionFunction
from njoy.dryad import InterpolationType

class Test_MixedAngularDistribution( unittest.TestCase ) :
    """Unit test for the MixedAngularDistribution class."""

    def test_component( self ) :

        def verify_isotropic_chunk( self, chunk ) :

            pdf = chunk.pdf

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 2, len( cdf.cosines ) )
            self.assertEqual( 2, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1. , cdf.cosines[0] )
            self.assertAlmostEqual(  1. , cdf.cosines[1] )
            self.assertAlmostEqual(  0., cdf.values[0] )
            self.assertAlmostEqual(  1., cdf.values[1] )
            self.assertAlmostEqual( 1, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

            self.assertAlmostEqual( 1., pdf.integral )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.5, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 0.5, chunk( cosine =  0. ) )
            self.assertAlmostEqual( 0.5, chunk( cosine =  0.5 ) )
            self.assertAlmostEqual( 0.5, chunk( cosine =  1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( cosine = -5. ) )
            self.assertAlmostEqual( 0.0, chunk( cosine =  5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 0.5, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 0.5, chunk( cosine = 0.75 ) )

            # verify average cosine - always the mean value even for unnormalised distributions
            self.assertAlmostEqual( 0., chunk.average_cosine )

            # verify linearisation
            linear = chunk.linearise()

            pdf = linear.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 2, len( pdf.cosines ) )
            self.assertEqual( 2, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1. , pdf.cosines[0] )
            self.assertAlmostEqual(  1. , pdf.cosines[1] )
            self.assertAlmostEqual(  0.5, pdf.values[0] )
            self.assertAlmostEqual(  0.5, pdf.values[1] )
            self.assertAlmostEqual( 1, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = linear.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 2, len( cdf.cosines ) )
            self.assertEqual( 2, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1. , cdf.cosines[0] )
            self.assertAlmostEqual(  1. , cdf.cosines[1] )
            self.assertAlmostEqual(  0., cdf.values[0] )
            self.assertAlmostEqual(  1., cdf.values[1] )
            self.assertAlmostEqual( 1, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

        def verify_legendre_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 1, pdf.order )
            self.assertEqual( 2, len( pdf.coefficients ) )
            self.assertAlmostEqual( 1.0 / normalisation, pdf.coefficients[0] )
            self.assertAlmostEqual( 0.5 / normalisation, pdf.coefficients[1] )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 2, cdf.order )
            self.assertEqual( 3, len( cdf.coefficients ) )
            self.assertAlmostEqual( 0.8333333333333333 / normalisation, cdf.coefficients[0] )
            self.assertAlmostEqual( 1. / normalisation                , cdf.coefficients[1] )
            self.assertAlmostEqual( 0.1666666666666666 / normalisation, cdf.coefficients[2] )
            self.assertAlmostEqual( 0., cdf( -1. ) )
            self.assertAlmostEqual( 2. / normalisation, cdf(  1. ) )

            # verify evaluation
            self.assertAlmostEqual( 0.5 / normalisation, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1.0 / normalisation, chunk( cosine =  0. ) )
            self.assertAlmostEqual( 1.5 / normalisation, chunk( cosine =  1. ) )

            # verify average cosine - always the mean value even for unnormalised distributions
            self.assertAlmostEqual( 1. / 3. / 2., chunk.average_cosine )

            # verify linearisation
            linear = chunk.linearise()
            self.assertAlmostEqual( -1., linear.pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., linear.pdf.upper_cosine_limit )
            self.assertEqual( 2, linear.pdf.number_points )
            self.assertEqual( 1, linear.pdf.number_regions )
            self.assertEqual( 2, len( linear.pdf.cosines) )
            self.assertEqual( 2, len( linear.pdf.values) )
            self.assertEqual( 1, len( linear.pdf.boundaries) )
            self.assertEqual( 1, len( linear.pdf.interpolants) )
            self.assertEqual( 1, linear.pdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.pdf.interpolants[0] )
            self.assertAlmostEqual( -1.0, linear.pdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.pdf.cosines[1] )
            self.assertAlmostEqual( 0.5 / normalisation, linear.pdf.values[0] )
            self.assertAlmostEqual( 1.5 / normalisation, linear.pdf.values[1] )
            self.assertEqual( True, linear.pdf.is_linearised )

            self.assertAlmostEqual( -1., linear.cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., linear.cdf.upper_cosine_limit )
            self.assertEqual( 2, linear.cdf.number_points )
            self.assertEqual( 1, linear.cdf.number_regions )
            self.assertEqual( 2, len( linear.cdf.cosines) )
            self.assertEqual( 2, len( linear.cdf.values) )
            self.assertEqual( 1, len( linear.cdf.boundaries) )
            self.assertEqual( 1, len( linear.cdf.interpolants) )
            self.assertEqual( 1, linear.cdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.cdf.interpolants[0] )
            self.assertAlmostEqual( -1.0, linear.cdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.cdf.cosines[1] )
            self.assertAlmostEqual( 0. / normalisation, linear.cdf.values[0] )
            self.assertAlmostEqual( 2. / normalisation, linear.cdf.values[1] )
            self.assertEqual( True, linear.cdf.is_linearised )

        def verify_tabulated_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 4, len( pdf.cosines ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1.  , pdf.cosines[0] )
            self.assertAlmostEqual(  0.  , pdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , pdf.cosines[2] )
            self.assertAlmostEqual(  1.  , pdf.cosines[3] )
            self.assertAlmostEqual(  0.  / normalisation, pdf.values[0] )
            self.assertAlmostEqual(  1.  / normalisation, pdf.values[1] )
            self.assertAlmostEqual(  1.5 / normalisation, pdf.values[2] )
            self.assertAlmostEqual(  2.  / normalisation, pdf.values[3] )
            self.assertAlmostEqual( 3, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 4, len( cdf.cosines ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1.  , cdf.cosines[0] )
            self.assertAlmostEqual(  0.  , cdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , cdf.cosines[2] )
            self.assertAlmostEqual(  1.  , cdf.cosines[3] )
            self.assertAlmostEqual(  0.    / normalisation, cdf.values[0] )
            self.assertAlmostEqual(  0.5   / normalisation, cdf.values[1] )
            self.assertAlmostEqual(  1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual(  2.    / normalisation, cdf.values[3] )
            self.assertAlmostEqual( 3, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

            self.assertAlmostEqual( 2.0 / normalisation, pdf.integral )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.  / normalisation, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1.  / normalisation, chunk( cosine =  0. ) )
            self.assertAlmostEqual( 1.5 / normalisation, chunk( cosine =  0.5 ) )
            self.assertAlmostEqual( 2.  / normalisation, chunk( cosine =  1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( cosine = -5. ) )
            self.assertAlmostEqual( 0.0, chunk( cosine =  5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 0.5  / normalisation, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 1.75 / normalisation, chunk( cosine = 0.75 ) )

            # verify average cosine - always the mean value even for unnormalised distributions
            self.assertAlmostEqual( 2. / 3. / 2., chunk.average_cosine )

            # verify linearisation
            linear = chunk.linearise()

            pdf = linear.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 4, len( pdf.cosines ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1.  , pdf.cosines[0] )
            self.assertAlmostEqual(  0.  , pdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , pdf.cosines[2] )
            self.assertAlmostEqual(  1.  , pdf.cosines[3] )
            self.assertAlmostEqual(  0.  / normalisation, pdf.values[0] )
            self.assertAlmostEqual(  1.  / normalisation, pdf.values[1] )
            self.assertAlmostEqual(  1.5 / normalisation, pdf.values[2] )
            self.assertAlmostEqual(  2.  / normalisation, pdf.values[3] )
            self.assertAlmostEqual( 3, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = linear.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 4, len( cdf.cosines ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1.  , cdf.cosines[0] )
            self.assertAlmostEqual(  0.  , cdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , cdf.cosines[2] )
            self.assertAlmostEqual(  1.  , cdf.cosines[3] )
            self.assertAlmostEqual(  0.    / normalisation, cdf.values[0] )
            self.assertAlmostEqual(  0.5   / normalisation, cdf.values[1] )
            self.assertAlmostEqual(  1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual(  2.    / normalisation, cdf.values[3] )
            self.assertAlmostEqual( 3, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

        # the data is given explicitly
        chunk1 = MixedAngularDistribution( pdf =IsotropicAngularDistributionFunction(), normalise = False )
        chunk2 = MixedAngularDistribution( pdf =IsotropicAngularDistributionFunction(), normalise = True )

        verify_isotropic_chunk( self, chunk1 )
        verify_isotropic_chunk( self, chunk2 )

        chunk1.normalise()
        chunk2.normalise()

        verify_isotropic_chunk( self, chunk1 )
        verify_isotropic_chunk( self, chunk2 )

        # the data is given explicitly
        chunk1 = MixedAngularDistribution( pdf = LegendreAngularDistributionFunction( [ 1., 0.5 ] ), normalise = False )
        chunk2 = MixedAngularDistribution( pdf = LegendreAngularDistributionFunction( [ 1., 0.5 ] ), normalise = True )

        verify_legendre_chunk( self, chunk1, False )
        verify_legendre_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_legendre_chunk( self, chunk1, True )
        verify_legendre_chunk( self, chunk2, True )

        # the data is given explicitly using a normalised table
        chunk1 = MixedAngularDistribution( pdf = TabulatedAngularDistributionFunction( [ -1., 0., 0.5, 1. ], [ 0., 1., 1.5, 2. ] ),
                                           normalise = False )
        chunk2 = MixedAngularDistribution( pdf = TabulatedAngularDistributionFunction( [ -1., 0., 0.5, 1. ], [ 0., 1., 1.5, 2. ] ),
                                           normalise = True )

        verify_tabulated_chunk( self, chunk1, False )
        verify_tabulated_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_tabulated_chunk( self, chunk1, True )
        verify_tabulated_chunk( self, chunk2, True )

    def test_comparison( self ) :

        left = MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.25 ] ) )
        equal = MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.25 ] ) )
        unnormalised = MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.5 ] ), True )
        different = MixedAngularDistribution( IsotropicAngularDistributionFunction() )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( True, ( left == unnormalised ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( False, ( left != unnormalised ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
