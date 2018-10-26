import qbs

Project {
	name: "QbsAutotests"
	condition: project.withAutotests
	references: [
		"app/app.qbs",
		"utils/utils.qbs",
	]
}
