#ifndef NJOY_DRYAD_THERMAL_INCOHERENTINELASTICSCATTERING
#define NJOY_DRYAD_THERMAL_INCOHERENTINELASTICSCATTERING

// system includes

// other includes
#include "scion/math/compare.hpp"
#include "njoy/utility/find_closest.hpp"
#include "njoy/dryad/thermal/ShortCollisionTimeScatteringKernel.hpp"
#include "njoy/dryad/thermal/ScatteringKernel.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Incoherent elastic thermal scattering data
   */
  class IncoherentInelasticScattering {

    /* fields */

    double lower_;
    double upper_;
    double bound_xs_;
    double ratio_;
    std::vector< ScatteringKernel > scattering_kernels_;

    std::vector< double > temperatures_;

    /* auxiliary functions */

    /**
     *  @brief Process the kernels
     *
     *  This sorts the kernels by temperature and extracts temperatures
     */
    void sortAndExtractTemperatures() {

      std::sort( this->scatteringKernels().begin(), this->scatteringKernels().end(),
                 [] ( auto&& left, auto&& right )
                    { return left.moderatorTemperature() < right.moderatorTemperature(); } );

      this->moderatorTemperatures().resize( this->scatteringKernels().size() );
      std::transform( this->scatteringKernels().begin(), this->scatteringKernels().end(),
                      this->moderatorTemperatures().begin(),
                      [] ( auto&& data )
                         { return data.moderatorTemperature(); } );
    }

    /**
     *  @brief Return an iterator for a given temperature (within a given tolerance)
     *
     *  @param[in] temperature   the temperature
     *  @param[in] tolerance     the tolerance
     */
    auto iterator( double temperature, double tolerance ) const {

      auto iter = utility::find_closest( this->moderatorTemperatures().begin(),
                                         this->moderatorTemperatures().end(),
                                         temperature, tolerance );
      if ( iter != this->moderatorTemperatures().end() ) {

        return std::next( this->scatteringKernels().begin(),
                          std::distance( this->moderatorTemperatures().begin(), iter ) );
      }

      return this->scatteringKernels().end();
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    IncoherentInelasticScattering() = default;

    IncoherentInelasticScattering( const IncoherentInelasticScattering& ) = default;
    IncoherentInelasticScattering( IncoherentInelasticScattering&& ) = default;

    IncoherentInelasticScattering& operator=( const IncoherentInelasticScattering& ) = default;
    IncoherentInelasticScattering& operator=( IncoherentInelasticScattering&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] lower     the lower energy limit
     *  @param[in] upper     the upper energy limit
     *  @param[in] xs        the bound atom cross section
     *  @param[in] ratio     the atomic mass ratio of the target to the projectile
     *  @param[in] kernels   the scattering kernels
     */
    IncoherentInelasticScattering( double lower,
                                   double upper,
                                   double xs,
                                   double ratio,
                                   std::vector< ScatteringKernel > kernels ) :
        lower_( lower ),
        upper_( upper ),
        bound_xs_( xs ),
        ratio_( ratio ),
        scattering_kernels_( std::move( kernels ) ) {

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
     *  @brief Return the lower energy limit
     */
    double& lowerEnergyLimit() {

      return this->lower_;
    }

    /**
     *  @brief Set the lower energy limit
     *
     *  @param[in] lower   the lower energy limit
     */
    void lowerEnergyLimit( double lower ) {

      this->lower_ = lower;
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->upper_;
    }

    /**
     *  @brief Return the upper energy limit
     */
    double& upperEnergyLimit() {

      return this->upper_;
    }

    /**
     *  @brief Set the upper energy limit
     *
     *  @param[in] upper   the upper energy limit
     */
    void upperEnergyLimit( double upper ) {

      this->upper_ = upper;
    }

    /**
     *  @brief Return the bound atom cross section value
     */
    double boundCrossSection() const {

      return this->bound_xs_;
    }

    /**
     *  @brief Return the bound atom cross section value
     */
    double& boundCrossSection() {

      return this->bound_xs_;
    }

    /**
     *  @brief Set the bound atom cross section value
     *
     *  @param[in] xs   the reaction product identifier
     */
    void boundCrossSection( double xs ) {

      this->bound_xs_ = xs;
    }

    /**
     *  @brief Return the ratio of the target mass to the projectile mass
     */
    double atomicWeightRatio() const {

      return this->ratio_;
    }

    /**
     *  @brief Return the ratio of the target mass to the projectile mass
     */
    double& atomicWeightRatio() {

      return this->ratio_;
    }

    /**
     *  @brief Set the ratio of the target mass to the projectile mass
     *
     *  @param[in] ratio   the mass ratio
     */
    void atomicWeightRatio( double ratio ) {

      this->ratio_ = ratio;
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
     *  @brief Return the scattering kernels
     */
    const std::vector< ScatteringKernel >& scatteringKernels() const {

      return this->scattering_kernels_;
    }

    /**
     *  @brief Return the moderator temperature values
     */
    std::vector< ScatteringKernel >& scatteringKernels() {

      return this->scattering_kernels_;
    }

    /**
     *  @brief Set the moderator temperature values
     *
     *  @param[in] kernels   the scattering kernels
     */
    void scatteringKernels( std::vector< ScatteringKernel > kernels ) {

      this->scattering_kernels_ = std::move( kernels );
    }

    /**
     *  @brief Return whether or not there is a scattering kernel for a given
     *         moderator temperature
     *
     *  @param[in] temperature   the moderator temperature
     */
    bool hasScatteringKernel( double temperature ) const {

      // get the closest temperature
      auto iter = this->iterator( temperature, constants::temperature_tolerance );
      return iter != this->scatteringKernels().end();
    }

    /**
     *  @brief Return the scattering kernel for a given moderator temperature
     *
     *  @param[in] temperature   the moderator temperature
     */
    const ScatteringKernel&
    scatteringKernel( double temperature ) const {

      // get the closest temperature
      auto iter = this->iterator( temperature, constants::temperature_tolerance );
      if ( iter != this->scatteringKernels().end() ) {

        return *iter;
      }
      else {

        Log::error( "No scattering kernel with moderator temperature equal to {} K could be found",
                    temperature );
        throw std::exception();
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentInelasticScattering& right ) const {

      return std::tie( this->lower_, this->upper_, this->scatteringKernels() ) ==
             std::tie( right.lower_, right.upper_, right.scatteringKernels() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentInelasticScattering& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
