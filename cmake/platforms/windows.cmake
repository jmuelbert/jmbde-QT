#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: MIT

configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/app.rc.in
${PROJECT_BINARY_DIR}/app.rc @ONLY)

configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/installer_Qt6_x64.iss.in
${PROJECT_BINARY_DIR}/installer_Qt6_x64.iss @ONLY)

install(FILES ${PROJECT_BINARY_DIR}/installer_Qt6_x64.iss
DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})