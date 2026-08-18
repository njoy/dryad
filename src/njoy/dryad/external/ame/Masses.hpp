#ifndef NJOY_DRYAD_EXTERNAL_AME_MASSES
#define NJOY_DRYAD_EXTERNAL_AME_MASSES

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
#include "njoy/dryad/external/ame/MassEntry.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace external {
namespace ame {

  /**
   *  @class
   *  @brief Atomic mass data from AME2020
   *
   *  The Masses class allows a user to interact with the AME2020 mass data.
   */
  class Masses {

    /* fields */

    static inline std::map< id::ParticleID, MassEntry > masses_;

    /* auxiliary functions */

    static auto iterator( const id::ParticleID& id ) {

      // the id can be for an excited state while the ame data is for
      // ground states only.

      auto iter = Masses::masses_.find( id.groundState() );
      if ( iter == Masses::masses_.end() ) {

        if ( Masses::size() == 0 ) {

          Masses::loadData();
          iter = Masses::masses_.find( id.groundState() );
        }
      }

      return iter;
    }

    static void loadData() {

      std::string config = configuration().get( "ame2020" );
      filesystem::path path( config );
      if ( ! path.is_absolute() ) {

        path = filesystem::path( datapath() );
        path /= config;
      }

      std::ifstream in( path.c_str(),
                        std::ios::in | std::ios::binary | std::ios::ate );
      if ( not in ) {

        Log::error( "Could not open file \'{}\'", path.string() );
        throw std::exception();
      }

      const auto file_size = in.tellg();
      in.seekg( 0, std::ios::beg );
      std::string file;
      file.resize( file_size / sizeof( char ) );
      in.read( &( file[ 0 ] ), file_size );

      // fortran statements
      using namespace njoy::tools::disco;
      using Entry = Record< Column< 9 >, Integer< 5 >, Integer< 5 >, Column< 9 >,
                            Real< 14 >, Real< 12 >, Real< 13 >, Column< 1 >, Real< 10 >,
                            Column< 3 >, Character< 24 >,
                            Column< 1 >, Integer< 3 >, Column< 1 >, Real< 13 >, Real< 12 > >;
      using Beta = Record< Real< 13 >, Real< 11 > >;

      // parse the file and get the data we need
      auto begin = file.begin();
      auto end = file.end();

      // skip 38 lines (skip past the neutron data)
      for ( std::size_t i = 0; i < 37; ++i ) {

        begin = std::find( begin, end, '\n' );
        ++begin;
      }
      std::replace( begin, end, '#', ' ' );

      // read all entries
      while ( begin != end ) {

        int z, a, m;
        double excess, binding, beta, mass;
        double unc_excess, unc_binding, unc_beta, unc_mass;
        std::string beta_string;
        Entry::read( begin, end, z, a, excess, unc_excess, binding, unc_binding,
                     beta_string, m, mass, unc_mass );

        int za = z * 1000 + a;
        excess *= constants::kilo;
        unc_excess *= constants::kilo;
        binding *= constants::kilo;
        unc_binding *= constants::kilo;
        mass = m + mass * constants::micro;
        unc_mass *= constants::micro;

        bool has_beta = std::find( beta_string.begin(), beta_string.end(), '*' ) == beta_string.end();
        if ( has_beta ) {

          auto iter = beta_string.begin();
          Beta::read( iter, beta_string.end(), beta, unc_beta );
          beta *= constants::kilo;
          unc_beta *= constants::kilo;
        }

        id::ParticleID particle = id::ParticleID::nuclide( za, 0 );
        Masses::masses_[ particle ] = { particle,
                                        excess, unc_excess, binding, unc_binding,
                                        has_beta ? std::make_optional( beta ) : std::nullopt,
                                        has_beta ? std::make_optional( unc_beta ) : std::nullopt,
                                        mass, unc_mass };
      }
    }

  public:

    /* methods */

    /**
     *  @brief Return the current size of the AME2020 mass data
     */
    static std::size_t size() {

      return Masses::masses_.size();
    }

    /**
     *  @brief Verify whether or not a given particle is present
     *
     *  @param[in] id   the particle identifier
     */
    static bool hasEntry( const id::ParticleID& id ) {

      return iterator( id ) != Masses::masses_.end();
    }

    /**
     *  @brief Retrieve a mass entry for a given particle
     *
     *  @param[in] id   the particle identifier
     */
    static const MassEntry& entry( const id::ParticleID& id ) {

      auto iter = iterator( id );
      if ( iter == Masses::masses_.end() ) {

        throw std::out_of_range( "Particle not found in the AME2020 masses" );
      }
      return iter->second;
    }
  };

} // ripl3 namespace
} // external namespace
} // dryad namespace
} // njoy namespace

#endif
