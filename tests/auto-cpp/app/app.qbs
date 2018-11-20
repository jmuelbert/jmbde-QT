import qbs

Project {
	name: "AppsAutotests"
	condition: project.withAutotests
	references: [
        "models/models.qbs",
	]
}
