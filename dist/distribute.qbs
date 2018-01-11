import qbs "1.0"
import qbs.File
import qbs.FileInfo

Product {
    name: "distribute"
    type: "installable"
    builtByDefault: false

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }

    Group {
        name: "QT DLLs"
        prefix: {
            if (qbs.targetOS.contains("windows")) {
                return Qt.core.binPath += "/"
            } else {
                return Qt.core.libPath += "/lib"
            }
        }

        property string postfix: {
            var suffix = "";
            if (qbs.targetOS.contains("windows") && qbs.debugInformation)
                suffix += "d";
            return suffix + cpp.dynamicLibrarySuffix;
        }

        files: {
            function addQtVersion(libs) {
                var result = [];
                for (i = 0; i < libs.length; ++i) {
                    var major = libs[i] + "." + Qt.core.versionMajor;
                    var minor = major + "." + Qt.core.versionMinor;
                    var patch = minor + "." + Qt.core.versionPatch;
                    result.push(libs[i], major, minor, patch);
            }
            return result;
        }

        var list = [];

        if (!Qt.core.frameworkBuild) {
            list.push(
                "Qt5Core" + postfix,
                "Qt5Gui" + postfix,
                "Qt5Network" + postfix,
                "Qt5Svg" + postfix,
                "Qt5Widgets" + postfix
                );
            }
            return list;

        }
        qbs.install: true;
        qbs.installDir: qbs.targetOS.contains("windows") ? "" : "lib"
    }

     Group {
        name: "Qt Platform Plugins"
        prefix: FileInfo.joinPaths(Qt.core.pluginPath, "/platforms/")
        files: pluginFiles
        excludeFiles: pluginExcludeFiles
        qbs.install: true
        qbs.installDir: "plugins/platforms"
    }

    Group {
        name: "Qt Platform Input Context Plugins"
        condition: qbs.targetOS.contains("linux")
        prefix: FileInfo.joinPaths(Qt.core.pluginPath, "/platforminputcontexts/")
        files: pluginFiles
        qbs.install: true
        qbs.installDir: "plugins/platforminputcontexts"
    }

    Group {
        name: "Qt Platform Theme Plugins"
        condition: qbs.targetOS.contains("linux")
        prefix: FileInfo.joinPaths(Qt.core.pluginPath, "/platformthemes/")
        files: pluginFiles
        qbs.install: true
        qbs.installDir: "plugins/platformthemes"
    }

    Group {
        name: "Qt Image Format Plugins"
        prefix: FileInfo.joinPaths(Qt.core.pluginPath, "/imageformats/")
        files: pluginFiles
        excludeFiles: pluginExcludeFiles
        qbs.install: true
        qbs.installDir: "plugins/imageformats"
    }

    Group {
        name: "Qt XCB GL Integration Plugins"
        condition: qbs.targetOS.contains("linux")
        prefix: FileInfo.joinPaths(Qt.core.pluginPath, "/xcbglintegrations/")
        files: pluginFiles
        qbs.install: true
        qbs.installDir: "plugins/xcbglintegrations"
    }

    Group {
        name: "Qt Icon Engine Plugins"
        condition: qbs.targetOS.contains("linux")
        prefix: FileInfo.joinPaths(Qt.core.pluginPath, "/iconengines/")
        files: pluginFiles
        qbs.install: true
        qbs.installDir: "plugins/iconengines"
    }

    Group {
        name: "Qt Translations"
        prefix: {
            if (qbs.targetOS.contains("windows")) {
                return FileInfo.joinPaths(Qt.core.binPath, "../translations/")
            } else if (qbs.targetOS.contains("linux")) {
                return FileInfo.joinPaths(Qt.core.libPath, "../translations/")
            }
        }
        files: {
            // Since Qt 5.5, the translations are split up by module and failing
            // to include all the .qm files results in the loading of the Qt
            // translator to fail (regardless of whether these modules are
            // actually used).
            var modules = ["",
                           "base",
                           "multimedia",
                           "quick1",
                           "script",
                           "xmlpatterns"];

            // TODO: Look into getting this list from the Tiled
            // 'translations.qbs' product.
            var languages = ["ar_DZ",
                             "bg",
                             "cs",
                             "de",
                             "en",
                             "es",
                             "fr",
                             "he",
                             "it",
                             "ja",
                             "lv",
                             "nb",
                             "nl",
                             "pl",
                             "pt",
                             "pt_PT",
                             "ru",
                             "tr",
                             "zh",
                             "zh_TW"];

            var list = [];
            var p = prefix;

            for (i = 0; i < languages.length; ++i) {
                for (j = 0; j < modules.length; ++j) {
                    var file = "qt" + modules[j] + "_" + languages[i] + ".qm";
                    if (File.exists(p + file))
                        list.push(file);
                }
            }

            return list;
        }
        qbs.install: true
        qbs.installDir: "translations"
    }

    Group {
        name: "Runtime DLLs"
        condition: qbs.targetOS.contains("windows")

        prefix: {
            if (qbs.toolchain.contains("mingw"))
                return FileInfo.joinPaths(cpp.toolchainInstallPath) + "/"
            else if (qbs.architecture === "x86_64")
                return "C:/windows/system32/"
            else
                return "C:/windows/SysWOW64/"
        }
        files: {
            if (qbs.toolchain.contains("mingw")) {
                return [
                    "libgcc_s_dw2-1.dll",
                    "libstdc++-6.dll",
                    "libwinpthread-1.dll",
                ]
            } else {
                return [
                    "MSVCP120.DLL",
                    "MSVCR120.DLL",
                ]
            }
        }
        qbs.install: true
        qbs.installDir: ""
    }

    Group {
        name: "Misc Files"
        prefix: "../"
        files: {
            var list = [
                "COPYING",
                "AUTHORS",
                "README.md",
                "NEWS.md",
                "LICENSE.APACHE",
                "LICENSE.BSD",
                "LICENSE.GPL",
            ];

            if (qbs.targetOS.contains("windows"))
                list.push("dist/win/qt.conf");
            else if (qbs.targetOS.contains("linux"))
                list.push("dist/linux/qt.conf");

            return list;
        }
        qbs.install: true
        qbs.installDir: ""
    }
}   

