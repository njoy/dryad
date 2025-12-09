#ifndef NJOY_DRYAD_INCOHERENTDISTRIBUTIONDATA
#define NJOY_DRYAD_INCOHERENTDISTRIBUTIONDATA

// system includes
#include <algorithm>
#include <optional>
#include <map>
#include <variant>

// other includes
#include "njoy/dryad/DistributionDataType.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/dryad/TabulatedScatteringFunction.hpp"
#include "njoy/dryad/TabulatedComptonProfile.hpp"

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
   *  MF27 MT504, supplemented with optional external Compton profile data.
   */
  class IncoherentDistributionData {

    /* fields */
    ReferenceFrame frame_;
    TabulatedScatteringFunction scattering_;

    std::optional< std::vector< TabulatedComptonProfile > > profiles_;

  public:

    /* constructor */

    #include "njoy/dryad/IncoherentDistributionData/src/ctor.hpp"

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

      this->scattering_ = std::move( scattering );
    }

    /**
     *  @brief Return the Compton profiles
     */
    const std::optional< std::vector< TabulatedComptonProfile > >&
    comptonProfiles() const {

      return this->profiles_;
    }

    /**
     *  @brief Set the Compton profiles
     *
     *  @param profiles   the Compton profiles
     */
    void comptonProfiles( std::optional< std::vector< TabulatedComptonProfile > > profiles ) {

      this->profiles_ = std::move( profiles );
      if ( this->profiles_.has_value() && this->profiles_.value().size() == 0 ) {

        this->profiles_ = std::nullopt;
      }
      else if ( this->profiles_.has_value() ) {

        std::sort( this->profiles_->begin(), this->profiles_->end(),
                   [] ( auto&& left, auto&& right )
                      { return left.identifier() < right.identifier(); } );
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentDistributionData& right ) const {

      return std::tie( this->frame(), this->scatteringFunction(), this->comptonProfiles() ) ==
             std::tie( right.frame(), right.scatteringFunction(), right.comptonProfiles() );
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
