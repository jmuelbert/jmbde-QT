# -*- coding: utf-8 -*-
#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#
#
import os

from conans import ConanFile, tools
from conan.tools.cmake import CMake
from conan.tools.layout import cmake_layout


class JmbdequickConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "qt/5.14.1@bincrafters/stable"
    name = "jmbdemodels"
    version = "0.1.1"
    license = "GPL-3.0-or-later"
    author = "juergen.muelbert@gmail.com"
    url = "https://github.com/jmuelbert/jmbdemodels"
    description = "The library for the jmbde quick ui"
    topics = ("jmbde", "quick", "qt5", "qt6")
    # VirtualBuildEnv and VirtualRunEnv can be avoided if "tools.env.virtualenv:auto_use" is defined
    # (it will be defined in Conan 2.0)
    generators = "CMakeDeps", "CMakeToolchain", "VirtualBuildEnv", "VirtualRunEnv"
    apply_env = False

    options = { "enable_testing": [True, False]}
    default_options = { "enable_testing": True}


    def build_requirements(self):
         if self.options.enable_testing:
             self.tool_requires("jmbdemodels/0.7", force_host_context=True)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def layout(self):
        cmake_layout(self)

    def test(self):
        if not tools.cross_building(self):
            cmd = os.path.join(self.cpp.build.bindirs[0], "example")
            self.run(cmd, env="conanrun")

