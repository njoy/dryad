# standard imports
import unittest
import os
import sys

# third party imports

# local imports
from njoy.dryad.external.ripl3 import Levels
from njoy.dryad.id import ParticleID

class Test_Levels( unittest.TestCase ) :
    """Unit test for the Levels class."""

    def test_predefined_particles( self ) :

        # photon
        photon = Levels.entry( ParticleID.photon() )

        self.assertEqual( ParticleID.photon(), photon.identifier )
        self.assertIsNone( photon.energy )
        self.assertAlmostEqual( 1.0, photon.spin )
        self.assertEqual( -1, photon.parity )
        self.assertIsNone( photon.half_life )

        # neutron
        neutron = Levels.entry( ParticleID.neutron() )

        self.assertEqual( ParticleID.neutron(), neutron.identifier )
        self.assertIsNone( neutron.energy )
        self.assertAlmostEqual( 0.5, neutron.spin )
        self.assertEqual( 1, neutron.parity )
        self.assertIsNone( neutron.half_life )

        # proton
        proton = Levels.entry( ParticleID.proton() )

        self.assertEqual( ParticleID.proton(), proton.identifier )
        self.assertIsNone( proton.energy )
        self.assertAlmostEqual( 0.5, proton.spin )
        self.assertEqual( 1, proton.parity )
        self.assertIsNone( proton.half_life )

        # deuteron
        deuteron = Levels.entry( ParticleID.deuteron() )

        self.assertEqual( ParticleID.deuteron(), deuteron.identifier )
        self.assertIsNone( deuteron.energy )
        self.assertAlmostEqual( 1.0, deuteron.spin )
        self.assertEqual( 1, deuteron.parity )
        self.assertIsNone( deuteron.half_life )

        # triton
        triton = Levels.entry( ParticleID.triton() )

        self.assertEqual( ParticleID.triton(), triton.identifier )
        self.assertIsNone( triton.energy )
        self.assertAlmostEqual( 0.5, triton.spin )
        self.assertEqual( 1, triton.parity )
        self.assertIsNone( triton.half_life )

        # helion
        helion = Levels.entry( ParticleID.helion() )

        self.assertEqual( ParticleID.helion(), helion.identifier )
        self.assertIsNone( helion.energy )
        self.assertAlmostEqual( 0.5, helion.spin )
        self.assertEqual( 1, helion.parity )
        self.assertIsNone( helion.half_life )

        # alpha
        alpha = Levels.entry( ParticleID.alpha() )

        self.assertEqual( ParticleID.alpha(), alpha.identifier )
        self.assertIsNone( alpha.energy )
        self.assertAlmostEqual( 0.0, alpha.spin )
        self.assertEqual( 1, alpha.parity )
        self.assertIsNone( alpha.half_life )

        data = Levels.entry( ParticleID( 'H1' ) )
        self.assertEqual( ParticleID( 'H1' ), data.identifier )
        self.assertAlmostEqual( 0., data.energy )
        self.assertAlmostEqual( 0.5, data.spin )
        self.assertEqual( 1, data.parity )
        self.assertIsNone( data.half_life )

        self.assertEqual(     29, Levels.size() )

        data = Levels.entry( ParticleID( 'He4' ) )
        self.assertEqual( ParticleID( 'He4' ), data.identifier )
        self.assertAlmostEqual( 0., data.energy )
        self.assertAlmostEqual( 0., data.spin )
        self.assertEqual( 1, data.parity )
        self.assertIsNone( data.half_life )

        self.assertEqual(     72, Levels.size() )

        data = Levels.entry( ParticleID( 'Li6' ) )
        self.assertEqual( ParticleID( 'Li6' ), data.identifier )
        self.assertAlmostEqual( 0., data.energy )
        self.assertAlmostEqual( 1., data.spin )
        self.assertEqual( 1, data.parity )
        self.assertIsNone( data.half_life )

        self.assertEqual(    146, Levels.size() )

        data = Levels.entry( ParticleID( 'Be9' ) )
        self.assertEqual( ParticleID( 'Be9' ), data.identifier )
        self.assertAlmostEqual( 0., data.energy )
        self.assertAlmostEqual( 1.5, data.spin )
        self.assertEqual( -1, data.parity )
        self.assertIsNone( data.half_life )

        self.assertEqual(    331, Levels.size() )

        data = Levels.entry( ParticleID( 'B10' ) )
        self.assertEqual( ParticleID( 'B10' ), data.identifier )
        self.assertAlmostEqual( 0., data.energy )
        self.assertAlmostEqual( 3., data.spin )
        self.assertEqual( 1, data.parity )
        self.assertIsNone( data.half_life )

        self.assertEqual(    545, Levels.size() )

        data = Levels.entry( ParticleID( 'C12' ) )
        self.assertEqual( ParticleID( 'C12' ), data.identifier )
        self.assertAlmostEqual( 0., data.energy )
        self.assertAlmostEqual( 0., data.spin )
        self.assertEqual( 1, data.parity )
        self.assertIsNone( data.half_life )

        self.assertEqual(    850, Levels.size() )

        data = Levels.entry( ParticleID( 'N14' ) )
        self.assertEqual( ParticleID( 'N14' ), data.identifier )
        self.assertAlmostEqual( 0., data.energy )
        self.assertAlmostEqual( 1., data.spin )
        self.assertEqual( 1, data.parity )
        self.assertIsNone( data.half_life )

        self.assertEqual(   1326, Levels.size() )

        data = Levels.entry( ParticleID( 'O16' ) )
        self.assertEqual( ParticleID( 'O16' ), data.identifier )
        self.assertAlmostEqual( 0., data.energy )
        self.assertAlmostEqual( 0., data.spin )
        self.assertEqual( 1, data.parity )
        self.assertIsNone( data.half_life )

        self.assertEqual(   1941, Levels.size() )

        data = Levels.entry( ParticleID( 'F19' ) )
        self.assertEqual(   2602, Levels.size() )

        data = Levels.entry( ParticleID( 'Ne20' ) )
        self.assertEqual(   3364, Levels.size() )

        data = Levels.entry( ParticleID( 'Na23' ) )
        self.assertEqual(   4229, Levels.size() )

        data = Levels.entry( ParticleID( 'Mg24' ) )
        self.assertEqual(   5176, Levels.size() )

        data = Levels.entry( ParticleID( 'Al27' ) )
        self.assertEqual(   6041, Levels.size() )

        data = Levels.entry( ParticleID( 'Si28' ) )
        self.assertEqual(   7043, Levels.size() )

        data = Levels.entry( ParticleID( 'P31' ) )
        self.assertEqual(   8138, Levels.size() )

        data = Levels.entry( ParticleID( 'S32' ) )
        self.assertEqual(   9609, Levels.size() )

        data = Levels.entry( ParticleID( 'Cl35' ) )
        self.assertEqual(  11430, Levels.size() )

        data = Levels.entry( ParticleID( 'Ar36' ) )
        self.assertEqual(  13136, Levels.size() )

        data = Levels.entry( ParticleID( 'K39' ) )
        self.assertEqual(  14495, Levels.size() )

        data = Levels.entry( ParticleID( 'Ca40' ) )
        self.assertEqual(  17476, Levels.size() )

        data = Levels.entry( ParticleID( 'Sc45' ) )
        self.assertEqual(  19711, Levels.size() )

        data = Levels.entry( ParticleID( 'Ti46' ) )
        self.assertEqual(  21261, Levels.size() )

        data = Levels.entry( ParticleID( 'V50' ) )
        self.assertEqual(  22962, Levels.size() )

        data = Levels.entry( ParticleID( 'Cr50' ) )
        self.assertEqual(  24572, Levels.size() )

        data = Levels.entry( ParticleID( 'Mn55' ) )
        self.assertEqual(  26373, Levels.size() )

        data = Levels.entry( ParticleID( 'Fe54' ) )
        self.assertEqual(  28138, Levels.size() )

        data = Levels.entry( ParticleID( 'Co59' ) )
        self.assertEqual(  30208, Levels.size() )

        data = Levels.entry( ParticleID( 'Ni58' ) )
        self.assertEqual(  33080, Levels.size() )

        data = Levels.entry( ParticleID( 'Cu63' ) )
        self.assertEqual(  35578, Levels.size() )

        data = Levels.entry( ParticleID( 'Zn64' ) )
        self.assertEqual(  37376, Levels.size() )

        data = Levels.entry( ParticleID( 'Ga69' ) )
        self.assertEqual(  38720, Levels.size() )

        data = Levels.entry( ParticleID( 'Ge70' ) )
        self.assertEqual(  40751, Levels.size() )

        data = Levels.entry( ParticleID( 'As75' ) )
        self.assertEqual(  42108, Levels.size() )

        data = Levels.entry( ParticleID( 'Se74' ) )
        self.assertEqual(  43779, Levels.size() )

        data = Levels.entry( ParticleID( 'Br79' ) )
        self.assertEqual(  45321, Levels.size() )

        data = Levels.entry( ParticleID( 'Kr78' ) )
        self.assertEqual(  47369, Levels.size() )

        data = Levels.entry( ParticleID( 'Rb85' ) )
        self.assertEqual(  48958, Levels.size() )

        data = Levels.entry( ParticleID( 'Sr84' ) )
        self.assertEqual(  51252, Levels.size() )

        data = Levels.entry( ParticleID( 'Y89' ) )
        self.assertEqual(  53237, Levels.size() )

        data = Levels.entry( ParticleID( 'Zr90' ) )
        self.assertEqual(  55638, Levels.size() )

        data = Levels.entry( ParticleID( 'Nb93' ) )
        self.assertEqual(  57390, Levels.size() )

        data = Levels.entry( ParticleID( 'Mo92' ) )
        self.assertEqual(  60225, Levels.size() )

        data = Levels.entry( ParticleID( 'Tc99' ) )
        self.assertEqual(  61923, Levels.size() )

        data = Levels.entry( ParticleID( 'Ru96' ) )
        self.assertEqual(  64028, Levels.size() )

        data = Levels.entry( ParticleID( 'Rh103' ) )
        self.assertEqual(  65843, Levels.size() )

        data = Levels.entry( ParticleID( 'Pd102' ) )
        self.assertEqual(  68066, Levels.size() )

        data = Levels.entry( ParticleID( 'Ag107' ) )
        self.assertEqual(  69629, Levels.size() )

        data = Levels.entry( ParticleID( 'Cd106' ) )
        self.assertEqual(  72785, Levels.size() )

        data = Levels.entry( ParticleID( 'In113' ) )
        self.assertEqual(  74813, Levels.size() )

        data = Levels.entry( ParticleID( 'Sn112' ) )
        self.assertEqual(  78060, Levels.size() )

        data = Levels.entry( ParticleID( 'Sb121' ) )
        self.assertEqual(  80520, Levels.size() )

        data = Levels.entry( ParticleID( 'Te120' ) )
        self.assertEqual(  84538, Levels.size() )

        data = Levels.entry( ParticleID( 'I127' ) )
        self.assertEqual(  87108, Levels.size() )

        data = Levels.entry( ParticleID( 'Xe124' ) )
        self.assertEqual(  90505, Levels.size() )

        data = Levels.entry( ParticleID( 'Cs133' ) )
        self.assertEqual(  92217, Levels.size() )

        data = Levels.entry( ParticleID( 'Ba130' ) )
        self.assertEqual(  95343, Levels.size() )

        data = Levels.entry( ParticleID( 'La138' ) )
        self.assertEqual(  97715, Levels.size() )

        data = Levels.entry( ParticleID( 'Ce136' ) )
        self.assertEqual( 100235, Levels.size() )

        data = Levels.entry( ParticleID( 'Pr141' ) )
        self.assertEqual( 102039, Levels.size() )

        data = Levels.entry( ParticleID( 'Nd142' ) )
        self.assertEqual( 105887, Levels.size() )

        data = Levels.entry( ParticleID( 'Pm138' ) )
        self.assertEqual( 107555, Levels.size() )

        data = Levels.entry( ParticleID( 'Sm144' ) )
        self.assertEqual( 110768, Levels.size() )

        data = Levels.entry( ParticleID( 'Eu151' ) )
        self.assertEqual( 112957, Levels.size() )

        data = Levels.entry( ParticleID( 'Gd152' ) )
        self.assertEqual( 116885, Levels.size() )

        data = Levels.entry( ParticleID( 'Tb159' ) )
        self.assertEqual( 118884, Levels.size() )

        data = Levels.entry( ParticleID( 'Dy156' ) )
        self.assertEqual( 122679, Levels.size() )

        data = Levels.entry( ParticleID( 'Ho165' ) )
        self.assertEqual( 124989, Levels.size() )

        data = Levels.entry( ParticleID( 'Er162' ) )
        self.assertEqual( 128473, Levels.size() )

        data = Levels.entry( ParticleID( 'Tm169' ) )
        self.assertEqual( 130861, Levels.size() )

        data = Levels.entry( ParticleID( 'Yb168' ) )
        self.assertEqual( 133796, Levels.size() )

        data = Levels.entry( ParticleID( 'Lu175' ) )
        self.assertEqual( 135947, Levels.size() )

        data = Levels.entry( ParticleID( 'Hf174' ) )
        self.assertEqual( 139416, Levels.size() )

        data = Levels.entry( ParticleID( 'Ta180' ) )
        self.assertEqual( 141726, Levels.size() )

        data = Levels.entry( ParticleID( 'W180' ) )
        self.assertEqual( 144837, Levels.size() )

        data = Levels.entry( ParticleID( 'Re185' ) )
        self.assertEqual( 147171, Levels.size() )

        data = Levels.entry( ParticleID( 'Os184' ) )
        self.assertEqual( 150318, Levels.size() )

        data = Levels.entry( ParticleID( 'Ir191' ) )
        self.assertEqual( 152373, Levels.size() )

        data = Levels.entry( ParticleID( 'Pt190' ) )
        self.assertEqual( 154972, Levels.size() )

        data = Levels.entry( ParticleID( 'Au197' ) )
        self.assertEqual( 157048, Levels.size() )

        data = Levels.entry( ParticleID( 'Hg196' ) )
        self.assertEqual( 159418, Levels.size() )

        data = Levels.entry( ParticleID( 'Tl203' ) )
        self.assertEqual( 160916, Levels.size() )

        data = Levels.entry( ParticleID( 'Pb204' ) )
        self.assertEqual( 164602, Levels.size() )

        data = Levels.entry( ParticleID( 'Bi209' ) )
        self.assertEqual( 166142, Levels.size() )

        data = Levels.entry( ParticleID( 'Po210' ) )
        self.assertEqual( 167353, Levels.size() )

        data = Levels.entry( ParticleID( 'At210' ) )
        self.assertEqual( 168086, Levels.size() )

        data = Levels.entry( ParticleID( 'Rn222' ) )
        self.assertEqual( 168815, Levels.size() )

        data = Levels.entry( ParticleID( 'Fr223' ) )
        self.assertEqual( 169480, Levels.size() )

        data = Levels.entry( ParticleID( 'Ra226' ) )
        self.assertEqual( 170437, Levels.size() )

        data = Levels.entry( ParticleID( 'Ac227' ) )
        self.assertEqual( 170886, Levels.size() )

        data = Levels.entry( ParticleID( 'Th232' ) )
        self.assertEqual( 172261, Levels.size() )

        data = Levels.entry( ParticleID( 'Pa231' ) )
        self.assertEqual( 172693, Levels.size() )

        data = Levels.entry( ParticleID( 'U238' ) )
        self.assertEqual( 174093, Levels.size() )

        data = Levels.entry( ParticleID( 'Np237' ) )
        self.assertEqual( 174542, Levels.size() )

        data = Levels.entry( ParticleID( 'Pu238' ) )
        self.assertEqual( 175284, Levels.size() )

        data = Levels.entry( ParticleID( 'Am242' ) )
        self.assertEqual( 175803, Levels.size() )

        data = Levels.entry( ParticleID( 'Cm246' ) )
        self.assertEqual( 176256, Levels.size() )

        data = Levels.entry( ParticleID( 'Bk239' ) )
        self.assertEqual( 176462, Levels.size() )

        data = Levels.entry( ParticleID( 'Cf255' ) )
        self.assertEqual( 176764, Levels.size() )

        data = Levels.entry( ParticleID( 'Es244' ) )
        self.assertEqual( 176842, Levels.size() )

        data = Levels.entry( ParticleID( 'Fm248' ) )
        self.assertEqual( 176935, Levels.size() )

        data = Levels.entry( ParticleID( 'Md252' ) )
        self.assertEqual( 176991, Levels.size() )

        data = Levels.entry( ParticleID( 'No251' ) )
        self.assertEqual( 177101, Levels.size() )

        data = Levels.entry( ParticleID( 'Lr255' ) )
        self.assertEqual( 177156, Levels.size() )

        data = Levels.entry( ParticleID( 'Rf256' ) )
        self.assertEqual( 177208, Levels.size() )

        data = Levels.entry( ParticleID( 'Db258' ) )
        self.assertEqual( 177236, Levels.size() )

        data = Levels.entry( ParticleID( 'Sg261' ) )
        self.assertEqual( 177259, Levels.size() )

        data = Levels.entry( ParticleID( 'Bh272' ) )
        self.assertEqual( 177286, Levels.size() )

        data = Levels.entry( ParticleID( 'Hs266' ) )
        self.assertEqual( 177312, Levels.size() )

        data = Levels.entry( ParticleID( 'Mt276' ) )
        self.assertEqual( 177335, Levels.size() )

        data = Levels.entry( ParticleID( 'Ds279' ) )
        self.assertEqual( 177359, Levels.size() )

        data = Levels.entry( ParticleID( 'Rg275' ) )
        self.assertEqual( 177374, Levels.size() )

        data = Levels.entry( ParticleID( 'Cn280' ) )
        self.assertEqual( 177387, Levels.size() )

        data = Levels.entry( ParticleID( 'Nh285' ) )
        self.assertEqual( 177401, Levels.size() )

        data = Levels.entry( ParticleID( 'Fl290' ) )
        self.assertEqual( 177409, Levels.size() )

        data = Levels.entry( ParticleID( 'Mc290' ) )
        self.assertEqual( 177415, Levels.size() )

        data = Levels.entry( ParticleID( 'Lv290' ) )
        self.assertEqual( 177420, Levels.size() )

        data = Levels.entry( ParticleID( 'Ts292' ) )
        self.assertEqual( 177424, Levels.size() )

        data = Levels.entry( ParticleID( 'Og294' ) )
        self.assertEqual( 177427, Levels.size() )

if __name__ == '__main__' :

    unittest.main()
