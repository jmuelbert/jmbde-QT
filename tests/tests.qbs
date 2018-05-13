import qbs

Project {
    references: [
        "auto/auto.qbs",
    ]

    AutotestRunner {
        Depends { name: "Qt.core" }
        Depends { name: "Qt.sql" }
        Depends { name: "jmbde" }


        arguments: project.autotestArguments
        wrapper: project.autotestWrapper
        environment: {
            var env = base
            if (qbs.hostOS.contains("windows") && qbs.targetOS.contains("windows")) {
                var path = "";
                for (var i = 0; i < env.length; ++i) {
                    if (env[i].startsWith("PATH=")) {
                        path = env[i].substring(5);
                        break;
                    }
                }
                path = Qt.core.binPath + ";" + path;
                var arrayElem = "PATH=" + path;
                if (i < env.length)
                    env[i] = arrayElem;
                else
                    env.push(arrayElem);
            }
            if (qbs.hostOS.contains("darwin") && qbs.targetOS.contains("darwin")) {
                env.push("DYLD_FRAMEWORK_PATH=" + Qt.core.libPath);
                env.push("DYLD_LIBRARY_PATH=" + Qt.core.libPath);
            }
            return env;
        }
    }
}
