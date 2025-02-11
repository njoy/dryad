/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
RadiativeTransitionData() = default;

RadiativeTransitionData( const RadiativeTransitionData& ) = default;
RadiativeTransitionData( RadiativeTransitionData&& ) = default;

RadiativeTransitionData& operator=( const RadiativeTransitionData& ) = default;
RadiativeTransitionData& operator=( RadiativeTransitionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param originatingShell   the identifier of the subshell from which the
 *                            vacancy filling electron originated
 *  @param probability        the probability of the transition
 */
RadiativeTransitionData( id::ElectronSubshellID originating, double probability ) :
  originating_shell_( std::move( originating ) ),
  probability_( std::move( probability ) ),
  energy_( std::nullopt ) {}

/**
 *  @brief Constructor
 *
 *  @param originatingShell   the identifier of the subshell from which the
 *                            vacancy filling electron originated
 *  @param probability        the probability of the transition
 *  @param energy             the energy of the emitted particle
 */
RadiativeTransitionData( id::ElectronSubshellID originating,
                         double probability, double energy ) :
  originating_shell_( std::move( originating ) ),
  probability_( std::move( probability ) ),
  energy_( std::move( energy ) ) {}
