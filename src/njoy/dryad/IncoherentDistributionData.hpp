#ifndef NJOY_DRYAD_INCOHERENTDISTRIBUTIONDATA
#define NJOY_DRYAD_INCOHERENTDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "dryad/DistributionDataType.hpp"
#include "dryad/ReferenceFrame.hpp"
#include "dryad/TabulatedScatteringFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The distribution data for incoherent scattering in photoatomic interactions
   *
   *  This representation is only available for a photoatomic ProjectileTarget.
   *
   *  In this representation, a scattering function S(x,Z) is defined that
   *  together with the Klein-Nishina cross section determines the double
   *  differential cross section.
   *
   *  This corresponds with the incoherent scattering function data given in
   *  MF27 MT504.
   */
  class IncoherentDistributionData {

    /* fields */
    ReferenceFrame frame_;
    TabulatedScatteringFunction scattering_;

  public:

    /* constructor */

    #include "dryad/IncoherentDistributionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() {

      return DistributionDataType::Incoherent;
    }

    /**
     *  @brief Return the reference frame
     */
    const ReferenceFrame& frame() const {

      return this->frame_;
    }

    /**
     *  @brief Set the reference frame
     *
     *  @param frame   the reference frame of the distribution data
     */
    void frame( ReferenceFrame frame ) {

      this->frame_ = std::move( frame );
    }

    /**
     *  @brief Return the scattering function
     */
    const TabulatedScatteringFunction& scatteringFunction() const {

      return this->scattering_;
    }

    /**
     *  @brief Set the scattering function
     *
     *  @param scattering   the scattering function
     */
    void scatteringFunction( TabulatedScatteringFunction scattering ) {

      this->scattering_ = scattering;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentDistributionData& right ) const {

      return this->frame() == right.frame() &&
             this->scatteringFunction() == right.scatteringFunction();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentDistributionData& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
