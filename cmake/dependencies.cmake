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

shacl_FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         09733ce8feda44821eeaba3fd0bb24b4a9e6cfcd  # develop - NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( scion
    GIT_REPOSITORY  ../../njoy/scion
    GIT_TAG         6cdd1a5f4db38ead180849f3808dde161a30d07e  # develop - NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( ACEtk
    GIT_REPOSITORY  ../../njoy/ACEtk
    GIT_TAG         2ffe9dc4d0f564777e83b60a2e5fbd81e8bb0720  # develop - NOT A RELEASED VERSION - CHANGE ME!
    )

shacl_FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  ../../njoy/ENDFtk
    GIT_TAG         08c8adb4fcf10f495e46a520e5e2ee405943f41f  # develop - NOT A RELEASED VERSION - CHANGE ME!
    )

#######################################################################
# Declare project dependencies
#######################################################################

if(njoy.python)
  shacl_FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         a2e59f0e7065404b44dfe92a28aca47ba1378dc4  # tag: v2.13.6
      )
  shacl_FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(njoy.tests)
  shacl_FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         b670de4fe12ac7c5e858b7de3a14fb4bd18c760e  # tag: v3.14.0
      )
  set( BUILD_SHARED_LIBS ON )
  shacl_FetchContent_MakeAvailable(
    Catch2
    )
  set( BUILD_SHARED_LIBS OFF )
endif()

shacl_FetchContent_MakeAvailable(
    pugixml
    eigen
    tools
    scion
    ACEtk
    ENDFtk
    )
