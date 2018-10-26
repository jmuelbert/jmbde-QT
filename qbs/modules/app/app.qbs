import qbs
import qbs.Environment
import qbs.FileInfo
import "app.js" as HelperFunctions

Module {
    property string app_display_version: '0.4.13'
    property string app_version_major: '0'
    property string app_version_minor: '4'
    property string app_version_release: '13'
    property string app_version: app_version_major + '.' 
                            + app_version_minor + '.'
                            + app_version_release


    property string app_compat_version_major: '0'
    property string app_compat_version_minor: '4'
    property string app_compat_version_release: '13'
    property string app_compat_version: app_compat_version_major + '.' 
                            + app_compat_version_minor + '.'
                            + app_compat_version_release

    property string app_copyright_year: '2018'
    property string app_copyright_string: "(C) " + app_copyright_year + "Jürgen Mülbert"

    property string app_display_name: "jmbde"
    property string app_id: "jmbde"
    property string app_cased_id: "JMBDE"
    property string app_bundle_identifier: 'de.juergen-muelbert.jmbde'

    property string libDirName: "lib"
    property string app_app_path: qbs.targetOS.contains("macos") ? "" : "bin"
    property string app_app_target: qbs.targetOS.contains("macos") ? app_display_name : app_id
    property string app_library_path: {
        if (qbs.targetOS.contains("macos"))
            return app_app_target + ".app/Contents/Frameworks"
        else if (qbs.targetOS.contains("windows"))
            return app_app_path
        else   
            return libDirName + "/" + app_id
    }
    
    property string app_plugin_path: {
        if (qbs.targetOS.contains("macos"))
            return app_app_target + ".app/Contents/PlugIns"
        else if (qbs.targetOS.contains("windows"))
            return app_library_path + "/" + app_id + "/plugins"
        else
            return app_library_path + "/plugins"
    }

    property string app_data_path: qbs.targetOS.contains("macos")
            ? app_app_target + ".app/Contents/Resources"
            : "share/" + app_id

    property string app_libexec_path: qbs.targetOS.contains("macos")
            ? app_data_path : qbs.targetOS.contains("windows")
            ? app_app_path
            : "libexec/" + app_id
    property string app_bin_path: qbs.targetOS.contains("macos")
            ? app_app_target + "./app/Contents/MacOs"
            : app_app_path

    property string app_doc_path: qbs.targetOS.contains("macos")
            ? app_data_path + "/doc"
            : "share/doc/" + app_id

    property string app_include_path: "include"
    property string app_qbs_resources_path: "qbs-resources"
    property string app_qbs_modules_path: app_qbs_resources_path + "/modules"
    property string app_qbs_imports_path: app_qbs_resources_path + "/imports"
    property string app_shared_sources_path: "src/shared"

    property bool make_dev_package: false

    // Will be replaced when creating modules from products
    property string export_data_base: project.app_source_tree + "/share/" + app_id

    property bool testsEnabled: Environment.getEnv("TEST") || qbs.buildVariant === "debug"
    property stringList generalDefines: [
        "JMBDE",
        'APP_LIBRARY_BASENAME="' + libDirName + '"',
        'RELATIVE_PLUGIN_PATH="' + FileInfo.relativePath('/' + app_bin_path,
                                                         '/' + app_plugin_path) + '"',
        'RELATIVE_LIBEXEC_PATH="' + FileInfo.relativePath('/' + app_bin_path,
                                                          '/' + app_libexec_path) + '"',
        'RELATIVE_DATA_PATH="' + FileInfo.relativePath('/' + app_bin_path,
                                                       '/' + app_data_path) + '"',
        'RELATIVE_DOC_PATH="' + FileInfo.relativePath('/' + app_bin_path, '/' + app_doc_path) + '"',
        "QT_NO_CAST_TO_ASCII",
        "QT_RESTRICTED_CAST_FROM_ASCII",
        "QT_DISABLE_DEPRECATED_BEFORE=0x050600",
        "QT_USE_FAST_OPERATOR_PLUS",
        "QT_USE_FAST_CONCATENATION",
    ].concat(testsEnabled ? ["WITH_TESTS"] : [])
     .concat(qbs.toolchain.contains("msvc") ? ["_CRT_SECURE_NO_WARNINGS"] : [])

    Rule {
        condition: make_dev_package
        inputs: product.type.filter(function f(t) {
            return t === "dynamiclibrary" || t === "staticlibrary" || t === "app.dev-headers";
        })
        explicitlyDependsOn: ["qbs"]
        Artifact {
            filePath: product.name + "-module.qbs"
            fileTags: ["qtc.dev-module"]
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "Creating " + output.fileName;
            cmd.sourceCode = function() {
                var transformedExportBlock = HelperFunctions.transformedExportBlock(product, input,
                                                                                    output);
                HelperFunctions.writeModuleFile(output, transformedExportBlock);

            };
            return [cmd];
        }
    }
}
