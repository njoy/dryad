private:

template < typename LeftTuple, typename RightTuple, std::size_t... Is >
static auto compare_key_impl( const LeftTuple& left, const RightTuple& right,
                              std::index_sequence< Is... > ) {

  auto compare = [] ( auto&& left, auto&& right ) {

    if ( left == std::nullopt || left == right ) {

      return true;
    }
    return false;
  };

  return ( compare( std::get< Is >( left ), std::get< Is >( right ) ) && ... );
}

static auto compare_key( const std::tuple< std::optional< Ts >... >& left,
                         const std::tuple< Ts... >& right ) {

  return compare_key_impl( left, right, std::make_index_sequence< sizeof...( Ts ) >{} );
}

public:

std::vector< std::size_t >
selection( const std::optional< Ts >&... args ) const {

  Selection select = std::make_tuple( args... );

  std::vector< std::size_t > indices;
  for ( std::size_t i = 0; i < this->keys().size(); ++i ) {

    if ( compare_key( select, this->keys()[i] ) ) {

      indices.emplace_back( i );
    }
  }
  return indices;
}
