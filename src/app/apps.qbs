import qbs 
import qbs.FileInfo
import qbs.TextFile

QbsProduct {
    Depends { name: "bundle" }
    Depends { name: "ib"; condition: qbs.targetOS.contains("macos") }
  
    Properties {
        condition: qbs.targetOS.contains("macos")
        ib.appIconName: "jmbde"
    }

    Properties {
        condition: qbs.targetOS.contains("windows")
        consoleApplication: qbs.debugInformation
    }
 
    consoleApplication: false

    type: [ "application" ]
    name: "jmbde"
    targetName: app.app_app_target
    version: app.app_version

    property bool isBundle: qbs.targetOS.contains("darwin") && bundle.isBundle
    installDir: isBundle ? app.app_app_path : app.app_bin_path
    installTags: (isBundle ? ["bundle.content"] : base).concat(["debuginfo_app"])
    property bool qtcRunnable: true

    bundle.identifier: app.app_bundle_identifier
    bundle.infoPlist: ({
        "NSHumanReadableCopyright": app.app_copyright_string
    })

    cpp.rpaths: qbs.targetOS.contains("macos") ? ["@executable_path/../Frameworks"]
                                             : ["$ORIGIN/../" + app.libDirName + "/jmbde"]
    cpp.includePaths: [
        project.app_source_tree + "/src/",       
        project.app_source_tree + "/src/app",
    ]

    Depends { name: "app_version_header" }
    Depends { name: "Qt"; submodules: ["widgets", "network", "sql", "printsupport", "help" ] }
    Depends { name: "DataLib" }
    Depends { name: "Utils" }
    // Depends { name: "ExtensionSystem" }

    files: [
        "app-Info.plist",
        "main.cpp",
        "../shared/qtsingleapplication/src/qtsingleapplication.h",
        "../shared/qtsingleapplication/src/qtsingleapplication.cpp",
        "../shared/qtsingleapplication/src/qtlocalpeer.h",
        "../shared/qtsingleapplication/src/qtlocalpeer.cpp",
        "../shared/qtlockedfile/src/qtlockedfile.cpp",
               "jmbde.qrc",
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

    Group {
          // We need the version in two separate formats for the .rc file
          //  RC_VERSION=4,3,82,0 (quadruple)
          //  RC_VERSION_STRING="4.4.0-beta1" (free text)
          // Also, we need to replace space with \x20 to be able to work with both rc and windres
          cpp.defines: outer.concat(["RC_VERSION=" + app.app_version.replace(/\./g, ",") + ",0",
                                     "RC_VERSION_STRING=" + app.app_display_version,
                                     "RC_COPYRIGHT=2008-" + app.app_copyright_year
                                     + " Jürgen Mülbert".replace(/ /g, "\\x20")])
          files: "jmbde.rc"
      }

      Group {
          name: "jmbde.sh"
          condition: qbs.targetOS.contains("unix") && !qbs.targetOS.contains("macos")
          files: "../../bin/jmbdecreator.sh"
          qbs.install: true
          qbs.installDir: "bin"
      }

    Group {
        name: "QtLockedFile_unix"
        condition: qbs.targetOS.contains("unix")
        files: [
            "../shared/qtlockedfile/src/qtlockedfile_unix.cpp"
        ]
    }

    Group {
        name: "QtLockedFile_win"
        condition: qbs.targetOS.contains("windows")
        files: [
            "../shared/qtlockedfile/src/qtlockedfile_win.cpp"
        ]
    }
  }
