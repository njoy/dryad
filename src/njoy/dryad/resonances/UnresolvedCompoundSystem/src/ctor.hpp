/**
 *  @brief  Default constructor (for pybind11 purposes only)
 */
UnresolvedCompoundSystem() = default;

UnresolvedCompoundSystem( const UnresolvedCompoundSystem& ) = default;
UnresolvedCompoundSystem( UnresolvedCompoundSystem&& ) = default;

UnresolvedCompoundSystem& operator=( const UnresolvedCompoundSystem& ) = default;
UnresolvedCompoundSystem& operator=( UnresolvedCompoundSystem&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] lowerEnergy   the lower energy limit for the unresolved compound system
 *  @param[in] upperEnergy   the upper energy limit for the unresolved compound system
 *  @param[in] spinGroups    the unresolved spin groups that make up the unresolved compound system
 */
UnresolvedCompoundSystem( double lowerEnergy, double upperEnergy,
                std::vector< UnresolvedSpinGroup > spinGroups ) :
    lower_( lowerEnergy ),
    upper_( upperEnergy ),
    unresolved_spin_groups_( std::move( spinGroups )) {

  this->processSpinGroups();
  this->verifyCompoundSystem(this->lower_, this->upper_);
}
