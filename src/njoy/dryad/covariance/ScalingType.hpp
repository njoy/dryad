#ifndef NJOY_DRYAD_COVARIANCE_SCALINGTYPE
#define NJOY_DRYAD_COVARIANCE_SCALINGTYPE

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace covariance {

/**
 *  @enum
 *  @brief The variance scaling type
 *
 *  This enum is used to differentiate variance scaling types. We currently
 *  distinguish two types of scaling: inverse and direct proportional.
 */
enum class ScalingType : short {

  /**
   *  The variance of group j is inversely proportional to the width of group j
   */
  Inverse = 1,
  /**
   *  The variance of group j is directly proportional to the width of group j
   */
  Direct = 2
};

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
