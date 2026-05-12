#ifndef NJOY_DRYAD_RESONANCES__UNRESOLVEDRESONANCETABLE
#define NJOY_DRYAD_RESONANCES__UNRESOLVEDRESONANCETABLE

#include <vector>

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


      /* methods */
    }

    

    public:
      /* constructor */
      #include "njoy/dryad/resonances/UnresolvedResonanceTable/src/ctor.hpp"

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



} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif