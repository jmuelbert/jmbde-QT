
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/installer_x64.iss.in
                ${PROJECT_BINARY_DIR}/installer_x64.iss @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/installer_x86.iss.in
                ${PROJECT_BINARY_DIR}/installer_x86.iss @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/installer_x86.nsis.in
                ${PROJECT_BINARY_DIR}/installer_x86.nsis @ONLY)
