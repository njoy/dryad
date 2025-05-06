/**
 *  @brief Update registry
 *
 *  @param element   the particle element
 *  @param a         the particle mass number
 *  @param level     the particle level
 */
static std::size_t updateRegistry( ElementID element, int a, LevelID state ) {

  // the index for the new identifier
  std::size_t index = entries.size();

  int number = element.number() * 1000000 + a * 1000 + state.number();
  std::vector< std::string > alternatives = {};
  std::string symbol = element.symbol() + std::to_string( a );
  if ( state.number() != 0 ) {

    symbol += state.symbol();
  }
  else {

    alternatives.emplace_back( symbol + std::string( "_e0" ) );
  }

  // create the data entry and set conversion
  entries.emplace_back( number, element.number(), static_cast< short >( a ),
                        state.number(), std::move( symbol ),
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
 *  @brief Update registry
 *
 *  @param element    the particle element
 *  @param subshell   the particle subshell
 */
static std::size_t updateRegistry( ElementID element, ElectronSubshellID subshell ) {

  // the index for the new identifier
  std::size_t index = entries.size();

  int number = element.number() * 1000000 + subshell.number();
  std::string symbol = element.symbol() + std::string( "{" ) + subshell.symbol() + std::string( "}" );
  std::vector< std::string > alternatives = { element.symbol() + std::string( "{" ) + subshell.name() + std::string( "}" ) };

  // create the data entry and set conversion
  entries.emplace_back( number, element.number(),
                        std::move( subshell ), std::move( symbol ),
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
 *  @param za       the za of the particle
 *  @param number   the particle level number or subshell number
 */
static std::size_t getIndex( int za, int number ) {

  try {

    return number_conversion_dictionary.at( za * 1000 + number );
  }
  catch ( ... ) {

    try {

      // data entries
      int mass = za % 1000;
      ElementID element( ( za - mass ) / 1000 );

      // look for state or subshell number
      if ( number <= LevelID::continuum ) {

        if ( ( mass == 0 ) && ( number != 0 ) ) {

          throw std::out_of_range( "An element cannot have a non-zero level number" );
        }

        // determine the level
        LevelID state( number );

        // update registry and return the index
        return updateRegistry( std::move( element ), std::move( mass ), std::move( state ) );
      }
      else if ( mass == 0 ) {

        // determine the level
        ElectronSubshellID subshell( number );

        // update registry and return the index
        return updateRegistry( std::move( element ), std::move( subshell ) );
      }
      else {

        throw std::out_of_range( "The za \'" + std::to_string( za ) + "\' and level or subshell number \'"
                                 + std::to_string( number ) + "\' does not define a standard particle or ion" );
      }
    }
    catch ( ... ) {

      throw std::out_of_range( "The za \'" + std::to_string( za ) + "\' and level or subshell number \'"
      + std::to_string( number ) + "\' does not define a standard particle or ion" );
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
    else if ( std::regex_match( string, match, ion_id_regex ) ) {

      // data entries
      ElementID element( match[1] );
      ElectronSubshellID subshell( match[2] );

      // update registry and return the index
      return updateRegistry( std::move( element ), std::move( subshell ) );
    }

    throw std::out_of_range( "Not a particle symbol or name: \'" + string + "\'" );
  }
}
