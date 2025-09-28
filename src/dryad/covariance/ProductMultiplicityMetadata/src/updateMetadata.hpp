void updateMetadata() {

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
  this->energies_.emplace_back( std::get< 1 >( this->keys().front() ).lowerEnergy() );
  for ( unsigned int i = 0; i < std::distance( this->keys().begin(), iter ); i = i + stride ) {

    this->energies_.emplace_back( std::get< 1 >( this->keys()[i] ).upperEnergy() );
  }

  // calculate stride on the reaction dimension and loop
  stride = ( this->energies_.size() - 1 ) * this->products_.size();
  for ( unsigned int i = 0; i < this->keys().size(); i = i + stride ) {

    this->reactions_.emplace_back( std::get< 0 >( this->keys()[i] ) );
  }
}
