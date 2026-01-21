# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.external import ComptonProfiles
from njoy.dryad import InterpolationType
from njoy.dryad.id import ElectronSubshellID

class Test_ComptonProfiles( unittest.TestCase ) :
    """Unit test for the ComptonProfiles class."""

    def test_component( self ) :

        def verify_chunk( self, chunk, normalise ) :

            normalisation = .50219407976 if normalise else 1.0

            # verify content
            self.assertEqual( ElectronSubshellID( '1s' ), chunk[0].subshell_identifier )

            self.assertEqual( 31, len( chunk[0].momentum ) )
            self.assertEqual( 31, len( chunk[0].values ) )
            self.assertEqual( 1, len( chunk[0].boundaries ) )
            self.assertEqual( 1, len( chunk[0].interpolants ) )

            self.assertAlmostEqual(   0.00, chunk[0].momentum[0] )
            self.assertAlmostEqual(   0.05, chunk[0].momentum[1] )
            self.assertAlmostEqual(   0.10, chunk[0].momentum[2] )
            self.assertAlmostEqual(   0.15, chunk[0].momentum[3] )
            self.assertAlmostEqual(   0.20, chunk[0].momentum[4] )
            self.assertAlmostEqual(   0.30, chunk[0].momentum[5] )
            self.assertAlmostEqual(   0.40, chunk[0].momentum[6] )
            self.assertAlmostEqual(   0.50, chunk[0].momentum[7] )
            self.assertAlmostEqual(   0.60, chunk[0].momentum[8] )
            self.assertAlmostEqual(   0.70, chunk[0].momentum[9] )
            self.assertAlmostEqual(   0.80, chunk[0].momentum[10] )
            self.assertAlmostEqual(   1.00, chunk[0].momentum[11] )
            self.assertAlmostEqual(   1.20, chunk[0].momentum[12] )
            self.assertAlmostEqual(   1.40, chunk[0].momentum[13] )
            self.assertAlmostEqual(   1.60, chunk[0].momentum[14] )
            self.assertAlmostEqual(   1.80, chunk[0].momentum[15] )
            self.assertAlmostEqual(   2.00, chunk[0].momentum[16] )
            self.assertAlmostEqual(   2.40, chunk[0].momentum[17] )
            self.assertAlmostEqual(   3.00, chunk[0].momentum[18] )
            self.assertAlmostEqual(   4.00, chunk[0].momentum[19] )
            self.assertAlmostEqual(   5.00, chunk[0].momentum[20] )
            self.assertAlmostEqual(   6.00, chunk[0].momentum[21] )
            self.assertAlmostEqual(   7.00, chunk[0].momentum[22] )
            self.assertAlmostEqual(   8.00, chunk[0].momentum[23] )
            self.assertAlmostEqual(  10.00, chunk[0].momentum[24] )
            self.assertAlmostEqual(  15.00, chunk[0].momentum[25] )
            self.assertAlmostEqual(  20.00, chunk[0].momentum[26] )
            self.assertAlmostEqual(  30.00, chunk[0].momentum[27] )
            self.assertAlmostEqual(  40.00, chunk[0].momentum[28] )
            self.assertAlmostEqual(  60.00, chunk[0].momentum[29] )
            self.assertAlmostEqual( 100.00, chunk[0].momentum[30] )

            self.assertAlmostEqual( 8.49E-01 / normalisation, chunk[0].values[0] )
            self.assertAlmostEqual( 8.42E-01 / normalisation, chunk[0].values[1] )
            self.assertAlmostEqual( 8.24E-01 / normalisation, chunk[0].values[2] )
            self.assertAlmostEqual( 7.94E-01 / normalisation, chunk[0].values[3] )
            self.assertAlmostEqual( 7.55E-01 / normalisation, chunk[0].values[4] )
            self.assertAlmostEqual( 6.55E-01 / normalisation, chunk[0].values[5] )
            self.assertAlmostEqual( 5.44E-01 / normalisation, chunk[0].values[6] )
            self.assertAlmostEqual( 4.35E-01 / normalisation, chunk[0].values[7] )
            self.assertAlmostEqual( 3.37E-01 / normalisation, chunk[0].values[8] )
            self.assertAlmostEqual( 2.57E-01 / normalisation, chunk[0].values[9] )
            self.assertAlmostEqual( 1.92E-01 / normalisation, chunk[0].values[10] )
            self.assertAlmostEqual( 1.06E-01 / normalisation, chunk[0].values[11] )
            self.assertAlmostEqual( 5.84E-02 / normalisation, chunk[0].values[12] )
            self.assertAlmostEqual( 3.27E-02 / normalisation, chunk[0].values[13] )
            self.assertAlmostEqual( 1.88E-02 / normalisation, chunk[0].values[14] )
            self.assertAlmostEqual( 1.11E-02 / normalisation, chunk[0].values[15] )
            self.assertAlmostEqual( 6.79E-03 / normalisation, chunk[0].values[16] )
            self.assertAlmostEqual( 2.75E-03 / normalisation, chunk[0].values[17] )
            self.assertAlmostEqual( 8.49E-04 / normalisation, chunk[0].values[18] )
            self.assertAlmostEqual( 1.73E-04 / normalisation, chunk[0].values[19] )
            self.assertAlmostEqual( 4.83E-05 / normalisation, chunk[0].values[20] )
            self.assertAlmostEqual( 1.68E-05 / normalisation, chunk[0].values[21] )
            self.assertAlmostEqual( 6.79E-06 / normalisation, chunk[0].values[22] )
            self.assertAlmostEqual( 3.09E-06 / normalisation, chunk[0].values[23] )
            self.assertAlmostEqual( 8.20E-07 / normalisation, chunk[0].values[24] )
            self.assertAlmostEqual( 7.40E-08 / normalisation, chunk[0].values[25] )
            self.assertAlmostEqual( 1.30E-08 / normalisation, chunk[0].values[26] )
            self.assertAlmostEqual( 1.20E-09 / normalisation, chunk[0].values[27] )
            self.assertAlmostEqual( 2.30E-10 / normalisation, chunk[0].values[28] )
            self.assertAlmostEqual( 4.30E-11 / normalisation, chunk[0].values[29] )
            self.assertAlmostEqual( 2.60E-11 / normalisation, chunk[0].values[30] )

            self.assertAlmostEqual( 30, chunk[0].boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, chunk[0].interpolants[0] )

        # the data is given explicitly using a normalised table
        chunk1 = ComptonProfiles.biggs_mendelsohn_mann_profiles( z = 1, normalise = False )
        chunk2 = ComptonProfiles.biggs_mendelsohn_mann_profiles( z = 1, normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

if __name__ == '__main__' :

    unittest.main()
