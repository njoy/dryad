auto iterator( const id::NewReactionID& id ) const {

  return std::find_if( this->reactions().begin(), this->reactions().end(),
                       [&id] ( auto&& reaction )
                             { return reaction.identifier() == id; } );
}
