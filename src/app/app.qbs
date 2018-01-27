import qbs 1.0
import qbs.FileInfo
import qbs.TextFile

QtGuiApplication {
    name: "jmbde"
    targetName: name
    version: project.version

    Depends { name: "Qt"; submodules: ["core", "widgets", "sql", "printsupport", "help" ]; versionAtLeast: "5.9" }

    property bool qtcRunnable: false

    cpp.includePaths: ["."]
    cpp.frameworks: {
        var frameworks = [];
        if (qbs.targetOS.contains("macos")) {
            frameworks.push("Foundation");
        }
        return frameworks;
    }

    cpp.useRPaths: project.useRPaths
    cpp.rpaths: {
        if (qbs.targetOS.contains("darwin"))
            return ["@loader_path/../Frameworks"];
        else if (project.linuxArchive)
            return ["$ORIGIN/lib"];
        else
            return ["$ORIGIN/../lib"];
    }

    cpp.useCxxPrecompiledHeader: qbs.buildVariant != "debug"
    cpp.cxxLanguageVersion: "c++14"

    cpp.defines: {
        var defs = [
            "JMBDE_VERSION=" + version,
            "QT_NO_CAST_FROM_ASCII",
            "QT_NO_CAST_TO_ASCII",
            "QT_NO_URL_CAST_FROM_STRING",
            "_USE_MATH_DEFINES"
        ];
        if (project.snapshot)
            defs.push("JMBDE_SNAPSHOT");
        return defs; 
    }

    consoleApplication: false;

    Group {
        name: "Precompiled header"
        files: ["pch.h"]
        fileTags: ["cpp_pch_src"]
    }

    files: [
        "accountdatamodel.cpp",
        "accountdatamodel.h",
        "chipcarddatamodel.cpp",
        "chipcarddatamodel.h",
        "chipcarddoorsdatamodel.cpp",
        "chipcarddoorsdatamodel.h",
        "chipcardprofiledatamodel.cpp",
        "chipcardprofiledatamodel.h",
        "chipcardprofiledoordatamodel.cpp",
        "chipcardprofiledoordatamodel.h",
        "cityinputarea.cpp",
        "cityinputarea.h",
        "cityinputarea.ui",
        "citynamedatamodel.cpp",
        "citynamedatamodel.h",
        "commondatamodel.cpp",
        "commondatamodel.h",
        "companydatamodel.cpp",
        "companydatamodel.h",
        "computerdatamodel.cpp",
        "computerdatamodel.h",
        "computerinputarea.cpp",
        "computerinputarea.h",
        "computerinputarea.ui",
        "computersoftwaredatamodel.cpp",
        "computersoftwaredatamodel.h",
        "constants.h",
        "csvimportdialog.cpp",
        "csvimportdialog.h",
        "csvimportdialog.ui",
        "datamodel.cpp",
        "datamodel.h",
        "definitions.h",
        "departmentdatamodel.cpp",
        "departmentdatamodel.h",
        "departmentinputarea.cpp",
        "departmentinputarea.h",
        "departmentinputarea.ui",
        "devicenamedatamodel.cpp",
        "devicenamedatamodel.h",
        "devicetypedatamodel.cpp",
        "devicetypedatamodel.h",
        "documentsdatamodel.cpp",
        "documentsdatamodel.h",
        "employeeaccountdatamodel.cpp",
        "employeeaccountdatamodel.h",
        "employeedatamodel.cpp",
        "employeedatamodel.h",
        "employeedocumentdatamodel.cpp",
        "employeedocumentdatamodel.h",
        "employeeinputarea.cpp",
        "employeeinputarea.h",
        "employeeinputarea.ui",
        "faxdatamodel.cpp",
        "faxdatamodel.h",
        "functiondatamodel.cpp",
        "functiondatamodel.h",
        "functioninputarea.cpp",
        "functioninputarea.h",
        "functioninputarea.ui",
        "helpbrowser.cpp",
        "helpbrowser.h",
        "idatamodel.h",
        "index.theme",
        "inventorydatamodel.cpp",
        "inventorydatamodel.h",
        "jmbde.qrc",
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
        "mainwindow.ui",
        "manufacturerdatamodel.cpp",
        "manufacturerdatamodel.h",
        "manufacturerinputarea.cpp",
        "manufacturerinputarea.h",
        "manufacturerinputarea.ui",
        "mobiledatamodel.cpp",
        "mobiledatamodel.h",
        "mobileinputarea.cpp",
        "mobileinputarea.h",
        "mobileinputarea.ui",
        "osdatamodel.cpp",
        "osdatamodel.h",
        "osinputarea.cpp",
        "osinputarea.h",
        "osinputarea.ui",
        "phonedatamodel.cpp",
        "phonedatamodel.h",
        "phoneinputarea.cpp",
        "phoneinputarea.h",
        "phoneinputarea.ui",
        "placedatamodel.cpp",
        "placedatamodel.h",
        "preferencesdialog.cpp",
        "preferencesdialog.h",
        "preferencesdialog.ui",
        "printerdatamodel.cpp",
        "printerdatamodel.h",
        "processordatamodel.cpp",
        "processordatamodel.h",
        "processorinputarea.cpp",
        "processorinputarea.h",
        "processorinputarea.ui",
        "resource.cpp",
        "resource.h",
        "softwaredatamodel.cpp",
        "softwaredatamodel.h",
        "softwareinputarea.cpp",
        "softwareinputarea.h",
        "softwareinputarea.ui",
        "src.pro",
        "systemdatamodel.cpp",
        "systemdatamodel.h",
        "titledatamodel.cpp",
        "titledatamodel.h",
        "titleinputarea.cpp",
        "titleinputarea.h",
        "titleinputarea.ui",
        "zipcitymodel.cpp",
        "zipcitymodel.h",
        "zipcodemodel.cpp",
        "zipcodemodel.h",
    ]

    Properties {
        condition: qbs.targetOS.contains("macos")
        cpp.cxxFlags: ["-Wno-unknown-pragmas"]
        bundle.identifierPrefix: "de.juergen-muelbert"
        ib.appIconName: "jmbde-icon-mac"
        targetName: "jmbde"
    }

    Group {
        name: "macOS"
        condition: qbs.targetOS.contains("macos")
        files: [
            "Info.plist"
        ]
    }

    Group {
        condition: !qbs.targetOS.contains("darwin")
        qbs.install: true
        qbs.installDir: {
            if (qbs.targetOS.contains("windows")
                   || project.linuxArchivee)
                return ""
            else
                return "bin"
        }
        qbs.installSourceBase: product.buildDirectory
        fileTagsFilter: product.type
    }

    Group {
        name: "macOS (icons)"
        condition: qbs.targetOS.contains("macos")
        files: ["images/Assets.xcassets"]
    }

    Group {
        name: "Desktop file (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/applications"
        files: ["../../jmbde.desktop" ]
    }

    Group {
        name: "AppData file (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/metainfo"
        files: ["../../jmbde.appdata.xml" ]
    }

    Group {
        name: "Man Page (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/man/man1"
        files: ["../../man/jmbde.1" ]
    }

    Group { 
        name: "Icon 16x16 (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/icons/hicolor/16x16/apps"
        files: [ "images/16x16/jmbde.png" ]
    }

    Group {
        name: "Icon 32x32 (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/icons/hicolor/32x32/apps"
        files: [ "images/32x32/jmbde.png" ]
    }

    Group {
        name: "Icon scalable (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/icons/hicolor/scalable/apps"
        files: [ "images/scalable/jmbde.svg" ]
    }

    // This is necessary to install the app bundle (OS X)
    Group {
        fileTagsFilter: [ "bundle.content" ]
        qbs.install: true
        qbs.installDir: "."
        qbs.installSourceBase: product.buildDirectory
    }

    // Generate the jmbde.rc file in order to dynamically specify the version
    Group {
        name: "RC file (Windows)"
        files: [ "jmbde.rc.in" ]
        fileTags: [ "rcIn" ]
    }

      Rule {
        inputs: ["rcIn"]
        Artifact {
            filePath: {
                var destdir = FileInfo.joinPaths(product.moduleProperty("Qt.core",
                                                         "generatedFilesDir"), input.fileName);
                return destdir.replace(/\.[^\.]*$/,'')
            }
            fileTags: "rc"
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "prepare " + FileInfo.fileName(output.filePath);
            cmd.highlight = "codegen";

            cmd.sourceCode = function() {
                var i;
                var vars = {};
                var inf = new TextFile(input.filePath);
                var all = inf.readAll();

                var versionArray = project.version.split(".");
                if (versionArray.length == 3)
                    versionArray.push("0");

                // replace vars
                vars['VERSION'] = project.version;
                vars['VERSION_CSV'] = versionArray.join(",");

                for (i in vars) {
                    all = all.replace(new RegExp('@' + i + '@(?!\w)', 'g'), vars[i]);
                }

                var file = new TextFile(output.filePath, TextFile.WriteOnly);
                file.truncate();
                file.write(all);
                file.close();
            }

            return cmd;
        }
    }
}