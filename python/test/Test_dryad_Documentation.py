# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import Documentation

def verify_chunk( self, chunk ) :

    description = str(
      '  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n'
      ' NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n'
      '---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n'
      '----- ATOMIC RELAXATION DATA                                      \n'
      '------ ENDF-6                                                     \n'
      '==================================================================\n'
      'The Livermore Evaluated Atomic Data Library (EADL) in the         \n'
      'ENDF-6 Format. Translated from the Livermore ENDL format          \n'
      'to the ENDF-6 Format.                                             \n'
      '==================================================================\n' )

    self.assertAlmostEqual( 15.8619530, chunk.awr )
    self.assertEqual( 0, chunk.library )
    self.assertEqual( 8, chunk.version[0] )
    self.assertEqual( 1, chunk.version[1] )
    self.assertEqual( description, chunk.description )

class Test_dryad_Documentation( unittest.TestCase ) :
    """Unit test for the Documentation class."""

    def test_component( self ) :

        chunk = Documentation( awr = 15.8619530,
                               library = 0,
                               version = [ 8, 1 ],
                               description = str(
                                 '  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n'
                                 ' NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n'
                                 '---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n'
                                 '----- ATOMIC RELAXATION DATA                                      \n'
                                 '------ ENDF-6                                                     \n'
                                 '==================================================================\n'
                                 'The Livermore Evaluated Atomic Data Library (EADL) in the         \n'
                                 'ENDF-6 Format. Translated from the Livermore ENDL format          \n'
                                 'to the ENDF-6 Format.                                             \n'
                                 '==================================================================\n' ) )

        verify_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = Documentation( awr = 15.8619530,
                               library = 0,
                               version = [ 8, 1 ],
                               description = str(
                                 '  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n'
                                 ' NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n'
                                 '---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n'
                                 '----- ATOMIC RELAXATION DATA                                      \n'
                                 '------ ENDF-6                                                     \n'
                                 '==================================================================\n'
                                 'The Livermore Evaluated Atomic Data Library (EADL) in the         \n'
                                 'ENDF-6 Format. Translated from the Livermore ENDL format          \n'
                                 'to the ENDF-6 Format.                                             \n'
                                 '==================================================================\n' ) )

        # the awr can be changed
        newawr = 25.
        original = 15.8619530

        chunk.awr = newawr

        self.assertEqual( newawr, chunk.awr )

        chunk.awr = original

        verify_chunk( self, chunk )

        # the library can be changed
        newlibrary = 1
        original = 0

        chunk.library = newlibrary

        self.assertEqual( newlibrary, chunk.library )

        chunk.library = original

        verify_chunk( self, chunk )

        # the version can be changed
        newversion = None
        original = [ 8, 1 ]

        chunk.version = newversion

        self.assertEqual( newversion, chunk.version )

        chunk.version = original

        verify_chunk( self, chunk )

        # the description can be changed
        newdescription = 'Something different                                               \n'
        original = str( '  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n'
                        ' NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n'
                        '---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n'
                        '----- ATOMIC RELAXATION DATA                                      \n'
                        '------ ENDF-6                                                     \n'
                        '==================================================================\n'
                        'The Livermore Evaluated Atomic Data Library (EADL) in the         \n'
                        'ENDF-6 Format. Translated from the Livermore ENDL format          \n'
                        'to the ENDF-6 Format.                                             \n'
                        '==================================================================\n' )

        chunk.description = newdescription

        self.assertEqual( newdescription, chunk.description )

        chunk.description = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = Documentation( awr = 15.8619530,
                              library = 0,
                              version = [ 8, 1 ],
                              description = str(
                                '  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n'
                                ' NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n'
                                '---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n'
                                '----- ATOMIC RELAXATION DATA                                      \n'
                                '------ ENDF-6                                                     \n'
                                '==================================================================\n'
                                'The Livermore Evaluated Atomic Data Library (EADL) in the         \n'
                                'ENDF-6 Format. Translated from the Livermore ENDL format          \n'
                                'to the ENDF-6 Format.                                             \n'
                                '==================================================================\n' ) )
        equal = Documentation( awr = 15.8619530,
                               library = 0,
                               version = [ 8, 1 ],
                               description = str(
                                 '  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n'
                                 ' NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n'
                                 '---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n'
                                 '----- ATOMIC RELAXATION DATA                                      \n'
                                 '------ ENDF-6                                                     \n'
                                 '==================================================================\n'
                                 'The Livermore Evaluated Atomic Data Library (EADL) in the         \n'
                                 'ENDF-6 Format. Translated from the Livermore ENDL format          \n'
                                 'to the ENDF-6 Format.                                             \n'
                                 '==================================================================\n' ) )
        different = Documentation( awr = 15.8619530,
                                   library = 0,
                                   version = [ 8, 1 ],
                                   description = str(
                                     'this is different                                                 \n' ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
