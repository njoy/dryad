// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/external/ripl3/Levels.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::external::ripl3;

SCENARIO( "Levels" ) {

  GIVEN( "the Levels static repository" ) {

    THEN( "predefined particles can be retrieved" ) {

      // photon
      const auto& photon = Levels::entry( id::ParticleID::photon() );

      CHECK( id::ParticleID::photon() == photon.identifier() );
      CHECK( std::nullopt == photon.energy() );
      CHECK_THAT( 1.0, WithinRel( photon.spin().value() ) );
      CHECK( -1 == photon.parity() );
      CHECK( std::nullopt == photon.halfLife() );

      // neutron
      const auto& neutron = Levels::entry( id::ParticleID::neutron() );

      CHECK( id::ParticleID::neutron() == neutron.identifier() );
      CHECK( std::nullopt == neutron.energy() );
      CHECK_THAT( 0.5, WithinRel( neutron.spin().value() ) );
      CHECK( 1 == neutron.parity() );
      CHECK( std::nullopt == neutron.halfLife() );

      // proton
      const auto& proton = Levels::entry( id::ParticleID::proton() );

      CHECK( id::ParticleID::proton() == proton.identifier() );
      CHECK( std::nullopt == proton.energy() );
      CHECK_THAT( 0.5, WithinRel( proton.spin().value() ) );
      CHECK( 1 == proton.parity() );
      CHECK( std::nullopt == proton.halfLife() );

      // deuteron
      const auto& deuteron = Levels::entry( id::ParticleID::deuteron() );

      CHECK( id::ParticleID::deuteron() == deuteron.identifier() );
      CHECK( std::nullopt == deuteron.energy() );
      CHECK_THAT( 1.0, WithinRel( deuteron.spin().value() ) );
      CHECK( 1 == deuteron.parity() );
      CHECK( std::nullopt == deuteron.halfLife() );

      // triton
      const auto& triton = Levels::entry( id::ParticleID::triton() );

      CHECK( id::ParticleID::triton() == triton.identifier() );
      CHECK( std::nullopt == triton.energy() );
      CHECK_THAT( 0.5, WithinRel( triton.spin().value() ) );
      CHECK( 1 == triton.parity() );
      CHECK( std::nullopt == triton.halfLife() );

      // helion
      const auto& helion = Levels::entry( id::ParticleID::helion() );

      CHECK( id::ParticleID::helion() == helion.identifier() );
      CHECK( std::nullopt == helion.energy() );
      CHECK_THAT( 0.5, WithinRel( helion.spin().value() ) );
      CHECK( 1 == helion.parity() );
      CHECK( std::nullopt == helion.halfLife() );

      // alpha
      const auto& alpha = Levels::entry( id::ParticleID::alpha() );

      CHECK( id::ParticleID::alpha() == alpha.identifier() );
      CHECK( std::nullopt == alpha.energy() );
      CHECK_THAT( 0.0, WithinRel( alpha.spin().value() ) );
      CHECK( 1 == alpha.parity() );
      CHECK( std::nullopt == alpha.halfLife() );

      // other nuclides - sanity check to see if all files get loaded in correctly
      CHECK(      9 == Levels::size() );

      if ( std::getenv( "NJOY_DATAPATH" ) ) {

        auto data = Levels::entry( id::ParticleID( "H1" ) );
        CHECK( id::ParticleID( "H1" ) == data.identifier() );
        CHECK_THAT( 0., WithinRel( data.energy().value() ) );
        CHECK_THAT( 0.5, WithinRel( data.spin().value() ) );
        CHECK( 1 == data.parity() );
        CHECK( std::nullopt == data.halfLife() );

        CHECK(     29 == Levels::size() );

        data = Levels::entry( id::ParticleID( "He4" ) );
        CHECK( id::ParticleID( "He4" ) == data.identifier() );
        CHECK_THAT( 0., WithinRel( data.energy().value() ) );
        CHECK_THAT( 0., WithinRel( data.spin().value() ) );
        CHECK( 1 == data.parity() );
        CHECK( std::nullopt == data.halfLife() );

        CHECK(     72 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Li6" ) );
        CHECK( id::ParticleID( "Li6" ) == data.identifier() );
        CHECK_THAT( 0., WithinRel( data.energy().value() ) );
        CHECK_THAT( 1., WithinRel( data.spin().value() ) );
        CHECK( 1 == data.parity() );
        CHECK( std::nullopt == data.halfLife() );

        CHECK(    146 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Be9" ) );
        CHECK( id::ParticleID( "Be9" ) == data.identifier() );
        CHECK_THAT( 0., WithinRel( data.energy().value() ) );
        CHECK_THAT( 1.5, WithinRel( data.spin().value() ) );
        CHECK( -1 == data.parity() );
        CHECK( std::nullopt == data.halfLife() );

        CHECK(    331 == Levels::size() );

        data = Levels::entry( id::ParticleID( "B10" ) );
        CHECK( id::ParticleID( "B10" ) == data.identifier() );
        CHECK_THAT( 0., WithinRel( data.energy().value() ) );
        CHECK_THAT( 3., WithinRel( data.spin().value() ) );
        CHECK( 1 == data.parity() );
        CHECK( std::nullopt == data.halfLife() );

        CHECK(    545 == Levels::size() );

        data = Levels::entry( id::ParticleID( "C12" ) );
        CHECK( id::ParticleID( "C12" ) == data.identifier() );
        CHECK_THAT( 0., WithinRel( data.energy().value() ) );
        CHECK_THAT( 0., WithinRel( data.spin().value() ) );
        CHECK( 1 == data.parity() );
        CHECK( std::nullopt == data.halfLife() );

        CHECK(    850 == Levels::size() );

        data = Levels::entry( id::ParticleID( "N14" ) );
        CHECK( id::ParticleID( "N14" ) == data.identifier() );
        CHECK_THAT( 0., WithinRel( data.energy().value() ) );
        CHECK_THAT( 1., WithinRel( data.spin().value() ) );
        CHECK( 1 == data.parity() );
        CHECK( std::nullopt == data.halfLife() );

        CHECK(   1326 == Levels::size() );

        data = Levels::entry( id::ParticleID( "O16" ) );
        CHECK( id::ParticleID( "O16" ) == data.identifier() );
        CHECK_THAT( 0., WithinRel( data.energy().value() ) );
        CHECK_THAT( 0., WithinRel( data.spin().value() ) );
        CHECK( 1 == data.parity() );
        CHECK( std::nullopt == data.halfLife() );

        CHECK(   1941 == Levels::size() );

        data = Levels::entry( id::ParticleID( "F19" ) );
        CHECK(   2602 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ne20" ) );
        CHECK(   3364 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Na23" ) );
        CHECK(   4229 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Mg24" ) );
        CHECK(   5176 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Al27" ) );
        CHECK(   6041 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Si28" ) );
        CHECK(   7043 == Levels::size() );

        data = Levels::entry( id::ParticleID( "P31" ) );
        CHECK(   8138 == Levels::size() );

        data = Levels::entry( id::ParticleID( "S32" ) );
        CHECK(   9609 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Cl35" ) );
        CHECK(  11430 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ar36" ) );
        CHECK(  13136 == Levels::size() );

        data = Levels::entry( id::ParticleID( "K39" ) );
        CHECK(  14495 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ca40" ) );
        CHECK(  17476 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Sc45" ) );
        CHECK(  19711 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ti46" ) );
        CHECK(  21261 == Levels::size() );

        data = Levels::entry( id::ParticleID( "V50" ) );
        CHECK(  22962 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Cr50" ) );
        CHECK(  24572 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Mn55" ) );
        CHECK(  26373 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Fe54" ) );
        CHECK(  28138 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Co59" ) );
        CHECK(  30208 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ni58" ) );
        CHECK(  33080 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Cu63" ) );
        CHECK(  35578 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Zn64" ) );
        CHECK(  37376 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ga69" ) );
        CHECK(  38720 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ge70" ) );
        CHECK(  40751 == Levels::size() );

        data = Levels::entry( id::ParticleID( "As75" ) );
        CHECK(  42108 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Se74" ) );
        CHECK(  43779 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Br79" ) );
        CHECK(  45321 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Kr78" ) );
        CHECK(  47369 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Rb85" ) );
        CHECK(  48958 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Sr84" ) );
        CHECK(  51252 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Y89" ) );
        CHECK(  53237 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Zr90" ) );
        CHECK(  55638 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Nb93" ) );
        CHECK(  57390 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Mo92" ) );
        CHECK(  60225 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Tc99" ) );
        CHECK(  61923 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ru96" ) );
        CHECK(  64028 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Rh103" ) );
        CHECK(  65843 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Pd102" ) );
        CHECK(  68066 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ag107" ) );
        CHECK(  69629 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Cd106" ) );
        CHECK(  72785 == Levels::size() );

        data = Levels::entry( id::ParticleID( "In113" ) );
        CHECK(  74813 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Sn112" ) );
        CHECK(  78060 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Sb121" ) );
        CHECK(  80520 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Te120" ) );
        CHECK(  84538 == Levels::size() );

        data = Levels::entry( id::ParticleID( "I127" ) );
        CHECK(  87108 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Xe124" ) );
        CHECK(  90505 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Cs133" ) );
        CHECK(  92217 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ba130" ) );
        CHECK(  95343 == Levels::size() );

        data = Levels::entry( id::ParticleID( "La138" ) );
        CHECK(  97715 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ce136" ) );
        CHECK( 100235 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Pr141" ) );
        CHECK( 102039 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Nd142" ) );
        CHECK( 105887 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Pm138" ) );
        CHECK( 107555 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Sm144" ) );
        CHECK( 110768 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Eu151" ) );
        CHECK( 112957 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Gd152" ) );
        CHECK( 116885 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Tb159" ) );
        CHECK( 118884 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Dy156" ) );
        CHECK( 122679 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ho165" ) );
        CHECK( 124989 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Er162" ) );
        CHECK( 128473 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Tm169" ) );
        CHECK( 130861 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Yb168" ) );
        CHECK( 133796 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Lu175" ) );
        CHECK( 135947 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Hf174" ) );
        CHECK( 139416 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ta180" ) );
        CHECK( 141726 == Levels::size() );

        data = Levels::entry( id::ParticleID( "W180" ) );
        CHECK( 144837 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Re185" ) );
        CHECK( 147171 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Os184" ) );
        CHECK( 150318 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ir191" ) );
        CHECK( 152373 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Pt190" ) );
        CHECK( 154972 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Au197" ) );
        CHECK( 157048 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Hg196" ) );
        CHECK( 159418 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Tl203" ) );
        CHECK( 160916 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Pb204" ) );
        CHECK( 164602 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Bi209" ) );
        CHECK( 166142 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Po210" ) );
        CHECK( 167353 == Levels::size() );

        data = Levels::entry( id::ParticleID( "At210" ) );
        CHECK( 168086 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Rn222" ) );
        CHECK( 168815 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Fr223" ) );
        CHECK( 169480 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ra226" ) );
        CHECK( 170437 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ac227" ) );
        CHECK( 170886 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Th232" ) );
        CHECK( 172261 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Pa231" ) );
        CHECK( 172693 == Levels::size() );

        data = Levels::entry( id::ParticleID(  "U238" ) );
        CHECK( 174093 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Np237" ) );
        CHECK( 174542 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Pu238" ) );
        CHECK( 175284 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Am242" ) );
        CHECK( 175803 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Cm246" ) );
        CHECK( 176256 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Bk239" ) );
        CHECK( 176462 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Cf255" ) );
        CHECK( 176764 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Es244" ) );
        CHECK( 176842 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Fm248" ) );
        CHECK( 176935 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Md252" ) );
        CHECK( 176991 == Levels::size() );

        data = Levels::entry( id::ParticleID( "No251" ) );
        CHECK( 177101 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Lr255" ) );
        CHECK( 177156 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Rf256" ) );
        CHECK( 177208 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Db258" ) );
        CHECK( 177236 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Sg261" ) );
        CHECK( 177259 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Bh272" ) );
        CHECK( 177286 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Hs266" ) );
        CHECK( 177312 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Mt276" ) );
        CHECK( 177335 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ds279" ) );
        CHECK( 177359 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Rg275" ) );
        CHECK( 177374 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Cn280" ) );
        CHECK( 177387 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Nh285" ) );
        CHECK( 177401 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Fl290" ) );
        CHECK( 177409 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Mc290" ) );
        CHECK( 177415 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Lv290" ) );
        CHECK( 177420 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Ts292" ) );
        CHECK( 177424 == Levels::size() );

        data = Levels::entry( id::ParticleID( "Og294" ) );
        CHECK( 177427 == Levels::size() );
      }
    } // THEN

    THEN( "requesting a non-existent particle throws an exception" ) {

      if ( std::getenv( "NJOY_DATAPATH" ) ) {

        id::ParticleID u214( "U214" ); // first available is U215
        id::ParticleID u235( "U235" );

        CHECK_THROWS( Levels::entry( u214 ) );
        CHECK_NOTHROW( Levels::entry( u235 ) );
      }
    } // THEN
  } // GIVEN
} // SCENARIO
