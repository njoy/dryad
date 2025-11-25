/**
 *  @brief Generate the symbol for an atom with subshell vacancies
 *
 *  @param element     the particle element
 *  @param vacancies   the subshells with vacancies
 */
static std::string
generateIonSymbol( const ElementID element, const std::vector< ElectronSubshellID >& vacancies ) {

  std::string symbol = element.symbol() + '{';
  for ( unsigned int i =0; i < vacancies.size(); ++i ) {

    if ( vacancies[i].isNonRelativistic() ) {

      throw std::invalid_argument( "Electron subshell identifiers used for particle identifiers must be relativistic" );
    }

    if ( i != 0 ) {

      symbol += ',';
    }
    symbol += vacancies[i].symbol();
  }
  symbol += '}';
  return symbol;
}

/**
 *  @brief Generate the alternative symbols for an atom with subshell vacancies
 *
 *  @param element     the particle element
 *  @param vacancies   the subshells with vacancies
 */
static std::vector< std::string >
generateIonAlternatives( const std::string& symbol, const ElementID element, const std::vector< ElectronSubshellID >& vacancies ) {

  //! @todo use a proper cartesian product in the future, for now: only do this for size() < 3

  std::vector< std::string > alternatives;
  std::string prefix = element.symbol() +'{';

  if ( vacancies.size() > 2 ) {

    throw std::runtime_error( "Atoms can currently only have 2 or less vacancies, contact a developer" );
  }

  alternatives.emplace_back( vacancies.front().symbol() );
  alternatives.insert( alternatives.end(), vacancies.front().alternatives().begin(), vacancies.front().alternatives().end() );

  std::vector< std::string > temp;
  for ( unsigned int i = 1; i < vacancies.size(); ++i ) {

    for ( unsigned int j = 0; j < alternatives.size(); ++j ) {

      temp.emplace_back( alternatives[j] + ',' + vacancies[i].symbol() );
      for ( unsigned int k = 0; k < vacancies[i].alternatives().size(); ++k ) {

        temp.emplace_back( alternatives[j] + ',' + vacancies[i].alternatives()[k] );
      }
    }
    std::swap( alternatives, temp );
    temp.clear();
  }

  for ( unsigned int i = 0; i < alternatives.size(); ++i ) {

    alternatives[i].insert( 0, prefix );
    alternatives[i] += '}';
  }

  auto iter = std::find( alternatives.begin(), alternatives.end(), symbol );
  if ( iter != alternatives.end() ) {

    alternatives.erase( iter );
  }

  return alternatives;
}

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

  std::string symbol = generateIonSymbol( element, vacancies );
  std::vector< std::string > alternatives = generateIonAlternatives( symbol, element, vacancies );

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
 *  @param element     the particle element
 *  @param vacancies   the subshells with vacancies
 */
static std::size_t getIndex( ElementID element, std::vector< ElectronSubshellID > vacancies ) {

  try {

    return string_conversion_dictionary.at( generateIonSymbol( element, vacancies ) );
  }
  catch ( ... ) {

    // update registry and return the index
    return updateRegistry( std::move( element ), std::move( vacancies ) );
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
      auto shells = tools::split( match[2], ',' );
      std::vector< ElectronSubshellID > vacancies( shells.size() );
      std::transform( shells.begin(), shells.end(), vacancies.begin(),
                      [] ( auto&& vacancy ) { return ElectronSubshellID( vacancy ); } );

      // update registry and return the index
      return updateRegistry( std::move( element ), std::move( vacancies ) );
    }

    throw std::invalid_argument( "Not a particle symbol or name: \'" + string + "\'" );
  }
}
