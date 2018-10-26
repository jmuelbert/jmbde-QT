import qbs 
import qbs.Environment
import qbs.FileInfo

Project {
    name: "jmbde"
    qbsSearchPaths: [
        "qbs",
    ]

    minimumQbsVersion: "1.8.0"

    property string minimumMacosVersion: "10.8"
    property bool withAutotests: qbs.buildVariant === "debug"
    property path app_source_tree: path
    property pathList additionalPlugins: []
    property pathList additionalLibs: []
    property pathList additionalTools: []
    property pathList additionalAutotests: []
    property string sharedSourcesDir: path + "/src/shared"
    property string lib3rdPartyDir: path + "/src/libs/3rdparty"
   
    property bool windowsInstaller: false
    property bool withCode: true
    property bool withDocker: false
    property bool withDocumentation: true
    property bool withExamples: false
    property bool withTests: withCode
 
    references: [
        "doc/doc.qbs",
        "src/src.qbs",
        "share/share.qbs",
        "share/app/translations/translations.qbs",
        "share/bundledqt/bundledqt.qbs",
        "tests/tests.qbs",
        "doc/man/man.qbs",
        "dist/archive.qbs",
        "dist/distribute.qbs",
        "dist/win/installer.qbs",
        "src/lib/3rdparty/qtsingleapplication",
    ]

    Product {
        name: "qbs_import_modules"
        Depends { name: "app" }
        Group {
            prefix: "qbs/"
            files: ["**/*"]
            qbs.install: app.make_dev_package
            qbs.installDir: app.app_qbs_resources_path
            qbs.installSourceBase: "qbs"
        }
    }

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

    AutotestRunner {
        Depends { name: "Qt.core" }
        Depends { name: "app" }
        environment: {
            var env = base;
            if (!qbs.hostOS.contains("windows") || !qbs.targetOS.contains("windows"))
                return env;
            var path = "";
            for (var i = 0; i < env.length; ++i) {
                if (env[i].startsWith("PATH=")) {
                    path = env[i].substring(5);
                    break;
                }
            }
            var fullAppInstallDir = FileInfo.joinPaths(qbs.installRoot, qbs.installPrefix);
            var fullLibInstallDir = FileInfo.joinPaths(fullAppInstallDir, app.app_library_path);
            var fullPluginInstallDir = FileInfo.joinPaths(fullAppInstallDir, app.app_plugin_path);
            path = Qt.core.binPath + ";" + fullLibInstallDir + ";" + fullPluginInstallDir
                    + ";" + path;
            var arrayElem = "PATH=" + path;
            if (i < env.length)
                env[i] = arrayElem;
            else
                env.push(arrayElem);
            return env;
        }
    }
  
    SubProject {
        filePath: "docker/docker.qbs"
        Properties {
            condition: parent.withDocker
        }
    }

    Product {
        name: "version"
        files: ["VERSION"]
    }
}
