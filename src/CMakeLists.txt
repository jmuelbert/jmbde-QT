
# building the libs
add_subdirectory(libs)

# building the app
add_subdirectory(app)

if(BUILD_TRANSLATIONS)
  add_subdirectory(translations)
endif()
