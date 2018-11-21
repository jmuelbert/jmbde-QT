import qbs

Product {
    name: 'jmbde-cpp-test'
    type: [
        'application',
        'autotest',
    ]

	Depends {
		name: 'Qt'
		submodules: [
			'testlib',
		]
	}

	Group {
		fileTagsFilter: "application"
		qbs.install: true
	}

	Group {
		name: "C++ source files"
		prefix: './'
		files: [
			"tst_test.cpp",
			"tst_test.h",
		]
	}
}
