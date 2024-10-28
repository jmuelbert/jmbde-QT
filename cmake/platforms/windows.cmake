#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: MIT

include(GNUInstallDirs)
include(Deployment)

set_target_properties(${TARGET_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
set_target_properties(
    ${TARGET_NAME}
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
               LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
               RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION .)

if(NOT EMBED_TRANSLATIONS)
    install(FILES ${APP_QM_FILES} DESTINATION lang)
endif()

install(DIRECTORY ${CMAKE_BINARY_DIR}/winqt/ DESTINATION .)

set(APPS "\${CMAKE_INSTALL_PREFIX}/${TARGET_NAME}.app"

include(Deployment)

find_package(
  QT NAMES Qt6 Qt5
  COMPONENTS Core
  REQUIRED)

if(ENABLE_APP_AUTO_DEPLOY)
    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        set(APP_QtX_DIR ${Qt6_DIR})
    else()
        set(APP_QtX_DIR ${Qt5_DIR})
    endif()
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${APP_QtX_DIR}/../../../bin/windeployqt ${CMAKE_BINARY_DIR}/${TARGET_NAME}.exe --compiler-runtime --verbose 2 --dir ${CMAKE_BINARY_DIR}/winqt/)
endif()

configure_file(${CMAKE_SOURCE_DIR}/assets/app.rc.in
${PROJECT_BINARY_DIR}/app.rc @ONLY)

configure_file(${CMAKE_SOURCE_DIR}/assets/installer_Qt6_x64.iss.in
${PROJECT_BINARY_DIR}/installer_Qt6_x64.iss @ONLY)
s
install(FILES ${PROJECT_BINARY_DIR}/installer_Qt6_x64.iss
DESTINATION ${CMAKE_INSTALL_BINDIR})
