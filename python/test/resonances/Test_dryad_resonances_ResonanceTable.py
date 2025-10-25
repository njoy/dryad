# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.resonances import ResonanceTable
from dryad.id import ChannelID

class Test_dryad_resonances_ResonanceTable( unittest.TestCase ) :
    """Unit test for the ResonanceTable class."""

    def test_component( self ) :

        table = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                             ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ],
                                energies = [ 1., 2., 3., 4. ],
                                amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )

        self.assertEqual( 2, table.number_channels )
        self.assertEqual( 4, table.number_resonances )

        self.assertEqual( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ), table.channels[0] )
        self.assertEqual( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ), table.channels[1] )

        self.assertEqual( True, table.has_channel( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ) ) )
        self.assertEqual( True, table.has_channel( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ) ) )
        self.assertEqual( False, table.has_channel( ChannelID( 'n,U235->n,U235_e1{1,1/2,1/2+}' ) ) )

        self.assertEqual( True, table.has_energy( 1. ) )
        self.assertEqual( True, table.has_energy( 2. ) )
        self.assertEqual( True, table.has_energy( 3. ) )
        self.assertEqual( True, table.has_energy( 4. ) )
        self.assertEqual( False, table.has_energy( 5. ) )

        self.assertAlmostEqual( 1., table.energies[0] )
        self.assertAlmostEqual( 2., table.energies[1] )
        self.assertAlmostEqual( 3., table.energies[2] )
        self.assertAlmostEqual( 4., table.energies[3] )

        self.assertAlmostEqual( 11., table.reduced_width_amplitudes[0][0] )
        self.assertAlmostEqual( 12., table.reduced_width_amplitudes[0][1] )
        self.assertAlmostEqual( 13., table.reduced_width_amplitudes[0][2] )
        self.assertAlmostEqual( 14., table.reduced_width_amplitudes[0][3] )
        self.assertAlmostEqual( 21., table.reduced_width_amplitudes[1][0] )
        self.assertAlmostEqual( 22., table.reduced_width_amplitudes[1][1] )
        self.assertAlmostEqual( 23., table.reduced_width_amplitudes[1][2] )
        self.assertAlmostEqual( 24., table.reduced_width_amplitudes[1][3] )

        table = ResonanceTable( channel = ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                energies = [ 1., 2., 3., 4. ],
                                amplitudes = [ 11., 12., 13., 14. ] )

        self.assertEqual( 1, table.number_channels )
        self.assertEqual( 4, table.number_resonances )

        self.assertEqual( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ), table.channels[0] )

        self.assertAlmostEqual( 1., table.energies[0] )
        self.assertAlmostEqual( 2., table.energies[1] )
        self.assertAlmostEqual( 3., table.energies[2] )
        self.assertAlmostEqual( 4., table.energies[3] )

        self.assertAlmostEqual( 11., table.reduced_width_amplitudes[0][0] )
        self.assertAlmostEqual( 12., table.reduced_width_amplitudes[0][1] )
        self.assertAlmostEqual( 13., table.reduced_width_amplitudes[0][2] )
        self.assertAlmostEqual( 14., table.reduced_width_amplitudes[0][3] )

    def test_merge( self ) :

        left = ResonanceTable( channel = ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                               energies = [ 1., 2., 4. ],
                                amplitudes = [ 11., 12., 14. ] )
        right = ResonanceTable( channel = ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ),
                                energies = [ 2., 3., 5. ],
                                amplitudes = [ 22., 23., 25. ] )

        table = ResonanceTable( left )
        table += right

        self.assertEqual( 2, table.number_channels )
        self.assertEqual( 5, table.number_resonances )

        self.assertEqual( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ), table.channels[0] )
        self.assertEqual( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ), table.channels[1] )

        self.assertAlmostEqual( 1., table.energies[0] )
        self.assertAlmostEqual( 2., table.energies[1] )
        self.assertAlmostEqual( 3., table.energies[2] )
        self.assertAlmostEqual( 4., table.energies[3] )
        self.assertAlmostEqual( 5., table.energies[4] )

        self.assertAlmostEqual( 11., table.reduced_width_amplitudes[0][0] )
        self.assertAlmostEqual( 12., table.reduced_width_amplitudes[0][1] )
        self.assertAlmostEqual(  0., table.reduced_width_amplitudes[0][2] )
        self.assertAlmostEqual( 14., table.reduced_width_amplitudes[0][3] )
        self.assertAlmostEqual(  0., table.reduced_width_amplitudes[0][4] )
        self.assertAlmostEqual(  0., table.reduced_width_amplitudes[1][0] )
        self.assertAlmostEqual( 22., table.reduced_width_amplitudes[1][1] )
        self.assertAlmostEqual( 23., table.reduced_width_amplitudes[1][2] )
        self.assertAlmostEqual(  0., table.reduced_width_amplitudes[1][3] )
        self.assertAlmostEqual( 25., table.reduced_width_amplitudes[1][4] )

        table = left + right

        self.assertEqual( 2, table.number_channels )
        self.assertEqual( 5, table.number_resonances )

        self.assertEqual( ChannelID( 'n,U235->n,U235{0,1/2,1/2+}' ), table.channels[0] )
        self.assertEqual( ChannelID( 'n,U235->n,U235_e1{0,1/2,1/2+}' ), table.channels[1] )

        self.assertAlmostEqual( 1., table.energies[0] )
        self.assertAlmostEqual( 2., table.energies[1] )
        self.assertAlmostEqual( 3., table.energies[2] )
        self.assertAlmostEqual( 4., table.energies[3] )
        self.assertAlmostEqual( 5., table.energies[4] )

        self.assertAlmostEqual( 11., table.reduced_width_amplitudes[0][0] )
        self.assertAlmostEqual( 12., table.reduced_width_amplitudes[0][1] )
        self.assertAlmostEqual(  0., table.reduced_width_amplitudes[0][2] )
        self.assertAlmostEqual( 14., table.reduced_width_amplitudes[0][3] )
        self.assertAlmostEqual(  0., table.reduced_width_amplitudes[0][4] )
        self.assertAlmostEqual(  0., table.reduced_width_amplitudes[1][0] )
        self.assertAlmostEqual( 22., table.reduced_width_amplitudes[1][1] )
        self.assertAlmostEqual( 23., table.reduced_width_amplitudes[1][2] )
        self.assertAlmostEqual(  0., table.reduced_width_amplitudes[1][3] )
        self.assertAlmostEqual( 25., table.reduced_width_amplitudes[1][4] )

    def test_comparison( self ) :

        left = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                            ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ],
                               energies = [ 1., 2., 3., 4. ],
                               amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )
        equal = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                             ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ],
                                energies = [ 1., 2., 3., 4. ],
                                amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )
        different = ResonanceTable( channel = ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                    energies = [ 1., 2., 3., 4. ],
                                    amplitudes = [ 11., 12., 13., 14. ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # the number of channels and column is inconsistent
        with self.assertRaises( Exception ) :

            table = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ],
                                    energies = [ 1., 2., 3., 4. ],
                                    amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )

        # the energies are not sorted orunique
        with self.assertRaises( Exception ) :

            table = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                 ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ],
                                    energies = [ 1., 3., 2., 4. ],
                                    amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )

        with self.assertRaises( Exception ) :

            table = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                 ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ],
                                    energies = [ 1., 2., 2., 4. ],
                                    amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )

        # the number of energies and number of amplitudes is inconsistent
        with self.assertRaises( Exception ) :

            table = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                 ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ],
                                    energies = [ 1., 2., 3. ],
                                    amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )

        with self.assertRaises( Exception ) :

            table = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                 ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ],
                                    energies = [ 1., 2., 3., 4. ],
                                    amplitudes = [ [ 11., 12., 13. ], [ 21., 22., 23., 24. ] ] )

        # the number of channels or resonances is zero
        with self.assertRaises( Exception ) :

            table = ResonanceTable( channels = [ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                 ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ],
                                    energies = [],
                                    amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )

        with self.assertRaises( Exception ) :

            table = ResonanceTable( channels = [],
                                    energies = [ 1., 2., 3., 4. ],
                                    amplitudes = [ [ 11., 12., 13., 14. ], [ 21., 22., 23., 24. ] ] )

if __name__ == '__main__' :

    unittest.main()
