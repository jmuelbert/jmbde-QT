import qbs 1.0

DynamicLibrary {
    targetName: "jmbde"

    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: [
        "core", 
        "quick", 
        "quickwidgets",
        "widgets", 
        "network", 
        "sql", 
        "printsupport", 
        "help" 
        ] 
    }

    // Additional import path used to resolve QML modules in Qt Creator's code model
    property pathList qmlImportPaths: []

    Properties {
        condition: !qbs.toolchain.contains("msvc")
        cpp.dynamicLibraries: base.concat(["z"])
    }

    cpp.includePaths: [ ".", "../jmbde" ]
    cpp.cxxLanguageVersion: "c++14"
    cpp.visibility: "minimal"
    cpp.defines: [
        "JMBDE_LIBRARY",
        "QT_NO_CAST_FROM_ASCII",
        "QT_NO_CAST_TO_ASCII",
        "QT_NO_URL_CAST_FROM_STRING",
        "_USE_MATH_DEFINES"
    ]

    Properties {
        condition: qbs.targetOS.contains("macos")
        cpp.cxxFlags: ["-Wno-unknown-pragmas"]
    }

    Properties {
        condition: qbs.targetOS.contains("darwin")
        bundle.isBundle: false
        cpp.sonamePrefix: "@rpath"
    }

    files: [
        "libjmbde.qmlproject",
        "definitions.h",
        "qml/qml.qrc",
        "qml/qtquickcontrols2.conf",
        "images/res.qrc",
        "images/icons/tango/tango-icon.theme",
        "libjmbde_global.h",
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
        condition: project.installHeaders
        qbs.install: true
        qbs.installDir: "include/jmbde"
        fileTagsFilter: "hpp"
    }

        Export {
            Depends { name: "cpp" }
            Depends { name: "Qt"; 
            submodules: [
                "core",
                "quick",
                "quickwidgets",
                "widgets",
                "network",
                "sql",
                "printsupport",
                "help"
                ]
            }

            cpp.includePaths: "."
        }

        Group {
            condition: !qbs.targetOS.contains("darwin")
            qbs.install: true
        qbs.installDir: {
            if (qbs.targetOS.contains("windows"))
                return ""
            else
                return "lib"
        }
        fileTagsFilter: "dynamiclibrary"
    }
}
