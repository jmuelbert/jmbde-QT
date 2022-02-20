#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: MIT
#
# Packaging instructios

set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert <juergen.muelbert@gmail.com>")
set(CPACK_PACKAGE_VERSION_MAJOR "${CMAKE_PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CMAKE_PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${CMAKE_PROJECT_VERSION_PATCH}")
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_STRIP_FILES "TRUE")

include(CPack)