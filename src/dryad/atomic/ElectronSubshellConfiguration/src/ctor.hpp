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
 *  @param id           the electron subshell identifier
 *  @param energy       the electron subshell binding energy
 *  @param population   the electron subshell population when the atom is neutral
 */
ElectronSubshellConfiguration( id::ElectronSubshellID id, double energy, 
                               double population ) :
  id_( std::move( id ) ), binding_energy_( energy ), population_( population ) {}

