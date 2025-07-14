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
 *  @param energy             the energy of the emitted electron (default: undefined)
 */
NonRadiativeTransitionData( id::ElectronSubshellID originating,
                            id::ElectronSubshellID emitting,
                            double probability,
                            std::optional< double > energy = std::nullopt ) :
  originating_shell_( std::move( originating ) ),
  emitting_shell_( std::move( emitting ) ),
  probability_( std::move( probability ) ),
  energy_( std::move( energy ) ) {}
