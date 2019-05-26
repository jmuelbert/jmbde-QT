import qbs
import qbs.Utilities

QtApplication {
	name: "GUI Tests"

    type: [
        'application',
        'autotest',
    ]

    Depends { name: "Qt"
        submodules: [
            "core", 
            "widgets", 
            "network", 
            "sql", 
            "printsupport", 
            "help",
            "testlib" 
            ] 
    }

    Depends { name: "libjmbde" }

	Group {
		fileTagsFilter: "application"
		qbs.install: true
	}
    
    cpp.includePaths: [
        ".",
        "../../../src/jmbde",
        "../../../src/libjmbde",
    ]

	files: [
        "tst_employeeinputarea.cpp",
	]

}
