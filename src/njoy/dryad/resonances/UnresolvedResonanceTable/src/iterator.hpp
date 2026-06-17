auto iterator( const id::ChannelID& id ) const {

  auto iter = std::lower_bound( this->channels().begin(), this->channels().end(),
                                id);
  return iter;
}