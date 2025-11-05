# standard imports
import unittest

# third party imports

# local imports
from njoy.dryad.id import ChannelID
from njoy.dryad.id import ReactionID
from njoy.dryad.resonances import ChannelQuantumNumbers

class Test_elementary_ChannelID( unittest.TestCase ) :
    """Unit test for the ChannelID class."""

    def test_values( self ) :

        elastic = ReactionID( 'n,U235->n,U235' )
        fission = ReactionID( 'n,U235->fission(t)' )
        numbers = ChannelQuantumNumbers( 0, 0.5, 0.5, +1 )

        id = ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' )
        self.assertEqual( elastic, id.reaction )
        self.assertEqual( numbers, id.quantum_numbers )
        self.assertIsNone( id.partial )
        self.assertEqual( 'n,U235->n,U235{0,1/2,1/2+}', id.symbol )
        self.assertEqual( id, ChannelID( elastic, numbers ) )

        id = ChannelID( 'n,U235->fission(t){0,1/2,1/2+}[0]' )
        self.assertEqual( fission, id.reaction )
        self.assertEqual( numbers, id.quantum_numbers )
        self.assertEqual( 0, id.partial )
        self.assertEqual( 'n,U235->fission(t){0,1/2,1/2+}[0]', id.symbol )
        self.assertEqual( id, ChannelID( fission, numbers, 0 ) )

        id = ChannelID( 'n,U235->fission(t){0,1/2,1/2+}[1]' )
        self.assertEqual( fission, id.reaction )
        self.assertEqual( numbers, id.quantum_numbers )
        self.assertEqual( 1, id.partial )
        self.assertEqual( 'n,U235->fission(t){0,1/2,1/2+}[1]', id.symbol )
        self.assertEqual( id, ChannelID( fission, numbers, 1 ) )

    def test_comparison( self ) :

        id1 = ChannelID( 'n,U235->fission(t){1,1/2,1/2-}[1]' )
        id2 = ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' )

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

        id1 = ChannelID( 'n,U235->fission(t){1,1/2,1/2-}[1]' )
        id2 = ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ ChannelID( 'n,U235->fission(t){1,1/2,1/2-}[1]' ) ], '1' )
        self.assertEqual( map[ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ], '2' )

    def test_failures( self ) :

        pass

if __name__ == '__main__' :

    unittest.main()