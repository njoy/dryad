void updateMetadata() {

  //! @todo once we move to c++23, use ranges instead of for loops

  // get all the energy groups in the metadata
  auto group = std::get< 2 >( this->keys().front() );
  auto iter = std::find_if( this->keys().begin() + 1, this->keys().end(),
                            [&group] ( const auto& tuple )
                                     { return group == std::get< 2 >( tuple ); } );
  this->energies_.resize( std::distance( this->keys().begin(), iter ) + 1 );
  this->energies_.front() = group.lowerEnergy();
  std::transform( this->keys().begin(), iter, this->energies_.begin() + 1,
                  [] ( const auto& tuple ) { return std::get< 2 >( tuple ).upperEnergy(); } );

  // calculate stride on the moment dimension and loop
  auto stride = this->energies_.size() - 1;
  auto moment = std::get< 1 >( this->keys().front() );
  iter = std::find_if( this->keys().begin() + stride, this->keys().end(),
                       [&moment] ( const auto& tuple )
                                  { return moment == std::get< 1 >( tuple ); } );
  this->moments_.resize( std::distance( this->keys().begin(), iter ) / stride );
  for ( unsigned int i = 0; i < std::distance( this->keys().begin(), iter ); i = i + stride ) {

    this->moments_[ i / stride] = std::get< 1 >( this->keys()[i] );
  }

  // calculate stride on the reaction dimension and loop
  stride = ( this->energies_.size() - 1 ) * this->moments_.size();
  this->reactions_.resize( this->keys().size() / stride );
  for ( unsigned int i = 0; i < this->keys().size(); i = i + stride ) {

    this->reactions_[ i / stride ] = std::get< 0 >( this->keys()[i] );
  }
}
