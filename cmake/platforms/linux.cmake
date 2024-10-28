#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: MIT

# This will define the default values for installation directories (all
# platforms even if named GNU)
include(GNUInstallDirs)
include(Deployment)

set_target_properties(
  ${TARGET_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(APP_LINUX_ICON_DIMENSIONS 16 32 128 256 512)

install(TARGETS ${TARGET_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})

# Configure the appdata file and install this
configure_file(${CMAKE_SOURCE_DIR}/assets/jmbde.appdata.xml.in
               ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/appdata)

# Install the desktop-file in XDG_APPS_INSTALL_DIR
install(
  FILES ${CMAKE_SOURCE_DIR}/assets/io.github.jmuelbert.jmbde.desktop.in
  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
  RENAME io.github.jmuelbert.jmbde.desktop)

foreach(APP_LINUX_ICON_DIMENSION ${APP_LINUX_ICON_DIMENSIONS})
  install(
    FILES ${CMAKE_SOURCE_DIR}/assets/icons/jmbde-${APP_LINUX_ICON_DIMENSION}.png
    DESTINATION
      "${CMAKE_INSTALL_DATADIR}/icons/hicolor/${APP_LINUX_ICON_DIMENSION}x${APP_LINUX_ICON_DIMENSION}/apps"
    RENAME ${TARGET_NAME}.png)
endforeach(APP_LINUX_ICON_DIMENSION)

if(NOT EMBED_TRANSLATIONS)
  install(FILES ${QM_FILES}
          DESTINATION "${CMAKE_INSTALL_DATADIR}/${TARGET_NAME}/lang")
endif()

if(NOT EMBED_DOCS)
  # install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manual.pdf DESTINATION
  # "${CMAKE_INSTALL_DATADIR}/doc/${TARGET_NAME}")
endif()

# man page
find_program(GZIP gzip)
if(GZIP)
  configure_file(${CMAKE_SOURCE_DIR}/assets/${TARGET_NAME}.1.in
                 ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.1 @ONLY)

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.1.gz
    COMMAND ${GZIP} -c ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.1 >
            ${TARGET_NAME}.1.gz
    COMMENT "Create the bin gz archive"
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.1)

  add_custom_target(
    man ALL
    COMMENT "Create man-file"
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.1.gz)

  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.1.gz
          DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/)
endif()
