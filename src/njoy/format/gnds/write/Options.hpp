#ifndef NJOY_FORMAT_GNDS_WRITE_OPTIONS
#define NJOY_FORMAT_GNDS_WRITE_OPTIONS

// system includes
#include <string>

// other includes

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief GNDS output options
   */
  struct Options {

    // default units
    std::string default_charge_unit = "e";
    std::string default_energy_unit = "eV";
    std::string default_mass_unit = "amu";

    // units to be used
    std::string charge_unit = "e";
    std::string energy_unit = "eV";
    std::string mass_unit = "amu";

    // precision: number of digits used to print numbers
    //            for floating point numbers: the number of digits after the
    //            decimal point is equal to precision - 1
    int precision = 10;

    // indent: indentation per level in the xml structure
    int indent = 2;
  };

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
