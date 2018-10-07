import qbs
import qbs.FileInfo
import qbs.Utilities

QtApplication {
    type: ["application", "autotest"]
    consoleApplication: true
    property string testName
    name: "tst_" + testName
    Depends { name: "Qt.testlib" }
    Depends { name: "jmbdedata" }
    Depends { name: "qbsbuildconfig" }
    cpp.defines: [
        "QBS_TEST_SUITE_NAME=" + Utilities.cStringQuote(testName.toUpperCase().replace("-", "_"))
    ]
    cpp.includePaths: [
        "../../../src",
        "../../../src/app/shared", // for the logger
    ]
    cpp.cxxLanguageVersion: "c++11"
    destinationDirectory: "bin"

    cpp.rpaths: [FileInfo.joinPaths(qbs.installRoot, qbs.installPrefix, qbsbuildconfig.libDirName)]
    qbs.commonRunEnvironment: ({
        "QBS_INSTALL_ROOT": qbs.installRoot
    })
}
