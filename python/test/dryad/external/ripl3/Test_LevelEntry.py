# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.external.ripl3 import LevelEntry
from njoy.dryad.id import ParticleID

class Test_LevelEntry( unittest.TestCase ) :
    """Unit test for the LevelEntry class."""

    def test_component( self ) :

        # neutron
        neutron = LevelEntry( id = ParticleID.neutron(), energy = None,
                              spin = 0.5, parity = +1, half_life = None )

        self.assertEqual( ParticleID.neutron(), neutron.identifier )
        self.assertIsNone( neutron.energy )
        self.assertAlmostEqual( 0.5, neutron.spin )
        self.assertEqual( +1, neutron.parity )
        self.assertIsNone( neutron.half_life )

        # proton
        proton = LevelEntry( id = ParticleID.proton(), energy = None,
                             spin = 0.5, parity = +1, half_life = None )

        self.assertEqual( ParticleID.proton(), proton.identifier )
        self.assertIsNone( proton.energy )
        self.assertAlmostEqual( 0.5, proton.spin )
        self.assertEqual( +1, proton.parity )
        self.assertIsNone( proton.half_life )

        # U235 ground state
        u235 = LevelEntry( id = ParticleID( 'U235' ), energy = 0.0,
                           spin = 3.5, parity = -1, half_life = 2.221e16 )

        self.assertEqual( ParticleID( 'U235' ), u235.identifier )
        self.assertEqual( 0.0, u235.energy )
        self.assertAlmostEqual( 3.5, u235.spin )
        self.assertEqual( -1, u235.parity )
        self.assertIsNotNone( u235.half_life )
        self.assertAlmostEqual( 2.221e16, u235.half_life )

        # U235 first excited state
        u235_e1 = LevelEntry( id = ParticleID( 'U235_e1' ), energy = 76.0,
                              spin = 0.5, parity = +1, half_life = 1560.0 )

        self.assertEqual( ParticleID( 'U235_e1' ), u235_e1.identifier )
        self.assertIsNotNone( u235_e1.energy )
        self.assertAlmostEqual( 76.0, u235_e1.energy )
        self.assertAlmostEqual( 0.5, u235_e1.spin )
        self.assertEqual( +1, u235_e1.parity )
        self.assertIsNotNone( u235_e1.half_life )
        self.assertAlmostEqual( 1560.0, u235_e1.half_life )

    def test_setter_functions( self ) :

        chunk = LevelEntry( id = ParticleID( 'U235_e1' ), energy = 76.0,
                            spin = 0.5, parity = +1, half_life = 1560.0 )

        # the identifier can be changed
        newid = ParticleID( 'U235' )
        original = ParticleID( 'U235_e1' )

        chunk.identifier = newid

        self.assertEqual( newid, chunk.identifier )

        chunk.identifier = original

        self.assertEqual( original, chunk.identifier )

        # the energy can be changed
        newenergy = 1e+5
        original = 76.0

        chunk.energy = newenergy

        self.assertEqual( newenergy, chunk.energy )

        chunk.energy = original

        self.assertEqual( original, chunk.energy )

        # the spin can be changed
        newspin = 1.5
        original = 0.5

        chunk.spin = newspin

        self.assertAlmostEqual( newspin, chunk.spin )

        chunk.spin = original

        self.assertAlmostEqual( original, chunk.spin )

        # the parity can be changed
        newparity = -1
        original = +1

        chunk.parity = newparity

        self.assertEqual( newparity, chunk.parity )

        chunk.parity = original

        self.assertEqual( original, chunk.parity )

        # the half life can be changed
        newhalflife = 1e+10
        original = 1560.0

        chunk.half_life = newhalflife

        self.assertEqual( newhalflife, chunk.half_life )

        chunk.half_life = original

        self.assertEqual( original, chunk.half_life )

    def test_comparison( self ) :

        left = LevelEntry( id = ParticleID.neutron(), energy = None,
                           spin = 0.5, parity = +1, half_life = None )
        equal = LevelEntry( id = ParticleID.neutron(), energy = None,
                            spin = 0.5, parity = +1, half_life = None )
        different = LevelEntry( id = ParticleID( 'U235_e1' ), energy = 76.0,
                                spin = 0.5, parity = +1, half_life = 1560.0 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
