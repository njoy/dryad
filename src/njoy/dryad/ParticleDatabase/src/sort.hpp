void sort() {

  std::sort( this->particles().begin(), this->particles().end(),
             [] ( auto&& left, auto&& right )
                { return left.identifier() < right.identifier(); } );
}
