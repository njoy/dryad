#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDWIDTHCONVERSIONFACTOR
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDWIDTHCONVERSIONFACTOR

#include <optional>
#include <variant>

//other includes
#include "njoy/dryad/resonances/HardSpherePenetrability.hpp"
#include "njoy/dryad/resonances/CoulombPenetrability.hpp"
#include "njoy/dryad/resonances/TabulatedWaveFunction.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  class UnresolvedWidthConversionFactor {

    private:
      
      double reference_energy_;
      
    public:
     
      using Penetrability = std::variant< double,
                                          HardSpherePenetrability,
                                          CoulombPenetrability,
                                          TabulatedWaveFunction >;
  }
}
}
}
