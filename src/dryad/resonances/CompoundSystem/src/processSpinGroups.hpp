void processSpinGroups() {

  std::sort( this->spinGroups().begin(), this->spinGroups().end(),
             [] ( auto&& left, auto&& right )
                { return std::make_tuple( left.totalAngularMomentum(), left.parity() ) <
                         std::make_tuple( right.totalAngularMomentum(), right.parity() ); } );
}