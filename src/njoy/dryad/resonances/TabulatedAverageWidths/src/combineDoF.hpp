static std::optional< int > combineDoF( const std::optional< int >& left, const std::optional< int >& right ) {
  if ( left.has_value() && right.has_value() ) {
    if ( left != right ) {
      Log::error( "TabulatedAverageWidths::combineDoF: conflicting degrees of freedom "
                  "values: {} and {}", left.value(), right.value() );
      throw std::exception();
    }
    return left;
  }
  return left.has_value() ? left : right;
}