import qbs
import qbs.File
import qbs.FileInfo

Product {
    name: "distribute"
    type: "installable"
    builtByDefault: false

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }

    Group {
        name: "Examples"
        prefix: "../examples/"
        files: ["**"]

        qbs.install: true
        qbs.installDir: "examples"
        qbs.installSourceBase: prefix
    }

    Group {
        name: "Misc Files"
        prefix: "../"
        files: {
            var list = [
                "LICENSE",
                "LICENSE.DE",
                "AUTHORS",
                "README.md",
                "NEWS.md",
            ];

            if (qbs.targetOS.contains("windows--"))
                 list.push("dist/win/qt.conf");
             else if (qbs.targetOS.contains("linux"))
                 list.push("dist/linux/qt.conf");
            return list;
        }
        qbs.install: true
        qbs.installDir: ""
    }
}
