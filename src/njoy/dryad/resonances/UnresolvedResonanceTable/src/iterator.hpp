auto iterator( const id::ChannelID& id ) const {

  auto compare = [] ( auto&& left, auto&& right ) {

    return left < right;
  };

  auto iter = std::lower_bound( this->channels().begin(), this->channels().end(),
                                id, compare );
  return iter;
}