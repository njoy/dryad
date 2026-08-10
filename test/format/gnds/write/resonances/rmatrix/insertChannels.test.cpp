// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/rmatrix/insertChannels.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();
std::string chunk3();

SCENARIO( "insertChannels" ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto sr88 = id::ParticleID( "Sr88" );
  auto sr89 = id::ParticleID( "Sr89[all]" );

  resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                        Particle( sr89, 88.15046 * njoy::constants::neutron_mass, 0, +1 ) );
  resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                         Particle( sr88, 87.15046 * njoy::constants::neutron_mass, 0, +1 ) );

  resonances::ChannelRadii zero_radii( 0., 0. );
  resonances::ChannelRadii equal_radii( 7.1, 7.1 );

  std::vector< resonances::Channel > channels = {

    { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
      neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
    { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ),
      neutron_pair, neutron_pair, 0.,std::nullopt, equal_radii, true,
      resonances::Kinematics::NonRelativistic }
  };

  std::vector< resonances::Channel > channels_with_background = {

    { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
      neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
    { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ),
      neutron_pair, neutron_pair, 0., std::nullopt, equal_radii, true,
      resonances::Kinematics::NonRelativistic,
      resonances::SammyBackground( { 0.45, 3.2e-7, 0. }, { 0.075, 0. }, 0., 9.55e+5 ) }
  };

  std::vector< resonances::Channel > channels_with_boundary_condition = {

    { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
      neutron_pair, photon_pair, 0., 0, zero_radii, false },
    { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ),
      neutron_pair, neutron_pair, 0., -1, equal_radii, true,
      resonances::Kinematics::NonRelativistic }
  };

  GIVEN( "a parent node and a spingroup without background using eliminate shift boundary condition" ) {

    gnds::write::Options options;

    resonances::SpinGroup group( channels,
                                 { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                     id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ) },
                                   { 1.241000e+4, 8.331700e+5 },
                                   { { 1., 2. },
                                     { 1.1, 2.1 } } },
                                 resonances::Formalism::ReichMoore,
                                 resonances::BoundaryCondition::ShiftFactor );

    THEN( "a channels node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertChannels( parent, options, group, 1e-5, 1.2e+6, "eval", true );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a spingroup with background using eliminate shift boundary condition" ) {

    gnds::write::Options options;

    resonances::SpinGroup group( channels_with_background,
                                 { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                     id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ) },
                                   { 1.241000e+4, 8.331700e+5 },
                                   { { 1., 2. },
                                     { 1.1, 2.1 } } },
                                 resonances::Formalism::ReichMoore,
                                 resonances::BoundaryCondition::ShiftFactor );

    THEN( "a channels node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertChannels( parent, options, group, 1e-5, 1.2e+6, "eval", true );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a spingroup without background using constant boundary condition" ) {

    gnds::write::Options options;

    resonances::SpinGroup group( channels_with_boundary_condition,
                                 { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                     id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ) },
                                   { 1.241000e+4, 8.331700e+5 },
                                   { { 1., 2. },
                                     { 1.1, 2.1 } } },
                                 resonances::Formalism::ReichMoore,
                                 resonances::BoundaryCondition::Constant );

    THEN( "a channels node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertChannels( parent, options, group, 1e-5, 1.2e+6, "eval", true );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<channels>\n"
         "  <channel label=\"n,Sr88->g,Sr89[all]{0,0,1/2-}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
         "    <scatteringRadius>\n"
         "      <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </scatteringRadius>\n"
         "  </channel>\n"
         "  <channel label=\"n,Sr88->n,Sr88{1,1/2,1/2-}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"1\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
         "    <scatteringRadius>\n"
         "      <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </scatteringRadius>\n"
         "  </channel>\n"
         "</channels>\n";
}

std::string chunk2() {

  return "<channels>\n"
         "  <channel label=\"n,Sr88->g,Sr89[all]{0,0,1/2-}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
         "    <scatteringRadius>\n"
         "      <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </scatteringRadius>\n"
         "  </channel>\n"
         "  <channel label=\"n,Sr88->n,Sr88{1,1/2,1/2-}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"1\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
         "    <scatteringRadius>\n"
         "      <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </scatteringRadius>\n"
         "    <externalRMatrix type=\"SAMMY\">\n"
         "      <double label=\"constantExternalR\" value=\"0.45\" />\n"
         "      <double label=\"linearExternalR\" value=\"3.2e-07\" unit=\"1/eV\" />\n"
         "      <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
         "      <double label=\"constantLogarithmicCoefficient\" value=\"0.075\" />\n"
         "      <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
         "      <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
         "      <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
         "    </externalRMatrix>\n"
         "  </channel>\n"
         "</channels>\n";
}

std::string chunk3() {

  return "<channels>\n"
         "  <channel label=\"n,Sr88->g,Sr89[all]{0,0,1/2-}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" boundaryConditionValue=\"0\" columnIndex=\"1\">\n"
         "    <scatteringRadius>\n"
         "      <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </scatteringRadius>\n"
         "  </channel>\n"
         "  <channel label=\"n,Sr88->n,Sr88{1,1/2,1/2-}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"1\" channelSpin=\"0.5\" boundaryConditionValue=\"-1\" columnIndex=\"2\">\n"
         "    <scatteringRadius>\n"
         "      <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "        </axes>\n"
         "      </constant1d>\n"
         "    </scatteringRadius>\n"
         "  </channel>\n"
         "</channels>\n";
}
