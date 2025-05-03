/**
 *  @brief Update registry
 *
 *  @param za      the za of the particle
 *  @param level   the particle level number (default is zero)
 */
static std::size_t updateRegistry( ElementID element, int mass, LevelID state ) {

  // the index for the new identifier
  std::size_t index = entries.size();

  int number = element.number() * 1000000 + mass * 1000 + state.number();
  std::vector< std::string > alternatives = {};
  std::string symbol = element.symbol() + std::to_string( mass );
  if ( state.number() != 0 ) {

    symbol += state.symbol();
  }
  else {

    alternatives.emplace_back( symbol + std::string( "_e0" ) );
  }

  // create the data entry and set conversion
  entries.emplace_back( number, std::move( element ), static_cast< char >( mass ),
                        std::move( state ), std::move( symbol ),
                        std::move( alternatives ) );

  number_conversion_dictionary[ entries[ index ].number() ] = index;
  string_conversion_dictionary[ entries[ index ].symbol() ] = index;
  for ( const auto& alternative : entries[ index ].alternatives() ) {

    string_conversion_dictionary[ alternative ] = index;
  }

  // return the index
  return index;
}

/**
 *  @brief Retrieve the index to the particle information entry
 *
 *  @param za      the za of the particle
 *  @param level   the particle level number (default is zero)
 */
static std::size_t getIndex( int za, int level ) {

  try {

    return number_conversion_dictionary.at( za * 1000 + level );
  }
  catch ( ... ) {

    try {

      // data entries
      int mass = za % 1000;
      ElementID element( ( za - mass ) / 1000 );
      LevelID state( level );

      // update registry and return the index
      return updateRegistry( std::move( element ), std::move( mass ), std::move( state ) );
    }
    catch ( ... ) {

      throw std::out_of_range( "Not a particle symbol or name: \'" + std::to_string( za ) + "\'" );
    }
  }
}

/**
 *  @brief Retrieve the index to the particle information entry
 *
 *  @param string    the particle id as a string
 */
static std::size_t getIndex( const std::string& string ) {

  try {

    return string_conversion_dictionary.at( string );
  }
  catch ( ... ) {

    std::smatch match;
    if ( std::regex_match( string, match, nuclide_id_regex ) ) {

      // data entries
      ElementID element( match[2] );
      int mass = std::stoi( match[3] );
      LevelID state( match[4] != "" ? match[5] != "" ? std::stoi( match[6] )
                                                     : LevelID::continuum
                                    : 0 );

      // update registry and return the index
      return updateRegistry( std::move( element ), std::move( mass ), std::move( state ) );
    }

    throw std::out_of_range( "Not a particle symbol or name: \'" + string + "\'" );
  }
}
