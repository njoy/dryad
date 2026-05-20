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
    self.assertEqual( table.spacings.values, spacing_values )
    self.assertEqual( table.widths[0].values, width_values[0] )
    self.assertEqual( table.widths[1].values, width_values[1] )

    self.assertEqual( 0, table.channel_index( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ) )
    self.assertEqual( 1, table.channel_index( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ) )

    self.assertEqual( width_values[0], table.widths_for_channel( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ).values )
    self.assertEqual( width_values[1], table.widths_for_channel( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ).values )

    self.assertEqual( energies, table.spacings.energies )
    self.assertEqual( energies, table.widths_for_channel( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ).energies )
    self.assertEqual( energies, table.widths_for_channel( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ).energies )

  def test_equality( self ):
    
    left = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                                                  ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ],
                                      energies = [ 1., 2., 3., 4. ],
                                      spacing_values = [ 10., 11., 12., 13. ],
                                      width_values = [ [ 0.11, 0.12, 0.13, 0.14 ],
                                                      [ 0.21, 0.22, 0.23, 0.24 ] ] )
    equal = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                                                    ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ],
                                      energies = [ 1., 2., 3., 4. ],
                                      spacing_values = [ 10., 11., 12., 13. ],
                                      width_values = [ [ 0.11, 0.12, 0.13, 0.14 ],
                                                        [ 0.21, 0.22, 0.23, 0.24 ] ] )
    different = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
                                          energies = [ 1., 2., 3., 4. ],
                                          spacing_values = [ 10., 11., 12., 13. ],
                                          width_values = [ [ 0.11, 0.12, 0.13, 0.14 ] ] )

    self.assertEqual(left, left)
    self.assertEqual(left, equal)
    self.assertNotEqual(left, different)


    self.assertEqual( True, ( left == left ) )
    self.assertEqual( True, ( left == equal ) )
    self.assertEqual( False, ( left == different ) )

    self.assertEqual( False, ( left != left ) )
    self.assertEqual( False, ( left != equal ) )
    self.assertEqual( True, ( left != different ) )

  def test_failures( self ) :
  
    # the number of channels and rows of width values is inconsistent
    with self.assertRaises( Exception ) :
            
        table = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
                                          energies = [ 1., 2., 3., 4. ],
                                          spacing_values = [ 10., 11., 12., 13. ],
                                          width_values = [ [ 0.11, 0.12, 0.13, 0.14 ],
                                                            [ 0.21, 0.22, 0.23, 0.24 ] ] )

    # the number of energies and number of width values per channel is inconsistent
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                                                        ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ],
                                          energies = [ 1., 2., 3. ],
                                          spacing_values = [ 10., 11., 12. ],
                                          width_values = [ [ 0.11, 0.12, 0.13, 0.14 ],
                                                            [ 0.21, 0.22, 0.23, 0.24 ] ] )

    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                                                        ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ],
                                          energies = [ 1., 2., 3., 4. ],
                                          spacing_values = [ 10., 11., 12., 13. ],
                                          width_values = [ [ 0.11, 0.12, 0.13 ],
                                                            [ 0.21, 0.22, 0.23, 0.24 ] ] )

    # the number of energies and number of spacing values is inconsistent
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                                                        ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ],
                                          energies = [ 1., 2., 3., 4. ],
                                          spacing_values = [ 10., 11., 12. ],
                                          width_values = [ [ 0.11, 0.12, 0.13, 0.14 ],
                                                            [ 0.21, 0.22, 0.23, 0.24 ] ] )

    # the number of channels or energies is zero
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                                                        ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ],
                                          energies = [],
                                          spacing_values = [],
                                          width_values = [ [ 0.11, 0.12, 0.13, 0.14 ],
                                                            [ 0.21, 0.22, 0.23, 0.24 ] ] )

    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable( channels = [],
                                          energies = [ 1., 2., 3., 4. ],
                                          spacing_values = [ 10., 11., 12., 13. ],
                                          width_values = [ [ 0.11, 0.12, 0.13, 0.14 ],
                                                            [ 0.21, 0.22, 0.23, 0.24 ] ] )

    # a channel that is not in the table is requested
    table = UnresolvedResonanceTable( channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
                                      energies = [ 1., 2., 3., 4. ],
                                      spacing_values = [ 10., 11., 12., 13. ],
                                      width_values = [ [ 0.11, 0.12, 0.13, 0.14 ] ] )

    with self.assertRaises( Exception ) :

        index = table.channel_index( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) )

    with self.assertRaises( Exception ) :

        widths = table.widths_for_channel( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) )





if __name__ == '__main__':
  unittest.main()