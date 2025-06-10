/**
 *  @brief Retrieve the index to the reaction identifier information entry
 *
 *  @param projectile   the projectile
 *  @param target       the target
 *  @param type         the reaction type
 */
static std::size_t getIndex( const ParticleID& projectile, const ParticleID& target,
                             const ReactionType& type ) {

  auto key = std::make_tuple( projectile, target, type );
  auto iter = tuple_conversion_dictionary.find( key );
  if ( iter != tuple_conversion_dictionary.end() ) {

    return iter->second;
  }
  else {

    // index of the new entry
    auto index = entries.size();

    // create entry and set up lookup
    entries.emplace_back( projectile, target, type );
    tuple_conversion_dictionary[ std::make_tuple( projectile, target, type ) ] = index;
    string_conversion_dictionary[ entries.back().longSymbol() ] = index;

    return index;
  }
}

/**
 *  @brief Retrieve the index to the reaction type information entry
 *
 *  @param string   the reaction identifier string
 */
static std::size_t getIndex( const std::string& string ) {

  try {

    return string_conversion_dictionary.at( string );
  }
  catch ( ... ) {

    throw std::invalid_argument( "\'" + string + "\' does not define a "
                                 "registered reaction identifier string" );
  }
}
