#ifndef NJOY_FORMAT_ENDF_WRITE_CREATETHERMALSCATTERINGFILE
#define NJOY_FORMAT_ENDF_WRITE_CREATETHERMALSCATTERINGFILE

// system includes
#include <fstream>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/format/endf/write/thermal/createCoherentElastic.hpp"
#include "njoy/format/endf/write/thermal/createIncoherentElastic.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/updateDirectory.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Create an ENDF thermal scattering file
   *
   *  @param[in] tsl        the thermal scattering data
   *  @param[in] za         the za number
   *  @param[in] mat        the ENDF mat number
   *  @param[in] filename   the file name for the ENDF file
   */
  inline void createThermalScatteringFile( const dryad::ThermalScattering& tsl,
                                           int za,
                                           int mat,
                                           const std::string& filename ) {

    int zaid = za;
    double awr = 0.;
    int lrp = -1;
    int lfi = 0;
    int nlib = tsl.documentation().library().has_value()
               ? tsl.documentation().library().value()
               : 0;
    int nmod = 0;
    double elis = 0;
    double sta = 0;
    int lis = 0;
    int liso = 0;
    int nfor = 6;
    double awi = 1; // neutrons
    double emax = 0;
    int lrel = tsl.documentation().version().has_value()
               ? tsl.documentation().version()->second
               : 0;
    int nsub = 12;
    int nver = tsl.documentation().version().has_value()
               ? tsl.documentation().version()->first
               : 0;
    double temp = 0;
    int ldrv = 0;
    std::string description = tsl.documentation().description().has_value()
                              ? tsl.documentation().description().value()
                              : "";

    // create MF1 MT451 section for this data
    ENDFtk::section::Type< 1, 451 >
    information( zaid, awr, lrp, lfi, nlib, nmod,
                 elis, sta, lis, liso, nfor,
                 awi, emax, lrel, nsub, nver,
                 temp, ldrv, std::move( description ),
                 { ENDFtk::DirectoryRecord( 1, 451, 1, 0 ) } );

    // create material
    ENDFtk::tree::Material material( mat );
    material.insert( information );

    // inser elastic if there is data
    if ( tsl.hasElasticScattering() ) {

      if ( tsl.hasCoherentElasticScattering() &&
           tsl.hasIncoherentElasticScattering() ) {

        ENDFtk::section::Type< 7, 2 >
        elastic( zaid, awr,
                 ENDFtk::section::Type< 7, 2 >::MixedElastic(
                   thermal::createCoherentElastic( tsl.coherentElasticScattering().value() ),
                   thermal::createIncoherentElastic( tsl.incoherentElasticScattering().value() ) ) );
        material.insert( elastic );
      }
      else if ( tsl.hasCoherentElasticScattering() ) {

        ENDFtk::section::Type< 7, 2 >
        elastic( zaid, awr,
                 thermal::createCoherentElastic( tsl.coherentElasticScattering().value() ) );
        material.insert( elastic );
      }
      else {

        ENDFtk::section::Type< 7, 2 >
        elastic( zaid, awr,
                 thermal::createIncoherentElastic( tsl.incoherentElasticScattering().value() ) );
        material.insert( elastic );
      }
    }

    // insert inelastic if there is data
    if ( tsl.hasInelasticScattering() ) {

      // unreachable for now
    }

    // update index
    ENDFtk::tree::updateDirectory( material );

    // add create tape
    ENDFtk::TapeIdentification id( "Thermal scattering data" );
    ENDFtk::tree::Tape tape( std::move( id ) );
    tape.insert( std::move( material ) );

    // print to file
    std::ofstream out( filename, std::ios::binary );
    out << tape.content();
    out.close();
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
