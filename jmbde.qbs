import qbs 1.0
import qbs.Environment
import qbs.FileInfo

Project {
    minimumQbsVersion: "1.10.0"
    qbsSearchPaths: ["qbs-resources"]

    name: "JMBde"

    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.25";
    property bool snapshot: Environment.getEnv("JMBDE_SNAPSHOT")
    property bool release: Environment.getEnv("JMBDE_RELEASE")

    property string minimumMacosVersion: "10.8"

    property bool installHeaders: false
    property bool useRPaths: true
    property bool windowsInstaller: false

    property pathList additionalPlugins: []
    property pathList additionalLibs: []
    property pathList additionalTools: []
    property pathList additionalAutotests: []
 
    references: [
        "dist/archive.qbs",
        "dist/distribute.qbs",
        "dist/win/installer.qbs",
        "src/libjmbde",
        "src/plugins",
        "src/3rd-party/qtsingleapplication",
        "src/jmbde",
        "src/jmbdequick",
        "translations",
        "tests",
    ]


    Product {
        name: "qmake project files"
        files: {
            var list = ["**/*.pr[io]"];
        var props = [additionalPlugins, additionalLibs, additionalTools, additionalAutotests];
            for (var i = 0; i < props.length; ++i) {
                for (var j = 0; j < props[i].length; ++j)
                    list.push(props[i][j] + "/**/*.pr[io]");
            }
            return list;
        }
    }

    Product {
        name: "Script files"
        files: [
            "scripts/**/*.bat",
            "scripts/**/*.sh",
            "scripts/**/*.py",
            "scripts/**/*.rb",
            "scripts/**/s*.ps1",
            "dist/**/*.bat",
            "dist/**/*.sh",
            "dist/**/*.py",
            "dist/**/*.rb",
            "dist/**/*.ps1"
        ]
    }

    Product {
        name: "Installer Files"
        files: [
            "dist/**/*.nuspec",
            "dist/**/*.spec",
            "dist/**/*.appdata.*",
            "dist/**/*.desktop",
            "dist/**/*.ronn",
            "dist/**/*.1",
            "dist/**/*.conf",
            "dist/**/snapcraft*",
            "dist/**/*.wxs",

        ]
    }


    Product {
        name: "CI Files"
        files: [
            ".travis.yml",
            "appveyor.yml",
            ".clang-format",
            ".clog.toml",
            ".coafile",
            ".linthub.yml",
            ".mailmap"
        ]
    }

    Product {
        name: "Text Documents"
        files: [
            "AUTHORS",
            "README.md",
            "CHANGELOG.md",
            "CODE_OF_CONDUCT.md",
            "CONTRIBUTING.md",
            "CONTRIBUTORS",
            "LICENSE",
            "LICENSE.*",
            "NEWS.md",
            "dist/**/*.rtf"
        ]
    }

       SubProject {
        filePath: "dist/mac/dmg.qbs"

    }

}
