# -*- coding: utf-8 -*-
#
#  SPDX-FileCopyrightText: 2013-2024 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#

import os

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain
from conan.tools.files import copy, rm, rmdir
from conan.tools.scm import Version

required_conan_version = ">=2.0"


class jmbdeReceipe(ConanFile):
    name = "jmbde"
    description = "A BDE Tool"
    license = "EUPL-1.2"
    url = "https://github.com/jmuelbert/jmbde-QT"
    homepage = "https://github.com/jmuelbert/jmbde-QT"
    author = "Jürgen Mülbert"
    topics = ("bde", "collect-data", "database", "qt", "qt6", "conan", "cmake", "c++")
    package_type = "application"
    settings = "os", "arch", "compiler", "build_type"
    version = "0.7.0"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "build_docs": [True, False],
        "build_translations": [True, False],
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "build_docs": True,
        "build_translations": True,
    }

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            self.options["qt"].shared = True
            self.options.rm_safe("qt:fPIC")
            self.options.rm_safe("fPIC")

    def layout(self):
        # We make the assumption that if the compiler is msvc the
        # CMake generator is multi-config
        multi = True if self.settings.get_safe("compiler") == "msvc" else False
        if multi:
            self.folders.generators = os.path.join("build", "generators")
            self.folders.build = "build"
        else:
            self.folders.generators = os.path.join(
                "build", str(self.settings.build_type), "generators"
            )
            self.folders.build = os.path.join("build", str(self.settings.build_type))

    def requirements(self):
        qt_dir = os.getenv("QT_ROOT_DIR")
        platform_qt = os.getenv("CMAKE_PREFIX_PATH")

        if not platform_qt or not qt_dir:
            self.output.info("CMAKE_PREFIX_PATH not set")
            self.output.info(
                "To use the Qt from your system, set the CMAKE_PREFIX_PATH env var"
            )

            # Verwenden Sie die Standard-Qt-Version, wenn die Umgebungsvariablen nicht gesetzt sind
            self.requires("qt/6.7.2")
            self.options["qt"].shared = self.options.shared
            self.options["qt"].qtsvg = True
            self.options["qt"].qtdeclarative = True
            self.options["qt"].qttools = True
            self.options["qt"].qtimageformats = True
            self.options["qt"].qtdoc = True

            if self.options.build_translations:
                self.options["qt"].qttranslations = True
        else:
            self.output.info(
                "Getting the Qt installation directory from the system: QT_ROOT_DIR = "
                + qt_dir
            )
            self.output.info(
                "Getting Qt from the system. CMAKE_PREFIX_PATH = " + platform_qt
            )

        self.requires("extra-cmake-modules/5.113.0")

    @property
    def _min_cppstd(self):
        return 14

    # In case the project requires C++14/17/20/... the minimum compiler version should be listed
    @property
    def _compilers_minimum_version(self):
        return {"msvc": "192", "gcc": "11", "clang": "13", "apple-clang": "14"}

    def _validate_cppstd(self):
        if self.settings.compiler.get_safe("cppstd"):
            # Validate the minimum cpp standard supported when installing the package. For C++ projects only
            check_min_cppstd(self, self._min_cppstd)
        minimum_version = self._compilers_minimum_version.get(
            str(self.settings.compiler), False
        )
        if (
            minimum_version
            and Version(self.settings.compiler.version) < minimum_version
        ):
            raise ConanInvalidConfiguration(
                f"{self.ref} requires C++{self._min_cppstd}, which your compiler does not support."
            )

    @property
    def _required_options(self):
        options = []
        # Usage: options.append(("boost", [("without_graph", False), ("without_test", False)]))
        return options

    def _strict_options_requirements(self):
        for requirement, options in self._required_options:
            for option_name, value in options:
                setattr(self.options[requirement], f"{option_name}", value)

    def _validate_options_requirements(self):
        for requirement, options in self._required_options:
            is_missing_option = not all(
                self.dependencies[requirement].options.get_safe(f"{option_name}")
                == value
                for option_name, value in options
            )
            if is_missing_option:
                raise ConanInvalidConfiguration(
                    f"{self.ref} requires {
                        requirement} with these options: {options}"
                )

    def validate(self):
        self._validate_cppstd()
        self._validate_options_requirements()

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.25 <4.0.0]")

    def generate(self):
        CMakeDeps(self).generate()
        toolchain = CMakeToolchain(self)
        toolchain.presets_prefix = ""
        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake.test()

    def package(self):
        copy(
            self,
            pattern="LICENSE",
            dst=os.path.join(self.package_folder, "licenses"),
            src=self.source_folder,
        )
        cmake = CMake(self)
        cmake.install()

        # some files extensions and folders are not allowed. Please, read the FAQs to get informed.
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        rm(self, "*.la", os.path.join(self.package_folder, "lib"))
        rm(self, "*.pdb", os.path.join(self.package_folder, "lib"))
        rm(self, "*.pdb", os.path.join(self.package_folder, "bin"))

    def package_info(self):
        self.cpp_info.libs = ["starter"]

        self.cpp_info.set_property("cmake_file_name", "starter")
        self.cpp_info.set_property("cmake_target_name", "starter::starter")
