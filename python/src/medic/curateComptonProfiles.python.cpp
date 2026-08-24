// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/medic/curateComptonProfiles.hpp"

// namespace aliases
namespace python = pybind11;

namespace medic {

  void wrapCurateComptonProfiles( python::module& module ) {

    // type aliases

    // wrap the function
    module
    .def(

      "curate_compton_profiles",
      &njoy::medic::curateComptonProfiles,
      python::arg( "photoatomic" ),
      python::arg( "relaxation" ),
      "Curate the Compton profile data\n\n"
      "This function ensures that the Compton profile data in the incoherent\n"
      "scattering function and the atomic relaxation data are consistent. The\n"
      "following operations are performed on the Compton profile data:\n"
      "  - when the Compton profile data contains a subshell that is not present\n"
      "    in the atomic relaxation data, that profile is removed\n"
      "  - when the atomic relaxation data contains subshells that are not present\n"
      "    in the Compton profiles, then the Compton profile for the missing subshell\n"
      "    is set to the one with the same principal and azimuthal quantum number\n"
      "    that is already present\n\n"
       "Parameters\n"
      "----------\n"
      "    photoatomic : njoy.dryad.ProjectileTarget\n"
      "        the photoatomic projectile-target data to be curated\n"
      "    relaxation : njoy.dryad.AtomicRelaxation\n"
      "        the atomic relaxation data"
    );
  }

} // medic namespace
