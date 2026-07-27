#ifndef NJOY_DRYAD_TWOBODYDISTRIBUTIONDATA
#define NJOY_DRYAD_TWOBODYDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "njoy/dryad/DistributionDataType.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/dryad/IsotropicAngularDistributions.hpp"
#include "njoy/dryad/LegendreAngularDistributions.hpp"
#include "njoy/dryad/TabulatedAngularDistributions.hpp"
#include "njoy/dryad/MixedAngularDistributions.hpp"
#include "tools/overload.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The energy-angle distribution data for a two-body output channel
   *
   *  In this representation, only the angular distributions as a function of
   *  incident energy is given and the outgoing particle's energy can be derived
   *  through kinematics.
   *
   *  For incident neutron data, this corresponds with elastic and inelastic
   *  scattering data given in MF4 (none of these will have corresponding MF5
   *  data). In the more general MF6 representation, this corresponds with
   *  LAW = 2 (discrete two-body scattering). This is also the representation for
   *  elastic scattering data in MF26 for electro-atomic interactions.
   */
  class TwoBodyDistributionData {

  public:

    /* type aliases */
    using AngularDistributions = std::variant< IsotropicAngularDistributions,
                                               LegendreAngularDistributions,
                                               TabulatedAngularDistributions,
                                               MixedAngularDistributions >;

  private:

    /* fields */
    ReferenceFrame frame_;
    AngularDistributions angle_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TwoBodyDistributionData() = default;

    TwoBodyDistributionData( const TwoBodyDistributionData& ) = default;
    TwoBodyDistributionData( TwoBodyDistributionData&& ) = default;

    TwoBodyDistributionData& operator=( const TwoBodyDistributionData& ) = default;
    TwoBodyDistributionData& operator=( TwoBodyDistributionData&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] frame       the reference frame of the distribution data
     *  @param[in] angle       the angular distributions
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TwoBodyDistributionData( ReferenceFrame frame,
                             AngularDistributions angle,
                             bool normalise = false ) :
        frame_( std::move( frame ) ), angle_( std::move( angle ) ) {

      if ( normalise ) {

        this->normalise();
      }
    }

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() {

      return DistributionDataType::TwoBody;
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
     *  @param[in] frame   the reference frame of the distribution data
     */
    void frame( ReferenceFrame frame ) {

      this->frame_ = std::move( frame );
    }

    /**
     *  @brief Return the angular distributions
     */
    const AngularDistributions& angle() const {

      return this->angle_;
    }

    /**
     *  @brief Return the angular distributions
     */
    AngularDistributions& angle() {

      return this->angle_;
    }

    /**
     *  @brief Set the angular distributions
     *
     *  @param[in] angle   the angular distributions
     */
    void angle( AngularDistributions angle ) {

      this->angle_ = std::move( angle );
    }

    //! @todo implement kinematics formulas to retrieve outgoing energy
    //!       from an incident energy and outgoing cosine

    /**
     *  @brief Normalise the distribution data
     */
    void normalise() {

      std::visit( tools::overload{

                    [] ( IsotropicAngularDistributions& ) {},
                    [] ( auto&& data ) { data.normalise(); }
                  },
                  this->angle() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TwoBodyDistributionData& right ) const {

      return this->frame() == right.frame() && this->angle() == right.angle();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TwoBodyDistributionData& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
