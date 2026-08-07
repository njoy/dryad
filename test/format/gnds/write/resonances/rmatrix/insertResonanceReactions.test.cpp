// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/rmatrix/insertResonanceReactions.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertResonanceReactions" ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto si29 = id::ParticleID( "Si29" );
  auto si30 = id::ParticleID( "Si30[all]" );

  resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                        Particle( si30, 29.728 * njoy::constants::neutron_mass, 0, +1 ) );
  resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                         Particle( si29, 28.728 * njoy::constants::neutron_mass, 0.5, +1 ) );

  resonances::ChannelRadii zero_radii( 0., 0. );
  resonances::ChannelRadii radii( 4.221, 4.221 );

  resonances::CompoundSystem compound( 1e-5, 1.3e+6,
                                       { { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                               neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                             { id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                           { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                               id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ) },
                                             { 3.740320e+5, 6.007182e+5 },
                                             { { 1., 2. },
                                               { 1.1, 2.1 } } },
                                           resonances::Formalism::ReichMoore,
                                           resonances::BoundaryCondition::ShiftFactor }, // 0- spin group
                                         { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0+}" ),
                                               neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                             { id::ChannelID( "n,Si29->n,Si29{0,0,0+}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                           { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                               id::ChannelID( "n,Si29->n,Si29{0,0,0+}" ) },
                                             { -2.041700e+6, 2.248487e+6 },
                                             { { 3., 4. },
                                               { 3.1, 4.1 } } },
                                           resonances::Formalism::ReichMoore,
                                           resonances::BoundaryCondition::ShiftFactor }, // 0+ spin group
                                         { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1-}" ),
                                               neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                             { id::ChannelID( "n,Si29->n,Si29{1,0,1-}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii },
                                             { id::ChannelID( "n,Si29->n,Si29{1,1,1-}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                           { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1-}" ),
                                               id::ChannelID( "n,Si29->n,Si29{1,0,1-}" ),
                                               id::ChannelID( "n,Si29->n,Si29{1,1,1-}" ) },
                                             { 1.529411e+4, 1.240000e+6 },
                                             { { 5., 6. },
                                               { 5.1, 6.1 },
                                               { 5.2, 6.2 } } },
                                           resonances::Formalism::ReichMoore,
                                           resonances::BoundaryCondition::ShiftFactor }, // 1- spin group
                                         { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1+}" ),
                                               neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                             { id::ChannelID( "n,Si29->n,Si29{0,1,1+}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii },
                                             { id::ChannelID( "n,Si29->n,Si29{2,1,1+}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                           { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1+}" ),
                                               id::ChannelID( "n,Si29->n,Si29{0,1,1+}" ),
                                               id::ChannelID( "n,Si29->n,Si29{2,1,1+}" ) },
                                             { 3.842219e+5, 1.388859e+6 },
                                             { { 7., 8. },
                                               { 7.1, 8.1 },
                                               { 7.2, 8.2 } } },
                                           resonances::Formalism::ReichMoore,
                                           resonances::BoundaryCondition::ShiftFactor }, // 1+ spin group
                                         { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2-}" ),
                                               neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                             { id::ChannelID( "n,Si29->n,Si29{1,1,2-}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                           { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2-}" ),
                                               id::ChannelID( "n,Si29->n,Si29{1,1,2-}" ) },
                                             { 3.883377e+4, 1.207629e+6 },
                                             { { 9., 10. },
                                               { 9.1, 10.1 } } },
                                           resonances::Formalism::ReichMoore,
                                           resonances::BoundaryCondition::ShiftFactor }, // 2- spin group
                                         { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2+}" ),
                                               neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                             { id::ChannelID( "n,Si29->n,Si29{2,0,2+}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii },
                                             { id::ChannelID( "n,Si29->n,Si29{2,1,2+}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                           { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2+}" ),
                                               id::ChannelID( "n,Si29->n,Si29{2,0,2+}" ),
                                               id::ChannelID( "n,Si29->n,Si29{2,1,2+}" ) } }, // empty table
                                           resonances::Formalism::ReichMoore,
                                           resonances::BoundaryCondition::ShiftFactor }, // 2+ spin group
                                         { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,3+}" ),
                                               neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                             { id::ChannelID( "n,Si29->n,Si29{2,1,3+}" ),
                                               neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                           { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,3+}" ),
                                               id::ChannelID( "n,Si29->n,Si29{2,1,3+}" ) },
                                             { 6.203529e+5 },
                                             { { 11. },
                                               { 11.1 } } },
                                           resonances::Formalism::ReichMoore,
                                           resonances::BoundaryCondition::ShiftFactor } } ); // 3+ spin group

  std::map< id::ReactionID, double > qvalues= {

    { { "n,Si29->g,Si30[all]" }, 0. }, { { "n,Si29->n,Si29" }, 1. } // setting elastic Q to 1 for testing purposes
  };

  GIVEN( "a parent node and a compound system" ) {

    gnds::write::Options options;

    THEN( "a resonanceReactions node can be inserted - fullResonanceData = true" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertResonanceReactions( parent, options, compound, qvalues, "eval", true );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a compound system" ) {

    gnds::write::Options options;

    THEN( "a resonanceReactions node can be inserted - fullResonanceData = false" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertResonanceReactions( parent, options, compound, qvalues, "eval", false );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  // all data is printed

  return "<resonanceReactions>\n"
         "  <resonanceReaction label=\"n,Si29->g,Si30[all]\" ejectile=\"g\" eliminated=\"true\">\n"
         "    <link href=\"/reactionSuite/reactions/reaction[@label=\'n,Si29->g,Si30[all]\']\" />\n"
         "    <Q>\n"
         "      <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </Q>\n"
         "  </resonanceReaction>\n"
         "  <resonanceReaction label=\"n,Si29->n,Si29\" ejectile=\"n\">\n"
         "    <link href=\"/reactionSuite/reactions/reaction[@label=\'n,Si29->n,Si29\']\" />\n"
         "    <Q>\n"
         "      <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </Q>\n"
         "  </resonanceReaction>\n"
         "</resonanceReactions>\n";
}

std::string chunk2() {

  // only non-default data is printed - since the qvalues has a qvalue of 1 for elastic, the zero
  // value in the compound system is not the default so it it printed.

  return "<resonanceReactions>\n"
         "  <resonanceReaction label=\"n,Si29->g,Si30[all]\" ejectile=\"g\" eliminated=\"true\">\n"
         "    <link href=\"/reactionSuite/reactions/reaction[@label=\'n,Si29->g,Si30[all]\']\" />\n"
         "  </resonanceReaction>\n"
         "  <resonanceReaction label=\"n,Si29->n,Si29\" ejectile=\"n\">\n"
         "    <link href=\"/reactionSuite/reactions/reaction[@label=\'n,Si29->n,Si29\']\" />\n"
         "    <Q>\n"
         "      <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </Q>\n"
         "  </resonanceReaction>\n"
         "</resonanceReactions>\n";
}
