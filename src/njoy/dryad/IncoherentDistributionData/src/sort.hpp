void sort() {

  std::sort( this->profiles_->begin(), this->profiles_->end(),
             [] ( auto&& left, auto&& right )
                { return left.identifier() < right.identifier(); } );
}
