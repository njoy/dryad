#ifndef NJOY_DRYAD_THERMAL_BRAGGEDGEDATA
#define NJOY_DRYAD_THERMAL_BRAGGEDGEDATA

// system includes
#include <vector>
#include <tuple>

// other includes

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Bragg edge data for a single temperature
   *
   *  The Bragg edge data consists of edge energies and structure
   *  factor values.
   */
  class BraggEdgeData {

    /* fields */

    double temperature_;
    std::vector< double > energies_;
    std::vector< double > structure_factors_;

  public:

    /* constructor */
    #include "njoy/dryad/thermal/BraggEdgeData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the temperature of the Bradd edge data
     */
    double temperature() const {

      return this->temperature_;
    }

    /**
     *  @brief Set the temperature of the Bradd edge data
     *
     *  @param temperature   the temperature
     */
    void temperature( double temperature ) {

      this->temperature_ = temperature;
    }

    /**
     *  @brief Return the energies of the Bragg edges
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the energies of the Bragg edges
     */
    std::vector< double >& energies() {

      return this->energies_;
    }

    /**
     *  @brief Return the structure factor values
     */
    const std::vector< double >& values() const {

      return this->structure_factors_;
    }

    /**
     *  @brief Return the structure factor values
     */
    std::vector< double >& values() {

      return this->structure_factors_;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const BraggEdgeData& right ) const {

      return std::tie( this->temperature_, this->energies(), this->values() ) ==
             std::tie( right.temperature_, right.energies(), right.values() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const BraggEdgeData& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
