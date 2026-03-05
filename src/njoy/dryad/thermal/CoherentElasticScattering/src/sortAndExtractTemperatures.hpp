void sortAndExtractTemperatures() {

  std::sort( this->braggEdges().begin(), this->braggEdges().end(),
             [] ( auto&& left, auto&& right )
                { return left.temperature() < right.temperature(); } );

  this->moderatorTemperatures().resize( this->braggEdges().size() );
  std::transform( this->braggEdges().begin(), this->braggEdges().end(),
                  this->moderatorTemperatures().begin(),
                  [] ( auto&& data )
                     { return data.temperature(); } );
}