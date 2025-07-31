void sort() noexcept {

  std::sort( this->subshells_.begin(), this->subshells_.end(),
             [] ( auto&& left, auto&& right )
                { return left.identifier() < right.identifier(); } );
}
