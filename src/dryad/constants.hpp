#ifndef NJOY_DRYAD_CONSTANTS
#define NJOY_DRYAD_CONSTANTS

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace constants {

  constexpr double pi = 3.141592653589793;

  // CODATA 2022 - atomic mass unit in kg
  constexpr double amu = 1.66053906892e-27;

  // CODATA 2022 - elementary charge in Coulomb
  constexpr double e = 1.602176634e-19;

  // CODATA 2022 - reduced Planck constant in ev s
  constexpr double hbar = 6.582119569e-16;

  // CODATA 2022 - vacuum electric permittivity in F / m = Coulomb^2 kg^−1 m^−3 s^2
  constexpr double epsilon0 = 8.8541878188e-12;

  // SI prefixes
  constexpr double giga = 1e+9;
  constexpr double mega = 1e+6;
  constexpr double kilo = 1e+3;
  constexpr double deci = 1e-1;
  constexpr double centi = 1e-2;
  constexpr double mili = 1e-3;
  constexpr double micro = 1e-6;
  constexpr double nano = 1e-9;
  constexpr double pico = 1e-12;
  constexpr double femto = 1e-15;

} // constants namespace
} // dryad namespace
} // njoy namespace

#endif
