cmake_minimum_required( VERSION 3.27 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( shacl_FetchContent )

shacl_FetchContent_Declare( pugixml
    GIT_REPOSITORY  ../../zeux/pugixml.git
    GIT_TAG         ee86beb30e4973f5feffe3ce63bfa4fbadf72f38  # tag: v1.15
    )

shacl_FetchContent_Declare( eigen
    GIT_REPOSITORY  ../../njoy/eigen
    GIT_TAG         d0bfdc1658ca0b4c659fd3702c351d2c2cdc876c  # 3.4.1 branch on July 26, 2023
    )
# the next line prevents eigen from populating the .cmake/packages folder
set( CMAKE_EXPORT_NO_PACKAGE_REGISTRY ON )

shacl_FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         08cac7cc68fcf83cc4b5230712fc3a4d9d990ac6  # NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( scion
    GIT_REPOSITORY  ../../njoy/scion
    GIT_TAG         14e10db7d2dbd49d79f5b3cf6abebff144855233  # NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( ACEtk
    GIT_REPOSITORY  ../../njoy/ACEtk
    GIT_TAG         166ee0e79af8287779dbdee824cc3ebbc27d4d84  # NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  ../../njoy/ENDFtk
    GIT_TAG         97838a724b1b32bdc6c0da7e219668e072750700  # NOT A RELEASED VERSION - CHANGE ME!
    )

#######################################################################
# Declare project dependencies
#######################################################################

if(dryad.python)
  shacl_FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         a2e59f0e7065404b44dfe92a28aca47ba1378dc4 # tag: v2.13.6
      )
  shacl_FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(dryad.tests)
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
