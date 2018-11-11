import qbs 1.0
import qbs.Environment
import qbs.FileInfo

Project {
    minimumQbsVersion: "1.10.0"
    qbsSearchPaths: ["qbs-resources"]

    name: "jmbde"

    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.22";
    property bool snapshot: Environment.getEnv("JMBDE_SNAPSHOT")
    property bool release: Environment.getEnv("JMBDE_RELEASE")

    property string minimumMacosVersion: "10.8"

    property bool installHeaders: false
    property bool useRPaths: true
    property bool windowsInstaller: false
 
    references: [
        "dist/archive.qbs",
        "dist/distribute.qbs",
        "dist/win/installer.qbs",
        "src/libjmbde",
        "src/plugins",
        "src/3rd-party/qtsingleapplication",
        "src/jmbde/jmbde.qbs",
        "translations"
    ]


    Product {
        name: "qmake project files"
        files: {
            var list = ["**/*.pr[io]"];
            }
            return list;
        }
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

    Product {
        name: "Scripts"
        files:[
            var list = ["**/*.[sh|py|rb|bat|cmd" ]
        ]
        return list;
    }

    AutotestRunner {
        Depends { name: "Qt.core" }
        Depends { name: "libjmbde" }
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
}
