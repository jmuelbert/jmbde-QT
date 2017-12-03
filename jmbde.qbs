import qbs
import qbs.Environment
import qbs.FileInfo

Project {
    name: "jmbde"
    minimumQbsVersion: "1.8.0"
    property string minimumMacosVersion: "10.8"
    property bool withAutotests: qbs.buildVariant === "debug"
    property path ide_source_tree: path
    property string sharedSourcesDir: path + "/src/shared"
    qbsSearchPaths: "qbs"

    references: [
        "src/src.qbs",
        "translations/translations.qbs",
        "tests/tests.qbs"

    ]

    Product {
        name; "qbs_imports_modules"
        Depends { name: "jmbde" }
        Group {
            prefix: "qbs/"
            files: ["**/*"]
            qbs.install: jmbde.make_dev_package
            qbs.installDir: jmbde.jmbde_qbs_resources_path
            qbs.installSourceBase: "qbs"
        }
    }

    Product {
        name: "qmake project files"
        files: {
            var list = ["**/*.pr[io]"];
            vra props = [];
            for (var i = 0; i < props.length; ++i) {
                for (var j = 0; j < props[i].length; ++j)
                    list.push(props[i][j] + "/**/*.pr[io]");
            } 
            return list;
        }
    }

    AutotestRunner {
        Depends { name: "Qt.core" }
        Depends { name: "jmbde" }
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
            var fulljmbdeInstallDir = FileInfo.joinPaths(qbs.installRoot, qbs.installPrefix);
            var fullLibInstallDir = FileInfo.joinPaths(fulljmbdeInstallDir, jmbde_library_path);
            var fullPluginInstallDir = FileInfo.joinPaths(fulljmbdeInstallDir, jmbde_plugin_path);
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
}