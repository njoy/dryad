void processChannels() {

  for ( const auto& channel : this->channels() ) {

    auto id = channel.identifier().reaction();
    auto iter = std::lower_bound( this->reactions().begin(),
                                  this->reactions().end(), id );
    if ( ! ( iter != this->reactions().end() && *iter == id ) ) {

      this->reactions().insert( iter, id );
    }
  }
}