# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import ShortCollisionTimeScatteringKernel

class Test_ShortCollisionTimeScatteringKernel( unittest.TestCase ) :
    """Unit test for the ShortCollisionTimeScatteringKernel class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            self.assertAlmostEqual( 293.6, chunk.moderator_temperature )
            self.assertAlmostEqual( 300. , chunk.effective_temperature )

            self.assertAlmostEqual( 0.169264243790294, chunk(  1,  1 ) )
            self.assertAlmostEqual( 0.169264243790294, chunk(  1, -1 ) )
            self.assertAlmostEqual( 0.080382331926097, chunk(  1,  2 ) )
            self.assertAlmostEqual( 0.080382331926097, chunk(  1, -2 ) )
            self.assertAlmostEqual( 0.072594377669250, chunk(  2,  2 ) )
            self.assertAlmostEqual( 0.072594377669250, chunk(  2, -2 ) )

        chunk = ShortCollisionTimeScatteringKernel( moderator_temperature = 293.6,
                                                    effective_temperature = 300 )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = ShortCollisionTimeScatteringKernel( moderator_temperature = 293.6,
                                                   effective_temperature = 300 )
        equal = ShortCollisionTimeScatteringKernel( moderator_temperature = 293.6,
                                                    effective_temperature = 300 )
        different = ShortCollisionTimeScatteringKernel( moderator_temperature = 300,
                                                        effective_temperature = 400 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
