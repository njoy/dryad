#ifndef NJOY_FORMAT_ENDF_WRITE_CREATEPROJECTILETARGETFILE
#define NJOY_FORMAT_ENDF_WRITE_CREATEPROJECTILETARGETFILE

// system includes
#include <fstream>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/constants.hpp"
#include "njoy/format/endf/write/createSublibraryType.hpp"
#include "njoy/format/endf/write/createFile2Section151.hpp"
#include "njoy/format/endf/write/createFile3Section.hpp"
#include "njoy/format/endf/write/createFile23Section.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/updateDirectory.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Create an ENDF incident particle file
   *
   *  @param[in] transport                the projectile-target data
   *  @param[in] mat                      the ENDF mat number
   *  @param[in] filename                 the file name for the ENDF file
   *  @param[in] reducedWidthAmplitudes   if there are resonances, use reduced width amplitudes
   */
  inline void createProjectileTargetFile( const dryad::ProjectileTarget& transport,
                                          int mat,
                                          const std::string& filename,
                                          bool reducedWidthAmplitudes = true ) {

    auto projectile = transport.projectileIdentifier();
    auto target = transport.targetIdentifier();

    int zaid = target.za();
    double awr = transport.particleData().has_value()
                 ? transport.particleData()->particle( target ).mass().value() /
                   constants::neutron_mass
                 : 0.;
    int lrp = transport.resonances().has_value() ? 1 : -1;
    int lfi = 0;
    int nlib = transport.documentation().library().has_value()
               ? transport.documentation().library().value()
               : 0;
    int nmod = 0;
    double elis = transport.particleData().has_value()
                  ? transport.particleData()->particle( target ).energy().value()
                  : 0.;
    double sta = 0;
    int lis = target.e();
    int liso = 0;
    int nfor = 6;
    double awi = transport.particleData().has_value()
                 ? transport.particleData()->particle( projectile ).mass().value() /
                   constants::neutron_mass
                 : 0.;
    double emax = transport.reactions().front().crossSection().upperEnergyLimit();
    int lrel = transport.documentation().version().has_value()
               ? transport.documentation().version()->second
               : 0;
    int nsub = createSublibraryType( projectile,
                                         transport.interactionType() );
    int nver = transport.documentation().version().has_value()
               ? transport.documentation().version()->first
               : 0;
    double temp = 0;
    int ldrv = 0;
    std::string description = transport.documentation().description().has_value()
                              ? transport.documentation().description().value()
                              : "";

    ENDFtk::section::Type< 1, 451 >
    information( zaid, awr, lrp, lfi, nlib, nmod,
                 elis, sta, lis, liso, nfor,
                 awi, emax, lrel, nsub, nver,
                 temp, ldrv, std::move( description ),
                 { ENDFtk::DirectoryRecord( 1, 451, 1, 0 ) } );

    ENDFtk::tree::Material material( mat );
    material.insert( information );

    //! @todo if lrp=0, should write a 'special case' MF2
    if ( transport.resonances().has_value() ) {

      material.insert( createFile2Section151( awr, transport.resonances().value(),
                                                  reducedWidthAmplitudes ) );
    }

    for ( const auto& reaction : transport.reactions() ) {

      if ( transport.interactionType() == dryad::InteractionType::Nuclear ) {

        material.insert( createFile3Section( awr, reaction ) );
      }
      else {

        if ( reaction.identifier().reactionType() != dryad::id::ReactionType( "deficit-scattering" ) ) {

          material.insert( createFile23Section( awr, reaction ) );
        }
      }
    }

    ENDFtk::tree::updateDirectory( material );

    ENDFtk::TapeIdentification id( projectile.symbol() + "+" +
                                   target.symbol() +
                                   " data" );
    ENDFtk::tree::Tape tape( std::move( id ) );
    tape.insert( std::move( material ) );

    std::ofstream out( filename, std::ios::binary );
    out << tape.content();
    out.close();
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
