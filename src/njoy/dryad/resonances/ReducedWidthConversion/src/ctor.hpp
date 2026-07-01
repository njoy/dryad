/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ReducedWidthConversion() = default;

ReducedWidthConversion( const ReducedWidthConversion& ) = default;
ReducedWidthConversion( ReducedWidthConversion&& ) = default;

ReducedWidthConversion& operator=( const ReducedWidthConversion& ) = default;
ReducedWidthConversion& operator=( ReducedWidthConversion&& ) = default;

/**
 *  @brief Constructor
 *  @param[in]  orbitalAngularMomentum    the orbitalAngularMomentum of the channel
 *  @param[in]  reference_energy          the reference energy at which the reduced width is
 *                                        defined (typically 1eV)
 *
 */
ReducedWidthConversion( unsigned int orbitalAngularMomentum,
                     double reference_energy ) :
  orbital_angular_momentum_( orbitalAngularMomentum ),
  penetrability_( orbitalAngularMomentum ),
  reference_energy_( reference_energy ) {}
