/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
NonRadiativeTransition() = default;

NonRadiativeTransition( const NonRadiativeTransition& ) = default;
NonRadiativeTransition( NonRadiativeTransition&& ) = default;

NonRadiativeTransition& operator=( const NonRadiativeTransition& ) = default;
NonRadiativeTransition& operator=( NonRadiativeTransition&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param originatingShell   the identifier of the subshell from which the
 *                            vacancy filling electron originated
 *  @param emittingShell      the identifier of the subshell from which the
 *                            emitted electron originated
 *  @param probability        the probability of the transition
 */
NonRadiativeTransition( id::ElectronSubshellID originating,
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
 *  @param energy             the energy of the emitted particle
 */
NonRadiativeTransition( id::ElectronSubshellID originating,
                        id::ElectronSubshellID emitting,
                        double probability, double energy ) :
  originating_shell_( std::move( originating ) ),
  emitting_shell_( std::move( emitting ) ),
  probability_( std::move( probability ) ),
  energy_( std::move( energy ) ) {}
