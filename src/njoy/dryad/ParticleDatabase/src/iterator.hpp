auto iterator( const id::ParticleID& id ) const {

  auto compare = [] ( auto&& left, auto&& right ) {

    return left.identifier() < right;
  };

  auto iter = std::lower_bound( this->particles().begin(), this->particles().end(),
                                id, compare );
  return iter;
}
