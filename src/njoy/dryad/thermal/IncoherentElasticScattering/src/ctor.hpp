/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
IncoherentElasticScattering() = default;

IncoherentElasticScattering( const IncoherentElasticScattering& ) = default;
IncoherentElasticScattering( IncoherentElasticScattering&& ) = default;

IncoherentElasticScattering& operator=( const IncoherentElasticScattering& ) = default;
IncoherentElasticScattering& operator=( IncoherentElasticScattering&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param xs                    the bound atom cross section
 *  @param debyeWallerIntegral   the Debye-Waller integral data
 */
IncoherentElasticScattering( double xs,
                             DebyeWallerIntegralData debyeWallerIntegral ) :
  bound_xs_( xs ),
  debye_waller_( std::move( debyeWallerIntegral ) ) {}
