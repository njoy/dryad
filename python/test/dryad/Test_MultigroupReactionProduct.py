# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import MultigroupReactionProduct
from njoy.dryad import MultigroupMultiplicity
from njoy.dryad import MultigroupAverageCosine
from njoy.dryad import MultigroupAverageEnergy
from njoy.dryad.id import ParticleID

def verify_chunk( self, chunk ) :

    # reaction product identifier
    self.assertEqual( ParticleID.neutron(), chunk.product_identifier )
    self.assertIsNone( chunk.parent_identifier )
    self.assertEqual( 0, chunk.chain_index )

    # multiplicity
    self.assertEqual( True, isinstance( chunk.multiplicity, int ) )
    self.assertEqual( 1, chunk.multiplicity )

    # average reaction product data
    self.assertEqual( 2, chunk.average_cosine.number_groups )
    self.assertEqual( 3, len( chunk.average_cosine.boundaries ) )
    self.assertAlmostEqual( 1., chunk.average_cosine.boundaries[0] )
    self.assertAlmostEqual( 2., chunk.average_cosine.boundaries[1] )
    self.assertAlmostEqual( 3., chunk.average_cosine.boundaries[2] )
    self.assertAlmostEqual( 0.1, chunk.average_cosine.values[0] )
    self.assertAlmostEqual( 0.2, chunk.average_cosine.values[1] )

    self.assertEqual( 2, chunk.average_energy.number_groups )
    self.assertEqual( 3, len( chunk.average_energy.boundaries ) )
    self.assertAlmostEqual( 1., chunk.average_energy.boundaries[0] )
    self.assertAlmostEqual( 2., chunk.average_energy.boundaries[1] )
    self.assertAlmostEqual( 3., chunk.average_energy.boundaries[2] )
    self.assertAlmostEqual( 1., chunk.average_energy.values[0] )
    self.assertAlmostEqual( 2., chunk.average_energy.values[1] )

    # metadata
    self.assertEqual( True, chunk.has_average_cosine )
    self.assertEqual( True, chunk.has_average_energy )

def verify_multigroup_chunk( self, chunk ) :

    # reaction product identifier
    self.assertEqual( ParticleID.neutron(), chunk.product_identifier )
    self.assertIsNone( chunk.parent_identifier )
    self.assertEqual( 0, chunk.chain_index )

    # multiplicity
    self.assertEqual( True, isinstance( chunk.multiplicity, MultigroupMultiplicity ) )
    self.assertEqual( 2, chunk.multiplicity.number_groups )
    self.assertAlmostEqual( 4., chunk.multiplicity.values[0] )
    self.assertAlmostEqual( 3., chunk.multiplicity.values[1] )

    # average reaction product data
    self.assertEqual( 2, chunk.average_cosine.number_groups )
    self.assertEqual( 3, len( chunk.average_cosine.boundaries ) )
    self.assertAlmostEqual( 1., chunk.average_cosine.boundaries[0] )
    self.assertAlmostEqual( 2., chunk.average_cosine.boundaries[1] )
    self.assertAlmostEqual( 3., chunk.average_cosine.boundaries[2] )
    self.assertAlmostEqual( 0.1, chunk.average_cosine.values[0] )
    self.assertAlmostEqual( 0.2, chunk.average_cosine.values[1] )

    self.assertEqual( 2, chunk.average_energy.number_groups )
    self.assertEqual( 3, len( chunk.average_energy.boundaries ) )
    self.assertAlmostEqual( 1., chunk.average_energy.boundaries[0] )
    self.assertAlmostEqual( 2., chunk.average_energy.boundaries[1] )
    self.assertAlmostEqual( 3., chunk.average_energy.boundaries[2] )
    self.assertAlmostEqual( 1., chunk.average_energy.values[0] )
    self.assertAlmostEqual( 2., chunk.average_energy.values[1] )

    # metadata
    self.assertEqual( True, chunk.has_average_cosine )
    self.assertEqual( True, chunk.has_average_energy )

class Test_MultigroupReactionProduct( unittest.TestCase ) :
    """Unit test for the MultigroupReactionProduct class."""

    def test_component( self ) :

        # the data is given explicitly using an integer multiplicity
        cosine = MultigroupAverageCosine( [ 1., 2., 3. ], [ 0.1, 0.2 ] )
        energy = MultigroupAverageEnergy( [ 1., 2., 3. ], [ 1., 2. ] )
        chunk = MultigroupReactionProduct( product = ParticleID.neutron(), multiplicity = 1,
                                           average_cosine = cosine, average_energy = energy )

        verify_chunk( self, chunk )

        # the data is given explicitly using a multigroup multiplicity
        multiplicity = MultigroupMultiplicity( [ 1., 2., 3. ], [ 4., 3. ] )
        chunk = MultigroupReactionProduct( product = ParticleID.neutron(), multiplicity = multiplicity,
                                           average_cosine = cosine, average_energy = energy )

        verify_multigroup_chunk( self, chunk )

    def test_setter_functions( self ) :

        cosine = MultigroupAverageCosine( [ 1., 2., 3. ], [ 0.1, 0.2 ] )
        energy = MultigroupAverageEnergy( [ 1., 2., 3. ], [ 1., 2. ] )
        chunk = MultigroupReactionProduct( ParticleID.neutron(), 1, cosine, energy )

        # the product identifier can be changed
        newid = ParticleID.proton()
        original = ParticleID.neutron()

        chunk.product_identifier = newid

        self.assertEqual( newid, chunk.product_identifier )

        chunk.product_identifier = original

        verify_chunk( self, chunk )

        # the parent identifier can be changed
        newid = ParticleID.proton()
        original = None

        chunk.parent_identifier = newid

        self.assertEqual( newid, chunk.parent_identifier )

        chunk.parent_identifier = original

        verify_chunk( self, chunk )

        # the chain index can be changed
        newindex = 1
        original = 0

        chunk.chain_index = newindex

        self.assertEqual( newindex, chunk.chain_index )

        chunk.chain_index = original

        verify_chunk( self, chunk )

        # the multiplicity can be changed
        newmultiplicity = MultigroupMultiplicity( [ 1., 2., 3. ], [ 4., 3. ] )
        original = 1

        chunk.multiplicity = newmultiplicity

        verify_multigroup_chunk( self, chunk )

        chunk.multiplicity = original

        verify_chunk( self, chunk )

        # the average cosine data can be changed
        newaverage = MultigroupAverageCosine( [ 1., 2., 3., 4. ], [ -1., 0., 1. ] )
        original = cosine

        chunk.average_cosine = newaverage

        self.assertEqual( newaverage, chunk.average_cosine )

        chunk.average_cosine = original

        verify_chunk( self, chunk )

        # the average energy data can be changed
        newaverage = MultigroupAverageEnergy( [ 1., 2., 3., 4. ], [ 4., 3., 2. ] )
        original = energy

        chunk.average_energy = newaverage

        self.assertEqual( newaverage, chunk.average_energy )

        chunk.average_energy = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = MultigroupReactionProduct( ParticleID.neutron(), 1 )
        equal = MultigroupReactionProduct( ParticleID.neutron(), 1 )
        different = MultigroupReactionProduct( ParticleID.proton(), 1 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
