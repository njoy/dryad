auto iterator( const id::ParticleID& type, std::size_t index = 0 ) const noexcept {

  auto functor = [&type] ( auto&& product )
                         { return product.identifier() == type; };

  auto iter = std::find_if( this->products().begin(), this->products().end(), functor );
  std::size_t current = index;
  while ( current != 0 && iter != this->products().end() ) {

    iter = std::find_if( iter + 1, this->products().end(), functor );
    --current;
  }

  return iter;
}
