#ifndef NJOY_DRYAD_ID_REACTIONID
#define NJOY_DRYAD_ID_REACTIONID

// system includes
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/id/ReactionType.hpp"

namespace njoy {
namespace dryad {
namespace id {

  using ReactionID = std::string;

//  /**
//   *  @class
//   *  @brief The reaction types, with associated symbol, aliases, particles, etc.
//   *
//   *  The ReactionType can be used to identify reaction types. For the moment, only
//   *  registered types can be used. In the future, we will extend this so that users
//   *  can create types other than the ones currently registered.
//   *
//   *  For more information on how to create instances of ReactionType, see the
//   *  Jupyter notebook dryad-identifiers.ipynb under python/examples.
//   */
//  class NewReactionID {
//
//    /* helper class */
//    #include "dryad/id/ReactionID/Entry.hpp"
//
//    static inline std::vector< Entry > entries{};
//    static inline std::unordered_map< std::string, std::size_t > string_conversion_dictionary{};
//
//    /* fields */
//    std::size_t index_;
//
//    /* auxiliary functions */
//    #include "dryad/id/ReactionID/src/getIndex.hpp"
//
//  public:
//
//    /* constructor */
//    #include "dryad/id/ReactionID/src/ctor.hpp"
//
//  };

} // id namespace
} // dryad namespace
} // njoy namespace

#endif
