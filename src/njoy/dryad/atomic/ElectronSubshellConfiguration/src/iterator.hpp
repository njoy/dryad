auto iterator( const id::ElectronSubshellID& originating ) const {

  return std::lower_bound( this->radiativeTransitions().begin(), this->radiativeTransitions().end(),
                           originating,
                           [] ( auto&& transition, auto&& right )
                              { return transition.originatingShell() < right; } );
}

auto iterator( const id::ElectronSubshellID& originating,
               const id::ElectronSubshellID& emitting ) const {

  return std::lower_bound( this->nonRadiativeTransitions().begin(), this->nonRadiativeTransitions().end(),
                           std::tie( originating, emitting ),
                           [] ( auto&& transition, auto&& right )
                              { return std::tie( transition.originatingShell(),
                                                 transition.emittingShell() ) < right; } );
}
