import qbs 1.0
import qbs.Environment
import qbs.FileInfo

Project {
    minimumQbsVersion: "1.10.0"
    qbsSearchPaths: ["qbs-resources"]

    name: "JMBde"

    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.22";
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
        "src/jmbde/jmbde.qbs",
        "translations",
        "tests/tests.qbs",
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
            "scripts/*.bat",
            "scripts/*.sh",
            "scripts/*.py",
            "scripts/*.rb"
        ]
    }

    Product {
        name: "Text Documents"
        files: [
            "AUTHORS",
            "README.md",
            "CHANGELOG.md",
            "CONTRIBUTING.md",
            "CONTRIBUTORS",
            "LICENSE",
            "LICENSE.*",
            "NEWS.md"
        ]
    }

}
