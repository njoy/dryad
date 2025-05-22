// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/ParticleID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ParticleID = njoy::dryad::id::ParticleID;

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
      CHECK( false == ParticleID::isRegistered( "H{K}" ) );
      CHECK( false == ParticleID::isRegistered( "He{1s1/2}" ) );
      CHECK( false == ParticleID::isRegistered( "He{K}" ) );
      CHECK( false == ParticleID::isRegistered( "H1" ) );
      CHECK( false == ParticleID::isRegistered( 1001 ) );
      CHECK( false == ParticleID::isRegistered( 1001, 0 ) );
      CHECK( false == ParticleID::isRegistered( 1001, njoy::dryad::id::LevelID::continuum ) );
      CHECK( false == ParticleID::isRegistered( 1001, njoy::dryad::id::LevelID::all ) );
      CHECK( false == ParticleID::isRegistered( 1002 ) );
      CHECK( false == ParticleID::isRegistered( 1002, 0 ) );
      CHECK( false == ParticleID::isRegistered( 1002, njoy::dryad::id::LevelID::continuum ) );
      CHECK( false == ParticleID::isRegistered( 1002, njoy::dryad::id::LevelID::all ) );
      CHECK( false == ParticleID::isRegistered( 92236, 10 ) );
      CHECK( false == ParticleID::isRegistered( 1000, njoy::dryad::id::ElectronSubshellID::K ) );
      CHECK( false == ParticleID::isRegistered( 2000, njoy::dryad::id::ElectronSubshellID::K ) );

      CHECK( size == ParticleID::size() );     // checking for registered particles does not change the size

      ParticleID id( "g" );
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "photon" );
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "gamma" );
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "x-ray" );
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::photon();
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 0 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "e-" );
      CHECK( 1 == id.number() );
      CHECK( "e-" == id.symbol() );
      CHECK( -1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( -1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "electron" );
      CHECK( 1 == id.number() );
      CHECK( "e-" == id.symbol() );
      CHECK( -1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( -1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "beta-" );
      CHECK( 1 == id.number() );
      CHECK( "e-" == id.symbol() );
      CHECK( -1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( -1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::electron();
      CHECK( 1 == id.number() );
      CHECK( "e-" == id.symbol() );
      CHECK( -1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( -1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "e+" );
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "positron" );
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "beta+" );
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "e-_anti" );
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::positron();
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "n" );
      CHECK( 10 == id.number() );
      CHECK( "n" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "neutron" );
      CHECK( 10 == id.number() );
      CHECK( "n" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::neutron();
      CHECK( 10 == id.number() );
      CHECK( "n" == id.symbol() );
      CHECK( 0 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "p" );
      CHECK( 1001 == id.number() );
      CHECK( "p" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "proton" );
      CHECK( 1001 == id.number() );
      CHECK( "p" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::proton();
      CHECK( 1001 == id.number() );
      CHECK( "p" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "d" );
      CHECK( 1002 == id.number() );
      CHECK( "d" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "deuteron" );
      CHECK( 1002 == id.number() );
      CHECK( "d" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::deuteron();
      CHECK( 1002 == id.number() );
      CHECK( "d" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "t" );
      CHECK( 1003 == id.number() );
      CHECK( "t" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1003 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "triton" );
      CHECK( 1003 == id.number() );
      CHECK( "t" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1003 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::triton();
      CHECK( 1003 == id.number() );
      CHECK( "t" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1003 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "h" );
      CHECK( 2003 == id.number() );
      CHECK( "h" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2003 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "helion" );
      CHECK( 2003 == id.number() );
      CHECK( "h" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2003 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::helion();
      CHECK( 2003 == id.number() );
      CHECK( "h" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 3 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2003 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "a" );
      CHECK( 2004 == id.number() );
      CHECK( "a" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 4 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2004 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID( "alpha" );
      CHECK( 2004 == id.number() );
      CHECK( "a" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 4 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2004 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      id = ParticleID::alpha();
      CHECK( 2004 == id.number() );
      CHECK( "a" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 4 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2004 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size == ParticleID::size() );     // only preregistered identifiers

      id = ParticleID( 1001, 0 );
      CHECK( 1001000 == id.number() );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 1 == ParticleID::size() ); // registering H1 using integers

      id = ParticleID( 1001 );
      CHECK( 1001000 == id.number() );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 1 == ParticleID::size() ); // H1 already registered

      id = ParticleID( "H1" );
      CHECK( 1001000 == id.number() );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 1 == ParticleID::size() ); // H1 already registered

      id = ParticleID( "H1_e0" );
      CHECK( 1001000 == id.number() );
      CHECK( "H1" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 1 == ParticleID::size() ); // H1 already registered

      id = ParticleID( "H1_e10" );
      CHECK( 1001010 == id.number() );
      CHECK( "H1_e10" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 2 == ParticleID::size() ); // registering H1_e10 using a string

      id = ParticleID( 1001, 10 );
      CHECK( 1001010 == id.number() );
      CHECK( "H1_e10" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 2 == ParticleID::size() ); // H1_e10 already registered

      id = ParticleID( 1001, njoy::dryad::id::LevelID::continuum );
      CHECK( 1001150 == id.number() );
      CHECK( "H1[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( njoy::dryad::id::LevelID::continuum == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 3 == ParticleID::size() ); // registering H1[continuum] using integers

      id = ParticleID( "H1[continuum]" );
      CHECK( 1001150 == id.number() );
      CHECK( "H1[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( njoy::dryad::id::LevelID::continuum == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 3 == ParticleID::size() ); // H1[continuum] already registered

      id = ParticleID( "H1_e150" );
      CHECK( 1001150 == id.number() );
      CHECK( "H1[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( njoy::dryad::id::LevelID::continuum == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 3 == ParticleID::size() ); // H1[continuum] already registered

      id = ParticleID( "H2[continuum]" );
      CHECK( 1002150 == id.number() );
      CHECK( "H2[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( njoy::dryad::id::LevelID::continuum == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 4 == ParticleID::size() ); // registering H2[continuum] as a string

      id = ParticleID( 1002, njoy::dryad::id::LevelID::continuum );
      CHECK( 1002150 == id.number() );
      CHECK( "H2[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( njoy::dryad::id::LevelID::continuum == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 4 == ParticleID::size() ); // H2[continuum] already registered

      id = ParticleID( "H2_e150" );
      CHECK( 1002150 == id.number() );
      CHECK( "H2[continuum]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( njoy::dryad::id::LevelID::continuum == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 4 == ParticleID::size() ); // H2[continuum] already registered

      id = ParticleID( 1001, njoy::dryad::id::LevelID::all );
      CHECK( 1001151 == id.number() );
      CHECK( "H1[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( njoy::dryad::id::LevelID::all == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 5 == ParticleID::size() ); // registering H1[all] using integers

      id = ParticleID( "H1[all]" );
      CHECK( 1001151 == id.number() );
      CHECK( "H1[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( njoy::dryad::id::LevelID::all == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 5 == ParticleID::size() ); // H1[all] already registered

      id = ParticleID( "H1_e151" );
      CHECK( 1001151 == id.number() );
      CHECK( "H1[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 1 == id.a() );
      CHECK( njoy::dryad::id::LevelID::all == id.e() );
      CHECK( 1001 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 5 == ParticleID::size() ); // H1[all] already registered

      id = ParticleID( "H2[all]" );
      CHECK( 1002151 == id.number() );
      CHECK( "H2[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( njoy::dryad::id::LevelID::all == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 6 == ParticleID::size() ); // registering H2[all] as a string

      id = ParticleID( 1002, njoy::dryad::id::LevelID::all );
      CHECK( 1002151 == id.number() );
      CHECK( "H2[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( njoy::dryad::id::LevelID::all == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 6 == ParticleID::size() ); // H2[all] already registered

      id = ParticleID( "H2_e151" );
      CHECK( 1002151 == id.number() );
      CHECK( "H2[all]" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 2 == id.a() );
      CHECK( njoy::dryad::id::LevelID::all == id.e() );
      CHECK( 1002 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 6 == ParticleID::size() ); // H2[continuum] already registered

      id = ParticleID( "U236_e10" );
      CHECK( 92236010 == id.number() );
      CHECK( "U236_e10" == id.symbol() );
      CHECK( 92 == id.z() );
      CHECK( 236 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 92236 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 7 == ParticleID::size() ); // registering U235_e10 as a string

      id = ParticleID( 92236, 10 );
      CHECK( 92236010 == id.number() );
      CHECK( "U236_e10" == id.symbol() );
      CHECK( 92 == id.z() );
      CHECK( 236 == id.a() );
      CHECK( 10 == id.e() );
      CHECK( 92236 == id.za() );
      CHECK( std::nullopt == id.subshell() );

      CHECK( size + 7 == ParticleID::size() ); // U235_e10 already registered

      id = ParticleID( 1000, njoy::dryad::id::ElectronSubshellID::K );
      CHECK( 1000534 == id.number() );
      CHECK( "H{1s1/2}" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( njoy::dryad::id::ElectronSubshellID::K == id.subshell() );

      CHECK( size + 8 == ParticleID::size() ); // registering H{1s1/2} using integers

      id = ParticleID( "H{1s1/2}" );
      CHECK( 1000534 == id.number() );
      CHECK( "H{1s1/2}" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( njoy::dryad::id::ElectronSubshellID::K == id.subshell() );

      CHECK( size + 8 == ParticleID::size() ); // H{1s1/2} already registered

      id = ParticleID( "H{K}" );
      CHECK( 1000534 == id.number() );
      CHECK( "H{1s1/2}" == id.symbol() );
      CHECK( 1 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 1000 == id.za() );
      CHECK( njoy::dryad::id::ElectronSubshellID::K == id.subshell() );

      CHECK( size + 8 == ParticleID::size() ); // H{1s1/2} already registered

      id = ParticleID( "He{1s1/2}" );
      CHECK( 2000534 == id.number() );
      CHECK( "He{1s1/2}" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2000 == id.za() );
      CHECK( njoy::dryad::id::ElectronSubshellID::K == id.subshell() );

      CHECK( size + 9 == ParticleID::size() ); // registering He{1s1/2} using a string

      id = ParticleID( "He{K}" );
      CHECK( 2000534 == id.number() );
      CHECK( "He{1s1/2}" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2000 == id.za() );
      CHECK( njoy::dryad::id::ElectronSubshellID::K == id.subshell() );

      CHECK( size + 9 == ParticleID::size() ); // He{1s1/2} already registered

      id = ParticleID( 2000, njoy::dryad::id::ElectronSubshellID::K );
      CHECK( 2000534 == id.number() );
      CHECK( "He{1s1/2}" == id.symbol() );
      CHECK( 2 == id.z() );
      CHECK( 0 == id.a() );
      CHECK( 0 == id.e() );
      CHECK( 2000 == id.za() );
      CHECK( njoy::dryad::id::ElectronSubshellID::K == id.subshell() );

      CHECK( size + 9 == ParticleID::size() ); // He{1s1/2} already registered

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
      CHECK( true == ParticleID::isRegistered( "H{K}" ) );
      CHECK( true == ParticleID::isRegistered( "He{1s1/2}" ) );
      CHECK( true == ParticleID::isRegistered( "He{K}" ) );
      CHECK( true == ParticleID::isRegistered( "H1" ) );
      CHECK( true == ParticleID::isRegistered( 1001 ) );
      CHECK( true == ParticleID::isRegistered( 1001, 0 ) );
      CHECK( true == ParticleID::isRegistered( 1001, njoy::dryad::id::LevelID::continuum ) );
      CHECK( true == ParticleID::isRegistered( 1001, njoy::dryad::id::LevelID::all ) );
      CHECK( true == ParticleID::isRegistered( 1002, njoy::dryad::id::LevelID::continuum ) );
      CHECK( true == ParticleID::isRegistered( 1002, njoy::dryad::id::LevelID::all ) );
      CHECK( true == ParticleID::isRegistered( 92236, 10 ) );
      CHECK( true == ParticleID::isRegistered( 1000, njoy::dryad::id::ElectronSubshellID::K ) );
      CHECK( true == ParticleID::isRegistered( 2000, njoy::dryad::id::ElectronSubshellID::K ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid ParticleID instances" ) {

    ParticleID id1( 92235 );
    ParticleID id2( 92235, 10 );

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
      CHECK( map[ ParticleID( 92235 ) ] == "1" );
      CHECK( map[ ParticleID( 92235, 10 ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< ParticleID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ParticleID( 92235 ) ] == "1" );
      CHECK( map[ ParticleID( 92235, 10 ) ] == "2" );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a ParticleID" ) {

    THEN( "an exception is thrown" ) {

      CHECK_THROWS( ParticleID( "not a particle symbol" ) );
      CHECK_THROWS( ParticleID( -1000 ) );
      CHECK_THROWS( ParticleID( 1000, 1 ) );
      CHECK_THROWS( ParticleID( 1000, njoy::dryad::id::LevelID::continuum ) );
      CHECK_THROWS( ParticleID( 1000, njoy::dryad::id::LevelID::all ) );
      CHECK_THROWS( ParticleID( 1000, 152 ) );
      CHECK_THROWS( ParticleID( 1001, -1 ) );
      CHECK_THROWS( ParticleID( 1001, 152 ) );
      CHECK_THROWS( ParticleID( "H_e0" ) );
      CHECK_THROWS( ParticleID( "H_e1" ) );
      CHECK_THROWS( ParticleID( "H1_e152" ) );
      CHECK_THROWS( ParticleID( 1000, 533 ) );
      CHECK_THROWS( ParticleID( 1000, 581 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
