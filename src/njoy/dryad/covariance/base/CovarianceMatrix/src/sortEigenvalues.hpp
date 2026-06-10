/**
 *  @brief Sort the eigenvalues in descending order
 */
void sortEigenvalues() {

  if ( this->eigenvalues().has_value() ) {

    // get the order (eigenvalues are in descending order)
    std::vector< std::size_t > order( this->eigenvalues()->size() );
    std::iota( order.begin(), order.end(), 0 );
    std::sort( order.begin(), order.end(),
               [&] ( auto&& i, auto&& j ) {

                 return this->eigenvalues().value()[i] > this->eigenvalues().value()[j];
               } );

    // sort the eigenvalues (descending order) and perform a permutation on the eigenvectors
    std::sort( this->eigenvalues()->rbegin(), this->eigenvalues()->rend() );
    tools::apply_permutation( this->eigenvectors().value(), order );
  }
}
