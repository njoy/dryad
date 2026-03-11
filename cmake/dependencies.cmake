cmake_minimum_required( VERSION 3.27 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( shacl_FetchContent )

shacl_FetchContent_Declare( pugixml
    GIT_REPOSITORY  ../../zeux/pugixml.git
    GIT_TAG         ee86beb30e4973f5feffe3ce63bfa4fbadf72f38  # tag: v1.15
    )

shacl_FetchContent_Declare( eigen
    GIT_REPOSITORY  ../../njoy/eigen
    GIT_TAG         bc3b39870ecb690a623a3f49149a358b95c5781d  # tag: 5.0.1
    )
# the next line prevents eigen from populating the .cmake/packages folder
set( CMAKE_EXPORT_NO_PACKAGE_REGISTRY ON )

shacl_FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         8d648f1d89116fc804eda661e5f854226524361e  # NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( scion
    GIT_REPOSITORY  ../../njoy/scion
    GIT_TAG         559b2a70f121a42d4819d12d8e9ec00a0d68aa30  # NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( ACEtk
    GIT_REPOSITORY  ../../njoy/ACEtk
    GIT_TAG         ff86bd5570d02f607fd8ff25c827a414a44fe304  # NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  ../../njoy/ENDFtk
    GIT_TAG         2d309b17eb69d1ab9db048b95e2294c471199253  # NOT A RELEASED VERSION - CHANGE ME!
    )

#######################################################################
# Declare project dependencies
#######################################################################

if(njoy.python)
  shacl_FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         a2e59f0e7065404b44dfe92a28aca47ba1378dc4 # tag: v2.13.6
      )
  shacl_FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(njoy.tests)
  shacl_FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
      )
  shacl_FetchContent_MakeAvailable(
    Catch2
    )
endif()

shacl_FetchContent_MakeAvailable(
    pugixml
    eigen
    tools
    scion
    ACEtk
    ENDFtk
    )
