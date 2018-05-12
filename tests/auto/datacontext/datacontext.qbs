import qbs
import qbs.Utilities

QbsAutotest {
    Depends { name: "qbsversion" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.sql" }

	testName: "datacontext"


	files: [
		"tst_datacontext.h",
		"tst_datacontext.cpp",
	]

    cpp.defines: base.concat(["APP_VERSION=" + Utilities.cStringQuote(qbsversion.version)])
}

