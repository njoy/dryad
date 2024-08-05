cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( ACEtk
    GIT_REPOSITORY  https://github.com/njoy/ACEtk.git
    GIT_TAG         29684a986a9c3df1281cbadb73a83775acf9fb69 # tag: v1.0.0
    )

FetchContent_Declare( Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2
    GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
    )

FetchContent_Declare( eigen
    GIT_REPOSITORY  https://gitlab.com/libeigen/eigen.git
    GIT_TAG         d0bfdc1658ca0b4c659fd3702c351d2c2cdc876c # 3.4.1 branch on July 26, 2023
    )

FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  https://github.com/njoy/ENDFtk.git
    GIT_TAG         2a0aeda4642880148ce060f620e50378654d07c9
    )

FetchContent_Declare( fast_float
    GIT_REPOSITORY  https://github.com/fastfloat/fast_float
    GIT_TAG         f476bc713fda06fbd34dc621b466745a574b3d4c # tag: v6.1.1
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         5b0a6fc2017fcc176545afe3e09c9f9885283242 # tag: v2.10.4
    )

FetchContent_Declare( range-v3
    GIT_REPOSITORY  https://github.com/ericniebler/range-v3
    GIT_TAG         4989f3e9ff2efee1852942bb9328ef121369ba02 # tag: 0.11.0
    )

FetchContent_Declare( scion
    GIT_REPOSITORY  https://github.com/njoy/scion
    GIT_TAG         6079dc15153b1948c772835096662be65b062676
    )

FetchContent_Declare( spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog
    GIT_TAG         ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36 # tag: v1.11.0
    )

FetchContent_Declare( tools
    GIT_REPOSITORY  https://github.com/njoy/tools
    GIT_TAG         368dbd9bd44754de616c46ffed0f80d2d16d8360 # tag: v0.3.0
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    ACEtk
    eigen
    ENDFtk
    fast_float
    range-v3
    scion
    spdlog
    tools
    )
