#ifndef NJOY_DRYAD_UNIFORMDISTRIBUTIONTYPE
#define NJOY_DRYAD_UNIFORMDISTRIBUTIONTYPE

// system includes

// other includes

namespace njoy {
namespace dryad {

/**
 *  @enum
 *  @brief The uniform distirbution types
 *
 *  This enum is used to differentiate uniform distribution types, either discrete
 *  values or intervals.
 */
enum class UniformDistributionType : short {

  /**
   *  The uniform distribution is given for discrete values
   */
  Discrete = 1,
  /**
   *  The uniform distribution is given for intervals
   */
  Interval = 2
};

} // dryad namespace
} // njoy namespace

#endif
