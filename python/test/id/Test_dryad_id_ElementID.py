# standard imports
import unittest

# third party imports

# local imports
from dryad.id import ElementID

class Test_dryad_id_ElementID( unittest.TestCase ) :
    """Unit test for the ElementID class."""

    numbers = range( 0, 119 )
    symbols = [ '', 'H', 'He', 'Li', 'Be', 'B', 'C', 'N', 'O', 'F', 'Ne', 'Na',
                'Mg', 'Al', 'Si', 'P', 'S', 'Cl', 'Ar', 'K', 'Ca', 'Sc', 'Ti',
                'V', 'Cr', 'Mn', 'Fe', 'Co', 'Ni', 'Cu', 'Zn', 'Ga', 'Ge',
                'As', 'Se', 'Br', 'Kr', 'Rb', 'Sr', 'Y', 'Zr', 'Nb', 'Mo', 'Tc',
                'Ru', 'Rh', 'Pd', 'Ag', 'Cd', 'In', 'Sn', 'Sb', 'Te', 'I',
                'Xe', 'Cs', 'Ba', 'La', 'Ce', 'Pr', 'Nd', 'Pm', 'Sm', 'Eu',
                'Gd', 'Tb', 'Dy', 'Ho', 'Er', 'Tm', 'Yb', 'Lu', 'Hf', 'Ta',
                'W', 'Re', 'Os', 'Ir', 'Pt', 'Au', 'Hg', 'Tl', 'Pb', 'Bi',
                'Po', 'At', 'Rn', 'Fr', 'Ra', 'Ac', 'Th', 'Pa', 'U', 'Np',
                'Pu', 'Am', 'Cm', 'Bk', 'Cf', 'Es', 'Fm', 'Md', 'No', 'Lr',
                'Rf', 'Db', 'Sg', 'Bh', 'Hs', 'Mt', 'Ds', 'Rg', 'Cn', 'Nh',
                'Fl', 'Mc', 'Lv', 'Ts', 'Og' ]
    names = [ '', 'Hydrogen', 'Helium', 'Lithium', 'Beryllium', 'Boron',
              'Carbon', 'Nitrogen', 'Oxygen', 'Fluorine', 'Neon','Sodium',
              'Magnesium', 'Aluminium', 'Silicon', 'Phosphorus', 'Sulfur',
              'Chlorine', 'Argon', 'Potassium', 'Calcium', 'Scandium',
              'Titanium', 'Vanadium', 'Chromium', 'Manganese', 'Iron', 'Cobalt',
              'Nickel', 'Copper', 'Zinc', 'Gallium', 'Germanium', 'Arsenic',
              'Selenium', 'Bromine', 'Krypton', 'Rubidium', 'Strontium',
              'Yttrium', 'Zirconium', 'Niobium', 'Molybdenum', 'Technetium',
              'Ruthenium', 'Rhodium', 'Palladium', 'Silver', 'Cadmium',
              'Indium', 'Tin', 'Antimony', 'Tellurium', 'Iodine', 'Xenon',
              'Caesium', 'Barium', 'Lanthanum', 'Cerium', 'Praseodymium',
              'Neodymium', 'Promethium', 'Samarium', 'Europium', 'Gadolinium',
              'Terbium', 'Dysprosium', 'Holmium', 'Erbium', 'Thulium',
              'Ytterbium', 'Lutetium', 'Hafnium', 'Tantalum', 'Tungsten',
              'Rhenium', 'Osmium', 'Iridium', 'Platinum', 'Gold', 'Mercury',
              'Thallium', 'Lead', 'Bismuth', 'Polonium', 'Astatine', 'Radon',
              'Francium', 'Radium', 'Actinium', 'Thorium', 'Protactinium',
              'Uranium', 'Neptunium', 'Plutonium', 'Americium', 'Curium',
              'Berkelium', 'Californium', 'Einsteinium', 'Fermium',
              'Mendelevium', 'Nobelium', 'Lawrencium', 'Rutherfordium',
              'Dubnium', 'Seaborgium', 'Bohrium', 'Hassium', 'Meitnerium',
              'Darmstadtium', 'Roentgenium', 'Copernicium', 'Nihonium',
              'Flerovium', 'Moscovium', 'Livermorium', 'Tennessine',
              'Oganesson' ]

    alternatives = { 'Aluminum' : 13, 'Cesium' : 55 }

    def test_values( self ) :

        for z in self.numbers :

            id = ElementID( z )
            self.assertEqual( id.number, z )
            self.assertEqual( id.symbol, self.symbols[z] )
            self.assertEqual( id.name, self.names[z] )

            id = ElementID( self.symbols[z] )
            self.assertEqual( id.number, z )
            self.assertEqual( id.symbol, self.symbols[z] )
            self.assertEqual( id.name, self.names[z] )

            id = ElementID( self.names[z] )
            self.assertEqual( id.number, z )
            self.assertEqual( id.symbol, self.symbols[z] )
            self.assertEqual( id.name, self.names[z] )

        for alternative, z in self.alternatives.items() :

            id = ElementID( alternative )
            self.assertEqual( id.number, z )
            self.assertEqual( id.symbol, self.symbols[z] )
            self.assertEqual( id.name, self.names[z] )

    def test_comparison( self ) :

        id1 = ElementID( 1 )
        id2 = ElementID( 2 )

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

        id1 = ElementID( 1 )
        id2 = ElementID( 2 )

        map = { id1 : '1', id2 : '2' }

        self.assertEqual( map[ id1 ], '1' )
        self.assertEqual( map[ id2 ], '2' )
        self.assertEqual( map[ ElementID( 1 ) ], '1' )
        self.assertEqual( map[ ElementID( 2 ) ], '2' )

    def test_failures( self ) :

        # illegal values
        with self.assertRaises( IndexError ) : id = ElementID( 119 )
        with self.assertRaises( IndexError ) : id = ElementID( -1 )
        with self.assertRaises( IndexError ) : id = ElementID( 'unknown' )

if __name__ == '__main__' :

    unittest.main()
