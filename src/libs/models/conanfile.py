from conans import ConanFile, tools
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
from conan.tools.layout import cmake_layout



class JmbdeModelsConan(ConanFile):
    name = "jmbdemodels"
    version = "0.7"

    # Optional metadata
    license = "https://raw.githubusercontent.com/jmuelber/jmbde-QT-models/master/LICENSE"
    author = "Jürgen Mülbert <juergen.muelbert@gmail.com>"
    url = "https://github.com/jmuelbert/jmbde-QT-models"
    description = "The models lib for the jmbde datamodel"
    topics = ("jmbde", "jmbdemodels", "datamodel", "qt", "qt6")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    options = dict(
        {
            "build_static": [True, False],
            "build_examples": [True, False],
            "build_tests": [True, False],
            "build_docs": [True, False],
            "fPIC": [True, False],
        }
    )

    default_options = dict(
        {
            "build_static": False,
            "build_examples": False,
            "build_tests": False,
            "build_docs": True,
            "fPIC": True,
        }
    )

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "CMakeLists_files.cmake", "cmake/*", "src/*", "include/*", "test_package/*"

    def requirements(self):
        self.requires("cmake/3.21.3")
        self.requires("extra-cmake-modules/5.84.0")
        self.requires("qt/6.2.1")

    # def source(self):
    #     git = tools.Git(folder="")
    #     git.clone(self.url)
    #     git.checkout("%s"%self.version)

    def configure(self):
        # ~$ conan create -ks -o qt:qttools=True -o qt:qtsvg=True -o qt:qtdeclarative=True -o qt:qtremoteobjects=True -o qt:qtscxml=True
        self.options["qt"].qtsvg = True
        # self.options["qt"].qtdeclarative = True
        self.options["qt"].qttools = True
    
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):        
        tc = CMakeToolchain(self)
        # This writes the "conan_toolchain.cmake"
        tc.generate()

        deps = CMakeDeps(self)
        # This write all the config files (xxx-config.cmake)
        deps.generate()


    def build(self):
        cmake = CMake(self)

        # put definitions here so that they are re-used in cmake between
        # build() and package()
        cmake.definitions["SOME_DEFINITION_NAME"] = "On"
        # cmake.definitions["BUILD_TRANSLATIONS"] = self.options.build_static
        # cmake.definitions["BUILD_EXAMPLES"] = self.options.build_examples
        # cmake.definitions["BUILD_TESTS"] = self.options.build_tests
        cmake.configure()
        cmake.build()

        # run unit tests after the build
        if self.self.options.build_tests:
            cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["jmbdemodels"]
