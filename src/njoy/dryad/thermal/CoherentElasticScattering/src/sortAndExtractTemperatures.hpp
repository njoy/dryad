void sortAndExtractTemperatures() {

  std::sort( this->braggEdgeData().begin(), this->braggEdgeData().end(),
             [] ( auto&& left, auto&& right )
                { return left.temperature() < right.temperature(); } );

  this->temperatures().resize( this->braggEdgeData().size() );
  std::transform( this->braggEdgeData().begin(), this->braggEdgeData().end(),
                  this->temperatures().begin(),
                  [] ( auto&& data )
                     { return data.temperature(); } );
}