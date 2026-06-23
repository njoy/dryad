static auto iterator( const id::ParticleID& id ) {

  // the id can be for an excited state while the ame data is for
  // ground states only.

  auto iter = Masses::masses_.find( id.groundState() );
  if ( iter == Masses::masses_.end() ) {

    if ( Masses::size() == 0 ) {

      Masses::loadData();
      iter = Masses::masses_.find( id.groundState() );
    }
  }

  return iter;
}
