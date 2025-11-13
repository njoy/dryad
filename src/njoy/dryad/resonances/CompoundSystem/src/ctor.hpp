/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CompoundSystem() = default;

CompoundSystem( const CompoundSystem& ) = default;
CompoundSystem( CompoundSystem&& ) = default;

CompoundSystem& operator=( const CompoundSystem& ) = default;
CompoundSystem& operator=( CompoundSystem&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] lowerEnergy   the lower energy limit for the compound system
 *  @param[in] upperEnergy   the upper energy limit for the compound system
 *  @param[in] spinGroups    the spin groups that make up the compound system
 */
CompoundSystem( double lowerEnergy, double upperEnergy,
                std::vector< SpinGroup > spinGroups ) :
    lower_( lowerEnergy ),
    upper_( upperEnergy ),
    spin_groups_( std::move( spinGroups ) ) {

  this->processSpinGroups();
}
