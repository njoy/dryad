#ifndef NJOY_DRYAD_RESONANCES__UNRESOLVEDRESONANCETABLE
#define NJOY_DRYAD_RESONANCES__UNRESOLVEDRESONANCETABLE

#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <optional>

#include "tools/apply_permutation.hpp"
#include "njoy/dryad/resonances/TabulatedLevelSpacing.hpp"
#include "njoy/dryad/resonances/TabulatedAverageWidths.hpp"
#include "njoy/dryad/id/ChannelID.hpp"


namespace njoy{
namespace dryad{

namespace resonances{

    /**
     * @class
     * @brief A resonance table of average resonance parameters corresponding 
     *        to a Jpi quantum number set for use in the unresolved resonance
     *        region
     */

    class UnresolvedResonanceTable {

      private:

      std::vector< id::ChannelID > channels_;
      std::vector< TabulatedAverageWidths > widths_;
      TabulatedLevelSpacing spacings_;

       /* auxiliary functions */
       #include "njoy/dryad/resonances/UnresolvedResonanceTable/src/processTable.hpp"


    

    public:
      /* constructor */
      #include "njoy/dryad/resonances/UnresolvedResonanceTable/src/ctor.hpp"

      /* methods */

      /**
       * @brief return the channel identifiers
       */
      const std::vector< id::ChannelID >& channels() const { 
        return this->channels_; 
      }

      /**
       * @brief Return the channel identifiers
       */

      std::vector< id::ChannelID >& channels() { 
        return this->channels_;
      }

      /**
       * @brief Return the average widths
       */
      const std::vector< TabulatedAverageWidths >& widths() const {
        return this->widths_;
      }

      /**
       * @brief Return the average widths
       */
      std::vector< TabulatedAverageWidths >& widths() {
        return this->widths_;
      }

      /**
       * @brief Return the level spacings
       */
      const TabulatedLevelSpacing& spacings() const {
        return this->spacings_;
      }

      /**
       * @brief Return the level spacings
       */
      TabulatedLevelSpacing& spacings() {
        return this->spacings_;
      }


} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif