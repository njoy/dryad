void updateMetadata() {

  // get all the energy groups in the metadata
  auto group = std::get< 1 >( this->keys().front() );
  auto iter = std::find_if( this->keys().begin() + 1, this->keys().end(),
                            [&group] ( const auto& tuple )
                                     { return group == std::get< 1 >( tuple ); } );
  this->energies_.resize( std::distance( this->keys().begin(), iter ) + 1 );
  this->energies_.front() = group.lowerEnergy();
  std::transform( this->keys().begin(), iter, this->energies_.begin() + 1,
                  [] ( const auto& tuple ) { return std::get< 1 >( tuple ).upperEnergy(); } );

  // calculate stride on the reaction dimension and loop
  auto stride = this->energies_.size() - 1;
  for ( unsigned int i = 0; i < this->keys().size(); i = i + stride ) {

    this->reactions_.emplace_back( std::get< 0 >( this->keys()[i] ) );
  }
}
