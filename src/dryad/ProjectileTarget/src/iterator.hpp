auto iterator( const id::ReactionID& id ) const noexcept {

  return std::find_if( this->reactions().begin(), this->reactions().end(),
                       [&id] ( auto&& reaction )
                             { return reaction.identifier() == id; } );
}
