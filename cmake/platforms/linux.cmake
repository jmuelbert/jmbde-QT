#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: MIT

install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})

include(GNUInstallDirs)

set(APP_LINUX_ICON_DIMENSIONS 16 32 128 256 512)

# Configure the appdata file and install this
configure_file(${CMAKE_SOURCE_DIR}/assets/jmbde.appdata.xml.in
                 ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml @ONLY)


install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/appdata)


# Install the desktop-file in XDG_APPS_INSTALL_DIR
install(
   FILES assets/io.github.jmuelbert.jmbde.desktop.in
   DESTINATION ${CMAKE_INSTALL_DATADIR}/applications RENAME io.github.jmuelbert.jmbde.desktop)

foreach(APP_LINUX_ICON_DIMENSION ${APP_LINUX_ICON_DIMENSIONS})
	install(FILES assets/icons/jmbde-${APP_LINUX_ICON_DIMENSION}.png DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/${APP_LINUX_ICON_DIMENSION}x${APP_LINUX_ICON_DIMENSION}/apps" RENAME jmbde.png)
endforeach(APP_LINUX_ICON_DIMENSION)

if(NOT EMBED_TRANSLATIONS)
    install(FILES ${QM_FILES} DESTINATION "${CMAKE_INSTALL_DATADIR}/jmbde/lang")
endif()

if(NOT EMBED_DOCS)
    install(FILES manual/manual.pdf DESTINATION "${CMAKE_INSTALL_DATADIR}/doc/jmbde")
endif()

# man page
find_program(GZIP gzip)
if(GZIP)
  configure_file(${CMAKE_SOURCE_DIR}/assets/jmbde.1.in
                   ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1 @ONLY)

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz
        COMMAND ${GZIP} -c ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1 > jmbde.1.gz
        COMMENT "Create the bin gz archive"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1)

    add_custom_target(
        man ALL
        COMMENT "Create man-file"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz
        DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/)
endif()