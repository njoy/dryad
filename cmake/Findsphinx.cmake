# find Sphinx executable

find_program( SPHINX_EXECUTABLE
    NAMES sphinx-build
)

include( FindPackageHandleStandardArgs )

find_package_handle_standard_args( sphinx
    "No sphinx executable found"
    SPHINX_EXECUTABLE
)