#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFSPINGROUP
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFSPINGROUP

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/resonances/moveCaptureToFront.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createBoundaryCondition.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createChannelData.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfResonanceChannels.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfBackgroundChannels.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  using ENDFtkResonanceParameters = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceParameters;
  using ENDFtkSpinGroup           = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SpinGroup;
  using ENDFtkBackgroundChannels  = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels;
  
  /**
   *  @brief Format a dryad sping group object to ENDFtk object
   *
   *  @param[in] dryad_spingroups   vector of dryad spin groups
   */
  inline std::vector< ENDFtkSpinGroup >
  createEndfSpinGroups( const std::vector< dryad::resonances::SpinGroup >& dryad_spingroups, ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& ppairs ) {

    std::vector< ENDFtkSpinGroup > spingroups;

    for ( const auto& group : dryad_spingroups) {

      std::vector< double > energies = group.resonanceTable().energies();

      // Dryad stores resononance in a matrix of shape (NCH, NE) ; ENDFtk receives a matrix of shape (NE, NCH)
      auto transpose = [] (const std::vector<std::vector<double>>& m) -> std::vector<std::vector<double>> {
          if (m.empty()) return {};

          std::size_t rows = m.size();
          std::size_t cols = m[0].size();

          std::vector<std::vector<double>> result(
              cols, std::vector<double>(rows)
          );

          for (std::size_t i = 0; i < rows; ++i)
              for (std::size_t j = 0; j < cols; ++j)
                  result[j][i] = m[i][j];

          return result;
      };

      std::vector< std::vector< double > > widths = transpose( group.resonanceTable().reducedWidthAmplitudes() );

      ENDFtkBackgroundChannels backgrounds = createEndfBackgroundChannels( group );

      if ( backgrounds.KBK() == 0 ) {
        spingroups.emplace_back(  std::move( createEndfResonanceChannels( group, ppairs ) ), 
                                  std::move( ENDFtkResonanceParameters( std::move(energies), 
                                                                        std::move(widths) ) ) );
      } else {
        spingroups.emplace_back(  std::move( createEndfResonanceChannels( group, ppairs ) ), 
                                  std::move( ENDFtkResonanceParameters( std::move(energies), 
                                                                        std::move(widths) ) ),
                                  std::move( backgrounds ) );
      }
    }

    return spingroups;
  }


} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
