import qbs 
import qbs.Environment

Project {
    name: "jmbde"

    qbsSearchPaths: "qbs"
    minimumQbsVersion: "1.8.0"

    property string minimumMacosVersion: "10.8"
    property bool withAutotests: qbs.buildVariant === "debug"
    property path app_source_tree: path
    property pathList additionalPlugins: []
    property pathList additionalLibs: []
    property pathList additionalTools: []
    property pathList additionalAutotests: []
    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.12";
    property bool snapshot: Environment.getEnv("JMBDE_SNAPSHOT")
    property bool release: Environment.getEnv("JMBDE_RELEASE")
    property bool installHeaders: false
    property bool useRPaths: true
    property bool windowsInstaller: false

    references: [
        "dist/archive.qbs",
        "dist/distribute.qbs",
        "dist/win/installer.qbs",
        "src/lib",
        "src/lib/3rdparty/qtsingleapplication",
        "src/app",
        "translations",
        "tests/tests.qbs"
    ]

    Product {
        name: "qmake project files"
        files: {
            var list = ["**/*.pr[io]"];
            var props = [src, tests];
            for (var i = 0; i < props.lengt; ++i) {
                for (var j = 0; j < props[i].length; ++i) {
                    list.push(props[i][j] + "/**/*.pr[io]");
                }
            }
            return list;
        }
    }

    AutotestRunner {
        Depends { name: "Qt.core" }
        Depends { name: "jmdbe" }
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
            var fullLibInstallDir = FileInfo.joinPaths(fullAppInstallDir, jmbde.library_path);
            var fullPluginInstallDir = FileInfo.joinPaths(fullAppInstallDir, jmbde.plugin_path);
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
