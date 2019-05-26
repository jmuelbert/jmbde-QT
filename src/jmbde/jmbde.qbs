import qbs 1.0
import qbs.File
import qbs.FileInfo
import qbs.TextFile

QtGuiApplication {
    name: "jmbde"
    targetName: name
    version: project.version
    
    Depends { name: "libjmbde" }
    Depends { name: "translations" }
    Depends { name: "qtsingleapplication" }
    Depends { name: "ib"; condition: qbs.hostOS.contains("macos") }
    Depends { name: "Qt"; submodules: ["core", "widgets", "network", "sql", "printsupport", "help" ] }

    property bool qtcRunnable: true

    cpp.includePaths: [ 
        ".", 
        "../libjmbde", 
        ]
        
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
        "jmbde.qrc",
    ]


    Properties {
        condition: qbs.targetOS.contains("darwin")
        cpp.cxxFlags: ["-Wno-unknown-pragmas"]        
        bundle.identifierPrefix: "io.github.jmuelbert"
        bundle.identifier: "io.github.jmuelbert.jmBDE"
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
        files: ["images/jmbde.iconset"]
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

   // This is necessary to install the app bundle (OS X)
   Group {
       fileTagsFilter: ["bundle.content"]
       qbs.install: true
       qbs.installDir: "."
       qbs.installSourceBase: product.buildDirectory
   }

   // Include libtiled.dylib in the app bundle
   Rule {
       condition: qbs.targetOS.contains("darwin")
       inputsFromDependencies: "dynamiclibrary"
       prepare: {
           var cmd = new JavaScriptCommand();
           cmd.description = "preparing " + input.fileName + " for inclusion in " + product.targetName + ".app";
           cmd.sourceCode = function() { File.copy(input.filePath, output.filePath); };
           return cmd;
       }

       Artifact {
           filePath: input.fileName
           fileTags: "bundle.input"
           bundle._bundleFilePath: product.destinationDirectory + "/" + product.targetName + ".app/Contents/Frameworks/" + input.fileName
       }
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
