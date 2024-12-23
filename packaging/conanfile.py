# -*- coding: utf-8 -*-
#
#  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#

from conans import CMake, ConanFile


class jmbdeConan(ConanFile):
    name = "jmbde"
    version = "0.6.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package"
    build_policy = "missing"
    url = "https://github.com/jmuelbert/jmbde-QT"
    license = "GPL V3+"
    author = "Jürgen Mülbert"
    description = "A BDE Tool"
    topics = ("bde", "collect-data", "database", "qt", "qt6", "conan", "cmake", "c++")
    generators = "cmake"

    options = {"testing": [True, False]}
    default_options = {"testing": False}
    build_policy = "missing"

    def build_requirements(self):
        self.build_requires("extra-cmake-modules/5.84.0")
        self.build_requires("catch2/2.13.8")
        self.build_requires("fmt/6.2.1")
        self.build_requires("spdlog/1.5.0")
        self.build_requires("qt/6.2.1")

    def requirements(self):
        if self.options.testing:
            self.requires("gtest/cci.20210126")
            self.requires("benchmark/1.6.0")

    def export_sources(self):
        self.copy("*")

    def _configure_cmake(self):
        cmake = CMake(self)
        # cmake.definitions["SOME_DEFINITION"] = "VALUE"
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        # self.cpp_info.includedirs = ['include']  # Ordered list of include paths
        # self.cpp_info.libs = ['dena_library']  # The libs to link against
        # self.cpp_info.system_libs = []  # System libs to link against
        # self.cpp_info.libdirs = ['lib']  # Directories where libraries can be found
        # self.cpp_info.resdirs = ['res']  # Directories where resources, data, etc. can be found
        # Directories where executables and shared libs can be found
        self.cpp_info.bindirs = ["bin"]
        # self.cpp_info.srcdirs = []  # Directories where sources can be found (debugging, reusing sources)
        # self.cpp_info.build_modules = {}  # Build system utility module files
        # self.cpp_info.defines = []  # preprocessor definitions
        # self.cpp_info.cflags = []  # pure C flags
        # self.cpp_info.cxxflags = []  # C++ compilation flags
        # self.cpp_info.sharedlinkflags = []  # linker flags
        # self.cpp_info.exelinkflags = []  # linker flags
        # self.cpp_info.components  # Dictionary with the different components a package may have
        # self.cpp_info.requires = None  # List of components from requirements
