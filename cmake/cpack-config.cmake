#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: MIT
#
# Packaging instructios

include(version)

set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert <juergen.muelbert@gmail.com>")
set( CPACK_PACKAGE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK} )
set( CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR} )
set( CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR} )
set( CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH} )
# set( CPACK_RESOURCE_FILE_LICENSE cmake/modules/license.rtf )

include( CPackComponent )

cpack_add_component( applications      DISPLAY_NAME "Applications" GROUP Runtime )
cpack_add_component( translations      DIAPLAY_NAME "Translation files" GROUP Runtime )
cpack_add_component( runtime_libraries DISPLAY_NAME "Runtime libraries" DESCRIPTION "libraries" GROUP Runtime )
cpack_add_component( plugins           DISPLAY_NAME "Plugins"   GROUP Runtime )
cpack_add_component( modules           DISPLAY_NAME "Modules"   GROUP Runtime )
cpack_add_component( py_modules        DISPLAY_NAME "PyModules" GROUP Runtime )

cpack_add_component( libraries         DISPLAY_NAME "Development libraries"
  DESCRIPTION "Static and import libraries" GROUP Development )

cpack_add_component( headers           DISPLAY_NAME "C++ Headers"
  DESCRIPTION "C++ header files for use with jmbde Toolkit" GROUP Development )

cpack_add_component_group( Runtime )
cpack_add_component_group( PyModules )
cpack_add_component_group( Development )


set( CPACK_ALL_INSTALL_TYPES Full Developer)
set( CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full )
set( CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full )
set( CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full )

set( CPACK_PACKAGE_EXECUTABLES jmbde "jmbde" )
set( CPACK_CREATE_DESKTOP_LINKS Qtjmbde )


include(CPack)