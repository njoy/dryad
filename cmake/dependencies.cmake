cmake_minimum_required( VERSION 3.27 )
include( FetchContent )

FetchContent_Declare( pugixml
    GIT_REPOSITORY  https://github.com/zeux/pugixml.git
    GIT_TAG         db78afc2b7d8f043b4bc6b185635d949ea2ed2a8  # tag: v1.14 
    )

FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         0133415ba4f1801a6ee86c7c04eb0cf303aeb731  # NOT A RELEASED VERSION - CHANGE ME!
    )

FetchContent_Declare( scion
    GIT_REPOSITORY  ../../njoy/scion
    GIT_TAG         e4358e66736191587288cede32f783d06bd68a16  # NOT A RELEASED VERSION - CHANGE ME!
    )

FetchContent_Declare( ACEtk
    GIT_REPOSITORY  ../../njoy/ACEtk
    GIT_TAG         cc588122d1aaedaae33dacf6f37fdfe6d59fad8b  # NOT A RELEASED VERSION - CHANGE ME!
    )

FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  ../../njoy/ENDFtk
    GIT_TAG         c9fd0ef4dc707689501479ff870f3c73b8f40f46  # NOT A RELEASED VERSION - CHANGE ME!
    )

#######################################################################
# Declare project dependencies
#######################################################################

if(dryad.python)
  FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         5b0a6fc2017fcc176545afe3e09c9f9885283242 # tag: v2.10.4
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
    tools
    scion
    ACEtk
    ENDFtk
    pugixml
    )
