find_package( sphinx REQUIRED )
set( SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/source )
set( SPHINX_BUILD ${CMAKE_CURRENT_SOURCE_DIR}/build )

add_custom_target( sphinx ALL 
    COMMAND 
    ${SPHINX_EXECUTABLE} -b html
    ${SPHINX_SOURCE} ${SPHINX_BUILD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "generating sphinx documentation in HTML"
)

