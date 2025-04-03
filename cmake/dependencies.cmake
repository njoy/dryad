cmake_minimum_required( VERSION 3.27 )
include( FetchContent )

FetchContent_Declare( pugixml
    GIT_REPOSITORY  https://github.com/zeux/pugixml.git
    GIT_TAG         db78afc2b7d8f043b4bc6b185635d949ea2ed2a8  # tag: v1.14
    )

FetchContent_Declare( eigen
    GIT_REPOSITORY  ../../njoy/eigen
    GIT_TAG         d0bfdc1658ca0b4c659fd3702c351d2c2cdc876c # 3.4.1 branch on July 26, 2023
    )
# the next line prevents eigen from populating the .cmake/packages folder
set( CMAKE_EXPORT_NO_PACKAGE_REGISTRY ON )

FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         204c0cf81eab97f51d3f8372c69fcdfd073ce60b  # tag: v0.4.2
    )

FetchContent_Declare( scion
    GIT_REPOSITORY  ../../njoy/scion
    GIT_TAG         1073840c04e94877dd52c10bc7cbf33314a09e00  # NOT A RELEASED VERSION - CHANGE ME!
    )

FetchContent_Declare( ACEtk
    GIT_REPOSITORY  ../../njoy/ACEtk
    GIT_TAG         5fdd3cf9c3082633c9edd229c4dc5d9d5577246f  # NOT A RELEASED VERSION - CHANGE ME!
    )

FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  ../../njoy/ENDFtk
    GIT_TAG         01745c4a715e0c9750674b5a9453eb4a25a4fd49  # NOT A RELEASED VERSION - CHANGE ME!
    )

#######################################################################
# Declare project dependencies
#######################################################################

if(dryad.python)
  FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         a2e59f0e7065404b44dfe92a28aca47ba1378dc4 # tag: v2.13.6
      )
  FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(dryad.tests)
  FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
      )
  FetchContent_MakeAvailable(
      Catch2
    )
endif()

FetchContent_MakeAvailable(
    pugixml
    eigen
    tools
    scion
    ACEtk
    ENDFtk
    )
