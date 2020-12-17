# ==================================================================================
# Translations
# ==================================================================================

if(${Qt6_FOUND})
  message("Qt6 gefunden!")
  message(STATUS "Qt version is ${Qt6Core_VERSION}")
  set(QT_DEFAULT_MAJOR_VERSION "ON")
  find_package(
    Qt6
    COMPONENTS LinguistTools
    REQUIRED)
else()
  message("Qt5 gefunden!")
  message(STATUS "Qt version is ${Qt5Core_VERSION}")
  find_package(
    Qt5
    COMPONENTS LinguistTools
    REQUIRED)
endif()

set(TRANSLATIONS_DIR ${CMAKE_SOURCE_DIR}/translations)
file(GLOB TRANSLATIONS_TS ${TRANSLATIONS_DIR}/**.ts)

if(${Qt6_FOUND})
  qt_add_translation(QM_FILES ${TRANSLATIONS_TS})
else()
  qt5_add_translation(QM_FILES ${TRANSLATIONS_TS})
endif()
