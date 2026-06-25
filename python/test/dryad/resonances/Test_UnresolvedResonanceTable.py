import unittest
import sys
from copy import copy


from njoy.dryad.resonances import UnresolvedResonanceTable, TabulatedAverageWidths, TabulatedLevelSpacing
from njoy.dryad.id import ChannelID

class Test_UnresolvedResonanceTable( unittest.TestCase ):
  """Unit test for the UnresolvedResonanceTable class."""

  def test_component( self ):

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
                      table.channel_widths( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ).values )
    self.assertEqual( [ 0.21, 0.22, 0.23, 0.24 ],
                      table.channel_widths( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ).values )

  def test_sorting( self ):

    energies = [ 1., 2., 3., 4. ]
    unsorted_channels = [ ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ),
                          ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ]
    unsorted_widths = [ TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ),
                        TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ) ]
    spacings = TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] )

    table = UnresolvedResonanceTable( unsorted_channels, unsorted_widths, spacings )

    self.assertEqual( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ), table.channels[0] )
    self.assertEqual( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ), table.channels[1] )

    # the widths follow the channel permutation
    self.assertEqual( [ 0.11, 0.12, 0.13, 0.14 ], table.widths[0].values )
    self.assertEqual( [ 0.21, 0.22, 0.23, 0.24 ], table.widths[1].values )

  def test_degrees_of_freedom( self ):

    energies = [ 1., 2., 3., 4. ]
    channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                 ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ]

    # both channels carry degrees of freedom
    widths_with_dof = [ TabulatedAverageWidths( 1, energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
                        TabulatedAverageWidths( 2, energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ]
    dof_table = UnresolvedResonanceTable( channels, widths_with_dof,
                                          TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] ) )

    self.assertEqual( TabulatedAverageWidths( 1, energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
                      dof_table.widths[0] )
    self.assertEqual( TabulatedAverageWidths( 2, energies, [ 0.21, 0.22, 0.23, 0.24 ] ),
                      dof_table.widths[1] )

    # one channel carries a degree of freedom, the other does not
    mixed_widths = [ TabulatedAverageWidths( 1, energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
                     TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ]
    mixed_table = UnresolvedResonanceTable( channels, mixed_widths,
                                            TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] ) )

    self.assertEqual( TabulatedAverageWidths( 1, energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
                      mixed_table.widths[0] )
    self.assertEqual( TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ),
                      mixed_table.widths[1] )

  def test_equality( self ):

    energies = [ 1., 2., 3., 4. ]
    channels = [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
                 ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ]
    widths = [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
               TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ]
    spacings = TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] )

    left = UnresolvedResonanceTable( channels, widths, spacings )
    equal = UnresolvedResonanceTable( channels, widths, spacings )
    different = UnresolvedResonanceTable(
        [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
        [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ) ],
        TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] ) )

    self.assertEqual( left, left )
    self.assertEqual( left, equal )
    self.assertNotEqual( left, different )

    self.assertEqual( True, ( left == left ) )
    self.assertEqual( True, ( left == equal ) )
    self.assertEqual( False, ( left == different ) )

    self.assertEqual( False, ( left != left ) )
    self.assertEqual( False, ( left != equal ) )
    self.assertEqual( True, ( left != different ) )

  def test_failures( self ) :

    energies = [ 1., 2., 3., 4. ]
    spacings = TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] )

    # the number of channels and the number of average widths is inconsistent
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable(
            [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
            [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
              TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ],
            spacings )

    # the number of channels is zero
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable( [], [], spacings )

    # two channels share the same identifier
    with self.assertRaises( Exception ) :

        table = UnresolvedResonanceTable(
            [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ),
              ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
            [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ),
              TabulatedAverageWidths( energies, [ 0.21, 0.22, 0.23, 0.24 ] ) ],
            spacings )

    # a channel that is not in the table is requested
    table = UnresolvedResonanceTable(
        [ ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ],
        [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] ) ],
        spacings )

    with self.assertRaises( Exception ) :

        widths = table.channel_widths( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) )

  def test_spin_group( self ) :

    energies = [ 1., 2., 3., 4. ]
    spacings = TabulatedLevelSpacing( energies, [ 10., 11., 12., 13. ] )

    def widths( n ) :
        return [ TabulatedAverageWidths( energies, [ 0.11, 0.12, 0.13, 0.14 ] )
                 for _ in range( n ) ]

    # channels sharing the same (L, J, parity) may be combined, regardless of
    # channel spin s
    table = UnresolvedResonanceTable(
        [ ChannelID( 'n,U235->n,U235{1,1/2,1/2-}' ),
          ChannelID( 'n,U235->n,U235_e1{1,3/2,1/2-}' ),
          ChannelID( 'n,U235->n,U235_e1{1,1/2,1/2-}' ) ],
        widths( 3 ),
        spacings )

    self.assertEqual( 3, table.number_channels )


if __name__ == '__main__':
  unittest.main()
