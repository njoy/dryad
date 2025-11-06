#ifndef NJOY_DRYAD_RESONANCES_KINEMATICS
#define NJOY_DRYAD_RESONANCES_KINEMATICS

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace resonances {

/**
 *  @enum
 *  @brief The kinematics option
 *
 *  This enum is used to differentiate between relativistic and non-relativistic
 *  kinematics in resonance reconstruction.
 */
enum class Kinematics : short {

  /**
   *  Non-relativistic kinematics
   */
  NonRelativistic = 0,
  /**
   *  Relativistic kinematics
   */
  Relativistic = 1
};

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
