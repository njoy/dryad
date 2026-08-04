#ifndef NJOY_FORMAT_GNDS_WRITE_TOSTRING
#define NJOY_FORMAT_GNDS_WRITE_TOSTRING

// system includes
#include <string>
#include <sstream>
#include <iomanip>

// other includes
#include "njoy/format/gnds/write/Options.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Convert a double to string
   *
   *  @param[in] value     the value
   *  @param[in] options   the gnds write options
   */
  std::string toString( const Options& options, double value ) {

    std::ostringstream out;
    out << std::setprecision( options.precision ) << value;

    return out.str();
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
