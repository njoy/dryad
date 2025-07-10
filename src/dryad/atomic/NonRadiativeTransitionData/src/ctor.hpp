/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
NonRadiativeTransitionData() = default;

NonRadiativeTransitionData( const NonRadiativeTransitionData& ) = default;
NonRadiativeTransitionData( NonRadiativeTransitionData&& ) = default;

NonRadiativeTransitionData& operator=( const NonRadiativeTransitionData& ) = default;
NonRadiativeTransitionData& operator=( NonRadiativeTransitionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param originatingShell   the identifier of the subshell from which the
 *                            vacancy filling electron originated
 *  @param emittingShell      the identifier of the subshell from which the
 *                            emitted electron originated
 *  @param probability        the probability of the transition
 */
NonRadiativeTransitionData( id::ElectronSubshellID originating,
                            id::ElectronSubshellID emitting,
                            double probability ) :
  originating_shell_( std::move( originating ) ),
  emitting_shell_( std::move( emitting ) ),
  probability_( std::move( probability ) ),
  energy_( std::nullopt ) {}

/**
 *  @brief Constructor
 *
 *  @param originatingShell   the identifier of the subshell from which the
 *                            vacancy filling electron originated
 *  @param emittingShell      the identifier of the subshell from which the
 *                            emitted electron originated
 *  @param probability        the probability of the transition
 *  @param energy             the energy of the emitted electron
 */
NonRadiativeTransitionData( id::ElectronSubshellID originating,
                            id::ElectronSubshellID emitting,
                            double probability, double energy ) :
  originating_shell_( std::move( originating ) ),
  emitting_shell_( std::move( emitting ) ),
  probability_( std::move( probability ) ),
  energy_( std::move( energy ) ) {}
