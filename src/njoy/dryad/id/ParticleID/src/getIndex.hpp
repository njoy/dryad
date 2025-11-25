/**
 *  @brief Update registry
 *
 *  @param element   the particle element
 *  @param mass      the particle mass number
 *  @param level     the particle level
 */
static std::size_t updateRegistry( ElementID element, int mass, LevelID level ) {

  // the index for the new identifier
  std::size_t index = entries.size();

  int number = element.number() * 1000000 + mass * 1000 + level.number();
  std::vector< std::string > alternatives = {};
  std::string symbol = element.symbol() + std::to_string( mass );
  if ( level.number() != 0 ) {

    if ( ( level.number() == LevelID::continuum ) || ( level.number() == LevelID::all ) ) {

      alternatives.emplace_back( symbol + std::string( "_e" ) +
                                 std::to_string( level.number() ) );
    }
    symbol += level.symbol();
  }
  else {

    alternatives.emplace_back( symbol + std::string( "_e0" ) );
  }

  // create the data entry and set conversion
  entries.emplace_back( element, mass, level,
                        std::move( symbol ), std::move( alternatives ) );

  number_conversion_dictionary[ number ] = index;
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
 *  @param element     the particle element
 *  @param vacancies   the subshells with vacancies
 */
static std::size_t updateRegistry( ElementID element,
                                   std::vector< ElectronSubshellID > vacancies ) {

  // the index for the new identifier
  std::size_t index = entries.size();

  if ( vacancies.front().isNonRelativistic() ) {

    throw std::invalid_argument( "Electron subshell identifiers used for particle identifiers must be relativistic" );
  }

  std::string symbol = element.symbol() + std::string( "{" ) + vacancies.front().symbol() + std::string( "}" );
  std::vector< std::string > alternatives;
  for ( const auto& alternative : vacancies.front().alternatives() ) {

    alternatives.emplace_back( element.symbol() + std::string( "{" ) + alternative + std::string( "}" ) );
  }

  // create the data entry and set conversion
  entries.emplace_back( element, std::move( vacancies ),
                        std::move( symbol ),
                        std::move( alternatives ) );

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
 *  @param element   the particle element
 *  @param mass      the particle mass number
 *  @param level     the particle level
 */
static std::size_t getIndex( ElementID element, int mass, LevelID level ) {

  try {

    return number_conversion_dictionary.at( ( element.number() * 1000 + mass ) * 1000 + level.number() );
  }
  catch ( ... ) {

    // update registry and return the index
    return updateRegistry( std::move( element ), std::move( mass ), std::move( level ) );
  }
}

/**
 *  @brief Retrieve the index to the particle information entry
 *
 *  @param element    the particle element
 *  @param subshell   the particle subshell
 */
static std::size_t getIndex( ElementID element, ElectronSubshellID subshell ) {

  try {

    return string_conversion_dictionary.at( element.symbol() + "{" + subshell.symbol() + "}" );
  }
  catch ( ... ) {

    // update registry and return the index
    return updateRegistry( std::move( element ), { std::move( subshell ) } );
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
      LevelID level( match[4] != ""
                     ? match[5] != "" ? std::stoi( match[6] )
                                      : match[7] != "" ? LevelID::all
                                                       : LevelID::continuum
                     : 0 );

      // update registry and return the index
      return updateRegistry( std::move( element ), std::move( mass ), std::move( level ) );
    }
    else if ( std::regex_match( string, match, ion_id_regex ) ) {

      // data entries
      ElementID element( match[1] );
      ElectronSubshellID subshell( match[2] );

      // update registry and return the index
      return updateRegistry( std::move( element ), { std::move( subshell ) } );
    }

    throw std::invalid_argument( "Not a particle symbol or name: \'" + string + "\'" );
  }
}
