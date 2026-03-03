// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/external/ComptonProfiles.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace external {

void wrapComptonProfiles( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::external::ComptonProfiles;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ComptonProfiles",
    "Compton profile data and models\n\n"
    "Compton profiles are currently not available in standard evaluated nuclear data\n"
    "files. The ComptonProfiles class is basically going to contain factory functions\n"
    "to produce Compton profiles for a given atom, either based on external data or\n"
    "possibly model calculations.\n\n"
    "Currently we only have tabulated data based on Biggs, Mendelsohn and Mann\n"
    "calculated profiles from the following reference:\n"
    "  F. Biggs, L. B. Mendelsohn, J. B. Mann,\n"
    "  Hartree-Fock Compton profiles for the elements,\n"
    "  Atomic data and nuclear data table, 16, 201-309 (1975)"
  );

  // wrap the component
  component
  .def_static(

    "biggs_mendelsohn_mann_subshell_identifiers",
    &Component::biggsMendelsohnMannSubshellIdentifiers,
    python::arg( "z" ),
    "Return the electron subshell identifiers for a given z number \n"
    "for which Biggs, Mendelsohn and Mann Compton profiles are available\n\n"
    "Parameters\n"
    "----------\n"
    "    z : int\n"
    "         the z number of the atom"
  )
  .def_static(

    "biggs_mendelsohn_mann_profiles",
    &Component::biggsMendelsohnMannProfiles,
    python::arg( "z" ), python::arg( "normalise" ),
    "Return Biggs, Mendelsohn and Mann Compton profiles for a given z number\n\n"
    "Parameters\n"
    "----------\n"
    "    z : int\n"
    "         z number of the atom\n"
    "    normalise : bool, default false\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  )
  .def_static(

    "apply",
    &Component::apply,
    python::arg( "pt" ), python::arg( "normalise" ),
    "Apply Compton profiles to a ProjectileTarget instance\n\n"
    "Parameters\n"
    "----------\n"
    "    pt : njoy.dryad.ProjectileTarget\n"
    "         projectile-target data to be modified\n"
    "    normalise : bool, default false\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );
}

} // external namespace
} // dryad namespace
