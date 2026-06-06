static auto iterator( const id::ParticleID& id ) {

  auto iter = Levels::levels_.find( id );
  if ( iter == Levels::levels_.end() ) {

    if ( id.a() != 0 ) {

      iter = std::lower_bound( Levels::levels_.begin(), Levels::levels_.end(),
                               id.z(),
                               [] ( auto&& left, auto&& right )
                                  { return left.first.z() < right; } );
      if ( iter == Levels::levels_.end() || iter->first != id ) {

        Levels::loadData( id.z() );
        iter = Levels::levels_.find( id );
      }
    }
  }

  return iter;
}
