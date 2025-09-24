void processKeys( const std::vector< Key >& keys ) {

  for ( const auto& key : keys ) {

    auto lower = std::get< 1 >( key ).lowerEnergy();
    auto upper = std::get< 1 >( key ).upperEnergy();
    auto product = std::get< 2 >( key );

    auto e_iter = std::lower_bound( this->energies_.begin(), this->energies_.end(), lower );
    if ( e_iter == this->energies_.end() || 
         ( e_iter != this->energies_.end() && *e_iter != lower ) ) {

      this->energies_.insert( e_iter, lower );
    }
    e_iter = std::lower_bound( this->energies_.begin(), this->energies_.end(), upper );
    if ( e_iter == this->energies_.end() || 
         ( e_iter != this->energies_.end() && *e_iter != upper ) ) {

      this->energies_.insert( e_iter, upper );
    }

    auto p_iter = std::lower_bound( this->products_.begin(), this->products_.end(), product );
    if ( p_iter == this->products_.end() || 
         ( p_iter != this->products_.end() && *p_iter != product ) ) {

      this->products_.insert( p_iter, product );
    }
  }
}

void generateMetadata() {

  this->reaction_ = std::get< 0 >( this->rowKeys().front() );

  this->processKeys( this->rowKeys() );
  if ( this->isOffDiagonal() ) {

    this->processKeys( this->columnKeys() );
  }
}
