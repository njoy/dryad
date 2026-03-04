#ifndef NJOY_DRYAD_THERMAL_COHERENTELASTICSCATTERING
#define NJOY_DRYAD_THERMAL_COHERENTELASTICSCATTERING

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/BraggEdgeData.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Coherent elastic thermal scattering data
   */
  class CoherentElasticScattering {

    /* fields */

    std::vector< double > temperatures_;
    std::vector< BraggEdgeData > edges_;

    /* auxiliary functions */

    #include "njoy/dryad/thermal/CoherentElasticScattering/src/sortAndExtractTemperatures.hpp"
    #include "njoy/dryad/thermal/CoherentElasticScattering/src/iterator.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/thermal/CoherentElasticScattering/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of temperatures for which data is available
     */
    std::size_t numberTemperatures() const {

      return this->temperatures().size();
    }

    /**
     *  @brief Return the temperature values
     */
    const std::vector< double >& temperatures() const {

      return this->temperatures_;
    }

    /**
     *  @brief Return the temperature values
     */
    std::vector< double >& temperatures() {

      return this->temperatures_;
    }

    /**
     *  @brief Return the Bragg edge data
     */
    const std::vector< BraggEdgeData >& braggEdges() const {

      return this->edges_;
    }

    /**
     *  @brief Return the Bragg edge data
     */
    std::vector< BraggEdgeData >& braggEdges() {

      return this->edges_;
    }

    /**
     *  @brief Set the Bragg edge data
     *
     *  @param braggEdges   the Bragg edge data
     */
    void braggEdges( std::vector< BraggEdgeData > braggEdges ) {

      this->edges_ = std::move( braggEdges );
      this->sortAndExtractTemperatures();
    }

    /**
     *  @brief Return whether or not there is Bragg edge data for a given temperature
     *
     *  @param[in] temperature   the temperature
     */
    bool hasBraggEdgeData( double temperature ) const {

      auto iter = this->iterator( temperature );
      return iter != this->braggEdges().end() && iter->temperature() == temperature;
    }

    /**
     *  @brief Return the Bragg edge data for a given temperature
     *
     *  @param[in] temperature   the temperature
     */
    const BraggEdgeData&
    braggEdgeData( double temperature ) const {

      auto iter = this->iterator( temperature );
      if ( iter != this->braggEdges().end() && iter->temperature() == temperature ) {

        return *iter;
      }
      else {

        Log::error( "No Bragg edge data with temperature equal to {} K could not be found",
                    temperature );
        throw std::exception();
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CoherentElasticScattering& right ) const {

      return std::tie( this->braggEdges() ) == std::tie( right.braggEdges() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CoherentElasticScattering& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
