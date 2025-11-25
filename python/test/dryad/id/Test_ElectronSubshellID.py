# standard imports
import unittest

# third party imports

# local imports
from njoy.dryad.id import ElectronSubshellID

class Test_ElectronSubshellID( unittest.TestCase ) :
    """Unit test for the ElectronSubshellID class."""

    numbers = range( 534, 580 )
    symbols = [  "1s1/2" , "2s1/2" , "2p1/2" , "2p3/2" , "3s1/2" ,
                 "3p1/2" , "3p3/2" , "3d3/2" , "3d5/2" , "4s1/2" ,
                 "4p1/2" , "4p3/2" , "4d3/2" , "4d5/2" , "4f5/2" ,
                 "4f7/2" , "5s1/2" , "5p1/2" , "5p3/2" , "5d3/2" ,
                 "5d5/2" , "5f5/2" , "5f7/2" , "5g7/2" , "5g9/2" ,
                 "6s1/2" , "6p1/2" , "6p3/2" , "6d3/2" , "6d5/2" ,
                 "6f5/2" , "6f7/2" , "6g7/2" , "6g9/2" , "6h9/2" ,
                 "6h11/2", "7s1/2" , "7p1/2" , "7p3/2" , "7d3/2" ,
                 "7d5/2" , "7f5/2" , "7f7/2" , "7g7/2" , "7g9/2" ,
                 "7h9/2" , "7h11/2", "7i11/2" , "7i13/2" ]
    names = [ "K"  , "L1" , "L2" , "L3" , "M1" ,
              "M2" , "M3" , "M4" , "M5" , "N1" ,
              "N2" , "N3" , "N4" , "N5" , "N6" ,
              "N7" , "O1" , "O2" , "O3" , "O4" ,
              "O5" , "O6" , "O7" , "O8" , "O9" ,
              "P1" , "P2" , "P3" , "P4" , "P5" ,
              "P6" , "P7" , "P8" , "P9" , "P10",
              "P11", "Q1" , "Q2" , "Q3" , "Q4" ,
              "Q5" , "Q6" , "Q7" , "Q8" , "Q9" ,
              "Q10", "Q11", "Q12", "Q13" ]
    predefined = [ ElectronSubshellID.K  , ElectronSubshellID.L1 , ElectronSubshellID.L2 , ElectronSubshellID.L3, ElectronSubshellID.M1,
                   ElectronSubshellID.M2 , ElectronSubshellID.M3 , ElectronSubshellID.M4 , ElectronSubshellID.M5, ElectronSubshellID.N1,
                   ElectronSubshellID.N2 , ElectronSubshellID.N3 , ElectronSubshellID.N4 , ElectronSubshellID.N5, ElectronSubshellID.N6,
                   ElectronSubshellID.N7 , ElectronSubshellID.O1 , ElectronSubshellID.O2 , ElectronSubshellID.O3, ElectronSubshellID.O4,
                   ElectronSubshellID.O5 , ElectronSubshellID.O6 , ElectronSubshellID.O7 , ElectronSubshellID.O8, ElectronSubshellID.O9,
                   ElectronSubshellID.P1 , ElectronSubshellID.P2 , ElectronSubshellID.P3 , ElectronSubshellID.P4, ElectronSubshellID.P5,
                   ElectronSubshellID.P6 , ElectronSubshellID.P7 , ElectronSubshellID.P8 , ElectronSubshellID.P9, ElectronSubshellID.P10,
                   ElectronSubshellID.P11, ElectronSubshellID.Q1 , ElectronSubshellID.Q2 , ElectronSubshellID.Q3, ElectronSubshellID.Q4,
                   ElectronSubshellID.Q5 , ElectronSubshellID.Q6 , ElectronSubshellID.Q7 , ElectronSubshellID.Q8, ElectronSubshellID.Q9,
                   ElectronSubshellID.Q10, ElectronSubshellID.Q11, ElectronSubshellID.Q12, ElectronSubshellID.Q13 ]

    def test_values( self ) :

        for s in self.numbers :

            i = s - self.numbers[0]

            id = ElectronSubshellID( s )
            self.assertEqual( id.mt, s )
            self.assertEqual( id.symbol, self.symbols[i] )

            id = ElectronSubshellID( self.symbols[i] )
            self.assertEqual( id.mt, s )
            self.assertEqual( id.symbol, self.symbols[i] )

            id = ElectronSubshellID( self.names[i] )
            self.assertEqual( id.mt, s )
            self.assertEqual( id.symbol, self.symbols[i] )

            id = ElectronSubshellID( self.predefined[i] )
            self.assertEqual( id.mt, s )
            self.assertEqual( id.symbol, self.symbols[i] )

    def test_component( self ) :

        id = ElectronSubshellID( ElectronSubshellID.K )
        self.assertEqual( 1, id.principal_quantum_number )
        self.assertEqual( 0, id.azimuthal_quantum_number )
        self.assertEqual( 0.5, id.total_angular_momentum )
        self.assertEqual( 534, id.mt )
        self.assertEqual( '1s1/2', id.symbol )
        self.assertEqual( id, ElectronSubshellID( '1s' ) )
        self.assertEqual( id, ElectronSubshellID( '1s+' ) )
        self.assertEqual( id, ElectronSubshellID( '1s1/2' ) )
        self.assertEqual( id, ElectronSubshellID( 'K' ) )
        self.assertEqual( True, id.is_relativistic )
        self.assertEqual( False, id.is_non_relativistic )

        id = ElectronSubshellID( '2p' )
        self.assertEqual( 2, id.principal_quantum_number )
        self.assertEqual( 1, id.azimuthal_quantum_number )
        self.assertEqual( None, id.total_angular_momentum )
        self.assertEqual( None, id.mt )
        self.assertEqual( '2p', id.symbol )
        self.assertEqual( False, id.is_relativistic )
        self.assertEqual( True, id.is_non_relativistic )

    def test_comparison( self ) :

        one = ElectronSubshellID( '1s1/2' )
        two = ElectronSubshellID( '2s1/2' )
        nonrelativistic = ElectronSubshellID( '2p' )
        relativistic = ElectronSubshellID( '2p1/2' )
        next = ElectronSubshellID( '2p3/2' )

        self.assertEqual( one < two, True )
        self.assertEqual( two < nonrelativistic, True )
        self.assertEqual( nonrelativistic < relativistic, True )
        self.assertEqual( relativistic < next, True )

        id1 = ElectronSubshellID( 'K' )
        id2 = ElectronSubshellID( 'L1' )

        self.assertEqual( id1 <  id1, False )
        self.assertEqual( id1 <= id1, True )
        self.assertEqual( id1 >  id1, False )
        self.assertEqual( id1 >= id1, True )
        self.assertEqual( id1 == id1, True )
        self.assertEqual( id1 != id1, False )
        self.assertEqual( id1 <  id2, True )
        self.assertEqual( id1 <= id2, True )
        self.assertEqual( id1 >  id2, False )
        self.assertEqual( id1 >= id2, False )
        self.assertEqual( id1 == id2, False )
        self.assertEqual( id1 != id2, True )
        self.assertEqual( id2 <  id1, False )
        self.assertEqual( id2 <= id1, False )
        self.assertEqual( id2 >  id1, True )
        self.assertEqual( id2 >= id1, True )
        self.assertEqual( id2 == id1, False )
        self.assertEqual( id2 != id1, True )

    def test_key( self ) :

        id1 = ElectronSubshellID( 'K' )
        id2 = ElectronSubshellID( 'L1' )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ ElectronSubshellID( 'K' ) ], '1' )
        self.assertEqual( map[ ElectronSubshellID( 'L1' ) ], '2' )

    def test_failures( self ) :

        # illegal values
        with self.assertRaises( ValueError ) : id = ElectronSubshellID( 'not a valid subshell id' )
        with self.assertRaises( ValueError ) : id = ElectronSubshellID( -1 )
        with self.assertRaises( ValueError ) : id = ElectronSubshellID( 533 )
        with self.assertRaises( ValueError ) : id = ElectronSubshellID( 583 )

if __name__ == '__main__' :

    unittest.main()
