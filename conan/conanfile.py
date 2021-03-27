from conans import ConanFile, CMake, tools


class jmbdeQTConan(ConanFile):
    name = "jmbde-QT"
    version = "0.5.4"
    license = (
        "https: // raw.githubusercontent.com/jmuelber/jmbde-QT/master/LICENSE"
    )
    author = "Jürgen Mülbert juergen.muelbert@gmail.com"
    url = "https://github.com/jmuelbert/jmbde-QT.git"
    description = "A BDE tool."
    generators = "cmake"
    options = dict({
        "build_static": [True, False],
        "build_examples": [True, False],
        "build_tests": [True, False],
        "build_python_bindings": [True, False],
        "python_bindings_install_prefix": "ANY"
    })
    default_options = dict({
        "build_static": False,
        "build_examples": True,
        "build_tests": False,
        "build_python_bindings": False,
        "python_bindings_install_prefix": "ANY"
    })
    settings = "build_type"

    def requirements(self):
        # Kdab uses a custom qt build
        # To build qt with extra modules enabled use qt package from:
        #   https://github.com/bincrafters/conan-qt
        # Build the command:
        #   conan create -ks -o qt:qtsvg=True -o qt:qtdeclarative=True -o qt:qtremoteobjects=True -o qt:qtscxml=True . 5.13.2@kdab/stable
        self.requires("qt/5.15.2@kdab/stable")

    def source(self):
        git = tools.Git(folder="")
        git.clone(self.url)
        # We want cmake support, so use master for now
        # git.checkout("kdchart-%s-release"%self.version)

    def configure(self):
        # Use kdab flags to match qt package hash
        # ~$ conan create -ks -o qt:qttools=True -o qt:qtsvg=True -o qt:qtdeclarative=True -o qt:qtremoteobjects=True -o qt:qtscxml=True . 5.13.2@kdab/stable
        self.options["qt"].qtsvg = True
        self.options["qt"].qtdeclarative = True
        self.options["qt"].qtremoteobjects = True
        self.options["qt"].qtscxml = True
        self.options["qt"].qttools = True

    def build(self):
        self.cmake = CMake(self)
        self.cmake.definitions["BUILD_TRANSLATIONS"] = self.options.build_static
        self.cmake.definitions["KDChart_EXAMPLES"] = self.options.build_examples
        self.cmake.definitions["KDChart_TESTS"] = self.options.build_tests
        self.cmake.configure()
        self.cmake.build()

    def package(self):
        self.cmake.install()

    def package_info(self):
        self.env_info.CMAKE_PREFIX_PATH.append(self.package_folder)
