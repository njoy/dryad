// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/photoatomic/createReactionProducts.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createReactionProducts" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "reaction products can be derived" ) {

        auto products = format::ace::photoatomic::createReactionProducts( table );

        CHECK( 5 == products.size() );

        CHECK( 0 == products[0].size() );

        CHECK( 1 == products[1].size() );
        CHECK( id::ParticleID( "g" ) == products[1][0].identifier() );
        CHECK( false == products[1][0].hasAverageEnergy() );
        CHECK( true == products[1][0].hasDistributionData() );
        CHECK( true == std::holds_alternative< int >( products[1][0].multiplicity() ) );
        auto multiplicity = std::get< int >( products[1][0].multiplicity() );
        CHECK( 1 == multiplicity );
        CHECK( std::nullopt == products[1][0].averageEnergy() );
        CHECK( std::nullopt != products[1][0].distributionData() );
        CHECK( true == std::holds_alternative< CoherentDistributionData >( products[1][0].distributionData().value() ) );
        auto coherent = std::get< CoherentDistributionData >( products[1][0].distributionData().value() );
        CHECK( DistributionDataType::Coherent == coherent.type() );
        CHECK( ReferenceFrame::CentreOfMass == coherent.frame() );
        CHECK( false == coherent.hasAnomolousFormFactor() );
        CHECK_THAT( 0., WithinRel( coherent.scatteringFunction().lowerInverseLengthLimit() ) );
        CHECK_THAT( 6., WithinRel( coherent.scatteringFunction().upperInverseLengthLimit() ) );
        CHECK( 55 == coherent.scatteringFunction().inverseLengths().size() );
        CHECK( 55 == coherent.scatteringFunction().values().size() );
        CHECK( 1 == coherent.scatteringFunction().boundaries().size() );
        CHECK( 1 == coherent.scatteringFunction().interpolants().size() );
        CHECK_THAT(          0., WithinRel( coherent.scatteringFunction().inverseLengths()[0] ) );
        CHECK_THAT(          6., WithinRel( coherent.scatteringFunction().inverseLengths()[54] ) );
        CHECK_THAT(          1., WithinRel( coherent.scatteringFunction().values()[0] ) );
        CHECK_THAT( 6.282400e-6, WithinRel( coherent.scatteringFunction().values()[54] ) );
        CHECK( 54 == coherent.scatteringFunction().boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == coherent.scatteringFunction().interpolants()[0] );
        CHECK( true == coherent.scatteringFunction().isLinearised() );
        CHECK( std::nullopt == coherent.realAnomolousFormFactor() );
        CHECK( std::nullopt == coherent.imaginaryAnomolousFormFactor() );

        CHECK( 1 == products[2].size() );
        CHECK( id::ParticleID( "g" ) == products[2][0].identifier() );
        CHECK( false == products[2][0].hasAverageEnergy() );
        CHECK( true == products[2][0].hasDistributionData() );
        CHECK( true == std::holds_alternative< int >( products[2][0].multiplicity() ) );
        multiplicity = std::get< int >( products[2][0].multiplicity() );
        CHECK( 1 == multiplicity );
        CHECK( std::nullopt == products[2][0].averageEnergy() );
        CHECK( std::nullopt != products[2][0].distributionData() );
        CHECK( true == std::holds_alternative< IncoherentDistributionData >( products[2][0].distributionData().value() ) );
        auto incoherent = std::get< IncoherentDistributionData >( products[2][0].distributionData().value() );
        CHECK( DistributionDataType::Incoherent == incoherent.type() );
        CHECK( ReferenceFrame::CentreOfMass == incoherent.frame() );
        CHECK_THAT( 0., WithinRel( incoherent.scatteringFunction().lowerInverseLengthLimit() ) );
        CHECK_THAT( 8., WithinRel( incoherent.scatteringFunction().upperInverseLengthLimit() ) );
        CHECK( 21 == incoherent.scatteringFunction().inverseLengths().size() );
        CHECK( 21 == incoherent.scatteringFunction().values().size() );
        CHECK( 1 == incoherent.scatteringFunction().boundaries().size() );
        CHECK( 1 == incoherent.scatteringFunction().interpolants().size() );
        CHECK_THAT( 0., WithinRel( incoherent.scatteringFunction().inverseLengths()[0] ) );
        CHECK_THAT( 8., WithinRel( incoherent.scatteringFunction().inverseLengths()[20] ) );
        CHECK_THAT( 0., WithinRel( incoherent.scatteringFunction().values()[0] ) );
        CHECK_THAT( 1., WithinRel( incoherent.scatteringFunction().values()[20] ) );
        CHECK( 20 == incoherent.scatteringFunction().boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == incoherent.scatteringFunction().interpolants()[0] );
        CHECK( true == incoherent.scatteringFunction().isLinearised() );

        CHECK( 0 == products[3].size() );

        CHECK( 0 == products[4].size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reaction products can be derived" ) {

        auto products = format::ace::photoatomic::createReactionProducts( table );

        CHECK( 6 == products.size() );

        CHECK( 0 == products[0].size() );

        CHECK( 1 == products[1].size() );
        CHECK( id::ParticleID( "g" ) == products[1][0].identifier() );
        CHECK( false == products[1][0].hasAverageEnergy() );
        CHECK( true == products[1][0].hasDistributionData() );
        CHECK( true == std::holds_alternative< int >( products[1][0].multiplicity() ) );
        auto multiplicity = std::get< int >( products[1][0].multiplicity() );
        CHECK( 1 == multiplicity );
        CHECK( std::nullopt == products[1][0].averageEnergy() );
        CHECK( std::nullopt != products[1][0].distributionData() );
        CHECK( true == std::holds_alternative< CoherentDistributionData >( products[1][0].distributionData().value() ) );
        auto coherent = std::get< CoherentDistributionData >( products[1][0].distributionData().value() );
        CHECK( DistributionDataType::Coherent == coherent.type() );
        CHECK( ReferenceFrame::CentreOfMass == coherent.frame() );
        CHECK( false == coherent.hasAnomolousFormFactor() );
        CHECK_THAT(   0., WithinRel( coherent.scatteringFunction().lowerInverseLengthLimit() ) );
        CHECK_THAT( 1e+9, WithinRel( coherent.scatteringFunction().upperInverseLengthLimit() ) );
        CHECK( 90 == coherent.scatteringFunction().inverseLengths().size() );
        CHECK( 90 == coherent.scatteringFunction().values().size() );
        CHECK( 1 == coherent.scatteringFunction().boundaries().size() );
        CHECK( 1 == coherent.scatteringFunction().interpolants().size() );
        CHECK_THAT(          0., WithinRel( coherent.scatteringFunction().inverseLengths()[0] ) );
        CHECK_THAT(        1e+9, WithinRel( coherent.scatteringFunction().inverseLengths()[89] ) );
        CHECK_THAT(          1., WithinRel( coherent.scatteringFunction().values()[0] ) );
        CHECK_THAT( 8.18290e-39, WithinRel( coherent.scatteringFunction().values()[89] ) );
        CHECK( 89 == coherent.scatteringFunction().boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == coherent.scatteringFunction().interpolants()[0] );
        CHECK( true == coherent.scatteringFunction().isLinearised() );
        CHECK( std::nullopt == coherent.realAnomolousFormFactor() );
        CHECK( std::nullopt == coherent.imaginaryAnomolousFormFactor() );

        CHECK( 1 == products[2].size() );
        CHECK( id::ParticleID( "g" ) == products[2][0].identifier() );
        CHECK( false == products[2][0].hasAverageEnergy() );
        CHECK( true == products[2][0].hasDistributionData() );
        CHECK( true == std::holds_alternative< int >( products[2][0].multiplicity() ) );
        multiplicity = std::get< int >( products[2][0].multiplicity() );
        CHECK( 1 == multiplicity );
        CHECK( std::nullopt == products[2][0].averageEnergy() );
        CHECK( std::nullopt != products[2][0].distributionData() );
        CHECK( true == std::holds_alternative< IncoherentDistributionData >( products[2][0].distributionData().value() ) );
        auto incoherent = std::get< IncoherentDistributionData >( products[2][0].distributionData().value() );
        CHECK( DistributionDataType::Incoherent == incoherent.type() );
        CHECK( ReferenceFrame::CentreOfMass == incoherent.frame() );
        CHECK_THAT(   0., WithinRel( incoherent.scatteringFunction().lowerInverseLengthLimit() ) );
        CHECK_THAT( 1e+9, WithinRel( incoherent.scatteringFunction().upperInverseLengthLimit() ) );
        CHECK( 94 == incoherent.scatteringFunction().inverseLengths().size() );
        CHECK( 94 == incoherent.scatteringFunction().values().size() );
        CHECK( 1 == incoherent.scatteringFunction().boundaries().size() );
        CHECK( 1 == incoherent.scatteringFunction().interpolants().size() );
        CHECK_THAT(   0., WithinRel( incoherent.scatteringFunction().inverseLengths()[0] ) );
        CHECK_THAT( 1e+9, WithinRel( incoherent.scatteringFunction().inverseLengths()[93] ) );
        CHECK_THAT(   0., WithinRel( incoherent.scatteringFunction().values()[0] ) );
        CHECK_THAT(   1., WithinRel( incoherent.scatteringFunction().values()[93] ) );
        CHECK( 93 == incoherent.scatteringFunction().boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == incoherent.scatteringFunction().interpolants()[0] );
        CHECK( true == incoherent.scatteringFunction().isLinearised() );

        CHECK( 0 == products[3].size() );

        CHECK( 0 == products[4].size() );

        CHECK( 0 == products[5].size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reaction products can be derived" ) {

        auto products = format::ace::photoatomic::createReactionProducts( table );

        CHECK( 6 == products.size() );

        CHECK( 0 == products[0].size() );

        CHECK( 1 == products[1].size() );
        CHECK( id::ParticleID( "g" ) == products[1][0].identifier() );
        CHECK( false == products[1][0].hasAverageEnergy() );
        CHECK( true == products[1][0].hasDistributionData() );
        CHECK( true == std::holds_alternative< int >( products[1][0].multiplicity() ) );
        auto multiplicity = std::get< int >( products[1][0].multiplicity() );
        CHECK( 1 == multiplicity );
        CHECK( std::nullopt == products[1][0].averageEnergy() );
        CHECK( std::nullopt != products[1][0].distributionData() );
        CHECK( true == std::holds_alternative< CoherentDistributionData >( products[1][0].distributionData().value() ) );
        auto coherent = std::get< CoherentDistributionData >( products[1][0].distributionData().value() );
        CHECK( DistributionDataType::Coherent == coherent.type() );
        CHECK( ReferenceFrame::CentreOfMass == coherent.frame() );
        CHECK( false == coherent.hasAnomolousFormFactor() );
        CHECK_THAT(   0., WithinRel( coherent.scatteringFunction().lowerInverseLengthLimit() ) );
        CHECK_THAT( 1e+9, WithinRel( coherent.scatteringFunction().upperInverseLengthLimit() ) );
        CHECK( 90 == coherent.scatteringFunction().inverseLengths().size() );
        CHECK( 90 == coherent.scatteringFunction().values().size() );
        CHECK( 1 == coherent.scatteringFunction().boundaries().size() );
        CHECK( 1 == coherent.scatteringFunction().interpolants().size() );
        CHECK_THAT(          0., WithinRel( coherent.scatteringFunction().inverseLengths()[0] ) );
        CHECK_THAT(        1e+9, WithinRel( coherent.scatteringFunction().inverseLengths()[89] ) );
        CHECK_THAT(          1., WithinRel( coherent.scatteringFunction().values()[0] ) );
        CHECK_THAT( 8.18290e-39, WithinRel( coherent.scatteringFunction().values()[89] ) );
        CHECK( 89 == coherent.scatteringFunction().boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == coherent.scatteringFunction().interpolants()[0] );
        CHECK( true == coherent.scatteringFunction().isLinearised() );
        CHECK( std::nullopt == coherent.realAnomolousFormFactor() );
        CHECK( std::nullopt == coherent.imaginaryAnomolousFormFactor() );

        CHECK( 1 == products[2].size() );
        CHECK( id::ParticleID( "g" ) == products[2][0].identifier() );
        CHECK( false == products[2][0].hasAverageEnergy() );
        CHECK( true == products[2][0].hasDistributionData() );
        CHECK( true == std::holds_alternative< int >( products[2][0].multiplicity() ) );
        multiplicity = std::get< int >( products[2][0].multiplicity() );
        CHECK( 1 == multiplicity );
        CHECK( std::nullopt == products[2][0].averageEnergy() );
        CHECK( std::nullopt != products[2][0].distributionData() );
        CHECK( true == std::holds_alternative< IncoherentDistributionData >( products[2][0].distributionData().value() ) );
        auto incoherent = std::get< IncoherentDistributionData >( products[2][0].distributionData().value() );
        CHECK( DistributionDataType::Incoherent == incoherent.type() );
        CHECK( ReferenceFrame::CentreOfMass == incoherent.frame() );
        CHECK_THAT(   0., WithinRel( incoherent.scatteringFunction().lowerInverseLengthLimit() ) );
        CHECK_THAT( 1e+9, WithinRel( incoherent.scatteringFunction().upperInverseLengthLimit() ) );
        CHECK( 94 == incoherent.scatteringFunction().inverseLengths().size() );
        CHECK( 94 == incoherent.scatteringFunction().values().size() );
        CHECK( 1 == incoherent.scatteringFunction().boundaries().size() );
        CHECK( 1 == incoherent.scatteringFunction().interpolants().size() );
        CHECK_THAT(   0., WithinRel( incoherent.scatteringFunction().inverseLengths()[0] ) );
        CHECK_THAT( 1e+9, WithinRel( incoherent.scatteringFunction().inverseLengths()[93] ) );
        CHECK_THAT(   0., WithinRel( incoherent.scatteringFunction().values()[0] ) );
        CHECK_THAT(   1., WithinRel( incoherent.scatteringFunction().values()[93] ) );
        CHECK( 93 == incoherent.scatteringFunction().boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == incoherent.scatteringFunction().interpolants()[0] );
        CHECK( true == incoherent.scatteringFunction().isLinearised() );

        CHECK( 0 == products[3].size() );

        CHECK( 0 == products[4].size() );

        CHECK( 0 == products[5].size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
