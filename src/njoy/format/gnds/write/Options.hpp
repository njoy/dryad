#ifndef NJOY_FORMAT_GNDS_WRITE_OPTIONS
#define NJOY_FORMAT_GNDS_WRITE_OPTIONS

// system includes

// other includes

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief GNDS output options
   */
  struct Options {

    // precision: number of digits used to print numbers
    //            for floating point numbers: the number of digits after the
    //            decimal point is equal to precision - 1
    int precision = 10;
  };

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
