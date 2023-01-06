# -*- coding: utf-8 -*-
#
#  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#

import string
from conans import ConanFile, tools
from conans.tools import Version, check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
from conan.tools.files import copy
from conans.errors import ConanInvalidConfiguration
import os, re

required_conan_version = ">=1.44.0"

class jmbdeConan(ConanFile):
    name = "jmbde"
    homepage = "https://github.com/jmuelbert/jmbde-QT"
    author = "Jürgen Mülbert"
    description = "A BDE Tool"
    topics = (
        "bde", 
        "collect-data", 
        "database", 
        "qt", 
        "qt6", 
        "conan", 
        "cmake", 
        "c++"
        )
    license = "GPL V3+"
    url = "https://github.com/jmuelbert/jmbde-QT"
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "build_docs": [True, False],
        "build_translations": [True, False]
    }

    default_options = {
        "shared": False,
        "build_docs": True,
        "build_translations": True
    }

    exports = ["License.md"]
    exports_sources = ["docs/*", "src/*", "test/*", "cmake/*", "example/*", "CMakeLists.txt"]

    generators = (
        "cmake_find_package_multi",
        "markdown",
        "txt"
    )

    @property
    def _run_tests(self):
        return tools.get_env("CONAN_RUN_TESTS", False)

    @property
    def _use_libfmt(self):
        compiler = self.settings.compiler
        version = Version(self.settings.compiler.version)
        std_support = \
            (compiler == "Visual Studio" and version >= 17 and compiler.cppstd == 23) or \
            (compiler == "msvc" and version >= 193 and compiler.cppstd == 23)
        return not std_support


    @property
    def _use_range_v3(self):
        compiler = self.settings.compiler
        version = Version(self.settings.compiler.version)
        return "clang" in compiler and compiler.libcxx == "libc++" and version < 14

    @property
    def _msvc_version(self):
        compiler = self.settings.compiler
        if compiler.update:
            return int(f"{compiler.version}{compiler.update}")
        else:
            return int(f"{compiler.version}0")

    def set_version(self):
        content = tools.load(os.path.join(self.recipe_folder, "CMakeLists.txt"))
        version = re.search(r"project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)", content).group(1)
        print("version = {}", version)

    
 
    """_summary_
    """
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

        self.options["qt"].shared = True
        self.options["qt"].qttranslations = True

    """_summary_
    """
    def requirements(self):
        self.requires("spdlog/1.11.0")
        self.requires("extra-cmake-modules/5.93.0")

        if self._use_libfmt:
            self.requires("fmt/9.1.0")
        if self._use_range_v3:
            self.requires("range-v3/0.11.0")
   
        self.requires("extra-cmake-modules/5.93.0")
        self.requires("spdlog/1.10.0")
        
        qtDir = os.environ.get("Qt6_Dir")
        if qtDir == 0:
            self.requires("qt/6.4.1")
            self.options["qt"].shared = self.options.shared
            self.options["qt"].qtsvg = True
            self.options["qt"].qtdeclarative = True
            self.options["qt"].qttools = True
            if self.options.build_translations:
                self.options["qt"].qttranslations = True
            self.options["qt"].qtimageformats = True
            self.options["qt"].qtdoc = True
            self.options["qt"].qtimageformats = True
            self.options["qt"].shared = self.options.shared
            self.options["qt"].qtimageformats = True

            
    """_summary_
    """
    def build_requirements(self):
        if self._build_tests:
            self.test_requires("gtest/1.12.1")
            self.test_requires("doctest/2.4.9")
            self.test_requires("catch2/3.1.0")
            # self.tool_requires("doxygen/1.9.4")
            

    # TODO Replace with `valdate()` for Conan 2.0 (https://github.com/conan-io/conan/issues/10723)
    def configure(self) :
        compiler = self.settings.compiler
        version = Version(self.settings.compiler.version)
        if compiler == "gcc":
            if version < 10:
                raise ConanInvalidConfiguration("jmbde-QT requires at least g++-10")
        elif compiler == "clang":
            if version < 12:
                raise ConanInvalidConfiguration("jmbde-QT requires at least clang++-12")
        elif compiler == "apple-clang":
            if version < 13:
                raise ConanInvalidConfiguration("jmbde-QT requires at least AppleClang 13")
        elif compiler == "Visual Studio":
            if version < 16:
                raise ConanInvalidConfiguration("jmbde-QT requires at least Visual Studio 16.9")
        elif compiler == "msvc":
            if self._msvc_version < 1928:
                raise ConanInvalidConfiguration("jmbde-QT requires at least MSVC 19.28")
        else:
            raise ConanInvalidConfiguration("Unsupported compiler")
        check_min_cppstd(self, 20)


    # TODO Uncomment this when environment is supported in the Conan toolchain
    # def config_options(self):
    #     if not self._run_tests:
    #         # build_docs has sense only in a development or CI build
    #         del self.options.build_docs


    def generate(self):
        tc = CMakeToolchain(self)
        # if self._run_tests:  # TODO Enable this when environment is supported in the Conan toolchain
        tc.variables["BUILD_DOCS"] = bool(self.options.build_docs)
        tc.variables["BUILD_TRANSATIONS"] = bool(self.options.build_translations)
        tc.variables["USE_LIBFMT"] = self._use_libfmt
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=None if self._run_tests else "src")
        cmake.build()
        if self._run_tests:
            cmake.test()

    def package_id(self):
        self.info.header_only()

    def package(self):
        copy(self, "LICENSE.md", self.source_folder, os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))

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

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="lib", src="lib")
        self.copy("*", dst="libexec", src="libexec")
        self.copy("*", dst="bin/archdatadir/plugins", src="bin/archdatadir/plugins")
        self.copy("*", dst="bin/archdatadir/qml", src="bin/archdatadir/qml")
        self.copy("*", dst="bin/archdatadir/libexec", src="bin/archdatadir/libexec")
        self.copy("*", dst="bin/datadir/translations", src="bin/datadir/translations")
        self.copy("*", dst="resources", src="resources")
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)
