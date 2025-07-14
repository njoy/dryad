/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ElectronSubshellConfiguration() = default;

ElectronSubshellConfiguration( const ElectronSubshellConfiguration& ) = default;
ElectronSubshellConfiguration( ElectronSubshellConfiguration&& ) = default;

ElectronSubshellConfiguration& operator=( const ElectronSubshellConfiguration& ) = default;
ElectronSubshellConfiguration& operator=( ElectronSubshellConfiguration&& ) = default;

/**
 *  @brief Constructor with transition data
 *
 *  @param[in] id             the electron subshell identifier
 *  @param[in] energy         the electron subshell binding energy
 *  @param[in] population     the electron subshell population when the atom is neutral
 *  @param[in] radiative      the radiative transitions that are available
 *  @param[in] nonradiative   the non-radiative transitions that are available
 *  @param[in] normalise      option to indicate whether or not to normalise
 *                            all probability data (default: no normalisation)
 */
ElectronSubshellConfiguration( id::ElectronSubshellID id, double energy,
                               double population,
                               std::vector< RadiativeTransitionData > radiative,
                               std::vector< NonRadiativeTransitionData > nonradiative,
                               bool normalise = false ) :
  id_( std::move( id ) ), binding_energy_( energy ), population_( population ),
  radiative_( std::move( radiative ) ), nonradiative_( std::move( nonradiative ) ) {

  if ( normalise ) {

    this->normalise();
  }
}

/**
 *  @brief Constructor without transition data
 *
 *  @param[in] id           the electron subshell identifier
 *  @param[in] energy       the electron subshell binding energy
 *  @param[in] population   the electron subshell population when the atom is neutral
 */
ElectronSubshellConfiguration( id::ElectronSubshellID id, double energy,
                               double population ) :
  ElectronSubshellConfiguration( std::move( id ), energy,
                                 population, {}, {} ) {}
