#ifndef NJOY_DRYAD_FORMAT_ACE_CREATEPROJECTILETARGETFROMFILE
#define NJOY_DRYAD_FORMAT_ACE_CREATEPROJECTILETARGETFROMFILE

// system includes

// other includes
#include "ACEtk/fromFile.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "dryad/format/ace/electroatomic/createProjectileTarget.hpp"
#include "dryad/format/ace/photoatomic/createProjectileTarget.hpp"

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
   *  @param[in] filename   the ACE file name
   */
  std::variant< ProjectileTarget, std::pair< ProjectileTarget, ProjectileTarget > >
  createProjectileTargetFromFile( const std::string& filename ) {

    Log::info( "Reading ACE file \'{}\'", filename );

    auto ace = ACEtk::fromFile( filename );

    auto zaid = std::visit( [] ( auto&& header ) { return header.ZAID(); }, ace.header() );
    switch ( zaid.back() ) {

      case 'p' : {

        ACEtk::PhotoatomicTable table( std::move( ace ) );
        if ( table.electronPhotonRelaxationFormat() > 0 ) {

          return std::make_pair( photoatomic::createProjectileTarget( table ),
                                 electroatomic::createProjectileTarget( table ) );
        }
        else {

          return photoatomic::createProjectileTarget( table );
        }
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
