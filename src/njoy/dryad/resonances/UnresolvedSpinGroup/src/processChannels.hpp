void processChannels() {

  std::sort( this->channels().begin(), this->channels().end(),
             [] ( auto&& left, auto&& right )
                { return left.identifier() < right.identifier(); }
    );

  for ( const auto& channel : this->channels() ) {

    auto id = channel.identifier().reaction();
    auto iter = std::lower_bound( this->reactions().begin(),
                                  this->reactions().end(), id );
    if ( ! ( iter != this->reactions().end() && *iter == id ) ) {
      this->reactions().insert( iter, id );
    }
  }
}