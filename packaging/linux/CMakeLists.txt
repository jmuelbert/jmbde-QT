install(
  FILES com.jmuelbert.jmbde.desktop
  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications/
  COMPONENT jmbde_Flatpak
)
install(
  FILES com.jmuelbert.jmbde.metainfo.xml
  DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo
  COMPONENT jmbde_Flatpak
)
install(
  FILES com.jmuelbert.jmbde.svg
  DESTINATION $(CMAKE_INSTALL_DATADIR)/icons/hicolor/scalable/apps/
  COMPONENT jmbde_Flatpak
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(CPACK_GENERATOR "ZIP")
else()
  set(CPACK_GENERATOR "TZST")
endif()

set(CPACK_COMPONENTS_ALL jmbde_Runtime jmbde_Development)
set(CPACK_ARCHIV_COMPONENT_INSTALL yes)
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_NAME jmbde)
set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The jmbde (QT) application")
set(CPACK_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_FILE_NAME 
  jmbde-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_PACKAGE_VERSION_PATCH})
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE__CURRENT_LIST_DIR}/cpackGeneratorOverride.cmake)
set(CPACK_STRIP_FILES yes)
set(CPACK_THREADS 0)
set(CPACK_VERBATIM_VARIABLES yes)

set(CPACK_SOURCE_IGNORE_FILES /\\.git/ \\.swp \\.orig /CMakeLists\\.txt\\.user /build/)

include(CPack)

cpack_add_component(
  jmbde_Runtime
  DISPLAY_NAME Runtime
  DESCRIPTION "Shared libraries and executables"
  REQUIRED
  INSTALL_TYPES Full Developer Minimal)
)
cpack_add_component(
  jmbde_Development
  DISPLAY_NAME "Developer pre-requisites"
  DESCRIPTION "Headers/static libs needed for building"
  INSTALL_TYPES Full Developer
)

cpack_add_install_type(Full)
cpack_add_install_type(Minimal)
cpack_add_install_type(Developer)
