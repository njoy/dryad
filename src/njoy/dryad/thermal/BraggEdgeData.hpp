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
   *
   *  @todo add a function to retrieve the cross section (interpolation type is 1/E)
   */
  class BraggEdgeData {

    /* fields */

    double temperature_;
    std::vector< double > energies_;
    std::vector< double > structure_factors_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    BraggEdgeData() = default;

    BraggEdgeData( const BraggEdgeData& ) = default;
    BraggEdgeData( BraggEdgeData&& ) = default;

    BraggEdgeData& operator=( const BraggEdgeData& ) = default;
    BraggEdgeData& operator=( BraggEdgeData&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] temperature   the temperature
     *  @param[in] energies      the Bragg edge energies
     *  @param[in] values        the structure factor values
     */
    BraggEdgeData( double temperature,
                   std::vector< double > energies,
                   std::vector< double > values ) :
      temperature_( temperature ),
      energies_( std::move( energies ) ),
      structure_factors_( std::move( values ) ) {}

    /* methods */

    /**
     *  @brief Return the temperature of the Bragg edge data
     */
    double temperature() const {

      return this->temperature_;
    }

    /**
     *  @brief Return the number of Bragg edges
     */
    std::size_t numberBraggEdges() const {

      return this->energies().size();
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
     *  @brief Return the cumulative structure factor values
     */
    const std::vector< double >& values() const {

      return this->structure_factors_;
    }

    /**
     *  @brief Return the cumulative structure factor values
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
