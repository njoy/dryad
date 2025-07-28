// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createAtomicRelaxationEndfFile.hpp"

// other includes
#include <filesystem>
#include "ENDFtk/tree/Material.hpp"

// convenience typedefs
using namespace njoy::dryad;

std::string chunk();
std::string readContentFromFile( const std::string& );

SCENARIO( "createAtomicRelaxation" ) {

  GIVEN( "Atomic relaxation data" ) {

    std::string description =
      "  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n"
      " NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n"
      "---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n"
      "----- ATOMIC RELAXATION DATA                                      \n"
      "------ ENDF-6                                                     \n"
      "==================================================================\n"
      "The Livermore Evaluated Atomic Data Library (EADL) in the         \n"
      "ENDF-6 Format. Translated from the Livermore ENDL format          \n"
      "to the ENDF-6 Format.                                             \n"
      "==================================================================\n"
      "  Contents                                                        \n"
      "==================================================================\n"
      "  MF/MT    Description                                            \n"
      "==================================================================\n"
      "  28/533   Atomic Relaxation Data for Electrons and Photons       \n"
      "==================================================================\n"
      "  Warning                                                         \n"
      "==================================================================\n"
      "  MF/MT combinations used to define ALL electron interaction data \n"
      "  are newly defined MF/MT numbers for ENDF/B-VI that did not exist\n"
      "  in earlier versions of ENDF/B.                                  \n"
      "==================================================================\n"
      "  Definition of Data                                              \n"
      "==================================================================\n"
      "  Atomic Relaxation Data for Electrons and Photons                \n"
      "==================================================================\n"
      "1) An atom can be ionized by a photon or an electron interaction. \n"
      "2) The atomic relaxation data included here describes how a       \n"
      "   singly ionized atom returns to neutrality, by emitting photons \n"
      "   (x-rays) and/or electrons (Auger, Coster-Kronig).              \n"
      "3) Data is given to define the transition probabilities between   \n"
      "   subshells for radiative (x-ray emission) and non-radiative     \n"
      "   (Auger, Coster-Kronig) transitions.                            \n"
      "4) The complete spectrum of emitted photons and electrons can be  \n"
      "   calculated using the data included here, e.g., see ref. 2,     \n"
      "   below, for am example of a computer code that analytically     \n"
      "   calculates these spectra.                                      \n"
      "==================================================================\n"
      "  References                                                      \n"
      "==================================================================\n"
      "1) S.T. Perkins, D.E. Cullen, etal., \"Tables and Graphs of Atomic \n"
      "   Subshell and Relaxation Data Derived from the LLNL Evaluated   \n"
      "   Atomic Data Library (EADL), Z = 1 - 100\", UCRL-50400, Vol. 30, \n"
      "   Lawrence Livermore National Laboratory (1991).                 \n"
      "2) D.E. Cullen \"Program RELAX: A Code Designed to Calculate X-Ray \n"
      "   and Electron Emission Spectra as Singly Charged Atoms Relax    \n"
      "   Back to Neutrality\", UCRL-ID-110438, Lawrence Livermore        \n"
      "   National Laboratory (1992).                                    \n"
      "3) D.E. Cullen \"A Survey of Atomic Binding Energies for use       \n"
      "   in EPICS2017\" ,IAEA-NDS-224, (2017), Nuclear Data Section,     \n"
      "   IAEA, Vienna, Austria                                          \n"
      "4) D.E. Cullen,\"EPICS2017: April 2019 Status Report\",             \n"
      "   IAEA-NDS-228, April 2019, Nuclear Data Section,                \n"
      "   IAEA, Vienna, Austria.                                         \n"
      "5) D.E. Cullen,\"EPICS2023: August 2023 Status Report\",            \n"
      "   IAEA-NDS-242, August 2023, Nuclear Data Section,               \n"
      "   IAEA, Vienna, Austria.                                         \n"
      "                                                                  \n"
      "  These are the primary references to the contents of this library\n"
      "  and they contain a complete list of references to the sources   \n"
      "  of data used in this library, methods of evaluation, accuracy   \n"
      "  of the data, etc.                                               \n"
      "==================================================================\n"
      "  History                                                         \n"
      "==================================================================\n"
      " (1) November, 1991 - Initial release in the ENDL format.         \n"
      " (2) November, 2001 - Initial release in the ENDF-6 format.       \n"
      " (3) September,2014 - Insure Standard C, C++, FORTRAN Format      \n"
      " (4) September,2014 - Updated based on recently publshed data     \n"
      " (5) September,2017 - New Binding Energies (see: ref.3)           \n"
      "                      Same Transition Probabilities               \n"
      " (6) August,   2023 - Reformatted, but data same as 2017 version  \n"
      "==================================================================\n"
      " ***************** Program FIXUP (Version 2023-2) ****************\n"
      " **************** Program DICTIN (VERSION 2023-1) ****************\n";

    id::ElementID element( 8 );
    std::vector< atomic::ElectronSubshellConfiguration > subshells = {

      atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L3" ), 13.62, 2.67 ),
      atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L2" ), 13.62, 1.33 ),
      atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L1" ), 28.48, 2 ),
      atomic::ElectronSubshellConfiguration(

        id::ElectronSubshellID( "K" ), 538, 2,
        { atomic::RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
          atomic::RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
        { atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
          atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
          atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
          atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
          atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
          atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) },
        false
      )
    };

    AtomicRelaxation relaxation( element, subshells );
    relaxation.documentation().awr( 15.8619530 );
    relaxation.documentation().library( 0 );
    relaxation.documentation().version( std::make_pair( 8, 1 ) );
    relaxation.documentation().description( std::move( description ) );

    THEN( "it can be converted to an ENDF material" ) {

      std::string filename = "test.endf";
      format::endf::createAtomicRelaxationEndfFile( relaxation, filename );

      CHECK( chunk() == readContentFromFile( filename ) );

      std::remove( filename.c_str() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    "Atomic relaxation data for Oxygen                                    0 0  0     \n"
    " 8.000000+3 15.8619530         -1          0          0          0 800 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 800 1451     \n"
    " 0.000000+0 0.000000+0          1          0          6          8 800 1451     \n"
    " 0.000000+0 0.000000+0          0          0         75          2 800 1451     \n"
    "  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                        800 1451     \n"
    " NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830    800 1451     \n"
    "---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1             800 1451     \n"
    "----- ATOMIC RELAXATION DATA                                       800 1451     \n"
    "------ ENDF-6                                                      800 1451     \n"
    "================================================================== 800 1451     \n"
    "The Livermore Evaluated Atomic Data Library (EADL) in the          800 1451     \n"
    "ENDF-6 Format. Translated from the Livermore ENDL format           800 1451     \n"
    "to the ENDF-6 Format.                                              800 1451     \n"
    "================================================================== 800 1451     \n"
    "  Contents                                                         800 1451     \n"
    "================================================================== 800 1451     \n"
    "  MF/MT    Description                                             800 1451     \n"
    "================================================================== 800 1451     \n"
    "  28/533   Atomic Relaxation Data for Electrons and Photons        800 1451     \n"
    "================================================================== 800 1451     \n"
    "  Warning                                                          800 1451     \n"
    "================================================================== 800 1451     \n"
    "  MF/MT combinations used to define ALL electron interaction data  800 1451     \n"
    "  are newly defined MF/MT numbers for ENDF/B-VI that did not exist 800 1451     \n"
    "  in earlier versions of ENDF/B.                                   800 1451     \n"
    "================================================================== 800 1451     \n"
    "  Definition of Data                                               800 1451     \n"
    "================================================================== 800 1451     \n"
    "  Atomic Relaxation Data for Electrons and Photons                 800 1451     \n"
    "================================================================== 800 1451     \n"
    "1) An atom can be ionized by a photon or an electron interaction.  800 1451     \n"
    "2) The atomic relaxation data included here describes how a        800 1451     \n"
    "   singly ionized atom returns to neutrality, by emitting photons  800 1451     \n"
    "   (x-rays) and/or electrons (Auger, Coster-Kronig).               800 1451     \n"
    "3) Data is given to define the transition probabilities between    800 1451     \n"
    "   subshells for radiative (x-ray emission) and non-radiative      800 1451     \n"
    "   (Auger, Coster-Kronig) transitions.                             800 1451     \n"
    "4) The complete spectrum of emitted photons and electrons can be   800 1451     \n"
    "   calculated using the data included here, e.g., see ref. 2,      800 1451     \n"
    "   below, for am example of a computer code that analytically      800 1451     \n"
    "   calculates these spectra.                                       800 1451     \n"
    "================================================================== 800 1451     \n"
    "  References                                                       800 1451     \n"
    "================================================================== 800 1451     \n"
    "1) S.T. Perkins, D.E. Cullen, etal., \"Tables and Graphs of Atomic  800 1451     \n"
    "   Subshell and Relaxation Data Derived from the LLNL Evaluated    800 1451     \n"
    "   Atomic Data Library (EADL), Z = 1 - 100\", UCRL-50400, Vol. 30,  800 1451     \n"
    "   Lawrence Livermore National Laboratory (1991).                  800 1451     \n"
    "2) D.E. Cullen \"Program RELAX: A Code Designed to Calculate X-Ray  800 1451     \n"
    "   and Electron Emission Spectra as Singly Charged Atoms Relax     800 1451     \n"
    "   Back to Neutrality\", UCRL-ID-110438, Lawrence Livermore         800 1451     \n"
    "   National Laboratory (1992).                                     800 1451     \n"
    "3) D.E. Cullen \"A Survey of Atomic Binding Energies for use        800 1451     \n"
    "   in EPICS2017\" ,IAEA-NDS-224, (2017), Nuclear Data Section,      800 1451     \n"
    "   IAEA, Vienna, Austria                                           800 1451     \n"
    "4) D.E. Cullen,\"EPICS2017: April 2019 Status Report\",              800 1451     \n"
    "   IAEA-NDS-228, April 2019, Nuclear Data Section,                 800 1451     \n"
    "   IAEA, Vienna, Austria.                                          800 1451     \n"
    "5) D.E. Cullen,\"EPICS2023: August 2023 Status Report\",             800 1451     \n"
    "   IAEA-NDS-242, August 2023, Nuclear Data Section,                800 1451     \n"
    "   IAEA, Vienna, Austria.                                          800 1451     \n"
    "                                                                   800 1451     \n"
    "  These are the primary references to the contents of this library 800 1451     \n"
    "  and they contain a complete list of references to the sources    800 1451     \n"
    "  of data used in this library, methods of evaluation, accuracy    800 1451     \n"
    "  of the data, etc.                                                800 1451     \n"
    "================================================================== 800 1451     \n"
    "  History                                                          800 1451     \n"
    "================================================================== 800 1451     \n"
    " (1) November, 1991 - Initial release in the ENDL format.          800 1451     \n"
    " (2) November, 2001 - Initial release in the ENDF-6 format.        800 1451     \n"
    " (3) September,2014 - Insure Standard C, C++, FORTRAN Format       800 1451     \n"
    " (4) September,2014 - Updated based on recently publshed data      800 1451     \n"
    " (5) September,2017 - New Binding Energies (see: ref.3)            800 1451     \n"
    "                      Same Transition Probabilities                800 1451     \n"
    " (6) August,   2023 - Reformatted, but data same as 2017 version   800 1451     \n"
    "================================================================== 800 1451     \n"
    " ***************** Program FIXUP (Version 2023-2) **************** 800 1451     \n"
    " **************** Program DICTIN (VERSION 2023-1) **************** 800 1451     \n"
    "                                1        451         81          0 800 1451     \n"
    "                               28        533         17          0 800 1451     \n"
    "                                                                   800 1  0     \n"
    "                                                                   800 0  0     \n"
    " 8.000000+3 15.8619530          0          0          4          0 80028533     \n"
    " 1.000000+0 0.000000+0          0          0         54          8 80028533     \n"
    " 5.380000+2 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 80028533     \n"
    " 3.000000+0 0.000000+0 5.230900+2 1.907680-3 0.000000+0 0.000000+0 80028533     \n"
    " 4.000000+0 0.000000+0 5.231300+2 3.800270-3 0.000000+0 0.000000+0 80028533     \n"
    " 2.000000+0 2.000000+0 4.788200+2 1.786440-1 0.000000+0 0.000000+0 80028533     \n"
    " 2.000000+0 3.000000+0 4.938600+2 1.162240-1 0.000000+0 0.000000+0 80028533     \n"
    " 2.000000+0 4.000000+0 4.939000+2 2.304180-1 0.000000+0 0.000000+0 80028533     \n"
    " 3.000000+0 3.000000+0 5.089000+2 1.108220-2 0.000000+0 0.000000+0 80028533     \n"
    " 3.000000+0 4.000000+0 5.089400+2 2.911150-1 0.000000+0 0.000000+0 80028533     \n"
    " 4.000000+0 4.000000+0 5.089800+2 1.668090-1 0.000000+0 0.000000+0 80028533     \n"
    " 2.000000+0 0.000000+0          0          0          6          0 80028533     \n"
    " 2.848000+1 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 80028533     \n"
    " 3.000000+0 0.000000+0          0          0          6          0 80028533     \n"
    " 1.362000+1 1.330000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 80028533     \n"
    " 4.000000+0 0.000000+0          0          0          6          0 80028533     \n"
    " 1.362000+1 2.670000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 80028533     \n"
    "                                                                   80028  0     \n"
    "                                                                   800 0  0     \n"
    "                                                                     0 0  0     \n"
    "                                                                    -1 0  0     \n";
}

std::string readContentFromFile( const std::string& filename ) {

  std::string content;
  std::ifstream in( filename,
                    std::ios::in | std::ios::binary | std::ios::ate );
  if ( not in ) {

    throw std::runtime_error( "test.endf not found" );
  }

  const auto file_size = in.tellg();
  in.seekg( 0, std::ios::beg );
  content.resize( file_size / sizeof( char ) );
  in.read( &( content[ 0 ] ), file_size );
  in.close();

  return content;
}