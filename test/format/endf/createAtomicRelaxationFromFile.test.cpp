// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createAtomicRelaxationFromFile.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const AtomicRelaxation&, bool );

SCENARIO( "createAtomicRelaxation" ) {

  GIVEN( "ENDF material with atomic relaxation data" ) {

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        AtomicRelaxation oxygen1 = format::endf::createAtomicRelaxationFromFile( "atom-008_O_000.endf", false );
        AtomicRelaxation oxygen2 = format::endf::createAtomicRelaxationFromFile( "atom-008_O_000.endf", true );

        verifyChunk( oxygen1, false );
        verifyChunk( oxygen2, true );

        oxygen1.normalise();
        oxygen2.normalise();

        verifyChunk( oxygen1, true );
        verifyChunk( oxygen2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const AtomicRelaxation& chunk,
                  bool normalise ) {

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

  CHECK_THAT( 15.8619530, WithinRel( chunk.documentation().awr().value() ) );
  CHECK( 0 == chunk.documentation().library() );
  CHECK( std::make_pair( 8, 1 ) == chunk.documentation().version() );
  CHECK( description == chunk.documentation().description() );

  CHECK( id::ElementID( 8 ) == chunk.elementIdentifier() );

  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "K" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L1" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L2" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L3" ) ) );
  CHECK( false == chunk.hasSubshell( id::ElectronSubshellID( "M1" ) ) );

  auto shell_k = chunk.subshell( id::ElectronSubshellID( "K" ) );
  CHECK( id::ElectronSubshellID( "K" ) == shell_k.identifier() );
  CHECK_THAT( 538, WithinRel( shell_k.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( shell_k.population() ) );

  CHECK( true == shell_k.hasRadiativeTransitions() );
  CHECK( true == shell_k.hasNonRadiativeTransitions() );
  CHECK( true == shell_k.hasTransitions() );

  CHECK( 2 == shell_k.numberRadiativeTransitions() );
  CHECK( 6 == shell_k.numberNonRadiativeTransitions() );
  CHECK( 8 == shell_k.numberTransitions() );
  CHECK( 2 == shell_k.radiativeTransitions().size() );
  CHECK( 6 == shell_k.nonRadiativeTransitions().size() );

  double normalisation = normalise ? 1.00000015 : 1.0;

  CHECK( atomic::TransitionType::Radiative == shell_k.radiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::Radiative == shell_k.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768 / normalisation, WithinRel( shell_k.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027 / normalisation, WithinRel( shell_k.radiativeTransitions()[1].probability() ) );
  CHECK_THAT( 523.09, WithinRel( shell_k.radiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 523.13, WithinRel( shell_k.radiativeTransitions()[1].energy().value() ) );

  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_k.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_k.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_k.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_k.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.nonRadiativeTransitions()[5].emittingShell() );
  CHECK_THAT( 0.178644  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.116224  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.230418  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0110822 / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 0.291115  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 0.166809  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[5].probability() ) );
  CHECK_THAT( 478.82, WithinRel( shell_k.nonRadiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 493.86, WithinRel( shell_k.nonRadiativeTransitions()[1].energy().value() ) );
  CHECK_THAT( 493.9 , WithinRel( shell_k.nonRadiativeTransitions()[2].energy().value() ) );
  CHECK_THAT( 508.9 , WithinRel( shell_k.nonRadiativeTransitions()[3].energy().value() ) );
  CHECK_THAT( 508.94, WithinRel( shell_k.nonRadiativeTransitions()[4].energy().value() ) );
  CHECK_THAT( 508.98, WithinRel( shell_k.nonRadiativeTransitions()[5].energy().value() ) );

  CHECK_THAT( 0.00570795 / normalisation, WithinRel( shell_k.totalRadiativeProbability() ) );
  CHECK_THAT( 0.9942922  / normalisation, WithinRel( shell_k.totalNonRadiativeProbability() ) );

  auto shell_l1 = chunk.subshell( id::ElectronSubshellID( "L1" ) );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_l1.identifier() );
  CHECK_THAT( 28.48, WithinRel( shell_l1.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( shell_l1.population() ) );

  CHECK( false == shell_l1.hasRadiativeTransitions() );
  CHECK( false == shell_l1.hasNonRadiativeTransitions() );
  CHECK( false == shell_l1.hasTransitions() );

  CHECK( 0 == shell_l1.numberRadiativeTransitions() );
  CHECK( 0 == shell_l1.numberNonRadiativeTransitions() );
  CHECK( 0 == shell_l1.numberTransitions() );
  CHECK( 0 == shell_l1.radiativeTransitions().size() );
  CHECK( 0 == shell_l1.nonRadiativeTransitions().size() );

  auto shell_l2 = chunk.subshell( id::ElectronSubshellID( "L2" ) );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_l2.identifier() );
  CHECK_THAT( 13.62, WithinRel( shell_l2.bindingEnergy() ) );
  CHECK_THAT( 1.33 , WithinRel( shell_l2.population() ) );

  CHECK( false == shell_l2.hasRadiativeTransitions() );
  CHECK( false == shell_l2.hasNonRadiativeTransitions() );
  CHECK( false == shell_l2.hasTransitions() );

  CHECK( 0 == shell_l2.numberRadiativeTransitions() );
  CHECK( 0 == shell_l2.numberNonRadiativeTransitions() );
  CHECK( 0 == shell_l2.numberTransitions() );
  CHECK( 0 == shell_l2.radiativeTransitions().size() );
  CHECK( 0 == shell_l2.nonRadiativeTransitions().size() );

  auto shell_l3 = chunk.subshell( id::ElectronSubshellID( "L3" ) );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_l3.identifier() );
  CHECK_THAT( 13.62, WithinRel( shell_l3.bindingEnergy() ) );
  CHECK_THAT( 2.67 , WithinRel( shell_l3.population() ) );

  CHECK( false == shell_l3.hasRadiativeTransitions() );
  CHECK( false == shell_l3.hasNonRadiativeTransitions() );
  CHECK( false == shell_l3.hasTransitions() );

  CHECK( 0 == shell_l3.numberRadiativeTransitions() );
  CHECK( 0 == shell_l3.numberNonRadiativeTransitions() );
  CHECK( 0 == shell_l3.numberTransitions() );
  CHECK( 0 == shell_l3.radiativeTransitions().size() );
  CHECK( 0 == shell_l3.nonRadiativeTransitions().size() );
}
