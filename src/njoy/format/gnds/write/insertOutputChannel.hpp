#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTOUTPUTCHANNEL
#define NJOY_FORMAT_GNDS_WRITE_INSERTOUTPUTCHANNEL

// system includes
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertQ.hpp"
#include "njoy/format/gnds/write/insertMultiplicity.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert output channel data from a reaction into a gnds node
   *
   *  Only primary reactions generate a
   *
   *  @param[in,out] parent     the parent node
   *  @param[in]     option     the gnds write options
   *  @param[in]     reaction   the reaction
   *  @param[in]     style      the style label to be used
   */
  inline pugi::xml_node
  insertOutputChannel( pugi::xml_node& parent,
                       const Options& options,
                       const dryad::Reaction& reaction,
                       const std::string& style ) {

    pugi::xml_node node;

    if ( reaction.isPrimaryReaction() || reaction.hasProducts() ) {

      node = parent.append_child( "outputChannel" );

      if ( reaction.isPrimaryReaction() ) {

        insertQ( node, options, reaction.reactionQValue().value(),
                 reaction.crossSection().lowerEnergyLimit(),
                 reaction.crossSection().upperEnergyLimit(),
                 style );
      }

      if ( reaction.hasProducts() ) {

        double min = reaction.crossSection().lowerEnergyLimit();
        double max = reaction.crossSection().upperEnergyLimit();

        auto products_node = node.append_child( "products" );
        for ( const auto& product : reaction.products() ) {

          if ( product.chainIndex() == 0 ) {

            auto product_node = products_node.append_child( "product" );
            product_node.append_attribute( "pid" ) = product.productIdentifier().symbol();
            product_node.append_attribute( "label" ) = product.productIdentifier().symbol();

            insertMultiplicity( product_node, options, product.multiplicity(), min, max, style );

            auto distribution_node = product_node.append_child( "distribution" );
            distribution_node = distribution_node.append_child( "unspecified" );
            distribution_node.append_attribute( "label" ) = style.c_str();
            distribution_node.append_attribute( "productFrame" ) = "lab";
          }
        }
      }
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
