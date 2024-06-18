cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( tools
    GIT_REPOSITORY  https://github.com/njoy/tools
    GIT_TAG         v0.3.0
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( ACEtk
    GIT_REPOSITORY  https://github.com/njoy/ACEtk.git
    GIT_TAG         v1.0.0
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  https://github.com/njoy/ENDFtk.git
    GIT_TAG         v1.1.0
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2
    GIT_TAG         v3.3.2
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         v2.10.4
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( scion
    GIT_REPOSITORY  https://github.com/njoy/scion
    GIT_TAG         develop
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( eigen
    GIT_REPOSITORY  https://gitlab.com/libeigen/eigen.git
    GIT_TAG         d0bfdc1658ca0b4c659fd3702c351d2c2cdc876c # 3.4.1 branch on July 26, 2023
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    ACEtk
    ENDFtk
    scion
    tools
    eigen
    )
