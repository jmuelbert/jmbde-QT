import qbs
import qbs.File
import qbs.FileInfo

Project {
	references: [ "man/man.qbs" ]

	Product {
        name: "jmbde documentation"
        builtByDefault: false
        type: ["qch", "app.doc-html-fixed" ]
		property string fixedHtmlDir: FileInfo.joinPaths(buildDirectory, "qdoc-html-fixed")

		Depends { name: "Qt.core" }
        Depends { name: "qbsbuildconfig" }
        Depends { name: "qbsversion" }

		files: [
			"../README.md",
			"app.qdoc",
			"app-online.qdocconf",
			"config/*.qdocconf",
			"reference/**/*",
			"templates/**/*",
			"images/**",
			"targets/**",
		]

		Group {
			name: "main qdocconf file"
			files: [
                "app.qdocconf",
            ]
			fileTags: "qdocconf-main"

		}

        property string versionTag: qbsversion.version.replace(/\.|-/g, "")
		Qt.core.qdocEnvironment: [
            "APP_VERSION=" + qbs.version.version,
			"SRCDIR=" + path,
			"QT_INSTALL_DOCS=" + Qt.core.docPath,
			"APP_VERSION_TAG=" + versionTag
		]
		
		Rule {
			inputs: [ "qdoc-html" ]
			Artifact {
				filePath: FileInfo.joinPaths(product.fixedHtmlDir, input.fileName)
				fileTags: [ "appdoc.qdoc-html-fixed" ]
			}
           prepare: {
                var cmd = new JavaScriptCommand();
                cmd.silent = true;
                cmd.sourceCode = function() { File.copy(input.filePath, output.filePath); }
                return [cmd];
            }
        }

        Group {
            fileTagsFilter: ["appdoc.qdoc-html-fixed"]
            qbs.install: qbsbuildconfig.installHtml
            qbs.installDir: qbsbuildconfig.docInstallDir
            qbs.installSourceBase: product.fixedHtmlDir
        }

        Group {
            fileTagsFilter: ["qdoc-css", "qdoc-png"]
            qbs.install: qbsbuildconfig.installHtml
            qbs.installDir: qbsbuildconfig.docInstallDir
            qbs.installSourceBase: Qt.core.qdocOutputDir
        }

        Group {
            fileTagsFilter: ["qch"]
            qbs.install: qbsbuildconfig.installQch
            qbs.installDir: qbsbuildconfig.docInstallDir
        }
    }
}
