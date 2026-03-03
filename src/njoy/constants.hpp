#ifndef NJOY_CONSTANTS
#define NJOY_CONSTANTS

// system includes

// other includes

namespace njoy {
namespace constants {

  // default linearisation tolerance and threshold
  namespace linearisation {

    constexpr double tolerance = 0.001;
    constexpr double threshold = 1e-10;
  }

  constexpr double pi = 3.141592653589793;

  // CODATA 2018 - atomic mass unit in kg
  // constexpr double amu = 1.66053906660e-27;
  // CODATA 2022 - atomic mass unit in kg
  constexpr double amu = 1.66053906892e-27;

  // CODATA 2018 - elementary charge in Coulomb
  // constexpr double e = 1.602176634e-19;
  // CODATA 2022 - elementary charge in Coulomb
  constexpr double e = 1.602176634e-19;

  // CODATA 2018 - Planck constant in J s
  // constexpr double h = 6.62607015e-34;
  // CODATA 2022 - Planck constant in J s
  constexpr double h = 6.62607015e-34;

  // CODATA 2018 - reduced Planck constant in ev s
  // constexpr double hbar = 6.582119569e-16;
  // CODATA 2022 - reduced Planck constant in ev s
  constexpr double hbar = 6.582119569e-16;

  // CODATA 2018 - light speed in m / s
  // constexpr double c = 299792458;
  // CODATA 2022 - light speed in m / s
  constexpr double c = 299792458;

  // CODATA 2018 - vacuum electric permittivity in F / m = Coulomb^2 kg^−1 m^−3 s^2
  // constexpr double epsilon0 = 8.8541878128e-12;
  // CODATA 2022 - vacuum electric permittivity in F / m = Coulomb^2 kg^−1 m^−3 s^2
  constexpr double epsilon0 = 8.8541878188e-12;

  // CODATA 2018 - neutron mass in amu
  // constexpr double neutron_mass = 1.00866491574;
  // CODATA 2022 - neutron mass in amu
  constexpr double neutron_mass = 1.00866491606;

  // CODATA 2018 - electron mass in amu
  // constexpr double electron_mass = 5.48579909065e-4;
  // CODATA 2022 - electron mass in amu
  constexpr double electron_mass = 5.485799090441e-4;

  // CODATA 2018 - classical electron radius in m
  // constexpr double electron_radius = 2.8179403262e-15;
  // CODATA 2022 - classical electron radius in m
  constexpr double electron_radius = 2.8179403205e-15;

  // SI prefixes
  constexpr double peta = 1e+15;
  constexpr double tera = 1e+12;
  constexpr double giga = 1e+9;
  constexpr double mega = 1e+6;
  constexpr double kilo = 1e+3;
  constexpr double hecto = 1e+2;
  constexpr double deca = 1e+1;
  constexpr double deci = 1e-1;
  constexpr double centi = 1e-2;
  constexpr double mili = 1e-3;
  constexpr double micro = 1e-6;
  constexpr double nano = 1e-9;
  constexpr double pico = 1e-12;
  constexpr double femto = 1e-15;

  // common conversion constants
  constexpr double m2_to_barn = 1e+28;

  // derived constants

  // electron rest mass in eV (~511 keV)
  constexpr double electron_rest_mass = electron_mass * c * c * amu / e;

} // constants namespace
} // njoy namespace

#endif
