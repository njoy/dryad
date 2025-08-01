# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import ReactionProduct
from dryad import TabulatedMultiplicity
from dryad import InterpolationType
from dryad import ReferenceFrame
from dryad import TabulatedAverageEnergy
from dryad import TwoBodyDistributionData
from dryad import IsotropicAngularDistributions
from dryad.id import ParticleID

def verify_chunk( self, chunk ) :

    # reaction product identifier
    self.assertEqual( ParticleID.neutron(), chunk.identifier )

    # multiplicity
    self.assertEqual( True, isinstance( chunk.multiplicity, int ) )
    self.assertEqual( 1, chunk.multiplicity )

    # average reaction product energy
    self.assertEqual( None, chunk.average_energy )

    # distribution data
    self.assertEqual( None, chunk.distribution_data )

    # metadata
    self.assertEqual( False, chunk.has_average_energy )
    self.assertEqual( False, chunk.has_distribution_data )

def verify_tabulated_chunk( self, chunk ) :

    # reaction product identifier
    self.assertEqual( ParticleID.neutron(), chunk.identifier )

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

    # average reaction product energy
    self.assertEqual( None, chunk.average_energy )

    # distribution data
    self.assertEqual( None, chunk.distribution_data )

    # metadata
    self.assertEqual( False, chunk.has_average_energy )
    self.assertEqual( False, chunk.has_distribution_data )

class Test_dryad_ReactionProduct( unittest.TestCase ) :
    """Unit test for the ReactionProduct class."""

    def test_component( self ) :

        # the data is given explicitly using an integer multiplicity
        chunk = ReactionProduct( id = ParticleID.neutron(), multiplicity = 1 )

        verify_chunk( self, chunk )

        # the data is given explicitly using a tabulated multiplicity
        chunk = ReactionProduct( id = ParticleID.neutron(),
                                 multiplicity = TabulatedMultiplicity ( [ 1., 2., 2., 3., 4. ],
                                                                        [ 4., 3., 4., 3., 2. ],
                                                                        [ 1, 4 ],
                                                                        [ InterpolationType.LinearLinear,
                                                                          InterpolationType.LinearLog ] ) )

        verify_tabulated_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = ReactionProduct( id = ParticleID.neutron(), multiplicity = 1 )

        # the product identifier can be changed
        newid = ParticleID.proton()
        original = ParticleID.neutron()

        chunk.identifier = newid

        self.assertEqual( newid, chunk.identifier )

        chunk.identifier = original

        verify_chunk( self, chunk )

        # the multiplicity can be changed
        newmultiplicity = TabulatedMultiplicity ( [ 1., 2., 2., 3., 4. ],
                                                  [ 4., 3., 4., 3., 2. ],
                                                  [ 1, 4 ],
                                                  [ InterpolationType.LinearLinear,
                                                    InterpolationType.LinearLog ] )
        original = 1

        chunk.multiplicity = newmultiplicity

        verify_tabulated_chunk( self, chunk )

        chunk.multiplicity = original

        verify_chunk( self, chunk )

        # the distribution data can be changed
        newdistribution = TwoBodyDistributionData( ReferenceFrame.CentreOfMass, IsotropicAngularDistributions() )
        original = None

        chunk.distribution_data = newdistribution

        self.assertEqual( newdistribution, chunk.distribution_data )

        chunk.distribution_data = original

        verify_chunk( self, chunk )

        # the average energy can be changed
        newaverage = TabulatedAverageEnergy( [ 1., 2., 2., 3., 4. ],
                                             [ 4., 3., 4., 3., 2. ],
                                             [ 1, 4 ],
                                             [ InterpolationType.LinearLinear,
                                               InterpolationType.LinearLog ] )
        original = None

        chunk.average_energy = newaverage

        self.assertEqual( newaverage, chunk.average_energy )

        chunk.average_energy = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = ReactionProduct( ParticleID.neutron(), 1 )
        equal = ReactionProduct( ParticleID.neutron(), 1 )
        different = ReactionProduct( ParticleID.proton(), 1,
                                     TwoBodyDistributionData( ReferenceFrame.CentreOfMass,
                                                              IsotropicAngularDistributions() ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
