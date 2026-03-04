void sortAndExtractTemperatures() {

  std::sort( this->braggEdges().begin(), this->braggEdges().end(),
             [] ( auto&& left, auto&& right )
                { return left.temperature() < right.temperature(); } );

  this->temperatures().resize( this->braggEdges().size() );
  std::transform( this->braggEdges().begin(), this->braggEdges().end(),
                  this->temperatures().begin(),
                  [] ( auto&& data )
                     { return data.temperature(); } );
}