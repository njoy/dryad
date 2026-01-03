template < typename Range >
static auto lower_iterator( const id::ElectronSubshellID& originating,
                            Range&& range ) {

  return std::lower_bound( std::begin( range ), std::end( range ),
                           originating,
                           [] ( auto&& transition, auto&& right )
                              { return transition.originatingShell() < right; } );
}

template < typename Range >
static auto upper_iterator( const id::ElectronSubshellID& originating,
                            Range&& range ) {

  return std::upper_bound( std::begin( range ), std::end( range ),
                           originating,
                           [] ( auto&& left, auto&& transition )
                              { return left < transition.originatingShell(); } );
}

auto iterator( const id::ElectronSubshellID& originating ) const {

  return lower_iterator( originating, this->radiativeTransitions() );
}

auto iterator( const id::ElectronSubshellID& originating,
               const id::ElectronSubshellID& emitting ) const {

  return std::lower_bound( this->nonRadiativeTransitions().begin(), this->nonRadiativeTransitions().end(),
                           std::tie( originating, emitting ),
                           [] ( auto&& transition, auto&& right )
                              { return std::tie( transition.originatingShell(),
                                                 transition.emittingShell() ) < right; } );
}
