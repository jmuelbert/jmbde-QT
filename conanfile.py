# -*- coding: utf-8 -*-
#
#  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#

from conans import ConanFile, tools
from conans.tools import Version, check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
from conan.tools.files import copy
from conans.errors import ConanInvalidConfiguration
import os, re
from pydoc_data.topics import topics

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
        # content = tools.load(os.path.join(self.recipe_folder, "src/CMakeLists.txt"))
        # version = re.search(r"project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)", content).group(1)
        # self.version = version.strip()
        self.version = "0.7.0"

    def requirements(self):
        platform_qt = os.getenv("CMAKE_PREFIX_PATH")
        if not platform_qt:
            self.output.info("CMAKE_PREFIX_PATH not set")
            self.output.info(
                "To use the Qt from your system, set the CMAKE_PREFIX_PATH env var"
            )
            # self.output.info("Trying to get Qt from Qt")
            # self.requires("qtbase/6.2.3@qt/everywhere")
            # self.requires("qtbuildprofiles/6.2.3@qt/everywhere")
            # self.requires("qtdeclarative/6.2.3@qt/everywhere")
            # self.requires("qtdoc/6.2.3@qt/everywhere")
            # self.requires("qtimageformats/6.2.3@qt/everywhere")
            # self.requires("qtsvg/6.2.3@qt/everywhere")
            # if self.options.build_translations:
            #    self.requires("qttranslations/6.2.3@qt/everywhere")



            self.requires("qt/6.2.4")
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

        else:
            self.output.info(
                "Getting Qt from the system. CMAKE_PREFIX_PATH = " + platform_qt
            )
        if self._use_libfmt:
            self.requires("fmt/8.1.1")
        if self._use_range_v3:
            self.requires("range-v3/0.11.0")

        # self.requires("extra-cmake-modules/5.93.0")
        self.requires("spdlog/1.10.0")
        self.requires("cli11/2.2.0")
        self.requires("fltk/1.3.8")

    def build_requirements(self):
        if self._run_tests:
            self.requires("catch2/2.13.9")
            self.requires("gtest/cci.20210126")
            self.requires("benchmark/1.6.1")
            if self.build_docs:
              self.tool_requieres("doxygen/1.9.2")

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
