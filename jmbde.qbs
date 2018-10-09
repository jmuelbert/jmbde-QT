import qbs 
import qbs.Environment

Project {

    qbsSearchPaths: "qbs"
    minimumQbsVersion: "1.8.0"

    property string minimumMacosVersion: "10.8"
    property bool withAutotests: qbs.buildVariant === "debug"
    property path app_source_tree: path
    property pathList additionalPlugins: []
    property pathList additionalLibs: []
    property pathList additionalTools: []
    property pathList additionalAutotests: []
    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.13";
    property bool snapshot: Environment.getEnv("JMBDE_SNAPSHOT")
    property bool release: Environment.getEnv("JMBDE_RELEASE")
    property bool installHeaders: false
    property bool useRPaths: true
    property bool windowsInstaller: false
    property bool withCode: true
    property bool withDocker: true
    property bool withDocumentation: false
    property bool withExamples: false
    property bool withTests: withCode
    property stringList autotestArguments: []
    property stringList autotestWrapper: []

    references: [
        "dist/archive.qbs",
        "dist/distribute.qbs",
        "dist/win/installer.qbs",
    ]

    SubProject {
        filePath: "docker/docker.qbs"
        Properties {
            condition: parent.withDocker
        }
    }

    SubProject {
        filePath: "doc/doc.qbs"
        Properties {
            condition: parent.withDocumentation
        }
    }

    SubProject {
        filePath: "src/src.qbs"
        Properties {
            condition: parent.withCode
        }
    }

    SubProject {
        filePath: "tests/tests.qbs"
        Properties {
            condition: parent.withTests
        }
    }

    SubProject {
        filePath: "translations/translations.qbs"
        Properties {
            condition: parent.withCode
        }
    }

    Product {
        name: "version"
        files: ["VERSION"]
    }

    Product {
        name: "qmake project files for qbs"
        files: ["**/*.pr[io]"]
    }
}
