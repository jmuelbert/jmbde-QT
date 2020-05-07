# -*- coding: utf-8 -*-
from conans import ConanFile, CMake


class JmbdemodelsConan(ConanFile):
    name = "jmbdemodels"
    version = "0.2"
    license = "GPL-3.0-or-later"
    author = "juergen.muelbert@gmail.com"
    url = "https://github.com/jmuelbert/jmbdemodels"
    description = "The library for the jmbde data models"
    topics = ("jmbde", "models", "qt5")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    exports_sources = "src/*"
    requires="qt/5.14.2@bincrafters/stable"

    def source(self):
        self.run('git clone https://github.com/jmuelbert/jmbdemodels.git')
        # This small hack might be useful to guarantee proper /MT /MD linkage
        # in MSVC if the packaged project doesn't have variables to set it
        # properly
        # tools.replace_in_file("hello/CMakeLists.txt", "PROJECT(MyHello)",
        #                      '''PROJECT(MyHello)
        #                        include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
        #                        conan_basic_setup()''')

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["jmbdemodels"]
