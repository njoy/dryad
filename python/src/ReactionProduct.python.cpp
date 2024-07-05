// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/ReactionProduct.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReactionProduct( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::ReactionProduct;
  using ParticleID = njoy::dryad::ParticleID;
  using Multiplicity = njoy::dryad::ReactionProduct::Multiplicity;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ReactionProduct",
    "The data associated to a single reaction product"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID, Multiplicity >(),
    python::arg( "id" ), python::arg( "multiplicity" ),
    "Initialise the reaction\n\n"
    "Arguments:\n"
    "    self           the reaction\n"
    "    id             the reaction product identifier\n"
    "    multiplicity   the multiplicity of the reaction product"
  )
  .def_property_readonly(

    "identifier",
    &Component::identifier,
    "The reaction product identifier"
  )
  .def_property_readonly(

    "multiplicity",
    &Component::multiplicity,
    "The multiplicity"
  )
  .def_property_readonly(

    "is_linearised",
    &Component::isLinearised,
    "Flag indicating whether or not the data is linearised"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the reaction product data and return a new reaction product\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    tolerance   the linearisation tolerance"
  )
  .def(

    "linearise_inplace",
    &Component::lineariseInplace,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the reaction product data inplace\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    tolerance   the linearisation tolerance"
  );
}
