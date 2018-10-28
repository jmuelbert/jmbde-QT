import qbs 
import qbs.FileInfo
import qbs.TextFile

QtGuiApplication {
    readonly property bool isBundle: qbs.targetOS.contains("darwin") && bundle.isBundle
    readonly property string dataInstallDir: jmbdedeployment.dataDir + "/jmbde"

    name: "jmbde"
    targetName: {
        if (qbs.targetOS.contains("windows"))
            return "jmBDE";
        return name;
    }
    consoleApplication: false

    Depends { name: "jmbdedeployment" }
    Depends { name: "Qt"; submodules: ["core", "widgets", "network", "sql", "printsupport", "help" ] }
    Depends { name: "ib"; condition: qbs.targetOS.contains("macos") }
    Depends { name: "jmbdetranslations" }
    

    
    Properties {
        condition: qbs.targetOS.contains("darwin")
        bundle.identifierPrefix: "io.github.jmuelbert"
        bundle.identifier: "io.github.jmuelbert.jmBDE"
        bundle.infoPlist: ({"CFBundleIconFile": "io.liri.Text"})
    }

    cpp.defines: {
        var defines = base.concat([
            "TEXT_VERSION=" + project.version,
            'USER_LANGUAGE_PATH="/language-specs/"',
            "LANGUAGE_DB_VERSION=1"
        ]);
        if (qbs.targetOS.contains("windows"))
            defines.push('RELATIVE_LANGUAGE_PATH="/language-specs/"');
        else if (qbs.targetOS.contains("macos"))
            defines.push('RELATIVE_LANGUAGE_PATH="../Resources/language-specs/"');
        else if (qbs.targetOS.contains("linux"))
            defines.push('ABSOLUTE_LANGUAGE_PATH="' + dataInstallDir + '/language-specs/"');
        return defines;
    }

    cpp.includePaths: [
         project.app_source_tree + "/src/",
         project.app_source_tree + "/src/jmbde",
     ]

    Qt.core.resourcePrefix: "/"
    Qt.core.resourceSourceBase: sourceDirectory

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
        "../../resources/graphics/icons/io.github.jmuelbert.jmbde.icns",
        "../../resources/jmbde.rc",
        "../../resources/jmbde.qrc",
        "../../resources/icons.qrc"
    ]

    Group {
        name: "Resource Data"
        files: [

        ]
        fileTags: ["qt.core.resource_data"]
    }

    Group {
        name: "Translations"
        files: ["../../translations/*.ts"]
    }

     Group {
        qbs.install: true
        qbs.installDir: jmbdedeployment.binDir
        qbs.installSourceBase: destinationDirectory
        fileTagsFilter: isBundle ? ["bundle.content"] : ["application"]
    }

   Group {
        condition: qbs.targetOS.contains("unix") && !qbs.targetOS.contains("darwin") && !qbs.targetOS.contains("android")
        name: "Desktop File"
        files: ["../../resources/desktop/io.github.jmuelbert.jmbde.desktop.in"]
        fileTags: ["jmbde.desktop.template"]
    }

    Group {
        name: "Desktop File Translations"
        files: ["../../translations/io.github.jmuelbert.jmbde_*.desktop"]
        fileTags: ["jmbde.desktop.translations"]
    }

   Group {
        qbs.install: true
        qbs.installDir: jmbdedeployment.applicationsDir
        fileTagsFilter: "jmbde.desktop.file"
    }

    Group {
        condition: qbs.targetOS.contains("unix") && !qbs.targetOS.contains("darwin") && !qbs.targetOS.contains("android")
        name: "AppStream Metadata"
        files: ["../../resources/desktop/*.appdata.xml"]
        qbs.install: true
        qbs.installDir: jmbdedeployment.appDataDir
    }

    Group {
        condition: qbs.targetOS.contains("unix") && !qbs.targetOS.contains("darwin") && !qbs.targetOS.contains("android")
        name: "Icons"
        prefix: "../../resources/graphics/icons/hicolor/"
        files: ["**/*.png", "**/*.svg"]
        qbs.install: true
        qbs.installSourceBase: prefix
        qbs.installDir: jmbdedeployment.dataDir + "/icons/hicolor"
    }

    Group {
        fileTagsFilter: "qm"
        qbs.install: true
        qbs.installDir: {
            if (qbs.targetOS.contains("windows"))
                return "translations";
            else if (qbs.targetOS.contains("macos"))
                return "Contents/Resources/data/translations";
            else
                return dataInstallDir + "/translations";
        }
    }

    // Group {
          // We need the version in two separate formats for the .rc file
          //  RC_VERSION=4,3,82,0 (quadruple)
          //  RC_VERSION_STRING="4.4.0-beta1" (free text)
          // Also, we need to replace space with \x20 to be able to work with both rc and windres
          // cpp.defines: outer.concat(["RC_VERSION=" + app.app_version.replace(/\./g, ",") + ",0",
          //                           "RC_VERSION_STRING=" + app.app_display_version,
          //                           "RC_COPYRIGHT=2008-" + app.app_copyright_year
          //                           + " Jürgen Mülbert".replace(/ /g, "\\x20")])
          // files: "jmbde.rc"
      // }

}
