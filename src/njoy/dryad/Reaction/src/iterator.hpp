template < typename Functor >
auto iterator( Functor&& functor, std::size_t index ) const {

  auto iter = std::find_if( this->products().begin(), this->products().end(), functor );
  std::size_t current = index;
  while ( current != 0 && iter != this->products().end() ) {

    iter = std::find_if( iter + 1, this->products().end(), functor );
    --current;
  }

  return iter;
}

auto iterator( const id::ParticleID& type, std::size_t index = 0 ) const {

  auto functor = [&] ( auto&& product )
                     { return product.productIdentifier() == type; };

  return this->iterator( functor, index );
}

auto iterator( const id::ParticleID& type, std::size_t chain, std::size_t index ) const {

  auto functor = [&] ( auto&& product )
                     { return product.productIdentifier() == type &&
                              product.chainIndex() == chain; };

  return this->iterator( functor, index );
}
