#ifndef NJOY_DRYAD_FORMAT_ACE_CREATEPROJECTILETARGETFROMFILE
#define NJOY_DRYAD_FORMAT_ACE_CREATEPROJECTILETARGETFROMFILE

// system includes

// other includes
#include "ACEtk/fromFile.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/format/ace/continuous/createProjectileTarget.hpp"
#include "njoy/dryad/format/ace/electroatomic/createProjectileTarget.hpp"
#include "njoy/dryad/format/ace/photoatomic/createProjectileTarget.hpp"
#include "njoy/dryad/format/ace/photonuclear/createProjectileTarget.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a ProjectileTarget from an ACE file
   *
   *  Most files will produce a single ProjectileTarget. The exception here is the
   *  photoatomic ACE file which may yield one ProjectileTarget (pre-eprdata) or two
   *  ProjectileTarget for eprdata files.
   *
   *  @param[in] filename    the ACE file name
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline std::variant< ProjectileTarget, std::pair< ProjectileTarget, ProjectileTarget > >
  createProjectileTargetFromFile( const std::string& filename, bool normalise ) {

    Log::info( "Reading ACE file \'{}\'", filename );

    auto ace = ACEtk::fromFile( filename );

    auto zaid = std::visit( [] ( auto&& header ) { return header.ZAID(); }, ace.header() );
    switch ( zaid.back() ) {

      case 'p' : {

        ACEtk::PhotoatomicTable table( std::move( ace ) );
        if ( table.electronPhotonRelaxationFormat() > 0 ) {

          return std::make_pair( photoatomic::createProjectileTarget( table, normalise ),
                                 electroatomic::createProjectileTarget( table, normalise ) );
        }
        else {

          return photoatomic::createProjectileTarget( table, normalise );
        }
      }
      case 'u' : {

        ACEtk::PhotonuclearTable table( std::move( ace ) );
        return photonuclear::createProjectileTarget( table, normalise );
      }
      case 'c' :
      case 'h' :
      case 'o' :
      case 'r' :
      case 's' :
      case 'a' : {

        ACEtk::ContinuousEnergyTable table( std::move( ace ) );
        return continuous::createProjectileTarget( table, normalise );
      }
      default : {

        Log::error( "The ACE file type \'{}\' is currently not supported yet" );
        throw std::exception();
      }
    }
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
