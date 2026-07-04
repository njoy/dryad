#ifndef NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGKERNEL
#define NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGKERNEL

// system includes
#include <algorithm>

// other includes
#include "scion/math/InterpolationTableFunction.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/thermal/TabulatedScatteringKernelFunction.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief An S(a,b) scattering kernel using tabulated scattering kernel functions
   *
   *  @todo add a symmetry flag for tables that are symmetric in beta, or handle that at read time
   *  @todo psychic test to verify the domain of the TabulatedScatteringKernel
   *  @todo medic function to prune the TabulatedScatteringKernel to the domain
   */
  class TabulatedScatteringKernel :
      protected scion::math::InterpolationTableFunction< double, TabulatedScatteringKernelFunction > {

    /* type aliases */

    using Parent = scion::math::InterpolationTableFunction< double, TabulatedScatteringKernelFunction >;

    /* fields */

    double lower_a_;
    double upper_a_;

    /* auxiliary functions */

    /**
     *  @brief Return the momentum transfer limits
     *
     *  All functions should have the same lower and upper momentum transfer limit,
     *  but there can be an error or roundoff. We take the largest value of the lower
     *  limit and the smallest value of the upper limit of each scattering function
     *  to ensure we do not have any gaps in the table's alpha domain.
     */
    void retrieveMomentumTransferLimits() {

      auto compare_lower = [] ( const auto& left, const auto& right )
                              { return left.lowerMomentumTransferLimit()
                                       < right.lowerMomentumTransferLimit(); };
      auto compare_upper = [] ( const auto& left, const auto& right )
                              { return left.upperMomentumTransferLimit()
                                       < right.upperMomentumTransferLimit(); };

      this->lower_a_ = std::max_element( this->functions().begin(), this->functions().end(),
                                         compare_lower )->lowerMomentumTransferLimit();
      this->upper_a_ = std::min_element( this->functions().begin(), this->functions().end(),
                                         compare_upper )->upperMomentumTransferLimit();
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedScatteringKernel() = default;

    TabulatedScatteringKernel( const TabulatedScatteringKernel& ) = default;
    TabulatedScatteringKernel( TabulatedScatteringKernel&& ) = default;

    TabulatedScatteringKernel& operator=( const TabulatedScatteringKernel& ) = default;
    TabulatedScatteringKernel& operator=( TabulatedScatteringKernel&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] energyTransfers        the energy transfer values
     *  @param[in] functions              the associated scattering functions
     *  @param[in] boundaries             the boundaries of the interpolation regions
     *  @param[in] interpolants           the interpolation types of the interpolation regions
     */
    TabulatedScatteringKernel( std::vector< double > energyTransfers,
                               std::vector< TabulatedScatteringKernelFunction > functions,
                               std::vector< std::size_t > boundaries,
                               std::vector< InterpolationType > interpolants ) :
      Parent( std::move( energyTransfers ), std::move( functions ),
              std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for scattering functions using a single interpolation zone
     *
     *  @param[in] energyTransfers        the energy transfer values
     *  @param[in] functions              the associated functions
     *  @param[in] interpolant            the interpolation type of the data (default lin-lin)
     */
    TabulatedScatteringKernel( std::vector< double > energyTransfers,
                               std::vector< TabulatedScatteringKernelFunction > functions,
                               InterpolationType interpolant = InterpolationType::LinearLinear ) :
      Parent( std::move( energyTransfers ), std::move( functions ), interpolant ) {}

    /* methods */

    /**
     *  @brief Return the energy transfer values
     */
    const std::vector< double >& energyTransfers() const {

      return this->x();
    }

    /**
     *  @brief Return the energy transfer values
     */
    std::vector< double >& energyTransfers() {

      return this->x();
    }

    /**
     *  @brief Return the associated scattering functions
     */
    const std::vector< TabulatedScatteringKernelFunction >& functions() const {

      return this->f();
    }

    /**
     *  @brief Return the associated distributions
     */
    std::vector< TabulatedScatteringKernelFunction >& functions() {

      return this->f();
    }

    /**
     *  @brief Return the lower energy transfer limit
     */
    double lowerEnergyTransferLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper energy transfer limit
     */
    double upperEnergyTransferLimit() const {

      return this->x().back();
    }

    /**
     *  @brief Return the lower momentum transfer limit
     */
    double lowerMomentumTransferLimit() const {

      return this->lower_a_;
    }

    /**
     *  @brief Return the upper momentum transfer limit
     */
    double upperMomentumTransferLimit() const {

      return this->upper_a_;
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
    TabulatedScatteringKernel linearise( double tolerance = constants::linearisation::tolerance ) const {

      std::vector< TabulatedScatteringKernelFunction > functions;
      functions.reserve( this->numberPoints() );
      std::transform( this->functions().begin(), this->functions().end(),
                      std::back_inserter( functions ),
                      [tolerance]
                        ( auto&& function )
                        { return function.linearise( std::move( tolerance ) ); } );
      return TabulatedScatteringKernel( this->energyTransfers(), std::move( functions ),
                                        this->boundaries(), this->interpolants() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedScatteringKernel& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedScatteringKernel& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
