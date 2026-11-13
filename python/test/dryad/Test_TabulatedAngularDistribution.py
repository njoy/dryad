# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import TabulatedAngularDistribution
from njoy.dryad import InterpolationType
from njoy.dryad import TabulatedAngularDistributionFunction

class Test_TabulatedAngularDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedAngularDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. / normalisation, chunk.values[0] )
            self.assertAlmostEqual( 1. / normalisation, chunk.values[1] )
            self.assertAlmostEqual( 1.5 / normalisation, chunk.values[2] )
            self.assertAlmostEqual( 2. / normalisation, chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )

            self.assertEqual( True, chunk.is_curated )

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., pdf.upper_cosine_limit )
            self.assertEqual( 4, len( pdf.cosines ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1. , pdf.cosines[0] )
            self.assertAlmostEqual( 0. , pdf.cosines[1] )
            self.assertAlmostEqual( 0.5 , pdf.cosines[2] )
            self.assertAlmostEqual( 1. , pdf.cosines[3] )
            self.assertAlmostEqual( 0. / normalisation, pdf.values[0] )
            self.assertAlmostEqual( 1. / normalisation, pdf.values[1] )
            self.assertAlmostEqual( 1.5 / normalisation, pdf.values[2] )
            self.assertAlmostEqual( 2. / normalisation, pdf.values[3] )
            self.assertEqual( 3, pdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., cdf.upper_cosine_limit )
            self.assertEqual( 4, len( cdf.cosines ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1. , cdf.cosines[0] )
            self.assertAlmostEqual( 0. , cdf.cosines[1] )
            self.assertAlmostEqual( 0.5 , cdf.cosines[2] )
            self.assertAlmostEqual( 1. , cdf.cosines[3] )
            self.assertAlmostEqual( 0. / normalisation, cdf.values[0] )
            self.assertAlmostEqual( 0.5 / normalisation, cdf.values[1] )
            self.assertAlmostEqual( 1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual( 2. / normalisation, cdf.values[3] )
            self.assertEqual( 3, cdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

            self.assertAlmostEqual( 2.0 / normalisation, pdf.integral )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0. / normalisation, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1. / normalisation, chunk( cosine = 0. ) )
            self.assertAlmostEqual( 1.5 / normalisation, chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 2. / normalisation, chunk( cosine = 1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0., chunk( cosine = -5. ) )
            self.assertAlmostEqual( 0., chunk( cosine = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 0.5 / normalisation, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 1.75 / normalisation, chunk( cosine = 0.75 ) )

            # average cosine - always the mean value even for unnormalised distributions
            self.assertAlmostEqual( 2. / 3. / 2., chunk.average_cosine )

            # linearisation
            linear = chunk.linearise()

            pdf = linear.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., pdf.upper_cosine_limit )
            self.assertEqual( 4, len( pdf.cosines ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1. , pdf.cosines[0] )
            self.assertAlmostEqual( 0. , pdf.cosines[1] )
            self.assertAlmostEqual( 0.5 , pdf.cosines[2] )
            self.assertAlmostEqual( 1. , pdf.cosines[3] )
            self.assertAlmostEqual( 0. / normalisation, pdf.values[0] )
            self.assertAlmostEqual( 1. / normalisation, pdf.values[1] )
            self.assertAlmostEqual( 1.5 / normalisation, pdf.values[2] )
            self.assertAlmostEqual( 2. / normalisation, pdf.values[3] )
            self.assertEqual( 3, pdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = linear.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., cdf.upper_cosine_limit )
            self.assertEqual( 4, len( cdf.cosines ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1. , cdf.cosines[0] )
            self.assertAlmostEqual( 0. , cdf.cosines[1] )
            self.assertAlmostEqual( 0.5 , cdf.cosines[2] )
            self.assertAlmostEqual( 1. , cdf.cosines[3] )
            self.assertAlmostEqual( 0. / normalisation, cdf.values[0] )
            self.assertAlmostEqual( 0.5 / normalisation, cdf.values[1] )
            self.assertAlmostEqual( 1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual( 2. / normalisation, cdf.values[3] )
            self.assertEqual( 3, cdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

        def verify_chunk_not_curated( self, chunk ) :

            self.assertEqual( 6, len( chunk.cosines ) )
            self.assertEqual( 6, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.cosines[4] )
            self.assertAlmostEqual( 1. , chunk.cosines[5] )
            self.assertAlmostEqual( 0., chunk.values[0] )
            self.assertAlmostEqual( 1., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 1., chunk.values[4] )
            self.assertAlmostEqual( 2., chunk.values[5] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )

            self.assertEqual( False, chunk.is_curated )

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., pdf.upper_cosine_limit )
            self.assertEqual( 6, len( pdf.cosines ) )
            self.assertEqual( 6, len( pdf.values ) )
            self.assertEqual( 2, len( pdf.boundaries ) )
            self.assertEqual( 2, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1. , pdf.cosines[0] )
            self.assertAlmostEqual( -0.5, pdf.cosines[1] )
            self.assertAlmostEqual( 0. , pdf.cosines[2] )
            self.assertAlmostEqual( 0. , pdf.cosines[3] )
            self.assertAlmostEqual( 0. , pdf.cosines[4] )
            self.assertAlmostEqual( 1. , pdf.cosines[5] )
            self.assertAlmostEqual( 0., pdf.values[0] )
            self.assertAlmostEqual( 1., pdf.values[1] )
            self.assertAlmostEqual( 2., pdf.values[2] )
            self.assertAlmostEqual( 3., pdf.values[3] )
            self.assertAlmostEqual( 1., pdf.values[4] )
            self.assertAlmostEqual( 2., pdf.values[5] )
            self.assertEqual( 2, pdf.boundaries[0] )
            self.assertEqual( 5, pdf.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, pdf.interpolants[1] )
            self.assertEqual( True, pdf.is_linearised )
            self.assertEqual( False, pdf.is_curated )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., cdf.upper_cosine_limit )
            self.assertEqual( 6, len( cdf.cosines ) )
            self.assertEqual( 6, len( cdf.values ) )
            self.assertEqual( 2, len( cdf.boundaries ) )
            self.assertEqual( 2, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1. , cdf.cosines[0] )
            self.assertAlmostEqual( -0.5, cdf.cosines[1] )
            self.assertAlmostEqual( 0. , cdf.cosines[2] )
            self.assertAlmostEqual( 0. , cdf.cosines[3] )
            self.assertAlmostEqual( 0. , cdf.cosines[4] )
            self.assertAlmostEqual( 1. , cdf.cosines[5] )
            self.assertAlmostEqual( 0. , cdf.values[0] )
            self.assertAlmostEqual( 0.25, cdf.values[1] )
            self.assertAlmostEqual( 1. , cdf.values[2] )
            self.assertAlmostEqual( 1. , cdf.values[3] )
            self.assertAlmostEqual( 1. , cdf.values[4] )
            self.assertAlmostEqual( 2.5 , cdf.values[5] )
            self.assertEqual( 2, cdf.boundaries[0] )
            self.assertEqual( 5, cdf.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf.interpolants[1] )
            self.assertEqual( True, cdf.is_linearised )
            self.assertEqual( False, cdf.is_curated )

        def verify_chunk_curated( self, chunk ) :

            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0. , chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0., chunk.values[0] )
            self.assertAlmostEqual( 1., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )

            self.assertEqual( True, chunk.is_curated )

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., pdf.upper_cosine_limit )
            self.assertEqual( 5, len( pdf.cosines ) )
            self.assertEqual( 5, len( pdf.values ) )
            self.assertEqual( 2, len( pdf.boundaries ) )
            self.assertEqual( 2, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1. , pdf.cosines[0] )
            self.assertAlmostEqual( -0.5, pdf.cosines[1] )
            self.assertAlmostEqual( 0. , pdf.cosines[2] )
            self.assertAlmostEqual( 0. , pdf.cosines[3] )
            self.assertAlmostEqual( 1. , pdf.cosines[4] )
            self.assertAlmostEqual( 0., pdf.values[0] )
            self.assertAlmostEqual( 1., pdf.values[1] )
            self.assertAlmostEqual( 2., pdf.values[2] )
            self.assertAlmostEqual( 1., pdf.values[3] )
            self.assertAlmostEqual( 2., pdf.values[4] )
            self.assertEqual( 2, pdf.boundaries[0] )
            self.assertEqual( 4, pdf.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, pdf.interpolants[1] )
            self.assertEqual( True, pdf.is_linearised )
            self.assertEqual( True, pdf.is_curated )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., cdf.upper_cosine_limit )
            self.assertEqual( 5, len( cdf.cosines ) )
            self.assertEqual( 5, len( cdf.values ) )
            self.assertEqual( 2, len( cdf.boundaries ) )
            self.assertEqual( 2, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1. , cdf.cosines[0] )
            self.assertAlmostEqual( -0.5, cdf.cosines[1] )
            self.assertAlmostEqual( 0. , cdf.cosines[2] )
            self.assertAlmostEqual( 0. , cdf.cosines[3] )
            self.assertAlmostEqual( 1. , cdf.cosines[4] )
            self.assertAlmostEqual( 0. , cdf.values[0] )
            self.assertAlmostEqual( 0.25, cdf.values[1] )
            self.assertAlmostEqual( 1. , cdf.values[2] )
            self.assertAlmostEqual( 1.0 , cdf.values[3] )
            self.assertAlmostEqual( 2.5 , cdf.values[4] )
            self.assertEqual( 2, cdf.boundaries[0] )
            self.assertEqual( 4, cdf.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf.interpolants[1] )
            self.assertEqual( True, cdf.is_linearised )
            self.assertEqual( True, cdf.is_curated )

        # cosines and probabilities for a table

        chunk1 = TabulatedAngularDistribution( cosines = [ -1., 0., 0.5, 1. ],
                                               values = [ 0., 1., 1.5, 2. ],
                                               interpolant = InterpolationType.LinearLinear,
                                               normalise = False )
        chunk2 = TabulatedAngularDistribution( cosines = [ -1., 0., 0.5, 1. ],
                                               values = [ 0., 1., 1.5, 2. ],
                                               interpolant = InterpolationType.LinearLinear,
                                               normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

        # cosines and probabilities for a table with discontinuities

        # curation can be requested at construction time

        chunk1 = TabulatedAngularDistribution( cosines = [ -1., -0.5, 0., 0., 0., 1. ],
                                               values = [ 0., 1., 2., 3., 1., 2. ],
                                               interpolant = InterpolationType.LinearLinear,
                                               normalise = False,
                                               curate = False )
        chunk2 = TabulatedAngularDistribution( cosines = [ -1., -0.5, 0., 0., 0., 1. ],
                                               values = [ 0., 1., 2., 3., 1., 2. ],
                                               interpolant = InterpolationType.LinearLinear,
                                               normalise = False,
                                               curate = True )

        verify_chunk_not_curated( self, chunk1 )
        verify_chunk_curated( self, chunk2 )

        # curation happens when linearising

        linear1 = chunk1.linearise()
        linear2 = chunk2.linearise()

        verify_chunk_curated( self, linear1 )
        verify_chunk_curated( self, linear2 )

        # curation can be requested after construction

        chunk1.curate()
        chunk2.curate()

        verify_chunk_curated( self, chunk1 )
        verify_chunk_curated( self, chunk2 )

        # cosines and probabilities for a table with discontinuities (the pdf and cdf are given explicitly and only one of them is curated)

        curated_pdf = TabulatedAngularDistributionFunction( cosines = [ -1., -0.5, 0., 0., 0., 1. ],
                                                            values = [ 0., 1., 2., 3., 1., 2. ],
                                                            interpolant = InterpolationType.LinearLinear,
                                                            curate = True )
        curated_cdf = TabulatedAngularDistributionFunction( cosines = [ -1., -0.5, 0., 0., 0., 1. ],
                                                            values = [ 0., 0.25, 1., 1., 1., 2.5 ],
                                                            interpolant = InterpolationType.LinearLinear,
                                                            curate = True )
        not_curated_pdf = TabulatedAngularDistributionFunction( cosines = [ -1., -0.5, 0., 0., 0., 1. ],
                                                                values = [ 0., 1., 2., 3., 1., 2. ],
                                                                interpolant = InterpolationType.LinearLinear,
                                                                curate = False )
        not_curated_cdf = TabulatedAngularDistributionFunction( cosines = [ -1., -0.5, 0., 0., 0., 1. ],
                                                                values = [ 0., 0.25, 1., 1., 1., 2.5 ],
                                                                interpolant = InterpolationType.LinearLinear,
                                                                curate = False )

        chunk1 = TabulatedAngularDistribution( pdf = curated_pdf,
                                               cdf = not_curated_cdf )
        chunk2 = TabulatedAngularDistribution( pdf = not_curated_pdf,
                                               cdf = curated_cdf )

        # the distribution is not curated
        self.assertEqual( True, chunk1.pdf.is_curated )
        self.assertEqual( False, chunk1.cdf.is_curated )
        self.assertEqual( False, chunk1.is_curated )

        self.assertEqual( False, chunk2.pdf.is_curated )
        self.assertEqual( True, chunk2.cdf.is_curated )
        self.assertEqual( False, chunk2.is_curated )

        # the distribution can be curated on demand
        chunk1.curate()
        chunk2.curate()

        verify_chunk_curated( self, chunk1 )
        verify_chunk_curated( self, chunk2 )

    def test_comparison( self ) :

        left = TabulatedAngularDistribution( [ -1., 1. ],
                                             [ 0.5, 0.5 ] )
        equal = TabulatedAngularDistribution( [ -1., 1. ],
                                              [ 0.5, 0.5 ] )
        unnormalised = TabulatedAngularDistribution( [ -1., 1. ],
                                                     [ 1., 1. ],
                                                     InterpolationType.LinearLinear,
                                                     True )
        different = TabulatedAngularDistribution( [ -1., 1. ],
                                                  [ 0.25, 0.75 ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( True, ( left == unnormalised ) )    # normalised under the hood, so equal
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( False, ( left != unnormalised ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # the cosine and values vector are not of the same length
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistribution( cosines = [ -1., 1. ],
                                                  values = [ 0., 0.5, 0.75, 1. ] )

if __name__ == '__main__' :

    unittest.main()
