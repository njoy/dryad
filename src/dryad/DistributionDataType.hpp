#ifndef NJOY_DRYAD_DISTRIBUTIONDATATYPE
#define NJOY_DRYAD_DISTRIBUTIONDATATYPE

// system includes

// other includes

namespace njoy {
namespace dryad {

/**
 *  @enum
 *  @brief The distribution data type of a reaction product
 *
 *  This enum is used to differentiate between the various distribution data
 *  types that are available for a reaction product.
 */
enum class DistributionDataType : short {

  TwoBody,      /**< The distribution data is given as two body scattering */
  Uncorrelated, /**< The distribution data is uncorrelated */
  Coherent,     /**< The distribution data is for coherent scattering for photoatomic interactions */
  Incoherent    /**< The distribution data is for incoherent scattering for photoatomic interactions */
};

} // dryad namespace
} // njoy namespace

#endif
