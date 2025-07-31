# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.atomic import TransitionType
from dryad.atomic import RadiativeTransitionData
from dryad.atomic import NonRadiativeTransitionData
from dryad.atomic import ElectronSubshellConfiguration
from dryad.id import ElectronSubshellID

def verify_chunk_without_transitions( self, chunk ) :

    self.assertEqual( ElectronSubshellID( 'K' ), chunk.identifier )
    self.assertAlmostEqual( 538, chunk.binding_energy )
    self.assertAlmostEqual( 2, chunk.population )

    self.assertEqual( False, chunk.has_radiative_transitions )
    self.assertEqual( False, chunk.has_non_radiative_transitions )
    self.assertEqual( False, chunk.has_transitions )

    self.assertEqual( 0, chunk.number_radiative_transitions )
    self.assertEqual( 0, chunk.number_non_radiative_transitions )
    self.assertEqual( 0, chunk.number_transitions )
    self.assertEqual( 0, len( chunk.radiative_transitions ) )
    self.assertEqual( 0, len( chunk.non_radiative_transitions ) )

    self.assertAlmostEqual( 0, chunk.total_radiative_probability )
    self.assertAlmostEqual( 0, chunk.total_non_radiative_probability )

def verify_chunk( self, chunk, normalise ) :

    self.assertEqual( ElectronSubshellID( 'K' ), chunk.identifier )
    self.assertAlmostEqual( 538, chunk.binding_energy )
    self.assertAlmostEqual( 2, chunk.population )

    self.assertEqual( True, chunk.has_radiative_transitions )
    self.assertEqual( True, chunk.has_non_radiative_transitions )
    self.assertEqual( True, chunk.has_transitions )

    self.assertEqual( 2, chunk.number_radiative_transitions )
    self.assertEqual( 6, chunk.number_non_radiative_transitions )
    self.assertEqual( 8, chunk.number_transitions )
    self.assertEqual( 2, len( chunk.radiative_transitions ) )
    self.assertEqual( 6, len( chunk.non_radiative_transitions ) )

    normalisation = 1.00000015 if normalise else 1.0

    self.assertEqual( TransitionType.Radiative, chunk.radiative_transitions[0].type )
    self.assertEqual( TransitionType.Radiative, chunk.radiative_transitions[1].type )
    self.assertEqual( ElectronSubshellID( 'L2' ), chunk.radiative_transitions[0].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), chunk.radiative_transitions[1].originating_shell )
    self.assertAlmostEqual( 0.00190768 / normalisation, chunk.radiative_transitions[0].probability )
    self.assertAlmostEqual( 0.00380027 / normalisation, chunk.radiative_transitions[1].probability )
    self.assertAlmostEqual( 523.09, chunk.radiative_transitions[0].energy )
    self.assertAlmostEqual( 523.13, chunk.radiative_transitions[1].energy )

    self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[0].type )
    self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[1].type )
    self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[2].type )
    self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[3].type )
    self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[4].type )
    self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[5].type )
    self.assertEqual( ElectronSubshellID( 'L1' ), chunk.non_radiative_transitions[0].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), chunk.non_radiative_transitions[1].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), chunk.non_radiative_transitions[2].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), chunk.non_radiative_transitions[3].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), chunk.non_radiative_transitions[4].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), chunk.non_radiative_transitions[5].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), chunk.non_radiative_transitions[0].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), chunk.non_radiative_transitions[1].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), chunk.non_radiative_transitions[2].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), chunk.non_radiative_transitions[3].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), chunk.non_radiative_transitions[4].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), chunk.non_radiative_transitions[5].emitting_shell )
    self.assertAlmostEqual( 0.178644  / normalisation, chunk.non_radiative_transitions[0].probability )
    self.assertAlmostEqual( 0.116224  / normalisation, chunk.non_radiative_transitions[1].probability )
    self.assertAlmostEqual( 0.230418  / normalisation, chunk.non_radiative_transitions[2].probability )
    self.assertAlmostEqual( 0.0110822 / normalisation, chunk.non_radiative_transitions[3].probability )
    self.assertAlmostEqual( 0.291115  / normalisation, chunk.non_radiative_transitions[4].probability )
    self.assertAlmostEqual( 0.166809  / normalisation, chunk.non_radiative_transitions[5].probability )
    self.assertAlmostEqual( 478.82, chunk.non_radiative_transitions[0].energy )
    self.assertAlmostEqual( 493.86, chunk.non_radiative_transitions[1].energy )
    self.assertAlmostEqual( 493.9 , chunk.non_radiative_transitions[2].energy )
    self.assertAlmostEqual( 508.9 , chunk.non_radiative_transitions[3].energy )
    self.assertAlmostEqual( 508.94, chunk.non_radiative_transitions[4].energy )
    self.assertAlmostEqual( 508.98, chunk.non_radiative_transitions[5].energy )

    self.assertAlmostEqual( 0.00570795 / normalisation, chunk.total_radiative_probability )
    self.assertAlmostEqual( 0.9942922  / normalisation, chunk.total_non_radiative_probability )

class Test_dryad_ElectronSubshellConfiguration( unittest.TestCase ) :
    """Unit test for the ElectronSubshellConfiguration class."""

    def test_component( self ) :

        # the data is given explicitly without transition data
        chunk = ElectronSubshellConfiguration( id = ElectronSubshellID( 'K' ), energy = 538, population = 2. )

        verify_chunk_without_transitions( self, chunk )

        # the data is given explicitly with transition data - not normalised
        chunk = ElectronSubshellConfiguration( id = ElectronSubshellID( 'K' ), energy = 538, population = 2.,
                                               radiative = [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                                             RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                               non_radiative = [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644 , 478.82 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224 , 493.86 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418 , 493.9 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115 , 508.94 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809 , 508.98 ) ],
                                               normalise = False )

        verify_chunk( self, chunk, False )

        chunk.normalise()

        verify_chunk( self, chunk, True )

        # the data is given explicitly with transition data - normalised
        chunk = ElectronSubshellConfiguration( id = ElectronSubshellID( 'K' ), energy = 538, population = 2.,
                                               radiative = [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                                             RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                               non_radiative = [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644 , 478.82 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224 , 493.86 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418 , 493.9 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115 , 508.94 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809 , 508.98 ) ],
                                               normalise = True )

        verify_chunk( self, chunk, True )

        chunk.normalise()

        verify_chunk( self, chunk, True )

    def test_setter_functions( self ) :

        chunk = ElectronSubshellConfiguration( id = ElectronSubshellID( 'K' ), energy = 538, population = 2. )

        # the binding energy can be changed
        newenergy = 538.6
        original = 538

        chunk.binding_energy = newenergy

        self.assertEqual( newenergy, chunk.binding_energy )

        chunk.binding_energy = original

        verify_chunk_without_transitions( self, chunk )

        # the population can be changed
        newpopulation = 1.5
        original = 2

        chunk.population = newpopulation

        self.assertEqual( newpopulation, chunk.population )

        chunk.population = original

        verify_chunk_without_transitions( self, chunk )

        # the transitions can be changed
        new_radiative = [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                          RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ]
        new_non_radiative = [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644 , 478.82 ),
                              NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224 , 493.86 ),
                              NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418 , 493.9 ),
                              NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                              NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115 , 508.94 ),
                              NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809 , 508.98 ) ]

        chunk.radiative_transitions = new_radiative
        chunk.non_radiative_transitions = new_non_radiative

        verify_chunk( self, chunk, False )

        chunk.radiative_transitions = []
        chunk.non_radiative_transitions = []

        verify_chunk_without_transitions( self, chunk )

    def test_comparison( self ) :

        k_shell = ElectronSubshellID( ElectronSubshellID.K )

        left = ElectronSubshellConfiguration( k_shell, 538., 2.,
                                              [ RadiativeTransitionData( ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                                RadiativeTransitionData( ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) ],
                                              [ NonRadiativeTransitionData( ElectronSubshellID( "L1" ), ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                                NonRadiativeTransitionData( ElectronSubshellID( "L1" ), ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
                                                NonRadiativeTransitionData( ElectronSubshellID( "L1" ), ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
                                                NonRadiativeTransitionData( ElectronSubshellID( "L2" ), ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
                                                NonRadiativeTransitionData( ElectronSubshellID( "L2" ), ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
                                                NonRadiativeTransitionData( ElectronSubshellID( "L3" ), ElectronSubshellID( "L3" ), 0.166809, 508.98 ) ] )
        equal = ElectronSubshellConfiguration( k_shell, 538., 2.,
                                               [ RadiativeTransitionData( ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                                 RadiativeTransitionData( ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) ],
                                               [ NonRadiativeTransitionData( ElectronSubshellID( "L1" ), ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                                 NonRadiativeTransitionData( ElectronSubshellID( "L1" ), ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
                                                 NonRadiativeTransitionData( ElectronSubshellID( "L1" ), ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
                                                 NonRadiativeTransitionData( ElectronSubshellID( "L2" ), ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
                                                 NonRadiativeTransitionData( ElectronSubshellID( "L2" ), ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
                                                 NonRadiativeTransitionData( ElectronSubshellID( "L3" ), ElectronSubshellID( "L3" ), 0.166809, 508.98 ) ] )
        different = ElectronSubshellConfiguration( k_shell, 538., 2.,
                                                   [ RadiativeTransitionData( ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                                     RadiativeTransitionData( ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) ],
                                                   [ NonRadiativeTransitionData( ElectronSubshellID( "L1" ), ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                                     NonRadiativeTransitionData( ElectronSubshellID( "L3" ), ElectronSubshellID( "L3" ), 0.166809, 508.98 ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
