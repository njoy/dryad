# standard imports
import unittest
from copy import copy
import sys

# third party imports

# local imports
from njoy.dryad import MixedAngularDistribution
from njoy.dryad import MixedAngularDistributions
from njoy.dryad import IsotropicAngularDistributionFunction
from njoy.dryad import LegendreAngularDistributionFunction
from njoy.dryad import InterpolationType
from njoy.dryad import TabulatedAngularDistributionFunction

class Test_MixedAngularDistributions( unittest.TestCase ) :
    """Unit test for the LegendreAngularDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.grid ) )
            self.assertEqual( 4, len( chunk.distributions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 3., chunk.grid[2] )
            self.assertAlmostEqual( 4., chunk.grid[3] )

            self.assertEqual( True, isinstance( chunk.distributions[0].pdf, IsotropicAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[3].pdf, LegendreAngularDistributionFunction ) )

            pdf0 = chunk.distributions[0].pdf
            pdf1 = chunk.distributions[1].pdf
            pdf2 = chunk.distributions[2].pdf
            pdf3 = chunk.distributions[3].pdf

            self.assertEqual( 1.0 / normalisation, pdf0.value )
            self.assertEqual( 2, len( pdf1.coefficients ) )
            self.assertEqual( 2, len( pdf2.coefficients ) )
            self.assertEqual( 2, len( pdf3.coefficients ) )
            self.assertAlmostEqual( 1.0 / normalisation, pdf1.coefficients[0] )
            self.assertAlmostEqual( 0.02 / normalisation, pdf1.coefficients[1] )
            self.assertAlmostEqual( 1.0 / normalisation, pdf2.coefficients[0] )
            self.assertAlmostEqual( 0.2 / normalisation, pdf2.coefficients[1] )
            self.assertAlmostEqual( 1.0 / normalisation, pdf3.coefficients[0] )
            self.assertAlmostEqual( 0.8 / normalisation, pdf3.coefficients[1] )

            self.assertEqual( True, isinstance( chunk.distributions[0].cdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[3].cdf, LegendreAngularDistributionFunction ) )

            cdf0 = chunk.distributions[0].cdf
            cdf1 = chunk.distributions[1].cdf
            cdf2 = chunk.distributions[2].cdf
            cdf3 = chunk.distributions[3].cdf

            self.assertEqual( 2, len( cdf0.cosines ) )
            self.assertEqual( 2, len( cdf0.values ) )
            self.assertEqual( 1, len( cdf0.interpolants ) )
            self.assertEqual( 1, len( cdf0.boundaries ) )
            self.assertEqual( 3, len( cdf1.coefficients ) )
            self.assertEqual( 3, len( cdf2.coefficients ) )
            self.assertEqual( 3, len( cdf3.coefficients ) )
            self.assertAlmostEqual( -1., cdf0.cosines[0] )
            self.assertAlmostEqual( 1., cdf0.cosines[1] )
            self.assertAlmostEqual( 0.0 , cdf0.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, cdf0.values[1] )
            self.assertEqual( 1, cdf0.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf0.interpolants[0] )
            self.assertAlmostEqual( 0.9933333333333333 / normalisation, cdf1.coefficients[0] )
            self.assertAlmostEqual( 1.0 / normalisation, cdf1.coefficients[1] )
            self.assertAlmostEqual( 0.0066666666666666 / normalisation, cdf1.coefficients[2] )
            self.assertAlmostEqual( 0.9333333333333333 / normalisation, cdf2.coefficients[0] )
            self.assertAlmostEqual( 1.0 / normalisation, cdf2.coefficients[1] )
            self.assertAlmostEqual( 0.0666666666666666 / normalisation, cdf2.coefficients[2] )
            self.assertAlmostEqual( 0.7333333333333333 / normalisation, cdf3.coefficients[0] )
            self.assertAlmostEqual( 1.0 / normalisation, cdf3.coefficients[1] )
            self.assertAlmostEqual( 0.2666666666666666 / normalisation, cdf3.coefficients[2] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_curated )

            # evaluate

            # values of x in the x grid
            self.assertAlmostEqual( 1.0 / normalisation, chunk( 1., -0.5 ) )
            self.assertAlmostEqual( 0.99 / normalisation, chunk( 2., -0.5 ) )
            self.assertAlmostEqual( 0.9 / normalisation, chunk( 3., -0.5 ) )
            self.assertAlmostEqual( 0.6 / normalisation, chunk( 4., -0.5 ) )

            # values of x outside the x grid
            self.assertAlmostEqual( 0., chunk( 0., -0.5 ) )
            self.assertAlmostEqual( 0., chunk( 5., -0.5 ) )

            # values of x inside the x grid
            self.assertAlmostEqual( 0.995 / normalisation, chunk( 1.5, -0.5 ) )
            self.assertAlmostEqual( 0.945 / normalisation, chunk( 2.5, -0.5 ) )
            self.assertAlmostEqual( 0.75 / normalisation, chunk( 3.5, -0.5 ) )

            # average cosine - always the mean value even for unnormalised distributions
            cosines = chunk.average_cosines

            self.assertAlmostEqual( 1., cosines.lower_energy_limit )
            self.assertAlmostEqual( 4., cosines.upper_energy_limit )
            self.assertEqual( 4, cosines.number_points )
            self.assertEqual( 1, cosines.number_regions )
            self.assertEqual( 4, len( cosines.energies ) )
            self.assertEqual( 4, len( cosines.values ) )
            self.assertEqual( 1, len( cosines.boundaries ) )
            self.assertEqual( 1, len( cosines.interpolants ) )
            self.assertAlmostEqual( 1., cosines.energies[0] )
            self.assertAlmostEqual( 2., cosines.energies[1] )
            self.assertAlmostEqual( 3., cosines.energies[2] )
            self.assertAlmostEqual( 4., cosines.energies[3] )
            self.assertAlmostEqual( 0. / 2., cosines.values[0] )
            self.assertAlmostEqual( 0.04 / 3. / 2., cosines.values[1] )
            self.assertAlmostEqual( 0.4 / 3. / 2., cosines.values[2] )
            self.assertAlmostEqual( 1.6 / 3. / 2., cosines.values[3] )
            self.assertEqual( 3, cosines.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cosines.interpolants[0] )
            self.assertEqual( True, cosines.is_linearised )

            # linearisation
            linear = chunk.linearise()

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )
            self.assertEqual( 4, len( linear.grid ) )
            self.assertEqual( 4, len( linear.distributions ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )
            self.assertAlmostEqual( 1., linear.grid[0] )
            self.assertAlmostEqual( 2., linear.grid[1] )
            self.assertAlmostEqual( 3., linear.grid[2] )
            self.assertAlmostEqual( 4., linear.grid[3] )
            self.assertEqual( True, linear.distributions[0].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[1].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[2].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[3].pdf.is_linearised )
            self.assertEqual( 2, len( linear.distributions[0].pdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[1].pdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[2].pdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[3].pdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[0].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[1].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[2].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[3].pdf.values ) )
            self.assertAlmostEqual( -1.0, linear.distributions[0].pdf.cosines[0] )
            self.assertAlmostEqual( 1.0, linear.distributions[0].pdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[1].pdf.cosines[0] )
            self.assertAlmostEqual( 1.0, linear.distributions[1].pdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[2].pdf.cosines[0] )
            self.assertAlmostEqual( 1.0, linear.distributions[2].pdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[3].pdf.cosines[0] )
            self.assertAlmostEqual( 1.0, linear.distributions[3].pdf.cosines[1] )
            self.assertAlmostEqual( 1.0 / normalisation, linear.distributions[0].pdf.values[0] )
            self.assertAlmostEqual( 1.0 / normalisation, linear.distributions[0].pdf.values[1] )
            self.assertAlmostEqual( 0.98 / normalisation, linear.distributions[1].pdf.values[0] )
            self.assertAlmostEqual( 1.02 / normalisation, linear.distributions[1].pdf.values[1] )
            self.assertAlmostEqual( 0.8 / normalisation, linear.distributions[2].pdf.values[0] )
            self.assertAlmostEqual( 1.2 / normalisation, linear.distributions[2].pdf.values[1] )
            self.assertAlmostEqual( 0.2 / normalisation, linear.distributions[3].pdf.values[0] )
            self.assertAlmostEqual( 1.8 / normalisation, linear.distributions[3].pdf.values[1] )
            self.assertEqual( True, linear.distributions[0].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[1].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[2].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[3].cdf.is_linearised )
            self.assertEqual( 2, len( linear.distributions[0].cdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[1].cdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[2].cdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[3].cdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[0].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[1].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[2].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[3].cdf.values ) )
            self.assertAlmostEqual( -1.0, linear.distributions[0].cdf.cosines[0] )
            self.assertAlmostEqual( 1.0, linear.distributions[0].cdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[1].cdf.cosines[0] )
            self.assertAlmostEqual( 1.0, linear.distributions[1].cdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[2].cdf.cosines[0] )
            self.assertAlmostEqual( 1.0, linear.distributions[2].cdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[3].cdf.cosines[0] )
            self.assertAlmostEqual( 1.0, linear.distributions[3].cdf.cosines[1] )
            self.assertAlmostEqual( 0.0 / normalisation, linear.distributions[0].cdf.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, linear.distributions[0].cdf.values[1] )
            self.assertAlmostEqual( 0.0 / normalisation, linear.distributions[1].cdf.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, linear.distributions[1].cdf.values[1] )
            self.assertAlmostEqual( 0.0 / normalisation, linear.distributions[2].cdf.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, linear.distributions[2].cdf.values[1] )
            self.assertAlmostEqual( 0.0 / normalisation, linear.distributions[3].cdf.values[0] )
            self.assertAlmostEqual( 2.0 / normalisation, linear.distributions[3].cdf.values[1] )
            self.assertEqual( 3, linear.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

        def verify_chunk_with_jump_curated( self, chunk ) :

            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.grid ) )
            self.assertEqual( 5, len( chunk.distributions ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 2., chunk.grid[2] )
            self.assertAlmostEqual( 3., chunk.grid[3] )
            self.assertAlmostEqual( 4., chunk.grid[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_curated )

            self.assertEqual( True, isinstance( chunk.distributions[0].pdf, IsotropicAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[3].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[4].pdf, LegendreAngularDistributionFunction ) )

            pdf0 = chunk.distributions[0].pdf
            pdf1 = chunk.distributions[1].pdf
            pdf2 = chunk.distributions[2].pdf
            pdf3 = chunk.distributions[3].pdf
            pdf4 = chunk.distributions[4].pdf

            self.assertEqual( 1.0, pdf0.value )
            self.assertEqual( 2, len( pdf1.coefficients ) )
            self.assertEqual( 2, len( pdf2.coefficients ) )
            self.assertEqual( 2, len( pdf3.coefficients ) )
            self.assertEqual( 2, len( pdf4.coefficients ) )
            self.assertAlmostEqual( 1.0 , pdf1.coefficients[0] )
            self.assertAlmostEqual( 0.02, pdf1.coefficients[1] )
            self.assertAlmostEqual( 1.0 , pdf2.coefficients[0] )
            self.assertAlmostEqual( 0.01, pdf2.coefficients[1] )
            self.assertAlmostEqual( 1.0 , pdf3.coefficients[0] )
            self.assertAlmostEqual( 0.2 , pdf3.coefficients[1] )
            self.assertAlmostEqual( 1.0 , pdf4.coefficients[0] )
            self.assertAlmostEqual( 0.8 , pdf4.coefficients[1] )

            self.assertEqual( True, isinstance( chunk.distributions[0].cdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[3].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[4].cdf, LegendreAngularDistributionFunction ) )

            cdf0 = chunk.distributions[0].cdf
            cdf1 = chunk.distributions[1].cdf
            cdf2 = chunk.distributions[2].cdf
            cdf3 = chunk.distributions[3].cdf
            cdf4 = chunk.distributions[4].cdf

            self.assertEqual( 2, len( cdf0.cosines ) )
            self.assertEqual( 2, len( cdf0.values ) )
            self.assertEqual( 1, len( cdf0.interpolants ) )
            self.assertEqual( 1, len( cdf0.boundaries ) )
            self.assertAlmostEqual( -1., cdf0.cosines[0] )
            self.assertAlmostEqual( 1., cdf0.cosines[1] )
            self.assertAlmostEqual( 0.0, cdf0.values[0] )
            self.assertAlmostEqual( 2.0, cdf0.values[1] )
            self.assertEqual( 1, cdf0.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf0.interpolants[0] )
            self.assertEqual( 3, len( cdf1.coefficients ) )
            self.assertEqual( 3, len( cdf2.coefficients ) )
            self.assertEqual( 3, len( cdf3.coefficients ) )
            self.assertEqual( 3, len( cdf4.coefficients ) )
            self.assertAlmostEqual( 1.0 - 0.02 / 3., cdf1.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf1.coefficients[1] )
            self.assertAlmostEqual( 0.02 / 3. , cdf1.coefficients[2] )
            self.assertAlmostEqual( 1.0 - 0.01 / 3., cdf2.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf2.coefficients[1] )
            self.assertAlmostEqual( 0.01 / 3. , cdf2.coefficients[2] )
            self.assertAlmostEqual( 1.0 - 0.2 / 3. , cdf3.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf3.coefficients[1] )
            self.assertAlmostEqual( 0.2 / 3. , cdf3.coefficients[2] )
            self.assertAlmostEqual( 1.0 - 0.8 / 3. , cdf4.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf4.coefficients[1] )
            self.assertAlmostEqual( 0.8 / 3. , cdf4.coefficients[2] )

        def verify_chunk_with_jump_not_curated( self, chunk ) :

            self.assertEqual( 6, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 6, len( chunk.grid ) )
            self.assertEqual( 6, len( chunk.distributions ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 2., chunk.grid[2] )
            self.assertAlmostEqual( 2., chunk.grid[3] )
            self.assertAlmostEqual( 3., chunk.grid[4] )
            self.assertAlmostEqual( 4., chunk.grid[5] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_curated )

            self.assertEqual( True, isinstance( chunk.distributions[0].pdf, IsotropicAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[3].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[4].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[5].pdf, LegendreAngularDistributionFunction ) )

            pdf0 = chunk.distributions[0].pdf
            pdf1 = chunk.distributions[1].pdf
            pdf2 = chunk.distributions[2].pdf
            pdf3 = chunk.distributions[3].pdf
            pdf4 = chunk.distributions[4].pdf
            pdf5 = chunk.distributions[5].pdf

            self.assertEqual( 1.0, pdf0.value )
            self.assertEqual( 2, len( pdf1.coefficients ) )
            self.assertEqual( 2, len( pdf2.coefficients ) )
            self.assertEqual( 2, len( pdf3.coefficients ) )
            self.assertEqual( 2, len( pdf4.coefficients ) )
            self.assertEqual( 2, len( pdf5.coefficients ) )
            self.assertAlmostEqual( 1.0 , pdf1.coefficients[0] )
            self.assertAlmostEqual( 0.02, pdf1.coefficients[1] )
            self.assertAlmostEqual( 1.0 , pdf2.coefficients[0] )
            self.assertAlmostEqual( 0.05, pdf2.coefficients[1] )
            self.assertAlmostEqual( 1.0 , pdf3.coefficients[0] )
            self.assertAlmostEqual( 0.01, pdf3.coefficients[1] )
            self.assertAlmostEqual( 1.0 , pdf4.coefficients[0] )
            self.assertAlmostEqual( 0.2 , pdf4.coefficients[1] )
            self.assertAlmostEqual( 1.0 , pdf5.coefficients[0] )
            self.assertAlmostEqual( 0.8 , pdf5.coefficients[1] )

            self.assertEqual( True, isinstance( chunk.distributions[0].cdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[3].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[4].cdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[5].cdf, LegendreAngularDistributionFunction ) )

            cdf0 = chunk.distributions[0].cdf
            cdf1 = chunk.distributions[1].cdf
            cdf2 = chunk.distributions[2].cdf
            cdf3 = chunk.distributions[3].cdf
            cdf4 = chunk.distributions[4].cdf
            cdf5 = chunk.distributions[5].cdf

            self.assertEqual( 2, len( cdf0.cosines ) )
            self.assertEqual( 2, len( cdf0.values ) )
            self.assertEqual( 1, len( cdf0.interpolants ) )
            self.assertEqual( 1, len( cdf0.boundaries ) )
            self.assertAlmostEqual( -1., cdf0.cosines[0] )
            self.assertAlmostEqual( 1., cdf0.cosines[1] )
            self.assertAlmostEqual( 0.0, cdf0.values[0] )
            self.assertAlmostEqual( 2.0, cdf0.values[1] )
            self.assertEqual( 1, cdf0.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf0.interpolants[0] )
            self.assertEqual( 3, len( cdf1.coefficients ) )
            self.assertEqual( 3, len( cdf2.coefficients ) )
            self.assertEqual( 3, len( cdf3.coefficients ) )
            self.assertEqual( 3, len( cdf4.coefficients ) )
            self.assertEqual( 3, len( cdf5.coefficients ) )
            self.assertAlmostEqual( 1.0 - 0.02 / 3., cdf1.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf1.coefficients[1] )
            self.assertAlmostEqual( 0.02 / 3. , cdf1.coefficients[2] )
            self.assertAlmostEqual( 1.0 - 0.05 / 3., cdf2.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf2.coefficients[1] )
            self.assertAlmostEqual( 0.05 / 3. , cdf2.coefficients[2] )
            self.assertAlmostEqual( 1.0 - 0.01 / 3., cdf3.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf3.coefficients[1] )
            self.assertAlmostEqual( 0.01 / 3. , cdf3.coefficients[2] )
            self.assertAlmostEqual( 1.0 - 0.2 / 3. , cdf4.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf4.coefficients[1] )
            self.assertAlmostEqual( 0.2 / 3. , cdf4.coefficients[2] )
            self.assertAlmostEqual( 1.0 - 0.8 / 3. , cdf5.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf5.coefficients[1] )
            self.assertAlmostEqual( 0.8 / 3. , cdf5.coefficients[2] )

        def verify_linearised_chunk_with_jump( self, chunk ) :

            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.grid ) )
            self.assertEqual( 5, len( chunk.distributions ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 2., chunk.grid[2] )
            self.assertAlmostEqual( 3., chunk.grid[3] )
            self.assertAlmostEqual( 4., chunk.grid[4] )
            self.assertEqual( True, chunk.distributions[0].pdf.is_linearised )
            self.assertEqual( True, chunk.distributions[1].pdf.is_linearised )
            self.assertEqual( True, chunk.distributions[2].pdf.is_linearised )
            self.assertEqual( True, chunk.distributions[3].pdf.is_linearised )
            self.assertEqual( True, chunk.distributions[4].pdf.is_linearised )
            self.assertEqual( 2, len( chunk.distributions[0].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[0].pdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[1].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[1].pdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[2].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[2].pdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[3].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[3].pdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[4].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[4].pdf.values ) )
            self.assertAlmostEqual( -1., chunk.distributions[0].pdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[0].pdf.cosines[1] )
            self.assertAlmostEqual( -1., chunk.distributions[1].pdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[1].pdf.cosines[1] )
            self.assertAlmostEqual( -1., chunk.distributions[2].pdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[2].pdf.cosines[1] )
            self.assertAlmostEqual( -1., chunk.distributions[3].pdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[3].pdf.cosines[1] )
            self.assertAlmostEqual( -1., chunk.distributions[4].pdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[4].pdf.cosines[1] )
            self.assertAlmostEqual( 1.0 , chunk.distributions[0].pdf.values[0] )
            self.assertAlmostEqual( 1.0 , chunk.distributions[0].pdf.values[1] )
            self.assertAlmostEqual( 0.98, chunk.distributions[1].pdf.values[0] )
            self.assertAlmostEqual( 1.02, chunk.distributions[1].pdf.values[1] )
            self.assertAlmostEqual( 0.99, chunk.distributions[2].pdf.values[0] )
            self.assertAlmostEqual( 1.01, chunk.distributions[2].pdf.values[1] )
            self.assertAlmostEqual( 0.8 , chunk.distributions[3].pdf.values[0] )
            self.assertAlmostEqual( 1.2 , chunk.distributions[3].pdf.values[1] )
            self.assertAlmostEqual( 0.2 , chunk.distributions[4].pdf.values[0] )
            self.assertAlmostEqual( 1.8 , chunk.distributions[4].pdf.values[1] )
            self.assertEqual( True, chunk.distributions[0].cdf.is_linearised )
            self.assertEqual( True, chunk.distributions[1].cdf.is_linearised )
            self.assertEqual( True, chunk.distributions[2].cdf.is_linearised )
            self.assertEqual( True, chunk.distributions[3].cdf.is_linearised )
            self.assertEqual( True, chunk.distributions[4].cdf.is_linearised )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[1].cdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[1].cdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[2].cdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[2].cdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[3].cdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[3].cdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[4].cdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[4].cdf.values ) )
            self.assertAlmostEqual( -1., chunk.distributions[0].cdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[0].cdf.cosines[1] )
            self.assertAlmostEqual( -1., chunk.distributions[1].cdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[1].cdf.cosines[1] )
            self.assertAlmostEqual( -1., chunk.distributions[2].cdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[2].cdf.cosines[1] )
            self.assertAlmostEqual( -1., chunk.distributions[3].cdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[3].cdf.cosines[1] )
            self.assertAlmostEqual( -1., chunk.distributions[4].cdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[4].cdf.cosines[1] )
            self.assertAlmostEqual( 0.0, chunk.distributions[0].cdf.values[0] )
            self.assertAlmostEqual( 2.0, chunk.distributions[0].cdf.values[1] )
            self.assertAlmostEqual( 0.0, chunk.distributions[1].cdf.values[0] )
            self.assertAlmostEqual( 2.0, chunk.distributions[1].cdf.values[1] )
            self.assertAlmostEqual( 0.0, chunk.distributions[2].cdf.values[0] )
            self.assertAlmostEqual( 2.0, chunk.distributions[2].cdf.values[1] )
            self.assertAlmostEqual( 0.0, chunk.distributions[3].cdf.values[0] )
            self.assertAlmostEqual( 2.0, chunk.distributions[3].cdf.values[1] )
            self.assertAlmostEqual( 0.0, chunk.distributions[4].cdf.values[0] )
            self.assertAlmostEqual( 2.0, chunk.distributions[4].cdf.values[1] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk_with_distribution_jump_curated( self, chunk ) :

            self.assertEqual( 3, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 3, len( chunk.grid ) )
            self.assertEqual( 3, len( chunk.distributions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 3., chunk.grid[2] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_curated )

            self.assertEqual( True, isinstance( chunk.distributions[0].pdf, IsotropicAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].pdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[0].cdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].cdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].cdf, LegendreAngularDistributionFunction ) )

            self.assertEqual( True, chunk.distributions[0].is_curated )
            self.assertEqual( True, chunk.distributions[1].is_curated )
            self.assertEqual( True, chunk.distributions[2].is_curated )

            pdf0 = chunk.distributions[0].pdf
            pdf1 = chunk.distributions[1].pdf
            pdf2 = chunk.distributions[2].pdf
            cdf0 = chunk.distributions[0].cdf
            cdf1 = chunk.distributions[1].cdf
            cdf2 = chunk.distributions[2].cdf

            # distribution 0: isotropic (not affected by curation)
            self.assertAlmostEqual( 1., pdf0.value )
            self.assertEqual( 2, len( cdf0.cosines ) )
            self.assertEqual( 2, len( cdf0.values ) )
            self.assertEqual( 1, len( cdf0.boundaries ) )
            self.assertEqual( 1, len( cdf0.interpolants ) )
            self.assertAlmostEqual( -1., cdf0.cosines[0] )
            self.assertAlmostEqual( 1., cdf0.cosines[1] )
            self.assertAlmostEqual( 0., cdf0.values[0] )
            self.assertAlmostEqual( 2., cdf0.values[1] )
            self.assertEqual( 1, cdf0.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf0.interpolants[0] )
            self.assertEqual( True, cdf0.is_linearised )
            self.assertEqual( True, cdf0.is_curated )

            # distribution 1: curated jump
            self.assertEqual( 5, len( pdf1.cosines ) )
            self.assertEqual( 5, len( pdf1.values ) )
            self.assertEqual( 2, len( pdf1.boundaries ) )
            self.assertEqual( 2, len( pdf1.interpolants ) )
            self.assertAlmostEqual( -1., pdf1.cosines[0] )
            self.assertAlmostEqual( -0.5, pdf1.cosines[1] )
            self.assertAlmostEqual( 0., pdf1.cosines[2] )
            self.assertAlmostEqual( 0., pdf1.cosines[3] )
            self.assertAlmostEqual( 1., pdf1.cosines[4] )
            self.assertAlmostEqual( 0., pdf1.values[0] )
            self.assertAlmostEqual( 1., pdf1.values[1] )
            self.assertAlmostEqual( 2., pdf1.values[2] )
            self.assertAlmostEqual( 1., pdf1.values[3] )
            self.assertAlmostEqual( 2., pdf1.values[4] )
            self.assertEqual( 2, pdf1.boundaries[0] )
            self.assertEqual( 4, pdf1.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, pdf1.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, pdf1.interpolants[1] )
            self.assertEqual( True, pdf1.is_linearised )
            self.assertEqual( True, pdf1.is_curated )
            self.assertEqual( 5, len( cdf1.cosines ) )
            self.assertEqual( 5, len( cdf1.values ) )
            self.assertEqual( 2, len( cdf1.boundaries ) )
            self.assertEqual( 2, len( cdf1.interpolants ) )
            self.assertAlmostEqual( -1., cdf1.cosines[0] )
            self.assertAlmostEqual( -0.5, cdf1.cosines[1] )
            self.assertAlmostEqual( 0., cdf1.cosines[2] )
            self.assertAlmostEqual( 0., cdf1.cosines[3] )
            self.assertAlmostEqual( 1., cdf1.cosines[4] )
            self.assertAlmostEqual( 0. , cdf1.values[0] )
            self.assertAlmostEqual( 0.25, cdf1.values[1] )
            self.assertAlmostEqual( 1. , cdf1.values[2] )
            self.assertAlmostEqual( 1. , cdf1.values[3] )
            self.assertAlmostEqual( 2.5 , cdf1.values[4] )
            self.assertEqual( 2, cdf1.boundaries[0] )
            self.assertEqual( 4, cdf1.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, cdf1.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf1.interpolants[1] )
            self.assertEqual( True, cdf1.is_linearised )
            self.assertEqual( True, cdf1.is_curated )

            # distribution 2: legendre (not affected by curation)
            self.assertEqual( 2, len( pdf2.coefficients ) )
            self.assertAlmostEqual( 1.0, pdf2.coefficients[0] )
            self.assertAlmostEqual( 0.2, pdf2.coefficients[1] )
            self.assertEqual( 3, len( cdf2.coefficients ) )
            self.assertAlmostEqual( 1.0 - 0.2 / 3., cdf2.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf2.coefficients[1] )
            self.assertAlmostEqual( 0.2 / 3. , cdf2.coefficients[2] )

        def verify_chunk_with_distribution_jump_not_curated( self, chunk ) :

            self.assertEqual( 3, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 3, len( chunk.grid ) )
            self.assertEqual( 3, len( chunk.distributions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 3., chunk.grid[2] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( False, chunk.is_curated )    # the grid is curated but distribution 1 is not

            self.assertEqual( True, isinstance( chunk.distributions[0].pdf, IsotropicAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].pdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].pdf, LegendreAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[0].cdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[1].cdf, TabulatedAngularDistributionFunction ) )
            self.assertEqual( True, isinstance( chunk.distributions[2].cdf, LegendreAngularDistributionFunction ) )

            self.assertEqual( True, chunk.distributions[0].is_curated )
            self.assertEqual( False, chunk.distributions[1].is_curated )
            self.assertEqual( True, chunk.distributions[2].is_curated )

            pdf0 = chunk.distributions[0].pdf
            pdf1 = chunk.distributions[1].pdf
            pdf2 = chunk.distributions[2].pdf
            cdf0 = chunk.distributions[0].cdf
            cdf1 = chunk.distributions[1].cdf
            cdf2 = chunk.distributions[2].cdf

            # distribution 0: isotropic (not affected by curation)
            self.assertAlmostEqual( 1., pdf0.value )
            self.assertEqual( 2, len( cdf0.cosines ) )
            self.assertEqual( 2, len( cdf0.values ) )
            self.assertEqual( 1, len( cdf0.boundaries ) )
            self.assertEqual( 1, len( cdf0.interpolants ) )
            self.assertAlmostEqual( -1., cdf0.cosines[0] )
            self.assertAlmostEqual( 1., cdf0.cosines[1] )
            self.assertAlmostEqual( 0., cdf0.values[0] )
            self.assertAlmostEqual( 2., cdf0.values[1] )
            self.assertEqual( 1, cdf0.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf0.interpolants[0] )
            self.assertEqual( True, cdf0.is_linearised )
            self.assertEqual( True, cdf0.is_curated )

            # distribution 1: tabulated with a uncurated jump
            self.assertEqual( 6, len( pdf1.cosines ) )
            self.assertEqual( 6, len( pdf1.values ) )
            self.assertEqual( 2, len( pdf1.boundaries ) )
            self.assertEqual( 2, len( pdf1.interpolants ) )
            self.assertAlmostEqual( -1., pdf1.cosines[0] )
            self.assertAlmostEqual( -0.5, pdf1.cosines[1] )
            self.assertAlmostEqual( 0., pdf1.cosines[2] )
            self.assertAlmostEqual( 0., pdf1.cosines[3] )
            self.assertAlmostEqual( 0., pdf1.cosines[4] )
            self.assertAlmostEqual( 1., pdf1.cosines[5] )
            self.assertAlmostEqual( 0., pdf1.values[0] )
            self.assertAlmostEqual( 1., pdf1.values[1] )
            self.assertAlmostEqual( 2., pdf1.values[2] )
            self.assertAlmostEqual( 3., pdf1.values[3] )
            self.assertAlmostEqual( 1., pdf1.values[4] )
            self.assertAlmostEqual( 2., pdf1.values[5] )
            self.assertEqual( 2, pdf1.boundaries[0] )
            self.assertEqual( 5, pdf1.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, pdf1.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, pdf1.interpolants[1] )
            self.assertEqual( True, pdf1.is_linearised )
            self.assertEqual( False, pdf1.is_curated )
            self.assertEqual( 6, len( cdf1.cosines ) )
            self.assertEqual( 6, len( cdf1.values ) )
            self.assertEqual( 2, len( cdf1.boundaries ) )
            self.assertEqual( 2, len( cdf1.interpolants ) )
            self.assertAlmostEqual( -1., cdf1.cosines[0] )
            self.assertAlmostEqual( -0.5, cdf1.cosines[1] )
            self.assertAlmostEqual( 0., cdf1.cosines[2] )
            self.assertAlmostEqual( 0., cdf1.cosines[3] )
            self.assertAlmostEqual( 0., cdf1.cosines[4] )
            self.assertAlmostEqual( 1., cdf1.cosines[5] )
            self.assertAlmostEqual( 0. , cdf1.values[0] )
            self.assertAlmostEqual( 0.25, cdf1.values[1] )
            self.assertAlmostEqual( 1. , cdf1.values[2] )
            self.assertAlmostEqual( 1. , cdf1.values[3] )
            self.assertAlmostEqual( 1. , cdf1.values[4] )
            self.assertAlmostEqual( 2.5 , cdf1.values[5] )
            self.assertEqual( 2, cdf1.boundaries[0] )
            self.assertEqual( 5, cdf1.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, cdf1.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, cdf1.interpolants[1] )
            self.assertEqual( True, cdf1.is_linearised )
            self.assertEqual( False, cdf1.is_curated )

            # distribution 2: legendre (not affected by curation)
            self.assertEqual( 2, len( pdf2.coefficients ) )
            self.assertAlmostEqual( 1.0, pdf2.coefficients[0] )
            self.assertAlmostEqual( 0.2, pdf2.coefficients[1] )
            self.assertEqual( 3, len( cdf2.coefficients ) )
            self.assertAlmostEqual( 1.0 - 0.2 / 3., cdf2.coefficients[0] )
            self.assertAlmostEqual( 1.0 , cdf2.coefficients[1] )
            self.assertAlmostEqual( 0.2 / 3. , cdf2.coefficients[2] )

        def verify_linearised_chunk_with_distribution_jump( self, chunk ) :

            self.assertEqual( 3, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 3, len( chunk.grid ) )
            self.assertEqual( 3, len( chunk.distributions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 3., chunk.grid[2] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_curated )

            # distribution 0: linearised isotropic distribution
            self.assertEqual( 2, len( chunk.distributions[0].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[0].pdf.values ) )
            self.assertEqual( 1, len( chunk.distributions[0].pdf.boundaries ) )
            self.assertEqual( 1, len( chunk.distributions[0].pdf.interpolants ) )
            self.assertAlmostEqual( -1., chunk.distributions[0].pdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[0].pdf.cosines[1] )
            self.assertAlmostEqual( 1., chunk.distributions[0].pdf.values[0] )
            self.assertAlmostEqual( 1., chunk.distributions[0].pdf.values[1] )
            self.assertEqual( 1, chunk.distributions[0].pdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.distributions[0].pdf.interpolants[0] )
            self.assertEqual( True, chunk.distributions[0].pdf.is_linearised )
            self.assertEqual( True, chunk.distributions[0].pdf.is_curated )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.values ) )
            self.assertEqual( 1, len( chunk.distributions[0].cdf.boundaries ) )
            self.assertEqual( 1, len( chunk.distributions[0].cdf.interpolants ) )
            self.assertAlmostEqual( -1., chunk.distributions[0].cdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[0].cdf.cosines[1] )
            self.assertAlmostEqual( 0., chunk.distributions[0].cdf.values[0] )
            self.assertAlmostEqual( 2., chunk.distributions[0].cdf.values[1] )
            self.assertEqual( 1, chunk.distributions[0].cdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.distributions[0].cdf.interpolants[0] )
            self.assertEqual( True, chunk.distributions[0].cdf.is_linearised )
            self.assertEqual( True, chunk.distributions[0].cdf.is_curated )
            self.assertEqual( True, chunk.distributions[0].is_curated )

            # distribution 1: curated jump
            self.assertEqual( 5, len( chunk.distributions[1].pdf.cosines ) )
            self.assertEqual( 5, len( chunk.distributions[1].pdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[1].pdf.boundaries ) )
            self.assertEqual( 2, len( chunk.distributions[1].pdf.interpolants ) )
            self.assertAlmostEqual( -1., chunk.distributions[1].pdf.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.distributions[1].pdf.cosines[1] )
            self.assertAlmostEqual( 0., chunk.distributions[1].pdf.cosines[2] )
            self.assertAlmostEqual( 0., chunk.distributions[1].pdf.cosines[3] )
            self.assertAlmostEqual( 1., chunk.distributions[1].pdf.cosines[4] )
            self.assertAlmostEqual( 0., chunk.distributions[1].pdf.values[0] )
            self.assertAlmostEqual( 1., chunk.distributions[1].pdf.values[1] )
            self.assertAlmostEqual( 2., chunk.distributions[1].pdf.values[2] )
            self.assertAlmostEqual( 1., chunk.distributions[1].pdf.values[3] )
            self.assertAlmostEqual( 2., chunk.distributions[1].pdf.values[4] )
            self.assertEqual( 2, chunk.distributions[1].pdf.boundaries[0] )
            self.assertEqual( 4, chunk.distributions[1].pdf.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.distributions[1].pdf.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.distributions[1].pdf.interpolants[1] )
            self.assertEqual( True, chunk.distributions[1].pdf.is_linearised )
            self.assertEqual( True, chunk.distributions[1].pdf.is_curated )
            self.assertEqual( 5, len( chunk.distributions[1].cdf.cosines ) )
            self.assertEqual( 5, len( chunk.distributions[1].cdf.values ) )
            self.assertEqual( 2, len( chunk.distributions[1].cdf.boundaries ) )
            self.assertEqual( 2, len( chunk.distributions[1].cdf.interpolants ) )
            self.assertAlmostEqual( -1., chunk.distributions[1].cdf.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.distributions[1].cdf.cosines[1] )
            self.assertAlmostEqual( 0., chunk.distributions[1].cdf.cosines[2] )
            self.assertAlmostEqual( 0., chunk.distributions[1].cdf.cosines[3] )
            self.assertAlmostEqual( 1., chunk.distributions[1].cdf.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.distributions[1].cdf.values[0] )
            self.assertAlmostEqual( 0.25, chunk.distributions[1].cdf.values[1] )
            self.assertAlmostEqual( 1. , chunk.distributions[1].cdf.values[2] )
            self.assertAlmostEqual( 1. , chunk.distributions[1].cdf.values[3] )
            self.assertAlmostEqual( 2.5 , chunk.distributions[1].cdf.values[4] )
            self.assertEqual( 2, chunk.distributions[1].cdf.boundaries[0] )
            self.assertEqual( 4, chunk.distributions[1].cdf.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.distributions[1].cdf.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.distributions[1].cdf.interpolants[1] )
            self.assertEqual( True, chunk.distributions[1].cdf.is_linearised )
            self.assertEqual( True, chunk.distributions[1].cdf.is_curated )
            self.assertEqual( True, chunk.distributions[1].is_curated )

            # distribution 2: linearised legendre distribution
            self.assertEqual( 2, len( chunk.distributions[2].pdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[2].pdf.values ) )
            self.assertEqual( 1, len( chunk.distributions[2].pdf.boundaries ) )
            self.assertEqual( 1, len( chunk.distributions[2].pdf.interpolants ) )
            self.assertAlmostEqual( -1., chunk.distributions[2].pdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[2].pdf.cosines[1] )
            self.assertAlmostEqual( 0.8, chunk.distributions[2].pdf.values[0] )
            self.assertAlmostEqual( 1.2, chunk.distributions[2].pdf.values[1] )
            self.assertEqual( 1, chunk.distributions[2].pdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.distributions[2].pdf.interpolants[0] )
            self.assertEqual( True, chunk.distributions[2].pdf.is_linearised )
            self.assertEqual( True, chunk.distributions[2].pdf.is_curated )
            self.assertEqual( 2, len( chunk.distributions[2].cdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[2].cdf.values ) )
            self.assertEqual( 1, len( chunk.distributions[2].cdf.boundaries ) )
            self.assertEqual( 1, len( chunk.distributions[2].cdf.interpolants ) )
            self.assertAlmostEqual( -1., chunk.distributions[2].cdf.cosines[0] )
            self.assertAlmostEqual( 1., chunk.distributions[2].cdf.cosines[1] )
            self.assertAlmostEqual( 0., chunk.distributions[2].cdf.values[0] )
            self.assertAlmostEqual( 2., chunk.distributions[2].cdf.values[1] )
            self.assertEqual( 1, chunk.distributions[2].cdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.distributions[2].cdf.interpolants[0] )
            self.assertEqual( True, chunk.distributions[2].cdf.is_linearised )
            self.assertEqual( True, chunk.distributions[2].cdf.is_curated )
            self.assertEqual( True, chunk.distributions[2].is_curated )

        # distributions and energy values

        chunk1 = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                            distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ) ],
                                            interpolant = InterpolationType.LinearLinear,
                                            normalise = False )
        chunk2 = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                            distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ) ],
                                            interpolant = InterpolationType.LinearLinear,
                                            normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

        # linearised data with a jump that consist of more than 2 points (curate is not requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump are kept. boundaries always point to the first point
        # in the jump, regardless of curation.

        chunk = MixedAngularDistributions( grid = [ 1., 2., 2., 2., 3., 4. ],
                                           distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1.0 ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.05 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.01 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ) ] )

        original = copy( chunk )

        # a MixedAngularDistributions can be constructed and members can be tested
        verify_chunk_with_jump_not_curated( self, chunk )

        # the table can be curated on demand and the extraneous points are removed
        chunk.curate()

        verify_chunk_with_jump_curated( self, chunk )

        # the table can be linearised and the extraneous point in the jump is removed
        chunk = copy( original )
        linear = chunk.linearise()

        verify_linearised_chunk_with_jump( self, linear )

        # linearised data with a jump that consist of more than 2 points (curate is requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump are kept. boundaries always point to the first point
        # in the jump, regardless of curation.

        chunk = MixedAngularDistributions( grid = [ 1., 2., 2., 2., 3., 4. ],
                                           distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1.0 ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.05 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.01 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ) ],
                                           interpolant = InterpolationType.LinearLinear,
                                           normalise = False,
                                           curate = True )

        # a MixedAngularDistributions can be constructed and members can be tested
        verify_chunk_with_jump_curated( self, chunk )

        # calling curate() again on an already curated table does not change anything
        chunk.curate()

        verify_chunk_with_jump_curated( self, chunk )

        # linearised data with a jump that consist of more than 2 points in one of the distributions (curate is not requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump of a distribution are kept. curation of the
        # distributions removes them from both the pdf and the cdf of the tabulated
        # distribution (the other distribution types are not affected).

        chunk = MixedAngularDistributions( grid = [ 1., 2., 3. ],
                                           distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                             MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., -0.5, 0., 0., 0., +1. ], [ 0., 1., 2., 3., 1., 2. ] ) ),    # <-- jump of 3 x values
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ) ] )

        original = copy( chunk )

        # a MixedAngularDistributions can be constructed and members can be tested
        verify_chunk_with_distribution_jump_not_curated( self, chunk )

        # the table can be curated on demand and the extraneous points are removed
        chunk.curate()

        verify_chunk_with_distribution_jump_curated( self, chunk )

        # the table can be linearised and the extraneous point in the jump is removed
        chunk = copy( original )
        linear = chunk.linearise()

        verify_linearised_chunk_with_distribution_jump( self, linear )

        # linearised data with a jump that consist of more than 2 points in one of the distributions (curate is requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump of a distribution are kept. curation of the
        # distributions removes them from both the pdf and the cdf of the tabulated
        # distribution (the other distribution types are not affected).

        chunk = MixedAngularDistributions( grid = [ 1., 2., 3. ],
                                           distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                             MixedAngularDistribution( TabulatedAngularDistributionFunction( [ -1., -0.5, 0., 0., 0., +1. ], [ 0., 1., 2., 3., 1., 2. ] ) ),    # <-- jump of 3 x values
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ) ],
                                           interpolant = InterpolationType.LinearLinear,
                                           normalise = False,
                                           curate = True )

        # a MixedAngularDistributions can be constructed and members can be tested
        verify_chunk_with_distribution_jump_curated( self, chunk )

        # calling curate() again on an already curated table does not change anything
        chunk.curate()

        verify_chunk_with_distribution_jump_curated( self, chunk )

        # data with a jump at the beginning
        # note: at construction time, the first point is removed

        chunk = MixedAngularDistributions( grid = [ 1., 1., 2., 3., 4. ],
                                           distributions = [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.01 ] ) ),
                                                             MixedAngularDistribution( IsotropicAngularDistributionFunction( 1.0 ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ) ] )

        # a MixedAngularDistributions can be constructed and members can be tested
        verify_chunk( self, chunk, False )

        # data with a jump at the end
        # note: at construction time, the last point is removed

        chunk = MixedAngularDistributions( grid = [ 1., 2., 3., 4., 4. ],
                                           distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.01 ] ) ) ] )

        # a MixedAngularDistributions can be constructed and members can be tested
        verify_chunk( self, chunk, False )

    def test_comparison( self ) :

        left = MixedAngularDistributions( [ 1., 2., 3., 4. ],
                                          [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5 ] ) ),
                                            MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.01 ] ) ),
                                            MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.1 ] ) ),
                                            MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.4 ] ) ) ] )
        equal = MixedAngularDistributions( [ 1., 2., 3., 4. ],
                                           [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5 ] ) ),
                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.01 ] ) ),
                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.1 ] ) ),
                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.4 ] ) ) ] )
        unnormalised = MixedAngularDistributions( [ 1., 2., 3., 4. ],
                                                  [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1. ] ) ),
                                                    MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                    MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                    MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ],
                                                  InterpolationType.LinearLinear,
                                                  True )
        different = MixedAngularDistributions( [ 1., 4. ],
                                               [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5 ] ) ),
                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.4 ] ) ) ] )

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

        # there are not enough values in the x or f(y) grid
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [], distributions = [] )

        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1. ],
                                               distributions = [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5 ] ) ) ] )

        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [],
                                               distributions = [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5 ] ) ) ] )

        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1. ],
                                               distributions = [] )

        # the x and f(y) grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                               distributions = [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.01 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.1 ] ) ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                               distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ) ],
                                               boundaries = [ 3 ],
                                               interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1., 3., 2., 4. ],
                                               distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                               distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.02 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.2 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1.0, 0.8 ] ) ) ],
                                               boundaries = [ 2 ],
                                               interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
