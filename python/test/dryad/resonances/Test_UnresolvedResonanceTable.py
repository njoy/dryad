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

  def test_component_from_tabulated( self ):

    energies = [ 1., 2., 3., 4. ]
    channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                 ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ]
    widths = [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
               TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ]
    spacings = TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] )

    table = UnresolvedResonanceTable( channels, widths, spacings )

    self.assertEqual( 2, table.number_channels )
    self.assertEqual( channels[0], table.channels[0] )
    self.assertEqual( channels[1], table.channels[1] )

    self.assertEqual( energies, table.spacings.energies )
    self.assertEqual( [ 10., 11., 12., 13. ], table.spacings.values )

    self.assertEqual( energies, table.widths[0].energies )
    self.assertEqual( energies, table.widths[1].energies )
    self.assertEqual( [ 0.11, 0.12, 0.13, 0.14 ], table.widths[0].values )
    self.assertEqual( [ 0.21, 0.22, 0.23, 0.24 ], table.widths[1].values )

    self.assertEqual( [ 0.11, 0.12, 0.13, 0.14 ],
                      table.widths_for_channel( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ).values )
    self.assertEqual( [ 0.21, 0.22, 0.23, 0.24 ],
                      table.widths_for_channel( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ).values )

    raw_table = UnresolvedResonanceTable( channels = channels,
                                          energies = energies,
                                          spacing_values = [ 10., 11., 12., 13. ],
                                          width_values = [ [ 0.11, 0.12, 0.13, 0.14 ],
                                                           [ 0.21, 0.22, 0.23, 0.24 ] ] )
    self.assertEqual( raw_table, table )

    unsorted_channels = [ ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ),
                          ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ]
    unsorted_widths = [ TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ),
                        TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ) ]
    spacings2 = TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] )
    sorted_table = UnresolvedResonanceTable( unsorted_channels, unsorted_widths, spacings2 )

    self.assertEqual( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ), sorted_table.channels[0] )
    self.assertEqual( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ), sorted_table.channels[1] )
    self.assertEqual( [ 0.11, 0.12, 0.13, 0.14 ], sorted_table.widths[0].values )
    self.assertEqual( [ 0.21, 0.22, 0.23, 0.24 ], sorted_table.widths[1].values )

    widths_with_dof = [ TabulatedAverageWidths( 1, energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
                        TabulatedAverageWidths( 2, energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ]
    spacings3 = TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] )
    dof_table = UnresolvedResonanceTable( channels, widths_with_dof, spacings3 )

    expected_widths0 = TabulatedAverageWidths( 1, energies, [ 0.11, 0.12, 0.13, 0.14 ] )
    expected_widths1 = TabulatedAverageWidths( 2, energies, [ 0.21, 0.22, 0.23, 0.24 ] )
    self.assertEqual( expected_widths0, dof_table.widths[0] )
    self.assertEqual( expected_widths1, dof_table.widths[1] )

  def test_grid_unification( self ):

    channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                 ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ]

    widths = [ TabulatedAverageWidths( 1, [ 1., 2., 3., 4. ], [ 1., 2., 3., 4. ] ),
               TabulatedAverageWidths( 1, [ 1., 2.5, 4. ], [ 1., 1., 1. ] ) ]
    spacings = TabulatedLevelSpacing( [ 1., 2., 3., 4. ], [ 10., 20., 30., 40. ] )

    table = UnresolvedResonanceTable( channels, widths, spacings )

    union_grid = [ 1., 2., 2.5, 3., 4. ]
    self.assertEqual( union_grid, table.spacings.energies )
    self.assertEqual( union_grid, table.widths[0].energies )
    self.assertEqual( union_grid, table.widths[1].energies )

    self.assertEqual( [ 10., 20., 25., 30., 40. ], table.spacings.values )
    self.assertEqual( [ 1., 2., 2.5, 3., 4. ], table.widths[0].values )
    self.assertEqual( [ 1., 1., 1., 1., 1. ], table.widths[1].values )

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

    # ---- Tabulated ctor failure cases ----

    energies = [ 1., 2., 3., 4. ]

    # channel count and widths count do not match
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable(
            [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
            [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
              TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ],
            TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] ) )

    # empty channels
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable(
            [],
            [],
            TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] ) )

    # two adjacent channels share the same identifier
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable(
            [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
              ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
            [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
              TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ],
            TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] ) )


if __name__ == '__main__':
  unittest.main()