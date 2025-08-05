#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEATOMICRELAXATIONENDFFILE
#define NJOY_DRYAD_FORMAT_ENDF_CREATEATOMICRELAXATIONENDFFILE

// system includes
#include <fstream>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/atomic/createEndfSubshellData.hpp"
#include "dryad/format/endf/createDocumentation.hpp"
#include "dryad/AtomicRelaxation.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/updateDirectory.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an ENDF atomic relaxation file
   *
   *  @param[in] relaxation   the atomic relaxation data
   *  @param[in] filename     the file name for the ENDF file
   */
  void createAtomicRelaxationEndfFile( const AtomicRelaxation& relaxation,
                                       const std::string& filename ) {

    int zaid = relaxation.elementIdentifier().number() * 1000;
    double awr = relaxation.documentation().awr().has_value()
                 ? relaxation.documentation().awr().value()
                 : 0.;
    int lrp = -1;
    int lfi = 0;
    int nlib = relaxation.documentation().library().has_value()
               ? relaxation.documentation().library().value()
               : 0;
    int nmod = 0;
    double elis = 0;
    double sta = 0;
    int lis = 0;
    int liso = 0;
    int nfor = 6;
    double awi = 0;
    double emax = 0;
    int lrel = relaxation.documentation().version().has_value()
               ? relaxation.documentation().version()->second
               : 0;
    int nsub = 6;
    int nver = relaxation.documentation().version().has_value()
               ? relaxation.documentation().version()->first
               : 0;
    double temp = 0;
    int ldrv = 0;
    std::string description = relaxation.documentation().description().has_value()
                              ? relaxation.documentation().description().value()
                              : "";

    ENDFtk::section::Type< 1, 451 >
    information( zaid, awr, lrp, lfi, nlib, nmod,
                 elis, sta, lis, liso, nfor,
                 awi, emax, lrel, nsub, nver,
                 temp, ldrv, std::move( description ),
                 { ENDFtk::DirectoryRecord( 1, 451, 1, 0 ) } );

    std::vector< ENDFtk::section::Type< 28 >::SubshellData > subshells;
    for ( const auto& subshell : relaxation.subshells() ) {

      subshells.emplace_back( atomic::createEndfSubshellData( subshell ) );
    }

    ENDFtk::section::Type< 28 >
    data( 533, zaid, awr, std::move( subshells ) );

    int mat = relaxation.elementIdentifier().number() < 100
              ? relaxation.elementIdentifier().number() * 100
              : 9900 + ( relaxation.elementIdentifier().number() - 99 ) * 20;
    ENDFtk::tree::Material material( mat );
    material.insert( information );
    material.insert( data );
    ENDFtk::tree::updateDirectory( material );

    ENDFtk::TapeIdentification id( "Atomic relaxation data for " +
                                   relaxation.elementIdentifier().name() );
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
