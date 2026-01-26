// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/dryad/id/ParticleID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ParticleID = njoy::dryad::id::ParticleID;
using ElementID = njoy::dryad::id::ElementID;
using LevelID = njoy::dryad::id::LevelID;
using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;

SCENARIO( "ParticleID" ) {

  GIVEN( "valid data for a ParticleID" ) {

    THEN( "a ParticleID can be created" ) {

      // original number of registered particles
      std::size_t size = ParticleID::size();

      // all fundamental particles are registered
      CHECK( true == ParticleID::isRegistered( "g" ) );
      CHECK( true == ParticleID::isRegistered( "photon" ) );
      CHECK( true == ParticleID::isRegistered( "gamma" ) );
      CHECK( true == ParticleID::isRegistered( "x-ray" ) );
      CHECK( true == ParticleID::isRegistered( "e-" ) );
      CHECK( true == ParticleID::isRegistered( "electron" ) );
      CHECK( true == ParticleID::isRegistered( "beta-" ) );
      CHECK( true == ParticleID::isRegistered( "e+" ) );
      CHECK( true == ParticleID::isRegistered( "positron" ) );
      CHECK( true == ParticleID::isRegistered( "beta+" ) );
      CHECK( true == ParticleID::isRegistered( "e-_anti" ) );
      CHECK( true == ParticleID::isRegistered( "n" ) );
      CHECK( true == ParticleID::isRegistered( "neutron" ) );
      CHECK( true == ParticleID::isRegistered( "p" ) );
      CHECK( true == ParticleID::isRegistered( "proton" ) );
      CHECK( true == ParticleID::isRegistered( "d" ) );
      CHECK( true == ParticleID::isRegistered( "deuteron" ) );
      CHECK( true == ParticleID::isRegistered( "t" ) );
      CHECK( true == ParticleID::isRegistered( "triton" ) );
      CHECK( true == ParticleID::isRegistered( "h" ) );
      CHECK( true == ParticleID::isRegistered( "helion" ) );
      CHECK( true == ParticleID::isRegistered( "a" ) );
      CHECK( true == ParticleID::isRegistered( "alpha" ) );

      // all other particles are not registered
      CHECK( false == ParticleID::isRegistered( "H1" ) );
      CHECK( false == ParticleID::isRegistered( "H1_e0" ) );
      CHECK( false == ParticleID::isRegistered( "H1_e10" ) );
      CHECK( false == ParticleID::isRegistered( "H1_e150" ) );
      CHECK( false == ParticleID::isRegistered( "H1_e151" ) );
      CHECK( false == ParticleID::isRegistered( "H1[continuum]" ) );
      CHECK( false == ParticleID::isRegistered( "H1[all]" ) );
      CHECK( false == ParticleID::isRegistered( "H2" ) );
      CHECK( false == ParticleID::isRegistered( "H2_e0" ) );
      CHECK( false == ParticleID::isRegistered( "H2_e10" ) );
      CHECK( false == ParticleID::isRegistered( "H2_e150" ) );
      CHECK( false == ParticleID::isRegistered( "H2_e151" ) );
      CHECK( false == ParticleID::isRegistered( "H2[continuum]" ) );
      CHECK( false == ParticleID::isRegistered( "H2[all]" ) );
      CHECK( false == ParticleID::isRegistered( "U236_e10" ) );
      CHECK( false == ParticleID::isRegistered( "H{1s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "H{1s}" ) );
      CHECK( false == ParticleID::isRegistered( "H{1s+}" ) );
      CHECK( false == ParticleID::isRegistered( "H{K}" ) );
      CHECK( false == ParticleID::isRegistered( "He{1s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "He{1s}" ) );
      CHECK( false == ParticleID::isRegistered( "He{1s+}" ) );
      CHECK( false == ParticleID::isRegistered( "He{K}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s1/2,2s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s1/2,2s}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s1/2,2s+}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s1/2,L1}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s,2s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s,2s}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s,2s+}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s,L1}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s+,2s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s+,2s}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s+,2s+}" ) );
      CHECK( false == ParticleID::isRegistered( "O{1s+,L1}" ) );
      CHECK( false == ParticleID::isRegistered( "O{K,2s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "O{K,2s}" ) );
      CHECK( false == ParticleID::isRegistered( "O{K,2s+}" ) );
      CHECK( false == ParticleID::isRegistered( "O{K,L1}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s1/2,2s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s1/2,2s}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s1/2,2s+}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s1/2,L1}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s,2s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s,2s}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s,2s+}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s,L1}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s+,2s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s+,2s}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s+,2s+}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{1s+,L1}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{K,2s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{K,2s}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{K,2s+}" ) );
      CHECK( false == ParticleID::isRegistered( "Fe{K,L1}" ) );
      CHECK( false == ParticleID::isRegistered( "H1" ) );
      CHECK( false == ParticleID::isRegistered( 1001 ) );
      CHECK( false == ParticleID::isRegistered( 1001, 0 ) );
      CHECK( false == ParticleID::isRegistered( 1001, LevelID::continuum ) );
      CHECK( false == ParticleID::isRegistered( 1001, LevelID::all ) );
      CHECK( false == ParticleID::isRegistered( 1002 ) );
      CHECK( false == ParticleID::isRegistered( 1002, 0 ) );
      CHECK( false == ParticleID::isRegistered( 1002, LevelID::continuum ) );
      CHECK( false == ParticleID::isRegistered( 1002, LevelID::all ) );
      CHECK( false == ParticleID::isRegistered( 92236, 10 ) );

      CHECK( size == ParticleID::size() );     // checking for registered particles does not change the size

      ParticleID id( "g" );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "photon" );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "gamma" );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "x-ray" );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::photon();
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "e-" );
      CHECK( "e-" == id.symbol() );
      CHECK( -1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( -1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "electron" );
      CHECK( "e-" == id.symbol() );
      CHECK( -1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( -1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "beta-" );
      CHECK( "e-" == id.symbol() );
      CHECK( -1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( -1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::electron();
      CHECK( "e-" == id.symbol() );
      CHECK( -1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( -1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "e+" );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "positron" );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "beta+" );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "e-_anti" );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::positron();
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "n" );
      CHECK( "n" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "neutron" );
      CHECK( "n" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::neutron();
      CHECK( "n" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "p" );
      CHECK( "p" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "proton" );
      CHECK( "p" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::proton();
      CHECK( "p" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "d" );
      CHECK( "d" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "deuteron" );
      CHECK( "d" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::deuteron();
      CHECK( "d" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "t" );
      CHECK( "t" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1003 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "triton" );
      CHECK( "t" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1003 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::triton();
      CHECK( "t" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1003 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "h" );
      CHECK( "h" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2003 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "helion" );
      CHECK( "h" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2003 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::helion();
      CHECK( "h" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2003 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "a" );
      CHECK( "a" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 4 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2004 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID( "alpha" );
      CHECK( "a" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 4 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2004 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      id = ParticleID::alpha();
      CHECK( "a" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 4 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2004 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size == ParticleID::size() );     // only preregistered identifiers

      id = ParticleID( ElementID( 1 ), 1, LevelID( 0 ) );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 1 == ParticleID::size() ); // H1 is new

      id = ParticleID::nuclide( 1001 );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 1 == ParticleID::size() ); // H1 already registered

      id = ParticleID::nuclide( 1001, 0 );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 1 == ParticleID::size() ); // H1 already registered

      id = ParticleID( "H1" );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 1 == ParticleID::size() ); // H1 already registered

      id = ParticleID( "H1_e0" );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 1 == ParticleID::size() ); // H1 already registered

      id = ParticleID( "H1_e10" );
      CHECK( "H1_e10" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 2 == ParticleID::size() ); // H1_e10 is new

      id = ParticleID::nuclide( 1001, 10 );
      CHECK( "H1_e10" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 2 == ParticleID::size() ); // H1_e10 already registered

      id = ParticleID( ElementID( 1 ), 1, LevelID( 10 ) );
      CHECK( "H1_e10" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 2 == ParticleID::size() ); // H1_e10 already registered

      id = ParticleID( ElementID( 1 ), 1, LevelID::continuum );
      CHECK( "H1[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( LevelID::continuum == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 3 == ParticleID::size() ); // H1[continuum] is new

      id = ParticleID::nuclide( 1001, LevelID::continuum );
      CHECK( "H1[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( LevelID::continuum == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 3 == ParticleID::size() ); // H1[continuum] already registered

      id = ParticleID( "H1[continuum]" );
      CHECK( "H1[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( LevelID::continuum == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 3 == ParticleID::size() ); // H1[continuum] already registered

      id = ParticleID( "H1_e150" );
      CHECK( "H1[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( LevelID::continuum == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 3 == ParticleID::size() ); // H1[continuum] already registered

      id = ParticleID( "H2[continuum]" );
      CHECK( "H2[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( LevelID::continuum == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 4 == ParticleID::size() ); // H2[continuum] is new

      id = ParticleID::nuclide( 1002, LevelID::continuum );
      CHECK( "H2[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( LevelID::continuum == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 4 == ParticleID::size() ); // H2[continuum] already registered

      id = ParticleID( ElementID( 1 ), 2, LevelID::continuum );
      CHECK( "H2[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( LevelID::continuum == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 4 == ParticleID::size() ); // H2[continuum] already registered

      id = ParticleID( "H2_e150" );
      CHECK( "H2[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( LevelID::continuum == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 4 == ParticleID::size() ); // H2[continuum] already registered

      id = ParticleID( ElementID( 1 ), 1, LevelID::all );
      CHECK( "H1[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( LevelID::all == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 5 == ParticleID::size() ); // H1[all] is new

      id = ParticleID::nuclide( 1001, LevelID::all );
      CHECK( "H1[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( LevelID::all == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 5 == ParticleID::size() ); // H1[all] already registered

      id = ParticleID( "H1[all]" );
      CHECK( "H1[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( LevelID::all == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 5 == ParticleID::size() ); // H1[all] already registered

      id = ParticleID( "H1_e151" );
      CHECK( "H1[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( LevelID::all == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 5 == ParticleID::size() ); // H1[all] already registered

      id = ParticleID( "H2[all]" );
      CHECK( "H2[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( LevelID::all == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 6 == ParticleID::size() ); // H2[all] is new

      id = ParticleID::nuclide( 1002, LevelID::all );
      CHECK( "H2[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( LevelID::all == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 6 == ParticleID::size() ); // H2[all] already registered

      id = ParticleID( ElementID( 1 ), 2, LevelID::all );
      CHECK( "H2[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( LevelID::all == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 6 == ParticleID::size() ); // H2[all] already registered

      id = ParticleID( "H2_e151" );
      CHECK( "H2[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( LevelID::all == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 6 == ParticleID::size() ); // H2[all] already registered

      id = ParticleID::nuclide( 92236, 10 );
      CHECK( "U236_e10" == id.symbol() );
      CHECK( 92 == id.z() );
      CHECK( 236 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 92236 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 7 == ParticleID::size() ); // U235_e10 is new

      id = ParticleID( "U236_e10" );
      CHECK( "U236_e10" == id.symbol() );
      CHECK( 92 == id.z() );
      CHECK( 236 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 92236 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 7 == ParticleID::size() ); // U235_e10 already registered

      id = ParticleID( ElementID( 92 ), 236, LevelID( 10 ) );
      CHECK( "U236_e10" == id.symbol() );
      CHECK( 92 == id.z() );
      CHECK( 236 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 92236 == id.za() );
      CHECK( std::nullopt == id.vacancies() );

      CHECK( size + 7 == ParticleID::size() ); // U235_e10 already registered

      id = ParticleID( ElementID( 1 ), ElectronSubshellID( "K" ) );
      CHECK( "H{1s1/2}" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 8 == ParticleID::size() ); // registering H{1s1/2} using integers

      id = ParticleID( "H{1s1/2}" );
      CHECK( "H{1s1/2}" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 8 == ParticleID::size() ); // H{1s1/2} already registered

      id = ParticleID( "H{1s}" );
      CHECK( "H{1s1/2}" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 8 == ParticleID::size() ); // H{1s1/2} already registered

      id = ParticleID( "H{1s+}" );
      CHECK( "H{1s1/2}" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 8 == ParticleID::size() ); // H{1s1/2} already registered

      id = ParticleID( "H{K}" );
      CHECK( "H{1s1/2}" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 8 == ParticleID::size() ); // H{1s1/2} already registered

      id = ParticleID( "He{1s1/2}" );
      CHECK( "He{1s1/2}" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 9 == ParticleID::size() ); // registering He{1s1/2} using a string

      id = ParticleID( "He{1s}" );
      CHECK( "He{1s1/2}" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 9 == ParticleID::size() ); // He{1s1/2} already registered

      id = ParticleID( "He{1s+}" );
      CHECK( "He{1s1/2}" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 9 == ParticleID::size() ); // He{1s1/2} already registered

      id = ParticleID( "He{K}" );
      CHECK( "He{1s1/2}" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 9 == ParticleID::size() ); // He{1s1/2} already registered

      id = ParticleID( ElementID( 2 ), ElectronSubshellID( "K" ) );
      CHECK( "He{1s1/2}" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ) } == id.vacancies() );

      CHECK( size + 9 == ParticleID::size() ); // He{1s1/2} already registered

      id = ParticleID( ElementID( 8 ), { ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // registering O{1s1/2,2s1/2}

      id = ParticleID( "O{1s1/2,2s1/2}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s1/2,2s}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s1/2,2s+}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s1/2,L1}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s,2s1/2}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s,2s}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s,2s+}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s,L1}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s+,2s1/2}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered
      id = ParticleID( "O{1s+,2s}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{1s+,2s+}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered
      id = ParticleID( "O{1s+,L1}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{K,2s1/2}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{K,2s}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{K,2s+}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "O{K,L1}" );
      CHECK( "O{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 8 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 8000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 10 == ParticleID::size() ); // O{1s1/2,2s1/2} already registered

      id = ParticleID( "Fe{K,L1}" );
      CHECK( "Fe{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 26 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 26000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 11 == ParticleID::size() ); // registering Fe{1s1/2,2s1/2}

      id = ParticleID( ElementID( 26 ), { ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } );
      CHECK( "Fe{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 26 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 26000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 11 == ParticleID::size() ); // Fe{1s1/2,2s1/2} already registered

      id = ParticleID( "Fe{1s1/2,2s1/2}" );
      CHECK( "Fe{1s1/2,2s1/2}" == id.symbol() );
      CHECK( 26 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 26000 == id.za() );
      CHECK( std::vector< ElectronSubshellID >{ ElectronSubshellID( "K" ), ElectronSubshellID( "L1" ) } == id.vacancies() );

      CHECK( size + 11 == ParticleID::size() ); // Fe{1s1/2,2s1/2} already registered

      // we're not testing all combination for iron to check that they actually were
      // properly registered (see below)

      // all other particles are now registered
      CHECK( true == ParticleID::isRegistered( "H1" ) );
      CHECK( true == ParticleID::isRegistered( "H1_e0" ) );
      CHECK( true == ParticleID::isRegistered( "H1_e10" ) );
      CHECK( true == ParticleID::isRegistered( "H1_e150" ) );
      CHECK( true == ParticleID::isRegistered( "H1_e151" ) );
      CHECK( true == ParticleID::isRegistered( "H1[continuum]" ) );
      CHECK( true == ParticleID::isRegistered( "H1[all]" ) );
      CHECK( true == ParticleID::isRegistered( "H2_e150" ) );
      CHECK( true == ParticleID::isRegistered( "H2_e151" ) );
      CHECK( true == ParticleID::isRegistered( "H2[continuum]" ) );
      CHECK( true == ParticleID::isRegistered( "H2[all]" ) );
      CHECK( true == ParticleID::isRegistered( "U236_e10" ) );
      CHECK( true == ParticleID::isRegistered( "H{1s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "H{1s}" ) );
      CHECK( true == ParticleID::isRegistered( "H{1s+}" ) );
      CHECK( true == ParticleID::isRegistered( "H{K}" ) );
      CHECK( true == ParticleID::isRegistered( "He{1s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "He{1s}" ) );
      CHECK( true == ParticleID::isRegistered( "He{1s+}" ) );
      CHECK( true == ParticleID::isRegistered( "He{K}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s1/2,2s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s1/2,2s}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s1/2,2s+}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s1/2,L1}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s,2s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s,2s}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s,2s+}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s,L1}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s+,2s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s+,2s}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s+,2s+}" ) );
      CHECK( true == ParticleID::isRegistered( "O{1s+,L1}" ) );
      CHECK( true == ParticleID::isRegistered( "O{K,2s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "O{K,2s}" ) );
      CHECK( true == ParticleID::isRegistered( "O{K,2s+}" ) );
      CHECK( true == ParticleID::isRegistered( "O{K,L1}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s1/2,2s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s1/2,2s}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s1/2,2s+}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s1/2,L1}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s,2s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s,2s}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s,2s+}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s,L1}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s+,2s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s+,2s}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s+,2s+}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{1s+,L1}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{K,2s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{K,2s}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{K,2s+}" ) );
      CHECK( true == ParticleID::isRegistered( "Fe{K,L1}" ) );
      CHECK( true == ParticleID::isRegistered( "H1" ) );
      CHECK( true == ParticleID::isRegistered( 1001 ) );
      CHECK( true == ParticleID::isRegistered( 1001, 0 ) );
      CHECK( true == ParticleID::isRegistered( 1001, LevelID::continuum ) );
      CHECK( true == ParticleID::isRegistered( 1001, LevelID::all ) );
      CHECK( true == ParticleID::isRegistered( 1002, LevelID::continuum ) );
      CHECK( true == ParticleID::isRegistered( 1002, LevelID::all ) );
      CHECK( true == ParticleID::isRegistered( 92236, 10 ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid ParticleID instances" ) {

    ParticleID fundamental( "n" );
    ParticleID element( "H" );
    ParticleID ion( "H{1s1/2}" );
    ParticleID nuclide( "H1" );
    ParticleID excited( "H1_e1" );
    ParticleID continuum( "H1[continuum]" );
    ParticleID all( "H1[all]" );
    ParticleID next( "He" );

    THEN( "the ordering is respected" ) {

      CHECK( fundamental < element );
      CHECK( element < ion );
      CHECK( ion < nuclide );
      CHECK( nuclide < excited );
      CHECK( excited < continuum );
      CHECK( continuum < all );
      CHECK( all < next );
    }

    ParticleID id1( "U235" );
    ParticleID id2( "U235_e10" );

    THEN( "instances can be compared" ) {

      CHECK( ( id1 <  id1 ) == false );
      CHECK( ( id1 <= id1 ) == true );
      CHECK( ( id1 >  id1 ) == false );
      CHECK( ( id1 >= id1 ) == true );
      CHECK( ( id1 == id1 ) == true );
      CHECK( ( id1 != id1 ) == false );
      CHECK( ( id1 <  id2 ) == true );
      CHECK( ( id1 <= id2 ) == true );
      CHECK( ( id1 >  id2 ) == false );
      CHECK( ( id1 >= id2 ) == false );
      CHECK( ( id1 == id2 ) == false );
      CHECK( ( id1 != id2 ) == true );
      CHECK( ( id2 <  id1 ) == false );
      CHECK( ( id2 <= id1 ) == false );
      CHECK( ( id2 >  id1 ) == true );
      CHECK( ( id2 >= id1 ) == true );
      CHECK( ( id2 == id1 ) == false );
      CHECK( ( id2 != id1 ) == true );
    } // THEN

    THEN( "instances can be used as keys in a std::map" ) {

      std::map< ParticleID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ParticleID( "U235" ) ] == "1" );
      CHECK( map[ ParticleID( "U235_e10" ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< ParticleID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ParticleID( "U235" ) ] == "1" );
      CHECK( map[ ParticleID( "U235_e10" ) ] == "2" );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a ParticleID" ) {

    THEN( "an exception is thrown" ) {

      CHECK_THROWS( ParticleID( "not a particle symbol" ) );
      CHECK_THROWS( ParticleID( "H_e0" ) );
      CHECK_THROWS( ParticleID( "H_e1" ) );
      CHECK_THROWS( ParticleID( "H1_e152" ) );
      CHECK_THROWS( ParticleID( "H{4p}" ) );   // non-relativistic vacancy is not allowed
    } // THEN
  } // GIVEN
} // SCENARIO
