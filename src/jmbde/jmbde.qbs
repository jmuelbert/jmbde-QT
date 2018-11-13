import qbs  1.0
import qbs.FileInfo
import qbs.TextFile

QtGuiApplication {
    name: "jmbde"
    targetName: name
    version: project.version
    
    Depends { name: "libjmbde" }
    Depends { name: "translations" }
    Depends { name: "qtsingleapplication" }
    Depends { name: "ib"; condition: qbs.targetOS.contains("macos") }
    Depends { name: "Qt"; submodules: ["core", "widgets", "network", "sql", "printsupport", "help" ] }

    property bool qtcRunnable: true

    cpp.includePaths: [ "." ]
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
    cpp.cxxLanguageVersion: "c++17"

    cpp.defines: {
        var defs = [
            "JMBDE_VERSION=" + version,
            "QT_DEPRECATED_WARNINGS",
            "QT_DISABLE_DEPRECATED_BEFORE=0x050900",
            "QT_NO_CAST_FROM_ASCII",
            "QT_NO_CAST_TO_ASCII",
            "QT_NO_FOREACH",
            "QT_NO_URL_CAST_FROM_STRING",
            "_USE_MATH_DEFINES"
        ];
        if (project.snapshot)
            defs.push("JMBDE_SNAPSHOT");
        return defs;
    }

    consoleApplication: false

    Group {
        name: "Precompiled header"
        files: ["pch.h"]
        fileTags: ["cpp_pch_src"]
    }
 
    files: [
        "main.cpp",
        "help/helpbrowser.cpp",
        "help/helpbrowser.h",
        "models/accountdatamodel.cpp",
        "models/accountdatamodel.h",
        "models/chipcarddatamodel.cpp",
        "models/chipcarddatamodel.h",
        "models/chipcarddoorsdatamodel.cpp",
        "models/chipcarddoorsdatamodel.h",
        "models/chipcardprofiledatamodel.cpp",
        "models/chipcardprofiledatamodel.h",
        "models/chipcardprofiledoordatamodel.cpp",
        "models/chipcardprofiledoordatamodel.h",
        "models/citynamedatamodel.cpp",
        "models/citynamedatamodel.h",
        "models/commondatamodel.cpp",
        "models/commondatamodel.h",
        "models/companydatamodel.cpp",
        "models/companydatamodel.h",
        "models/computerdatamodel.cpp",
        "models/computerdatamodel.h",
        "models/computersoftwaredatamodel.cpp",
        "models/computersoftwaredatamodel.h",
        "models/datacontext.cpp",
        "models/datacontext.h",
        "models/datacontext.qrc",
        "models/datamodel.cpp",
        "models/datamodel.h",
        "models/departmentdatamodel.cpp",
        "models/departmentdatamodel.h",
        "models/devicenamedatamodel.cpp",
        "models/devicenamedatamodel.h",
        "models/devicetypedatamodel.cpp",
        "models/devicetypedatamodel.h",
        "models/documentsdatamodel.cpp",
        "models/documentsdatamodel.h",
        "models/employeeaccountdatamodel.cpp",
        "models/employeeaccountdatamodel.h",
        "models/employeedatamodel.cpp",
        "models/employeedatamodel.h",
        "models/employeedocumentdatamodel.cpp",
        "models/employeedocumentdatamodel.h",
        "models/faxdatamodel.cpp",
        "models/faxdatamodel.h",
        "models/functiondatamodel.cpp",
        "models/functiondatamodel.h",
        "models/idatamodel.cpp",
        "models/idatamodel.h",
        "models/inventorydatamodel.cpp",
        "models/inventorydatamodel.h",
        "models/manufacturerdatamodel.cpp",
        "models/manufacturerdatamodel.h",
        "models/mobiledatamodel.cpp",
        "models/mobiledatamodel.h",
        "models/osdatamodel.cpp",
        "models/osdatamodel.h",
        "models/phonedatamodel.cpp",
        "models/phonedatamodel.h",
        "models/placedatamodel.cpp",
        "models/placedatamodel.h",
        "models/printerdatamodel.cpp",
        "models/printerdatamodel.h",
        "models/processordatamodel.cpp",
        "models/processordatamodel.h",
        "models/softwaredatamodel.cpp",
        "models/softwaredatamodel.h",
        "models/systemdatamodel.cpp",
        "models/systemdatamodel.h",
        "models/titledatamodel.cpp",
        "models/titledatamodel.h",
        "models/zipcitymodel.cpp",
        "models/zipcitymodel.h",
        "models/zipcodemodel.cpp",
        "models/zipcodemodel.h",
        "models/script.sql",
        "views/aboutdialog.cpp",
        "views/aboutdialog.h",
        "views/aboutdialog.ui",
        "views/chipcardinputarea.cpp",
        "views/chipcardinputarea.h",
        "views/chipcardinputarea.ui",
        "views/cityinputarea.cpp",
        "views/cityinputarea.h",
        "views/cityinputarea.ui",
        "views/computerinputarea.cpp",
        "views/computerinputarea.h",
        "views/computerinputarea.ui",
        "views/csvimportdialog.cpp",
        "views/csvimportdialog.h",
        "views/csvimportdialog.ui",
        "views/departmentinputarea.cpp",
        "views/departmentinputarea.h",
        "views/departmentinputarea.ui",
        "views/employeeinputarea.cpp",
        "views/employeeinputarea.h",
        "views/employeeinputarea.ui",
        "views/functioninputarea.cpp",
        "views/functioninputarea.h",
        "views/functioninputarea.ui",
        "views/mainwindow.cpp",
        "views/mainwindow.h",
        "views/mainwindow.ui",
        "views/manufacturerinputarea.cpp",
        "views/manufacturerinputarea.h",
        "views/manufacturerinputarea.ui",
        "views/mobileinputarea.cpp",
        "views/mobileinputarea.h",
        "views/mobileinputarea.ui",
        "views/osinputarea.cpp",
        "views/osinputarea.h",
        "views/osinputarea.ui",
        "views/phoneinputarea.cpp",
        "views/phoneinputarea.h",
        "views/phoneinputarea.ui",
        "views/preferencesdialog.cpp",
        "views/preferencesdialog.h",
        "views/preferencesdialog.ui",
        "views/printerinputarea.cpp",
        "views/printerinputarea.h",
        "views/printerinputarea.ui",
        "views/processorinputarea.cpp",
        "views/processorinputarea.h",
        "views/processorinputarea.ui",
        "views/softwareinputarea.cpp",
        "views/softwareinputarea.h",
        "views/softwareinputarea.ui",
        "views/titleinputarea.cpp",
        "views/titleinputarea.h",
        "views/titleinputarea.ui",
    ]

   
    Properties {
        condition: qbs.targetOS.contains("darwin")
        cpp.cxxFlags: ["-Wno-unknown-pragmas"]        
        bundle.identifierPrefix: "io.github.jmuelbert"
        bundle.identifier: "io.github.jmuelbert.jmBDE"
        ib.appIconName: "jmbde-icon-mac"
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
                    || project.linuxArchive)
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
        files: ["images/jmbde.xcassets"]
    }

    Group {
        name: "Desktop file (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/applications"
        files: [ "../../dist/linux/desktop/io.github.jmuelbert.jmbde.desktop" ]
    }

    Group {
        name: "AppData file (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/metainfo"
        files: [ "../../dist/linux/desktop/io.github.jmuelbert.jmbde.appdata.xml" ]
    }

    Group {
        name: "Man page (Linux)"
        condition: qbs.targetOS.contains("linux")
        qbs.install: true
        qbs.installDir: "share/man/man1"
        files: [ "../../dist/linux/man/jmbde.1" ]
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

    // Generate the tiled.rc file in order to dynamically specify the version
    Group {
        name: "RC file (Windows)"
        files: [ "jmbde.rc.in" ]
        fileTags: ["rcIn"]
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
