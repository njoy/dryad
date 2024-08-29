/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
RadiativeTransition() = default;

RadiativeTransition( const RadiativeTransition& ) = default;
RadiativeTransition( RadiativeTransition&& ) = default;

RadiativeTransition& operator=( const RadiativeTransition& ) = default;
RadiativeTransition& operator=( RadiativeTransition&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param originatingShell   the identifier of the subshell from which the
 *                            vacancy filling electron originated
 *  @param probability        the probability of the transition
 */
RadiativeTransition( id::ElectronSubshellID originating, double probability ) :
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
RadiativeTransition( id::ElectronSubshellID originating,
                     double probability, double energy ) :
  originating_shell_( std::move( originating ) ),
  probability_( std::move( probability ) ),
  energy_( std::move( energy ) ) {}
