#
# SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# This is the build for the models
add_subdirectory(models)

#
# This is only for the Widgetversion
add_subdirectory(widgets)

#
# This is only for the QML/Quickversion
add_subdirectory(quick)
