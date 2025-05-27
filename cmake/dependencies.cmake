cmake_minimum_required( VERSION 3.27 )
include( FetchContent )

FetchContent_Declare( pugixml
    GIT_REPOSITORY  ../../zeux/pugixml.git
    GIT_TAG         ee86beb30e4973f5feffe3ce63bfa4fbadf72f38  # tag: v1.15
    )

FetchContent_Declare( eigen
    GIT_REPOSITORY  ../../njoy/eigen
    GIT_TAG         d0bfdc1658ca0b4c659fd3702c351d2c2cdc876c  # 3.4.1 branch on July 26, 2023
    )
# the next line prevents eigen from populating the .cmake/packages folder
set( CMAKE_EXPORT_NO_PACKAGE_REGISTRY ON )

FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         309169c0715c20424e4344131604c91a0f7415b6  # NOT A RELEASED VERSION - CHANGE ME!
    )

FetchContent_Declare( scion
    GIT_REPOSITORY  ../../njoy/scion
    GIT_TAG         545cc2de109e70afc0775a09d8c4c95b90586129  # NOT A RELEASED VERSION - CHANGE ME!
    )

FetchContent_Declare( ACEtk
    GIT_REPOSITORY  ../../njoy/ACEtk
    GIT_TAG         56fc1ba58ca54ab60e7aefc6f1d30902d282d8da  # NOT A RELEASED VERSION - CHANGE ME!
    )

FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  ../../njoy/ENDFtk
    GIT_TAG         ab62fd35295824f2d916042aaa5166082cf50745  # NOT A RELEASED VERSION - CHANGE ME!
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
