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
 *  @param[in] spinGroups   the spin groups that make up the compound system
 */
CompoundSystem( std::vector< SpinGroup > spinGroups ) :
    spin_groups_( std::move( spinGroups ) ) {

  this->processSpinGroups();
}
