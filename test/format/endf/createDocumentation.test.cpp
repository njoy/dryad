// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createDocumentation.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const Documentation& );

SCENARIO( "createDocumentation" ) {

  GIVEN( "ENDF material with atomic relaxation data" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "atom-008_O_000.endf" );
    auto mf1mt451 = tape.materials().front().section( 1, 451 ).parse< 1, 451 >();

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        Documentation chunk = format::endf::createDocumentation( mf1mt451 );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const Documentation& chunk ) {

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

  CHECK_THAT( 15.8619530, WithinRel( chunk.awr().value() ) );
  CHECK( 0 == chunk.library() );
  CHECK( 8 == chunk.version()->first );
  CHECK( 1 == chunk.version()->second );
  CHECK( description == chunk.description().value() );
}
