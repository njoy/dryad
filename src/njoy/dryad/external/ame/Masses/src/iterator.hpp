static auto iterator( const id::ParticleID& id ) {

  auto iter = Masses::masses_.find( id );
  if ( iter == Masses::masses_.end() ) {

    if ( Masses::size() == 0 ) {

      Masses::loadData();
      iter = Masses::masses_.find( id );
    }
  }

  return iter;
}
