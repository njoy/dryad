// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/calculator/ReichMoore.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ReichMoore" ) {

  GIVEN( "valid number of channels and a resonance table" ) {

    auto photon = id::ParticleID::photon();
    auto neutron = id::ParticleID::neutron();
    auto proton = id::ParticleID::proton();
    auto cu63 = id::ParticleID( "Cu63" );
    auto cu64 = id::ParticleID( "Cu64[all]" );

    ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                              Particle( cu64, 63.389 * constants::neutron_mass, 0, +1 ) );
    ParticlePair neutron_pair( Particle( neutron, constants::neutron_mass, 0.5, +1 ),
                               Particle( cu63, 62.389 * constants::neutron_mass, 1.5, -1 ) );

    ChannelRadii zero_radii( 0., 0. );
    ChannelRadii radii( 6.7, 6.7 );

    // boundary conditions are set to -l
    // for ShiftFactor, the boundary conditions are normally set to std::nullopt
    Channel capture( id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,0+}" ),
                     neutron_pair, photon_pair,
                     0., 0, zero_radii );
    Channel elastic( id::ChannelID( "n,Cu63->n,Cu63{1,1,0+}" ),
                     neutron_pair, neutron_pair,
                     0., -1, radii );

    ResonanceTable table( { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,0+}" ),
                            id::ChannelID( "n,Cu63->n,Cu63{1,1,0+}" ) },
                          { 1. },
                          { { 2. }, { 3. } } );

    calculator::ReichMoore rlmatrix_constant( BoundaryCondition::Constant,
                                              { capture, elastic } );
    calculator::ReichMoore rlmatrix_shiftfactor( BoundaryCondition::ShiftFactor,
                                                 { capture, elastic } );

    auto calculate_shiftfactor = [&] ( double energy ) {

      double p = elastic.penetrability( energy );
      std::complex< double > r = 9. / std::complex< double >( 1. - energy, -4. );
      std::complex< double > rl = 1. - r * std::complex< double >( 0., p );
      std::complex< double > result = 1. / rl * r;
      return result;
    };

    auto calculate_constant = [&] ( double energy ) {

      double p = elastic.penetrability( energy );
      std::complex< double > r = 9. / std::complex< double >( 1. - energy, -4. );
      std::complex< double > rl = 1. - r * std::complex< double >( elastic.shiftFactor( energy ) + 1., p );
      std::complex< double > result = 1. / rl * r;
      return result;
    };

    // test shift factor boundary condition

    CHECK( 1 == rlmatrix_shiftfactor.r_l_matrix().cols() );
    CHECK( 1 == rlmatrix_shiftfactor.r_l_matrix().rows() );

    double e = 1.;

    auto omega = std::exp( std::complex< double >( 0., -elastic.phaseShift( e ) ) );

    auto matrix = rlmatrix_shiftfactor.r_l_matrix( e, { capture, elastic }, table );
    auto result = calculate_shiftfactor( e );
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_shiftfactor.t_matrix( e, { capture, elastic }, table );
    result = elastic.penetrability( e ) * result;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_shiftfactor.w_matrix( e, { capture, elastic }, table );
    result = 1. + std::complex< double >( 0., 2. ) * result;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_shiftfactor.u_matrix( e, { capture, elastic }, table );
    result = omega * result * omega;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    e = 2.;

    omega = std::exp( std::complex< double >( 0., -elastic.phaseShift( e ) ) );

    matrix = rlmatrix_shiftfactor.r_l_matrix( e, { capture, elastic }, table );
    result = calculate_shiftfactor( e );
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_shiftfactor.t_matrix( e, { capture, elastic }, table );
    result = elastic.penetrability( e ) * result;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_shiftfactor.w_matrix( e, { capture, elastic }, table );
    result = 1. + std::complex< double >( 0., 2. ) * result;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_shiftfactor.u_matrix( e, { capture, elastic }, table );
    result = omega * result * omega;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    // test constant boundary condition

    CHECK( 1 == rlmatrix_constant.r_l_matrix().cols() );
    CHECK( 1 == rlmatrix_constant.r_l_matrix().rows() );

    e = 1.;

    omega = std::exp( std::complex< double >( 0., -elastic.phaseShift( e ) ) );

    matrix = rlmatrix_constant.r_l_matrix( e, { capture, elastic }, table );
    result = calculate_constant( e );
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_constant.t_matrix( e, { capture, elastic }, table );
    result = elastic.penetrability( e ) * result;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_constant.w_matrix( e, { capture, elastic }, table );
    result = 1. + std::complex< double >( 0., 2. ) * result;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_constant.u_matrix( e, { capture, elastic }, table );
    result = omega * result * omega;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    e = 2.;

    omega = std::exp( std::complex< double >( 0., -elastic.phaseShift( e ) ) );

    matrix = rlmatrix_constant.r_l_matrix( e, { capture, elastic }, table );
    result = calculate_constant( e );
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_constant.t_matrix( e, { capture, elastic }, table );
    result = elastic.penetrability( e ) * result;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_constant.w_matrix( e, { capture, elastic }, table );
    result = 1. + std::complex< double >( 0., 2. ) * result;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );

    matrix = rlmatrix_constant.u_matrix( e, { capture, elastic }, table );
    result = omega * result * omega;
    CHECK( 1 == matrix.cols() );
    CHECK( 1 == matrix.rows() );
    CHECK_THAT( result.real(), WithinRel( matrix(0,0).real() ) );
    CHECK_THAT( result.imag(), WithinRel( matrix(0,0).imag() ) );
  } // GIVEN
} // SCENARIO
