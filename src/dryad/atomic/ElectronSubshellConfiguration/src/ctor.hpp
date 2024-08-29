/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ElectronSubshellConfiguration() = default;

ElectronSubshellConfiguration( const ElectronSubshellConfiguration& ) = default;
ElectronSubshellConfiguration( ElectronSubshellConfiguration&& ) = default;

ElectronSubshellConfiguration& operator=( const ElectronSubshellConfiguration& ) = default;
ElectronSubshellConfiguration& operator=( ElectronSubshellConfiguration&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param id             the electron subshell identifier
 *  @param energy         the electron subshell binding energy
 *  @param population     the electron subshell population when the atom is neutral
 *  @param radiative      the radiative transitions that are available
 *  @param nonradiative   the non-radiative transitions that are available
 */
ElectronSubshellConfiguration( id::ElectronSubshellID id, double energy,
                               double population,
                               std::vector< RadiativeTransitionData > radiative,
                               std::vector< NonRadiativeTransitionData > nonradiative ) :
  id_( std::move( id ) ), binding_energy_( energy ), population_( population ),
  radiative_( std::move( radiative ) ), nonradiative_( std::move( nonradiative ) ),
  radiative_probability_( 0. ), nonradiative_probability_( 0. ) {

  this->calculateProbabilities();
}

/**
 *  @brief Constructor
 *
 *  @param id             the electron subshell identifier
 *  @param energy         the electron subshell binding energy
 *  @param population     the electron subshell population when the atom is neutral
 */
ElectronSubshellConfiguration( id::ElectronSubshellID id, double energy,
                               double population ) :
  ElectronSubshellConfiguration( std::move( id ), energy,
                                 population, {}, {} ) {}
