import qbs
import qbs.Utilities

QbsAutotest {
    Depends { name: "Qt.core" }
    Depends { name: "Qt.sql" }
    Depends { name: "Utils" }

	name: "datacontext"

    cpp.includePaths: [
        project.app_source_tree + "/src/app",
        project.app_source_tree + "/src/app/models",
    ]

	files: [
        project.app_source_tree + "/src/app/models/datacontext.h",
        project.app_source_tree + "/src/app/models/datacontext.cpp",
        "tst_datacontext.h",
		"tst_datacontext.cpp",
	]

}

