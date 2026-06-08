#ifndef NJOY_CONSTANTS
#define NJOY_CONSTANTS

// system includes

// other includes

namespace njoy {
namespace constants {

  // default psychic constants
  namespace psychic {

    constexpr double tolerance = 1e-10;
    constexpr double largest_allowed_negative_eigenvalue = -1e-10;
    constexpr double smallest_eigenvalue_ratio = 1e-8;
  }

  // default linearisation tolerance and threshold
  namespace linearisation {

    constexpr double tolerance = 0.001;
    constexpr double threshold = 1e-10;
  }

  // default integration tolerance
  namespace integration {

    constexpr double tolerance = 1e-8;
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

  // CODATA 2018 - particle mass in amu
  // constexpr double neutron_mass  = 1.008664915950;
  // constexpr double proton_mass   = 1.007276466621;
  // constexpr double deuteron_mass = 2.013553212745;
  // constexpr double triton_mass   = 3.015500716210;
  // constexpr double helion_mass   = 3.014932247175;
  // constexpr double alpha_mass    = 4.001506179127;
  // CODATA 2022 - particle mass in amu
  constexpr double neutron_mass  = 1.008664916060;
  constexpr double proton_mass   = 1.0072764665789;
  constexpr double deuteron_mass = 2.013553212544;
  constexpr double triton_mass   = 3.015500715970;
  constexpr double helion_mass   = 3.014932246932;
  constexpr double alpha_mass    = 4.001506179129;

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
