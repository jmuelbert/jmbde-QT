import qbs 
import qbs.Environment
import qbs.FileInfo

Project {
    minimumQbsVersion: "1.10.0"

    name: "jmbde"
    qbsSearchPaths: ["qbs-resources"]
    
    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.23";
    property bool snapshot: Environment.getEnv("JMBDE_SNAPSHOT")
    property bool release: Environment.getEnv("JMBDE_RELEASE")
    property bool useStaticAnalyzer: false

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
        "src/jmbde/jmbde.qbs",
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
}
