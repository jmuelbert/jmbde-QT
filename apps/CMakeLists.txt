# shared libraries used by jmbde-widget and jmbde-quick applications
add_subdirectory(libs)

# the jmbde-widgets application
ecm_optional_add_subdirectory(jmbde-widgets)

# the jmbde-quick application
ecm_optional_add_subdirectory(jmbde-quick)
