/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
InelasticScattering() = default;

InelasticScattering( const InelasticScattering& ) = default;
InelasticScattering( InelasticScattering&& ) = default;

InelasticScattering& operator=( const InelasticScattering& ) = default;
InelasticScattering& operator=( InelasticScattering&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param xs            the bound atom cross section
 *  @param selfScatter   the self-scattering S(a,b) function
 */
InelasticScattering( double xs,
                     TabulatedScatteringKernel selfScatter ) :
  bound_xs_( xs ),
  self_scatter_( std::move( selfScatter ) ) {}
