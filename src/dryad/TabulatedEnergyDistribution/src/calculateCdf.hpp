void calculateCdf( bool set_cdf_to_one = false ) {

  std::vector< double > cdf = this->pdf().cumulativeIntegral();
  if ( set_cdf_to_one ) {

    cdf.back() = 1.;
  }
  this->cdf_ = TabulatedEnergyDistributionFunction( this->pdf().energies(),
                                                    std::move( cdf ),
                                                    this->pdf().boundaries(),
                                                    this->pdf().interpolants() );
}
