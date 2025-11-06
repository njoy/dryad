/**
 *  @brief Constructor for variance scaling
 *
 *  @param[in] type        the scaling procedure type
 *  @param[in] energies    the energy boundaries
 *  @param[in] factors     the scaling factors
 */
VarianceScaling( ScalingType type,
                 std::vector< double > energies,
                 std::vector< double > factors ) :
    type_( std::move( type ) ),
    energies_( std::move( energies ) ),
    factors_( std::move( factors ) ) {

  verifySize( this->energies(), this->factors() );
}
