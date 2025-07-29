#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILETARGETENDFFILE
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILETARGETENDFFILE

// system includes
#include <fstream>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createEndfFile3Section.hpp"
#include "dryad/format/endf/createDocumentation.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/updateDirectory.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an ENDF incident particle file
   *
   *  @param[in] data       the projectile-target data
   *  @param[in] mat        the ENDF mat number
   *  @param[in] filename   the file name for the ENDF file
   */
  void createProjectileTargetEndfFile( const ProjectileTarget& transport,
                                       int mat,
                                       const std::string& filename ) {

    if ( transport.projectileIdentifier() != id::ParticleID::neutron() ) {

      throw std::runtime_error( "creating ENDF file only implemented for neutron data" );
    }

    int zaid = transport.targetIdentifier().za();
    double awr = transport.documentation().awr().has_value()
                 ? transport.documentation().awr().value()
                 : 0.;
    int lrp = -1;
    int lfi = 0;
    int nlib = transport.documentation().library().has_value()
               ? transport.documentation().library().value()
               : 0;
    int nmod = 0;
    double elis = 0;
    double sta = 0;
    int lis = 0;
    int liso = 0;
    int nfor = 6;
    double awi = 0;
    double emax = 0;
    int lrel = transport.documentation().version().has_value()
               ? transport.documentation().version()->second
               : 0;
    int nsub = 10; // neutron induced
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

    for ( const auto& reaction : transport.reactions() ) {

      material.insert( createEndfFile3Section( transport.targetIdentifier(), awr, reaction ) );
    }

    ENDFtk::tree::updateDirectory( material );

    ENDFtk::TapeIdentification id( transport.projectileIdentifier().symbol() + "+" +
                                   transport.targetIdentifier().symbol() +
                                   " data" );
    ENDFtk::tree::Tape tape( std::move( id ) );
    tape.insert( std::move( material ) );

    std::ofstream out( filename );
    out << tape.content();
    out.close();
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
