/**
 *  @brief Retrieve the index to the reaction identifier information entry
 *
 *  @param reaction   the reaction
 *  @param numbers    the channel quantum numbers
 */
static std::size_t getIndex( const ReactionID& reaction,
                             const resonances::ChannelQuantumNumbers& numbers,
                             const std::optional< std::size_t >& partial ) {

  auto key = std::make_tuple( reaction, numbers, partial );
  auto iter = tuple_conversion_dictionary.find( key );
  if ( iter != tuple_conversion_dictionary.end() ) {

    return iter->second;
  }
  else {

    // index of the new entry
    auto index = entries.size();

    // create entry and set up lookup
    entries.emplace_back( reaction, numbers, partial );
    tuple_conversion_dictionary[ key ] = index;
    for ( const auto& symbol : entries.back().symbols() ) {

      string_conversion_dictionary[ symbol ] = index;
    }

    return index;
  }
}

/**
 *  @brief Retrieve the index to the reaction identifier information entry
 *
 *  @param string   the reaction identifier string
 */
static std::size_t getIndex( const std::string& string ) {

  auto iter = string_conversion_dictionary.find( string );
  if ( iter != string_conversion_dictionary.end() ) {

    return iter->second;
  }
  else {

    std::string id = string;
    std::optional< std::size_t > partial = std::nullopt;

    // check for a partial
    if ( string.back() == ']' ) {

      auto pos = id.rfind( '[' );
      if ( pos != std::string::npos ) {

        std::string temp = id.substr( pos );
        id.erase( pos );

        try {

          partial = std::stoi( temp.substr( 1, temp.size() - 1 ) );
        }
        catch ( ... ) {

          // if you get to this point, this is not a channel id string
          throw std::invalid_argument( "\'" + string + "\' does not define a "
                                       "channel identifier string" );
        }
      }
      else {

        // if you get to this point, this is not a channel id string
        throw std::invalid_argument( "\'" + string + "\' does not define a "
                                     "channel identifier string" );
      }
    }

    // get the quantum numbers
    auto pos = id.rfind( '{' );
    if ( pos != std::string::npos ) {

      try {

        // channel numbers and reaction id
        resonances::ChannelQuantumNumbers numbers( id.substr( pos ) );
        id.erase( pos );
        ReactionID reaction( id );

        // index of the new entry
        auto index = entries.size();

        // create entry and set up lookup
        auto key = std::make_tuple( reaction, numbers, partial );
        entries.emplace_back( reaction, numbers, partial );
        tuple_conversion_dictionary[ key ] = index;
        for ( const auto& symbol : entries.back().symbols() ) {

          string_conversion_dictionary[ symbol ] = index;
        }

        return index;
      }
      catch ( ... ) {

        // if you get to this point, this is not a channel id string
        throw std::invalid_argument( "\'" + string + "\' does not define a "
                                     "channel identifier string" );
      }
    }

    // if you get to this point, this is not a channel id string
    throw std::invalid_argument( "\'" + string + "\' does not define a "
                                 "channel identifier string" );
  }
}
