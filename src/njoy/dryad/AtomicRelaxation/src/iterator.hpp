auto iterator( const id::ElectronSubshellID& id ) const {

  return std::lower_bound( this->subshells().begin(), this->subshells().end(),
                           id,
                           [] ( auto&& subshell, auto&& right )
                              { return subshell.identifier() < right; } );
}
