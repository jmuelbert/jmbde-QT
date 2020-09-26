
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/install.iss.in)
                ${PROJECT_BINARY_DIR}/installer.iss @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/install.nsis.in)
                ${PROJECT_BINARY_DIR}/installer.iss @ONLY)
