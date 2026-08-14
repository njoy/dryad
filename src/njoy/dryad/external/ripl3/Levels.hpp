#ifndef NJOY_DRYAD_EXTERNAL_RIPL3_LEVELS
#define NJOY_DRYAD_EXTERNAL_RIPL3_LEVELS

// system includes
#include <map>

#if __has_include(<filesystem>) && (defined(_MSVC_LANG) ? (_MSVC_LANG >= 201703L) : (__cplusplus >= 201703L))
#include <filesystem>
namespace filesystem = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;
#endif

// other includes
#include "tools/Log.hpp"
#include "tools/disco.hpp"
#include "njoy/configuration.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/external/ripl3/LevelEntry.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace external {
namespace ripl3 {

  /**
   *  @class
   *  @brief RIPL-3 level data
   *
   *  The Levels class allows a user to interact with the nuclear levels part of the RIPL-3
   *  database.
   *
   *  While elementary particles (g, n, p, d, t, h, a) are not included in RIPL-3, their spin
   *  and parity information has been added.
   */
  class Levels {

    /* fields */

    static inline std::optional< std::string > ripl3_levels_datapath_;

    static inline std::map< id::ParticleID, LevelEntry > levels_ = {

      { id::ParticleID::photon(), { id::ParticleID::photon(), std::nullopt, 1.0, -1, std::nullopt } },
      { id::ParticleID::electron(), { id::ParticleID::electron(), std::nullopt, std::nullopt, std::nullopt, std::nullopt } },
      { id::ParticleID::positron(), { id::ParticleID::positron(), std::nullopt, std::nullopt, std::nullopt, std::nullopt } },
      { id::ParticleID::neutron(), { id::ParticleID::neutron(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::proton(), { id::ParticleID::proton(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::deuteron(), { id::ParticleID::deuteron(), std::nullopt, 1.0, 1, std::nullopt } },
      { id::ParticleID::triton(), { id::ParticleID::triton(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::helion(), { id::ParticleID::helion(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::alpha(), { id::ParticleID::alpha(), std::nullopt, 0.0, 1, std::nullopt } }
    };

    /* auxiliary functions */

    static auto iterator( const id::ParticleID& id ) {

      auto iter = Levels::levels_.find( id );
      if ( iter == Levels::levels_.end() ) {

        if ( id.a() != 0 ) {

          iter = std::lower_bound( Levels::levels_.begin(), Levels::levels_.end(),
                                   id.z(),
                                   [] ( auto&& left, auto&& right )
                                      { return left.first.z() < right; } );
          if ( iter == Levels::levels_.end() || iter->first != id ) {

            Levels::loadData( id.z() );
            iter = Levels::levels_.find( id );
          }
        }
      }

      return iter;
    }

    static void loadData( int z ) {

      // set the absolute datapath if we haven't already
      if ( ! Levels::ripl3_levels_datapath_.has_value() ) {

        std::string config = configuration().get( "ripl3_levels" );
        filesystem::path path( config );
        if ( ! path.is_absolute() ) {

          path = filesystem::path( datapath() );
          path /= config;
        }
        Levels::ripl3_levels_datapath_ = path.string();
      }

      // open the ripl-3 file
      filesystem::path path( ripl3_levels_datapath_.value() );
      std::string file = z < 10 ? "z00" : z < 100 ? "z0" : "z";
      file += std::to_string( z ) + ".dat";
      path /= file;

      std::ifstream in( path.c_str(),
                        std::ios::in | std::ios::binary | std::ios::ate );
      if ( not in ) {

        Log::error( "Could not open file \'{}\'", path.string() );
        throw std::exception();
      }

      const auto file_size = in.tellg();
      in.seekg( 0, std::ios::beg );
      file.clear();
      file.resize( file_size / sizeof( char ) );
      in.read( &( file[ 0 ] ), file_size );


      // fortran statements
      using namespace njoy::tools::disco;
      using Identification = Record< Character< 5 >, Integer< 5 >, Integer< 5 >, Integer< 5 >,
                                     Integer< 5 >, Integer< 5 >, Integer< 5 >, Real< 12 >, Real< 12 > >;
      using Level = Record< Integer< 3 >, Column< 1 >, Real< 10 >, Column< 1 >, Real< 5 >,
                            Integer< 3 >, Column< 1 >, Real< 10 >, Integer< 3 > >;
      using Gamma = Record< Column< 39 >, Integer< 4 >, Column< 1 >, Real< 10 >,
                            Column< 1 >, Real< 10 >, Column< 1 >, Real< 10 >,
                            Column< 1 >, Real< 10 > >;

      // parse the file and get the data we need
      auto begin = file.begin();
      auto end = file.end();
      while ( begin != end ) {

        std::string symb;
        int a, z, Nol, Nog, Nmax, Nc;
        double Sn, Sp;
        Identification::read( begin, end, symb, a, z, Nol, Nog, Nmax, Nc, Sn, Sp );

        int za = z * 1000 + a;
        Sn *= constants::mega;
        Sp *= constants::mega;

        if ( Nol < 0 ) {

          Log::error( "Number of levels for isotope {} in ripl-3 levels file is less than zero", symb );
          throw std::exception();
        }

        std::size_t number_levels = static_cast< std::size_t >( Nol );
        for ( std::size_t i = 0; i < number_levels; ++i ) {

          int N1, p, Ng;
          double Elv, s, Thalf;
          Level::read( begin, end, N1, Elv, s, p, Thalf, Ng );

          id::ParticleID particle = id::ParticleID::nuclide( za, N1 - 1 );
          Elv *= constants::mega;

          if ( Ng < 0 ) {

            Log::error( "Number of gammas for isotope {} and level index {} in ripl-3 levels file is less than zero", symb, N1 );
            throw std::exception();
          }

          std::size_t number_gammas = static_cast< std::size_t >( Ng );
          for ( std::size_t j = 0; j < number_gammas; ++j ) {

            int Nf;
            double Eg, Pg, Pe, ICC;
            Gamma::read( begin, end, Nf, Eg, Pg, Pe, ICC );
          }

          Levels::levels_[ particle ] = { particle, Elv,
                                          s < 0 ? std::nullopt : std::make_optional( s ),
                                          p == 0 ? std::nullopt : std::make_optional( p ),
                                          Thalf < 0 ? std::nullopt : std::make_optional( Thalf ) };
        }
      }
    }

  public:

    /* methods */

    /**
     *  @brief Return the current size of the RIPL-3 levels data
     */
    static std::size_t size() {

      return Levels::levels_.size();
    }

    /**
     *  @brief Verify whether or not a given particle is present
     *
     *  @param[in] id   the particle identifier
     */
    static bool hasEntry( const id::ParticleID& id ) {

      return iterator( id ) != Levels::levels_.end();
    }

    /**
     *  @brief Retrieve a level entry for a given particle
     *
     *  @param[in] id   the particle identifier
     */
    static const LevelEntry& entry( const id::ParticleID& id ) {

      auto iter = iterator( id );
      if ( iter == Levels::levels_.end() ) {

        throw std::out_of_range( "Particle not found in RIPL-3 levels database" );
      }
      return iter->second;
    }
  };

} // ripl3 namespace
} // external namespace
} // dryad namespace
} // njoy namespace

#endif
