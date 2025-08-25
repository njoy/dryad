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

    // split the reaction symbol in incident and outgoing particles
    auto strings = njoy::tools::split( string, "->" );
    if ( strings.size() == 2 ) {

      // split the projectile and target
      auto incident = njoy::tools::split( strings[0], ',' );
      if ( incident.size() == 2 ) {

        ParticleID projectile( incident[0] );
        ParticleID target( incident[1] );

        // check for partial designator [xxxx]
        if ( strings[1].back() == ']' &&
             strings[1].find( "[all]" ) == std::string::npos &&
             strings[1].find( "[continuum]" ) == std::string::npos ) {

          auto pos = strings[1].find( '[' );
          if ( pos != std::string::npos ) {

            // create the reaction type
            auto type = ReactionType( strings[1].substr( pos + 1, strings[1].size() - pos - 2 ) );
            return getIndex( projectile, target, type );
          }
        }
        else {

          // split the outgoing particles
          auto outgoing = njoy::tools::split( strings[1], ',' );
          if ( outgoing.size() > 1 ) {

            // the last one should be the residual
            ParticleID residual( outgoing.back() );

            // get the outgoing particles
            auto particles = strings[1].substr( 0, strings[1].size() - outgoing.back().size() - 1 );
            if ( residual.e() != LevelID::all ) {

              if ( residual.e() == LevelID::continuum ) {

                particles += "(c)";
              }
              else {

                particles += "(" + std::to_string( residual.e() ) + ")";
              }
            }

            // create the reaction type and verify against the residual
            auto type = ReactionType( particles );
            if ( type.resolve( projectile, target ) == residual ) {

              return getIndex( projectile, target, type );
            }
          }
          else if ( outgoing.size() == 1 ) {

            // create the reaction type
            auto type = ReactionType( outgoing.front() );
            return getIndex( projectile, target, type );
          }
        }
      }
    }

    // if you get to this point, this is not a reaction string
    throw std::invalid_argument( "\'" + string + "\' does not define a "
                                 "reaction identifier string" );
  }
}
