/**
 *  @brief Reconstruct metadata from keys
 *
 *  This method extracts the unique reactions, energy groups and products from the
 *  keys. This function relies on the fact that tuple keys are lexographically
 *  sorted (as implemented by the operator< on std::tuple).
 */
void updateMetadata() {

  //! @todo once we move to c++23, use ranges instead of for loops

  // get all the products in the metadata
  auto product = std::get< 2 >( this->keys().front() );
  auto iter = std::find_if( this->keys().begin() + 1, this->keys().end(),
                            [&product] ( const auto& tuple )
                                       { return product == std::get< 2 >( tuple ); } );
  this->products_.resize( std::distance( this->keys().begin(), iter ) );
  std::transform( this->keys().begin(), iter, this->products_.begin(),
                  [] ( const auto& tuple ) { return std::get< 2 >( tuple ); } );

  // calculate stride on the energy dimension and loop
  auto stride = this->products_.size();
  auto group = std::get< 1 >( this->keys().front() );
  iter = std::find_if( this->keys().begin() + stride, this->keys().end(),
                       [&group] ( const auto& tuple )
                                { return group == std::get< 1 >( tuple ); } );
  this->energies_.resize( std::distance( this->keys().begin(), iter ) / stride + 1 );
  this->energies_.front() = std::get< 1 >( this->keys().front() ).lowerEnergy();
  for ( unsigned int i = 0; i < std::distance( this->keys().begin(), iter ); i = i + stride ) {

    this->energies_[ i / stride + 1 ] = std::get< 1 >( this->keys()[i] ).upperEnergy();
  }

  // calculate stride on the reaction dimension and loop
  stride = ( this->energies_.size() - 1 ) * this->products_.size();
  this->reactions_.resize( this->keys().size() / stride );
  for ( unsigned int i = 0; i < this->keys().size(); i = i + stride ) {

    this->reactions_[ i / stride ] = std::get< 0 >( this->keys()[i] );
  }
}
