#ifndef NJOY_DRYAD_REFERENCEFRAME
#define NJOY_DRYAD_REFERENCEFRAME

// system includes

// other includes

namespace njoy {
namespace dryad {

/**
 *  @enum
 *  @brief The reference frame types
 *
 *  This enum is used to differentiate reference frames for distribution data
 *  in the ProjectileTarget. We currently distinguish two different frames:
 *  centre of mass or laboratory.
 */
enum class ReferenceFrame : bool {

  Laboratory,   /**< The data is given in the laboratory frame of reference */
  CentreOfMass  /**< The data is given in the centre of mass frame of reference */
};

} // dryad namespace
} // njoy namespace

#endif
