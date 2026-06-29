#ifndef NJOY_DRYAD_THERMAL_COHERENTELASTICSCATTERING
#define NJOY_DRYAD_THERMAL_COHERENTELASTICSCATTERING

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/utility/find_closest.hpp"
#include "njoy/dryad/thermal/BraggEdgeData.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Coherent elastic thermal scattering data
   *
   *  @todo add an operator()?
   */
  class CoherentElasticScattering {

    /* fields */

    double lower_;
    double upper_;
    std::vector< double > temperatures_;
    std::vector< BraggEdgeData > edges_;

    /* auxiliary functions */

    /**
     *  @brief Process the Bragg edge data
     *
     *  This sorts the Bragg edges by temperature and extract temperatures
     */
    void sortAndExtractTemperatures() {

      std::sort( this->braggEdges().begin(), this->braggEdges().end(),
                 [] ( auto&& left, auto&& right )
                    { return left.temperature() < right.temperature(); } );

      this->moderatorTemperatures().resize( this->braggEdges().size() );
      std::transform( this->braggEdges().begin(), this->braggEdges().end(),
                      this->moderatorTemperatures().begin(),
                      [] ( auto&& data )
                         { return data.temperature(); } );
    }

    /**
     *  @brief Return an iterator for a given temperature (using lower_bound)
     *
     *  @param[in] temperature   the temperature
     */
    auto iterator( double temperature ) const {

      return std::lower_bound( this->braggEdges().begin(), this->braggEdges().end(),
                               temperature,
                               [] ( auto&& edges, auto&& right )
                                  { return edges.temperature() < right; } );
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    CoherentElasticScattering() = default;

    CoherentElasticScattering( const CoherentElasticScattering& ) = default;
    CoherentElasticScattering( CoherentElasticScattering&& ) = default;

    CoherentElasticScattering& operator=( const CoherentElasticScattering& ) = default;
    CoherentElasticScattering& operator=( CoherentElasticScattering&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] lower        the lower energy limit
     *  @param[in] upper        the upper energy limit
     *  @param[in] braggEdges   the Bragg edge data
     */
    CoherentElasticScattering( double lower,
                               double upper,
                               std::vector< BraggEdgeData > braggEdges ) :
        lower_( lower ),
        upper_( upper ),
        edges_( std::move( braggEdges ) ) {

      this->sortAndExtractTemperatures();
    }

    /* methods */

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->lower_;
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->upper_;
    }

    /**
     *  @brief Return the number of moderator temperatures for which data is available
     */
    std::size_t numberModeratorTemperatures() const {

      return this->moderatorTemperatures().size();
    }

    /**
     *  @brief Return the moderator temperature values
     */
    const std::vector< double >& moderatorTemperatures() const {

      return this->temperatures_;
    }

    /**
     *  @brief Return the moderator temperature values
     */
    std::vector< double >& moderatorTemperatures() {

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
     *  @param[in] braggEdges   the Bragg edge data
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
     *  @brief Return the incoherent elastic scattering cross section
     *
     *  @param[in] temperature   the moderator temeprature for which the
     *                           cross section is requested
     */
    TabulatedCrossSection
    crossSection( double temperature ) const {

      // find the closest temperature, within 0.001 K
      auto iter = utility::find_closest( this->moderatorTemperatures().begin(),
                                         this->moderatorTemperatures().end(),
                                         temperature, 0.001 );
      if ( iter == this->moderatorTemperatures().end() ) {

        throw std::runtime_error( "The requested temperature "
                                  + std::to_string( temperature )
                                  + " K is not present" );
      }

      std::size_t index = std::distance( this->moderatorTemperatures().begin(), iter );
      return this->braggEdges()[index].crossSection( this->upperEnergyLimit() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CoherentElasticScattering& right ) const {

      return std::tie( this->lower_, this->upper_, this->braggEdges() ) ==
             std::tie( right.lower_, right.upper_, right.braggEdges() );
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
