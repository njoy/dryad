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

        def verify_isotropic_chunk( self, chunk, normalise ) :

            self.assertEqual( True, isinstance( chunk.pdf, IsotropicAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.cdf, TabulatedAngularDistributionFunction ) )

            self.assertEqual( True, chunk.is_curated )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., cdf.upper_cosine_limit )
            self.assertEqual( 2, len( cdf.cosines ) )
            self.assertEqual( 2, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1., cdf.cosines[0] )
            self.assertAlmostEqual( 1., cdf.cosines[1] )
            self.assertAlmostEqual( 0., cdf.values[0] )
            self.assertAlmostEqual( 1., cdf.values[1] )
            self.assertEqual( 1, cdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

            # evaluate
            self.assertAlmostEqual( 0.5, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 0.5, chunk( cosine = 0. ) )
            self.assertAlmostEqual( 0.5, chunk( cosine = 1. ) )

            # average cosine - always the mean value even for unnormalised distributions
            self.assertAlmostEqual( 0., chunk.average_cosine )

            # linearisation
            linear = chunk.linearise()

            linearpdf = linear.pdf
            self.assertAlmostEqual( -1., linearpdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., linearpdf.upper_cosine_limit )
            self.assertEqual( 2, len( linearpdf.cosines ) )
            self.assertEqual( 2, len( linearpdf.values ) )
            self.assertEqual( 1, len( linearpdf.boundaries ) )
            self.assertEqual( 1, len( linearpdf.interpolants ) )
            self.assertAlmostEqual( -1., linearpdf.cosines[0] )
            self.assertAlmostEqual( 1., linearpdf.cosines[1] )
            self.assertAlmostEqual( 0.5, linearpdf.values[0] )
            self.assertAlmostEqual( 0.5, linearpdf.values[1] )
            self.assertEqual( 1, linearpdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linearpdf.interpolants[0] )

            linearcdf = linear.cdf
            self.assertAlmostEqual( -1., linearcdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., linearcdf.upper_cosine_limit )
            self.assertEqual( 2, len( linearcdf.cosines ) )
            self.assertEqual( 2, len( linearcdf.values ) )
            self.assertEqual( 1, len( linearcdf.boundaries ) )
            self.assertEqual( 1, len( linearcdf.interpolants ) )
            self.assertAlmostEqual( -1., linearcdf.cosines[0] )
            self.assertAlmostEqual( 1., linearcdf.cosines[1] )
            self.assertAlmostEqual( 0., linearcdf.values[0] )
            self.assertAlmostEqual( 1., linearcdf.values[1] )
            self.assertEqual( 1, linearcdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linearcdf.interpolants[0] )

        def verify_legendre_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            self.assertEqual( True, isinstance( chunk.pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.cdf, LegendreAngularDistributionFunction ) )

            self.assertEqual( True, chunk.is_curated )

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., pdf.upper_cosine_limit )
            self.assertEqual( 1, pdf.order )
            self.assertEqual( 2, len( pdf.coefficients ) )
            self.assertAlmostEqual( 1.0 / normalisation, pdf.coefficients[0] )
            self.assertAlmostEqual( 0.5 / normalisation, pdf.coefficients[1] )

            self.assertAlmostEqual( 2.0 / normalisation, pdf.integral )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., cdf.upper_cosine_limit )
            self.assertEqual( 2, cdf.order )
            self.assertEqual( 3, len( cdf.coefficients ) )
            self.assertAlmostEqual( 0.8333333333333333 / normalisation, cdf.coefficients[0] )
            self.assertAlmostEqual( 1. / normalisation , cdf.coefficients[1] )
            self.assertAlmostEqual( 0.1666666666666666 / normalisation, cdf.coefficients[2] )
            self.assertAlmostEqual( 0., cdf( -1. ) )
            self.assertAlmostEqual( 2. / normalisation, cdf( 1. ) )

            # evaluate
            self.assertAlmostEqual( 0.5 / normalisation, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1.0 / normalisation, chunk( cosine = 0. ) )
            self.assertAlmostEqual( 1.5 / normalisation, chunk( cosine = 1. ) )

            # average cosine - always the mean value even for unnormalised distributions
            self.assertAlmostEqual( 1. / 3. / 2., chunk.average_cosine )

            # linearisation
            linear = chunk.linearise()

            linearpdf = linear.pdf
            self.assertAlmostEqual( -1., linearpdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., linearpdf.upper_cosine_limit )
            self.assertEqual( 2, len( linearpdf.cosines ) )
            self.assertEqual( 2, len( linearpdf.values ) )
            self.assertEqual( 1, len( linearpdf.boundaries ) )
            self.assertEqual( 1, len( linearpdf.interpolants ) )
            self.assertAlmostEqual( -1., linearpdf.cosines[0] )
            self.assertAlmostEqual( 1., linearpdf.cosines[1] )
            self.assertAlmostEqual( 0.5 / normalisation, linearpdf.values[0] )
            self.assertAlmostEqual( 1.5 / normalisation, linearpdf.values[1] )
            self.assertEqual( 1, linearpdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linearpdf.interpolants[0] )

            linearcdf = linear.cdf
            self.assertAlmostEqual( -1., linearcdf.lower_cosine_limit )
            self.assertAlmostEqual( 1., linearcdf.upper_cosine_limit )
            self.assertEqual( 2, len( linearcdf.cosines ) )
            self.assertEqual( 2, len( linearcdf.values ) )
            self.assertEqual( 1, len( linearcdf.boundaries ) )
            self.assertEqual( 1, len( linearcdf.interpolants ) )
            self.assertAlmostEqual( -1., linearcdf.cosines[0] )
            self.assertAlmostEqual( 1., linearcdf.cosines[1] )
            self.assertAlmostEqual( 0. / normalisation, linearcdf.values[0] )
            self.assertAlmostEqual( 2. / normalisation, linearcdf.values[1] )
            self.assertEqual( 1, linearcdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linearcdf.interpolants[0] )

        def verify_tabulated_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            self.assertEqual( True, isinstance( chunk.pdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.cdf, TabulatedAngularDistributionFunction ) )

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

            # evaluation

            # values of x in the x grid
            self.assertAlmostEqual( 0. / normalisation, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1. / normalisation, chunk( cosine = 0. ) )
            self.assertAlmostEqual( 1.5 / normalisation, chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 2. / normalisation, chunk( cosine = 1. ) )

            # values of x outside the x grid
            self.assertAlmostEqual( 0., chunk( cosine = -5. ) )
            self.assertAlmostEqual( 0., chunk( cosine = 5. ) )

            # values of x inside the x grid
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

            self.assertEqual( True, isinstance( chunk.pdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.cdf, TabulatedAngularDistributionFunction ) )

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

            self.assertEqual( True, isinstance( chunk.pdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.cdf, TabulatedAngularDistributionFunction ) )

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

        def verify_chunk_not_curated_tabulated_angular_distribution( self, chunk ) :

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

        def verify_chunk_curated_tabulated_angular_distribution( self, chunk ) :

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

        # an IsotropicAngularDistributionFunction instance

        chunk1 = MixedAngularDistribution( IsotropicAngularDistributionFunction(),
                                           False )
        chunk2 = MixedAngularDistribution( IsotropicAngularDistributionFunction(),
                                           True )

        verify_isotropic_chunk( self, chunk1, False )
        verify_isotropic_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_isotropic_chunk( self, chunk1, True )
        verify_isotropic_chunk( self, chunk2, True )

        # a LegendreAngularDistributionFunction instance

        chunk1 = MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.5 ] ),
                                           False )
        chunk2 = MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.5 ] ),
                                           True )

        verify_legendre_chunk( self, chunk1, False )
        verify_legendre_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_legendre_chunk( self, chunk1, True )
        verify_legendre_chunk( self, chunk2, True )

        # a TabulatedAngularDistributionFunction instance

        chunk1 = MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., 0., 0.5, 1. ], [ 0., 1., 1.5, 2. ], InterpolationType.LinearLinear ),
                                           False )
        chunk2 = MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., 0., 0.5, 1. ], [ 0., 1., 1.5, 2. ], InterpolationType.LinearLinear ),
                                           True )

        verify_tabulated_chunk( self, chunk1, False )
        verify_tabulated_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_tabulated_chunk( self, chunk1, True )
        verify_tabulated_chunk( self, chunk2, True )

        # a TabulatedAngularDistributionFunction instance with discontinuities

        chunk1 = MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., -0.5, 0., 0., 0., 1. ], [ 0., 1., 2., 3., 1., 2. ], InterpolationType.LinearLinear, False ) )
        chunk2 = MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., -0.5, 0., 0., 0., 1. ], [ 0., 1., 2., 3., 1., 2. ], InterpolationType.LinearLinear, True ) )

        verify_chunk_not_curated( self, chunk1 )
        verify_chunk_curated( self, chunk2 )

        # curation happens when linearising

        linear1 = chunk1.linearise()
        linear2 = chunk2.linearise()

        verify_chunk_curated_tabulated_angular_distribution( self, linear1 )
        verify_chunk_curated_tabulated_angular_distribution( self, linear2 )

        # curation can be requested after construction

        chunk1.curate()
        chunk2.curate()

        verify_chunk_curated( self, chunk1 )
        verify_chunk_curated( self, chunk2 )

    def test_comparison( self ) :

        left = MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., 1. ], [ 0.5, 0.5 ] ) )
        equal = MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., 1. ], [ 0.5, 0.5 ] ) )
        unnormalised = MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., 1. ], [ 1., 1. ], InterpolationType.LinearLinear ),
                                                 True )
        different = MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 1. ] ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( True, ( left == unnormalised ) )    # normalised under the hood, so equal
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( False, ( left != unnormalised ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
