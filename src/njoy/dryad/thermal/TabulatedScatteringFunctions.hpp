#ifndef NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGFUNCTIONS
#define NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGFUNCTIONS

// system includes

// other includes
#include "scion/math/InterpolationTableFunction.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/thermal/TabulatedScatteringFunction.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief An S(a,b) scattering kernel using tabulated scattering functions
   */
  class TabulatedScatteringFunctions :
      protected scion::math::InterpolationTableFunction< double, TabulatedScatteringFunction > {

    /* type aliases */
    using Parent = scion::math::InterpolationTableFunction< double, TabulatedScatteringFunction >;

  public:

    /* constructor */

    #include "njoy/dryad/thermal/TabulatedScatteringFunctions/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy transfer values
     */
    const std::vector< double >& energyTransfers() const {

      return this->x();
    }

    /**
     *  @brief Return the associated scattering functions
     */
    const std::vector< TabulatedScatteringFunction >& functions() const {

      return this->f();
    }

    /**
     *  @brief Return the associated distributions
     */
    std::vector< TabulatedScatteringFunction >& functions() {

      return this->f();
    }

    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;
    using Parent::operator();

    /**
     *  @brief Return linearised scattering functions
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedScatteringFunctions linearise( double tolerance = constants::linearisation::tolerance ) const {

      std::vector< TabulatedScatteringFunction > functions;
      functions.reserve( this->numberPoints() );
      std::transform( this->functions().begin(), this->functions().end(),
                      std::back_inserter( functions ),
                      [tolerance]
                        ( auto&& function )
                        { return function.linearise( std::move( tolerance ) ); } );
      return TabulatedScatteringFunctions( this->energyTransfers(), std::move( functions ),
                                           this->boundaries(), this->interpolants() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedScatteringFunctions& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedScatteringFunctions& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
