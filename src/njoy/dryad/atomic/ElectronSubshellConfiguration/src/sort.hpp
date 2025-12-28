void sort() {

  std::sort( this->radiative_.begin(), this->radiative_.end(),
             [] ( auto&& left, auto&& right )
                { return left.originatingShell() < right.originatingShell(); } );
  std::sort( this->nonradiative_.begin(), this->nonradiative_.end(),
             [] ( auto&& left, auto&& right )
                { return std::tie( left.originatingShell(), left.emittingShell() ) <
                         std::tie( right.originatingShell(), right.emittingShell() ); } );
}
