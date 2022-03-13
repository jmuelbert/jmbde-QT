macro(run_conan)

  option(${PROJECT_NAME}_ENABLE_CONAN_BUILD_ALL "Enable rebuild of all conan requires from source" OFF)

  set(${PROJECT_NAME}_CONAN_REQUIRES "")
  set(${PROJECT_NAME}_CONAN_OPTIONS "")

  # Download automatically, you can also just copy the conan.cmake file
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(
      DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/release/0.17/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake"
      EXPECTED_HASH SHA256=3bef79da16c2e031dc429e1dac87a08b9226418b300ce004cc125a82687baeef
      TLS_VERIFY ON)
    message(STATUS "Cmake-Conan downloaded succesfully.")
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)

  conan_cmake_configure(
    REQUIRES
    ${${PROJECT_NAME}_CONAN_REQUIRES}
    OPTIONS
    ${${PROJECT_NAME}_CONAN_OPTIONS}
    BASIC_SETUP
    CMAKE_TARGETS # Individual targets to link to
    BUILD
    missing)

  if(ENABLE_CONAN_BUILD_ALL)
    set(CONAN_BUILD all)
  else()
    set(CONAN_BUILD missing)
  endif()

  if(CMAKE_CONFIGURATION_TYPES)
    foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
      conan_cmake_autodetect(settings BUILD_TYPE ${TYPE})

      conan_cmake_install(
        PATH_OR_REFERENCE
        .
        BUILD
        ${CONAN_BUILD}
        SETTINGS
        ${settings})
    endforeach()
  else()
    conan_cmake_autodetect(settings)

    conan_cmake_install(
      PATH_OR_REFERENCE
      .
      BUILD
      ${CONAN_BUILD}
      SETTINGS
      ${settings})
  endif()

  list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
  verbose_message("Conan is setup and all requires have been installed.")
endmacro()
