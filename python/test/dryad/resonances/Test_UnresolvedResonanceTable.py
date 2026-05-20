import unittest
import sys
from copy import copy


from njoy.dryad.resonances import UnresolvedResonanceTable, TabulatedAverageWidths, TabulatedLevelSpacing
from njoy.dryad.id import ChannelID

class Test_UnresolvedResonanceTable( unittest.TestCase ):
  """Unit test for the UnresolvedResonanceTable class."""

  def test_component( self ):


    channels = [ ChannelID('n,U235->n,U235{0,1/2,1/2+}'), 
                 ChannelID('n,U235->n,U235_e1{0,1/2,1/2+}') ]
    energies = [1., 2., 3., 4.]
    spacing_values = [ 10.0, 11.0, 12.0, 13.0 ]
    width_values = [[ 0.11, 0.12, 0.13, 0.14 ],
                    [ 0.21, 0.22, 0.23, 0.24 ]]
    dofs = [ 1, 2 ]
    
    table = UnresolvedResonanceTable( channels, energies, spacing_values, width_values, dofs )
    
    self.assertEqual( table.channels[0], channels[0] )
    self.assertEqual( table.channels[1], channels[1] )
    #self.assertEqual( table.energies, energies )
    self.assertEqual( table.spacings.values, spacing_values )
    self.assertEqual( table.widths[0].values, width_values[0] )
    self.assertEqual( table.widths[1].values, width_values[1] )
    #self.assertEqual( table.dofs, dofs )

    self.assertEqual( 0, table.channel_index( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ) )
    self.assertEqual( 1, table.channel_index( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ) )

    self.assertEqual( width_values[0], table.widths_for_channel( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ).values )
    self.assertEqual( width_values[1], table.widths_for_channel( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ).values )

    self.assertEqual( energies, table.spacings.energies )
    self.assertEqual( energies, table.widths_for_channel( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ).energies )
    self.assertEqual( energies, table.widths_for_channel( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ).energies )


if __name__ == '__main__':
  unittest.main()